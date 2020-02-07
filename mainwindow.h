#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "students/studentwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_PB_Signin_clicked();
    void on_PB_Exit_clicked();

private:
    Ui::MainWindow *ui;
    StudentWindow *wstudent;
};
#endif // MAINWINDOW_H