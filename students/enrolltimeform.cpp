#include "enrolltimeform.h"
#include "ui_enrolltimeform.h"
#include <QMessageBox>

extern Student* Extstudent;

EnrollTimeForm::EnrollTimeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnrollTimeForm)
{
    ui->setupUi(this);
}

EnrollTimeForm::~EnrollTimeForm()
{
    delete ui;
}

void EnrollTimeForm::on_PB_ShowResult_clicked()
{
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
    ui->L_Time->setText(QString::fromStdString(Extstudent->getTerm(term).getEnrollmentBeginTime().getTime(2)));
}
