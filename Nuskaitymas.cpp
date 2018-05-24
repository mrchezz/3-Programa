//
// Created by MD on 2018-05-21.
//

#include "Nuskaitymas.h"
#include "Studentas.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using std::ifstream;
using std::sort;
using std::cout;
using std::setprecision;
using std::endl;
using std::setw;
using std::ofstream;

bool Skirstymas(const Studentas& a)
{
    return a.getVidurkis() > 6;
}

void Nuskaitymas(int kiekis)
{
    vector<Studentas> visi;
    vector<Studentas> kieti;
    vector<Studentas> moliai;
    ifstream fd;
    ofstream fr;
    string zodis;
    double skaicius;
    try {
        if (kiekis == 10)
            fd.open("10.txt");
        if (kiekis == 100)
            fd.open("100.txt");
        if (kiekis == 1000)
            fd.open("1000.txt");
        if (kiekis == 10000)
            fd.open("10000.txt");
        if (kiekis == 100000)
            fd.open("100000.txt");

        if (kiekis == 10)
            fr.open("10rez.txt");
        if (kiekis == 100)
            fr.open("100rez.txt");
        if (kiekis == 1000)
            fr.open("1000rez.txt");
        if (kiekis == 10000)
            fr.open("10000rez.txt");
        if (kiekis == 100000)
            fr.open("100000rez.txt");
    }
    catch (const std::ifstream::failure &e) {
        std::cout << e.what() << std::endl;
    }
    string line;
    while (std::getline(fd, line)) {
        Studentas laikinas;
        std::istringstream iss(line);
        iss >> zodis;
        laikinas.setVardas(zodis);
        iss >> zodis;
        laikinas.setPavarde(zodis);
        laikinas.setMediana(0);
        for (int i = 0; i < 5; i++) {
            iss >> skaicius;
            laikinas.setPazymiai(skaicius);
            laikinas.fillVidurkis(skaicius);
        }
        const int Kiekis = laikinas.getSize();
        iss >> skaicius;
        laikinas.setEgzaminas(skaicius);

        laikinas.sortPazymiai();
            if(Kiekis%2==0)
            {
                       laikinas.setMediana((laikinas.getPazymiai(Kiekis/2)+laikinas.getPazymiai((Kiekis/2)+1))/2);
            }

        if(Kiekis%2!=0)
        {
                laikinas.setMediana(laikinas.getPazymiai(Kiekis/2));
        }
        laikinas.setVidurkis(laikinas.getVidurkis()/Kiekis);
            visi.push_back(laikinas);
    }
    fr<<"Visi studentai:"<<endl;
    fr<<"Vardas    Pavarde      vidurkis     mediana"<<endl;
    for(auto i=visi.begin(); i != visi.end(); ++i)
        fr<<i->getVardas()<<setw(11)<<i->getPavarde()<<setw(11)<<setprecision(3)<<i->getVidurkis()<<setw(11)<<i->getMediana()<<endl;
    vector<Studentas>::iterator riba;
    riba=std::stable_partition(visi.begin(),visi.end(),Skirstymas);
    //sort(visi.begin(),visi.end());
    fr<<endl<<"moliai:"<<endl;
    fr<<"Vardas    Pavarde      vidurkis     mediana"<<endl;

    for(auto i=riba; i != visi.end(); ++i)
        fr<<i->getVardas()<<setw(11)<<i->getPavarde()<<setw(11)<<setprecision(3)<<i->getVidurkis()<<setw(11)<<i->getMediana()<<endl;
    fr<<endl<<"kieti:"<<endl;
    fr<<"Vardas    Pavarde      vidurkis     mediana"<<endl;
    for(auto i=visi.begin(); i != riba; ++i)
        fr<<i->getVardas()<<setw(11)<<i->getPavarde()<<setw(11)<<setprecision(3)<<i->getVidurkis()<<setw(11)<<i->getMediana()<<endl;

}