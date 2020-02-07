#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PB_Signin_clicked()
{
    //ui->LE_Username
    //ui->LE_Password
    {
        wstudent = new StudentWindow();
        wstudent->setGeometry(this->geometry());
        if (this->isMaximized())
        {
            wstudent->showMaximized();
        }
        if (this->isFullScreen())
        {
            wstudent->showFullScreen();
        }
        wstudent->show();
    }
    //
    this->hide();

}

void MainWindow::on_PB_Exit_clicked()
{
    QApplication::quit();
}
