#include "prepenrollmentform.h"
#include "ui_prepenrollmentform.h"

extern Student* Extstudent;

PrepEnrollmentForm::PrepEnrollmentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrepEnrollmentForm)
{
    ui->setupUi(this);
}

PrepEnrollmentForm::~PrepEnrollmentForm()
{
    delete ui;
}
