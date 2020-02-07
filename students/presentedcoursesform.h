#ifndef PRESENTEDCOURSESFORM_H
#define PRESENTEDCOURSESFORM_H

#include <QWidget>

namespace Ui {
class PresentedCoursesForm;
}

class PresentedCoursesForm : public QWidget
{
    Q_OBJECT

public:
    explicit PresentedCoursesForm(QWidget *parent = nullptr);
    ~PresentedCoursesForm();

private:
    Ui::PresentedCoursesForm *ui;
};

#endif // PRESENTEDCOURSESFORM_H
