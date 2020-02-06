#include "pino.hh"
#include <iostream>
using namespace std;

Pino::Pino()
{
    alkiot = nullptr;
    ensimmainen_osoite_ = nullptr;
    koko_ = 0;
}

Pino::~Pino()
{
    if (this->empty())
        return;

    delete [] alkiot;
    ensimmainen_osoite_ = nullptr;
}

int Pino::koko() const
{
    return koko_;
}

bool Pino::empty() const
{
    return ensimmainen_osoite_ == nullptr;
}

int& Pino::top()
{
    return *ensimmainen_osoite_;
}

void Pino::push_front(int lisattava_arvo)
{
    if (this->empty())
    {
        koko_++;
        alkiot = new int[1];
        alkiot[0] = lisattava_arvo;
        ensimmainen_osoite_ = alkiot;
    } else {
        koko_++;
        int* uusi_alkiot = new int[koko_];

        for (int i = 0; i < koko_-1; i++)
            uusi_alkiot[i] = alkiot[i];

        uusi_alkiot[koko_-1] = lisattava_arvo;
        delete [] alkiot;
        alkiot = nullptr;

        alkiot = uusi_alkiot;
        ensimmainen_osoite_ = uusi_alkiot + (koko_ - 1);
    }
}

bool Pino::pop_front(int &poistettu_arvo)
{
    if (this->empty())
        return false;

    poistettu_arvo = alkiot[koko_-1];

    if (koko_ == 1)
    {
        delete [] alkiot;
        ensimmainen_osoite_ = nullptr;
        koko_--;
        return true;
    }

    koko_--;
    int* uusi_alkiot = new int[koko_];

    for (int i = 0; i < koko_; i++)
        uusi_alkiot[i] = alkiot[i];

    delete [] alkiot;
    alkiot = uusi_alkiot;
    ensimmainen_osoite_ = uusi_alkiot + koko_ - 1;

    return true;
}

void Pino::takaperin()
{
    int* uusi_alkiot = new int[koko_];

    for (int i = 0; i < koko_; i++)
        uusi_alkiot[i] = alkiot[koko_-i-1];

    delete [] alkiot;
    alkiot = uusi_alkiot;
    ensimmainen_osoite_ = uusi_alkiot + koko_ - 1;
}

void Pino::print() const
{
    if (this->empty())
        return;

    for (unsigned int i = koko_; i > 0; i--)
        cout << alkiot[i-1] << " ";

    cout << endl;
}
