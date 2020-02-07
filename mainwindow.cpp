#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "professors/professorwindow.h"


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
    connect(&wprofessor, &ProfessorWindow::want2close, this, &MainWindow::show);
    wprofessor.setGeometry(this->geometry());
    if (this->isMaximized())
    {
        wprofessor.showMaximized();
    }
    wprofessor.show();
    this->hide();
}

void MainWindow::on_PB_Exit_clicked()
{
    QApplication::quit();
}
