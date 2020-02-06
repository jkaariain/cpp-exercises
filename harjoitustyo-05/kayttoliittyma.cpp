// harjoitustyo-05
#include "kayttoliittyma.hh"
#include <iostream>
#include <regex>
using namespace std;

Kayttoliittyma::Kayttoliittyma() : lopeta_(false)
{

}

void Kayttoliittyma::tulosta_virhe(string viesti) const
{
    cout << "Virhe: " << viesti << endl;
}

void Kayttoliittyma::suorita()
{
    // Lue resepti-tiedosto
    if (!reseptit_.lue_tiedosto())
    {
        this->tulosta_virhe("Tiedostoa ei voitu lukea.");
        return;
    } else {
        cout << "Tuotantoketjut luettu onnistuneesti." << endl;
    }

    // Pääsilmukka
    cout << "testikayttoliittyma> ";

    while (getline(cin, syotevirta_))
    {
        kasittele_komento(syotevirta_);

        if (lopeta_)
            break;

        cout << "testikayttoliittyma> ";
    }
}

void Kayttoliittyma::kasittele_komento(string komento)
{
    const regex TYHJA_REGEX("[[:space:]]*");
    const regex LOPPU_REGEX("[[:space:]]*loppu[[:space:]]*");
    const regex REPPU_REGEX("[[:space:]]*reppu[[:space:]]*"
                            "([[:space:]]+[a-zA-Z_]+)*[[:space:]]*");
    const regex ASKARRELTAVISSA_REGEX("[[:space:]]*askarreltavissa"
                                      "[[:space:]]+[a-zA-Z_]+[[:space:]]*");
    const regex ASKARRELTAVISSA_BONUS_REGEX("[[:space:]]*askarreltavissa_bonus"
                                            "[[:space:]]+[a-zA-Z_]+[[:space:]]*");
    const regex MATERIAALIT_REGEX("[[:space:]]*materiaalit"
                                  "[[:space:]]+[a-zA-Z_]+[[:space:]]*");
    const regex TULOSTAREPPU_REGEX("[[:space:]]*tulostareppu[[:space:]]*");

    if (regex_match(komento, LOPPU_REGEX)){ // lopeta
        lopeta_ = true;
    } else if (regex_match(komento, REPPU_REGEX)){ // reppu mat1 mat2 mat3 ...
        regex argumentti("[a-zA-Z_]+");
        string edellinen_materiaali;

        reppu_.tyhjenna();

        for (sregex_iterator iter =
             sregex_iterator(komento.begin(), komento.end(), argumentti);
             iter != sregex_iterator(); ++iter)
        {
            smatch m = *iter;
            string materiaali = m.str();

            edellinen_materiaali = materiaali;

            if (materiaali == "reppu")
                continue;

            if (!reseptit_.hae_kaikki_materiaalit()->onko_joukossa(materiaali))
            {
                tulosta_virhe("Tuntematon esine tai materiaali syotteessa");
                reppu_.tyhjenna();
                return;
            }

            if (!reppu_.lisaa(materiaali))
            {
                tulosta_virhe("Sama esine tai materiaali"
                              " esiintyi useasti syotteessa");
                reppu_.tyhjenna();
                return;
            }
        }

        if (edellinen_materiaali != "reppu")
            cout << "Repun sisalto asetettu." << endl;
        else
            cout << "Reppu tyhjennetty." << endl;
    } else if (regex_match(komento, TULOSTAREPPU_REGEX)){ // tulostareppu
        reppu_.tulosta();
    } else if (regex_match(komento, TYHJA_REGEX)){ // pelkkää tyhjää syötteessä
        return;
    } else if (regex_match(komento, ASKARRELTAVISSA_REGEX)){
        // askarreltavissa "esine"
        regex argumentti("[a-zA-Z_]+");
        string askarreltava;

        for (sregex_iterator iter =
             sregex_iterator(komento.begin(), komento.end(), argumentti);
             iter != sregex_iterator(); ++iter)
        {
            smatch m = *iter;
            askarreltava = m.str();

            if (askarreltava == "askarreltavissa")
                continue;
        }

        int voi_askarrella = askarreltavissa(askarreltava);

        if (voi_askarrella == 1)
            cout << "On askarreltavissa." << endl;
        else if (voi_askarrella == 0)
            cout << "Ei ole askarreltavissa." << endl;

    } else if (regex_match(komento, ASKARRELTAVISSA_BONUS_REGEX)){
        // askarreltavissa_bonus "esine"
        regex argumentti("[a-zA-Z_]+");
        string askarreltava;

        for (sregex_iterator iter =
             sregex_iterator(komento.begin(), komento.end(), argumentti);
             iter != sregex_iterator(); ++iter)
        {
            smatch m = *iter;
            askarreltava = m.str();

            if (askarreltava == "askarreltavissa")
                continue;
        }

        int voi_askarrella = askarreltavissa_bonus(askarreltava);

        if (voi_askarrella == 1)
            cout << "On askarreltavissa." << endl;
        else if (voi_askarrella == 0)
            cout << "Ei ole askarreltavissa." << endl;
    } else if (regex_match(komento, MATERIAALIT_REGEX)) {
        // materiaalit "esine"
        regex argumentti("[a-zA-Z_]+");
        string esine;

        for (sregex_iterator iter =
             sregex_iterator(komento.begin(), komento.end(), argumentti);
             iter != sregex_iterator(); ++iter)
        {
            smatch m = *iter;
            esine = m.str();

            if (esine == "materiaalit")
                continue;
        }

        materiaalit(esine);
    } else {
        tulosta_virhe("Tuntematon tai virheellinen komento.");
    }
}

