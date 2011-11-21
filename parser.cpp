#include "parser.h"

Parser::Parser() {
}

void Parser::setFile(QString filename) {
    this->filename = filename;
}

bool Parser::parse(Config &c) {
    QFile file(this->filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream is(&file);
    QString line;

    QFile save("plyta_3d.inp");
    if (!save.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream os(&save);

    while (!is.atEnd()) {
        line = is.readLine();
        line = processLine(line, c);
//        cout << line.toStdString() << endl;
        os << line << endl;
    }
    file.close();
    save.close();
    return true;
}

QString Parser::processLine(QString line, Config &c) {
    int align = -8;
    int precision = 3;

    if (line.contains("{$EPS}")) {
        line.replace("{$EPS}", QString("%1").arg(c.getEps(), align, 'e', precision));
    } else if (line.contains("{$FLIMIT}")) {
        line.replace("{$FLIMIT}", QString("%1").arg(c.getFlimit(), align, 'f', precision));
    } else if (line.contains("{$NTPR1}")) {
        line.replace("{$NTPR1}", QString("%1").arg(c.getNtpr1(), align));
    } else if (line.contains("{$NTPR2}")) {
        line.replace("{$NTPR2}", QString("%1").arg(c.getNtpr2(), align));
    } else if (line.contains("{$NTPRE}")) {
        line.replace("{$NTPRE}", QString("%1").arg(c.getNtpre(), align));
    } else if (line.contains("{$TAMB}")) {
        line.replace("{$TAMB}", QString("%1").arg(c.getTamb(), align, 'f', precision));
    } else if (line.contains("{$DTIME}")) {
        line.replace("{$DTIME}", QString("%1").arg(c.getDtime(), align, 'f', precision));
    } else if (line.contains("{$DTMIN}")) {
        line.replace("{$DTMIN}", QString("%1").arg(c.getDtmin(), align, 'f', precision));
    } else if (line.contains("{$TINIT}")) {
        line.replace("{$TINIT}", QString("%1").arg(c.getTinit(), align, 'f', precision));
    } else if (line.contains("{$QPRZEM}")) {
        line.replace("{$QPRZEM}", QString("%1").arg(c.getQprzem(), align, 'e', precision));
    } else if (line.contains("{$RALFB1}")) {
        line.replace("{$RALFB1}", QString("%1").arg(c.getRalfb1(), align, 'f', precision));
    } else if (line.contains("{$RALFB5}")) {
        line.replace("{$RALFB5}", QString("%1").arg(c.getRalfb5(), align, 'f', precision));
    } else if (line.contains("{$T2SLE}")) {
        line.replace("{$T2SLE}", QString("%1").arg(c.getT2sle(), align, 'f', precision));
    } else if (line.contains("{$CEPWEL}")) {
        line.replace("{$CEPWEL}", QString("%1").arg(c.getCepwel(), align, 'f', precision));
    } else if (line.contains("{$GESWEL}")) {
        line.replace("{$GESWEL}", QString("%1").arg(c.getGeswel(), align, 'f', precision));
    } else if (line.contains("{$WLAWEL}")) {
        line.replace("{$WLAWEL}", QString("%1").arg(c.getWlawel(), align, 'f', precision));
    } else if (line.contains("{$NSTPP}")) {
        line.replace("{$NSTPP}", QString("%1").arg(c.getNstpp(), align));
    } else if (line.contains("{$NX1}")) {
        line.replace("{$NX1}", QString("%1").arg(c.getNx1(), align));
    } else if (line.contains("{$NX2}")) {
        line.replace("{$NX2}", QString("%1").arg(c.getNx2(), align));
    } else if (line.contains("{$NX3}")) {
        line.replace("{$NX3}", QString("%1").arg(c.getNx3(), align));
    } else if (line.contains("{$DNP2}")) {
        line.replace("{$DNP2}", QString("%1").arg(c.getDnp2(), align));
    } else if (line.contains("{$X1NODES}")) {
        QString nodes;
        int size = c.getX1Nodes().size();
        for (int i = 0; i < size; ++i) {
            float pos = c.getX1Nodes().at(i);
            if (i + 1 == size) {
                nodes += QString("%1").arg(pos, 0, 'f', precision);
            } else {
                nodes += QString("%1 ").arg(pos, 0, 'f', precision);
            }
        }

        line.replace("{$X1NODES}", QString("%1\t").arg(nodes));
    } else if (line.contains("{$X2NODES}")) {
        QString nodes;
        int size = c.getX2Nodes().size();
        for (int i = 0; i < size; ++i) {
            float pos = c.getX2Nodes().at(i);
            if (i + 1 == size) {
                nodes += QString("%1").arg(pos, 0, 'f', precision);
            } else {
                nodes += QString("%1 ").arg(pos, 0, 'f', precision);
            }
        }

        line.replace("{$X2NODES}", QString("%1\t").arg(nodes));
    } else if (line.contains("{$X3NODES}")) {
        QString nodes;
        int size = c.getX3Nodes().size();
        for (int i = 0; i < size; ++i) {
            float pos = c.getX3Nodes().at(i);
            if (i + 1 == size) {
                nodes += QString("%1").arg(pos, 0, 'f', precision);
            } else {
                nodes += QString("%1 ").arg(pos, 0, 'f', precision);
            }
        }

        line.replace("{$X3NODES}", QString("%1").arg(nodes));
    } else if (line.contains("{$XNAD}") || line.contains("{$YNAD}")) {
        QString x;
        QString y;
        int size = c.getWspWymianyCieplaNadPlyta().size();
        for (int i = 0; i < size; ++i) {
            QPair<float, float> pos = c.getWspWymianyCieplaNadPlyta().at(i);
            if (i + 1 == size) {
                x += QString("%1").arg(pos.first, 0, 'f', precision);
                y += QString("%1").arg(pos.second, 0, 'f', precision);
            } else {
                x += QString("%1 ").arg(pos.first, 0, 'f', precision);
                y += QString("%1 ").arg(pos.second, 0, 'f', precision);
            }
        }

        line.replace("{$XNAD}", QString("%1").arg(x));
        line.replace("{$YNAD}", QString("%1").arg(y));
    } else if (line.contains("{$WSPWYMC}") || line.contains("{$GESSTRC}")) {
        QString wspolczynnikWymianyCiepla;
        QString gestoscStrumieniaCiepla;
        int size = c.getWspWymianyCieplaNadPlyta().size();
        for (int i = 0; i < size; ++i) {
            float wspWymC = c.getWspWymianyCieplaPodPlyta().at(i);
            float gesStrC = c.getGestoscStrumieniaCieplaPodPlyta().at(i);
            if (i + 1 == size) {
                wspolczynnikWymianyCiepla += QString("%1").arg(wspWymC, 0, 'f', precision);
                gestoscStrumieniaCiepla += QString("%1").arg(gesStrC, 0, 'f', precision);
            } else {
                wspolczynnikWymianyCiepla += QString("%1 ").arg(wspWymC, 0, 'f', precision);
                gestoscStrumieniaCiepla += QString("%1 ").arg(gesStrC, 0, 'f', precision);
            }
        }

        line.replace("{$WSPWYMC}", QString("%1").arg(wspolczynnikWymianyCiepla));
        line.replace("{$GESSTRC}", QString("%1").arg(gestoscStrumieniaCiepla));
    } else if (line.contains("{$TEMPNAD}") || line.contains("{$TEMPPOD}")) {
        QString temperaturaNadPlyta;
        QString temperaturaPodPlyta;
        int size = c.getWspWymianyCieplaNadPlyta().size();
        for (int i = 0; i < size; ++i) {
            QPair<float, float> temp = c.getTempPodNadPlyta().at(i);
            if (i + 1 == size) {
                temperaturaNadPlyta += QString("%1").arg(temp.first, 0, 'f', precision);
                temperaturaPodPlyta += QString("%1").arg(temp.second, 0, 'f', precision);
            } else {
                temperaturaNadPlyta += QString("%1 ").arg(temp.first, 0, 'f', precision);
                temperaturaPodPlyta += QString("%1 ").arg(temp.second, 0, 'f', precision);
            }
        }

        line.replace("{$TEMPNAD}", QString("%1").arg(temperaturaNadPlyta));
        line.replace("{$TEMPPOD}", QString("%1").arg(temperaturaPodPlyta));
    } else if (line.contains("{$PRZEWODNOSC_WARSTW}") || line.contains("{$GESTOSC_WARSTW}")
                || line.contains("{$CIEPLO_WLASCIWE_WARSTW}")) {
        QString przewodnoscWarstw;
        QString gestoscWarstw;
        QString cieploWlasciweWarstw;
        int size = c.getWlasciwosciWarstw().size();
        for (int i = 0; i < size; ++i) {
            QTriple<float, float, float> temp = c.getWlasciwosciWarstw().at(i);
            if (i + 1 == size) {
                przewodnoscWarstw += QString("%1").arg(temp.first, 0, 'f', precision);
                cieploWlasciweWarstw += QString("%1").arg(temp.second, 0, 'f', precision);
                gestoscWarstw += QString("%1").arg(temp.third, 0, 'f', precision);
            } else {
                przewodnoscWarstw += QString("%1 ").arg(temp.first, 0, 'f', precision);
                cieploWlasciweWarstw += QString("%1 ").arg(temp.second, 0, 'f', precision);
                gestoscWarstw += QString("%1 ").arg(temp.third, 0, 'f', precision);
            }
        }

        line.replace("{$PRZEWODNOSC_WARSTW}", QString("%1").arg(przewodnoscWarstw));
        line.replace("{$GESTOSC_WARSTW}", QString("%1").arg(gestoscWarstw));
        line.replace("{$CIEPLO_WLASCIWE_WARSTW}", QString("%1").arg(cieploWlasciweWarstw));
    } else if (line.contains("{$MOSTEK}")) {
       QString mostek;
       int size = c.getMostekCieplny().size();
       for (int i = 0; i < size; ++i) {
           double temp = c.getMostekCieplny().at(i);
           if (i + 1 == size) {
               mostek += QString("%1").arg(temp, 0, 'f', 1);
           } else {
               mostek += QString("%1 ").arg(temp, 0, 'f', 1);
           }
       }

       line.replace("{$MOSTEK}", QString("%1").arg(mostek));
   } else if (line.contains("{$PRZEWODNOSC_MOSTKA}") || line.contains("{$GESTOSC_MOSTKA}")
              || line.contains("{$CIEPLO_WLASCIWE_MOSTKA}")) {
      QString przewodnoscMostka;
      QString gestoscMostka;
      QString cieploWlasciweMostka;
      int size = c.getWlasciowsciMostka().size();
      for (int i = 0; i < size; ++i) {
          QTriple<float, float, float> temp = c.getWlasciowsciMostka().at(i);
          if (i + 1 == size) {
              przewodnoscMostka += QString("%1").arg(temp.first, 0, 'f', precision);
              gestoscMostka += QString("%1").arg(temp.second, 0, 'f', precision);
              cieploWlasciweMostka += QString("%1").arg(temp.third, 0, 'f', precision);
          } else {
              przewodnoscMostka += QString("%1 ").arg(temp.first, 0, 'f', precision);
              gestoscMostka += QString("%1 ").arg(temp.second, 0, 'f', precision);
              cieploWlasciweMostka += QString("%1 ").arg(temp.third, 0, 'f', precision);
          }
      }

      line.replace("{$PRZEWODNOSC_MOSTKA}", QString("%1").arg(przewodnoscMostka));
      line.replace("{$GESTOSC_MOSTKA}", QString("%1").arg(gestoscMostka));
      line.replace("{$CIEPLO_WLASCIWE_MOSTKA}", QString("%1").arg(cieploWlasciweMostka));
  }

    return line;
}

