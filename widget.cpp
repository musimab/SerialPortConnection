#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_pThread = new QThread(this);

}

Widget::~Widget()
{
    delete ui;
    m_pThread->exit();
}


void Widget::on_receiveButton_clicked()
{
    SerialPort* workerSerial = new SerialPort;
    workerSerial->moveToThread(m_pThread);
    //connect(m_pThread, &QThread::started, workerSerial, &SerialPort::initSerialPortConfiguration);
    connect(m_pThread, &QThread::finished, workerSerial, &SerialPort::deleteLater);
    connect(m_pThread, &QThread::started, []() {
        qDebug() << "Thread started";
    });
    connect(m_pThread, &QThread::finished, []() {
        qDebug() << "Thread receiver finished";
    });
    m_pThread->start();
   connect(ui->horizontalSlider, &QSlider::valueChanged, workerSerial, &SerialPort::increaseLedBrightness );

    connect(ui->tansmitButton, &QPushButton::clicked, workerSerial, &SerialPort::changeTransmitvalue);
}



