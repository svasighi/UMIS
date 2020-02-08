#include "../mainwindow.h"
#include "studentwindow.h"
#include "ui_studentwindow.h"
#include "presentedcoursesform.h"
#include "weekscheduleform.h"
#include "examscheduleform.h"
#include "../src/student.h"
//#include "tuitionform.h"
#include "assessmentform.h"
#include "fullinformationform.h"

extern Student* Extstudent ;

StudentWindow::StudentWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
    ui->L_User->setNum(Extstudent->getUserName());

    ui->TW_UserMenu->setCurrentIndex(0);
}

StudentWindow::~StudentWindow()
{
    delete ui;
}

void StudentWindow::on_TB_Signout_clicked()
{

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

void StudentWindow::on_TW_Program_tabCloseRequested(int index)
{

    if(index)
    {
        ui->TW_Program->removeTab(index);
    }
}


void StudentWindow::on_PB_PresentedCourses_clicked()
{
    ui->TW_Program->addTab(new PresentedCoursesForm(), QString("دروس ارائه شده در ترم"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void StudentWindow::on_PB_WeekSchedule_clicked()
{
    ui->TW_Program->addTab(new WeekScheduleForm(), QString("برنامه هفتگی دانشجو"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void StudentWindow::on_PB_ExamSchedule_clicked()
{
    ui->TW_Program->addTab(new ExamScheduleForm(), QString("برنامه امتحان پایان ترم دانشجو"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}
/*
void StudentWindow::on_PB_Tuition_clicked()
{
    ui->TW_Program->addTab(new TuitionForm(), QString("مشاهده وضعیت شهریه"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}
*/
void StudentWindow::on_PB_Assessment_clicked()
{
    ui->TW_Program->addTab(new AssessmentForm(), QString("ارزشیابی"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void StudentWindow::on_PB_FullInformatin_clicked()
{
    ui->TW_Program->addTab(new FullInformationForm(), QString("اطلاعات جامع دانشجو"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}


