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
    * Ci¹g znaków odpowiadaj¹cy wartoœciom RGBA
    */
    string hex;

    /*
    * Format w jakim zosta³ zapisany ci¹g znaków hex
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
    * Konwertuje zapisane liczby RGBA na odpowiadaj¹cy ci¹g znaków i zapisuje je do hex
    */
    void generateHex();

public:
    /*
    * Inicjalizuje kolor domyœlnie na kolor czarny
    */
    Color();

    /*
    * Inicjalizuje kolor na podane wartoœci RGBA
    */
    Color(const int& red, const int& green, const int& blue, const int& alpha = 255);

    /*
    * Interpretuje podany ci¹g znaków i zapisuje je jako RGBA
    */
    Color(const string& color);

    ~Color();

    /*
    * Interpretuje podany ci¹g znaków i zapisuje je jako RGBA
    */
    void fromString(const string& color);

    /*
    * Czyta z pliku kolory, dostêpne s¹ ró¿ne tryby pracy (domyœlny jest mix):
    * - mix           - odczytuje uœrednion¹ wartoœæ wszystkich odczytanych kolorów
    * - lowest        - najciemniejszy dostêpny kolor (liczone niezale¿nie dla ka¿dego kana³u koloru)
    * - highest       - najjaœniejszy dostêpny kolor (liczone niezale¿nie dla ka¿dego kana³u koloru)
    * - mix-saturate  - wybiera ostatni dostêpny kolor i ustawia saturacjê na œredni¹ ze wszystkich kolorów
    */
    void readFromFile(const string& mode = "mix", const string& name = "colors.txt");

    /*
    * Wyœwietla wszystkie dane jakie przechowuje obiekt
    */
    string getInfo();

    /*
    * Zwraca reprezentacjê ci¹gu znaków odpowiadaj¹cemu danemu kolorowi (RGBA),
    * mo¿na ponownie wykorzystaæ te dane podczas inicjalizacji innego obiektu
    */
    string getHex();
};
