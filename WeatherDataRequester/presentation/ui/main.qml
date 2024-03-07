import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Погодные данные")

    Button {
        id: updateButton
        text: "Обновить"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        onClicked: updUpdateButtonClickDelegate.onUpdateButtonClick()
    }

    Text {
        width: 500
        height: 480
        anchors.top: updateButton.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: weatherModel.text
        color: "black"
    }
}
