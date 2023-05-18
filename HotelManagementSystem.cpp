#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Soba
{
    unsigned int brojSobe;
    char tipSobe;
    double cijena;
};

struct Gost
{
    char ime[50];
    char prezime[50];
    unsigned int brojSobe;
    unsigned int vrijemeBoravka;
};

void dodavanjeSobe(Soba soba)
{
    if (soba.brojSobe < 0)
    {
        cout << "Krivi unos sobe";
        return;
    }
    fstream file;
    file.open("sobe.bin", )
}

void pause()
{
    cout << endl << "Pritisnite enter za nastavak...";
    string dummy;
    cin.ignore();
    getline(cin, dummy);
}

int main()
{
    int izbor;
    while (1)
    {
        system("cls");
        cout << "Dobrodosli u Hotel Mol\n";
        cout << "1. Unos soba" << endl;
        cout << "2. Ispis soba" << endl;
        cout << "3. Upis gostiju" << endl;
        cout << "4. Ispis gostiju" << endl;
        cout << "5. Ispis slobodnih soba" << endl;
        cout << "6. Brisanje gostiju" << endl;
        cout << "7. Uredi sobu" << endl;
        cout << "8. Izlaz iz programa" << endl;
        cout << "vas odabir: ";
        cin >> izbor;
        switch (izbor){
        case 1:
        {
            Soba soba;
            cout << "Upisite broj sobe: ";

        }

        case 2:
        {

        }
        case 3:
        {

        }
        case 4:
        {

        }
        case 5:
        {

        }
        case 6:
        {

        }
        case 7:
        {

        }

        case 8:
        {
            cout << "Izlaz iz programa!";
            break;
        }
        default :
            cout << "Krivi unos!";
        }
        pause();
    }
    return 0;
}