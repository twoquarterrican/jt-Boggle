#include "lexicon.h"
#include <QMap>
#include <QFile>
#include <QTextStream>
//#include <QErrorMessage>
#include <QDebug>


struct node {
    bool isWord;
    QMap<QChar, node *> suffixes;
    node();
    ~node();
};

node::node() {
    isWord = false;
}

node::~node() {
    foreach (const QChar &ch , suffixes.keys()) {
        delete suffixes[ch];
    }
}

void Lexicon::addFromFile(const QString &filename) {
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //QErrorMessage em(0);
        //em.showMessage("Could not open file "+filename);
        qDebug() << "could not open file "+filename;
        return;
    }
    QTextStream in(&file);
    QString line;
    while(true) {
        line = in.readLine();
        if(line.isNull()) break;
        this->add(line);
    }
}

void Lexicon::add(const QString& word) {
    ensureNodeExists(word)->isWord = true;
}

bool Lexicon::containsPrefix(const QString& prefix) const {
    return findNode(prefix) != NULL;
}

bool Lexicon::contains(const QString& word) const {
    const node *found = findNode(word);
    return found != NULL && found->isWord;
}

const node *Lexicon::findNode(const QString& str) const {
    const node *curr = root;
    for (int pos = 0; pos < str.size() && curr != NULL; pos++) {
        curr = curr->suffixes.contains(str[pos]) ?
                    curr->suffixes.value(str[pos]) : NULL;
    }
    return curr;
}

node *Lexicon::ensureNodeExists(const QString& str) {
    node **currp = &root;
    int pos = 0;
    while (true) {
        if (*currp == NULL) *currp = new node;
        if (pos == str.size()) break;
        currp = &((*currp)->suffixes[str[pos]]);
        pos++;
    }
    return *currp;
}

//void addFromFile(const QString &filename, Lexicon &e) {
//using namespace std;
////qDebug() << "why can't I see anything here?";
////using std::cerr;
////using std::cout;
////using std::endl;
////using std::ifstream;
//// This program reads values from the file 'example.dat'
//// and echoes them to the display until a negative value
//// is read.
//    QFile file("dict.txt");
//    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    QTextStream in(&file);
//    QString line;
//    int count = 0;
//    while(true) {
//        line = in.readLine();
//        if(line.isNull()) break;
//        if((++count)%1000 == 0) {
//            qDebug() << line;
//        }
//        if(count >= 1000000) break;
//        e.add(line);
//    }
//    if (e.contains("AALIIS")) {
//        cout << "success with AALIIS" << endl;
//    }
//    if (e.containsPrefix("WESTL")) {
//        cout << "success with prefix WESTL" << endl;
//    }
//    if (!e.containsPrefix("WHP")) {
//        cout << "no WHP" << endl;
//    }
//    /*ifstream indata("dict.txt", ios::in); // indata is like cin
//    string num; // variable for input value
//    QString str;
//    //indata.open("en_US.txt"); // opens the file
//    if(!indata.good()) { // file couldn't be opened
//        cerr << "Error: file could not be opened" << endl;
//        exit(1);
//    }
//   // indata >> num;

//    indata >> str;
//    int count = 0;
//    while ( !indata.eof() ) { // keep reading until end-of-file
//        qDebug() << str;
//        indata >>str;
//        if (count++ > 10) break;
//        e.add(str);
//    }
//    indata.close();
//    cout << "End-of-file reached.." << endl;*/
//}
