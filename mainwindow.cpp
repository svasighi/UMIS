#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "professors/professorwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


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
void MainWindow::DatabaseConnect()
{
    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

        db.setDatabaseName("University");

        if(!db.open())
            qWarning() << "MainWindow::DatabaseConnect - ERROR: " << db.lastError().text();
    }
    else
        qWarning() << "MainWindow::DatabaseConnect - ERROR: no driver " << DRIVER << " available";
}
void MainWindow::DatabaseInit()
{
    QSqlQuery query("CREATE TABLE users (id INTEGER PRIMARY KEY, username INTEGER, passwrod TEXT, firstname TEXT, lastname TEXT, degree TEXT, departmentcode INTEGER,  groupcode INTEGER, is_supervisor INTEGER,type TEXT,)");

    if(!query.isActive())
        qWarning() << "MainWindow::DatabaseInit - ERROR: " << query.lastError().text();

}
void MainWindow::DatabasePopulate()
{
    QSqlQuery query;

    if(!query.exec("INSERT INTO users(username, password, firstname, lastname, degree, departmentcode, departmentcode, groupcode, is_supervisor ,type) VALUES('head' , 'd0b63845e6aa07489a797146420b8b15' , 'کاربر' , 'تست' , 'نا معلوم' , '0' ,'0' , 0 , 'departmenthead')"))
        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
}
