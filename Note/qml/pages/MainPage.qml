import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.LocalStorage 2.0
import "../assets/Database.js" as JS

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    SilicaListView {
        anchors.fill: parent
        model: ListModel { id: noteModel }

        delegate: ListItem {

            menu: ContextMenu {
                 MenuItem {
                    text: qsTr("Изменить")
                    onClicked: {
                        var dialog = pageStack.push(
                                    Qt.resolvedUrl("CreateNoteDialog.qml"),
                                    { "noteId" : noteId, "note" : noteText, "date" : noteDate }
                                    )
                        dialog.onAccepted.connect(function () {
                            onDialogResult(dialog.noteId, dialog.date, dialog.note)
                        });
                    }
                 }
                 MenuItem {
                    text: qsTr("Удалить")
                    onClicked: {
                        JS.dbRemove(noteId)
                        updateNoteList()
                    }
                 }
             }


            Column {
                Label {
                    text: new Date(noteDate).toLocaleDateString()
                }
                Label {
                    text: noteText
                }
            }
        }

        header: PageHeader {
            objectName: "pageHeader"
            title: qsTr("Список заметок")
        }

        PullDownMenu {
            quickSelect: true
            MenuItem {
                text: "Добавить заметку"
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("CreateNoteDialog.qml"))
                    dialog.onAccepted.connect(function () {
                        onDialogResult(null, dialog.date, dialog.note)
                    });
                }
            }
        }
    }

    Component.onCompleted: {
        JS.dbInit()
        updateNoteList()
    }

    /** Обновляем список заметок на экране. В идеале нужна привязка через модель. */
    function updateNoteList() {
      return JS.dbReadAll()
    }

    /** Обрабатываем результат закрывшегося диалога */
    function onDialogResult(noteId, noteDate, noteText){
        console.log("id: " + noteId)
        console.log("date: " + noteDate)
        console.log("text: " + noteText)

        if(isNaN(noteDate) === true || !noteText) {
            Notices.show(
                  "Дата или текст заметки навалидны",
                  Notice.Short,
                  Notice.Bottom,
                  0,
                  -Theme.horizontalPageMargin
            )
        } else {
            if(noteId){
               JS.dbUpdate(noteId, noteDate, noteText)
            } else {
                JS.dbInsert(noteDate, noteText)
            }
            updateNoteList()
        }
    }
}
