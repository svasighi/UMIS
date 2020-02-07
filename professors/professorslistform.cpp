#include "professorslistform.h"
#include "ui_professorslistform.h"
#include <QTextStream>
#include <QFile>

ProfessorsListForm::ProfessorsListForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfessorsListForm)
{
    ui->setupUi(this);
}

ProfessorsListForm::~ProfessorsListForm()
{
    delete ui;
}
/* void Write(QString Filename ,QString data){

    QFile myFile(Filename);
    if(!myFile.open(QFile::WriteOnly|QFile::Text))
    {
        return;
    }
    QTextStream out(&myFile);
    out << data;
    myFile.flush();
    myFile.close();

}
void Update(QString Filename ,QString data){

    QFile myFile(Filename);
    if(!myFile.open(QFile::ReadWrite|QFile::Text))
    {
        return;
    }
    QTextStream inout(&myFile);

    inout >> ;
    myFile.flush();
    myFile.close();

}
*/
void ProfessorsListForm::on_readData_clicked()
{

    QFile myFile("../sotrage/professors.txt");
    if(!myFile.open(QFile::ReadOnly|QFile::Text))
    {

    }
    QTextStream in(&myFile);
    QString text = in.readAll();

    myFile.close();
    ;
}
