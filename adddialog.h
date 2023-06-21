#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "Struct.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class addDialog;
}
QT_END_NAMESPACE

class AddDialog : public QDialog {
 Q_OBJECT

 public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

 private:
    Ui::addDialog *ui;

};

#endif // ADDDIALOG_H
