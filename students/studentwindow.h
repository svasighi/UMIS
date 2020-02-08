#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QWidget>

namespace Ui {
class StudentWindow;
}

class StudentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr);
    ~StudentWindow();

private:
    Ui::StudentWindow *ui;

private slots:
    void on_TB_Signout_clicked();
    void on_TW_Program_tabCloseRequested(int index);
    void on_PB_PresentedCourses_clicked();
    void on_PB_WeekSchedule_clicked();
    void on_PB_ExamSchedule_clicked();
    /*void on_PB_Tuition_clicked();*/
    void on_PB_Assessment_clicked();
    void on_PB_FullInformatin_clicked();

};

#endif // STUDENTWINDOW_H
