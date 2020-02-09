#include "mainwindow.h"
#include <QApplication>

Professor* Extprofessor = nullptr;
Student* Extstudent = nullptr;
int curterm = 3982;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
