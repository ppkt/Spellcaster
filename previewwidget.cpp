#include <algorithm>
#include <cmath>
#include <iostream>
#include <QPainter>
#include <QPicture>
#include <QVector3D>
#include "previewwidget.h"

using std::cout;
using std::endl;

PreviewWidget::PreviewWidget(QWidget *parent) :
    QWidget(parent) {
    this->parent = 0;
}

void PreviewWidget::setDataContainter(Spellcaster *parent) {
    this->parent = parent;
}

void PreviewWidget::paintEvent(QPaintEvent *) {
    if (!parent) {
        return;
    }

    //pobieramy skalê:
    QList<float> wsp1 = parent->wspolrzedneX1;
    QList<float> wsp2 = parent->wspolrzedneX2;
    QList<float> wsp3 = parent->wspolrzedneX3;

    if (wsp1.size() == 0 || wsp2.size() == 0 || wsp3.size() == 0) {
        return;
    }

    qSort(wsp1);
    qSort(wsp2);
    qSort(wsp3);

    float X1min = wsp1.first();
    float X1max = wsp1.last();

    float X2min = wsp2.first();
    float X2max = wsp2.last();

    float X3min = wsp3.first();
    float X3max = wsp3.last();

    cout << X1min << " " << X1max << endl;
    cout << X2min << " " << X2max << endl;
    cout << X3min << " " << X3max << endl;

    QList<QVector3D> x1Points;
    QList<QVector3D> x2Points;
    QList<QVector3D> x3Points;

    for (int i = 0; i < wsp1.size(); ++i) {
        x1Points.append(QVector3D(wsp1.at(i), X2min, X3min));
    }

    for (int i = 0; i < wsp2.size(); ++i) {
        x2Points.append(QVector3D(X1min, wsp2.at(i), X3min));
    }

    for (int i = 0; i < wsp3.size(); ++i) {
        x3Points.append(QVector3D(X1min, X2min,  wsp3.at(i)));
    }

    QPicture pic;
    QPainter paint(&pic);
    paint.setRenderHint(QPainter::Antialiasing);

    //rysujemy front:
    QVector3D p1 = x1Points.first();
    QVector3D p2 = x1Points.last();
    QVector3D p3 = x2Points.last();
    QVector3D p4 = p2 + QVector3D(0, (X2max - X2min), 0);

    paint.drawLine(iso(p1), iso(p2));
    paint.drawLine(iso(p1), iso(p3));
    paint.drawLine(iso(p2), iso(p4));
    paint.drawLine(iso(p3), iso(p4));

    QVector3D p5 = p4 + QVector3D(0, 0, -(X3max - X3min));
    QVector3D p6 = p2 + QVector3D(0, 0, -(X3max - X3min));
    QVector3D p7 = p1 + QVector3D(0, 0, -(X3max - X3min));

    paint.drawLine(iso(p4), iso(p5));
    paint.drawLine(iso(p5), iso(p6));
    paint.drawLine(iso(p2), iso(p6));
    paint.drawLine(iso(p1), iso(p7));
    paint.drawLine(iso(p6), iso(p7));

    //rysowanie siatki elementów
    for (int i = 1; i + 1< x1Points.size(); ++i) {
        QVector3D p1 = x1Points.at(i);
        QVector3D p2 = p1 + QVector3D(0, (X2max - X2min), 0);
        paint.drawLine(iso(p1), iso(p2));

        QVector3D p3 = p1 + QVector3D(0, 0, -(X3max - X3min));
        paint.drawLine(iso(p1), iso(p3));
    }

    for (int i = 1; i + 1< x2Points.size(); ++i) {
        QVector3D p1 = x2Points.at(i);
        QVector3D p2 = p1 + QVector3D((X1max - X1min), 0, 0);
        paint.drawLine(iso(p1), iso(p2));

        QVector3D p3 = p1 + QVector3D((X1max - X1min), 0, -(X3max - X3min));
        paint.drawLine(iso(p2), iso(p3));
    }

    for (int i = 1; i + 1< x3Points.size(); ++i) {
        QVector3D p1 = x3Points.at(i) + QVector3D(X1max - X1min, 0, -(X3max - X3min));

        QVector3D p2 = p1 - QVector3D((X1max - X1min), 0, 0);
        paint.drawLine(iso(p1), iso(p2));

        QVector3D p3 = p1 - QVector3D(0, -(X2max - X2min), 0);
        paint.drawLine(iso(p1), iso(p3));
    }

//    paint.drawLine(iso(x1Points.first()), iso(x1Points.last()));
//    paint.drawLine(iso(x2Points.first()), iso(x2Points.last()));
//    paint.drawLine(iso(x3Points.first()), iso(x3Points.last()));
//    for (int i = 0; i < x1Points.size(); ++i) {
//        paint.drawLine(iso(x1Points.at(i)));
//    }


    paint.end();


    paint.begin(this);
    paint.drawPicture(100, 100, pic);
    paint.end();
}

QPointF PreviewWidget::iso(QVector3D point) {
    double isoX = sqrt(3) * point.x() - sqrt(3) * point.z();
    double isoY = point.x() + 2 * point.y() + point.z();

    isoX *= 1.0 / sqrt(6);
    isoY *= 1.0 / sqrt(6);

    return QPointF(isoX, isoY);
}

