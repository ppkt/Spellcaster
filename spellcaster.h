#ifndef SPELLCASTER_H
#define SPELLCASTER_H

#include <qwt_legend.h>
#include <QMainWindow>
#include <QModelIndex>
#include "qtriple.h"

class PreviewWidget;

namespace Ui {
    class Spellcaster;
}

class Spellcaster : public QMainWindow {
    Q_OBJECT
friend class PreviewWidget;

public:
    explicit Spellcaster(QWidget *parent = 0);
    ~Spellcaster();

private slots:
//    void closeEvent(QCloseEvent *);
    void on_btnAddX1_clicked();
    void on_btnDeleteX1_clicked();
    void on_X1List_activated(const QModelIndex &index);
    void on_btnAddX2_clicked();
    void on_X2List_activated(const QModelIndex &index);
    void on_btnDeleteX2_clicked();
    void on_btnAddX3_clicked();
    void on_btnDeleteX3_clicked();
    void on_X3List_activated(const QModelIndex &index);
    void on_btnClearListX1_clicked();
    void on_btnClearListX2_clicked();
    void on_btnClearListX3_clicked();
    void on_btnGenerate_clicked();
    void on_btnBrowse_clicked();
    void on_btnAddOther_clicked();
    void on_btnClearListOther_clicked();
    void on_btnDeleteOther_clicked();
    void on_otherList_activated(const QModelIndex &index);

    void on_btnTempX1_clicked();

    void on_btnTempBottom_clicked();

    void on_btnTempUpper_clicked();

private:
    void ppktAddX1(float pos, float gestosc, float cieploWlasciwe, float przewodnoscCieplna);
    void ppktAddX2(float pos, bool mostek = false, float gestosc = 0.0, float cieploWlasciwe = 0.0,
                   float przewodnoscCieplna = 0.0);
    void ppktAddX3(float pos);
    void ppktAddOther(float time, float wspolczynnikWymianyCieplaNadPlyta, float temperaturaNadPlyta,
                      float temperaturaPodPlyta, float gestoscStrumieniaCieplaPodPlyta,
                      float wspolczynnikWymianyCieplaPodPlyta);
    void drawMarkers();
    Ui::Spellcaster *ui;
    QList<float> wspolrzedneX1;
    QList<float> wspolrzedneX2;
    QList<float> wspolrzedneX3;
    QList<QTripleFloat > wlasciwosciX1;
    QList<QTripleFloat> wlasciwosciX2;
    QList<bool> mostek;
    QList<QList<double> > other;
    QList<double> otherTime;
    QwtLegend *legend;
};

#endif // SPELLCASTER_H
