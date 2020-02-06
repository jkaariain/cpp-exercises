/* harjoitustyo-01
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <limits>
using namespace std;

class Splitter{
public:
    /* Paloittelijan rakentajafunktio */
    /* const string& paloiteltava_merkkijono: paloiteltava merkkijono */
    Splitter(const string& paloiteltava_merkkijono = "");

    /* Asettaa paloittelijan merkkijonon */
    /* const string& merkkijono: paloiteltava merkkijono */
    void aseta_paloiteltava_merkkijono(const string& merkkijono);

    /* Paloittelee merkkijonon ja tallentaa paloitellut
     * merkkijonot merkkijonot_-sailioon.
     * char erotinmerkki: merkki, jonka perusteella merkkijonot paloitellaan
     * bool ohita_tyhjat: sailioon ei sisallyteta tyhjia alkioita*/
    unsigned int paloittele(char erotinmerkki, bool ohita_tyhjat = false);

    /* Palauttaa sailion kenttien lukumaaran */
    unsigned int kenttien_lukumaara() const;

    /* Hakee kentan arvon
     * unsigned int kentan_numero: sailion indeksi */
    string hae_kentta(unsigned int kentan_numero) const;
private:
    string merkkijono_;

    vector<string> merkkijonot_;

    bool paloittele_metodi_kutsuttu_;
};

class Pankkitili{
public:
    /* Pankkitilin rakentajafunktio. Jos saldo on negatiivinen, saldoksi
     * asetetaan 0.0 */
    Pankkitili();
    Pankkitili(double saldo, string tilinumero, unsigned int asiakasnumero);
    ~Pankkitili();

    /* Hakee pankkitilin saldon. */
    /* paluuarvo: saldo desimaalilukuna */
    double hae_saldo() const;

    /* Hakee pankkitilin tilinumeron. */
    /* paluuarvo: tilinumero merkkijonona */
    string hae_tilinumero() const;

    /* Hakee pankkitilin asiakasnumeron. */
    /* paluuarvo: asiakasnumero kokonaislukuna*/
    unsigned int hae_asiakasnumero() const;

    /* Asettaa pankkitilin saldon. Metodi asettaa saldon arvoksi 0.0, jos
     * parametrin arvo on negatiivinen. */
    /* double saldo: asetettava saldo*/
    void aseta_saldo(double saldo);

    /* Asettaa pankkitilin tilinumeron. */
    /* string tilinumero: asetettava tilinumero*/
    void aseta_tilinumero(string tilinumero);

    /* Asettaa pankkitilin asiakasnumeron. */
    /* unsigned int asiakasnumero: asetettava asiakasnumero*/
    void aseta_asiakasnumero(unsigned int asiakasnumero);

    /* Suorittaa tilisiirron lahdekortilta kohdekorttiin.
     * Metodi palauttaa 'true', jos tilisiirto onnistui.
     * Metodi palauttaa 'false', jos rahamaara on suurempi kuin tilin saldo.
     * Pankkitili& kohdetili: tili, jonne siirretaan rahasumma
     * double rahamaara: siirrettava rahasumma */
    bool tilisiirto(Pankkitili& kohdetili, double rahamaara);

private:
    double saldo_;
    string tilinumero_;
    unsigned int asiakasnumero_;
};

/* Kasittelee kayttajan antamat komennot. */
/* bool& loppu: viittemuuttuja ohjelman lopetus -muuttujalle */
/* vector<Pankkitili>& tilit: viitemuuttuja pankkitilisailioon */
/* vector<Pankkitili>::size_type eka_parametri*/
/* vector<Pankkitili>::size_type toinen_parametri */
void suorita_komento(bool& loppu, vector<Pankkitili>& tilit,
                 const string& komennon_nimi,
                 vector<Pankkitili>::size_type eka_parametri,
                 vector<Pankkitili>::size_type toinen_parametri);

/* Tulostaa pankkitilin tiedot */
/* const Pankkitili& tili: tulostettava pankkitili*/
void tulosta_pankkitili(const Pankkitili& tili);

/* Kysyy kayttajalta pankkitille tarvittavat tiedot ja tallentaa ne tilille. */
/* Pankkitili& tili: tili, jonne tiedot tallennetaan.*/
void aseta_tiedot(Pankkitili& tili);

