#include "professorslistform.h"
#include "ui_professorslistform.h"

extern Professor* Extprofessor ;

ProfessorsListForm::ProfessorsListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfessorsListForm)
{
    ui->setupUi(this);
}

ProfessorsListForm::~ProfessorsListForm()
{
    delete ui;
}

void ProfessorsListForm::on_PB_ReadData_clicked()
{

}

void ProfessorsListForm::on_PB_AddProfessor_clicked()
{

}
