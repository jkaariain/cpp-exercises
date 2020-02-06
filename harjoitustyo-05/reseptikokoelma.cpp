// harjoitustyo-05
#include "reseptikokoelma.hh"
#include <iostream>
#include <fstream>
#include <regex>

ReseptiKokoelma::ReseptiKokoelma() : alku_(nullptr), loppu_(nullptr)
{

}

ReseptiKokoelma::~ReseptiKokoelma()
{
    this->tyhjenna();
}

bool ReseptiKokoelma::lue_tiedosto()
{
    const regex TYHJA_RIVI_REGEX("[[:space:]]*");
    const regex KOMMENTTI_RIVI_REGEX("[[:space:]]*#.*");
    const regex RESEPTI_RIVI_REGEX("[[:space:]]*([a-zA-Z_]+)[[:space:]]*"
                                   ":[[:space:]]*([a-zA-Z_]+)[[:space:]]*");

    string tiedoston_nimi;

    cout << "Syotetiedosto: ";
    getline(cin, tiedoston_nimi);

    ifstream tiedosto(tiedoston_nimi);

    if (!tiedosto.is_open()){
        return false;
    }

    string rivi;
    smatch tulos;
    while (getline(tiedosto, rivi))
    {
        if (regex_match(rivi, TYHJA_RIVI_REGEX)){
            continue;
        } else if (regex_match(rivi, KOMMENTTI_RIVI_REGEX)){
            continue;
        } else if (regex_match(rivi, tulos, RESEPTI_RIVI_REGEX)){
            string reseptin_nimi = tulos.str(1);
            string materiaali = tulos.str(2);

            if (!this->lisaa(reseptin_nimi, materiaali))
                return false;
        } else {
            return false;
        }
    }

    return true;
}

bool ReseptiKokoelma::onko_tyhja() const
{
    return alku_ == nullptr;
}

bool ReseptiKokoelma::onko_resepti_kokoelmassa(string reseptin_nimi) const
{
    if (onko_tyhja())
        return false;

    Resepti* iter = alku_;

    while (iter != nullptr)
    {
        if (iter->nimi == reseptin_nimi)
            return true;

        iter = iter->seuraava;
    }

    return false;
}

bool ReseptiKokoelma::lisaa(string reseptin_nimi, string materiaalin_nimi)
{
    // TODO: korjaa lisays-komento

    materiaalit_.lisaa(reseptin_nimi);
    materiaalit_.lisaa(materiaalin_nimi);

    // Lisää resepti kokoelmaan
    if (onko_tyhja()){
        Resepti* uusi = new Resepti;
        uusi->nimi = reseptin_nimi;
        uusi->materiaalit.lisaa(materiaalin_nimi);
        uusi->seuraava = nullptr;
        alku_ = uusi;
        loppu_ = uusi;
    } else if (onko_resepti_kokoelmassa(reseptin_nimi)) {
        // Lisää olemassaolevaan reseptiin uusi materiaali
        Resepti* iter = alku_;

        while (iter != nullptr)
        {
            if (iter->nimi == reseptin_nimi)
                break;

            iter = iter->seuraava;
        }

        if (!iter->materiaalit.lisaa(materiaalin_nimi))
            return false;
    } else {
        Resepti* uusi = new Resepti;
        uusi->nimi = reseptin_nimi;
        uusi->materiaalit.lisaa(materiaalin_nimi);
        loppu_->seuraava = uusi;
        loppu_ = uusi;
        uusi->seuraava = nullptr;
    }

    // Lisää materiaali resepteihin
    if (!onko_resepti_kokoelmassa(materiaalin_nimi))
    {
        Resepti* uusi = new Resepti;
        uusi->nimi = materiaalin_nimi;
        loppu_->seuraava = uusi;
        loppu_ = uusi;
        uusi->seuraava = nullptr;
    }

    return true;
}

bool ReseptiKokoelma::poista_alusta()
{
    if (onko_tyhja())
        return false;

    if (alku_->seuraava == nullptr){
        alku_->materiaalit.tyhjenna();
        delete alku_;
        alku_ = nullptr;
        loppu_ = nullptr;
    } else {
        Resepti* temp = alku_->seuraava;
        alku_->materiaalit.tyhjenna();
        delete alku_;
        alku_ = temp;
    }

    return true;
}

void ReseptiKokoelma::tyhjenna()
{
    while (poista_alusta());
}

MerkkijonoJoukko* ReseptiKokoelma::hae_materiaalit(string reseptin_nimi)
{
    Resepti* iter = alku_;

    while (iter != nullptr)
    {
        if (iter->nimi == reseptin_nimi){
            break;
        }

        iter = iter->seuraava;
    }

    if (iter == nullptr)
        return nullptr;

    return &(iter->materiaalit);
}

const MerkkijonoJoukko* ReseptiKokoelma::hae_kaikki_materiaalit() const
{
    return &materiaalit_;
}


