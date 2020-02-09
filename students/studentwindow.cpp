#include "../mainwindow.h"
#include "studentwindow.h"
#include "ui_studentwindow.h"
#include "presentedcoursesform.h"
#include "weekscheduleform.h"
#include "examscheduleform.h"
#include "tuitionform.h"
#include "assessmentform.h"
#include "fullinformationform.h"
#include "enrolltimeform.h"
#include "mainenrollmentform.h"
#include "prepenrollmentform.h"
#include "changepasswordform.h"

extern Student* Extstudent;

StudentWindow::StudentWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
    ui->TW_UserMenu->setCurrentIndex(0);
    ui->L_User->setText(QString::fromStdString(Extstudent->getFirstName() + " " + Extstudent->getLastName()));
}

StudentWindow::~StudentWindow()
{
    deleteTabs();
    delete ui;
}

void StudentWindow::on_TB_Signout_clicked()
{
    delete Extstudent;
    Extstudent = nullptr;
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

void StudentWindow::deleteTabs()
{
    for (int i = tabs.size() - 1; i >= 0; i--)
    {
        delete tabs[i];
        tabs[i] = nullptr;
    }
    tabs.clear();
    ui->TW_Program->clear();
}

void StudentWindow::on_TW_Program_tabCloseRequested(int index)
{
    if (index)
    {
        ui->TW_Program->removeTab(index);
    }
}

void StudentWindow::on_PB_PresentedCourses_clicked()
{
    tabs.push_back(new PresentedCoursesForm());
    ui->TW_Program->addTab(tabs.back(), QString("دروس ارائه شده در ترم"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void StudentWindow::on_PB_WeekSchedule_clicked()
{
    tabs.push_back(new WeekScheduleForm());
    ui->TW_Program->addTab(tabs.back(), QString("برنامه هفتگی دانشجو"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void StudentWindow::on_PB_ExamSchedule_clicked()
{
    tabs.push_back(new ExamScheduleForm());
    ui->TW_Program->addTab(tabs.back(), QString("برنامه امتحان پایان ترم دانشجو"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void StudentWindow::on_PB_Tuition_clicked()
{
    tabs.push_back(new TuitionForm());
    ui->TW_Program->addTab(new TuitionForm(), QString("مشاهده وضعیت شهریه"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void StudentWindow::on_PB_Assessment_clicked()
{
    tabs.push_back(new AssessmentForm());
    ui->TW_Program->addTab(tabs.back(), QString("ارزشیابی"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void StudentWindow::on_PB_FullInformatin_clicked()
{
    tabs.push_back(new FullInformationForm());
    ui->TW_Program->addTab(tabs.back(), QString("اطلاعات جامع دانشجو"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void StudentWindow::on_PB_EnrollTime_clicked()
{
    tabs.push_back(new EnrollTimeForm());
    ui->TW_Program->addTab(tabs.back(), QString("مشاهده ساعت ثبت نام"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void StudentWindow::on_PB_PrepEnroll_clicked()
{
    tabs.push_back(new PrepEnrollmentForm());
    ui->TW_Program->addTab(tabs.back(), QString("ثبت نام مقدماتی"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void StudentWindow::on_PB_MainEnroll_clicked()
{
    tabs.push_back(new MainEnrollmentForm());
    ui->TW_Program->addTab(tabs.back(), QString("ثبت نام اصلی"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}

void StudentWindow::on_PB_ChangePassword_clicked()
{
    tabs.push_back(new ChangePasswordForm());
    ui->TW_Program->addTab(tabs.back(), QString("تغییر گذرواژه"));
    ui->TW_Program->setCurrentIndex(ui->TW_Program->count() - 1);
}
