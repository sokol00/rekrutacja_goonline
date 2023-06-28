#pragma once
#include <string>
#include <regex>
#include <fstream>
#include <sstream>

using namespace std;

#include <iostream>

class Color
{
private:
    int red, green, blue, alpha;
    double hue, saturation, lightness;

    /*
    * Ci�g znak�w odpowiadaj�cy warto�ciom RGBA
    */
    string hex;

    /*
    * Format w jakim zosta� zapisany ci�g znak�w hex
    */
    string format;
    
    /*
    * Konwertuje zapisane liczby z modelu RGB na model HSL
    */
    void convertRGBtoHSL();

    /*
    * Konwertuje zapisane liczby z modelu HSL na model RGB
    */
    void convertHSLtoRGB();

    /*
    * Konwertuje zapisane liczby RGBA na odpowiadaj�cy ci�g znak�w i zapisuje je do hex
    */
    void generateHex();

public:
    /*
    * Inicjalizuje kolor domy�lnie na kolor czarny
    */
    Color();

    /*
    * Inicjalizuje kolor na podane warto�ci RGBA
    */
    Color(const int& red, const int& green, const int& blue, const int& alpha = 255);

    /*
    * Interpretuje podany ci�g znak�w i zapisuje je jako RGBA
    */
    Color(const string& color);

    ~Color();

    /*
    * Interpretuje podany ci�g znak�w i zapisuje je jako RGBA
    */
    void fromString(const string& color);

    /*
    * Czyta z pliku kolory, dost�pne s� r�ne tryby pracy (domy�lny jest mix):
    * - mix           - odczytuje u�rednion� warto�� wszystkich odczytanych kolor�w
    * - lowest        - najciemniejszy dost�pny kolor (liczone niezale�nie dla ka�dego kana�u koloru)
    * - highest       - najja�niejszy dost�pny kolor (liczone niezale�nie dla ka�dego kana�u koloru)
    * - mix-saturate  - wybiera ostatni dost�pny kolor i ustawia saturacj� na �redni� ze wszystkich kolor�w
    */
    void readFromFile(const string& mode = "mix", const string& name = "colors.txt");

    /*
    * Wy�wietla wszystkie dane jakie przechowuje obiekt
    */
    string getInfo();

    /*
    * Zwraca reprezentacj� ci�gu znak�w odpowiadaj�cemu danemu kolorowi (RGBA),
    * mo�na ponownie wykorzysta� te dane podczas inicjalizacji innego obiektu
    */
    string getHex();
};
