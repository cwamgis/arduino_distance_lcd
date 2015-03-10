// Ecran LCD
#include <LiquidCrystal.h>

/* Code basé sur : 
https://itechnofrance.wordpress.com/2013/03/12/utilisation-du-module-ultrason-hc-sr04-avec-larduino/
*/

/* Utilisation du capteur Ultrason HC-SR04 */

// capteur ultra sonique
#define ULTRA_SON_TRIG 46
#define ULTRA_SON_ECHO 31

// les deux LED
#define LED 49
#define LED2 41

// nb de cm pour affichage distinctif LED
#define DISTANCE_LED 50

// lecture echo et conversion en cm
long lecture_echo;
long cm;

// Ecran LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup()
{
  pinMode(ULTRA_SON_TRIG, OUTPUT);// initialisation trigger as output pour la carte
  digitalWrite(ULTRA_SON_TRIG, LOW); // On envoi du low
  
  pinMode(ULTRA_SON_ECHO, INPUT);// initialisation echo as input pour la carte
  Serial.begin(9600); // data rate in bits per second 
  
  // initialisation  LED
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  
   lcd.begin(16, 2);              // Lance la librarie LCD (16 caractères x 2 lignes)
   lcd.setCursor(0,0); //En haut à gauche (numéroté depuis 0)
   lcd.print("distance en cm"); // Afficher un petit message
}

void loop()
{

  
  // 10 us de high pour trig pour lancer le capteur ultra sonique
  digitalWrite(ULTRA_SON_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRA_SON_TRIG, LOW);
  
  // on recupere l echo
  lecture_echo = pulseIn(ULTRA_SON_ECHO, HIGH);
  cm = lecture_echo / 58;
  // Affichage moniteur
  Serial.print("pouet : ");
  Serial.println(cm);
  // Affichage LCD
   lcd.setCursor(0,1);   //Ligne du bas
     lcd.print("                   ");   //Effacer cette ligne
   lcd.setCursor(0,1);   //Ligne du bas
   lcd.print(cm);   // distance

  // affichage LED selon seuil de distance
  if (cm < DISTANCE_LED)
  {
    digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED2, LOW);  
}
  else 
 {
   digitalWrite(LED2, HIGH);  
   digitalWrite(LED, LOW);  
 } 
  
  delay(500);
}

