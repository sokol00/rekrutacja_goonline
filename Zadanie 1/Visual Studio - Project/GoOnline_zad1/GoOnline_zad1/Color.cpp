#include "Color.h"



Color::Color() : red(0), green(0), blue(0), alpha(0), hex("0,0,0,0"), format("^([0-9]{1,3},){3}[0-9]{1,3}$"), hue(0), saturation(0), lightness(0) { }

Color::Color(const int& red, const int& green, const int& blue, const int& alpha) : red(red), green(green), blue(blue), alpha(alpha)
{
    generateHex();
    convertRGBtoHSL();
}

Color::Color(const string& color)
{
    fromString(color);
}

Color::~Color() { }



void Color::convertRGBtoHSL()
{
    double r = red   / 255.0;
    double g = green / 255.0;
    double b = blue  / 255.0;

    double maxVal = max(max(r, g), b);
    double minVal = min(min(r, g), b);

    double delta = maxVal - minVal;


    // Obliczanie Lightness
    lightness = (maxVal + minVal) / 2.0;

    // Obliczanie Saturation
    if (delta == 0)
        saturation = 0.0;
    else
        saturation = delta / (1.0 - abs(2 * lightness - 1.0));


    // Obliczanie Hue
    if (delta == 0)
        hue = 0.0;  // Wartoœæ nieokreœlona, mo¿na ustawiæ na 0 lub inny dowolny k¹t
    else
    {
        double hue_temp = 0.0;
        if (maxVal == r)
            hue_temp =       (g - b) / delta;
        else if (maxVal == g)
            hue_temp = 2.0 + (b - r) / delta;
        else
            hue_temp = 4.0 + (r - g) / delta;

        hue_temp *= 60.0;

        if (hue_temp < 0.0)
            hue_temp += 360.0;

        hue = hue_temp;
    }
}

void Color::convertHSLtoRGB()
{
    double c = (1 - fabs(2 * lightness - 1)) * saturation;
    double x = c * (1 - fabs(fmod(hue / 60, 2) - 1));
    double m = lightness - c / 2;

    double r, g, b;

    if (hue >= 0 && hue < 60)
    {
        r = c;
        g = x;
        b = 0;
    }
    else if (hue >= 60 && hue < 120)
    {
        r = x;
        g = c;
        b = 0;
    }
    else if (hue >= 120 && hue < 180)
    {
        r = 0;
        g = c;
        b = x;
    }
    else if (hue >= 180 && hue < 240)
    {
        r = 0;
        g = x;
        b = c;
    }
    else if (hue >= 240 && hue < 300)
    {
        r = x;
        g = 0;
        b = c;
    }
    else
    {
        r = c;
        g = 0;
        b = x;
    }

    red   = int((r + m) * 255);
    green = int((g + m) * 255);
    blue  = int((b + m) * 255);
}

void Color::generateHex()
{
    hex = "";
    hex += to_string(red)   + ",";
    hex += to_string(green) + ",";
    hex += to_string(blue)  + ",";
    hex += to_string(alpha);
    format = "^([0-9]{1,3},){3}[0-9]{1,3}$";
}

void Color::fromString(const string& color)
{
    /*
    regex format1("^([0-9a-f]{3})$");
    regex format2("^([0-9a-f]{6})$");
    regex format3("^([0-9a-f]{8})$");
    regex format4("^([0-9]{1,3},){3}[0-9]{1,3}$");
    */
    vector<string> formats(4);
    formats[0] = "^([0-9a-fA-F]{3})$";
    formats[1] = "^([0-9a-fA-F]{6})$";
    formats[2] = "^([0-9a-fA-F]{8})$";
    formats[3] = "^([0-9]{1,3},){3}[0-9]{1,3}$";
    
    //sprawdzanie i wyszukiwanie formatu danych
    for (int i = 0; 1; i++)
    {
        if (i == formats.size())
            throw invalid_argument("Bledne dane!");
        if (regex_match(color, regex(formats[i])))
        {
            format = formats[i];
            hex = color;
            break;
        }
    }

    //zapisywanie koloru do int wed³ug ustalonego formatu
    if (format == formats[0])
    {
        string r, g, b;
        //r = hex[0] + hex[0];
        //g = hex[1] + hex[1];
        //b = hex[2] + hex[2];
        r = hex.substr(0, 1);
        g = hex.substr(1, 1);
        b = hex.substr(2, 1);
        r = r + r;
        g = g + g;
        b = b + b;
        red   = stoi(r, nullptr, 16);
        green = stoi(g, nullptr, 16);
        blue  = stoi(b, nullptr, 16);
        alpha = 255;
    }
    if (format == formats[1])
    {
        string r, g, b;
        //r = hex[0] + hex[1];
        //g = hex[2] + hex[3];
        //b = hex[4] + hex[5];
        r = hex.substr(0, 2);
        g = hex.substr(2, 2);
        b = hex.substr(4, 2);
        red   = stoi(r, nullptr, 16);
        green = stoi(g, nullptr, 16);
        blue  = stoi(b, nullptr, 16);
        alpha = 255;
    }
    if (format == formats[2])
    {
        string r, g, b, a;
        //r = hex[0] + hex[1];
        //g = hex[2] + hex[3];
        //b = hex[4] + hex[5];
        //a = hex[6] + hex[7];
        r = hex.substr(0, 2);
        g = hex.substr(2, 2);
        b = hex.substr(4, 2);
        a = hex.substr(6, 2);
        red   = stoi(r, nullptr, 16);
        green = stoi(g, nullptr, 16);
        blue  = stoi(b, nullptr, 16);
        alpha = stoi(a, nullptr, 16);
    }
    if (format == formats[3])
    {
        string r, g, b, a;
        stringstream ss(hex);
        getline(ss, r, ',');
        getline(ss, g, ',');
        getline(ss, b, ',');
        getline(ss, a, ',');
        red   = stoi(r);
        green = stoi(g);
        blue  = stoi(b);
        alpha = stoi(a);
    }

    //zapisywanie koloru w formacie HSL
    convertRGBtoHSL();
}

