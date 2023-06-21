#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "Struct.h"
#include "form.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class addDialog;
}
QT_END_NAMESPACE

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

private:
    Ui::addDialog *ui;

    int eventCount;

    QList<eventList> todolist;

    int row_;

    Form* form_;

};

#endif // ADDDIALOG_H
