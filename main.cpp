#include "wg.h"
#include "terraformator.h"
#include "appsettings.h"
#include "preset.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    appSettings::instance();

    Terraformator app;

    if(fullscr)
    app.showFullScreen();
    else{
        //Setting Fixed Size //
        app.setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
        app.setFixedSize(800,600);
        //                  //
        app.show();
    }

    return a.exec();
}
