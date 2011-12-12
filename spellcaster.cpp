#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "config.h"
#include "parser.h"
#include "qtriple.h"
#include "spellcaster.h"
#include "ui_spellcaster.h"

Spellcaster::Spellcaster(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Spellcaster) {
    ui->setupUi(this);

    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup("X1");
    QList<QVariant> X1wspolrzedneTmp = settings.value("wspolrzedne").toList();
    QList<QVariant> X1wartosciTmp = settings.value("wlasciwosci").toList();
    settings.endGroup();

    for (int i = 0; i < X1wspolrzedneTmp.size(); ++i) {\
        float wspolrzedne = X1wspolrzedneTmp.at(i).toFloat();
        QTriple<float, float, float> a = X1wartosciTmp.at(i).value<QTripleFloat>();
        float gestosc = a.first;
        float cieploWlasciwe = a.second;
        float przewodnoscCieplna = a.third;
        this->ppktAddX1(wspolrzedne, gestosc, cieploWlasciwe, przewodnoscCieplna);
    }

    this->ppktAddX1(0.0, 1900, 840, 1.04);
    this->ppktAddX1(1.0, 1900, 840, 1.04);
    this->ppktAddX1(5.0, 1900, 840, 1.04);
    this->ppktAddX1(10.0, 1900, 840, 1.04);
    this->ppktAddX1(15.0, 1900, 840, 1.04);
    this->ppktAddX1(20.0, 1900, 840, 1.04);

    this->ppktAddX1(25.0, 1800, 920, 0.75);
    this->ppktAddX1(40.0, 1800, 920, 0.75);
    this->ppktAddX1(70.0, 1800, 920, 0.75);
    this->ppktAddX1(120.0, 1800, 920, 0.75);
    this->ppktAddX1(170.0, 1800, 920, 0.75);
    this->ppktAddX1(220.0, 1800, 920, 0.75);
    this->ppktAddX1(270.0, 1800, 920, 0.75);
    this->ppktAddX1(295.0, 1800, 920, 0.75);
    this->ppktAddX1(315.0, 1800, 920, 0.75);
    this->ppktAddX1(320.0, 1800, 920, 0.75);

    this->ppktAddX1(325.0, 20, 1460, 0.042);
    this->ppktAddX1(345.0, 20, 1460, 0.042);
    this->ppktAddX1(370.0, 20, 1460, 0.042);
    this->ppktAddX1(420.0, 20, 1460, 0.042);
    this->ppktAddX1(445.0, 20, 1460, 0.042);
    this->ppktAddX1(465.0, 20, 1460, 0.042);
    this->ppktAddX1(470.0, 20, 1460, 0.042);

    this->ppktAddX1(475.0, 40, 750, 0.045);
    this->ppktAddX1(495.0, 40, 750, 0.045);
    this->ppktAddX1(515.0, 40, 750, 0.045);
    this->ppktAddX1(520.0, 40, 750, 0.045);

    this->ppktAddX1(525.0, 1400, 840, 0.64);
    this->ppktAddX1(545.0, 1400, 840, 0.64);
    this->ppktAddX1(570.0, 1400, 840, 0.64);
    this->ppktAddX1(595.0, 1400, 840, 0.64);
    this->ppktAddX1(615.0, 1400, 840, 0.64);
    this->ppktAddX1(619.0, 1400, 840, 0.64);
    this->ppktAddX1(620.0, 1400, 840, 0.64);

    /*
    this->ppktAddX2(0);
    this->ppktAddX2(10);
    this->ppktAddX2(30);
    this->ppktAddX2(50);
    this->ppktAddX2(100);
    this->ppktAddX2(150);
    this->ppktAddX2(170);
    this->ppktAddX2(190);
    this->ppktAddX2(200);

    this->ppktAddX3(0);
    this->ppktAddX3(66);
    this->ppktAddX3(133);
    this->ppktAddX3(200);
    */

    this->ppktAddX2(0);
    this->ppktAddX2(20);
    this->ppktAddX2(60);
    this->ppktAddX2(100);
    this->ppktAddX2(200);
    this->ppktAddX2(300);
    this->ppktAddX2(340);
    this->ppktAddX2(380);
    this->ppktAddX2(400);

    this->ppktAddX3(0);
    this->ppktAddX3(133);
    this->ppktAddX3(266);
    this->ppktAddX3(400);


    this->ppktAddOther(0,   10, -10,  30, 0, 30);
    this->ppktAddOther(60,  10, -10,  30, 0, 30);
    this->ppktAddOther(120, 100,-30,  30, 0, 30);
    this->ppktAddOther(180, 100,-30,  30, 0, 30);
    this->ppktAddOther(240, 10, -10,  30, 0, 30);
    this->ppktAddOther(300, 10, -10,  30, 0, 30);

    ui->preview->setDataContainter(this);

    ui->qwtPlot->setAxisTitle(0, "Temperatura [C]");
    ui->qwtPlot->setAxisTitle(2, "Odleglosc [mm]");
    this->legend = new QwtLegend();
    ui->qwtPlot->insertLegend(legend);
}

