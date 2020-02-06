#include <iostream>
#include <string>
#include <regex>
#include <iomanip>

using namespace std;

int main()
{
    string pvm;
    regex PVM_REGEX("^\\s*(\\d{1,2})\\.(\\d{1,2})\\.(\\d{4})\\s*$");
    smatch pvm_tulos;

    cout << "Syota paivamaara (pp.kk.vvvv): ";
    getline(cin, pvm);

    if (!regex_match(pvm, pvm_tulos, PVM_REGEX))
    {
        cout << "Virheellinen syote.\n" << endl;
        return -1;
    }

    int paiva = stoi(pvm_tulos.str(1));
    int kuukausi = stoi(pvm_tulos.str(2));
    int vuosi = stoi(pvm_tulos.str(3));

    cout << setfill('0') << setw(4) << vuosi << "-" << setw(2)
         << kuukausi << "-" << setw(2) << paiva << endl;

    return 0;
}
