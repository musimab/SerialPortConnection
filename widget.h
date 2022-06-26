#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include "serial.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_receiveButton_clicked();

    //void on_horizontalSlider_valueChanged(int value);


private:
    Ui::Widget *ui;
    QThread* m_pThread;
    SerialPort* workerSerial = nullptr;

};
#endif // WIDGET_H
