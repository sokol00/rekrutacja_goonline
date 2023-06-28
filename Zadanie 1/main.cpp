#include <iostream>
#include "Color.h"

using namespace std;



int main(int argc, char* argv[])
{
    string mode = "mix";
    Color c;
    //odczytywanie argumentów
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--MODE" || string(argv[i]) == "-m")
        {
            if (++i < argc)
                mode = argv[i];
            continue;
        }
        try {
            c.fromString(argv[i]); // można zainicjować kolor z cli (dla testow)
            cout << "Wprowadzono kolor: " << argv[i] << endl << c.getInfo() << endl << endl;
        } catch (const exception& e) {
            cout << "Nierozpoznano argumentu: " << argv[i] << endl;
            cout << "Przechwycono wyjatek: " << e.what() << endl;
        }
    }
    //wykonywanie programu z podanymi argumentami
    try {
        c.readFromFile(mode);
    } catch (const exception& e) {
        cout << "Przechwycono wyjatek podczas czytania pliku: " << e.what() << endl;
    }
    cout << "Podsumowanie:\n" << c.getInfo() << endl;
}