Spellcaster::~Spellcaster() {

    delete ui;
}

void Spellcaster::on_btnAddX1_clicked() {
    float wspolrzedne = ui->X1wspolrzedne->value();
    float gestosc = ui->X1gestosc->value();
    float cieploWlasciwe = ui->X1cieploWlasciwe->value();
    float przewodnoscCieplna = ui->X1przewodnoscCieplna->value();

    QTriple<float, float, float> wlasciwosci;
    wlasciwosci.first = przewodnoscCieplna;
    wlasciwosci.second = cieploWlasciwe;
    wlasciwosci.third = gestosc;
    QString label = QString("%1 (%2, %3, %4)")
            .arg(wspolrzedne)
            .arg(przewodnoscCieplna)
            .arg(cieploWlasciwe)
            .arg(gestosc);

    if (!wspolrzedneX1.contains(wspolrzedne)) {
        int index;
        for (index = 0; index < this->wspolrzedneX1.size(); ++index) {
            double currentPosition = this->wspolrzedneX1.at(index);
            if (wspolrzedne > currentPosition) {
                continue;
            } else {
                break;
            }
        }

        ui->X1List->insertItem(index, label);
        this->wspolrzedneX1.insert(index, wspolrzedne);
        this->wlasciwosciX1.insert(index, wlasciwosci);
        ui->X1wspolrzedne->setValue(wspolrzedne + ui->X1increment->value());
    } else {
        QModelIndex index = ui->X1List->currentIndex();
        QListWidgetItem *item = ui->X1List->currentItem();
        if (item == NULL) {
            return;
        }
        item->setData(Qt::DisplayRole, label);

        this->wlasciwosciX1[index.row()] = wlasciwosci;
        this->wspolrzedneX1[index.row()] = wspolrzedne;
    }
}

void Spellcaster::on_btnDeleteX1_clicked() {
    QModelIndex index = ui->X1List->currentIndex();
    QListWidgetItem* item = ui->X1List->takeItem(index.row());
    delete item;

    this->wlasciwosciX1.removeAt(index.row());
    this->wspolrzedneX1.removeAt(index.row());
}

void Spellcaster::on_X1List_activated(const QModelIndex &index) {
    int row = index.row();
    QTriple <float, float, float> temp = this->wlasciwosciX1.at(row);

    float wspolrzedne = this->wspolrzedneX1.at(row);
    float przewodnoscCieplna = temp.first;
    float cieploWlasciwe = temp.second;
    float gestosc = temp.third;
    this->ui->X1wspolrzedne->setValue(wspolrzedne);
    this->ui->X1gestosc->setValue(gestosc);
    this->ui->X1cieploWlasciwe->setValue(cieploWlasciwe);
    this->ui->X1przewodnoscCieplna->setValue(przewodnoscCieplna);
}

