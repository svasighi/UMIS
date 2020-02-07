#ifndef PROFESSORPRESENTEDCOURSESFORM_H
#define PROFESSORPRESENTEDCOURSESFORM_H

#include <QWidget>

namespace Ui {
class ProfessorPresentedCoursesForm;
}

class ProfessorPresentedCoursesForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProfessorPresentedCoursesForm(QWidget *parent = nullptr);
    ~ProfessorPresentedCoursesForm();

private:
    Ui::ProfessorPresentedCoursesForm *ui;
};

#endif // PROFESSORPRESENTEDCOURSESFORM_H
