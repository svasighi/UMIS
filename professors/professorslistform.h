#ifndef PROFESSORSLISTFORM_H
#define PROFESSORSLISTFORM_H

#include <QWidget>
#include "../dbmanager.h"

namespace Ui {
class ProfessorsListForm;
}

class ProfessorsListForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProfessorsListForm(QWidget *parent = nullptr);
    ~ProfessorsListForm();

private slots:
    void on_PB_ReadData_clicked();

    void on_PB_AddProfessor_clicked();

private:
    Ui::ProfessorsListForm *ui;
};

#endif // PROFESSORSLISTFORM_H
