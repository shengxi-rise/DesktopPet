#include "adddialog.h"
#include "ui_adddialog.h"
#include "Struct.h"

/// TODO: 1. 写入配置文件，每次打开都要从配置文件中导入渲染
///       2. 鼠标悬停，随机弹出tips
///       3. 允许用户自定义图像

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDialog) {
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint | windowFlags());         // 置顶让用户方便查看其他信息
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    eventCount = 0;
    connect(ui->cancel_button, &QPushButton::clicked, this, [&] {

      this->hide();
    });


    connect(ui->confirm_button, &QPushButton::clicked, this, [&] {
      // 清理先前的内容，重新录入一遍
      todolist.clear();
      for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
          eventList node;
          node.event = ui->tableWidget->item(i, 0)->text();         // 不能虚空添加。
          node.done = nullptr;
          todolist.append(node);
      }
      qDebug() << todolist.size();

      this->hide();
      // 配置配置文件
//        QSettings* cfg = new QSettings("../config/eventlist.ini", QSettings::IniFormat);  //保存.ini路径
//        cfg->beginGroup("evenList");
//        cfg->setValue("1","test");
//        cfg->endGroup();
    });


    connect(ui->add_button, &QPushButton::clicked, this, [&] {

      eventCount++;
      ui->tableWidget->setRowCount(eventCount);
    });


    connect(ui->delete_button, &QPushButton::clicked, this, [&] {

      eventCount ? eventCount-- : eventCount = 0;
      int position;
      position = ui->tableWidget->currentRow();
      ui->tableWidget->removeRow(position);

    });

}

AddDialog::~AddDialog() {
    delete ui;
}
