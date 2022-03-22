TARGET=$${NAME}

CONFIG += sailfishapp

DEFINES += APP_VERSION=\"\\\"$${VERSION}\\\"\"

SOURCES += src/harbour-tide.cpp \
    src/realhighlighter.cpp \
    src/documenthandler.cpp \
    src/iconprovider.cpp \
    src/keyboardshortcut.cpp \
    src/helper.cpp

OTHER_FILES += qml/harbour-tide.qml \
    qml/cover/CoverPage.qml \
    qml/pages/CreateProject.qml \
    qml/pages/ProjectHome.qml \
    qml/pages/CreatorHome.qml \
    qml/pages/AddFileDialog.qml \
    qml/pages/AppOutput.qml \
    qml/pages/RestoreDialog.qml \
    qml/pages/BuildOutput.qml \
    qml/pages/MainPage.qml \
    qml/pages/FileManagerPage.qml \
    qml/pages/SettingsPage.qml \
    translations/*.ts

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256

CONFIG += sailfishapp_i18n

TRANSLATIONS += translations/harbour-tide-sv.ts\
    translations/harbour-tide-nl.ts

DISTFILES += \
    qml/python/createProject.py \
    qml/python/startProject.py \
    qml/python/openFile.py \
    qml/python/editFile.py \
    qml/python/addFile.py \
    qml/python/stopProject.py \
    qml/python/buildRPM.py \
    qml/python/settings.py \
    qml/pages/AboutPage.qml \
    qml/python/deleteProject.py \
    qml/pages/SplitPage.qml \
    qml/pages/EditorPage.qml \
    qml/components/TopBar.qml \
    qml/components/EditorArea.qml \
    qml/components/LineNumArea.qml \
    qml/components/FileManagerComponent.qml

HEADERS += \
    src/realhighlighter.h \
    src/documenthandler.h \
    src/iconprovider.h \
    src/keyboardshortcut.h \
    src/helper.h

RESOURCES += \
    src/dictionarys.qrc
