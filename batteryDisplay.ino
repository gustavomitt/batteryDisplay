#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_GFX.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_SSD1306.h> //INCLUSÃO DE BIBLIOTECA
 
Adafruit_SSD1306 display = Adafruit_SSD1306(); //OBJETO DO TIPO Adafruit_SSD1306

 
const int currentPin = A0;
int sensitivity = 185;
int adcValue= 0;
double offsetVoltage = 2.5;
int offsetByte = 511;
int maxCurrent = 5;
int maxVoltage = 5;
double adcVoltage = 0;
double currentValue = 0;

const int voltagePin = A1;
int voltageBinary = 0;
int voltageFactor = 3;
double voltageValue = 0;


void setup(){
  Serial.begin(115200);
  delay(500);
  
  Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE); //DEFINE A COR DO TEXTO
  display.setTextSize(1); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
}
void loop() {

  // Obtem corrente:
  adcValue = analogRead(currentPin);
  adcVoltage = (adcValue / 1024.0) * 5;
  currentValue = (adcValue - offsetByte)/ 1024.0 * maxVoltage *  maxCurrent / offsetVoltage;
  Serial.println("adcValue: " + String(adcValue));
  Serial.println("adcVoltage: " + String(adcVoltage));
  Serial.println("currentValue: " + String(currentValue));

  // Obtem voltagem:
  voltageBinary = analogRead(voltagePin);
  voltageValue = (voltageBinary / 1024.0) * maxVoltage * voltageFactor;
  Serial.println("voltageBinary: " + String(voltageBinary));
  Serial.println("voltageValue: " + String(voltageValue));

  
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
  display.setCursor(5,0); 
  display.print("Tensao: " + String(voltageValue,1) + " V"); //ESCREVE O TEXTO NO DISPLAY
  display.setCursor(5,10); 
  display.print("Corrente: " + String(currentValue,1) + " A"); //ESCREVE O TEXTO NO DISPLAY
  display.display();
  delay(500); //INTERVALO DE 1,5 SEGUNDOS
}
