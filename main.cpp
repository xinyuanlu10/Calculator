#include "tabwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tabwidget w;
    //tabwidget *wp = &w;
    w.show();
//    w.setMaximumSize(10000, 6667);
    //QScrollArea *scroll = new QScrollArea;
    //scroll->setWidget(wp);
    //scroll->setGeometry(0, 0, 320, 240);
    //scroll->show();
    return a.exec();
}