void Spellcaster::on_btnAddX2_clicked() {
    float wspolrzedne = ui->X2wspolrzedne->value();
    bool mostek = ui->X2mostek->isChecked();
    float gestosc = ui->X2gestosc->value();
    float cieploWlasciwe = ui->X2cieploWlasciwe->value();
    float przewodnoscCieplna = ui->X2przewodnoscCieplna->value();

    QTriple<float, float, float> wlasciwosci;
    wlasciwosci.first = przewodnoscCieplna;
    wlasciwosci.second = cieploWlasciwe;
    wlasciwosci.third = gestosc;
    QString label;
    if (mostek) {
        label = QString("%1 (%2, %3, %4)")
                    .arg(wspolrzedne)
                    .arg(przewodnoscCieplna)
                    .arg(cieploWlasciwe)
                    .arg(gestosc);
    } else {
        label = QString("%1")
                    .arg(wspolrzedne);
    }

    if (!wspolrzedneX2.contains(wspolrzedne)) {
        int index;
        for (index = 0; index < this->wspolrzedneX2.size(); ++index) {
            double currentPosition = this->wspolrzedneX2.at(index);
            if (wspolrzedne > currentPosition) {
                continue;
            } else {
                break;
            }
        }

        ui->X2List->insertItem(index, label);
        this->wspolrzedneX2.insert(index, wspolrzedne);
        this->wlasciwosciX2.insert(index, wlasciwosci);
        this->mostek.insert(index, mostek);
        ui->X2wspolrzedne->setValue(wspolrzedne + ui->X2increment->value());
    } else {
        QModelIndex index = ui->X2List->currentIndex();
        QListWidgetItem *item = ui->X2List->currentItem();
        if (item == NULL) {
            return;
        }
        item->setData(Qt::DisplayRole, label);

        this->wlasciwosciX2[index.row()] = wlasciwosci;
        this->wspolrzedneX2[index.row()] = wspolrzedne;
        this->mostek[index.row()] = mostek;
    }

}

void Spellcaster::on_btnDeleteX2_clicked() {
    QModelIndex index = ui->X2List->currentIndex();
    QListWidgetItem* item = ui->X2List->takeItem(index.row());
    delete item;

    this->wlasciwosciX2.removeAt(index.row());
    this->wspolrzedneX2.removeAt(index.row());
    this->mostek.removeAt(index.row());
}

void Spellcaster::on_X2List_activated(const QModelIndex &index) {
    int row = index.row();
    QTriple <float, float, float> temp = this->wlasciwosciX2.at(row);

    float wspolrzedne = this->wspolrzedneX2.at(row);
    float gestosc = temp.first;
    float cieploWlasciwe = temp.second;
    float przewodnoscCieplna = temp.third;
    bool mostek = this->wspolrzedneX2.at(row);

    this->ui->X2wspolrzedne->setValue(wspolrzedne);
    this->ui->X2gestosc->setValue(gestosc);
    this->ui->X2cieploWlasciwe->setValue(cieploWlasciwe);
    this->ui->X2przewodnoscCieplna->setValue(przewodnoscCieplna);
    this->ui->X2mostek->setChecked(mostek);
}

void Spellcaster::on_btnAddX3_clicked() {
    float wspolrzedne = ui->X3wspolrzedne->value();


    QString label = QString("%1")
            .arg(wspolrzedne);

    if (!wspolrzedneX3.contains(wspolrzedne)) {
        int index;
        for (index = 0; index < this->wspolrzedneX3.size(); ++index) {
            double currentPosition = this->wspolrzedneX3.at(index);
            if (wspolrzedne > currentPosition) {
                continue;
            } else {
                break;
            }
        }

        ui->X3List->insertItem(index, label);
        this->wspolrzedneX3.insert(index, wspolrzedne);
        ui->X3wspolrzedne->setValue(wspolrzedne + ui->X3increment->value());
    } else {
        QModelIndex index = ui->X3List->currentIndex();
        QListWidgetItem *item = ui->X3List->currentItem();
        if (item == NULL) {
            return;
        }
        item->setData(Qt::DisplayRole, label);

        this->wspolrzedneX3[index.row()] = wspolrzedne;
    }
}

