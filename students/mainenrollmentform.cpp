#include "mainenrollmentform.h"
#include "ui_mainenrollmentform.h"
#include <QMessageBox>

extern Student* Extstudent;
extern int curterm;
extern DbManager db;

MainEnrollmentForm::MainEnrollmentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainEnrollmentForm)
{
    ui->setupUi(this);
    comboitems << " " << "ثبت" << "انتظار" << "حذف";
    addPreviousCourses();
}

MainEnrollmentForm::~MainEnrollmentForm()
{
    deleteItems();
    delete ui;
}

void MainEnrollmentForm::deleteItems()
{
    for (int i = items.size() - 1; i >= 0; i--)
    {
        delete items[i];
        items[i] = nullptr;
    }
    items.clear();
    for (int i = comboboxes.size() - 1; i >= 0; i--)
    {
        delete comboboxes[i];
        comboboxes[i] = nullptr;
    }
    comboboxes.clear();
    for (int i = lineedits.size() - 1; i >= 0; i--)
    {
        delete lineedits[i];
        lineedits[i] = nullptr;
    }
    lineedits.clear();
    for (int i = ui->TBW_Courses->rowCount() - 1; i >= 0; i--)
    {
        ui->TBW_Courses->removeRow(i);
    }
}

void MainEnrollmentForm::addPreviousCourses()
{
    std::map<PresentedCourse*, MyCourse> precourses = Extstudent->getTerm(curterm).getCourses();
    int r = 0;
    for (const auto& c : precourses)
    {
        ui->TBW_Courses->insertRow(r);
        comboboxes.push_back(new QComboBox());
        comboboxes.back()->addItems(comboitems);
        ui->TBW_Courses->setCellWidget(r, 0, comboboxes.back());

        items.push_back(new QTableWidgetItem);
        switch(c.second.getStatus())
        {
        case MyCourse::enrolled :
            items.back()->setText("ثبت");
            break;
        case MyCourse::waiting :
            items.back()->setText("انتظار");
            break;
        }
        ui->TBW_Courses->setItem(r, 1, items.back());

        lineedits.push_back(new QLineEdit());
        lineedits.back()->setText(QString::number(c.first->getGroup_no()));
        ui->TBW_Courses->setCellWidget(r, 2, lineedits.back());
        items.push_back(new QTableWidgetItem(QString::number(c.first->getCourseCode())));
        ui->TBW_Courses->setItem(r, 3, items.back());
        items.push_back(new QTableWidgetItem(QString::number(c.first->getGroupCode())));
        ui->TBW_Courses->setItem(r, 4, items.back());
        items.push_back(new QTableWidgetItem(QString::number(c.first->getDepartmentCode())));
        ui->TBW_Courses->setItem(r, 5, items.back());
        items.push_back(new QTableWidgetItem(QString::fromStdString(c.first->getName())));
        ui->TBW_Courses->setItem(r, 6, items.back());
        items.push_back(new QTableWidgetItem(QString::number(c.first->getCredit())));
        ui->TBW_Courses->setItem(r, 7, items.back());

        r++;
    }
}

void MainEnrollmentForm::on_PB_AddNewRow_clicked()
{
    int r = ui->TBW_Courses->rowCount();
    ui->TBW_Courses->insertRow(r);
    comboboxes.push_back(new QComboBox());
    comboboxes.back()->addItems(comboitems);
    ui->TBW_Courses->setCellWidget(r, 0, comboboxes.back());
    lineedits.push_back(new QLineEdit());
    ui->TBW_Courses->setCellWidget(r, 2, lineedits.back());
    lineedits.push_back(new QLineEdit());
    ui->TBW_Courses->setCellWidget(r, 3, lineedits.back());
    lineedits.push_back(new QLineEdit());
    ui->TBW_Courses->setCellWidget(r, 4, lineedits.back());
    lineedits.push_back(new QLineEdit());
    ui->TBW_Courses->setCellWidget(r, 5, lineedits.back());
}

