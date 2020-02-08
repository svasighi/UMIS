#include "tuitionform.h"
#include "ui_tuitionform.h"

extern Student* Extstudent;

TuitionForm::TuitionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TuitionForm)
{
    ui->setupUi(this);
}

TuitionForm::~TuitionForm()
{
    delete ui;
}