void Spellcaster::on_btnDeleteX3_clicked() {
    QModelIndex index = ui->X3List->currentIndex();
    QListWidgetItem* item = ui->X3List->takeItem(index.row());
    delete item;

    this->wspolrzedneX3.removeAt(index.row());
}

void Spellcaster::on_X3List_activated(const QModelIndex &index) {
    int row = index.row();

    float wspolrzedne = this->wspolrzedneX3.at(row);

    this->ui->X3wspolrzedne->setValue(wspolrzedne);
}


void Spellcaster::on_btnAddOther_clicked() {
    double wspolczynnikWymianyCieplaNadPlyta = ui->otherWspWymCNad->value();
    double temperaturaNadPlyta = ui->otherTempNad->value();
    double temperaturaPodPlyta = ui->otherTempPod->value();
    double gestoscstrumieniaCieplaPodPlyta = ui->otherGestStrCPod->value();
    double wspolczynnikWymianyCieplaPodPlyta = ui->otherWspWymCPod->value();
    double czas = ui->otherCzas->value();
    QList<double> row;
    row.append(wspolczynnikWymianyCieplaNadPlyta);
    row.append(temperaturaNadPlyta);
    row.append(temperaturaPodPlyta);
    row.append(gestoscstrumieniaCieplaPodPlyta);
    row.append(wspolczynnikWymianyCieplaPodPlyta);

    QString label = QString("T: %1 (%2, %3, %4, %5, %6)")
            .arg(czas)
            .arg(row[0])
            .arg(row[1])
            .arg(row[2])
            .arg(row[3])
            .arg(row[4]);

    if (!this->otherTime.contains(czas)) {
        this->other.append(row);
        this->otherTime.append(czas);
        int index;
        for (index = 0; index < this->otherTime.size(); ++index) {
            double currentTime = this->otherTime.at(index);
            if (czas > currentTime) {
                continue;
            } else {
                break;
            }
        }
        ui->otherList->insertItem(index, label);

    } else {
        QModelIndex index = ui->otherList->currentIndex();
        QListWidgetItem *item = ui->otherList->currentItem();
        if (item == NULL) {
            return;
        }
        item->setData(Qt::DisplayRole, label);

        this->other[index.row()] = row;
    }
}

void Spellcaster::on_btnDeleteOther_clicked() {
    QModelIndex index = ui->otherList->currentIndex();
    QListWidgetItem* item = ui->otherList->takeItem(index.row());
    delete item;

    this->other.removeAt(index.row());
}

void Spellcaster::on_otherList_activated(const QModelIndex &index) {
    int row = index.row();
    QList<double> temp = this->other.at(row);

    ui->otherWspWymCNad->setValue(temp[0]);
    ui->otherTempNad->setValue(temp[1]);
    ui->otherTempPod->setValue(temp[2]);
    ui->otherGestStrCPod->setValue(temp[3]);
    ui->otherWspWymCPod->setValue(temp[4]);
    ui->otherCzas->setValue(this->otherTime.at(row));
}


void Spellcaster::on_btnClearListX1_clicked(){
    this->ui->X1List->clear();
    this->wlasciwosciX1.clear();
    this->wspolrzedneX1.clear();
}

void Spellcaster::on_btnClearListX2_clicked() {
    this->ui->X2List->clear();
    this->wspolrzedneX2.clear();
    this->wlasciwosciX2.clear();
    this->mostek.clear();
}

void Spellcaster::on_btnClearListX3_clicked() {
    this->ui->X3List->clear();
    this->wspolrzedneX3.clear();
}

void Spellcaster::on_btnClearListOther_clicked() {
    ui->otherList->clear();
    this->other.clear();
}

void Spellcaster::ppktAddX1(float pos, float gestosc, float cieploWlasciwe, float przewodnoscCieplna) {
    ui->X1wspolrzedne->setValue(pos);
    ui->X1gestosc->setValue(gestosc);
    ui->X1cieploWlasciwe->setValue(cieploWlasciwe);
    ui->X1przewodnoscCieplna->setValue(przewodnoscCieplna);

    ui->btnAddX1->click();
}

