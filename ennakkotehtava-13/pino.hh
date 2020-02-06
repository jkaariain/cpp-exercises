#ifndef PINO_HH
#define PINO_HH

#include <iostream>

using namespace std;

template <class T>
class Pino
{
public:
    Pino();
    ~Pino();

    bool empty() const;
    void push_front(T lisattava_arvo);
    bool pop_front(T& poistettu_arvo);

    void print() const;
    int koko() const;
    void takaperin();
    T& top();
private:
    T* alkiot;
    T* ensimmainen_osoite_;
    int koko_;
};

#endif // PINO_HH

template <class T>
Pino<T>::Pino()
{
    alkiot = nullptr;
    ensimmainen_osoite_ = nullptr;
    koko_ = 0;
}

template <class T>
Pino<T>::~Pino()
{
    if (this->empty())
        return;

    delete [] alkiot;
    ensimmainen_osoite_ = nullptr;
}

template <class T>
int Pino<T>::koko() const
{
    return koko_;
}

template <class T>
bool Pino<T>::empty() const
{
    return ensimmainen_osoite_ == nullptr;
}

template <class T>
T& Pino<T>::top()
{
    return *ensimmainen_osoite_;
}

template <class T>
void Pino<T>::push_front(T lisattava_arvo)
{
    if (this->empty())
    {
        koko_++;
        alkiot = new T[1];
        alkiot[0] = lisattava_arvo;
        ensimmainen_osoite_ = alkiot;
    } else {
        koko_++;
        T* uusi_alkiot = new T[koko_];

        for (int i = 0; i < koko_-1; i++)
            uusi_alkiot[i] = alkiot[i];

        uusi_alkiot[koko_-1] = lisattava_arvo;
        delete [] alkiot;
        alkiot = nullptr;

        alkiot = uusi_alkiot;
        ensimmainen_osoite_ = uusi_alkiot + (koko_ - 1);
    }
}

template <class T>
bool Pino<T>::pop_front(T &poistettu_arvo)
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
    T* uusi_alkiot = new T[koko_];

    for (int i = 0; i < koko_; i++)
        uusi_alkiot[i] = alkiot[i];

    delete [] alkiot;
    alkiot = uusi_alkiot;
    ensimmainen_osoite_ = uusi_alkiot + koko_ - 1;

    return true;
}

template <class T>
void Pino<T>::takaperin()
{
    int* uusi_alkiot = new int[koko_];

    for (int i = 0; i < koko_; i++)
        uusi_alkiot[i] = alkiot[koko_-i-1];

    delete [] alkiot;
    alkiot = uusi_alkiot;
    ensimmainen_osoite_ = uusi_alkiot + koko_ - 1;
}

template <class T>
void Pino<T>::print() const
{
    if (this->empty())
        return;

    for (unsigned int i = koko_; i > 0; i--)
        cout << alkiot[i-1] << " ";

    cout << endl;
}
