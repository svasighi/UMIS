#include "presentedcoursesform.h"
#include "ui_presentedcoursesform.h"
#include <QMessageBox>

extern Student* Extstudent;

PresentedCoursesForm::PresentedCoursesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PresentedCoursesForm)
{
    ui->setupUi(this);
}

PresentedCoursesForm::~PresentedCoursesForm()
{
	deleteItems();
    delete ui;
}

void PresentedCoursesForm::deleteItems()
{
    for (int i = items.size() - 1; i >= 0; i--)
    {
        delete items[i];
    }
    items.clear();
    for (int i = ui->TBW_Courses->rowCount() - 1; i >= 0; i--)
    {
        ui->TBW_Courses->removeRow(i);
    }
}

void PresentedCoursesForm::on_PB_ShowResult_clicked()
{
    int term = ui->LE_TermNo->text().toInt();
    deleteItems();
    // complete
}
