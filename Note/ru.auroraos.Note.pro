TARGET = ru.auroraos.Note

CONFIG += \
    auroraapp

PKGCONFIG += \

SOURCES += \
    src/main.cpp \

HEADERS += \

DISTFILES += \
    qml/pages/CreateNoteDialog.qml \
    rpm/ru.auroraos.Note.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.auroraos.Note.ts \
    translations/ru.auroraos.Note-ru.ts \
