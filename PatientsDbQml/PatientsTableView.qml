import QtQuick 2.15
import QtQuick.Window 2.1
import QtQuick.Controls 2.15

/**
 * Таблица пациентов
 */
Item {

    HorizontalHeaderView {
        id: patientsHorizontalHeader
        syncView: patientsTableView
    }

    TableView {
        id: patientsTableView
        width: parent.width
        height: parent.height
        anchors.left: patientsHorizontalHeader.left
        anchors.top: patientsHorizontalHeader.bottom

        columnWidthProvider: function (column) {
            switch (column) {
            case 2:
                return 80
            default:
                return 150
            }
        }
        rowHeightProvider: function (column) {
            return 40
        }

        model: patientsModel

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
                id: patientsMauseArea
                anchors.fill: parent
                onClicked: {
                    console.log("QML: нажата строка с индексом " + model.row)
                    patientsModel.onRowClick(model.row)
                }
            }
        }
    }
}
