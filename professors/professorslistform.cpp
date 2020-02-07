#include "professorslistform.h"
#include "ui_professorslistform.h"
#include "../mainwindow.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

ProfessorsListForm::ProfessorsListForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfessorsListForm)
{
    ui->setupUi(this);
}

ProfessorsListForm::~ProfessorsListForm()
{
    delete ui;
}
void ProfessorsListForm::on_readData_clicked()
{

}

