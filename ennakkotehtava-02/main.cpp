/*
 * ennakkotehtava-02
 *
*/

#include <iostream>
#include <iomanip>
#include <limits>

int hae_luku(); /* Hakee kokonaisluvun käyttäjältä. */

using namespace std;

class Kellonaika{
public:
    Kellonaika();
    Kellonaika(int tunti, int minuutti);
    void tiktok();  // Aika kasvaa yhdellä minuutilla
    int hae_minuutti() const;
    int hae_tunti() const;
    int aikaero_min(const Kellonaika& toinen_aika) const;
    void tulosta() const;

    int aseta_tunti();
    int aseta_minuutti();

private:
    int kuluneet_minuutit_;
};

int main(){
    Kellonaika kello1, kello2;

    cout << "Kello 1:\nTunti: ";
    kello1.aseta_tunti();
    cout << "Minuutti: ";
    kello1.aseta_minuutti();

    kello1.tulosta();

    cout << "Kello 2:\nTunti: ";
    kello2.aseta_tunti();
    cout << "Minuutti: ";
    kello2.aseta_minuutti();

    kello2.tulosta();

    cout << "Aikaero (min): " << kello1.aikaero_min(kello2) << endl;

    return 0;
}

Kellonaika::Kellonaika():
    kuluneet_minuutit_(0){

}

Kellonaika::Kellonaika(int tunti, int minuutti):
    kuluneet_minuutit_(60 * tunti + minuutti){

}

void Kellonaika::tiktok(){
    ++kuluneet_minuutit_;
    if (kuluneet_minuutit_ >= 24 * 60){
        kuluneet_minuutit_ = 0;
    }
}

void Kellonaika::tulosta() const{
    cout << setw(2) << setfill('0') << hae_tunti()
         << '.'
         << setw(2) << hae_minuutti()
         << endl;
}

int Kellonaika::hae_minuutti() const{
    return kuluneet_minuutit_ % 60;
}

int Kellonaika::hae_tunti() const{
    return kuluneet_minuutit_ / 60;
}

int Kellonaika::aikaero_min(const Kellonaika &toinen_aika) const{
    /* Jos ensimmäisen kellon aika on pienempi kuin toisen kellon. */
    if (kuluneet_minuutit_ < toinen_aika.hae_tunti()
            * 60 + toinen_aika.hae_minuutti()){
        /* kello2 - kello1 */
        return (toinen_aika.hae_tunti() * 60 + toinen_aika.hae_minuutti())
                - kuluneet_minuutit_;
    }
    /* Jos kello ovat samassa ajassa. */
    else if (kuluneet_minuutit_ == toinen_aika.hae_tunti() * 60
             + toinen_aika.hae_minuutti()){
        return 0;
    }

    /* kello2 < kello1 */
    /* (1 d) 1440 min - kello1 + kello2 */
    return (24 * 60 - kuluneet_minuutit_) + toinen_aika.hae_tunti()
            * 60 + toinen_aika.hae_minuutti();
}

int Kellonaika::aseta_tunti(){
    int tunti = hae_luku();

    while (tunti < 0 || tunti > 23){
        cout << "Vain 0-23 kelpaavat tunneiksi." << endl;
        tunti = hae_luku();
    }

    kuluneet_minuutit_ += tunti * 60;
}

int Kellonaika::aseta_minuutti(){
    int minuutti = hae_luku();

    while (minuutti < 0 || minuutti > 59){
        cout << "Vain 0-59 kelpaavat minuuteiksi." << endl;
        minuutti = hae_luku();
    }

    kuluneet_minuutit_ += minuutti;
}

int hae_luku(){
    int syote;

    while (!(cin >> syote)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Syota luku.\n";
        if (cin >> syote){
            break;
        }
    }

    return syote;
}
