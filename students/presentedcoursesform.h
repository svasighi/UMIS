#ifndef PRESENTEDCOURSESFORM_H
#define PRESENTEDCOURSESFORM_H

#include <QWidget>
#include <QTableWidgetItem>
#include "../dbmanager.h"

namespace Ui {
class PresentedCoursesForm;
}

class PresentedCoursesForm : public QWidget
{
    Q_OBJECT

public:
    explicit PresentedCoursesForm(QWidget *parent = nullptr);
    ~PresentedCoursesForm();
    void deleteItems();

private slots:
    void on_PB_ShowResult_clicked();

private:
    Ui::PresentedCoursesForm *ui;
    std::vector<QTableWidgetItem*> items;
};

#endif // PRESENTEDCOURSESFORM_H
