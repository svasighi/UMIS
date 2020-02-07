#ifndef EXAMSCHEDULEFORM_H
#define EXAMSCHEDULEFORM_H

#include <QWidget>

namespace Ui {
class ExamScheduleForm;
}

class ExamScheduleForm : public QWidget
{
    Q_OBJECT

public:
    explicit ExamScheduleForm(QWidget *parent = nullptr);
    ~ExamScheduleForm();

private:
    Ui::ExamScheduleForm *ui;
};

#endif // EXAMSCHEDULEFORM_H
