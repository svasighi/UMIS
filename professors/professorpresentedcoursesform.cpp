#include "professorpresentedcoursesform.h"
#include "ui_professorpresentedcoursesform.h"

ProfessorPresentedCoursesForm::ProfessorPresentedCoursesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfessorPresentedCoursesForm)
{
    ui->setupUi(this);
}

ProfessorPresentedCoursesForm::~ProfessorPresentedCoursesForm()
{
    delete ui;
}
