#include "myprogressring.h"
#include <QPainter>

MyProgressRing::MyProgressRing(QWidget *parent) : QWidget(parent),
    dMin(0),
    dMax(100),
    dValue(0),
    progressColor(QColor("#1F8CE1")),
    backgroundColor(QColor("#1F8CE1")),
    otherColor(QColor("#E6E6E6"))
{

}

void MyProgressRing::setValue(double dValue)
{
    this->dValue = dValue;
    this->update();
}

void MyProgressRing::setRange(double dMin, double dMax)
{
    this->dMin = dMin;
    this->dMax = dMax;
}

void MyProgressRing::setColor(QColor backgroundColor, QColor progressColor, QColor otherColor)
{
    this->backgroundColor = backgroundColor;
    this->progressColor = progressColor;
    this->otherColor = otherColor;
}

void MyProgressRing::drawForeground(QPainter *pPainter)
{
    int iRadius = 80;
    pPainter->save();
    pPainter->setPen(Qt::NoPen);
    pPainter->setBrush(QColor("#FFFFFF"));
    pPainter->drawEllipse(-iRadius, -iRadius, iRadius * 2, iRadius *2);
    pPainter->restore();
}

void MyProgressRing::drawProgressPie(QPainter *pPainter)
{
    int iRadius = 100;
    pPainter->save();
    pPainter->setPen(Qt::NoPen);

    QRectF rectF(-iRadius, -iRadius, iRadius * 2, iRadius *2);

    /* 计算当前进度角度 */
    double dAngleAll = 360.0;
    double dAngleCurrent = dAngleAll * ((dValue - dMin)/ (dMax - dMin));
    double dAngleOther = dAngleAll - dAngleCurrent;

    /* 绘制当前进度 */
    pPainter->setBrush(progressColor);
    pPainter->drawPie(rectF, dAngleCurrent * 16, (dAngleAll + 90) * 16);

    /* 绘制剩余进度 */
    pPainter->setBrush(otherColor);
    pPainter->drawPie(rectF, (dAngleAll + 90)* 16, dAngleOther * 16);

    pPainter->restore();
}

void MyProgressRing::paintEvent(QPaintEvent *event)
{
    int iWidth = this->width();
    int iHeight = this->height();
    int iSide = qMin(iWidth, iHeight);

    /* 启用反锯齿 */
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing| QPainter::TextAntialiasing);

    /* 平移坐标轴中心，等比例缩放 */
    painter.translate(iWidth * 0.5, iHeight * 0.5);
    painter.scale(iSide / 200.0, iSide / 200.0);

    /* 绘制进度 */
    drawProgressPie(&painter);

    /* 绘制前景 */
    drawForeground(&painter);
}

