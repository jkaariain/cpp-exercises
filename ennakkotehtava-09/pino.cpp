#include "pino.hh"
#include <iostream>
using namespace std;

Pino::Pino(): ensimmainen_osoite_(nullptr){

}

Pino::~Pino(){
    int arvo;

    while (!this->empty())
        this->pop_front(arvo);
}

bool Pino::empty() const{
    return ensimmainen_osoite_ == nullptr;
}

void Pino::push_front(int lisattava_arvo){
    Alkio* uusi = new Alkio;

    uusi->data = lisattava_arvo;

    if (this->empty()){
        uusi->seuraava_ptr = nullptr;
        ensimmainen_osoite_ = uusi;
    } else {
        uusi->seuraava_ptr = ensimmainen_osoite_;
        ensimmainen_osoite_ = uusi;
    }
}

bool Pino::pop_front(int &poistettu_arvo){
    if (this->empty())
        return false;

    poistettu_arvo = ensimmainen_osoite_->data;

    Alkio* ptr = ensimmainen_osoite_;
    ensimmainen_osoite_ = ensimmainen_osoite_->seuraava_ptr;
    delete ptr;

    return true;
}

void Pino::print() const{
    if (this->empty())
        return;

    Alkio* ptr = ensimmainen_osoite_;

    while (ptr->seuraava_ptr != nullptr){
        cout << ptr->data << " ";
        ptr = ptr->seuraava_ptr;
    }

    cout << ptr->data << " ";

    cout << endl;
}

int Pino::koko() const{
    int koko = 0;

    if (this->empty())
        return koko;

    Alkio* ptr = ensimmainen_osoite_;

    while (ptr->seuraava_ptr != nullptr){
        koko++;
        ptr = ptr->seuraava_ptr;
    }

    return koko + 1;
}

void Pino::takaperin(){
    Alkio* uuden_ensimmainen_ptr = nullptr;

    while (ensimmainen_osoite_ != nullptr){
        Alkio* siirrettavaptr = ensimmainen_osoite_;
        ensimmainen_osoite_ = ensimmainen_osoite_->seuraava_ptr;

        siirrettavaptr->seuraava_ptr = uuden_ensimmainen_ptr;
        uuden_ensimmainen_ptr = siirrettavaptr;
    }

    ensimmainen_osoite_ = uuden_ensimmainen_ptr;
}
