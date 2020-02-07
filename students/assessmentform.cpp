#include "assessmentform.h"
#include "ui_assessmentform.h"

AssessmentForm::AssessmentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AssessmentForm)
{
    ui->setupUi(this);
}

AssessmentForm::~AssessmentForm()
{
    delete ui;
}
