#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <ios>
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
    if (soba.brojSobe <= 0)
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
    }//provjera za unos klase

    fstream file;
    file.open("sobe.bin", ios::binary | ios::in);
    if (!file)
    {
        cout << "Greska pri otvaranju datoteke!" << endl;
        return;
    }

    Soba postojecaSoba;
    bool sobaPostoji = false;
    while (file.read((char*)&postojecaSoba.brojSobe, sizeof(postojecaSoba.brojSobe)) && file.read((char*)&postojecaSoba.tipSobe, sizeof(postojecaSoba.tipSobe)) && file.read((char*)&postojecaSoba.cijena, sizeof(postojecaSoba.cijena)))
    {
        if (postojecaSoba.brojSobe == soba.brojSobe)
        {
            sobaPostoji = true;
            break;
        }
    }//provjerava jel unesen broj sobe vec postoji

    file.close();

    if (sobaPostoji)
    {
        cout << "Soba s tim brojem vec postoji!" << endl;
        return;
    }

    file.open("sobe.bin", ios::binary | ios::app);
    if (!file)
    {
        cout << "Greska pri otvaranju datoteke!" << endl;
        return;
    }

    file.write((char*)&soba.brojSobe, sizeof(soba.brojSobe));
    file.write((char*)&soba.tipSobe, sizeof(soba.tipSobe));
    file.write((char*)&soba.cijena, sizeof(soba.cijena));

    file.close();

    cout << "Soba uspjesno dodana." << endl;
}


void ispisSoba(Soba soba)
{
    fstream file;
    file.open("sobe.bin", ios::binary | ios::in);
    if (!file)
    {
        cout << "Greska pri otvaranju datoteke!" << endl;
        return;
    }

    while (file.read((char*)&soba.brojSobe, sizeof(soba.brojSobe)) && file.read((char*)&soba.tipSobe, sizeof(soba.tipSobe)) && file.read((char*)&soba.cijena, sizeof(soba.cijena)))
    {
        cout << "Broj sobe: " << soba.brojSobe << endl;
        cout << "Tip sobe: " << soba.tipSobe << endl;
        cout << "Cijena: " << soba.cijena << endl;
    }
    file.close();
}

void dodavanjeGostiju(Gost* gost)
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
        break;
    }

    fstream file;
    file.open("sobe.bin", ios::binary | ios::in);

    if (!file)
    {
        cout << "Greska pri otvaranju datoteke!" << endl;
        return;
    }

    bool sobaPostoji = false;
    Soba soba;

    while (file.read((char*)&soba.brojSobe, sizeof(soba.brojSobe)) && file.read((char*)&soba.tipSobe, sizeof(soba.tipSobe)) && file.read((char*)&soba.cijena, sizeof(soba.cijena)))
    {
        if (soba.brojSobe == gost[index - 1].brojSobe)
        {
            sobaPostoji = true;
            break;
        }
    }
    file.close();

    if (!sobaPostoji)
    {
        cout << "Soba ne postoji!" << endl;
        return;
    }



    fstream file2;
    file2.open("gosti.txt", ios::app);
    for (int i = 0; i < index; i++)
    {
        file2 << "Ime: " << gost[i].ime << endl;
        file2 << "Prezime: " << gost[i].prezime << endl;
        file2 << "Broj sobe: " << gost[i].brojSobe << endl;
        file2 << "Vrijeme boravka: " << gost[i].vrijemeBoravka << " noci" << endl;
    }

    file2.close();
}


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

void ispisSlobodnihSoba()
{
    
}



void brisanjeGostiju()
{
    fstream inputFile("gosti.txt", ios::in);
    if (!inputFile)
    {
        cout << "Greska pri otvaranju datoteke!" << endl;
        return;
    }

    fstream tempFile("temp.txt", ios::out);  // Privremena datoteka za pohranu promijenjenih podataka

    cout << "Unesite ime gosta za brisanje: ";
    char ime[51];
    cin.ignore();
    cin.getline(ime, sizeof(ime));

    cout << "Unesite prezime gosta za brisanje: ";
    char prezime[101];
    cin.getline(prezime, sizeof(prezime));

    bool deleted = false;  // Zastavica - provjera ako je našto izbrisano

    string line;
    while (getline(inputFile, line))
    {
        if (line.find("Ime: " + string(ime)) != string::npos && getline(inputFile, line) && line.find("Prezime: " + string(prezime)) != string::npos)
        {
            // Skip
            getline(inputFile, line);  // Skip "Broj sobe: ..."
            getline(inputFile, line);  // Skip "Vrijeme boravka: ..."
            deleted = true;
            continue;
        }

        tempFile << line << endl;
    }

    inputFile.close();
    tempFile.close();

    remove("gosti.txt");            // Micanje originalne datoteke
    rename("temp.txt", "gosti.txt"); // Preimenovanje privremene datoteke koja mijenja originalnu

    if (deleted)
        cout << "Gost uspjesno obrisan." << endl;
    else
        cout << "Gost s tim imenom i prezimenom nije pronaden." << endl;
}




