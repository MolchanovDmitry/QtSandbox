QT += quick concurrent

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        data/weatherdataparser.cpp \
        data/weatherrepository.cpp \
        domain/getweatherusecase.cpp \
        domain/weatherdata.cpp \
        presentation/weathermodel.cpp \
        presentation/updatebuttonclickdelegate.cpp \

RESOURCES += presentation/ui/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    data/weatherdataparser.h \
    data/weatherrepository.h \
    domain/getweatherusecase.h \
    domain/weatherdata.h \
    presentation/weathermodel.h \
    presentation/updatebuttonclickdelegate.h \
