#include "lista.hh"
#include <iostream>
#include <string>
using namespace std;

Lista::Lista() : ensimmaisen_osoite_(nullptr), viimeisen_osoite_(nullptr) {

}

Lista::~Lista() {
    Listan_Alkio* vapautettavan_osoite;

    while ( ensimmaisen_osoite_ != nullptr ) {
        vapautettavan_osoite = ensimmaisen_osoite_;
        ensimmaisen_osoite_ = ensimmaisen_osoite_->seuraavan_osoite;
        delete vapautettavan_osoite;
    }
}

void Lista::tulosta() const {
    Listan_Alkio* tulostettavan_osoite = ensimmaisen_osoite_;
    int jarjestysnumero = 1;

    while ( tulostettavan_osoite != nullptr ) {
        cout << jarjestysnumero << ". "
             << tulostettavan_osoite->tehtava << endl;
        ++jarjestysnumero;
        tulostettavan_osoite = tulostettavan_osoite->seuraavan_osoite;
    }
}

void Lista::lisaa_alkio_loppuun(const string &lisattava_tehtava) {
    Listan_Alkio* uuden_osoite = new Listan_Alkio{lisattava_tehtava, nullptr};

    if ( ensimmaisen_osoite_ == nullptr ) {
        ensimmaisen_osoite_ = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite;
    } else {
        viimeisen_osoite_->seuraavan_osoite = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite;
    }
}

bool Lista::poista_alkio_alusta(string &poistettu_tehtava) {
    if ( onko_tyhja() ) {
        return false;
    }

    Listan_Alkio* poistettavan_osoite = ensimmaisen_osoite_;

    poistettu_tehtava = poistettavan_osoite->tehtava;

    if ( ensimmaisen_osoite_ == viimeisen_osoite_ ) {
        ensimmaisen_osoite_ = nullptr;
        viimeisen_osoite_ = nullptr;
    } else {
        ensimmaisen_osoite_ = ensimmaisen_osoite_->seuraavan_osoite;
    }

    delete poistettavan_osoite;

    return true;
}

bool Lista::poista_alkio(const string &poistettava_tehtava) {
    if ( onko_tyhja() )
        return false;
    else if ( ensimmaisen_osoite_->tehtava == poistettava_tehtava
              && ensimmaisen_osoite_ == viimeisen_osoite_ ) {
        // Ainoa alkio
        delete ensimmaisen_osoite_;
        ensimmaisen_osoite_ = nullptr;
        viimeisen_osoite_ = nullptr;
    } else if ( ensimmaisen_osoite_->tehtava == poistettava_tehtava ) {
        // Alkio on listan alussa
        Listan_Alkio* poistettava = ensimmaisen_osoite_;
        ensimmaisen_osoite_ = ensimmaisen_osoite_->seuraavan_osoite;
        delete poistettava;
        poistettava = nullptr;
    } else if ( viimeisen_osoite_->tehtava == poistettava_tehtava ) {
        // Alkio on listan lopussa
        Listan_Alkio* edeltajan_osoite = ensimmaisen_osoite_;
        while (edeltajan_osoite->seuraavan_osoite != viimeisen_osoite_) {
            edeltajan_osoite = edeltajan_osoite->seuraavan_osoite;
        }
        delete viimeisen_osoite_;
        viimeisen_osoite_ = edeltajan_osoite;
        viimeisen_osoite_->seuraavan_osoite = nullptr;
    } else {
        // Alkion poistaminen listan keskelta
        Listan_Alkio* edeltajan_osoite = ensimmaisen_osoite_;
        Listan_Alkio* poistettavan_osoite = ensimmaisen_osoite_;
        Listan_Alkio* seuraajan_osoite = ensimmaisen_osoite_;

        while (poistettavan_osoite->tehtava != poistettava_tehtava) {
            if (poistettavan_osoite->seuraavan_osoite == nullptr)
                return false;

            poistettavan_osoite = poistettavan_osoite->seuraavan_osoite;
        }

        while (edeltajan_osoite->seuraavan_osoite != poistettavan_osoite)
            edeltajan_osoite = edeltajan_osoite->seuraavan_osoite;

        while (poistettavan_osoite->seuraavan_osoite != seuraajan_osoite){
            if (seuraajan_osoite->seuraavan_osoite == nullptr)
                break;

            seuraajan_osoite = seuraajan_osoite->seuraavan_osoite;
        }

        edeltajan_osoite->seuraavan_osoite = seuraajan_osoite;
        delete poistettavan_osoite;
    }

    return true;
}

//bool Lista::poista_alkio(const string &poistettava_tehtava) {
//    if ( onko_tyhja() )
//        return false;

//    Listan_Alkio* poistettavan_osoite = ensimmaisen_osoite_;

//    // Etsi tehtavan osoite
//    while ( poistettavan_osoite->tehtava != poistettava_tehtava ) {
//        if ( poistettavan_osoite->seuraavan_osoite == nullptr )
//            break;

//        poistettavan_osoite = poistettavan_osoite->seuraavan_osoite;
//    }

//    if ( poistettavan_osoite->tehtava != poistettava_tehtava )
//        return false;

//    if ( poistettavan_osoite == viimeisen_osoite_ &&
//         poistettavan_osoite == ensimmaisen_osoite_ ) {
//        // Ainoa alkio.
//        ensimmaisen_osoite_ = nullptr;
//        viimeisen_osoite_ = nullptr;
//    } else if ( poistettavan_osoite == viimeisen_osoite_ ) {
//        // Jos alkio on listan lopussa.
//        viimeisen_osoite_ = poistettavan_osoite->edellisen_osoite;
//        viimeisen_osoite_->seuraavan_osoite = nullptr;
//    } else if ( poistettavan_osoite == ensimmaisen_osoite_ ) {
//        // Jos alkio on listan alussa.
//        ensimmaisen_osoite_ = ensimmaisen_osoite_->seuraavan_osoite;
//        ensimmaisen_osoite_->edellisen_osoite = nullptr;
//    } else {
//        // Jos alkio on listan keskellä.
//        poistettavan_osoite->edellisen_osoite->seuraavan_osoite
//                = poistettavan_osoite->seuraavan_osoite;
//        poistettavan_osoite->seuraavan_osoite->edellisen_osoite
//                = poistettavan_osoite->edellisen_osoite;
//    }

//    delete poistettavan_osoite;

//    return true;
//}

bool Lista::onko_tyhja() const {
    if ( ensimmaisen_osoite_ == nullptr ) {
        return true;
    } else {
        return false;
    }
}
