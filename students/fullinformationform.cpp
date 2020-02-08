#include "fullinformationform.h"
#include "ui_fullinformationform.h"
#include <QMessageBox>

extern Student* Extstudent;

FullInformationForm::FullInformationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FullInformationForm)
{
    ui->setupUi(this);
    FullInformationForm::on_PB_Refresh_clicked();
}

FullInformationForm::~FullInformationForm()
{
	deleteItems();
    delete ui;
}

void FullInformationForm::deleteItems()
{
    for (int i = items.size() - 1; i >= 0; i--)
    {
        delete items[i];
    }
    items.clear();
    for (int i = ui->TBW_Terms->rowCount() - 1; i >= 0; i--)
    {
        ui->TBW_Terms->removeRow(i);
    }
}

void FullInformationForm::on_PB_Refresh_clicked()
{
    //........................................................................................................test
    //........................................................................................................
    Course* c0 = new Course(17, 34, 888, 3, "DSP", 3);
    Course* c1 = new Course(17, 34, 125, 3, "Algorithm", 2);
    Course* c2 = new Course(17, 34, 300, 3, "Signal", 4);
    Course* c3 = new Course(17, 34, 241, 2, "AP", 1);
    Course* c4 = new Course(17, 34, 380, 1, "C", 0);
    c0->addCorequisite(c1);
    c1->addCorequisite(c0);

    Faculty* p0 = new Faculty(12398, "123", "Ali", "Rohan", 17, 34, 1, true);
    Faculty* p1 = new Faculty(12345, "pass", "Reza", "Khandan", 17, 34, 1, true);
    Faculty* p2 = new Faculty(12724, "iu", "Amir", "Kar", 17, 34, 1, true);
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
    pc0->setFinalExamTime(ExamTime(Date(1394, 10, 1), Time(8), Time(11)));
    pc1->setFinalExamTime(ExamTime(Date(1394, 10, 1), Time(11), Time(14)));
    pc2->setFinalExamTime(ExamTime(Date(1394, 10, 2), Time(13,30), Time(16,30)));
    pc3->setFinalExamTime(ExamTime(Date(1395, 4, 1), Time(8), Time(12)));
    pc4->setFinalExamTime(ExamTime(Date(1395, 10, 1), Time(8), Time(12)));

    Student* s0 = new Student(9430703,"1234","Saeed","Mohseni",17,Student::day,"electric",34);
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

    mode = 0;
    deleteItems();
    ui->TBW_Terms->setColumnCount(8);
    QStringList header;
    header << "ترم" << "اخذ شده" << "گذرانده" << "اعلام نشده" << "حذف شده" << "رد شده" << "وضعیت" << "شهریه";
    ui->TBW_Terms->setHorizontalHeaderLabels(header);

    ui->L_UserName->setText(QString::number(Extstudent->getUserName()));
    ui->L_Name->setText(QString::fromStdString(Extstudent->getLastName() + " " + Extstudent->getFirstName()));
    ui->L_Grade->setText(Extstudent->getGrade() >= 0 ? QString::number(Extstudent->getGrade()) : "-");
    ui->L_PassedCredits->setText(QString::number(Extstudent->numberofAllCreditsWithStatus(MyCourse::passed)));
    ui->L_Department->setText(QString::number(Extstudent->getDepartmentCode()));
    ui->L_Field->setText(QString::fromStdString(Extstudent->getField()));
    switch(Extstudent->getType())
    {
    case Student::day :
        ui->L_Type->setText("روزانه");
        break;
    case Student::guest :
        ui->L_Type->setText("مهمان");
        break;
    case Student::transitional :
        ui->L_Type->setText("انتقالی");
        break;
    case Student::night :
        ui->L_Type->setText("شبانه");
        break;
    }
    ui->L_Supervisor->setText(QString::fromStdString(Extstudent->getSupervisor()->getLastName() + " " + Extstudent->getSupervisor()->getFirstName()));
    std::map<int,MyTerm> terms = Extstudent->getTerms();
    int r = 0;
    for(const auto& term : terms)
    {
        ui->TBW_Terms->insertRow(r);
        items.push_back(new QTableWidgetItem(QString::number(term.first)));
        ui->TBW_Terms->setItem(r, 0, items.back());

        int nall = term.second.numberofCredits();
        int npassed = term.second.numberofCreditsWithStatus(MyCourse::passed);
        int ndropped = term.second.numberofCreditsWithStatus(MyCourse::emergency_drop);
        int nrefused = term.second.numberofCreditsWithStatus(MyCourse::refused);
        items.push_back(new QTableWidgetItem(QString::number(nall)));
        ui->TBW_Terms->setItem(r, 1, items.back());
        items.push_back(new QTableWidgetItem(QString::number(npassed)));
        ui->TBW_Terms->setItem(r, 2, items.back());
        items.push_back(new QTableWidgetItem(QString::number(nall - npassed - nrefused - ndropped - nrefused)));
        ui->TBW_Terms->setItem(r, 3, items.back());
        items.push_back(new QTableWidgetItem(QString::number(ndropped)));
        ui->TBW_Terms->setItem(r, 4, items.back());
        items.push_back(new QTableWidgetItem(QString::number(nrefused)));
        ui->TBW_Terms->setItem(r, 5, items.back());

        items.push_back(new QTableWidgetItem);
        switch(term.second.getStatus())
        {
        case MyTerm::created :
            items.back()->setText("ایجاد شده");
            break;
        case MyTerm::preliminary_enrollment_confirmed_by_student :
        case MyTerm::preliminary_enrollment_confirmed_by_professor :
        case MyTerm::preliminary_enrollment_rejected_by_professor :
            items.back()->setText("ثبت نام مقدماتی");
            break;
        case MyTerm::enrollment_in_action :
            items.back()->setText("در حال ثبت نام");
            break;
        case MyTerm::amendment_in_action :
            items.back()->setText("ترمیم");
            break;
        case MyTerm::studying :
            items.back()->setText("مشغول به تحصیل");
            break;
        case MyTerm::passed :
            items.back()->setText("قبول");
            break;
        case MyTerm::on_probation :
            items.back()->setText("مشروط");
            break;
        case MyTerm::refused :
            items.back()->setText("رد");
            break;
        case MyTerm::removed :
            items.back()->setText("حذف ترم");
            break;
        default:
            items.back()->setText("نامشخص");
        }
        ui->TBW_Terms->setItem(r, 6, items.back());

        r++;
    }
}