void Spellcaster::ppktAddX2(float pos, bool mostek, float gestosc, float cieploWlasciwe, float przewodnoscCieplna) {
    ui->X2wspolrzedne->setValue(pos);
    ui->X2mostek->setChecked(mostek);
    if (mostek) {
        ui->X2gestosc->setValue(gestosc);
        ui->X2cieploWlasciwe->setValue(cieploWlasciwe);
        ui->X2przewodnoscCieplna->setValue(przewodnoscCieplna);
    }

    ui->btnAddX2->click();
}

void Spellcaster::ppktAddX3(float pos) {
    ui->X3wspolrzedne->setValue(pos);

    ui->btnAddX3->click();
}

void Spellcaster::ppktAddOther(float time, float wspolczynnikWymianyCieplaNadPlyta,
                               float temperaturaNadPlyta, float temperaturaPodPlyta,
                               float gestoscStrumieniaCieplaPodPlyta,
                               float wspolczynnikWymianyCieplaPodPlyta) {
    ui->otherCzas->setValue(time);
    ui->otherWspWymCNad->setValue(wspolczynnikWymianyCieplaNadPlyta);
    ui->otherWspWymCPod->setValue(wspolczynnikWymianyCieplaPodPlyta);
    ui->otherTempNad->setValue(temperaturaNadPlyta);
    ui->otherTempPod->setValue(temperaturaPodPlyta);
    ui->otherGestStrCPod->setValue(gestoscStrumieniaCieplaPodPlyta);

    ui->btnAddOther->click();
}

void Spellcaster::on_btnGenerate_clicked() {
    Parser p;
    p.setFile("template.txt");

    Config c;
    c.setEps(ui->doubleEPS->value() * 1.0e-04);
    c.setFlimit(ui->doubleFLIMIT->value());
    c.setNtpr1(ui->doubleNTPR1->value());
    c.setNtpr2(ui->doubleNTPR2->value());
    c.setNtprE(ui->doubleNTPRE->value() * 60);
    c.setTamb(ui->doubleTAMB->value());
    c.setDtime(ui->doubleDTIME->value());
    c.setDtmin(ui->doubleDTMIN->value());
    c.setTinit(ui->doubleTINIT->value());
    c.setQprzem(ui->doubleQPRZEM->value());
    c.setRalfb1(ui->doubleRALFB1->value());
    c.setRalfb5(ui->doubleRALFB5->value());
    c.setT2sle(ui->doubleT2SLE->value() * 60);
    c.setCepwel(ui->doubleCEPWEL->value());
    c.setGeswel(ui->doubleGESWEL->value());
    c.setWlawel(ui->doubleWLAWEL->value());
    c.setNstpp(ui->doubleNSTPP->value());

    for (int i = 0; i < this->wspolrzedneX1.size(); ++i) {
        QTriple<float, float, float> values = wlasciwosciX1.at(i);
        c.addElementX1(wspolrzedneX1.at(i), values.first, values.second, values.third);
    }

    for (int j = 0; j < this->wspolrzedneX2.size(); ++j) {
        QTriple<float, float, float> values = wlasciwosciX2.at(j);
        bool mostek = this->mostek.at(j);
        c.addElementX2(wspolrzedneX2.at(j), mostek, values.first, values.second, values.third);
    }

    for (int k = 0; k < this->wspolrzedneX3.size(); ++k) {
        c.addElementX3(wspolrzedneX3.at(k));
    }

    for (int t = 0; t < this->otherTime.size(); ++t) {
        double time = this->otherTime.at(t);
        QList<double> row = this->other.at(t);

        c.addWspWymianyCieplaNadPlyta(time, row[0]);
        c.addTempNadPodPlyta(row[1], row[2]);
        c.addGestoscStrumieniaCieplaPodPlyta(row[3]);
        c.addWspWymianyCieplaPodPlyta(row[4]);
    }

//    c.addGestoscStrumieniaCieplaPodPlyta(0);
//    c.addGestoscStrumieniaCieplaPodPlyta(0);
//    c.addWspWymianyCieplaPodPlyta(20);
//    c.addWspWymianyCieplaPodPlyta(20);

//    c.addTempNadPodPlyta(20, 30);
//    c.addTempNadPodPlyta(20, 30);

//    c.addWspWymianyCieplaNadPlyta(0, 25);
//    c.addWspWymianyCieplaNadPlyta(10, 25);
//    c.addGestoscStrumieniaCieplaPodPlyta(0);
//    c.addGestoscStrumieniaCieplaPodPlyta(0);
//    c.addWspWymianyCieplaPodPlyta(0);
//    c.addWspWymianyCieplaPodPlyta(0);
//    c.addTempNadPodPlyta(20, 0);
//    c.addTempNadPodPlyta(20, 0);

    if (p.parse(c)) {
        QMessageBox::information(this, "good job",
                                 "plik wygenerowany");
    } else {
        QMessageBox::critical(this, "you fail", "but thanks for trying");
    }

}

