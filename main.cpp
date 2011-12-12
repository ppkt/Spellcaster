#include <QtGui/QApplication>
#include "spellcaster.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Spellcaster w;

    w.show();

    return a.exec();
}
