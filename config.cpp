#include "config.h"

Config::Config()
{
}

void Config::addElementX1(float position, float przewodnosc, float gestosc, float cieploWlasciwe) {
    this->x1Nodes.append(position);

    if (this->x1Nodes.size() == 1) {
        return;
    }

    QTriple<float, float, float> temp;
    temp.first = przewodnosc;
    temp.second = gestosc;
    temp.third = cieploWlasciwe;

    this->wlasciwosciWarstw.append(temp);
}

void Config::addElementX1(float position) {
    if (this->x1Nodes.size() <= 1) {
        addElementX1(position, 0, 0, 0);
    } else {
        int index = this->x1Nodes.size() - 2;
        QTriple<float, float, float> warstwa = this->wlasciwosciWarstw.at(index);
        float przewodnosc = warstwa.first;
        float gestosc = warstwa.second;
        float cieploWlasciwe = warstwa.third;
        addElementX1(position, przewodnosc, cieploWlasciwe, gestosc);
    }
}

void Config::addElementX2(float position, bool mostek, float przewodnosc, float cieploWlasciwe, float gestosc) {
    this->x2Nodes.append(position);

    if (this->x2Nodes.size() == 1) {
        return;
    }

    this->mostekCieplny.append(mostek);

    QTriple<float, float, float> temp;
    if (mostek) {
        temp.first = przewodnosc;
        temp.second = cieploWlasciwe;
        temp.third = gestosc;
    } else {
        temp.first = 0;
        temp.second = 0;
        temp.third = 0;
    }
    this->wlasciowsciMostka.append(temp);
}

void Config::addElementX3(float position) {
    this->x3Nodes.append(position);
}

float Config::getNx1() const {
    int size = this->x1Nodes.size() - 1;
    if (size < 0) {
        return 0;
    }
    return size;
}

float Config::getNx2() const {
    int size = this->x2Nodes.size() - 1;
    if (size < 0) {
        return 0;
    }
    return size;
}

float Config::getNx3() const {
    int size = this->x3Nodes.size() - 1;
    if (size < 0) {
        return 0;
    }
    return size;
}

float Config::getDnp2() const {
    return this->wspWymianyCieplaNadPlyta.size();
}

void Config::addWspWymianyCieplaNadPlyta(float time, float wspolczynnikWymianyCiepla) {
    QPair<float, float> temp = qMakePair(time, wspolczynnikWymianyCiepla);
    this->wspWymianyCieplaNadPlyta.append(temp);
}

void Config::addTempNadPodPlyta(float temperaturaNadPlyta, float temperaturaPodPlyta) {
    QPair<float, float> temp = qMakePair(temperaturaNadPlyta, temperaturaPodPlyta);
    this->tempNadPodPlyta.append(temp);
}

void Config::addWarstwa(float przewodnosc, float gestosc, float cieploWlasciwe) {
    QTriple<float, float, float> temp;
    temp.first = przewodnosc;
    temp.second = gestosc;
    temp.third = cieploWlasciwe;

    this->wlasciwosciWarstw.append(temp);
}
