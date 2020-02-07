#ifndef PROFESSORSLISTFORM_H
#define PROFESSORSLISTFORM_H

#include <QMainWindow>

namespace Ui {
class ProfessorsListForm;
}

class ProfessorsListForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProfessorsListForm(QWidget *parent = nullptr);
    ~ProfessorsListForm();

private slots:
    void on_readData_clicked();

private:
    Ui::ProfessorsListForm *ui;
};

#endif // PROFESSORSLISTFORM_H
