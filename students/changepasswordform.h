#ifndef CHANGEPASSWORDFORM_H
#define CHANGEPASSWORDFORM_H

#include <QWidget>
#include "../dbmanager.h"

namespace Ui {
class ChangePasswordForm;
}

class ChangePasswordForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePasswordForm(QWidget *parent = nullptr);
    ~ChangePasswordForm();

private slots:
    void on_PB_Commit_clicked();

private:
    Ui::ChangePasswordForm *ui;
};

#endif // CHANGEPASSWORDFORM_H
