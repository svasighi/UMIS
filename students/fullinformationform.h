#ifndef FULLINFORMATIONFORM_H
#define FULLINFORMATIONFORM_H

#include <QWidget>
#include <QTableWidgetItem>
#include "../variables.h"

namespace Ui {
class FullInformationForm;
}

class FullInformationForm : public QWidget
{
    Q_OBJECT

public:
    explicit FullInformationForm(QWidget *parent = nullptr);
    ~FullInformationForm();
	void deleteItems();

private slots:
    void on_PB_Refresh_clicked();
    void on_TBW_Terms_cellClicked(int row, int column);

private:
    Ui::FullInformationForm *ui;
	std::vector<QTableWidgetItem*> items;
    int mode;
    int curtermno;
};

#endif // FULLINFORMATIONFORM_H
