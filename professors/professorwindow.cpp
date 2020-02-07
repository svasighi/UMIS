#include "professorwindow.h"
#include "ui_professorwindow.h"
#include "professorpresentedcoursesform.h"
#include "professorslistform.h"

ProfessorWindow::ProfessorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfessorWindow)
{
    ui->setupUi(this);
    ui->TW_ProfMenu->setCurrentIndex(0);
}

ProfessorWindow::~ProfessorWindow()
{
    delete ui;
}
void ProfessorWindow::on_TB_Signout_clicked()
{
    emit want2close();
    this->close();
    ui->TW_ProfMenu->setCurrentIndex(0);
}

void ProfessorWindow::on_TW_Program_tabCloseRequested(int index)
{
    if(index)
    {
        ui->TW_Program->removeTab(index);
    }
}

void ProfessorWindow::on_PB_PresentedCourses_clicked()
{
    ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("دروس ارائه شده در ترم"));
}
void ProfessorWindow::on_PB_EnterScores_clicked(){
    ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("ثیت نمرات"));
}
void ProfessorWindow::on_PB_StudentsObjections_clicked(){
    ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("اعتراضات دانشجویان"));
}
void ProfessorWindow::on_PB_SrudentsList_clicked(){
    ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("مشاهده لیست دانشجویان"));
}
void ProfessorWindow::on_PB_Exceptions_clicked(){
    ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("فرم های استثنا"));
}
void ProfessorWindow::on_PB_PreEnrollmentStats_clicked(){
    ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("وضعیت ثبت نام مقدماتی"));
}
void ProfessorWindow::on_PB_AddCourse_clicked(){
    ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("افزودن درس"));
}
void ProfessorWindow::on_PB_AddPresentedCourse_clicked(){
    ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("افزودن درس ارائه شده"));
}
void ProfessorWindow::on_PB_ProfessorsAssesment_clicked(){
    ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("آمار ارزشیابی اساتید"));
}
void ProfessorWindow::on_PB_CalculateSalary_clicked(){
    ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("محاسبه حقوق"));
}
void ProfessorWindow::on_PB_ProfessorsList_clicked(){
    ui->TW_Program->addTab(new ProfessorsListForm(), QString("لیست اساتید"));

}
