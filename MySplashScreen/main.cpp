#include "widget.h"

#include <QApplication>
#include <QSplashScreen>
#include <QDateTime>
#include <QBoxLayout>
#include "myprogresspie.h"
#include "myprogressring.h"

#define MY_SPLASH_SCREEN_PIXMAP_PATH ":/new/luanch/src/luanch.JPG"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap luanchPixmap(MY_SPLASH_SCREEN_PIXMAP_PATH);
    luanchPixmap = luanchPixmap.scaled(600, 240);
    QSplashScreen mySplashScreen(luanchPixmap);
    Widget w;

    /* 设置启动页样式 */
    mySplashScreen.setFixedSize(600, 240);

    /* 在启动页上添加控件 */
    QHBoxLayout splashScreenLayout(&mySplashScreen);
    MyProgressPie progressPie(&mySplashScreen);
    progressPie.setRange(0, 100);
    progressPie.setFixedSize(100, 100);

    MyProgressRing progressRing(&mySplashScreen);
    progressRing.setRange(0, 100);
    progressRing.setFixedSize(100, 100);
    //progressBar.setStyleSheet("QProgressBar::chunk{"\
    //"background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 red,stop:1 blue);}");
    splashScreenLayout.addStretch(1);
    splashScreenLayout.addWidget(&progressPie);
    splashScreenLayout.addStretch(1);
    splashScreenLayout.addWidget(&progressRing);
    splashScreenLayout.addStretch(1);
    mySplashScreen.setLayout(&splashScreenLayout);

    /* 先显示启动页 */
    mySplashScreen.show();

    /* 延时处理 */
    QDateTime relayTime = QDateTime::currentDateTime();
    QDateTime currentTime;

    do
    {
        currentTime = QDateTime::currentDateTime();
        progressPie.setValue(relayTime.secsTo(currentTime) / 10.0 * 100);
        progressRing.setValue(relayTime.secsTo(currentTime) / 10.0 * 100);

        /* 刷新UI */
        QCoreApplication::processEvents();
    }
    while(relayTime.secsTo(currentTime) < 10);

    /* 显示软件界面 */
    w.show();

    /* 关闭启动页 */
    mySplashScreen.finish(&w);
    int iRet = a.exec();

    /* 退出页 */
    mySplashScreen.show();
    relayTime = QDateTime::currentDateTime();
    progressPie.setValue(0);
    do
    {
        currentTime = QDateTime::currentDateTime();
        progressPie.setValue(relayTime.secsTo(currentTime) / 10.0 * 100);
        progressRing.setValue(relayTime.secsTo(currentTime) / 10.0 * 100);
        /* 刷新UI */
        QCoreApplication::processEvents();
    }
    while(relayTime.secsTo(currentTime) < 10);

    return iRet;
}
