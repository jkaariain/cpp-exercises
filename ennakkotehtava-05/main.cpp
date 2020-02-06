/*
 * ennakkotehtava-05
 *
 */

#include "splitter.hh"
#include "laskin.hh"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    Splitter paloittelija;
    string syote;
    double luku1, luku2, tulos;
    char operaattori;

    while (true){
        cout << "laskin> ";
        getline(cin, syote);

        if (syote == "")
            break;

        paloittelija.aseta_paloiteltava_merkkijono(syote);
        paloittelija.paloittele(' ', true);

        if (paloittelija.kenttien_lukumaara() != 3){
            continue;
        }

        luku1 = stod(paloittelija.hae_kentta(0));
        luku2 = stod(paloittelija.hae_kentta(2));
        operaattori = paloittelija.hae_kentta(1).c_str()[0];

        if (operaattori == '+'){
            tulos = summa(luku1, luku2);
        } else if (operaattori == '-'){
            tulos = erotus(luku1, luku2);
        } else if (operaattori == '*'){
            tulos = kerto(luku1, luku2);
        } else if (operaattori == '/'){
            tulos = jako(luku1, luku2);
        } else{
            continue;
        }

        cout << setprecision(2) << fixed
             << tulos << endl;
    }

    cout << "Kiitos ja näkemiin!" << endl;

    return 0;
}
