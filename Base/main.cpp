#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.cpp"
#include <fstream>


int main(int argc, char *argv[])
{
    setlocale(LC_CTYPE, "Russian");
    QApplication a(argc, argv);
    MainWindow *w = MainWindow::GetInstance();
    w->show();

    return a.exec();
}
