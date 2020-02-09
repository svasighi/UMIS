#include "../mainwindow.h"
#include "professorwindow.h"
#include "ui_professorwindow.h"
//#include "professorpresentedcoursesform.h"
#include "professorslistform.h"

extern Professor* Extprofessor ;

ProfessorWindow::ProfessorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfessorWindow)
{
    ui->setupUi(this);
    ui->TW_ProfMenu->setCurrentIndex(0);
    ui->L_User->setText(QString(Extprofessor->getUserName()));
    if(typeid (Extprofessor) != typeid(DepartmentHead))
        ui->TW_ProfMenu->setTabEnabled(4, false);
    if(typeid (Extprofessor) != typeid(GroupManager))
        ui->TW_ProfMenu->setTabEnabled(3, false);
    if(typeid (Extprofessor) != typeid(Faculty))
        ui->TW_ProfMenu->setTabEnabled(2, false);
}

ProfessorWindow::~ProfessorWindow()
{
    delete ui;
}

void ProfessorWindow::on_TB_Signout_clicked()
{
    delete Extprofessor;
    Extprofessor = nullptr;
    MainWindow *wmain = new MainWindow();
    wmain->setGeometry(this->geometry());
    if (this->isMaximized())
    {
        wmain->showMaximized();
    }
    if (this->isFullScreen())
    {
        wmain->showFullScreen();
    }
    wmain->show();
    this->close();
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
    //ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("دروس ارائه شده در ترم"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void ProfessorWindow::on_PB_EnterScores_clicked()
{
    //ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("ثیت نمرات"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void ProfessorWindow::on_PB_StudentsObjections_clicked()
{
    //ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("اعتراضات دانشجویان"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void ProfessorWindow::on_PB_SrudentsList_clicked()
{
    //ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("مشاهده لیست دانشجویان"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void ProfessorWindow::on_PB_Exceptions_clicked()
{
    //ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("فرم های استثنا"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void ProfessorWindow::on_PB_PreEnrollmentStats_clicked()
{
    //ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("وضعیت ثبت نام مقدماتی"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void ProfessorWindow::on_PB_AddCourse_clicked()
{
    //ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("افزودن درس"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void ProfessorWindow::on_PB_AddPresentedCourse_clicked()
{
    //ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("افزودن درس ارائه شده"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void ProfessorWindow::on_PB_ProfessorsAssesment_clicked()
{
    //ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("آمار ارزشیابی اساتید"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void ProfessorWindow::on_PB_CalculateSalary_clicked()
{
    //ui->TW_Program->addTab(new ProfessorPresentedCoursesForm(), QString("محاسبه حقوق"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void ProfessorWindow::on_PB_ProfessorsList_clicked()
{
    ui->TW_Program->addTab(new ProfessorsListForm(), QString("لیست اساتید"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}
