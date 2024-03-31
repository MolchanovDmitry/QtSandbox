TARGET = ru.auroraos.Notifier

CONFIG += \
    auroraapp

PKGCONFIG += \

SOURCES += \
    src/main.cpp \
    src/notificationmanager.cpp

HEADERS += \
    src/notificationmanager.h

DISTFILES += \
    rpm/ru.auroraos.Notifier.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

QT += dbus

TRANSLATIONS += \
    translations/ru.auroraos.Notifier.ts \
    translations/ru.auroraos.Notifier-ru.ts \
