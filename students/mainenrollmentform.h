#ifndef MAINENROLLMENTFORM_H
#define MAINENROLLMENTFORM_H

#include <QWidget>
#include "../variables.h"

namespace Ui {
class MainEnrollmentForm;
}

class MainEnrollmentForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainEnrollmentForm(QWidget *parent = nullptr);
    ~MainEnrollmentForm();

private:
    Ui::MainEnrollmentForm *ui;
};

#endif // MAINENROLLMENTFORM_H
