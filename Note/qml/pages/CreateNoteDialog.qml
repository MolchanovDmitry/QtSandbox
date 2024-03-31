import QtQuick 2.0
import Sailfish.Silica 1.0
import "../assets/Database.js" as JS

Dialog {
    objectName: "aboutPage"
    allowedOrientations: Orientation.All

    property int noteId: null
    property string note: null
    property date date: null
    Column {
        anchors.fill: parent
        DialogHeader {
            acceptText: qsTr("Save")
            cancelText: qsTr("Cancel")
        }

        Button {
            property date pickedDate

            id: button
            text: {
                console.log("date " + date)
                var buttonText = qsTr("select_date")
                if (!isNaN(date)) {
                    buttonText = date
                    pickedDate = date
                }
                buttonText
            }
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: {
                var dialog = pageStack.push(pickerComponent, {
                                                "date": new Date()
                                            })
                dialog.accepted.connect(function () {
                    pickedDate = dialog.date
                    button.text = dialog.dateText
                })
            }

            Component {
                id: pickerComponent
                DatePickerDialog {}
            }
        }

        TextArea {
            id: noteArea
            placeholderText: qsTr("note_input")
            text: note
        }
    }

    onAccepted: {
        date = button.pickedDate
        note = noteArea.text
    }
}
