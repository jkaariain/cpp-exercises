#include "reppu.hh"

Reppu::Reppu()
{

}

void Reppu::tulosta_sisalto() const
{
    sisalto_.tulosta();
}


void Reppu::tyhjenna()
{
    sisalto_tyhjenna();
}
