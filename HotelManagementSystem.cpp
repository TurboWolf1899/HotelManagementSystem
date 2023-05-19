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
    }/* provjerava jel upisano A, B ili C, ako je onda se program nastavlja a
    ako ne onda se ispise kaj se vec ispise te se vraca u main. Malo cudno je ali ne radi mi
    sa if-om nekako.*/

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

void dodavanjeGostiju(Gost* gost, int index)
{
    /*fstream file1;
    file1.open("sobe.bin", ios::binary | ios::in);

    if (!file1)
    {
        cout << "Greska pri otvaranju datoteke!" << endl;
        return;
    }

    bool roomExists = false;
    Soba soba;

    while (file1.read(reinterpret_cast<char*>(&soba), sizeof(Soba)))
    {
        if (soba.brojSobe == gost[index].brojSobe)
        {
            roomExists = true;
            break;
        }
    }
    file1.close();

    if (!roomExists)
    {
        cout << "Soba ne postoji!" << endl;
        return;
    }                   Cijeli kod koji provjerava jel soba uopce postoji ne dela
    
    
                                jos.                                                     
                                
                                ne odustajem.                                                            */


    fstream file2;
    file2.open("gosti.txt", ios::app);
    for (int i = 0; i < index; i++)
    {
        file2 << "Ime: " << gost[i].ime << endl;
        file2 << "Prezime: " << gost[i].prezime << endl;
        file2 << "Broj sobe: " << gost[i].brojSobe << endl;
        file2 << "Vrijeme boravka: " << gost[i].vrijemeBoravka << " noci" << endl;
        file2 << endl;
    }
    
    file2.close();
}

void ispisSlobodnihSoba()
{
    fstream file1;
    file1.open("gosti.txt", ios::in);

    if (!file1)
    {
        cout << "Greska pri otvaranju datoteke!" << endl;
        return;
    }

    int ukupnoSoba = 0;
    int zauzetihSoba = 0;
    Gost gost;
    Soba soba;

    while (file1.read(reinterpret_cast<char*>(&gost), sizeof(Gost)))
    {
        if (strlen(gost.ime) > 0)
            zauzetihSoba++;
    }
    file1.close();

    fstream file2;
    file2.open("sobe.bin", ios::in);

    if (!file2)
    {
        cout << "Greska pri otvaranju datoteke!" << endl;
        return;
    }

    while (file2.read(reinterpret_cast<char*>(&soba), sizeof(Soba)))
        ukupnoSoba++; //doslovno treba delati al ne dela.

    int dostupneSobe = ukupnoSoba - zauzetihSoba;

    if (dostupneSobe > 0)
        cout << "Broj slobodnih soba: " << dostupneSobe << endl;
    else
        cout << "Nema slobodnih soba." << endl;

    file2.close();
}// dela al ne tocno, kad upisem jednu sobu kaze da nema slobodnih soba, a kad upisem drugu onda pise da ima samo jedna

void ispisGostiju()
{
    fstream file;
    file.open("gosti.txt", ios::in);
    if (!file)
    {
        cout << "Greska pri otvaranju datoteke!" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        cout << line << endl;
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
    Gost* gost = new Gost[100];
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
            int index = 0;
            while (index < 100)
            {
                cout << "Unesite ime gosta: ";
                cin.ignore();
                cin.getline(gost[index].ime, sizeof(gost[index].ime));

                cout << "Unesite prezime gosta: ";
                cin.getline(gost[index].prezime, sizeof(gost[index].prezime));

                cout << "Unesite broj sobe gosta: ";
                cin >> gost[index].brojSobe;

                cout << "Unesite vrijeme boravka gosta: ";
                cin >> gost[index].vrijemeBoravka;

                index++;

                cout << "Zelite li unijeti jos gostiju? (da/ne): ";
                string izbor;
                cin >> izbor;

                if (izbor != "da")
                    break;
            }
            dodavanjeGostiju(gost, index);
            break;
        }
        case 4:
        {
            ispisGostiju();
            break;
        }
        case 5:
        {
            ispisSlobodnihSoba();
            break;
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