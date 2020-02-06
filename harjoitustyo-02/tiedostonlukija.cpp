/* harjoitustyo-02
 */
#include "tiedostonlukija.hh"
#include <iostream>

Tiedostonlukija::Tiedostonlukija()
{
    tiedosto_avattu_ = false;
}

Tiedostonlukija::Tiedostonlukija(const string& tiedoston_nimi)
{
    if (avaa_tiedosto(tiedoston_nimi))
        tiedosto_avattu_ = true;
    else
        tiedosto_avattu_ = false;
}

Tiedostonlukija::~Tiedostonlukija()
{
    // Sulje tiedosto
    tiedosto_.close();
}

bool Tiedostonlukija::avaa_tiedosto(const string& tiedoston_nimi)
{
    // Avaa tiedosto
    tiedosto_.open(tiedoston_nimi);

    // Tarkista, onko tiedosto avattu.
    if (tiedosto_.is_open())
    {
        tiedosto_avattu_ = true;
    }
    else // Virhe tiedoston avaamisessa.
    {
        tiedosto_avattu_= false;
        return false;
    }

    if (!tarkista_tiedoston_eheys_ja_tallenna_tietorakenteeseen_()){
        tiedosto_avattu_ = false;
        return false;
    }

    tiedosto_.close();
    return true;
}

bool Tiedostonlukija::tarkista_tiedoston_eheys_ja_tallenna_tietorakenteeseen_()
{
    vector<string>::const_iterator iter;
    Tuote tuote;

    while (getline(tiedosto_, rivi_)){
        paloittelija_.aseta_paloiteltava_merkkijono(rivi_);
        paloittelija_.paloittele(';', false);

        if (paloittelija_.kenttien_lukumaara() != 4)
            return false;

        // Tarkista etteivät kentät ole tyhjiä.
        unsigned int iter = 0;

        while (iter < paloittelija_.kenttien_lukumaara())
        {
            if (paloittelija_.hae_kentta(iter++) == "")
                return false;
        }

        string kaupan_nimi = paloittelija_.hae_kentta(0);
        string paikkakunnan_nimi = paloittelija_.hae_kentta(1);
        tuote.tuotenimi = paloittelija_.hae_kentta(2);

        try
        {
            tuote.hinta = stod(paloittelija_.hae_kentta(3));
        } catch (invalid_argument){
            tuote.hinta = -1.0; // Tuote loppu
        }

        tuotenimet_.insert(tuote.tuotenimi);

        vector<Tuote>::iterator vec_iter =
                tietorakenne_[kaupan_nimi][paikkakunnan_nimi].begin();

        // Eliminoi saman tuotteen toistuminen tiedostossa.
        while (vec_iter != tietorakenne_[kaupan_nimi][paikkakunnan_nimi].end())
        {
            if (vec_iter->tuotenimi == tuote.tuotenimi)
            {
                tietorakenne_[kaupan_nimi][paikkakunnan_nimi].erase(vec_iter);
                break;
            }

            vec_iter++;
        }

        tietorakenne_[kaupan_nimi][paikkakunnan_nimi].push_back(tuote);

    }

    return true;
}

map<string, map<string, vector<Tuote>>>& Tiedostonlukija::anna_tietorakenne()
{
    return tietorakenne_;
}

set<string>& Tiedostonlukija::anna_tuotenimet()
{
    return tuotenimet_;
}
