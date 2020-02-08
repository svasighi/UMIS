#ifndef WEEKSCHEDULEFORM_H
#define WEEKSCHEDULEFORM_H

#include <QWidget>
#include <QTableWidgetItem>
#include "../variables.h"

namespace Ui {
class WeekScheduleForm;
}

class WeekScheduleForm : public QWidget
{
    Q_OBJECT

public:
    explicit WeekScheduleForm(QWidget *parent = nullptr);
    ~WeekScheduleForm();
	void deleteItems();

private slots:
    void on_PB_ShowResult_clicked();

private:
    Ui::WeekScheduleForm *ui;
	std::vector<QTableWidgetItem*> items;
};

#endif // WEEKSCHEDULEFORM_H
