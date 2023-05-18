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
    char ime[51];
    char prezime[101];
    unsigned int brojSobe;
    unsigned int vrijemeBoravka;
};

void dodavanjeSobe(Soba soba)
{
    if (soba.brojSobe < 0)
    {
        cout << "Krivi unos sobe" << endl;
        return;
    }

    switch (soba.tipSobe)
    {
    case 'A':
    case 'B':
    case 'C':
        break;
    default:
        cout << "Krivi unos klase!" << endl;
        return;
    }

    fstream file;
    file.open("sobe.bin", ios::binary | ios::app);
    file.write((char*)&soba.brojSobe, sizeof(soba.brojSobe));
    file.write((char*)&soba.tipSobe, sizeof(soba.tipSobe));
    file.write((char*)&soba.cijena, sizeof(soba.cijena));

    file.close();
}

void ispisSoba(Soba soba)
{
    fstream file;
    file.open("sobe.bin", ios::binary | ios::in);
    while (file.read((char*)&soba.brojSobe, sizeof(soba.brojSobe)) && file.read((char*)&soba.tipSobe, sizeof(soba.tipSobe)) && file.read((char*)&soba.cijena, sizeof(soba.cijena)))
    {
        cout << "Broj sobe: " << soba.brojSobe << endl;
        cout << "Tip sobe: " << soba.tipSobe << endl;
        cout << "Cijena: " << soba.cijena << endl;
    }
    file.close();
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
    Soba soba = { 0, '\0', 0.0 }; //napravio sam ovo da ispis soba zapravo dela, dakle postavim sve vrijednosti na nulu
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
            cout << "Upisite broj sobe: ";
            cin >> soba.brojSobe;
            cout << "Upisite klasu sobe (A, B, C): ";
            cin >> soba.tipSobe;
            cout << "Unesite cijenu za jednu noc: ";
            cin >> soba.cijena;
            dodavanjeSobe(soba);
            break;
        }

        case 2:
        {
            ispisSoba(soba);
            break;
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
            return 0;
            break;
        }
        default :
            cout << "Krivi unos!";
        }
        pause();
    }
}