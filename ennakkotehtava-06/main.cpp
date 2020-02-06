#include <iostream>
#include <string>
#include <map>
using namespace std;

int laske_nimet(const map<string,string>& puhelinluettelo,
                char nimen_alkukirjain)
{
    int lukumaara = 0;
    map<string, string>::const_iterator iter = puhelinluettelo.begin();

    while (iter != puhelinluettelo.end())
    {
        if (iter->first.at(0) == nimen_alkukirjain)
            ++lukumaara;
        iter++;
    }

    return lukumaara;
}

int laske_nimet_rek(map<string, string> puhelinluettelo,
                    char nimen_alkukirjain)
{
    if (puhelinluettelo.size() == 0)
        return 0;
    else
    {
        const map<string, string>::const_iterator iter =
                puhelinluettelo.begin();

        string nimi = iter->first;

        puhelinluettelo.erase(iter);

        return (nimi.at(0) == nimen_alkukirjain) +
                laske_nimet_rek(puhelinluettelo, nimen_alkukirjain);
    }
}

int main()
{
    map<string, string> luettelo =
    {
        {"Mikko", "1"},
        {"Aikko", "1"},
        {"Brkko", "1"},
        {"Mikko", "1"},
        {"Eikko", "1"},
        {"Eikka", "1"},
        {"Bikko", "1"}
    };

    cout << "Iteratiivinen: " << laske_nimet(luettelo, 'B') << endl;
    cout << "Rekursiivinen: " << laske_nimet_rek(luettelo, 'B') << endl;

    return 0;
}
