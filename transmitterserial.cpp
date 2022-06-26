#include "transmitterserial.h"

TransmitterSerial::TransmitterSerial(QObject *parent) : QObject(parent)
{
    m_transmitterPort = new QSerialPort(this);
    //initSerialPortConfiguration();


}

void TransmitterSerial::initSerialPortConfiguration()
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
        m_transmitterPort->setPortName(arduiono_uno_port_name);
        m_transmitterPort->open(QSerialPort::WriteOnly);
        m_transmitterPort->setBaudRate(QSerialPort::Baud9600);
        m_transmitterPort->setDataBits(QSerialPort::Data8);
        m_transmitterPort->setFlowControl(QSerialPort::NoFlowControl);
        m_transmitterPort->setParity(QSerialPort::NoParity);
        m_transmitterPort->setStopBits(QSerialPort::OneStop);
     }
    else {
        qDebug() << "Couldnt find the correct port for arduino";
    }
}

void TransmitterSerial::writeSerial(QString command)
{

    if(m_transmitterPort->isWritable()) {
        m_transmitterPort->write(command.toStdString().c_str());

    }
    else {
        qDebug() << "Couldnt write to serial";
    }
}
