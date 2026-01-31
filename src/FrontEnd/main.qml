import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: "QtQuick App"

    Button {
        text: "Hello QtQuick!"
        anchors.centerIn: parent
    }
}