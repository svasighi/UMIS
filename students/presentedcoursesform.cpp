#include "presentedcoursesform.h"
#include "ui_presentedcoursesform.h"

PresentedCoursesForm::PresentedCoursesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PresentedCoursesForm)
{
    ui->setupUi(this);
}

PresentedCoursesForm::~PresentedCoursesForm()
{
    delete ui;
}
