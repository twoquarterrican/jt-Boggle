#include "bogglegameplay.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QString path = QDir::currentPath();
//    qDebug () << path;
//    qDebug() << QCoreApplication::applicationDirPath();
//    QFileInfo exec_fileinfo(argv[0]);
//    qDebug() << "Executable is in" << exec_fileinfo.absolutePath();
//    QFile file("EnglishWords.dat");
//    //QFile file("test.txt");
//    if (!file.open(QIODevice::ReadOnly)) return 5;
//    QByteArray blob = file.readAll();

    BoggleGamePlay game;
   
    return a.exec();
}
