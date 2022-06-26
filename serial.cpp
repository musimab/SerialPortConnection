#include "serial.h"
#include <QDebug>

SerialPort::SerialPort(QObject *parent) : QObject(parent)
{
    m_serialPort = new QSerialPort(this);
    initSerialPortConfiguration();
    connect(m_serialPort, &QIODevice::readyRead, this, &SerialPort::readSerial);
}

SerialPort::~SerialPort()
{
    if(m_serialPort->isOpen()) {
        m_serialPort->close();
    }
}

void SerialPort::initSerialPortConfiguration()
{
    bool arduino_is_available = false;
    QString arduiono_uno_port_name;

    foreach(const QSerialPortInfo & serialPortInfo, QSerialPortInfo::availablePorts()) {
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()) {
            if((serialPortInfo.productIdentifier() == arduaino_uno_product_id)
                    && (serialPortInfo.vendorIdentifier() == arduaino_uno_vendor_id)) {
                arduino_is_available = true;
                arduiono_uno_port_name = serialPortInfo.portName();
            }
        }
    }
    if (arduino_is_available) {
        qDebug() << "Found the arduino port ..." << arduiono_uno_port_name;
        m_serialPort->setPortName(arduiono_uno_port_name);
        m_serialPort->open(QSerialPort::ReadWrite);
        m_serialPort->setBaudRate(QSerialPort::Baud9600);
        m_serialPort->setDataBits(QSerialPort::Data8);
        m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
        m_serialPort->setParity(QSerialPort::NoParity);
        m_serialPort->setStopBits(QSerialPort::OneStop);
     }
    else {
        qDebug() << "Couldnt find the correct port for arduino";
    }
}

void SerialPort::readSerial(){
    qDebug() << "Read signal";
    TempInfo temperature_info;
    //while(m_serialPort->canReadLine()) {
        m_buffer = m_serialPort->readAll();
        qDebug() << "Read signal:.." << m_buffer;
        temperature_info.temperature_value = m_buffer.trimmed().toDouble();
        temperature_info.temperature_id = 15;
        //qDebug() << "Read signal" << temperature_info.temperature_value;
        emit send_temperature_info(temperature_info.temperature_value);
    //}
}

void SerialPort::increaseLedBrightness(int value)
{
    qDebug() << "increase led" << QString("r%1").arg(value);
    writeSerial(QString("r%1").arg(value));
}

void SerialPort::changeTransmitvalue()
{
    QByteArray sentData;
    //sentData.resize(8);
    quint8 num = 77;
    sentData[0] = 1;
    sentData[1] = 2;
    sentData[2] = 5;
    sentData[3] = 25;
    sentData[4] = 99;
    sentData[5] = 'a';
    sentData[6] = 'b';

    qDebug() << "sentData size:" << sentData.size();
    if(m_serialPort->isWritable()) {
        m_serialPort->write(sentData);
        m_serialPort->waitForBytesWritten(100);
        qDebug() << sentData;
    }

    else {
        qDebug() << "Couldnt write to serial";
    }
}

void SerialPort::writeSerial( QString command)
{

    if(m_serialPort->isWritable()) {
        m_serialPort->write(command.toStdString().c_str());
    }

    else {
        qDebug() << "Couldnt write to serial";
    }
}



QByteArray SerialPort::writeAndRead(Command com, quint8 y1, quint8 y2)
{

    // Data sent to the serial port.
    QByteArray sentData;
    sentData[0] = 15;
    sentData[1] = 25;
    sentData[2] = 35;
    sentData[3] = 45;
    sentData[4] = 55;
    sentData[5] = 65;
    sentData[6] = 75;
    sentData[7] = 85;
    qDebug() << sentData.size();
    // Write to the serial port and wait for up to 100 ms until the recording is done.
    m_serialPort->write(sentData);
    m_serialPort->waitForBytesWritten(100);

}

