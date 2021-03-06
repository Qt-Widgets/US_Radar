//MIT License

//Copyright (c) 2018 salvato

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#ifndef RADARWIDGET_H
#define RADARWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>

// From the manuals:
// If you intend to use Qt Charts C++ classes in your application,
// use the following include and using directives:
#include <QtCharts>
using namespace QtCharts;


class RadarWidget : public QPolarChart
{
    Q_OBJECT
public:
    explicit RadarWidget(QGraphicsItem *parent = nullptr);
    void stopArduino();

signals:
    void arduinoFound();

public slots:
    void onTimerUpdate();
    void onSerialDataAvailable();
    void onArduinoConnectionTimerTimeout();
    virtual void onArduinoFound();
    void onPointReplaced();

protected:
    void ConnectToArduino();
    int  writeSerialRequest(QByteArray requestData);
    QByteArray decodeResponse(QByteArray response);
    bool executeCommand(QByteArray command);

private:

protected:
    QSerialPort            serialPort;
    QSerialPortInfo        serialPortinfo;
    QList<QSerialPortInfo> serialPorts;
    QSerialPort::BaudRate  baudRate;
    int                    currentPort;
    int                    waitTimeout;
    QByteArray             requestData;
    QByteArray             responseData;
    QTimer                 arduinoConnectionTimer;

    const quint8           StartMarker  = quint8(0xFF);
    const quint8           EndMarker    = quint8(0xFE);
    const quint8           AngleMarker  = quint8(0xFD);
    const quint8           DistMarker   = quint8(0xFC);
    const quint8           SpecialByte  = quint8(0x80);
    const quint8           StartSending = quint8(0x81);
    const quint8           StopSending  = quint8(0x82);
    const quint8           AreYouThere  = quint8(0xAA);

private:
    QTimer updateTimer;
    QLineSeries* series1;
    double angle;
    double distance;
    bool starting;
    int nElem, currElem, iDir;
};

#endif // RADARWIDGET_H
