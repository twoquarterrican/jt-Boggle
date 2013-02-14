#include "bogglegameplay.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BoggleGamePlay game;
   
    return a.exec();
}
