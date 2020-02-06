/*
 * ennakkotehtava-03
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

const unsigned int SPLITTER_VIRHE = 0;

class Splitter{
public:
    Splitter(const string& paloiteltava_merkkijono = "");

    void aseta_paloiteltava_merkkijono(const string& merkkijono);

    unsigned int paloittele(char erotinmerkki, bool ohita_tyhjat = false);

    unsigned int kenttien_lukumaara() const;

    string hae_kentta(unsigned int kentan_numero) const;
private:
    string merkkijono_;

    vector<string> merkkijonot_;

    bool paloittele_metodi_kutsuttu_;
};

int main()
{
    Splitter paloittelija("a::bc:def::hijklm");

    paloittelija.paloittele(':');

    cout << "kenttia: " << paloittelija.kenttien_lukumaara() << endl; // 6

    cout << paloittelija.hae_kentta(0) << endl; // a
    cout << paloittelija.hae_kentta(4) << endl; // (tyhjä)
    cout << paloittelija.hae_kentta(5) << endl; // hijklm

    for (unsigned int i = 0; i < paloittelija.kenttien_lukumaara(); ++i){
        string kasiteltava_kentta = paloittelija.hae_kentta(i);
        cout << i << ": [" << kasiteltava_kentta << "]" << endl;
    }

    paloittelija.aseta_paloiteltava_merkkijono(" A B  C    D    E     ");
    unsigned int kenttia = paloittelija.paloittele(' ', true);

    cout << "kenttia: " << kenttia << endl; // 5

    for (unsigned int i = 0; i < kenttia; ++i){
        string kasiteltava_kentta = paloittelija.hae_kentta(i);
        cout << i << ": [" << kasiteltava_kentta << "]" << endl;
    }

    cout << paloittelija.hae_kentta(5) << endl;

    return 0;
}

Splitter::Splitter(const string &paloiteltava_merkkijono)
    : merkkijono_(paloiteltava_merkkijono){
    merkkijonot_.clear();
    paloittele_metodi_kutsuttu_ = false;
}

void Splitter::aseta_paloiteltava_merkkijono(const string &merkkijono){
    merkkijono_ = merkkijono;
    merkkijonot_.clear();
    paloittele_metodi_kutsuttu_ = false;
}

unsigned int Splitter::paloittele(char erotinmerkki, bool ohita_tyhjat){
    paloittele_metodi_kutsuttu_ = true;
    string lisattava_merkkijono = "";

    for (char c : merkkijono_){
        if (c == erotinmerkki){
            if (ohita_tyhjat && lisattava_merkkijono == ""){
                continue;
            }

            merkkijonot_.push_back(lisattava_merkkijono);
            lisattava_merkkijono = "";
            continue;
        }

        lisattava_merkkijono.push_back(c);
    }

    if (lisattava_merkkijono.size() > 0){
        merkkijonot_.push_back(lisattava_merkkijono);
        lisattava_merkkijono = "";
    }

    return (unsigned int)merkkijonot_.size();
}

unsigned int Splitter::kenttien_lukumaara() const{
    if (!paloittele_metodi_kutsuttu_)
        return SPLITTER_VIRHE;

    return (unsigned int)merkkijonot_.size();
}

string Splitter::hae_kentta(unsigned int kentan_numero) const{
    try{
        if (kentan_numero > merkkijonot_.size() ||
                !paloittele_metodi_kutsuttu_)
            throw out_of_range("virheellinen kentan_numero");


        return merkkijonot_.at(kentan_numero);
    }
    catch (out_of_range){
        cout << "virheellinen kentan_numero";
    }

    return "";
}
