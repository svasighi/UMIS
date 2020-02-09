#include "presentedcoursesform.h"
#include "ui_presentedcoursesform.h"
#include <QMessageBox>

extern Student* Extstudent;
extern DbManager db;

PresentedCoursesForm::PresentedCoursesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PresentedCoursesForm)
{
    ui->setupUi(this);
}

PresentedCoursesForm::~PresentedCoursesForm()
{
	deleteItems();
    delete ui;
}

void PresentedCoursesForm::deleteItems()
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

void PresentedCoursesForm::on_PB_ShowResult_clicked()
{
    deleteItems();
    if(ui->LE_TermNo->text() == "" || ui->LE_DepartmentCode->text() == "")
    {
        QMessageBox::warning(this, "هشدار", "شماره ترم و شماره دانشکده نمی تواند خالی باشد");
        return;
    }

    bool okt, okd;
    int term = ui->LE_TermNo->text().toInt(&okt);
    int departmentcode = ui->LE_DepartmentCode->text().toInt(&okd);
    if (okt == false || okd == false)
    {
        QMessageBox::warning(this, "هشدار", "شماره ترم و شماره دانشکده باید عدد باشد");
        return;
    }
    std::vector<PresentedCourse*> courses = db.getPresentedCourseByDepartment(departmentcode, term);

    int r = 0;
    for(const auto& course : courses)
    {
        ui->TBW_Courses->insertRow(r);
        items.push_back(new QTableWidgetItem);
        items.back()->setText(QString::number(course->getGroup_no()) + "_" + QString::number(course->getCourseID()));
        ui->TBW_Courses->setItem(r, 0, items.back());

        items.push_back(new QTableWidgetItem(QString::fromStdString(course->getName())));
        ui->TBW_Courses->setItem(r, 1, items.back());

        items.push_back(new QTableWidgetItem(QString::number(course->getCredit())));
        ui->TBW_Courses->setItem(r, 2, items.back());

        items.push_back(new QTableWidgetItem(QString::number(course->getCapacity())));
        ui->TBW_Courses->setItem(r, 3, items.back());

        items.push_back(new QTableWidgetItem(QString::number(course->getEnrolledNumber())));
        ui->TBW_Courses->setItem(r, 4, items.back());

        items.push_back(new QTableWidgetItem(QString::number(course->getWaitingNumber())));
        ui->TBW_Courses->setItem(r, 5, items.back());

        items.push_back(new QTableWidgetItem);
        items.back()->setText(QString::fromStdString(course->getCourseProfessor()->getLastName() + " " + course->getCourseProfessor()->getFirstName()));
        ui->TBW_Courses->setItem(r, 6, items.back());

        items.push_back(new QTableWidgetItem);
        items.back()->setText(QString::fromStdString(course->getCourseLocation()));
        ui->TBW_Courses->setItem(r, 7, items.back());

        items.push_back(new QTableWidgetItem);
        items.back()->setText(QString::fromStdString(course->getFinalExamTime().getDate().getDate(0) + " " +
                                                     course->getFinalExamTime().getTime().getStart().getTime(2) + "-" +
                                                     course->getFinalExamTime().getTime().getFinish().getTime(2)));
        ui->TBW_Courses->setItem(r, 8, items.back());

        r++;
    }
}
