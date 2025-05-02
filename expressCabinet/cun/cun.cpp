#include "cun.h"
#include "ui_cun.h"

cun::cun(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cun)
{
    ui->setupUi(this);
}

cun::~cun()
{
    delete ui;
}
