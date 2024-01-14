#include "mainwindow.h"

#include <QApplication>
#include <QVBoxLayout>
#include "materialswitch.h"

void makeTransparent(QWidget* widget){
    widget->setAttribute(Qt::WA_TranslucentBackground);
    widget->setWindowFlags(Qt::FramelessWindowHint);
    widget->setStyleSheet("background:transparent");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;

    QVBoxLayout layout(&window);

    MaterialSwitch switchWidget;
    layout.addWidget(&switchWidget);

    makeTransparent(&window);

    window.show();
    return app.exec();
}
