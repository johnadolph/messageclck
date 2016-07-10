// Sketch Build 3.0 compiled on Arduino 1.0.6    . 
// copy the sketch below and paste it into the Arduino IDE verify, and run the program.
// this sketch was created using code from the adafruit-libraries

#include "pitches.h" 
#define sclk 13
#define mosi 11
#define cs   10
#define dc   9
#define rst  8 

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h> // Serial Peripheral Interface (SPI) is a synchronous serial data protocol 
#include <Wire.h> // library needed for RTC
#include "RTClib.h" //RTC Library
RTC_DS1307 RTC;

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

// notes  for Darth Vader's Theme Song
 int melody1[] = {
   NOTE_G4, NOTE_G4,NOTE_G4, NOTE_DS4, NOTE_AS4, NOTE_G4, NOTE_DS4, NOTE_AS4, NOTE_G4, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_DS5, NOTE_AS4, NOTE_FS4, NOTE_DS4, NOTE_AS4, NOTE_G4, NOTE_G5, NOTE_G4, NOTE_G4, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_E5, NOTE_DS5, NOTE_E5, 0, NOTE_GS4, NOTE_CS5, NOTE_C5, NOTE_B4, NOTE_AS4, NOTE_A4, NOTE_AS4, 0, NOTE_DS4, NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_AS4, NOTE_G4, NOTE_AS4, NOTE_D5, NOTE_G5, NOTE_G4, NOTE_G4, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_E5, NOTE_DS5, NOTE_E5, 0, NOTE_GS4, NOTE_CS5, NOTE_C5, NOTE_B4, NOTE_AS4, NOTE_A4, NOTE_AS4, 0, NOTE_DS4, NOTE_FS4, NOTE_DS4, NOTE_AS4, NOTE_G4, NOTE_DS4, NOTE_AS4, NOTE_G4 };
// note durations for Darth Vader's Theme Song: 4 = quarter note, 8 = eighth note, etc.:
 int noteDurations1[] = {
   4, 4, 4, 6, 16, 4, 6, 16, 2, 4, 4, 4, 6, 16, 4, 6, 16, 2, 4, 6, 16, 4, 6, 16, 16, 16, 8, 8, 8, 4, 6, 16, 16, 16, 8, 8, 8, 4, 6, 16, 4, 6, 16, 2, 4, 6, 16, 4, 6, 16, 16, 16, 8, 8, 8, 4, 6, 16, 16, 16, 8, 8, 8, 4, 6, 16, 4, 6, 16, 2,};
 int buzzer = 7; // tone output pin, connect buzzer or speaker + to this pin

// happy birthday theme
 int length = 28; // the number of notes

char notes[] = "GGAGcB GGAGdc GGxecBA yyecdc";

int beats[] = { 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8,8, 16, 1, 2,2,8,8,8,8,16, 1,2,2,8,8,8,16 };

int tempo = 150;
void playTone(int tone, int duration) {

 for (long i = 0; i < duration * 1000L; i += tone * 2) {

   digitalWrite(buzzer, HIGH);

   delayMicroseconds(tone);

   digitalWrite(buzzer, LOW);

   delayMicroseconds(tone);

 }

}

void playNote(char note, int duration) {

 char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',           

                 'c', 'd', 'e', 'f', 'g', 'a', 'b',

                 'x', 'y' };

 int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,

                 956,  834,  765,  593,  468,  346,  224,

                 655 , 715 };

 int SPEE = 5;

 // play the tone corresponding to the note name

 for (int i = 0; i < 17; i++) {

   if (names[i] == note) {
    int newduration = duration/SPEE;
     playTone(tones[i], newduration);

   }

 }

}
void setup(void) {
   pinMode(buzzer, OUTPUT);
   pinMode(6, OUTPUT);
   pinMode(5, OUTPUT); // RGB LED Pins
   pinMode(4, OUTPUT);
   pinMode(3, OUTPUT); // RGB LED GND
   pinMode (A3, OUTPUT);                  //  Plug the clock board into pins A2 through A5
   digitalWrite (A3, HIGH);               //  Using pin A3 as a supply voltage to the clock board (VCC)
   pinMode (A2, OUTPUT);                  //  Using pin A2   as ground for the RTC (GND)
   digitalWrite (A2, LOW);                //  Set this pin low so that it acts as Ground for the clock
   delay(500);
   Wire.begin();
   RTC.begin();
 // RTC.adjust(DateTime(__DATE__, __TIME__));
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK); // Clear screen
  tft.setRotation(0);
  
   if (! RTC.isrunning()) { 
    tft.println("  RTC was NOT running!");
    tft.println("     Resetting RTC ");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
    }
 }
 

