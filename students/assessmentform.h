#ifndef ASSESSMENTFORM_H
#define ASSESSMENTFORM_H

#include <QWidget>
#include "../dbmanager.h"

namespace Ui {
class AssessmentForm;
}

class AssessmentForm : public QWidget
{
    Q_OBJECT

public:
    explicit AssessmentForm(QWidget *parent = nullptr);
    ~AssessmentForm();

private:
    Ui::AssessmentForm *ui;
};

#endif // ASSESSMENTFORM_H
