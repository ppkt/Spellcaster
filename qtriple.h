#ifndef QTRIPLE_H
#define QTRIPLE_H
#include <QMetaType>

template <typename X, typename Y, typename Z>
class QTriple {
public:
    QTriple() {}
    X first;
    Y second;
    Z third;
};

class QTripleFloat : public QTriple<float, float, float> {
public:
    QTripleFloat(QTriple<float, float, float> t) {
        this->first = t.first;
        this->second = t.second;
        this->third = t.third;
    }
    QTripleFloat() {}
};

Q_DECLARE_METATYPE(QTripleFloat)
Q_DECLARE_METATYPE(QList<QTripleFloat>)
Q_DECLARE_METATYPE(QList<float>)

#endif // QTRIPLE_H
