#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial RFID(2, 3);


int rele = 13;
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup()
{
  RFID.begin(9600);
  Serial.begin(9600);
  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);
  lcd.begin();
  lcd.backlight();
  lcd.print("iniciando");
  Serial.println("Bienvenido");
  delay(3000);
}

void loop()
{
  leerRFID();
  leerPC();

}


void leerRFID() {
  int i = 0;
  String data="";
  if (RFID.available() > 0)
  { 
    i = RFID.read();
    data="pin:"+String(i);
    Serial.println(data);
  }

}

void leerPC() {
  String orden = "";
  String mensaje = "";
  String str = "";

  if (Serial.available() > 0)
  {
    str = Serial.readStringUntil('\n');
    orden = getValue(str, ',', 0);
    mensaje = getValue(str, ',', 1);
    accion(orden, mensaje);


  }

}

void accion(String orden, String mensaje) {

  if (orden == "Abrir") {

    Serial.println("molinete abierto");
    Serial.println(mensaje);
    digitalWrite(rele, HIGH);
    lcd.setCursor(0, 1);
    lcd.print(mensaje);
    delay(10000);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Bienvenido");
    Serial.println("Bienvenido");
  }
  else {
    Serial.println("no accion");
    Serial.println(mensaje);
    digitalWrite(rele, LOW);
  }


}


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
