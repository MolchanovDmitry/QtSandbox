import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    PageHeader { title: qsTr("Ввод логина и номера") }
    Column {
        anchors.centerIn: parent
        width: parent.width

        TextField {
            property bool shouldHighlightError: false

            id: loginText
            width: parent.width
            placeholderText: qsTr("Логин")
            labelVisible: true
            inputMethodHints: Qt.ImhNoAutoUppercase
            validator: RegExpValidator {
                regExp: /^(?=.*[A-Za-z0-9]$)[A-Za-z][A-Za-z\d.-]{0,19}$/
            }
            onTextChanged: {
                placeholderText = "Логин"
                label = ""
                shouldHighlightError = false
            }
        }

        TextField {
            property bool shouldHighlightError : false

            id: phoneText
            width: parent.width
            placeholderText: qsTr("Номер телефона")
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            validator: RegExpValidator {
                regExp: /^(\+\d{1,2}\s?)?\(?\d{3}\)?[\s.-]?\d{3}[\s.-]?\d{4}$/
            }
            onTextChanged: {
                placeholderText = "Номер телефона"
                label = ""
                shouldHighlightError = false
            }
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Дальше")
            onClicked: {
                var isAllFieldsCoorect = true
                if(loginText._isEmpty){
                    isAllFieldsCoorect = false
                    loginText.shouldHighlightError = true
                    loginText.placeholderText = "Введите логин"
                    loginText.placeholderColor = Theme.errorColor
                }
                if(loginText.errorHighlight){
                    isAllFieldsCoorect = false
                    loginText.shouldHighlightError = true
                    loginText.label = "Логин некорректного формата"
                }
                if(phoneText._isEmpty){
                    isAllFieldsCoorect = false
                    phoneText.shouldHighlightError = true
                    phoneText.placeholderText = "Введите номер телефона"
                    phoneText.placeholderColor = Theme.errorColor
                }
                if(phoneText.errorHighlight){
                    isAllFieldsCoorect = false
                    phoneText.shouldHighlightError = true
                    phoneText.label = "Номер телефона некорректного формата"
                }

                if(isAllFieldsCoorect){
                    pageStack.push(Qt.resolvedUrl("SecondRegistrationPage.qml"))
                }
            }
        }

    }
}


