#include "boggleWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BoggleWindow boggle;
    boggle.setWindowTitle("this is boggle window");
    boggle.show();



    //boggle.show();
    //QWidget *widget = new QWidget();
    //QGraphicsScene scene;
    //QRectF boardRect = QRectF(50,50,100,100);
    //QGraphicsProxyWidget *proxy = scene.addWidget(widget);
    //QGridLayout *layout = new QGridLayout;
    //QGroupBox *groupbox = new QGroupBox;
    //Boggle w;
    //w.show();
    //QWidget w;
    //QLabel *ql = new QLabel();
    //QLineEdit *textBox = new QLineEdit();
    //Boggle *boggle = new Boggle(kBoardSize,kBoardSize,boardRect,widget);
    //layout->addWidget(ql,0,1);
    //layout->addWidget(textBox,0,2);
    //layout->addWidget(boggle,1,1,1,2);

    //groupbox->setLayout(layout);
    //scene.addWidget(groupbox);

    //QGraphicsView view(&scene);
    //view.show();


    //view.show();
    //QTextStream out(stdout);
    //out << QString("SomeTesa");

    //Boggle p;
    //QGraphicsView aview(p.getScene());
    //aview.show();
    //p.drawBoard();
    
    return a.exec();
}
