import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    Column {
        anchors.centerIn: parent
        width: parent.width

        TextField {
            id: notificationText
            width: parent.width
            placeholderText: qsTr("Введите текст для уведомления")
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Отправить")
            onClicked: {
                clickListener.notify(notificationText.text.toString())
            }
        }
    }
}
