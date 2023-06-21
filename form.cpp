#include "form.h"
#include "ui_form.h"
#include "Struct.h"


Form::Form(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::Form) {
    ui_->setupUi(this);
    ui_->todolist->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui_->todolist->setColumnWidth(0, 40);
}

Form::~Form() {
    delete ui_;

}

///TODO: 1. 用一个结构体把信息储存起来   2. 把信息写入配置文件

// 显示任务清单
/// TODO: 1. 渲染控件就放到dialog那里去，这里调用就行

void Form::ShowList() {
//    ui_dialog_->LoadEvent();
    this->setWindowFlags(Qt::CoverWindow | Qt::FramelessWindowHint | windowFlags());
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->show();
}

void Form::HideList() {

    this->hide();
}

