#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>
#include "spellcaster.h"

class PreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewWidget(QWidget *parent = 0);
    void setDataContainter(Spellcaster *parent);

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    Spellcaster *parent;
    QPointF iso(QVector3D point);
};

#endif // PREVIEWWIDGET_H
