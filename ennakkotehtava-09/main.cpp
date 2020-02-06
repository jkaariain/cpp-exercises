#include <iostream>
#include "pino.hh"

using namespace std;

int main()
{
    Pino testipino;
    int arvo;

    cout << boolalpha;

    cout << "Tyhjä: ";
    cout << testipino.empty() << endl;
    testipino.print();

    testipino.push_front(1);
    testipino.push_front(2);
    testipino.push_front(3);
    testipino.push_front(4);
    testipino.push_front(5);

    cout << "Tyhjä: ";
    cout << testipino.empty() << endl;
    testipino.print();

    cout << "Pino: ";
    testipino.print();

    cout << "Koko: " << testipino.koko() << endl;

    testipino.pop_front(arvo);
    cout << "Poistettu arvo: " << arvo << endl;
    cout << "Koko: " << testipino.koko() << endl;

    cout << "Tyhjä: ";
    cout << testipino.empty() << endl;

    cout << "Pino: ";
    testipino.print();

    cout << "Takaperin: ";
    testipino.takaperin();
    testipino.print();

    return 0;
}
