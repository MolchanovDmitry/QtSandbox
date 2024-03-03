import QtQuick 2.15
import QtQuick.Window 2.1
import QtQuick.Controls 2.15

Window {
    width: 1340
    height: 570
    visible: true
    title: qsTr("База пациентов")

    PatientsTableView {
        id: patientsTableView
        width: 380
        height: parent.height
        anchors.left: parent.left
        anchors.top: menuBar.bottom
    }

    Text {
        id: text1
        anchors.left: patientsTableView.right
        anchors.top: patientsTableView.top
        anchors.margins: 18
        color: "black"
        text: patientInfoModel.text
        font.pixelSize: 20
    }

    ResearchTableView {
        width: 500
        height: 500
        anchors.left: patientsTableView.right
        anchors.top: patientsTableView.verticalCenter
    }

    CustomMenuBar {
        id: menuBar
    }
}