void Spellcaster::on_btnBrowse_clicked() {
    QString path;
#ifdef WINDOWS
    path = QFileDialog::getExistingDirectory(this, trUtf8("Wybierz katalog z plikami dat"),
                                                    "D:\\AGH\\9 sem\\SIWE\\progs-spr1\\SIWE\\plyta_3d");
#endif
#ifdef unix
    path = QFileDialog::getExistingDirectory(this, trUtf8("Wybierz katalog z plikami dat"),
                                             "/media/Win1/AGH/9 sem/SIWE/progs-spr1/SIWE/plyta_3d");
#endif

    if (path.isEmpty()) {
        return;
    }

    ui->linePath->setText(path);
}

//void Spellcaster::closeEvent(QCloseEvent *) {
//    QSettings settings("settings.ini", QSettings::IniFormat);
//    QVariant tmp;
//    qVariantSetValue(tmp, this->wspolrzedneX1);
//    settings.beginGroup("X1");
////    tmp.setValue(this->wspolrzedneX1);
//    if (tmp.canConvert<QList<float> >()) {
//        settings.setValue("wspolrzedne", QVariant::fromValue(this->wspolrzedneX1));
//    }
//    if (tmp.canConvert<QList<QTripleFloat> >()) {
//        settings.setValue("wlasciwosci", QVariant::fromValue(this->wlasciwosciX1));
//    }
////    tmp.setValue(this->wlasciwosciX1);
////    settings.setValue("wlasciwosci", this->wlasciwosciX1);
//    settings.endGroup();
//}

void Spellcaster::on_btnTempX1_clicked() {
    ui->qwtPlot->detachItems();
    int start, step, end;
    start = ui->doubleNTPR1->value() + 1;
    step = ui->doubleNTPR2->value();
    end = ui->doubleNTPRE->value() + 1;

    QString line;
    QStringList list;

    for (int i = start; i <= end; i += step) {

        QString filename = QString("/tem%1.dat")
                .arg(i, 3, 10, QChar('0'));
        QFile file(ui->linePath->text() + filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            cout << "Nie mo¿na otworzyæ pliku!" << endl;
            return;
        }

        QVector<double> x;
        QVector<double> y;

        foreach (float pos, this->wspolrzedneX1) {
            x.append(pos);
        }

        QTextStream in(&file);
        for (int j = 0; j < this->wspolrzedneX1.size() * 13; ++j) {
            in.readLine();
        }
        for (int j = 0; j < this->wspolrzedneX1.size(); ++j) {
            //float pos = this->wspolrzedneX1.at(j);
            line = in.readLine();
            list = line.split(QRegExp("\\s+"));

            float temp = list.at(4).toFloat();

            y.append(temp);
        }
        QwtPlotCurve *curve = new QwtPlotCurve(QString("Czas: %1").arg(i));
        double val = (i / (end * 1.0)) * 255;
        curve->setPen(QPen(QBrush(QColor(val, 255-val, 64)), 3));
        curve->attach(ui->qwtPlot);
        curve->setRenderHint(QwtPlotCurve::RenderAntialiased);
        curve->setSamples(x, y);
    }

    drawMarkers();

    ui->qwtPlot->replot();
}

