#include "mainenrollmentform.h"
#include "ui_mainenrollmentform.h"

extern Student* Extstudent;

MainEnrollmentForm::MainEnrollmentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainEnrollmentForm)
{
    ui->setupUi(this);
}

MainEnrollmentForm::~MainEnrollmentForm()
{
    delete ui;
}
