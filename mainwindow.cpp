#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "professors/professorwindow.h"
#include "dbmanager.h"
#include <string>
#include <QString>
#include <qcryptographichash>
#include <QMessageBox>

DbManager db = DbManager();
extern Professor* Extprofessor = nullptr;
extern Student* Extstudent = nullptr;
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
    bool haserror = false;

    if(ui->LE_Password->text().length() < 6){
        haserror = true;
        ui->LE_Password->setStyleSheet("QLineEdit { background: rgb(255,103,125); selection-background-color: rgb(233, 99, 0); }");;
    }else{
        ui->LE_Password->setStyleSheet("QLineEdit { background: rgb(255,255,255); selection-background-color: rgb(233, 99, 0); }");;
    }
    if (ui->LE_Username->text().length() == 0) {
        haserror = true;
        ui->LE_Username->setStyleSheet("QLineEdit { background: rgb(255,103,125); selection-background-color: rgb(233, 99, 0); }");;
    }else{
        ui->LE_Password->setStyleSheet("QLineEdit { background: rgb(255,255,255); selection-background-color: rgb(233, 99, 0); }");;
    }

    if(!haserror){
        QString password = QString(QCryptographicHash::hash((ui->LE_Password->text().toUtf8()) , QCryptographicHash::Md5).toHex());
        int username = ui->LE_Username->text().toInt();
        if(choice == 0){
            Student* student =  db.getStudent(username);
            if(student->checkPassword(password.toStdString()))
            {
                Extstudent = student;
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
            Extprofessor = professor;
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
