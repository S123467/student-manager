#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

/**
 * @brief 主函数
 * 程序入口点
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置应用程序信息
    a.setApplicationName("StudentManager");
    a.setApplicationVersion("1.0");
    a.setOrganizationName("University");

    // 使用 Fusion 风格，界面更美观
    a.setStyle(QStyleFactory::create("Fusion"));

    MainWindow w;
    w.show();

    return a.exec();
}
