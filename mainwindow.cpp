#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCryptographicHash>

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
        if(ui->RB_Student->isChecked()){
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
        else if (ui->RB_Professor->isChecked()) {
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
    else if (ui->RB_Staff->isChecked())
    {

    }
    else
    {
        QMessageBox::warning(this, "خطا", "یکی از گزینه ها را انتخاب کنید");
    }

}

void MainWindow::on_PB_Exit_clicked()
{
    QApplication::quit();
}
