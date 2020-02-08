#ifndef PROFESSORWINDOW_H
#define PROFESSORWINDOW_H

#include <QWidget>
#include "../variables.h"

namespace Ui {
class ProfessorWindow;
}

class ProfessorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ProfessorWindow(QWidget *parent = nullptr);
    ~ProfessorWindow();

private:
    Ui::ProfessorWindow *ui;
	
signals:
    void want2close();

private slots:

    void on_PB_PresentedCourses_clicked();
    void on_TB_Signout_clicked();
    void on_TW_Program_tabCloseRequested(int);
    void on_PB_EnterScores_clicked();
    void on_PB_StudentsObjections_clicked();
    void on_PB_SrudentsList_clicked();
    void on_PB_Exceptions_clicked();
    void on_PB_PreEnrollmentStats_clicked();
    void on_PB_AddCourse_clicked();
    void on_PB_AddPresentedCourse_clicked();
    void on_PB_ProfessorsAssesment_clicked();
    void on_PB_CalculateSalary_clicked();
    void on_PB_ProfessorsList_clicked();
};

#endif // PROFESSORWINDOW_H
