#ifndef REPPU_HH
#define REPPU_HH

#include "merkkijonojoukko.hh"
#include "reseptikokoelma.hh"

class Reppu
{
public:
    Reppu();

    bool aseta_sisalto(MerkkijonoJoukko sisalto);

    void tyhjenna();

    void tulosta_sisalto() const;
private:
    MerkkijonoJoukko sisalto_;
};

#endif // REPPU_HH
