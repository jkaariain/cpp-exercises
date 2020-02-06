#ifndef LISTA_HH
#define LISTA_HH

#include <string>
using namespace std;

class Lista
{
public:
    Lista();
    ~Lista();

    void lisaa_alkio_loppuun(const string& lisattava_tehtava);
    bool poista_alkio_alusta(string& poistettu_tehtava);
    bool poista_alkio(const string& poistettava_tehtava);
    bool onko_tyhja() const;
    void tulosta() const;

private:
    struct Listan_Alkio {
        string tehtava;
        Listan_Alkio* seuraavan_osoite;
    };

    Listan_Alkio* ensimmaisen_osoite_;
    Listan_Alkio* viimeisen_osoite_;
};

#endif // LISTA_HH
