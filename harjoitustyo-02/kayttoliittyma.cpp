/* harjoitustyo-02
 */
#include "kayttoliittyma.hh"
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>

Kayttoliittyma::Kayttoliittyma()
{
    lopeta_ = false;
    syote_ = "";

}

void Kayttoliittyma::tulosta_virhe(const string& viesti) const{
    cout << "Virhe: " << viesti << endl;
}

void Kayttoliittyma::suorita()
{
    if (!tiedostonlukija_.avaa_tiedosto("tuotetiedot.txt"))
    {
        tulosta_virhe("syotetiedostoa ei saatu luettua.");
        lopeta_ = true;
    }

    // Ohjelmasilmukka
    while (!lopeta_)
    {
        cout << "tuotehaku> ";
        getline(cin, syote_);

        paloittelija_.aseta_paloiteltava_merkkijono(syote_);
        paloittelija_.paloittele(' ', true);

        if (paloittelija_.kenttien_lukumaara() > 0)
            hae_komento(paloittelija_.hae_kentta(0));
    }
}

void Kayttoliittyma::hae_komento(const string& komennon_nimi)
{
    if (komennon_nimi == "lopeta"){
        lopeta_ = true;
    } else if (komennon_nimi == "kauppaketjut"){
        tulosta_kauppaketjut();
    } else if (komennon_nimi == "tuotenimet"){
        tulosta_tuotteet();
    } else if (komennon_nimi == "myymalat"){
        tulosta_myymalat();
    } else if (komennon_nimi == "halvin"){
        tulosta_halvin();
    } else if (komennon_nimi == "tuotevalikoima"){
        tulosta_tuotevalikoima();
    }
    else {
        tulosta_virhe("tuntematon komento.");
    }
}

void Kayttoliittyma::tulosta_kauppaketjut()
{
    if (paloittelija_.kenttien_lukumaara() != 1)
    {
        tulosta_virhe("virheellinen syote.");
        return;
    }

    for (auto iter : tiedostonlukija_.anna_tietorakenne())
        cout << iter.first << endl;
}

void Kayttoliittyma::tulosta_tuotteet()
{
    if (paloittelija_.kenttien_lukumaara() != 1)
    {
        tulosta_virhe("virheellinen syote.");
        return;
    }

    for (string nimi : tiedostonlukija_.anna_tuotenimet())
        cout << nimi << endl;
}

void Kayttoliittyma::tulosta_myymalat()
{
    if (paloittelija_.kenttien_lukumaara() != 2)
    {
        tulosta_virhe("virheellinen syote.");
        return;
    }

    string kaupan_nimi = paloittelija_.hae_kentta(1);
    auto iter = tiedostonlukija_.anna_tietorakenne().find(kaupan_nimi);

    if (iter == tiedostonlukija_.anna_tietorakenne().end())
    {
        tulosta_virhe("kauppaa ei loytynyt.");
        return;
    }

    for (auto iter : tiedostonlukija_.anna_tietorakenne()[kaupan_nimi])
        cout << iter.first << endl;
}

void Kayttoliittyma::tulosta_halvin()
{
    if (paloittelija_.kenttien_lukumaara() != 2)
    {
        tulosta_virhe("virheellinen syote.");
        return;
    }

    string tuotteen_nimi = paloittelija_.hae_kentta(1);

    if (tiedostonlukija_.anna_tuotenimet().find(tuotteen_nimi)
            == tiedostonlukija_.anna_tuotenimet().end())
    {
        cout << "Tuote ei kuulu valikoimiin." << endl;
        return;
    }

    double halvin = numeric_limits<double>::max();

    // Etsi halvin tuotteen hinta
    for (auto iter : tiedostonlukija_.anna_tietorakenne()) // kauppaketjut
    {
        for (auto iter2 : iter.second) // sijainnit
        {
            for (auto iter3 : iter2.second) // tuotteet
            {
                if (iter3.tuotenimi != tuotteen_nimi)
                    continue;
                else
                {
                    if (iter3.hinta >= 0 && iter3.hinta <= halvin)
                        halvin = iter3.hinta;
                }
            }
        }
    }

    // Jos tuote on tilapäisesti loppunut
    if (halvin == numeric_limits<double>::max())
    {
        cout << "Tuote on tilapaisesti loppu kaikkialta." << endl;
        return;
    }

    // Tulosta halvin hinta ja myymälät
    cout << setprecision(2) << fixed << halvin << " euroa" << endl;
    for (auto iter : tiedostonlukija_.anna_tietorakenne()) // kauppaketjut
    {
        for (auto iter2 : iter.second) // sijainnit
        {
            for (auto iter3 : iter2.second) // tuotteet
            {
                if (iter3.tuotenimi != tuotteen_nimi)
                    continue;
                else
                {
                    if (iter3.hinta == halvin)
                        cout << iter.first << " " << iter2.first << endl;
                }
            }
        }
    }
}

// Vertailufunktio Tuote-tietueille, joka
// järjestää tuotteiden nimet aakkosjärjestykseen
bool nimi_pienempi_kuin(const Tuote& x, const Tuote& y)
{
    return x.tuotenimi < y.tuotenimi;
}

void Kayttoliittyma::tulosta_tuotevalikoima()
{
    if (paloittelija_.kenttien_lukumaara() != 3)
    {
        tulosta_virhe("virheellinen syote.");
        return;
    }

    // Tarkista kaupan olemassaolo
    bool kauppa_loydetty = false;

    string kaupan_nimi = paloittelija_.hae_kentta(1);
    string paikkakunta = paloittelija_.hae_kentta(2);

    // Etsi kauppa
    for (auto iter : tiedostonlukija_.anna_tietorakenne()) // kaupat
    {
        for (auto iter2 : iter.second) // sijainnit
        {
            if (iter.first == kaupan_nimi && iter2.first == paikkakunta)
                kauppa_loydetty = true;

            if (kauppa_loydetty)
                break;
        }

        if (kauppa_loydetty)
            break;
    }

    if (!kauppa_loydetty)
    {
        tulosta_virhe("kauppaa ei loytynyt.");
        return;
    }

    // Tulosta tuotevalikoima
    vector<Tuote> valikoima = tiedostonlukija_.anna_tietorakenne()[kaupan_nimi][paikkakunta];
    sort(valikoima.begin(), valikoima.end(), nimi_pienempi_kuin); // Järjestä valikoima

    for (Tuote t : valikoima)
    {
        cout << t.tuotenimi << " ";

        if (t.hinta < 0.0)
            cout << "loppu" << endl;
        else
            cout << t.hinta << endl;
    }
}
