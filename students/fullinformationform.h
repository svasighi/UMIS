#ifndef FULLINFORMATIONFORM_H
#define FULLINFORMATIONFORM_H

#include <QWidget>

namespace Ui {
class FullInformationForm;
}

class FullInformationForm : public QWidget
{
    Q_OBJECT

public:
    explicit FullInformationForm(QWidget *parent = nullptr);
    ~FullInformationForm();

private:
    Ui::FullInformationForm *ui;
};

#endif // FULLINFORMATIONFORM_H
