#ifndef PROFESSORWINDOW_H
#define PROFESSORWINDOW_H

#include <QWidget>

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
    void on_PB_EnterScores();
    void on_PB_StudentsObjections();
    void on_PB_SrudentsList();
    void on_PB_Exceptions();
    void on_PB_PreEnrollmentStats();
    void on_PB_AddCourse();
    void on_PB_AddPresentedCourse();
    void on_PB_ProfessorsAssesment();
    void on_PB_CalculateSalary();
    void on_PB_ProfessorsList();
};

#endif // PROFESSORWINDOW_H
