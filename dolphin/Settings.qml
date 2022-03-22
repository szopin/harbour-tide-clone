import QtQuick 2.2
import Sailfish.Silica 1.0
import harbour.tide.keyboard 1.0
import org.nemomobile.configuration 1.0

Item {
    id: settings

    property alias spacebar: _spacebar.value
    property alias keys: _keys.value
    property alias word: _word.value
    property alias fusion: _fusion.value
    property alias enMode: _enMode.value
    property alias swipe: _swipe.value

    property alias tabsize: _tabsize.value

    property alias scale: _scale.value
    property alias size: _size.value
    property alias toolbar: _toolbar.value
    property alias background: _background.value
    property alias transparency: _transparency.value


    //

    ConfigurationValue {
        id: _spacebar
        key: "/apps/harbour-tide-keyboard/settings/keyboard/spacebar"
        defaultValue: false
    }

    ConfigurationValue {
        id: _keys
        key: "/apps/harbour-tide-keyboard/settings/keyboard/keys"
        defaultValue: true
    }

    ConfigurationValue {
        id: _word
        key: "/apps/harbour-tide-keyboard/settings/keyboard/word"
        defaultValue: true
    }

    ConfigurationValue {
        id: _fusion
        key: "/apps/harbour-tide-keyboard/settings/keyboard/fusion"
        defaultValue: false
    }

    ConfigurationValue {
        id: _enMode
        key: "/apps/harbour-tide-keyboard/settings/keyboard/enmode"
        defaultValue: false
    }

    ConfigurationValue {
        id: _swipe
        key: "/apps/harbour-tide-keyboard/settings/keyboard/swipe"
        defaultValue: false
    }

    ConfigurationValue {
        id: _tabsize
        key: "/apps/harbour-tide-keyboard/settings/appearance/tabsize"
        defaultValue: false
    }

    //Appearance

    ConfigurationValue {
        id: _scale
        key: "/apps/harbour-tide-keyboard/settings/appearance/scale"
        defaultValue: 1
    }

    ConfigurationValue {
        id: _size
        key: "/apps/harbour-tide-keyboard/settings/appearance/size"
        defaultValue: 1
    }

    ConfigurationValue {
        id: _background
        key: "/apps/harbour-tide-keyboard/settings/appearance/background"
        defaultValue: ""
    }

    ConfigurationValue {
        id: _transparency
        key: "/apps/harbour-tide-keyboard/settings/appearance/transparency"
        defaultValue: 1
    }

    //Tooblar
    ConfigurationValue {
        id: _toolbar
        key: "/apps/harbour-tide-keyboard/settings/appearance/toolbar"
        defaultValue: 1
    }



}
