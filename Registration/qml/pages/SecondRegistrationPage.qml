import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    PageHeader {
        title: qsTr("Заполните информацию о себе")
        description: qsTr("Обязательные поля помечены звездочкой")
    }
    Column {
        anchors.centerIn: parent
        width: parent.width

        TextField {
            id: surnameText
            width: parent.width
            placeholderText: qsTr("Фамилия")
            inputMethodHints: Qt.ImhNoAutoUppercase
            validator: RegExpValidator {
                regExp: /(^[A-ZА-ЯЁ]{1}[a-zа-яё]+$)|(^$)/
            }
        }

        TextField {
            id: nameText
            width: parent.width
            placeholderText: qsTr("Имя")
            inputMethodHints: Qt.ImhNoAutoUppercase
            validator: RegExpValidator {
                regExp: /(^[A-ZА-ЯЁ]{1}[a-zа-яё]+$)|(^$)/
            }
        }

        TextField {
            id: patronymicText
            width: parent.width
            placeholderText: qsTr("Отчество")
            inputMethodHints: Qt.ImhNoAutoUppercase
            validator: RegExpValidator {
                regExp: /(^[A-ZА-ЯЁ]{1}[a-zа-яё]+$)|(^$)/
            }
        }

        TextField {
            property bool shouldHighlightError : false
            id: emailText
            width: parent.width
            placeholderText: qsTr("* Адрес электронной почты")
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            validator: RegExpValidator {
                regExp: /^(.+)@(\S+)\.(\S+)$/
            }
            onTextChanged: {
                placeholderText = "Адрес электронной почты"
                label = ""
                shouldHighlightError = false
            }
        }

        TextField {
            id: interestsText
            width: parent.width
            placeholderText: qsTr("Интересы")
            inputMethodHints: Qt.ImhFormattedNumbersOnly
        }

        TextSwitch {
            id: agreementSwitch
            width: page.width
            text: "Cогласие на обработку персональных данных"
            onCheckedChanged: {
                _label.color = Theme.lightPrimaryColor
                if(!checked){
                    description = "Необходимо дать согласие"
                } else{
                    description = ""
                }
            }
        }

        TextSwitch {
            width: page.width
            text: qsTr("Согласие на рассылку спама")
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Зарегистрироваться")
            onClicked: {
                var isAllFieldsCoorect = true
                if(emailText._isEmpty){
                    isAllFieldsCoorect = false
                    emailText.shouldHighlightError = true
                    emailText.placeholderText = "Введите email"
                    emailText.placeholderColor = Theme.errorColor
                } else if(emailText.errorHighlight){
                    isAllFieldsCoorect = false
                    emailText.shouldHighlightError = true
                    emailText.label = "Адрес некорректного формата"
                }
                if(!agreementSwitch.checked){
                    isAllFieldsCoorect = false
                    agreementSwitch._label.color = Theme.errorColor
                    agreementSwitch.description = "Необходимо дать согласие"
                }
                if(surnameText.errorHighlight  || nameText.errorHighlight || patronymicText.errorHighlight || interestsText.errorHighlight){
                    isAllFieldsCoorect = false
                }
                if(isAllFieldsCoorect){
                    pageStack.push(Qt.resolvedUrl("SuccessPage.qml"))
                }
            }
        }
    }
}