void loop() {
  tft.drawRoundRect(0, 0, 125, 80, 15, ST7735_GREEN);
  //tft.drawRoundRect(0, 80, 125, 80, 15, ST7735_GREEN);
   tft.setTextColor(ST7735_YELLOW,ST7735_BLACK);//set text color & size for  DATE coming from TinyRTC
      tft.setTextSize(2);
      tft.setCursor(10,20);
      DateTime now = RTC.now();
      if(now.month()>9) {tft.setTextSize(1);}
      tft.print(now.month(), DEC);
      tft.print('/');
      tft.print(now.day(), DEC);
      tft.print('/');
      tft.print(now.year(), DEC);
      tft.setCursor(15,50);
      tft.setTextColor(ST7735_MAGENTA,ST7735_BLACK); //set color for TIME
      tft.setTextSize(2);//set text  size for  TIME coming from TinyRTC
    //tft.print(now.hour(), DEC);
      if(now.hour()< 10) { //PRINT A 0 IN FRONT OF THE MINUTE IF LESS THAN 10
      tft.print('0'); 
      tft.print(now.hour(), DEC);
      }
       else {
       tft.print(now.hour(), DEC);
      }
      tft.print(':');
      if(now.minute() < 10) { //PRINT A 0 IN FRONT OF THE MINUTE IF LESS THAN 10
      tft.print('0'); 
      tft.print(now.minute(), DEC);
      }
       else {
       tft.print(now.minute(), DEC);
      }
       tft.print(':');
      if(now.second() < 10) {//PRINT A 0 IN FRONT OF THE SECONDS IF LESS THAN 10
      tft.print('0'); 
      tft.print(now.second(), DEC);
      }
       else {
       tft.print(now.second(), DEC);
      }
     if (now.hour()==0 && now.minute()== 26){
         
         roundrects();
     }  
     if (now.month()==12 && now.day()== 25){
       tft.setCursor(5,100);
       tft.setTextColor(ST7735_RED,ST7735_BLACK);
       tft.print(" MERRY " );
       tft.setCursor(5,120);
       tft.print("CHRISTMAS");
     
      } 
      if (now.month()==1 && now.day()== 1){
       tft.setCursor(5,100);
       tft.setTextColor(ST7735_RED,ST7735_BLACK);
       tft.print("  HAPPY " );
       tft.setCursor(5,120);
       tft.print(" NEW YEAR");
       }
       
      
      if (now.month()== 10 && now.day()== 24 && now.minute()==25 ){
       tft.setCursor(2,100);
       tft.setTextColor(ST7735_GREEN,ST7735_BLACK);
       tft.print("  HAPPY  " );
       tft.setCursor(2,120);
       tft.print(" BIRTHDAY ");
        tft.setCursor(2,140);
       tft.print("  NAME");
       for (int i = 0; i < length; i++) {
       int rgb = random(4,7);
        
       if (notes[i] == ' ') {

      delay(beats[i] * tempo); // rest

     } else {
  
      playNote(notes[i], beats[i] * tempo);
       digitalWrite(rgb,HIGH);
     }

     // pause between notes

     delay(tempo);
     digitalWrite(rgb,LOW);
 }
      } 
   else {   
       tft.setCursor(5,100);
       tft.setTextColor(ST7735_YELLOW,ST7735_BLACK);
       tft.drawRoundRect(0, 80, 125, 80, 15, ST7735_GREEN);
       tft.print("  HAVE A " );
       tft.setCursor(2,120);
       tft.print("   NICE ");
       tft.setCursor(5,140);
       tft.print("   DAY  ");
            }
   if ( now.month()==5 && now.day() ==4 && now.minute() ==0){
       tft.setCursor(0,100);
       tft.setTextColor(ST7735_RED,ST7735_BLACK);
       tft.print("May The 4" );
       tft.setTextSize(1);
       tft.print("th" );
       tft.setTextSize(2);
       tft.setCursor(5,120);
       tft.print("B WITH U!");
         
         for (int thisNote = 0; thisNote < 70; thisNote++) {  // play 70 notes... 
         int rgb = random(4,7);
         digitalWrite(rgb,HIGH);
         int noteDuration1 = 1000/noteDurations1[thisNote];  // sets up note duration for Darth Vader's Theme
         tone(buzzer, melody1[thisNote],noteDuration1);  //  play Darth Vader's Theme
         digitalWrite(rgb,LOW);
         int pauseBetweenNotes = noteDuration1 * 1.60;  // sets the tempo for the song
         delay(pauseBetweenNotes);  // pauses the buzzer
         
         noTone(buzzer);  // stops the buzzer playing
         }
      } 
     
   }

void roundrects() {
  tft.fillScreen(ST7735_BLACK);
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 80;
    int w = 125;
    int h = 80;
    for(i = 0 ; i <= 25; i+=1) {
      tft.drawRoundRect(x, y, w, h, 15, color);
      x+=1;
      y+=1;
      w-=2;
      h-=2;
      color+=1100;
    }
    color+=100;
  }
}



