#include "form.h"
#include "ui_form.h"
#include "Struct.h"

// 这个是查看事件的窗口

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::Form) {
    ui_->setupUi(this);
    ui_->todolist->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);          // 设置表格平分
//    ui_->todolist->setColumnWidth(0, 80);

}

Form::~Form() {
    delete ui_;

}


//  显示任务列表
void Form::ShowList() {
    LoadEvent();
    this->setWindowFlags(Qt::CoverWindow | Qt::FramelessWindowHint | windowFlags());        // 设置窗口置顶，边框隐藏
    this->setAttribute(Qt::WA_TranslucentBackground);        // 设置窗口透明
    this->show();

}

/// TODO: 1. 关闭窗口的时候判断checkbox，然后删除eventlist里面的内容，再重写配置文件

void Form::HideList() {
//    for (int i = 0; i < eventCount; ++i) {
//        if(status_[i].cbox->checkState() == Qt::Unchecked){
//            eventlist.removeAt(i);
//            status_.removeAt(i);
//            eventCount--;
//        }
//    }
//    cfg->beginGroup("eventList");
//    cfg->clear();
//    cfg->setValue("count",eventCount);
//    for (int i = 0; i < eventCount; ++i) {
//        cfg->setValue("event"+QString::number(i+1),eventlist[i].event);
//    }
//    cfg->endGroup();
    this->hide();
}

// 加载列表内的事件
void Form::LoadEvent() {
    cfg->beginGroup("eventList");
    eventCount = cfg->value("count").toInt();           // 先从配置文件中获取事件的个数
    eventlist.clear();


    for (int i = 0; i < eventCount; ++i) {
        eventList node;
//        checkBox cnode;
//        cnode.cbox->setCheckState(Qt::Checked);
        node.event = cfg->value("event" + QString::number(i + 1)).toString();
        eventlist.append(node);                     // 从配置文件中读取事件存到列表中
//        status_.append(cnode);

//        disconnect(status_[i].cbox,0,0,0);
//        connect(status_[i].cbox, &QCheckBox::stateChanged, this, [=](int state) {
//          if (state == Qt::Unchecked) {
////              eventlist.removeAt(i);
////             status_[i].cbox->setCheckState(Qt::Unchecked);     // 这个是需要写的吗？
//              qDebug() << "unchecked" << i;
//          } else {
//              qDebug() << "checked" << i;
//          }
//        });
    }
    cfg->endGroup();

    ui_->todolist->setRowCount(eventCount);
    for (int i = 0; i < eventCount; ++i) {
//        ui_->todolist->setCellWidget(i, 0, status_[i].cbox);
        ui_->todolist->setItem(i, 1, new QTableWidgetItem(eventlist[i].event));   // 渲染列表中存储好的事件
        ui_->todolist->setItem(i, 0, new QTableWidgetItem("无"));     // 没有选择控件之前，先将就一下吧

    }
}
