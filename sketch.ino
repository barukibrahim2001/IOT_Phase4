#include "RTClib.h"
#include "Wire.h"
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 6
#define DHTTYPE DHT22 
#define I2C_ADDR  0x27
#define LCD_COLUMNS 20
#define LCD_LINES 4
LiquidCrystal_I2C lcd(I2C_ADDR,LCD_COLUMNS,LCD_LINES);
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int r1=5;
int r2=4;
int r3=2;
int r4=3;
DHT dht(DHTPIN, DHTTYPE);
void setup () {
  Serial.begin(115200);
  Serial.println("welcome to my project");
  lcd.init();
  lcd.backlight();
   lcd.setCursor(3,0);
   lcd.print(" WELCOME TO");
   lcd.setCursor(0,1);
   lcd.print(" SMART AGRICULTURE");
   lcd.setCursor(5,2);
    lcd.print(("IRRIGATION"));
   lcd.setCursor(7,3);
   lcd.print("SYSTEM");
   delay(4000);
   lcd.clear();
   pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
}

void loop ()
 {
  rtcdata();
  dhtdata();
  }
  void rtcdata(){
  DateTime now = rtc.now();
  lcd.setCursor(3,0);
  lcd.print("TIME");
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  delay(500);
/*  lcd.setCursor(0,1);
   lcd.print("RELAY1:");
   lcd.setCursor(10,1);
   lcd.print("RELAY2:");
   lcd.setCursor(0,2);
   lcd.print("RELAY3:");
   lcd.setCursor(10,2);
   lcd.print("RELAY4:");*/
   if(now.minute()>=23&&now.minute()<=24)
   {
    lcd.setCursor(0,1);
   lcd.print("RELAY1:on");
   lcd.setCursor(10,1);
   lcd.print("RELAY2:off");
   lcd.setCursor(0,2);
   lcd.print("RELAY3:off");
   lcd.setCursor(10,2);
   lcd.print("RELAY4:off");
   digitalWrite(r1, HIGH);
   }
   else{
    digitalWrite(r1,LOW);
   }
   if(now.minute()>=25&&now.minute()<=26)
   {
    lcd.clear();
    lcd.setCursor(0,1);
   lcd.print("RELAY1:off");
   lcd.setCursor(10,1);
   lcd.print("RELAY2:on");
   lcd.setCursor(0,2);
   lcd.print("RELAY3:off");
   lcd.setCursor(10,2);
   lcd.print("RELAY4:off");
   digitalWrite(r2, HIGH);
   }
   else
   {
    digitalWrite(r2, LOW);
   }
   if(now.minute()>=27&&now.minute()<=28)
   {
    lcd.clear();
    lcd.setCursor(0,1);
   lcd.print("RELAY1:off");
   lcd.setCursor(10,1);
   lcd.print("RELAY2:off");
   lcd.setCursor(0,2);
   lcd.print("RELAY3:on");
   lcd.setCursor(10,2);
   lcd.print("RELAY4:off");
   digitalWrite(r3, HIGH);
   }
   else
   {
    digitalWrite(r3, LOW);
   }
  if(now.minute()>=46&&now.minute()<=47)
   {
    lcd.clear();
    lcd.setCursor(0,1);
   lcd.print("RELAY1:off");
   lcd.setCursor(10,1);
   lcd.print("RELAY2:off");
   lcd.setCursor(0,2);
   lcd.print("RELAY3:off");
   lcd.setCursor(10,2);
   lcd.print("RELAY4:on");
   digitalWrite(r4, HIGH);
   }
   else{
    digitalWrite(r4, LOW);
   }
  }
   void dhtdata()
   {{
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}
}

   
