#ifndef EXAMSCHEDULEFORM_H
#define EXAMSCHEDULEFORM_H

#include <QWidget>
#include <QTableWidgetItem>
#include "../variables.h"

namespace Ui {
class ExamScheduleForm;
}

class ExamScheduleForm : public QWidget
{
    Q_OBJECT

public:
    explicit ExamScheduleForm(QWidget *parent = nullptr);
    ~ExamScheduleForm();
    void deleteItems();

private slots:
    void on_PB_ShowResult_clicked();

private:
    Ui::ExamScheduleForm *ui;
    std::vector<QTableWidgetItem*> items;
};

#endif // EXAMSCHEDULEFORM_H
