//------------------------------------------------
//  TIE-02200 Ohjelmoinnin peruskurssi -koodipohja
//  Copyright © 2017  opersk@tut.fi
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;


struct Opiskelija {
    string nimi;
    unsigned int opnum;
};


// ***** TODO *****************************************************************
// Toteuta tähän kohtaan vertailufunktio algorithm-kirjaston
// sort-funktiota varten.  Funktion on osattava vertailla kahta
// Opiskelija-tyyppistä struct:ia siten, että aakkosissa aiemmin
// oleva nimi-kenttä tulkitaan pienemmäksi struct:iksi.
// ****************************************************************************
bool opiskelijan_nimi_pienempi(const Opiskelija op1,
                               const Opiskelija op2)
{
    return op1.nimi < op2.nimi;
}


// ***** TODO *****************************************************************
// Toteuta tähän kohtaan vertailufunktio algorithm-kirjaston
// sort-funktiota varten.  Funktion on osattava vertailla kahta
// Opiskelija-tyyppiseen struct:iin osoittavaa osoitinta siten,
// että pienemmäksi tulkitaan se niistä, joka osoittaa opiskelija-
// numeroltaan pienempään opiskelijaan.
// ****************************************************************************
bool opiskelijan_numero_pienempi(const Opiskelija* op1,
                               const Opiskelija* op2)
{
    return op1->opnum < op2->opnum;
}


int main() {
    vector<Opiskelija> oprek = {
        { "Teekkari, Tiina",           52401 },
        { "Ylikuuskajaskari, Jaska",  186112 },
        { "Repolainen, Reijo",        117118 },
        { "Teekkari, Teemu",          196196 },
        { "Santaholma, Santtu",       173421 },
    };

    vector<Opiskelija*> opiskelijaosoittimet = { };

    // Laitetaan opiskelijaosoittimet-vektoriin kaikkien oprek:iin
    // talletettujen opiskelijoiden muistiosoitteet.
    for ( vector<Opiskelija>::size_type i = 0; i < oprek.size(); ++i ) {
        opiskelijaosoittimet.push_back( &oprek.at(i) );
    }



    // ***** TODO *************************************************************
    // Käytä tässä kohdassa algorithm-kirjaston sort-funktiota siten,
    // että saat oprek-vektorissa olevat opiskelijat järjestetty
    // nimi-kentän mukaiseen kasvavaan aakkosjärjestykseen.
    // ************************************************************************
    sort(oprek.begin(), oprek.end(), opiskelijan_nimi_pienempi);


    // ***** TODO *************************************************************
    // Käytä tässä kohdassa algorithm-kirjaston sort-funktiota siten,
    // että saat opiskelijaosoittimet-vektorissa olevat osoittimet
    // järjestettyä siten, että ne ovat osoittamiensa opiskelijoiden
    // mukaisessa kasvavassa opiskelijanumerojärjestyksessä.
    // ************************************************************************
    sort(opiskelijaosoittimet.begin(), opiskelijaosoittimet.end(),
         opiskelijan_numero_pienempi);


    //------------------------------------------------------------------//
    // Tässä kohdassa kumpikin vektori on järjestetty oman vertailu-    //
    // kriteerinsä perusteella kasvavaan järjestykseen. Tätä tilannetta //
    // havainnollistetaan tehtävänannon kuvassa, joka esittää           //
    // lajittelun jälkeistä lopputilannetta.                            //
    //------------------------------------------------------------------//



    // Tulostetaan opiskelijoiden tiedot näytölle kuumankin edellä
    // lajitellun vektorin avulla, jotta nähdään onko lajittelu onnistunut.

    cout << "Opiskelijat nimen mukaisessa järjestyksessa:" << endl;
    cout << "--------------------------------------------" << endl;
    for ( Opiskelija opisk : oprek ) {
        cout << setw(24) << left << opisk.nimi
             << setw(6) << right << opisk.opnum << endl;
    }

    cout << endl;

    cout << "Opiskelijat numeron mukaisessa järjestyksessa:" << endl;
    cout << "----------------------------------------------" << endl;
    for ( Opiskelija* opisk_ptr : opiskelijaosoittimet ) {
        cout << setw(24) << left << opisk_ptr->nimi
             << setw(6) << right << opisk_ptr->opnum << endl;
    }
}