void FullInformationForm::on_TBW_Terms_cellClicked(int row, int column)
{
    if (mode == 0)
    {
        mode = 1;
        curtermno = ui->TBW_Terms->item(row, 0)->text().toInt();
        deleteItems();
        ui->TBW_Terms->setColumnCount(6);
        QStringList header;
        header << "شماره درس" << "نام درس" << "واحد" << "نمره" << "وضعیت" << "نوع درس";
        ui->TBW_Terms->setHorizontalHeaderLabels(header);

        std::map<PresentedCourse*, MyCourse> courses = Extstudent->getTermCourses(curtermno);
        int r = 0;

        for(const auto& course : courses)
        {
            ui->TBW_Terms->insertRow(r);
            items.push_back(new QTableWidgetItem);
            items.back()->setText(QString::number(course.first->getGroup_no()) + "_" + QString::number(course.first->getCourseID()));
            ui->TBW_Terms->setItem(r, 0, items.back());
            items.push_back(new QTableWidgetItem(QString::fromStdString(course.first->getName())));
            ui->TBW_Terms->setItem(r, 1, items.back());
            items.push_back(new QTableWidgetItem(QString::number(course.first->getCredit())));
            ui->TBW_Terms->setItem(r, 2, items.back());
            items.push_back(new QTableWidgetItem(course.second.getScore() >=0 ? QString::number(course.second.getScore()) : ""));
            ui->TBW_Terms->setItem(r, 3, items.back());

            items.push_back(new QTableWidgetItem);
            switch(course.second.getStatus())
            {
            case MyCourse::enrolled :
                items.back()->setText("ثبت");
                break;
            case MyCourse::waiting :
                items.back()->setText("انتظار");
                break;
            case MyCourse::notconfirmed :
                items.back()->setText("تایید نشده");
                break;
            case MyCourse::confirmed :
                items.back()->setText("تایید شده");
                break;
            case MyCourse::passed :
                items.back()->setText("قبول");
                break;
            case MyCourse::refused :
                items.back()->setText("رد");
                break;
            case MyCourse::emergency_drop :
                items.back()->setText("حذف اضطراری");
                break;
            default:
                items.back()->setText("نامشخص");
            }
            ui->TBW_Terms->setItem(r, 4, items.back());

            items.push_back(new QTableWidgetItem);
            switch(course.first->getType())
            {
            case 0 :
                items.back()->setText("پایه");
                break;
            case 1 :
                items.back()->setText("عمومی");
                break;
            case 2 :
                items.back()->setText("اصلی");
                break;
            case 3 :
                items.back()->setText("تخصصی");
                break;
            case 4 :
                items.back()->setText("اختیاری");
                break;
            default:
                items.back()->setText("نامشخص");
            }
            ui->TBW_Terms->setItem(r, 5, items.back());

            r++;
        }
    }
    else if (mode == 1)
    {
        // objection to score
    }
}
