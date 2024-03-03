import QtQuick 2.15
import QtQuick.Window 2.1
import QtQuick.Controls 2.15

/**
 * Кастомное меню
 */
MenuBar {

    Menu {
        title: qsTr("Файл")
        width: 420

        Instantiator {
            model: menuBarClickDelegate
        }

        MenuItem {
            text: qsTr("Открыть внутреннюю базу данных")
            onClicked: {
                menuBarClickDelegate.onOpenInternalDbClicked()
            }
        }
    }
}
