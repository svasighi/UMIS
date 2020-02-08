#ifndef PREPENROLLMENTFORM_H
#define PREPENROLLMENTFORM_H

#include <QWidget>
#include "../variables.h"

namespace Ui {
class PrepEnrollmentForm;
}

class PrepEnrollmentForm : public QWidget
{
    Q_OBJECT

public:
    explicit PrepEnrollmentForm(QWidget *parent = nullptr);
    ~PrepEnrollmentForm();

private:
    Ui::PrepEnrollmentForm *ui;
};

#endif // PREPENROLLMENTFORM_H
