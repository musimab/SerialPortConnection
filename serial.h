#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QThread>

class SerialPort : public QObject
{
    Q_OBJECT

private:
    QByteArray m_buffer;
    QSerialPort* m_serialPort;
    bool m_isConnected;
    QString parsed_received_data;
    enum class Command: quint8;

    enum class Command : quint8
        {
            S = 0x53, // Command request status.
            P = 0x50, // Command for setting parameters.
            N = 0x4e, // Command to turn on the X-ray.
            F = 0x46  // X-ray shutdown command.
        };

    const quint8 STARTBYTE = 0x40;  // Beginning of the parcel.
    const quint8 DEV = 0;  // Emitter ID.
    static const quint16 arduaino_uno_vendor_id = 6790;
    static const quint16 arduaino_uno_product_id = 29987;
public:
    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort();

    void initSerialPortConfiguration();
    void writeSerial(QString command);
    QByteArray writeAndRead(Command com, quint8 y1, quint8 y2);
    struct TempInfo {
        double temperature_value = 0;
        int temperature_id = 12;
    };

public slots:

     void readSerial();
     void increaseLedBrightness(int value);
     void changeTransmitvalue();

signals:
    void send_temperature_info(double temp_info);


};

#endif // SERIAL_H