void MainEnrollmentForm::on_PB_Check_clicked()
{
    std::map<PresentedCourse*, char> newcourses;
    int nrow = ui->TBW_Courses->rowCount();
    bool ok;
    for (int r = 0; r < nrow; r++)
    {
        int estatus, departmentcode, groupcode, coursecode, group_no;
        estatus = dynamic_cast<QComboBox*>(ui->TBW_Courses->cellWidget(r, 0))->currentIndex();
        group_no= dynamic_cast<QLineEdit*>(ui->TBW_Courses->cellWidget(r, 2))->text().toInt(&ok);
        if (ok == false)
        {
            QMessageBox::critical(this, "خطا", "شماره گروه باید عدد باشد");
            return;
        }
        coursecode = ui->TBW_Courses->item(r, 3)->text().toInt(&ok);
        if (ok == false)
        {
            QMessageBox::critical(this, "خطا", "شماره درس باید عدد باشد");
            return;
        }
        groupcode = ui->TBW_Courses->item(r, 4)->text().toInt(&ok);
        if (ok == false)
        {
            QMessageBox::critical(this, "خطا", "شماره گروه آموزشی باید عدد باشد");
            return;
        }
        departmentcode = ui->TBW_Courses->item(r, 5)->text().toInt(&ok);
        if (ok == false)
        {
            QMessageBox::critical(this, "خطا", "شماره دانشکده باید عدد باشد");
            return;
        }
        int course_id = std::stoi(std::to_string(departmentcode) + std::to_string(groupcode) + std::to_string(coursecode));
        PresentedCourse* course = db.getPresentedCourseByCode(course_id, group_no, curterm);
        if (course == nullptr)
        {
            QMessageBox::critical(this, "خطا", "درسی با این شماره وجود ندارد");
            return;
        }
        newcourses.insert(std::make_pair(course, estatus));
    }
    std::vector<std::unique_ptr<EnrollmentError>> err = Extstudent->checkEnrollment(curterm, newcourses);
    if (err.empty())
    {
        QMessageBox::information(this, "موفقیت", "خطایی وجود ندارد");
    }
    else
    {
        for (const auto& e : err)
        {
            switch(e->getErrorCode())
            {
            case EnrollmentError::passed_before :
                QMessageBox::critical(this, "error", QString::fromStdString(dynamic_cast<PassedBefore*>(e.get())->what()));
                break;
            case EnrollmentError::taken_same_course :
                QMessageBox::critical(this, "error", QString::fromStdString(dynamic_cast<PassedBefore*>(e.get())->what()));
                break;
            case EnrollmentError::not_passed_prerequisite :
                QMessageBox::critical(this, "error", QString::fromStdString(dynamic_cast<PassedBefore*>(e.get())->what()));
                break;
            case EnrollmentError::not_taken_corequisite :
                QMessageBox::critical(this, "error", QString::fromStdString(dynamic_cast<PassedBefore*>(e.get())->what()));
                break;
            case EnrollmentError::course_time_overlap :
                QMessageBox::critical(this, "error", QString::fromStdString(dynamic_cast<PassedBefore*>(e.get())->what()));
                break;
            case EnrollmentError::exam_time_overlap :
                QMessageBox::critical(this, "error", QString::fromStdString(dynamic_cast<PassedBefore*>(e.get())->what()));
                break;
            case EnrollmentError::full_capacity :
                QMessageBox::critical(this, "error", QString::fromStdString(dynamic_cast<FullCapacity*>(e.get())->what()));
                break;
            default:
                QMessageBox::critical(this, "error", QString("Error #%0").arg(e->getErrorCode()));
            }
        }
    }
}

void MainEnrollmentForm::on_PB_Commit_clicked()
{
    std::map<PresentedCourse*, char> newcourses;
    int nrow = ui->TBW_Courses->rowCount();
    bool ok;
    for (int r = 0; r < nrow; r++)
    {
        int estatus, departmentcode, groupcode, coursecode, group_no;
        estatus = dynamic_cast<QComboBox*>(ui->TBW_Courses->cellWidget(r, 0))->currentIndex();
        group_no= dynamic_cast<QLineEdit*>(ui->TBW_Courses->cellWidget(r, 2))->text().toInt(&ok);
        if (ok == false)
        {
            QMessageBox::critical(this, "خطا", "شماره گروه باید عدد باشد");
            return;
        }
        coursecode = ui->TBW_Courses->item(r, 3)->text().toInt(&ok);
        if (ok == false)
        {
            QMessageBox::critical(this, "خطا", "شماره درس باید عدد باشد");
            return;
        }
        groupcode = ui->TBW_Courses->item(r, 4)->text().toInt(&ok);
        if (ok == false)
        {
            QMessageBox::critical(this, "خطا", "شماره گروه آموزشی باید عدد باشد");
            return;
        }
        departmentcode = ui->TBW_Courses->item(r, 5)->text().toInt(&ok);
        if (ok == false)
        {
            QMessageBox::critical(this, "خطا", "شماره دانشکده باید عدد باشد");
            return;
        }
        int course_id = std::stoi(std::to_string(departmentcode) + std::to_string(groupcode) + std::to_string(coursecode));
        PresentedCourse* course = db.getPresentedCourseByCode(course_id, group_no, curterm);
        if (course == nullptr)
        {
            QMessageBox::critical(this, "خطا", "درسی با این شماره وجود ندارد");
            return;
        }
        newcourses.insert(std::make_pair(course, estatus));
    }
    std::vector<std::unique_ptr<EnrollmentError>> err = Extstudent->commitEnrollment(curterm, newcourses);
    if (err.empty())
    {
        QMessageBox::information(this, "موفقیت", "خطایی وجود ندارد");
    }
    else
    {
        for (const auto& e : err)
        {
            switch(e->getErrorCode())
            {
            case EnrollmentError::passed_before :
                QMessageBox::critical(this, "error", QString::fromStdString(dynamic_cast<PassedBefore*>(e.get())->what()));
                break;
            case EnrollmentError::taken_same_course :
                QMessageBox::critical(this, "error", QString::fromStdString(dynamic_cast<PassedBefore*>(e.get())->what()));
                break;
            case EnrollmentError::not_passed_prerequisite :
                QMessageBox::critical(this, "error", QString::fromStdString(dynamic_cast<PassedBefore*>(e.get())->what()));
                break;
            case EnrollmentError::not_taken_corequisite :
                QMessageBox::critical(this, "error", QString::fromStdString(dynamic_cast<PassedBefore*>(e.get())->what()));
                break;
            case EnrollmentError::course_time_overlap :
                QMessageBox::critical(this, "error", QString::fromStdString(dynamic_cast<PassedBefore*>(e.get())->what()));
                break;
            case EnrollmentError::exam_time_overlap :
                QMessageBox::critical(this, "error", QString::fromStdString(dynamic_cast<PassedBefore*>(e.get())->what()));
                break;
            case EnrollmentError::full_capacity :
                QMessageBox::critical(this, "error", QString::fromStdString(dynamic_cast<FullCapacity*>(e.get())->what()));
                break;
            default:
                QMessageBox::critical(this, "error", QString("Error #%0").arg(e->getErrorCode()));
            }
        }
    }
}