string Color::getInfo()
{
    string out = "";
    out += "hex:\t"    + hex;
    out += "\n";
    out += "format:\t" + format;
    out += "\n";

    out += "RGBA:\t" + to_string(red);
    out += ","       + to_string(green);
    out += ","       + to_string(blue);
    out += ","       + to_string(alpha);
    out += "\n";

    out += "HSL:\t" + to_string(hue);
    out += ","      + to_string(saturation);
    out += ","      + to_string(lightness);
    //out += "\n";
    return out;
}

string Color::getHex()
{
    if (hex == "")
        generateHex();
    return hex;
}

void Color::readFromFile(const string& mode, const string& name)
{
    //otwieranie pliku
    string line;
    ifstream file(name);
    if (!file.is_open())
        throw runtime_error("Nie mo¿na otworzyæ pliku: " + name);

    //interpretowanie danych wed³ug wybranego trybu
    if (mode == "default" || mode == "DEFAULT")
    {
        //getline(file, line);
        file >> line;
        fromString(line); //inicjalizacja obiektu z otrzymanych danych
    }
    else if (mode == "mix" || mode == "MIX")
    {
        Color a, b;
        while (!file.eof())
        {
            getline(file, line);
            try { a.fromString(line); }
            catch (const exception&) { continue; }
            break;
        }
        int i = 1;
        while (!file.eof())
        {
            getline(file, line);
            try { b.fromString(line); }
            catch (const exception&) { continue; }
            a.red   += b.red;
            a.green += b.green;
            a.blue  += b.blue;
            a.alpha += b.alpha;
            i++;
        }
        red   = a.red   / i;
        green = a.green / i;
        blue  = a.blue  / i;
        alpha = a.alpha / i;
        generateHex();
        convertRGBtoHSL();
    }
    else if (mode == "lowest" || mode == "LOWEST")
    {
        Color a, b;
        while (!file.eof())
        {
            getline(file, line);
            try { a.fromString(line); }
            catch (const exception&) { continue; }
            break;
        }
        while (!file.eof())
        {
            getline(file, line);
            try { b.fromString(line); }
            catch (const exception&) { continue; }
            a.red   = (a.red   > b.red)   ? b.red   : a.red;
            a.green = (a.green > b.green) ? b.green : a.green;
            a.blue  = (a.blue  > b.blue)  ? b.blue  : a.blue;
            a.alpha = (a.alpha > b.alpha) ? b.alpha : a.alpha;
        }
        a.generateHex();
        fromString(a.getHex());
    }
    else if (mode == "highest" || mode == "HIGHEST")
    {
        Color a, b;
        while (!file.eof())
        {
            getline(file, line);
            try { a.fromString(line); }
            catch (const exception&) { continue; }
            break;
        }
        while (!file.eof())
        {
            getline(file, line);
            try {  b.fromString(line); }
            catch (const exception&) { continue; }
            a.red   = (a.red   < b.red)   ? b.red   : a.red;
            a.green = (a.green < b.green) ? b.green : a.green;
            a.blue  = (a.blue  < b.blue)  ? b.blue  : a.blue;
            a.alpha = (a.alpha < b.alpha) ? b.alpha : a.alpha;
        }
        a.generateHex();
        fromString(a.getHex());
    }
    else if (mode == "mix-saturate" || mode == "MIX-SATURATE")
    {
        Color a, b;
        while (!file.eof())
        {
            getline(file, line);
            try { a.fromString(line); }
            catch (const exception&) { continue; }
            break;
        }
        int i = 1;
        while (!file.eof())
        {
            getline(file, line);
            try { b.fromString(line); }
            catch (const exception&) { continue; }
            a.saturation += b.saturation;
            i++;
        }
        b.saturation = a.saturation / i;
        b.convertHSLtoRGB();
        b.generateHex();
        fromString(b.getHex());
    }
    else
    {
        file.close();
        throw invalid_argument("Nie rozpoznano trybu: " + mode);
    }

    //zamykanie pliku
    file.close();
}


