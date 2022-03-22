#!/usr/bin/env python
# -*- coding: utf-8 -*-

import pyotherside
import os, shutil, tarfile, pty, sys, re, glob
from select import select
from subprocess import PIPE, Popen, STDOUT
from threading import Thread
import signal

process =None
bgthread =None
buildP =None
name=None

def createBuildDir(projectName, buildPath, projectPath):
    try:
        if not os.path.exists(buildPath):
            os.makedirs(buildPath +"/BUILD")
            os.makedirs(buildPath +"/SOURCES")
            os.makedirs(buildPath +"/SPECS")
            os.makedirs(buildPath +"/BUILDROOT/")
        if os.path.exists(buildPath +"/"+ projectName):
            #create new
            shutil.rmtree(buildPath +"/"+ projectName)
        getReady(projectName, buildPath, projectPath)
    except:
        raise

def getReady(projectName, buildPath, projectPath):
    #Find the specfile
    for file in glob.glob(projectPath+"/"+ projectName+"/rpm/*" + ".spec"):
        specfile = file
    #Read the version
    spec = open(specfile, 'r')
    spectxt = spec.read()
    spec.close()
    version=re.search('(?<=Version:).*',spectxt).group(0).strip()
    global name
    name = re.search('(?<=Name:).*',spectxt).group(0).strip()
    if("version" in re.search('(?<=%setup -q -n %{).*',spectxt).group(0).strip()):#if spec file prep includes version
        with tarfile.open(name+"-"+version+".tar.bz2", "w:bz2") as tar:
            tar.add(projectPath+"/"+ projectName, arcname=name+"-"+version)#os.path.basename(projectPath+"/"+ projectName))
    else:#if it doesnt include
        with tarfile.open(name+"-"+version+".tar.bz2", "w:bz2") as tar:
            tar.add(projectPath+"/"+ projectName, arcname=name)#os.path.basename(projectPath+"/"+ projectName))
    shutil.move(name+"-"+version+".tar.bz2", buildPath+"/SOURCES/"+name+"-"+version+".tar.bz2")
    shutil.copy(specfile, buildPath+"/SPECS/"+name+".spec")
    global buildP
    buildP =buildPath

def build():
    master_fd, slave_fd = pty.openpty()
    global process
    process = Popen(["rpmbuild", "-ba", buildP+"/SPECS/"+name+".spec"], stdin=slave_fd, stdout=slave_fd, stderr=STDOUT, bufsize=0, close_fds=True)
    pyotherside.send('pid', process.pid)
    timeout = .1
    with os.fdopen(master_fd, 'r+b', 0) as master:
        input_fds = [master, sys.stdin]
        while True:
            fds = select(input_fds, [], [], timeout)[0]
            if master in fds: # subprocess' output is ready
                data = os.read(master_fd, 512) # <-- doesn't block, may return less
                if not data: # EOF
                    input_fds.remove(master)
                else:
                    os.write(sys.stdout.fileno(), data) # copy to our stdout
                    pyotherside.send('output', {'out':data})
            if sys.stdin in fds: # got user input
                data = os.read(sys.stdin.fileno(), 512)
                if not data:
                    input_fds.remove(sys.stdin)
                else:
                    master.write(data) # copy it to subprocess' stdin
            if not fds: # timeout in select()
                if process.poll() is not None: # subprocess ended
                    # and no output is buffered <-- timeout + dead subprocess
                    assert not select([master], [], [], 0)[0] # race is possible
                    os.close(slave_fd) # subproces don't need it anymore
                    break
    rc = process.wait()
    pyotherside.send('output', {'out':"subprocess exited with status %d" % rc})
    process.kill()

def init():
    global bgthread
    bgthread = Thread(target=build)
    return "create"

def start_proc():
    bgthread.start()
    return "started"

def kill():
    if(process.pid):
        try:
            os.kill(process.pid, signal.SIGTERM)
        except ProcessLookupError:
            bgthread = None
    process.wait()
    bgthread = None
    return "stopperd"
