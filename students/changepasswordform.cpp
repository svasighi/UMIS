#include "changepasswordform.h"
#include "ui_changepasswordform.h"
#include <QMessageBox>
#include <QCryptographicHash>

extern Student* Extstudent;

ChangePasswordForm::ChangePasswordForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePasswordForm)
{
    ui->setupUi(this);
}

ChangePasswordForm::~ChangePasswordForm()
{
    delete ui;
}

void ChangePasswordForm::on_PB_Commit_clicked()
{
    if (ui->LE_newPass->text().length() < 6)
    {
        QMessageBox::critical(this, "خطا", "گذرواژه جدید باید حداقل شش رقم باشد");
        return;
    }
    // QCryptographicHash::hash((ui->LE_curPass->text().toUtf8()), QCryptographicHash::Md5).toHex();
    std::string curpassword = ui->LE_curPass->text().toStdString();
    std::string newpassword = ui->LE_newPass->text().toStdString();
    bool f = Extstudent->changePassword(curpassword, newpassword);
    if (f == false)
    {
        QMessageBox::critical(this, "خطا", "گذرواژه فعلی نادرست وارد شده است");
    }
    else
    {
        QMessageBox::information(this, "", "گذرواژه با موفقیت تغییر یافت");
    }
}
