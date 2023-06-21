#include "adddialog.h"
#include "ui_adddialog.h"
#include "Struct.h"

/// TODO: 1. 写入配置文件，每次打开都要从配置文件中导入渲染
///       2. 鼠标悬停，随机弹出tips  （qt好像实现不了这样的效果）
///       3. 允许用户自定义图像
///       4. 对配置文件的操作很乱，可以适当优化一下

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDialog) {
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint | windowFlags());         // 置顶让用户方便查看其他信息
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //  启动就渲染table的内容
    cfg->beginGroup("eventList");
    eventCount = cfg->value("count").toInt();
    ui->tableWidget->setRowCount(eventCount);
    ui->tableWidget->setColumnCount(1);
    qDebug() << "dialog" << eventCount;
    for (int i = 0; i < eventCount; ++i) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(cfg->value("event" + QString::number(i + 1)).toString()));
        qDebug() << cfg->value("event" + QString::number(i + 1)).toString();
    }
    cfg->endGroup();

    // 确认按钮
    connect(ui->confirm_button, &QPushButton::clicked, this, [&] {
      // 清理先前的内容，重新录入一遍
      eventlist.clear();

      // 直接读取表格内的内容添加进数组的
      for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
          eventList node;
          node.event = ui->tableWidget->item(i, 0)->text();         // 不能虚空添加。
          eventlist.append(node);
      }
      qDebug() << eventlist.size();

      this->hide();

      // 写入配置文件
      cfg->beginGroup("eventList");
      cfg->setValue("count", eventCount);
      for (int i = 0; i < eventlist.size(); ++i) {
          cfg->setValue("event" + QString::number(i + 1), eventlist[i].event);
      }
      cfg->endGroup();
    });

    // 添加按钮
    connect(ui->add_button, &QPushButton::clicked, this, [&] {

      eventCount++;
      ui->tableWidget->setRowCount(eventCount);
    });

    // 删除按钮
    connect(ui->delete_button, &QPushButton::clicked, this, [&] {
      int position;         // 默认是0
      position = ui->tableWidget->currentRow();         // 如果没选中的话，就是-1
      if (position != -1) {
          eventCount ? eventCount-- : eventCount = 0;
          ui->tableWidget->removeRow(position);
          eventlist.removeAt(position);
          cfg->beginGroup("eventList");
          cfg->clear();
          cfg->endGroup();
      }
    });

    // 取消按钮
    connect(ui->cancel_button, &QPushButton::clicked, this, [&] {

      this->hide();
    });

    // 开启就读取信息进数组
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        eventList node;
        node.event = ui->tableWidget->item(i, 0)->text();         // 不能虚空添加。
        eventlist.append(node);
    }
    qDebug() << eventlist.size();
}

AddDialog::~AddDialog() {
    delete ui;
}
