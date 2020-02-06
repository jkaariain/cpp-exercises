// harjoitustyo-05
//
// MerkkijonoJoukko on luokka linkitetylle listalle, johon voi varastoida
// merkkijonoja. Merkkijonot kuitenkin ovat uniikkeja eli joukossa ei
// voi olla useamman kerran samaa merkkijonoa.
//
// MerkkijonoJoukolle on kehitetty lisäksi oma iteraattori, jonka avulla
// joukon alkioita pystyy tutkimaan ja muokkaamaan.
#ifndef MERKKIJONOJOUKKO_HH
#define MERKKIJONOJOUKKO_HH

#include <string>
using namespace std;

struct Alkio {
    string data;
    Alkio* seuraava;
};

class MerkkijonoJoukko
{
public:
    // Asettaa alku_ ja loppu_ osoittimet arvoon nullptr.
    MerkkijonoJoukko();

    // Tyhjentää joukon
    ~MerkkijonoJoukko();

    // Palauttaa totuusarvon, jonka mukaan voidaan päätellä,
    // onko merkkijonojoukko tyhjä.
    // true: Merkkijonojoukko on tyhjä.
    // false: Merkkijonojoukko ei ole tyhjä.
    bool tyhja() const;

    // Tulostaa merkkijonojoukon sisällön.
    void tulosta() const;

    // Lisää merkkijonojoukkoon merkkijonon. Jos merkkijono on jo joukossa,
    // merkkijonoa ei lisätä.
    // merkkijono: Lisättävä merkkijono.
    // true: Merkkijono lisättiin joukkoon.
    // false: Merkkijonoa ei lisätty joukkoon.
    bool lisaa(string merkkijono);

    // Poistaa merkkijonojoukon alusta merkkijonon.
    // Jos joukko on tyhjä, funktio ei tee mitään.
    // true: Merkkijono poistettiin joukon alusta.
    // false: Merkkijonoa ei poistettu (joukko on tyhjä)
    bool poista_alusta();

    // Etsii joukosta merkkijonoa ja palauttaa tietyn totuusarvon
    // tilanteesta riippuen.
    // merkkijono: Etsittävä merkkijono
    // true: Merkkijono on joukossa.
    // false: Merkkijono ei ole joukossa.
    bool onko_joukossa(string merkkijono) const;

    // Tyhjentää joukon.
    void tyhjenna();

    // Järjestää joukon aakkosjärjestykseen.
    // Algoritmina on käytetty valintalajittelua.
    void jarjesta();

    // Palauttaa alkioiden määrän joukossa.
    int koko() const;

    // Palauttaa osoittimen joukon alkuun.
    Alkio* alku();

    // Palauttaa arvon nullptr.
    Alkio* loppu();

private:
    Alkio* alku_;
    Alkio* loppu_;
};

class Iteraattori
{
public:
    // Rakentajafunktio iteraattorille
    Iteraattori(Alkio* alkio);

    // ++ -operaattori: siirtää iteraattorin seuraavaan alkioon.
    Iteraattori& operator++(); // prefix-operaattori
    Iteraattori operator++(int); // postfix-operaattori

    // Palauttaa iteraattorin osoittaman alkion datan eli merkkijonon.
    string &operator *();

    // Palauttaa totuusarvon, jonka avulla voidaan päätellä,
    // osoittavatko iteraattorit samaan osoitteeseen.
    bool operator==(const Iteraattori& rhs);

    // Palauttaa totuusarvon, jonka avulla voidaan päätellä,
    // osoittavatko iteraattorit eri osoitteisiin.
    bool operator!=(const Iteraattori& rhs);
private:
    Alkio* alkio_;
};


#endif // MERKKIJONOJOUKKO_HH
