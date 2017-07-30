#include <QtGui>
//#include <mywidget.h>

#include <QApplication>
#include "mainwindow.h"

#include <iostream>
#include <vector>
#include "foncAux.h"
#include <cstdlib> // pour le exit(1)
#include <string>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.window();
    w.show();

    //On initialise le variable de temps por faire des vecteurs aleatoires
    srand((unsigned)time(0));

    return a.exec();
}


