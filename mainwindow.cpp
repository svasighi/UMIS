#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "professors/professorwindow.h"
#include "dbmanager.h"
#include <string>
#include <QString>
#include <qcryptographichash>
#include <QMessageBox>

extern int choice = 0;
DbManager db = DbManager();

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
    int username = ui->LE_Username->text().toInt();
    QString password = QString(QCryptographicHash::hash((ui->LE_Password->text().toUtf8()) , QCryptographicHash::Md5).toHex());
    if(choice == 0){

        if(//studet->checkPassword(password.toStdString()))
                true)
        {
            wstudent = new StudentWindow();
            wstudent->setGeometry(this->geometry());
            if (this->isMaximized())
            {
                wstudent->showMaximized();
            }
            wstudent->show();
            this->hide();
        }
    }
    else if (choice == 1) {
        Professor* professor =  db.getProfessor(username);
        if(professor->checkPassword(password.toStdString())){
            wprofessor = new ProfessorWindow();
            wprofessor->setGeometry(this->geometry());
            if (this->isMaximized())
            {
                wprofessor->showMaximized();
            }
            wprofessor->show();
            this->hide();
        }

    }

}

void MainWindow::on_PB_Exit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_radioButton_3_clicked()
{
    choice = 0;
}

void MainWindow::on_radioButton_2_clicked()
{
    choice = 1;

}

void MainWindow::on_radioButton_clicked()
{
    choice = 2;
}
