#include "weekscheduleform.h"
#include "ui_weekscheduleform.h"

WeekScheduleForm::WeekScheduleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeekScheduleForm)
{
    ui->setupUi(this);
}

WeekScheduleForm::~WeekScheduleForm()
{
    delete ui;
}
