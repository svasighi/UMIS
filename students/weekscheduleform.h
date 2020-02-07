#ifndef WEEKSCHEDULEFORM_H
#define WEEKSCHEDULEFORM_H

#include <QWidget>

namespace Ui {
class WeekScheduleForm;
}

class WeekScheduleForm : public QWidget
{
    Q_OBJECT

public:
    explicit WeekScheduleForm(QWidget *parent = nullptr);
    ~WeekScheduleForm();

private:
    Ui::WeekScheduleForm *ui;
};

#endif // WEEKSCHEDULEFORM_H
