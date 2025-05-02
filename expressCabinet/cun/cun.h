#ifndef CUN_H
#define CUN_H

#include <QWidget>

namespace Ui {
class cun;
}

class cun : public QWidget
{
    Q_OBJECT

public:
    explicit cun(QWidget *parent = nullptr);

    
    ~cun();

private:
    Ui::cun *ui;
};

#endif // CUN_H
