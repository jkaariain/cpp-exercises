/*
 * ennakkotehtava-01
 *
*/

#include <iostream>
#include <limits> /* Sisältää numeric_limits funktion. */
#include <cmath> /* Sisältää piin lukuarvon ja potenssifunktion */
using namespace std;

/* Määrittää ympyrän pinta-alan säteen pituuden perusteella.
 * double sade: Ympyrän säde.
 * Palautusarvo: Ympyrän pinta-ala.
*/
double ympyran_pinta_ala(double sade);


/* Määrittää ympyrän piirin pituuden säteen pituuden perusteella.
 * double sade: Ympyrän säde.
 * Palautusarvo: Ympyrän piirin pituus.
*/
double ympyran_piirin_pituus(double sade);

int main()
{
    double ympyran_sade;

    cout << "Ympyran sade: ";

    /* Jos käyttäjän syöte ei ole kelvollinen, tyhjennä merkkipuskuri
       ja pyydä käyttäjää syöttämään luku.*/
    while (!(cin >> ympyran_sade)){
        cin.clear(); /* Resetoi syötevirran tila. */

        /* Vältä virheellisen syötteen merkit. */
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Syota luku.\n";
        /* Jos syöte on kelvollinen, poistu silmukasta. */
        if (cin >> ympyran_sade)
            break;
    }

    /* Tulosta ympyrän pinta-alan suuruus ja piirin pituus. */
    cout << "\nYmpyran ala: " << ympyran_pinta_ala(ympyran_sade);
    cout << "\nYmpyran piiri: " << ympyran_piirin_pituus(ympyran_sade)
         << endl;

    return 0;
}

double ympyran_pinta_ala(double sade)
{
    return M_PI * pow(sade, 2);
}

double ympyran_piirin_pituus(double sade)
{
    return 2 * M_PI * sade;
}
