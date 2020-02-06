#include "lista.hh"
#include <iostream>

using namespace std;

int main() {
    Lista tyolista;
    string poistettu = "";

    tyolista.lisaa_alkio_loppuun("siivoa tyopoyta");
    tyolista.lisaa_alkio_loppuun("pese pyykit");
    tyolista.lisaa_alkio_loppuun("tee kotilaksyt");
    tyolista.lisaa_alkio_loppuun("tee laiskanlaksyt");
    tyolista.lisaa_alkio_loppuun("tee rahaa");

    tyolista.poista_alkio("siivoa tyopoyta");
    //tyolista.poista_alkio("pese pyykit");
    tyolista.poista_alkio("tee kotilaksyt");
    //tyolista.poista_alkio("tee laiskanlaksyt");
    tyolista.poista_alkio("tee rahaa");

    cout << "Tekemattomat askareet:" << endl;
    tyolista.tulosta();

    tyolista.lisaa_alkio_loppuun("tiskaa");
    tyolista.lisaa_alkio_loppuun("vie roskat");

    cout << endl << "Tekemattomat askareet:" << endl;
    tyolista.tulosta();

    while ( !tyolista.onko_tyhja() ) {
        tyolista.poista_alkio_alusta(poistettu);
        cout << "\tsuoritettu: " << poistettu << endl;
    }

    if ( tyolista.onko_tyhja() ) {
        cout << "Kaikki askareet suoritettu!" << endl;
    }

    return 0;
}
