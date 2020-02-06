#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void tulosta(const map<string, vector<string>>& tilasto);
void lisaa_laji(map<string, vector<string>>& tilasto,
                const string lajin_nimi, const vector<string>& kilpailijat={});

void tulosta(const map<string, vector<string>>& tilasto)
{
    for (auto laji : tilasto){
        cout << laji.first << endl;

        vector<string>::const_iterator iter;
        iter = laji.second.begin();

        while (iter != laji.second.end()){
            cout << "\t" << (iter - laji.second.begin())+1 << ". "
                 << *iter << endl;
            iter++;
        }

        cout << endl;
    }
}

void lisaa_laji(map<string, vector<string>>& tilasto,
                const string lajin_nimi, const vector<string> &kilpailijat)
{
    auto iter = tilasto.find(lajin_nimi);

    if (iter == tilasto.end()){
        tilasto.insert({lajin_nimi, kilpailijat});
    }
}

int main()
{
    map<string, vector<string>> kilpailijoiden_sijoitus = {
        {"Keihas", {"Heimo Heittaja",
                    "Henni Asunmaa",
                    "Niina Laaksonen",
                    "Ville Eronen",
                    "Niko Saksala",
                    "Kalle Keihanen"}},
        {"Seivas", {"Hilkka Hyppaaja",
                    "Into Setala",
                    "Anneli Hilkka",
                    "Iines Naarajarvi",
                    "Jarmo Jutila",
                    "Ari-Pekka Sormunen",
                    "Elma Rahkamo",
                    "Alina Myllyniemi",
                    "Sinikka Seivas"}},
        {"Kuula", {"Kalevi Kuula",
                   "Eveliina Ikonen",
                   "Janne Itkonen",
                   "Annikki Paatalo",
                   "Tauno Teras"}}
    };

    vector<string> keilailu_kilp = {"Mauno Ahokangas",
                                   "Eija Leinonen",
                                   "Asko Laaksonen",
                                   "Samuli Isokoski"};

    lisaa_laji(kilpailijoiden_sijoitus, "Keilailu", keilailu_kilp);

    tulosta(kilpailijoiden_sijoitus);

    return 0;
}
