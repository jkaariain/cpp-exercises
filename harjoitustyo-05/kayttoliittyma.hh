// harjoitustyo-05
//
// Kayttoliittyma-moduuli huolehtii ohjelman pääsilmukasta.
// Lisäksi se käsittelee käyttäjän syöttämät syötteet
// tarvittavilla funktioilla.
#ifndef KAYTTOLIITTYMA_HH
#define KAYTTOLIITTYMA_HH

#include "reseptikokoelma.hh"
#include <string>
using namespace std;

class Kayttoliittyma
{
public:
    Kayttoliittyma();

    // "Käynnistää" käyttöliittymän
    void suorita();
private:
    // Tulostaa virheilmoituksen.
    // viesti: Virheilmoitus
    void tulosta_virhe(string viesti) const;

    // Käsittelee käyttäjän syöttämän komennon.
    // komento: käyttäjän syöttämä komento
    void kasittele_komento(string komento);

    // Hakee esineen askartelemiseen tarvittavat materiaalit
    // ja tulostaa ne komentoriviin aakkosjärjestyksessä.
    // Jos esineen askartelemiseen ei tarvita materiaaleja,
    // funktio ei tulosta mitään.
    // esine: Esine, josta materiaalit haetaan.
    void materiaalit(string esine);

    // Tarkastaa, voiko repun sisällöstä askarrella
    // käyttäjän pyytämää materiaalia.
    // Tämä funktio kuitenkin vain askarreltavan materiaalin suorat edeltäjät.
    // materiaali: askarreltava materiaali
    // -1: materiaalia ei ole olemassa.
    // 0: Materiaalia ei voi askarrella.
    // 1: Materiaalin voi askarrella.
    int askarreltavissa(string materiaali);

    // Tarkastaa, voiko repun sisällöstä askarrella
    // käyttäjän pyytämää materiaalia.
    // Tämä funktio on hienostuneempi versio askarreltavissa-funktiosta,
    // sillä se käy läpi tuotantoketjussa olevat välimateriaalit.
    // materiaali: askarreltava materiaali
    // -1: materiaalia ei ole olemassa.
    // 0: Materiaalia ei voi askarrella.
    // 1: Materiaalin voi askarrella.
    int askarreltavissa_bonus(string materiaali);

    string syotevirta_;
    MerkkijonoJoukko reppu_;
    ReseptiKokoelma reseptit_;
    bool lopeta_;
};

#endif // KAYTTOLIITTYMA_HH
