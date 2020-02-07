#include "examscheduleform.h"
#include "ui_examscheduleform.h"

ExamScheduleForm::ExamScheduleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamScheduleForm)
{
    ui->setupUi(this);
}

ExamScheduleForm::~ExamScheduleForm()
{
    delete ui;
}
