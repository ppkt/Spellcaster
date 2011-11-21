#ifndef PARSER_H
#define PARSER_H
#include <QtCore>
#include <iostream>
#include "config.h"

using std::cout;
using std::endl;

class Parser {
public:
    Parser();
    void setFile(QString filename);
    bool parse(Config &c);

private:
    QString processLine(QString line, Config &c);
    QString filename;
};

#endif // PARSER_H
