#define PIR_MOTION_SENSOR D0//Use pin 2 to receive the signal from the module 
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

#include "TFT_eSPI.h" //include TFT LCD library 
#include "Free_Fonts.h"
/*
//pour wifi
#include <rpcWiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
// Set these to your desired credentials.
const char* ssid = "Project_IoT_grp_4";
const char* password = "IoT_pwd_!";
WiFiServer server(80); //Initialize Wi-Fi Server on port 80
*/

TFT_eSPI tft; //initialize TFT LCD 
TFT_eSprite spr = TFT_eSprite(&tft); //initialize buffer

int pir_detection = 0; //is detection du PIR passe a 1
int sonor_lvl_high = 0; //si le micro indique qu'il y a trop de bruit il passe à 1, 0 sinon
int nb_occupant = 0;
int mode = 0;
int first_eco = 1; //evite de reactualiser l'ecran a chaque fois
//bool wifi_on = false; //indique que le wifi est allumé

void setup()
{
 	//Pin setup
 	pinMode(PIR_MOTION_SENSOR, INPUT);
	pinMode(LED_BUILTIN,OUTPUT);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP); //si bouton préssé, simule fin de detection caméra
  pinMode(WIO_5S_LEFT, INPUT_PULLUP); //si bouton a gauche, simule trop de son
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);//si bouton a droite, simule que le son est bon
  pinMode(WIO_KEY_A, INPUT_PULLUP);
  pinMode(WIO_KEY_B, INPUT_PULLUP);
  pinMode(WIO_KEY_C, INPUT_PULLUP);
  

  //Interruption setup  
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_A), passage_mode_normal, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_B), passage_mode_eco, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_KEY_C), passage_mode_debug, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_5S_LEFT), _Too_loud_from_micro, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_5S_RIGHT), _Not_Too_loud_from_micro, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIO_5S_PRESS), _No_PeopleDetected_PIR, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIR_MOTION_SENSOR), _PeopleDetected_PIR, RISING);  
  
  /*
  //partie wifi
  Serial.begin(115200);
  while(!Serial); // Wait for Serial to be ready
  delay(1000);
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP(); 
  Serial.print("AP IP address: ");
  Serial.println(myIP); //Record this IP, will used by Client (such as Web Browser)
  server.begin();
  Serial.println("Server started");
  */

  //Screen setup
  tft.begin(); //start TFT LCD
  tft.setRotation(3); //set screen rotation
  spr.createSprite(TFT_HEIGHT,TFT_WIDTH); //create buffer
  spr.fillSprite(TFT_BLACK); //fill background
  delay(1000);

  randomSeed(analogRead(0));//pour le taux d'occupation
}

void loop() 
{ 
  if (mode == 0) 
  {
    mode_demarage();
  }

  else if (mode == 1) 
  {
    mode_normal();
  }

  else if (mode == 2) 
  {
    mode_eco();
  }

  else if (mode == 3) 
  {
    mode_debug();
  }
  delay(1000);
}

void mode_demarage()//mode = 0
{
  //démarage écran
  start_screen(); 
  spr.drawString("Demarage ", 115, 10); //draw text string 
  spr.drawFastHLine(40, 35, 240, TFT_DARKGREY); //draw horizontal line
  spr.setTextColor(TFT_WHITE);
  //delay(1000);

  spr.drawString("Selectionnez un mode :", 20, 50);
  spr.drawString("Bouton droite -> normal", 20, 100);
  spr.drawString("Bouton milieu -> eco", 20, 135);
  spr.drawString("Bouton gauche -> debug", 20, 170);

  spr.pushSprite(0,0);
  spr.deleteSprite();
}

void passage_mode_normal() 
{
  mode = 1;
  if (first_eco == 0) //on vient du mode eco, il faut allumer l'ecran
  {
    digitalWrite(LCD_BACKLIGHT, HIGH);
    first_eco = 1; //au prochain passage en eco on nettoie l'ecran
  }
}

void mode_normal() //mode = 1
{
  //démarage écran
  start_screen(); 
  digitalWrite(LED_BUILTIN,LOW);
  spr.drawString("Normal mode -- Sensor info", 15, 10); //draw text string 
  spr.drawFastHLine(40, 35, 240, TFT_DARKGREY); //draw horizontal line
  spr.setTextColor(TFT_WHITE);
  digitalWrite(LED_BUILTIN,LOW);
  //delay(1000);
  if(pir_detection == 1) {
    Serial.println("camera on");
    spr.drawString("Camera is ON", 20, 50);
    //si l'esp32 est on, il va envoyer des informations
    if (sonor_lvl_high)
    {
      Serial.println("sonor_lvl_high");
      spr.drawString("Salle Agite", 20, 85);
      flash_the_LED(); //si il y a trop de bruit la LED clignote
    }
    else {
      Serial.println("sonor_lvl_low");
      spr.drawString("Salle Silencieuse", 20, 85);
    }
    
    //affichage taux d'occupation
    nb_occupant = random(1, 10);
    spr.drawNumber(nb_occupant, 20, 120);
    spr.drawString("personnes presentes", 50, 120);
  }
  else if (pir_detection == 0){
    Serial.println("camera off");
    spr.drawString("Camera is OFF", 20, 50);
  }
  else { //case when pir_detection is not defined
    digitalWrite(LED_BUILTIN,LOW);
    spr.drawString("ERROR DETECTED", 20, 50);
  }
  spr.pushSprite(0,0);
  spr.deleteSprite();  
}