void uredenjeSobe()
{
    fstream file;
    file.open("sobe.bin", ios::binary | ios::in | ios::out);

    if (!file)
    {
        cout << "Greska pri otvaranju datoteke!" << endl;
        return;
    }

    unsigned int brojSobe;
    cout << "Unesite broj sobe koju zelite urediti: ";
    cin >> brojSobe;

    Soba soba;
    bool sobaPostoji1 = false;

    while (file.read((char*)&soba.brojSobe, sizeof(soba.brojSobe)) && file.read((char*)&soba.tipSobe, sizeof(soba.tipSobe)) && file.read((char*)&soba.cijena, sizeof(soba.cijena)))
    {
        if (soba.brojSobe == brojSobe)
        {
            sobaPostoji1 = true;
            break;
        }
    }

    if (!sobaPostoji1)
    {
        cout << "Soba ne postoji!" << endl;
        file.close();
        return;
    }

    cout << "Unesite novi broj sobe: ";
    unsigned int noviBrojSobe;
    cin >> noviBrojSobe;

    Soba postojecaSoba;
    bool sobaPostoji2 = false;
    while (file.read((char*)&postojecaSoba.brojSobe, sizeof(postojecaSoba.brojSobe)) && file.read((char*)&postojecaSoba.tipSobe, sizeof(postojecaSoba.tipSobe)) && file.read((char*)&postojecaSoba.cijena, sizeof(postojecaSoba.cijena)))
    {
        if (postojecaSoba.brojSobe == noviBrojSobe)
        {
            sobaPostoji2 = true;
            break;
        }
    }//provjerava jel unesen broj sobe vec postoji

    if (sobaPostoji2)
    {
        cout << "Soba s tim brojem vec postoji!" << endl;
        return;
    }

    cout << "Unesite novu klasu sobe (A, B, C): ";
    char novaKlasa;
    cin >> novaKlasa;
    cout << "Unesite novu cijenu za jednu noc: ";
    double novaCijena;
    cin >> novaCijena;

    // Pomice fileov pokazivac nazad na pocetak
    file.seekp(file.tellg() - static_cast<streampos>(sizeof(soba.brojSobe) + sizeof(soba.tipSobe) + sizeof(soba.cijena)));

    // Upisuje azurirane podatke nazad u datoteku
    file.write((char*)&noviBrojSobe, sizeof(noviBrojSobe));
    file.write((char*)&novaKlasa, sizeof(novaKlasa));
    file.write((char*)&novaCijena, sizeof(novaCijena));

    file.close();

    // Azurira broj sobe u gosti.txt
    ifstream gostiFile("gosti.txt");
    if (!gostiFile)
    {
        cout << "Greska pri otvaranju datoteke gosti.txt!" << endl;
        return;
    }

    ofstream tempFile("temp.txt"); // Privremena datoteka za pohranu promijenjenih podataka 

    string line;
    while (getline(gostiFile, line))
    {
        if (line.find("Broj sobe: ") != string::npos)
        {
            // Azurira broj sobe
            tempFile << "Broj sobe: " << noviBrojSobe << endl;
        }
        else
        {
            tempFile << line << endl;
        }
    }

    gostiFile.close();
    tempFile.close();

    remove("gosti.txt");            
    rename("temp.txt", "gosti.txt");

    cout << "Soba uspjesno uredena." << endl;
}




void pause()    //originalni kod - Zlatko Damijanic
{
    cout << endl << "Pritisnite enter za nastavak...";
    string dummy;
    cin.ignore();
    getline(cin, dummy);
}

int main()
{
    int izbor;
    Soba soba = { 0, '\0', 0.0 };
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
            
            dodavanjeGostiju(gost);
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
            brisanjeGostiju();
            break;
        }
        case 7:
        {
            uredenjeSobe();
            break;
        }
        case 8:
        {
            cout << "Izlaz iz programa!";
            return 0;
            break;
        }
        default :
            cout << "Krivi unos!";
            break;
        }
        pause();
    }
}