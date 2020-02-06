// harjoitustyo-05
//
// Reseptikokoelma on map-kaltainen tietorakenne, jonka avaimena on merkkijono
// ja arvona on MerkkijonoJoukko. Jokaisella reseptillä on nimi sekä lista
// materiaaleista, joita tarvitaan sen valmistamiseksi.
// Samalla se huolehtii resepti-tiedoston lataamisesta ohjelman muistiin.
#ifndef RESEPTIKOKOELMA_HH
#define RESEPTIKOKOELMA_HH

#include "merkkijonojoukko.hh"
#include <string>

class ReseptiKokoelma
{
public:
    ReseptiKokoelma();
    ~ReseptiKokoelma();

    // Kysyy käyttäjältä resepti-tiedoston nimen ja lukee sen ohjelman
    // muistiin.
    // true: Tiedosto luettiin onnistuneesti.
    // false: Tiedostossa oli jotain vikaa tai sitä ei voida lukea.
    bool lue_tiedosto();

    // Lisää reseptin reseptikokoelmaan. Lisäksi se lisää reseptin
    // materiaalit_ merkkijonojoukkoon. Jos resepti on lisätty,
    // funktio täydentää reseptiä uudella materiaalilla
    // reseptin_nimi: Reseptin nimi
    // materiaalin_nimi: Materiaali, joka kuuluu reseptiin
    // true: Resepti lisätty tai täydennetty onnistuneesti.
    // false: Jos reseptiin yritetään lisätä materiaalia,
    //        joka on jo lisätty reseptiin.
    bool lisaa(string reseptin_nimi, string materiaalin_nimi);

    // Etsii reseptiä kokoelmasta ja palauttaa true tai false
    // tilanteesta riippuen.
    // reseptin_nimi: Etsittävän reseptin nimi
    // true: Resepti on kokoelmassa
    // false: Resepti ei ole kokoelmassa
    bool onko_resepti_kokoelmassa(string reseptin_nimi) const;

    // Palauttaa totuusarvon, jonka perusteella voidaan päätellä,
    // onko reseptikokoelma tyhjä.
    // true: Kokoelma on tyhjä.
    // false: Kokoelma ei ole tyhjä.
    bool onko_tyhja() const;

    // Poistaa kokoelmasta reseptin kokoelman alusta.
    // true: Resepti poistettiin
    // false: Reseptiä ei poistettu (kokoelma tyhjä)
    bool poista_alusta();

    // Tyhjentää reseptikokoelman.
    void tyhjenna();

    // Hakee reseptin toteuttamiseen tarvittavat materiaalit.
    // reseptin_nimi: Resepti, josta haetaan materiaalit
    // Palauttaa osoittimen reseptin materiaaleihin.
    // Jos reseptia ei ole kokoelmassa, se palauttaa nullptr arvon.
    MerkkijonoJoukko *hae_materiaalit(string reseptin_nimi);

    // Hakee kaikki materiaalit ja esineet, jotka ovat ladattuna
    // ohjelman muistiin.
    // Palauttaa vakio-osoittimen materiaalit_ merkkijonojoukkoon.
    const MerkkijonoJoukko* hae_kaikki_materiaalit() const;

private:
    struct Resepti{
        string nimi;
        MerkkijonoJoukko materiaalit;
        Resepti* seuraava;
    };

    Resepti* alku_;
    Resepti* loppu_;
    MerkkijonoJoukko materiaalit_;
};

#endif // RESEPTIKOKOELMA_HH
