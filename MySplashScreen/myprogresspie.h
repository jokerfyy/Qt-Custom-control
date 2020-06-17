#ifndef MYPROGRESSPIE_H
#define MYPROGRESSPIE_H

#include <QWidget>

class MyProgressPie : public QWidget
{
    Q_OBJECT
public:
    explicit MyProgressPie(QWidget *parent = nullptr);

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

    void drawBackground(QPainter *pPainter);
    void drawProgressPie(QPainter *pPainter);

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:

};

#endif // MYPROGRESSPIE_H
