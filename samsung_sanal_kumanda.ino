/*
 * definitely visit...
https://www.youtube.com/channel/UCPPBrcYj6yDUcKBamCzIDNg?view_as=subscriber
 * 
 * project video
 * https://youtu.be/Md8_0fxJVrw
 */



#define BLYNK_PRINT Serial
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Samsung.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRSamsungAc ac(kIrLed);  

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "qvewZqVaZ_aqhS5dvdrfx6FrihEJ7jQ1";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "projenet";
char pass[] = "227986ia"; // kendi WİFİ parolanızı bu kısma giriyorsunuz.

boolean Ac;
boolean kapat;
boolean hizli;
boolean yavas;
boolean sogut;
boolean isit;
int sicaklik;

String cevirici;

BLYNK_WRITE_DEFAULT() {
  Serial.print("input V");
  Serial.print(request.pin);
  Serial.println(":");
  // Print all parameter values
  for (auto i = param.begin(); i < param.end(); ++i) {
    Serial.print("* ");
    Serial.println(i.asString());

    if(request.pin == 0) // eger bylink den gelen virtual  0 ise (V0 açma komutu olarak atamıştık)
    {
      cevirici = i.asString();
      Ac = cevirici.toInt();
    }
    
    if(request.pin == 1)
    {
      cevirici = i.asString();
      kapat = cevirici.toInt();
    }
    
    if(request.pin == 2)
    {
      cevirici = i.asString();
      sicaklik = cevirici.toInt();
    }
    
    if(request.pin == 3)
    {
      cevirici = i.asString();
      sogut = cevirici.toInt();
    }
    
    if(request.pin == 4)
    {
      cevirici = i.asString();
      isit = cevirici.toInt();
    }
    
    if(request.pin == 5)
    {
      cevirici = i.asString();
      yavas = cevirici.toInt();
    }
    
    if(request.pin == 6)
    {
      cevirici = i.asString();
      hizli = cevirici.toInt();
    }
    
  }
}



void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  ac.begin();
}

void loop()
{
  Blynk.run();

  switch(Ac)
  {
    case 1:
    ac.on();
    ac.setTemp(25);
    ac.setSwing(false);
    ac.send();
    delay(1000);
    break;
    default:
    break;
  }
  switch(kapat)
  {
    case 1:
    ac.off();
    ac.send();
    delay(1000);
    break;
    default:
    break;
  }
  switch(sogut)
  {
    case 1:
    ac.on();
    ac.setMode(kSamsungAcCool);
    ac.setTemp(20);
    ac.send();
    delay(1000);
    break;
    default:
    break;
  }
  switch(isit)
  {
    case 1:
    ac.on();
    ac.setMode(kSamsungAcHeat);
    ac.setTemp(28);
    ac.send();
    delay(1000);
    break;
    default:
    break;
      }

      switch(yavas)
      {
        case 1:
        ac.setFan(kSamsungAcFanLow);
        ac.send();
        delay(500);
        break;
        default:
        break;
      }
      switch (hizli)
      {
        case 1:
        ac.setFan(kSamsungAcFanHigh);
        ac.send();
        delay(500);
        break;
        default:
        break;
      }
      if (sicaklik >17 && sicaklik < 31)
      {
        ac.on();
        ac.setTemp(sicaklik);
        ac.send();
        delay(500);
      }
      else{}
}
