#ifndef CONFIG_H
#define CONFIG_H
#include <QList>
#include <QPair>
#include "qtriple.h"

class Config
{
public:
    Config();

    void setEps(float eps) { this->eps = eps; }
    void setFlimit(float flimit) { this->flimit = flimit; }
    void setNtpr1(int ntpr1) {this->ntpr1 = ntpr1; }
    void setNtpr2(int ntpr2) { this->ntpr2 = ntpr2; }
    void setNtprE(int ntpre) { this->ntpre = ntpre; }
    void setTamb(float tamb) { this->tamb = tamb; }
    void setDtime(float dtime) { this->dtime = dtime; }
    void setDtmin(float dtmin) { this->dtmin = dtmin; }
    void setTinit(float tinit) { this->tinit = tinit; }
    void setQprzem(float qprzem) { this->qprzem = qprzem; }
    void setRalfb1(float ralfb1) { this->ralfb1 = ralfb1; }
    void setRalfb5(float ralfb5) { this->ralfb5 = ralfb5; }
    void setT2sle(float t2sle) { this->t2sle = t2sle; }
    void setCepwel(float cepwel) { this->cepwel = cepwel; }
    void setGeswel(float geswel) { this->geswel = geswel; }
    void setWlawel(float wlawel) { this->wlawel = wlawel; }
    void setNstpp(int nstpp) { this->nstpp = nstpp; }
    void addElementX1(float position);
    void addElementX1(float position, float przewodnosc, float cieploWlasciwe, float gestosc);
    void addElementX2(float position, bool mostek = false, float przewodnosc = 0.0, float gestosc = 0.0, float cieploWlasciwe = 0.0);
    void addElementX3(float position);

    void addWspWymianyCieplaNadPlyta(float time, float wspolczynnikWymianyCiepla);
    void addWspWymianyCieplaPodPlyta(float wspolczynnikWymianCiepla) { this->wspWymianyCieplaPodPlyta.append(wspolczynnikWymianCiepla); }
    void addGestoscStrumieniaCieplaPodPlyta(float gestoscStrumieniaCiepla) { this->gestoscStrumieniaCieplaPodPlyta.append(gestoscStrumieniaCiepla); }
    void addTempNadPodPlyta(float temperaturaNadPlyta, float temperaturaPodPlyta);
    void addWarstwa(float przewodnosc, float gestosc, float cieploWlasciwe);

    float getEps() const { return this->eps; }
    float getFlimit() const { return this->flimit; }
    float getNtpr1() const { return this->ntpr1; }
    float getNtpr2() const { return this->ntpr2; }
    float getNtpre() const { return this->ntpre; }
    float getTamb() const { return this->tamb; }
    float getDtime() const { return this->dtime; }
    float getDtmin() const { return this->dtmin; }
    float getTinit() const { return this->tinit; }
    float getQprzem() const { return this->qprzem; }
    float getRalfb1() const { return this->ralfb1; }
    float getRalfb5() const { return this->ralfb5; }
    float getT2sle() const { return this->t2sle; }
    float getCepwel() const { return this->cepwel; }
    float getGeswel() const { return this->geswel; }
    float getWlawel() const { return this->wlawel; }
    float getNstpp() const { return this->nstpp; }
    float getNx1() const;
    float getNx2() const;
    float getNx3() const;
    float getDnp2() const;

    QList<float> getX1Nodes() const { return this->x1Nodes; }
    QList<float> getX2Nodes() const { return this->x2Nodes; }
    QList<float> getX3Nodes() const { return this->x3Nodes; }
    QList< QPair<float, float> > getWspWymianyCieplaNadPlyta() const { return this->wspWymianyCieplaNadPlyta; }
    QList<float> getWspWymianyCieplaPodPlyta() const { return this->wspWymianyCieplaPodPlyta; }
    QList<float> getGestoscStrumieniaCieplaPodPlyta() const { return this->gestoscStrumieniaCieplaPodPlyta; }
    QList< QPair<float, float> > getTempPodNadPlyta() const { return this->tempNadPodPlyta; }
    QList< QTriple<float, float, float> > getWlasciwosciWarstw() const { return this->wlasciwosciWarstw; }
    QList<bool> getMostekCieplny() const { return this->mostekCieplny; }
    QList< QTriple<float, float, float> > getWlasciowsciMostka() const { return this->wlasciowsciMostka; }

private:
    float eps;
    float flimit;
    int ntpr1;
    int ntpr2;
    int ntpre;
    float tamb;
    float dtime;
    float dtmin;
    float tinit;
    float qprzem;
    float ralfb1;
    float ralfb5;
    float t2sle;
    float cepwel;
    float geswel;
    float wlawel;
    int nstpp;
    int nx1;
    int nx2;
    int nx3;
    int dnp2;

    QList<float> x1Nodes;
    QList<float> x2Nodes;
    QList<float> x3Nodes;

    QList< QPair<float, float> > wspWymianyCieplaNadPlyta;
    QList<float> wspWymianyCieplaPodPlyta;
    QList<float> gestoscStrumieniaCieplaPodPlyta;

    QList< QPair<float, float> > tempNadPodPlyta;

    QList< QTriple<float, float, float> > wlasciwosciWarstw;

    QList<bool> mostekCieplny;

    QList< QTriple<float, float, float> > wlasciowsciMostka;
};

#endif // CONFIG_H
