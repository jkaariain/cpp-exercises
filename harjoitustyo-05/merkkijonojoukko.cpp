// harjoitustyo-05
#include "merkkijonojoukko.hh"
#include <iostream>
#include <algorithm>

MerkkijonoJoukko::MerkkijonoJoukko() :
    alku_(nullptr), loppu_(nullptr)
{

}

MerkkijonoJoukko::~MerkkijonoJoukko()
{
    this->tyhjenna();
}

bool MerkkijonoJoukko::tyhja() const
{
    return alku_ == nullptr;
}

bool MerkkijonoJoukko::lisaa(string merkkijono)
{
    if (this->onko_joukossa(merkkijono))
        return false;

    Alkio* uusi = new Alkio;
    uusi->data = merkkijono;

    if (alku_ == nullptr)
    {
        alku_ = uusi;
        loppu_ = uusi;
        loppu_->seuraava = nullptr;
    } else {
        loppu_->seuraava = uusi;
        loppu_ = uusi;
        loppu_->seuraava = nullptr;
    }

    return true;
}

void MerkkijonoJoukko::jarjesta()
{
    if (tyhja() || koko() == 1)
        return;

    // Valintalajittelu
    for (Alkio* iter = alku_; iter->seuraava != nullptr;
         iter = iter->seuraava)
    {
        for (Alkio* valinta = iter->seuraava; valinta != nullptr;
             valinta = valinta->seuraava)
        {
            if (iter->data > valinta->data)
                swap(iter->data, valinta->data);
        }
    }
}

void MerkkijonoJoukko::tulosta() const
{
    if (tyhja())
        return;

    Alkio* iter = alku_;

    while (iter != nullptr)
    {
        cout << iter->data << endl;
        iter = iter->seuraava;
    }
}

bool MerkkijonoJoukko::poista_alusta()
{
    if (this->tyhja())
        return false;

    if (alku_->seuraava == nullptr){
        delete alku_;
        alku_ = nullptr;
        loppu_ = nullptr;
    } else {
        Alkio* temp = alku_->seuraava;
        delete alku_;
        alku_ = temp;
    }

    return true;
}

bool MerkkijonoJoukko::onko_joukossa(string merkkijono) const
{
    if (this->tyhja())
        return false;

    Alkio* iter = alku_;

    while (iter != nullptr)
    {
        if (iter->data == merkkijono)
            return true;
        iter = iter->seuraava;
    }

    return false;
}

int MerkkijonoJoukko::koko() const
{
    Alkio* iter = alku_;
    int koko = 0;

    if (tyhja())
        return koko;

    while (iter != nullptr){
        koko++;
        iter = iter->seuraava;
    }

    return koko;
}

void MerkkijonoJoukko::tyhjenna()
{
    while (this->poista_alusta());
}

Iteraattori::Iteraattori(Alkio *alkio)
{
    alkio_ = alkio;
}

Iteraattori& Iteraattori::operator ++()
{
    alkio_ = alkio_->seuraava;
    return *this;
}

Iteraattori Iteraattori::operator ++(int)
{
    Iteraattori temp(*this);
    ++(*this);
    return temp;
}

bool Iteraattori::operator ==(const Iteraattori& rhs)
{
    return alkio_ == rhs.alkio_;
}

bool Iteraattori::operator !=(const Iteraattori& rhs)
{
    return alkio_ != rhs.alkio_;
}

string& Iteraattori::operator *()
{
    return alkio_->data;
}

Alkio* MerkkijonoJoukko::alku()
{
    return alku_;
}

Alkio* MerkkijonoJoukko::loppu()
{
    return loppu_->seuraava;
}
