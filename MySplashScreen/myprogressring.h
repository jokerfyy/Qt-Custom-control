#ifndef MYPROGRESSRING_H
#define MYPROGRESSRING_H

#include <QWidget>

class MyProgressRing : public QWidget
{
    Q_OBJECT
public:
    explicit MyProgressRing(QWidget *parent = nullptr);

    void setValue(double dValue);
    void setRange(double dMin, double dMax);
    void setColor(QColor backgroundColor, QColor progressColor, QColor otherColor);

private:
    double dMin;
    double dMax;
    double dValue;
    QColor backgroundColor;
    QColor progressColor;
    QColor otherColor;

    void drawForeground(QPainter *pPainter);
    void drawProgressPie(QPainter *pPainter);

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:

};

#endif // MYPROGRESSRING_H
