#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCryptographicHash>

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
    QString password = QString(QCryptographicHash::hash((ui->LE_Password->text().toUtf8()), QCryptographicHash::Md5).toHex());
    if (ui->RB_Student->isChecked())
    {
        if (//student->checkPassword(password.toStdString()))
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
    else if (ui->RB_Professor->isChecked())
    {
        Professor* professor = db.getProfessor(username);
        if(professor->checkPassword(password.toStdString()))
        {
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
