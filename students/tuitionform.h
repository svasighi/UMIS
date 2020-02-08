#ifndef TUITIONFORM_H
#define TUITIONFORM_H

#include <QWidget>
#include "../variables.h"

namespace Ui {
class TuitionForm;
}

class TuitionForm : public QWidget
{
    Q_OBJECT

public:
    explicit TuitionForm(QWidget *parent = nullptr);
    ~TuitionForm();

private:
    Ui::TuitionForm *ui;
};

#endif // TUITIONFORM_H
