#include <string.h>
#include <Wire.h>

class Color
{
public:
  int red, green, blue, white;
  double hue, saturation, lightness;

  Color();
  Color(const int& red, const int& green, const int& blue, const int& white = 0);

  void convertRGBtoHSL();
  void convertHSLtoRGB();
  String getInfo();
  char* getColorCode();
};



#define I2C_ADDRESS 0b1110000

Color c(255, 0, 0, 0);
void setup()
{
  Serial.begin(115200);
  Wire.begin();
  
}

void loop()
{
  Serial.println(c.getInfo());
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(c.getColorCode(), 5);
  Wire.endTransmission();
  
  delay(100);
  c.hue = fmod(c.hue+1, 360);
  c.convertHSLtoRGB();
}







Color::Color() : red(0), green(0), blue(0), white(0), hue(0), saturation(0), lightness(0) { }

Color::Color(const int& red, const int& green, const int& blue, const int& white) : red(red), green(green), blue(blue), white(white)
{
  convertRGBtoHSL();
}

String Color::getInfo()
{
  String out = "";

  out += "RGBA:\t" + String(red);
  out += "," + String(green);
  out += "," + String(blue);
  out += "," + String(white);
  out += "\n";

  out += "HSL:\t" + String(hue);
  out += "," + String(saturation);
  out += "," + String(lightness);
  //out += "\n";
  return out;
}

char* Color::getColorCode()
{
  static char* text = new char[5];
  text[0] = 0b10100010;
  text[1] = char(red);
  text[2] = char(green);
  text[3] = char(blue);
  text[4] = char(white);
  return text;
}

void Color::convertRGBtoHSL()
{
  // Przeliczenie wartości RGBW na zakres [0, 1]
  float r = red / 255.0;
  float g = green / 255.0;
  float b = blue / 255.0;
  
  float cmax = fmaxf(fmaxf(r, g), b); // Największa składowa
  float cmin = fminf(fminf(r, g), b); // Najmniejsza składowa
  float delta = cmax - cmin;
  
  float h, s, l;
  
  // Obliczenie odcienia (Hue)
  if (delta == 0)
    h = 0;
  else if (cmax == red)
    h = fmodf((green - blue) / delta, 6);
  else if (cmax == green)
    h = (blue - red) / delta + 2;
  else if (cmax == blue)
    h = (red - green) / delta + 4;
  else
    h = 0; // Hue = 0 dla czarnego światła
    
  h *= 60; // Przekształcenie odcienia do zakresu [0, 360]
  
  // Obliczenie jasności (Lightness)
  l = (cmax + cmin) / 2;
  
  // Obliczenie nasycenia (Saturation)
  if (delta == 0)
    s = 0; // Saturation = 0 dla odcieni szarości
  else
    s = delta / (1 - fabsf(2 * l - 1));
  
  hue = h;
  saturation = s;
  lightness = l;
}

void Color::convertHSLtoRGB()
{
  float c = (1 - abs(2 * lightness - 1)) * saturation;
  float x = c * (1 - abs(fmod((hue/60),2)-1));
  float m = (lightness - c/2) * 255;
  int h = floor(hue / 60);
  switch(h)
  {
    case 0:
      red = 255 * c;
      green = 255 * x;
      blue = 0;
    break;
    case 1:
      red = 255 * x;
      green = 255 * c;
      blue = 0;
    break;
    case 2:
      red = 0;
      green = 255 * c;
      blue = 255 * x;
    break;
    case 3:
      red = 0;
      green = 255 * x;
      blue = 255 * c;
    break;
    case 4:
      red = 255 * x;
      green = 0;
      blue = 255 * c;
    break;
    case 5:
      red = 255 * c;
      green = 0;
      blue = 255 * x;
    break;
    default:
    break;
  }
  red += m;
  green += m;
  blue += m;
}
