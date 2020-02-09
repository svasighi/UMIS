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
        items[i] = nullptr;
    }
    items.clear();
    for (int i = ui->TBW_Courses->rowCount() - 1; i >= 0; i--)
    {
        ui->TBW_Courses->removeRow(i);
    }
}

void WeekScheduleForm::on_PB_ShowResult_clicked()
{
    deleteItems();
    bool ok;
    int term = ui->LE_TermNo->text().toInt(&ok);
    if (ui->LE_TermNo->text() == "")
    {
        QMessageBox::warning(this, "هشدار", "شماره ترم نمی توند خالی باشد");
        return;
    }
    if (ok == 0)
    {
        QMessageBox::warning(this, "هشدار", "شماره ترم باید عدد باشد");
        return;
    }
    if (Extstudent->getTerms().count(term) == 0)
    {
        QMessageBox::warning(this, "هشدار", "ترم وجود ندارد");
        return;
    }

    std::vector<PresentedCourse*> courses = Extstudent->getTerm(term).getCoursesWithoutResult();
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