/* Hakee desimaaliluvun syotelaitteesta. */
/* paluuarvo: desimaaliluku*/
double hae_desimaaliluku();

/* Hakee positiivisen kokonaisluvun syotelaitteesta. */
/* paluuarvo: positiivinen kokonaisluku*/
unsigned int hae_pos_kokonaisluku();

int main()
{
    // Ohjelman lopetusmuuttuja
    bool lopeta = false;
    vector<Pankkitili> tilit;
    string syote;
    string komennon_nimi;
    Splitter paloittelija;

    Pankkitili tili1(13.21, "FI1122223333444455", 1234567);
    Pankkitili tili2(12345.67, "FI123456789101112", 6836234);
    Pankkitili tili3(16721.02, "FI5544443333222211", 4711123);

    tilit.push_back(tili1);
    tilit.push_back(tili2);
    tilit.push_back(tili3);

    vector<Pankkitili>::size_type eka_parametri = INT32_MAX;
    vector<Pankkitili>::size_type toinen_parametri = INT32_MAX;

    while (!lopeta){
        eka_parametri = INT32_MAX;
        toinen_parametri = INT32_MAX;

        cout << "pankkitilitesti> ";
        getline(cin, syote);
        paloittelija.aseta_paloiteltava_merkkijono(syote);
        paloittelija.paloittele(' ', true);

        komennon_nimi = paloittelija.hae_kentta(0);

        try{

            eka_parametri = stoi(paloittelija.hae_kentta(1));
            toinen_parametri = stoi(paloittelija.hae_kentta(2));
        } catch (invalid_argument){

        }

        suorita_komento(lopeta, tilit, komennon_nimi, eka_parametri,
                        toinen_parametri);
    }

    return 0;
}

double hae_desimaaliluku(){
    double syote;

    while (!(cin >> syote)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Syota desimaaliluku: ";
        if (cin >> syote)
            break;
    }

    return syote;
}

unsigned int hae_pos_kokonaisluku(){
    unsigned int syote;

    while (!(cin >> syote)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Syota positiivinen kokonaisluku: ";
        if (cin >> syote)
            break;
    }

    return syote;
}

Pankkitili::Pankkitili(){
    saldo_ = 0.0;
    tilinumero_ = "";
    asiakasnumero_ = 0;
}

Pankkitili::Pankkitili(double saldo, string tilinumero,
                       unsigned int asiakasnumero):
    saldo_(saldo), tilinumero_(tilinumero), asiakasnumero_(asiakasnumero)
{
    if (saldo < 0.0)
        saldo_ = 0.0;
}

Pankkitili::~Pankkitili(){

}

double Pankkitili::hae_saldo() const{
    return saldo_;
}

string Pankkitili::hae_tilinumero() const{
    return tilinumero_;
}

unsigned int Pankkitili::hae_asiakasnumero() const{
    return asiakasnumero_;
}

void Pankkitili::aseta_saldo(double saldo){
    if (saldo < 0.0)
        saldo_ = 0.0;

    saldo_ = saldo;
}

void Pankkitili::aseta_tilinumero(string tilinumero){
    tilinumero_ = tilinumero;
}

void Pankkitili::aseta_asiakasnumero(unsigned int asiakasnumero){
    asiakasnumero_ = asiakasnumero;
}

bool Pankkitili::tilisiirto(Pankkitili& kohdetili, double rahamaara){
    if (saldo_ < rahamaara)
        return false;

    kohdetili.aseta_saldo(kohdetili.hae_saldo() + rahamaara);
    saldo_ -= rahamaara;

    return true;
}

