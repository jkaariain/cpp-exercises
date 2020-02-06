/* harjoitustyo-02
 *
 * Jaakko Kääriäinen, 265788
 * jaakko.kaariainen@student.tut.fi
 */
#ifndef KAYTTOLIITTYMA_HH
#define KAYTTOLIITTYMA_HH

#include "splitter.hh"
#include "tiedostonlukija.hh"
#include <string>
#include <vector>
using namespace std;

class Kayttoliittyma
{
public:
    Kayttoliittyma();

    // "Käynnistää" käyttöliittymän
    void suorita();

    // Hakee käyttäjän syöttämän komennon. Jos komento ei ole kelvollinen,
    // tulostetaan virheilmoitus.
    // const string& komennon_nimi: käyttäjän syöttämä komento
    void hae_komento(const string& komennon_nimi);

    // Tulostaa virheilmoituksen seuraavassa muodossa:
    // "Virhe: <viesti>\n", "\n" = rivin vaihto
    // const string& viesti: Virheilmoituksen sanoma
    void tulosta_virhe(const string& viesti) const;

    // Tulostaa tiedoston tietorakenteen kauppaketjut
    // Käyttö: kauppaketjut
    void tulosta_kauppaketjut();

    // Tulostaa tiedoston tietorakenteen kaikkien tuotteiden nimet.
    // Käyttö: tuotenimet
    void tulosta_tuotteet();

    // Tulostaa kauppaketjun kaikki myymälät.
    // Metodi keskeytyy, jos kauppaketjun nimeä ei ole syötetty
    // Käyttö: myymalat <kauppaketjun nimi>
    void tulosta_myymalat();

    // Tulostaa syötetyn tuotteen halvimman hinnan ja myymälät,
    // joissa kyseisen hintaista tuotetta myydään.
    // Metodi keskeytyy, jos tuotteen nimeä ei ole syötetty.
    // Käyttö: halvin <tuotteen nimi>
    void tulosta_halvin();

    // Tulostaa kauppaketjun ja sen myymälän tuotevalikoiman.
    // Metodi keskeytyy, jos kauppaketjun nimeä ja sijaintia ei ole syötetty.
    // Käyttö: tuotevalikoima <kauppaketjun nimi> <sijainti>
    void tulosta_tuotevalikoima();
private:
    bool lopeta_;
    string syote_;
    Splitter paloittelija_;
    Tiedostonlukija tiedostonlukija_;
};

#endif // KAYTTOLIITTYMA_HH
