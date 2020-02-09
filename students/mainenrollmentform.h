#ifndef MAINENROLLMENTFORM_H
#define MAINENROLLMENTFORM_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QLineEdit>
#include "../dbmanager.h"

namespace Ui {
class MainEnrollmentForm;
}

class MainEnrollmentForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainEnrollmentForm(QWidget *parent = nullptr);
    ~MainEnrollmentForm();
    void deleteItems();
    void addPreviousCourses();

private slots:
    void on_PB_AddNewRow_clicked();
    void on_PB_Check_clicked();
    void on_PB_Commit_clicked();

private:
    Ui::MainEnrollmentForm *ui;
    std::vector<QTableWidgetItem*> items;
    std::vector<QComboBox*> comboboxes;
    std::vector<QLineEdit*> lineedits;
    QStringList comboitems;
};

#endif // MAINENROLLMENTFORM_H
