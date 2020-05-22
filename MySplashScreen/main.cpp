#include "widget.h"

#include <QApplication>
#include <QSplashScreen>
#include <QDateTime>
#include <QBoxLayout>
#include <QProgressBar>

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
    QVBoxLayout splashScreenLayout(&mySplashScreen);
    QProgressBar progressBar(&mySplashScreen);
    progressBar.setRange(0, 100);
    progressBar.setFixedHeight(40);
    progressBar.setStyleSheet("QProgressBar::chunk{"\
    "background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 red,stop:1 blue);}");
    splashScreenLayout.addStretch(2);
    splashScreenLayout.addWidget(&progressBar);
    splashScreenLayout.addStretch(1);
    mySplashScreen.setLayout(&splashScreenLayout);

    /* 先显示启动页 */
    mySplashScreen.show();

    /* 延时处理 */
    QDateTime relayTime = QDateTime::currentDateTime();
    QDateTime currentTime;
    int i = 0;
    do
    {
        currentTime = QDateTime::currentDateTime();
        progressBar.setValue(i * 20);

        /* 刷新UI */
        QCoreApplication::processEvents();
        i++;
    }
    while(relayTime.secsTo(currentTime) <= 5);

    /* 显示软件界面 */
    w.show();

    /* 关闭启动页 */
    mySplashScreen.finish(&w);
    return a.exec();
}
