#include "weekscheduleform.h"
#include "ui_weekscheduleform.h"
#include <QMessageBox>

extern Student* Extstudent;

WeekScheduleForm::WeekScheduleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeekScheduleForm)
{
    ui->setupUi(this);
}

WeekScheduleForm::~WeekScheduleForm()
{
	deleteItems();
    delete ui;
}

void WeekScheduleForm::deleteItems()
{
    for (int i = items.size() - 1; i >= 0; i--)
    {
        delete items[i];
    }
    items.clear();
    for (int i = ui->TBW_Courses->rowCount() - 1; i >= 0; i--)
    {
        ui->TBW_Courses->removeRow(i);
    }
}

void WeekScheduleForm::on_PB_ShowResult_clicked()
{
    //........................................................................................................test
    //........................................................................................................
    Course* c0 = new Course(17, 34, 888, 3, "DSP", 3);
    Course* c1 = new Course(17, 34, 125, 3, "Algorithm", 3);
    Course* c2 = new Course(17, 34, 300, 3, "Signal", 3);
    Course* c3 = new Course(17, 34, 241, 2, "AP", 3);
    Course* c4 = new Course(17, 34, 380, 1, "C", 3);
    c0->addCorequisite(c1);
    c1->addCorequisite(c0);

    Faculty* p0 = new Faculty(12398, "123", "Ali", "Rohan", 17, 34, 1, true);
    Faculty* p1 = new Faculty(12345, "pass", "Reza", "Khandan", 17, 34, 1, true);
    Faculty* p2 = new Faculty(12724, "iu", "Amir", "Khar", 17, 34, 1, true);
    PresentedCourse* pc0 = new PresentedCourse(c0, 3941, 0, p1, 20);
    PresentedCourse* pc1 = new PresentedCourse(c1, 3941, 0, p2, 10);
    PresentedCourse* pc2 = new PresentedCourse(c4, 3941, 0, p0, 10);
    PresentedCourse* pc3 = new PresentedCourse(c2, 3942, 0, p1, 20);
    PresentedCourse* pc4 = new PresentedCourse(c3, 3951, 0, p0, 20);
    pc0->setCourseTime(CourseTime({ 1,2 }, Time(8), Time(9, 30)));
    pc1->setCourseTime(CourseTime({ 2,4 }, Time(9, 30), Time(11)));
    pc2->setCourseTime(CourseTime({ 3 }, Time(9, 30), Time(11)));
    pc3->setCourseTime(CourseTime({ 2,4 }, Time(9, 30), Time(11)));
    pc4->setCourseTime(CourseTime({ 2,4 }, Time(9, 30), Time(11)));
    pc0->setCourseLocation("class 3");
    pc1->setCourseLocation("class 4");
    pc2->setCourseLocation("class 5");
    pc3->setCourseLocation("class 7");
    pc4->setCourseLocation("class 8");

    Student *s0 = new Student(9430703,"1234","Saeed","Mohseni",17,Student::day,"electric",34);
    s0->setSupervisor(p1);
    s0->addTerm(3941);
    auto e = s0->commitEnrollment(3941, { {pc0,ENROLL}, {pc1,ENROLL}, {pc2,ENROLL} });
    s0->addTerm(3942);
    auto e2 = s0->commitEnrollment(3942, { {pc3,ENROLL} });
    s0->addTerm(3951);
    auto e3 = s0->commitEnrollment(3951, { {pc4,ENROLL} });
    s0->setGrade(17.5);
    Extstudent = s0;
    //........................................................................................................
    //........................................................................................................test
    int term = ui->LE_TermNo->text().toInt();
    deleteItems();
    if (Extstudent->getTerms().count(term) == 0)
    {
        QMessageBox::warning(this, "خطا", "ترم وجود ندارد");
    }
    else
    {
        std::vector<PresentedCourse*> courses = Extstudent->getTermCoursesWithoutResult(term);
        int r = 0;
        for(const auto& course : courses)
        {
            ui->TBW_Courses->insertRow(r);
            items.push_back(new QTableWidgetItem);
            items.back()->setText(QString::number(course->getGroup_no()) + "_" + QString::number(course->getCourseID()));
            ui->TBW_Courses->setItem(r, 0, items.back());

            items.push_back(new QTableWidgetItem(QString::fromStdString(course->getName())));
            ui->TBW_Courses->setItem(r, 1, items.back());

            items.push_back(new QTableWidgetItem);
            items.back()->setText(QString::fromStdString(course->getCourseProfessor()->getLastName() + " " + course->getCourseProfessor()->getFirstName()));
            ui->TBW_Courses->setItem(r, 2, items.back());

            items.push_back(new QTableWidgetItem);
            items.back()->setText(QString::fromStdString(course->getCourseLocation()));
            ui->TBW_Courses->setItem(r, 3, items.back());

            std::multimap<char, TimePeriod> times = course->getCourseTime().getTimes();
            for(const auto& t : times)
            {
                items.push_back(new QTableWidgetItem);
                items.back()->setText(QString::fromStdString(t.second.getStart().getTime(2) + "-" + t.second.getFinish().getTime(2)));
                switch(t.first)
                {
                case 1 :
                    ui->TBW_Courses->setItem(r, 4, items.back());
                    break;
                case 2 :
                    ui->TBW_Courses->setItem(r, 5, items.back());
                    break;
                case 3 :
                    ui->TBW_Courses->setItem(r, 6, items.back());
                    break;
                case 4 :
                    ui->TBW_Courses->setItem(r, 7, items.back());
                    break;
                case 5 :
                    ui->TBW_Courses->setItem(r, 8, items.back());
                    break;
                }
            }

            r++;
        }
    }
}
