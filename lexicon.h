#ifndef LEXICON_H
#define LEXICON_H

#include <QString>

class Lexicon
{
public:
    Lexicon() { root = NULL; }
    //Lexicon(QString filename);
    ~Lexicon() { delete root; }

    void add(const QString& word);
    bool contains(const QString& word) const;
    bool containsPrefix(const QString& prefix) const;
    void addFromFile(const QString& fileneame);

private:
    struct node *root;
    const struct node *findNode(const QString& str) const;
    struct node *ensureNodeExists(const QString& str);
};

//void addFromFile(const QString &filename, Lexicon &e);
#endif // LEXICON_H
