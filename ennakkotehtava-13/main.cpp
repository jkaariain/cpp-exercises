#include "pino.hh"
#include <iostream>

using namespace std;

int main()
{
    Pino<int> pino;
    cout << "Koko: " << pino.koko() << endl;

    for (int i = 0; i < 80; i++)
        pino.push_front(i);

    int luku;

    pino.print();

    cout << pino.top() << endl;
    //cout << "Takaperin:" << endl;
    //pino.takaperin();
    //pino.print();
    cout << "Koko: " << pino.koko() << endl;

    while (pino.koko() > 0){
        pino.pop_front(luku);
        pino.print();
    }

    cout << "Koko: " << pino.koko() << endl;

    pino.print();

    return 0;
}
