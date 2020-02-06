/* harjoitustyo-02
 */
#ifndef TIEDOSTONLUKIJA_HH
#define TIEDOSTONLUKIJA_HH

#include "splitter.hh"
#include "tuote.hh"
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <map>
using namespace std;

class Tiedostonlukija
{
public:
    Tiedostonlukija();
    Tiedostonlukija(const string& tiedoston_nimi);
    ~Tiedostonlukija();

    // Avaa tiedoston.
    // return bool: true, jos tiedoston avaus onnistui
    //              false, tiedoston avaus epäonnistui
    bool avaa_tiedosto(const string& tiedoston_nimi);

    // Antaa viittauksen tietorakenteeseen
    // return map<string, map<string, vector<Tuote>>>& tietorakenne
    map<string, map<string, vector<Tuote>>>& anna_tietorakenne();

    // Antaa viittauksen tietorakenteen tuotevalikoimaan
    // set<string>& tuotevalikoima
    set<string>& anna_tuotenimet();
private:
    // Tarkistaa tiedoston rivit ja tallentaa jokaisen rivin
    // tietorakenteeseen.
    // return bool: true, jos tiedostossa ei ole mitään vikaa
    //              false, tiedostossa on jotakin vikaa.)
    bool tarkista_tiedoston_eheys_ja_tallenna_tietorakenteeseen_();

    ifstream tiedosto_;
    bool tiedosto_avattu_;
    Splitter paloittelija_;
    string rivi_;

    set<string> tuotenimet_;
    map<string, map<string, vector<Tuote>>> tietorakenne_;
};

#endif // TIEDOSTONLUKIJA_HH
