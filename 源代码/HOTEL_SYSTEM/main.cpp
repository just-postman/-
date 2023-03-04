#include "mainwindow.h"
#include <QApplication>
//#include"clientpage1.h"
//#include"clientpage2.h"
//#include"clientpage3.h"
//#include"clientpage4.h"
#include"SuperPage/superadmin.h"
//#include"superpage1.h"
//#include"superpage2.h"
//#include"superpage3.h"
//#include"superpage4.h"
//#include"superpage5.h"
//#include"superpage6.h"
//#include"myslidervalid.h"
#include"servicewidget.h"
#include"ClientPage/clientwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    qApp->setWindowIcon(QIcon(":/icon/windowIcon.png"));
//    qApp->setApplicationName("新华智慧科技酒店");
    MainWindow w;
    w.setWindowTitle("新华智慧科技酒店");
//    clientWidget clientpage;
//    clientpage.show();
    w.show();
//    servicewidget ser;
//    ser.show();
//    SuperAdmin adminPage;
//    adminPage.show();
    return a.exec();
}