void Spellcaster::on_btnTempBottom_clicked() {
    ui->qwtPlot->detachItems();
    int start, step, end;
    start = ui->doubleNTPR1->value() + 1;
    step = ui->doubleNTPR2->value();
    end = ui->doubleNTPRE->value() + 1;

    QString line;
    QStringList list;

    for (int i = start; i <= end; i += step) {

        QString filename = QString("/tld12%1.dat")
                .arg(i, 3, 10, QChar('0'));
        QFile file(ui->linePath->text() + filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            cout << "Nie mo¿na otworzyæ pliku!" << endl;
            return;
        }

        QVector<double> x;
        QVector<double> y;

        foreach (float pos, this->wspolrzedneX2) {
            x.append(pos);
        }

        QTextStream in(&file);
        for (int j = 0; j < this->wspolrzedneX2.size(); ++j) {
            line = in.readLine();
            list = line.split(QRegExp("\\s+"));

            float temp = list.at(2).toFloat();

            y.append(temp);
        }
        QwtPlotCurve *curve = new QwtPlotCurve(QString("Czas: %1").arg(i));
        double val = (i / (end * 1.0)) * 255;
        curve->setPen(QPen(QBrush(QColor(val, 255-val, 64)), 3));
        curve->attach(ui->qwtPlot);
        curve->setRenderHint(QwtPlotCurve::RenderAntialiased);
        curve->setSamples(x, y);
    }

    ui->qwtPlot->replot();
}

void Spellcaster::drawMarkers() {
    QwtPlotMarker* marker = new QwtPlotMarker();
    marker->setValue(20, 0);
    marker->setLineStyle(QwtPlotMarker::VLine);
    marker->attach(ui->qwtPlot);

    marker = new QwtPlotMarker();
    marker->setValue(320, 0);
    marker->setLineStyle(QwtPlotMarker::VLine);
    marker->attach(ui->qwtPlot);

    marker = new QwtPlotMarker();
    marker->setValue(470, 0);
    marker->setLineStyle(QwtPlotMarker::VLine);
    marker->attach(ui->qwtPlot);

    marker = new QwtPlotMarker();
    marker->setValue(520, 0);
    marker->setLineStyle(QwtPlotMarker::VLine);
    marker->attach(ui->qwtPlot);

    marker = new QwtPlotMarker();
    marker->setValue(620, 0);
    marker->setLineStyle(QwtPlotMarker::VLine);
    marker->attach(ui->qwtPlot);
}

void Spellcaster::on_btnTempUpper_clicked() {
    ui->qwtPlot->detachItems();
    int start, step, end;
    start = ui->doubleNTPR1->value() + 1;
    step = ui->doubleNTPR2->value();
    end = ui->doubleNTPRE->value() + 1;

    QString line;
    QStringList list;

    for (int i = start; i <= end; i += step) {

        QString filename = QString("/tlg12%1.dat")
                .arg(i, 3, 10, QChar('0'));
        QFile file(ui->linePath->text() + filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            cout << "Nie mo¿na otworzyæ pliku!" << endl;
            return;
        }

        QVector<double> x;
        QVector<double> y;

        foreach (float pos, this->wspolrzedneX2) {
            x.append(pos);
        }

        QTextStream in(&file);
        for (int j = 0; j < this->wspolrzedneX2.size(); ++j) {
            //float pos = this->wspolrzedneX1.at(j);
            line = in.readLine();
            list = line.split(QRegExp("\\s+"));

            float temp = list.at(2).toFloat();

            y.append(temp);
        }
        QwtPlotCurve *curve = new QwtPlotCurve(QString("Czas: %1").arg(i));
        double val = (i / (end * 1.0)) * 255;
        curve->setPen(QPen(QBrush(QColor(val, 255-val, 64)), 3));
        curve->attach(ui->qwtPlot);
        curve->setRenderHint(QwtPlotCurve::RenderAntialiased);
        curve->setSamples(x, y);
    }

    ui->qwtPlot->replot();
}
