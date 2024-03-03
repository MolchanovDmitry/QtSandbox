import QtQuick 2.15
import QtQuick.Window 2.1
import QtQuick.Controls 2.15


/**
 * Таблица исследований
 */
Item {
    HorizontalHeaderView {
        id: researchHorizontalHeader
        syncView: researchTableView
    }

    TableView {
        id: researchTableView
        width: parent.width
        height: parent.height
        anchors.left: researchHorizontalHeader.left
        anchors.top: researchHorizontalHeader.bottom

        columnWidthProvider: function (column) {
            switch (column) {
            case 2:
                return 80
            case 3:
                return 400
            default:
                return 150
            }
        }
        rowHeightProvider: function (column) {
            return 35
        }

        model: researchModel

        delegate: Rectangle {
            Text {
                text: display
                anchors.fill: parent
                anchors.margins: 10
                color: 'black'
                font.pixelSize: 15
                verticalAlignment: Text.AlignVCenter
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("QML: нажата строка с индексом " + model.row)
                    researchModel.onRowClick(model.row)
                }
            }
        }
    }
}