void passage_mode_eco() 
{
  mode = 2;
}

void mode_eco() //mode = 2
{
  if (first_eco) //reset de l'ecran si on vient d'un autre mode
    {
      start_screen();
      spr.fillSprite(TFT_BLACK); //fill background
      spr.pushSprite(0,0);
      spr.deleteSprite();
      digitalWrite(LCD_BACKLIGHT, LOW);
      first_eco = 0;
    }

  if(pir_detection == 1) {
    Serial.println("pir_detection -> camera started");
    digitalWrite(LED_BUILTIN,HIGH);
    if (sonor_lvl_high) {
      flash_the_LED(); //si il y a trop de bruit la LED clignote
      Serial.println("ALLERT Confort sonore NOK");
    }
  }
  else {
    digitalWrite(LED_BUILTIN,LOW);
    Serial.println("pir_detection == 0");
    Serial.println("Confort sonore OK");
  }
}

void passage_mode_debug() 
{
  mode = 3;
  if (first_eco == 0) //on vient du mode eco, il faut allumer l'ecran
  {
    digitalWrite(LCD_BACKLIGHT, HIGH);
    first_eco = 1; //au prochain passage en eco on nettoie l'ecran
  }
  
}

void mode_debug() //mode = 3
{
  //démarage écran
  start_screen(); 
  spr.drawString("Debug mode", 100, 10); //draw text string 
  spr.drawFastHLine(40, 35, 240, TFT_DARKGREY); //draw horizontal line
  spr.setTextColor(TFT_WHITE);
  //delay(1000);

  spr.drawString("pir_detection :", 20, 50);
  spr.drawNumber(pir_detection, 255, 50);
  spr.drawString("sonor_lvl :", 20, 85);
  spr.drawNumber(sonor_lvl_high, 255, 85);
  spr.drawString("Personnes presentes :", 20, 120);
  spr.drawNumber(nb_occupant, 255, 120);
  
  spr.pushSprite(0,0);
  spr.deleteSprite();
  
  flash_the_LED();
}


void start_screen()
{
  //écriture
  spr.createSprite(TFT_HEIGHT,TFT_WIDTH); //create buffer
  spr.fillSprite(TFT_BLACK); //fill background 
  spr.setFreeFont(FMB9); // set font type
  //spr.setTextSize(2); //set text size 
  spr.setTextColor(TFT_YELLOW); //set text color 
}


void flash_the_LED()
{
	digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
}

void _PeopleDetected_PIR() 
//interrupt launched when peop detected on PIR sensor
{
  pir_detection = 1;
}

void _No_PeopleDetected_PIR() 
/*interrupt launched when no peop detected on camera
simulate with right button (A BUTTON) */
{
  //pir_detection = 0;
  //test sans pir connecté au wio
  if (pir_detection) pir_detection = 0;
  else pir_detection = 1;
  
}

void _Too_loud_from_micro()
{
  sonor_lvl_high = 1;
}

void _Not_Too_loud_from_micro()
{
  sonor_lvl_high = 0;
}

/*
void allumage_wifi()
{
  WiFiClient client = server.available();   // listen for incoming clients
 
    if (client) {                             // if you get a client,
        Serial.println("New Client.");           // print a message out the serial port
        String currentLine = "";                // make a String to hold incoming data from the client
        while (client.connected()) {            // loop while the client's connected
            if (client.available()) {             // if there's bytes to read from the client,
                char c = client.read();             // read a byte, then
                Serial.write(c);                    // print it out the serial monitor
                if (c == '\n') {                    // if the byte is a newline character
 
                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0) {
                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();
 
                        // the content of the HTTP response follows the header:
                        client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
                        client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");
 
                        // The HTTP response ends with another blank line:
                        client.println();
                        // break out of the while loop:
                        break;
                    } else {    // if you got a newline, then clear currentLine:
                        currentLine = "";
                    }
                } else if (c != '\r') {  // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }
 
                // Check to see if the client request was "GET /H" or "GET /L":
                if (currentLine.endsWith("GET /H")) {
                    digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
                }
                if (currentLine.endsWith("GET /L")) {
                    digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
                }
            }
        }
        // close the connection:
        client.stop();
        Serial.println("Client Disconnected.");
    }
  wifi_on = true; //on valide que le wifi est allumé
}*/