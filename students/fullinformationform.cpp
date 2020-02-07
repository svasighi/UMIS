#include "fullinformationform.h"
#include "ui_fullinformationform.h"

FullInformationForm::FullInformationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FullInformationForm)
{
    ui->setupUi(this);
}

FullInformationForm::~FullInformationForm()
{
    delete ui;
}