void suorita_komento(bool& loppu, vector<Pankkitili>& tilit,
                 const string& komennon_nimi,
                 vector<Pankkitili>::size_type eka_parametri,
                 vector<Pankkitili>::size_type toinen_parametri)
{
    if (komennon_nimi == "loppu"){
        loppu = true;
    } else if (komennon_nimi == "aseta"){
        eka_parametri--;

        try{
            aseta_tiedot(tilit.at(eka_parametri));

            cout << "Tilin " << eka_parametri+1 <<
                    " tiedot asetettu." << endl;

            cin.get();
        } catch (out_of_range) {
            cout << "Virhe: tilia ei ole olemassa." << endl;
        }
    } else if (komennon_nimi == "tulosta"){
        eka_parametri--;

        try{
            tulosta_pankkitili(tilit.at(eka_parametri));
        } catch (out_of_range){
            cout << "Virhe: tilia ei ole olemassa" << endl;
        }
    }
    else if (komennon_nimi == "otto"){

        eka_parametri--;

        try{
            Pankkitili kohdetili = tilit.at(eka_parametri);

            double rahamaara;
            cout << "Syota rahamaara: ";
            rahamaara = hae_desimaaliluku();

            while (rahamaara < 0.0){
                cout << "Virhe: rahamaara ei voi olla pienempi kuin nolla.\n";
                cout << "Syota rahamaara: ";
                rahamaara = hae_desimaaliluku();
            }

            double saldo_oton_jalkeen =
                    tilit[eka_parametri].hae_saldo() - rahamaara;

            if (saldo_oton_jalkeen >= 0.0)
            {
                tilit[eka_parametri].aseta_saldo(saldo_oton_jalkeen);
                cout << "Otto suoritettu tililta " <<
                        eka_parametri+1 << ".\n";
            } else {
                cout << "Virhe: tililla ei ole riittavasti katetta.\n";
            }

            cin.get();
        } catch (out_of_range){
            cout << "Virhe: tilia ei ole olemassa" << endl;
        }
    } else if (komennon_nimi == "pano"){

        eka_parametri--;

        try{
            Pankkitili kohdetili = tilit.at(eka_parametri);

            double rahamaara;
            cout << "Syota rahamaara: ";
            rahamaara = hae_desimaaliluku();

            while (rahamaara < 0.0){
                cout << "Virhe: rahamaara ei voi olla pienempi kuin nolla.\n";
                cout << "Syota rahamaara: ";
                rahamaara = hae_desimaaliluku();
            }

            tilit[eka_parametri].aseta_saldo(tilit[eka_parametri].hae_saldo()
                                             + rahamaara);
            cout << "Pano suoritettu tilille " << eka_parametri+1 << ".\n";

            cin.get();
        } catch (out_of_range){
            cout << "Virhe: tilia ei ole olemassa" << endl;
        }
    } else if (komennon_nimi == "tilisiirto"){

        eka_parametri--;
        toinen_parametri--;

        try{
            // Olemassaolotesti
            Pankkitili lahde = tilit.at(eka_parametri);
            Pankkitili kohde = tilit.at(toinen_parametri);

            double rahamaara;
            cout << "Syota siirtomaara: ";
            rahamaara = hae_desimaaliluku();

            while (rahamaara < 0.0){
                cout << "Virhe: rahamaara ei voi olla pienempi kuin nolla.\n";
                cout << "Syota rahamaara: ";
                rahamaara = hae_desimaaliluku();
            }

            if (!tilit[eka_parametri].tilisiirto(tilit[toinen_parametri]
                                                 , rahamaara)){
                cout << "Virhe: tilisiirto epaonnistui.\n";
            }

            cin.get();
        } catch (out_of_range){
            cout << "Virhe: Yksi tai useampi tileista ei ole olemassa.\n";
        }
    } else if (komennon_nimi == ""){
        return;
    }
    else
    {
        cout << "Virhe: tuntematon komento" << endl;
    }
}

void tulosta_pankkitili(const Pankkitili &tili){
    cout << "Tilinumero: " << tili.hae_tilinumero() << endl;
    cout << fixed << setprecision(2) << "Saldo: " << tili.hae_saldo() << endl;
    cout << "Asiakasnumero: " << tili.hae_asiakasnumero() << endl;
}

void aseta_tiedot(Pankkitili& tili){
    string tilinum;
    unsigned int asiakasnum;
    double sald;

    cout << "Syota tilinumero: ";
    cin >> tilinum;
    cout << "Syota saldo: ";
    sald = hae_desimaaliluku();
    cout << "Syota asiakasnumero: ";
    asiakasnum = hae_pos_kokonaisluku();

    tili.aseta_tilinumero(tilinum);
    tili.aseta_saldo(sald);
    tili.aseta_asiakasnumero(asiakasnum);
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
        return 0;

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
        return "";
    }
}

