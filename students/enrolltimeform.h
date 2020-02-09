#ifndef ENROLLTIMEFORM_H
#define ENROLLTIMEFORM_H

#include <QWidget>
#include "../dbmanager.h"

namespace Ui {
class EnrollTimeForm;
}

class EnrollTimeForm : public QWidget
{
    Q_OBJECT

public:
    explicit EnrollTimeForm(QWidget *parent = nullptr);
    ~EnrollTimeForm();

private slots:
    void on_PB_ShowResult_clicked();

private:
    Ui::EnrollTimeForm *ui;
};

#endif // ENROLLTIMEFORM_H