void Kayttoliittyma::materiaalit(string esine)
{
    MerkkijonoJoukko* materiaalit;
    materiaalit = reseptit_.hae_materiaalit(esine);

    if (!reseptit_.onko_resepti_kokoelmassa(esine)){
        tulosta_virhe("Materiaalia tai esinetta ei ole olemassa");
        return;
    }

    materiaalit->jarjesta();
    materiaalit->tulosta();
}

int Kayttoliittyma::askarreltavissa(string materiaali)
{
    MerkkijonoJoukko* tarvittavat_materiaalit;
    int voi_askarrella = 1;

    if (!reseptit_.onko_resepti_kokoelmassa(materiaali))
    {
        tulosta_virhe("Materiaalia tai esinetta ei ole olemassa");
        return -1;
    }

    tarvittavat_materiaalit = reseptit_.hae_materiaalit(materiaali);
    Iteraattori it(tarvittavat_materiaalit->alku());

    // Jos materiaali on repussa, esineen voi "askarrella"
    if (reppu_.onko_joukossa(materiaali))
        return voi_askarrella;
    else if (!tarvittavat_materiaalit->tyhja())
    {
        for (; it != tarvittavat_materiaalit->loppu(); it++)
        {
            // Jos yksikin tarvittava materiaali puuttuu,
            // esinettä ei voi askarrella.
            if(!reppu_.onko_joukossa(*it)){
                voi_askarrella = 0;
                break;
            }
        }
    } else {
        // Jos esineellä ei ole tarvittavia materiaaleja eikä se ole repussa,
        // esinettä ei voi askarrella.
        voi_askarrella = 0;
    }

    return voi_askarrella;
}

int Kayttoliittyma::askarreltavissa_bonus(string materiaali)
{
    if (!reseptit_.onko_resepti_kokoelmassa(materiaali))
    {
        tulosta_virhe("Materiaalia tai esinetta ei ole olemassa");
        return -1;
    }

    MerkkijonoJoukko* tarvittavat_materiaalit;
    tarvittavat_materiaalit = reseptit_.hae_materiaalit(materiaali);
    int voi_askarrella = 1;

    // Jos esinettä ei voi askarrella ja sillä on tarvittavia materiaaleja.
    if (askarreltavissa(materiaali) == 0 && !tarvittavat_materiaalit->tyhja())
    {
        for (Iteraattori iter = tarvittavat_materiaalit->alku();
             iter != tarvittavat_materiaalit->loppu();
             iter++)
        {
            // Hae tarkasteltavan materiaalin tarvittavat materiaalit.
            MerkkijonoJoukko* tarvittavat_materiaalit_2 =
                    reseptit_.hae_materiaalit(*iter);

            if (askarreltavissa(*iter) == 0 &&
                    tarvittavat_materiaalit_2->tyhja())
            {
                // Jos tarkasteltavaa materiaalia ei voi askarrella, eikä
                // sillä ole tarvittavia materiaaleja.
                // Esinettä ei voi askarrella.
                voi_askarrella = 0;
                break;
            } else {
                // Jos tarkasteltavalla materiaalilla on
                // tarvittavia materiaaleja,
                // eikä niitäkään voi askarrella.
                // Esinettä ei voi askarrella.
                if (askarreltavissa_bonus(*iter) == 0)
                {
                    voi_askarrella = 0;
                    break;
                }
            }
        }
    }

    return voi_askarrella;
}
