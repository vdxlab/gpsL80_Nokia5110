//   pantalles 2


// GPS L80 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define rxGPS A0
#define txGPS A1     

    long lat,lon; 
    int counter = 0;     
    SoftwareSerial gpsSerial(rxGPS,txGPS); 
    TinyGPSPlus gps;

    int c=0;
#include<stdlib.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// LCD //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The pins to use on the arduino
#define PIN_RESET 9
#define PIN_SCE   8
#define PIN_DC    7
#define PIN_SDIN  6
#define PIN_SCLK  5 
 
// COnfiguration for the LCD
#define LCD_C     LOW
#define LCD_D     HIGH
#define LCD_CMD   0
 
// Size of the LCD
#define LCD_X     84
#define LCD_Y     48
 
int scrollPosition = -10;

// per jugar amb diferents tamanys de caracters
#include<LCD5110_Basic.h>
  LCD5110 myGLCD(5,6,7,9,8);
  extern uint8_t SmallFont[];
  extern uint8_t MediumNumbers[];
  extern uint8_t BigNumbers[];

// per jugar amb els polsadors per canviar la pantalla mostrada
volatile int pantalla;
#define boto_dret 2
#define boto_esquerre 3

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const byte ASCII[][5] =
{
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c ¥
,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ←
,{0x00, 0x06, 0x09, 0x09, 0x06} // 7f →
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void LcdCharacter(char character)         
{
  LcdWrite(LCD_D, 0x00);
  for (int index = 0; index < 5; index++)
  {
    LcdWrite(LCD_D, ASCII[character - 0x20][index]);
  }
  LcdWrite(LCD_D, 0x00);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LcdClear(void)
{
  for (int index = 0; index < LCD_X * LCD_Y / 8; index++)
  {
    LcdWrite(LCD_D, 0x00);
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LcdInitialise(void)
{
  pinMode(PIN_SCE,   OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC,    OUTPUT);
  pinMode(PIN_SDIN,  OUTPUT);
  pinMode(PIN_SCLK,  OUTPUT);
 
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);
 
  LcdWrite(LCD_CMD, 0x21);  // LCD Extended Commands.
  LcdWrite(LCD_CMD, 0xBf);  // Set LCD Vop (Contrast). //B1
  LcdWrite(LCD_CMD, 0x04);  // Set Temp coefficent. //0x04
  LcdWrite(LCD_CMD, 0x14);  // LCD bias mode 1:48. //0x13
  LcdWrite(LCD_CMD, 0x0C);  // LCD in normal mode. 0x0d for inverse
  LcdWrite(LCD_C, 0x20);
  LcdWrite(LCD_C, 0x0C);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void LcdString(char *characters)
{
  while (*characters)
  {
    LcdCharacter(*characters++);
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LcdWrite(byte dc, byte data)
{
  digitalWrite(PIN_DC, dc);
  digitalWrite(PIN_SCE, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_SCE, HIGH);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * gotoXY routine to position cursor
 * x - range: 0 to 84
 * y - range: 0 to 5
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gotoXY(int x, int y)
{
  LcdWrite( 0, 0x80 | x);  // Column.
  LcdWrite( 0, 0x40 | y);  // Row.
}
 
void drawBox(void)
{
  int j;
  for(j = 0; j < 84; j++) // top
  {
    gotoXY(j, 0);
    LcdWrite(1, 0x01);
  }     
 
  for(j = 0; j < 84; j++) //Bottom
  {
    gotoXY(j, 5);
    LcdWrite(1, 0x80);
  }     
 
  for(j = 0; j < 6; j++) // Right
  {
    gotoXY(83, j);
    LcdWrite(1, 0xff);
  }     
 
  for(j = 0; j < 6; j++) // Left
  {
    gotoXY(0, j);
    LcdWrite(1, 0xff);
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scroll(String message)
{
  for (int i = scrollPosition; i < scrollPosition + 11; i++)
  {
    if ((i >= message.length()) || (i < 0))
    {
      LcdCharacter(' ');
    }
    else	
    {
      LcdCharacter(message.charAt(i));
    }
  }
  scrollPosition++;
  if ((scrollPosition >= message.length()) && (scrollPosition > 0))
  {
    scrollPosition = -10;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        
void polsador_esquerre() 
{
    pantalla=1 ;// Serial.println (pantalla);// aquet serial.print pot fer que es pengi l'arduino.... OJO !!!!
}
        
void polsador_dret() 
{
    pantalla=0 ; //Serial.println (pantalla);// aquet serial.print pot fer que es pengi l'arduino.... OJO !!!!
}


//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------

    void setup()
    {
      //  GPS
      Serial.begin(9600); // connect serial
      gpsSerial.begin(9600); // connect gps sensor
      
      //  LCD
      LcdInitialise();
 //     LcdClear();
   myGLCD.InitLCD();
      drawBox();
      gotoXY(7,1);
      LcdString("Nokia 5110");
     
      gotoXY(17,2);
      LcdString("GPS L80");   
     
      gotoXY(3,3);
      LcdString("pantalles 2");   
      
      pinMode(boto_dret, INPUT_PULLUP);
      digitalWrite(boto_dret, HIGH);
      pinMode(boto_esquerre, INPUT_PULLUP);
      digitalWrite(boto_dret,HIGH);
   
      attachInterrupt(0, polsador_dret, FALLING);
      attachInterrupt(1, polsador_esquerre, FALLING);
   
    }


//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------


    void loop(){
      while(!gpsSerial.available() & c==0){ // check for NO gps data
      gotoXY(4,4);
      Scroll("waiting for gpsSerial.available");
      delay(10);
      }
      
      while(gpsSerial.available()){ // check for gps data
        if(gps.encode(gpsSerial.read())){ // encode gps data
   //       if(counter > 50) {  // uns 8s 
          if(counter > 1) {     // uns 1s
           Serial.println("");
           Serial.println("---------------------------");
           Serial.print("SATS: ");
           Serial.println(gps.satellites.value());
           Serial.print("LAT: ");
           Serial.println(gps.location.lat(), 6);
           Serial.print("LONG: ");
           Serial.println(gps.location.lng(), 6);
           Serial.print("ALT: ");
           Serial.println(gps.altitude.meters());
           Serial.print("SPEED: ");
           Serial.println(gps.speed.mps()*3.6); //  km/h
   
           Serial.print("Date: ");
           Serial.print(gps.date.day()); Serial.print("/");
           Serial.print(gps.date.month()); Serial.print("/");
           Serial.println(gps.date.year());
   
           Serial.print("Hour: ");
           Serial.print(gps.time.hour()+1); Serial.print(":");  //  horari espana:    estiu_(GMT+2)     hivern_(GMT+1)
           Serial.print(gps.time.minute()); Serial.print(":");
           Serial.println(gps.time.second());
           Serial.println("---------------------------");
           Serial.print (pantalla);
           Serial.println("---");
         
   
           LcdClear();
   
        // PART COMU A LES DUES PANTALLES        
   
           gotoXY(0,0);
           LcdString("SATS: ");
           char sats [10];  //="12345";
           sprintf (sats, "%i", gps.satellites.value());
           LcdString(sats);
       
           gotoXY(14,5);
          // LcdString("hora ");
           char hora [3];-
           sprintf (hora, "%i", gps.time.hour()+1);  //  horari espana:    estiu_(GMT+2)     hivern_(GMT+1)
           char minut [3];
           sprintf (minut, "%i", gps.time.minute());
           char segon [3];
           sprintf (segon, "%i", gps.time.second());
       
           LcdString(hora);
           LcdString(":");
           LcdString(minut);
           LcdString(" :");
           LcdString(segon);
             
          
           switch (pantalla) {
           case 0:
      
        // imprimint al lcd la primera pantalla amb la velocitat 
       
           gotoXY(0,3);  
           LcdString("Km/h:    ");
           char VELOCITAT [3];
           dtostrf(gps.speed.mps()*3.3,3,0,VELOCITAT);     // km/h   //    dtostrf(gps.speed.mps(),7,0,velocitat);     // metres per segon
           myGLCD.setFont(BigNumbers);                    
           myGLCD.print(String (VELOCITAT), 42, 15);    //    myGLCD.print(String velocitat, int x, int y);
                                                        // void	print(char *st, int x, int y);
                                                        // void	print(String st, int x, int y);
                                                        // void	printNumI(long num, int x, int y, int length=0, char filler=' ');
                                                        // printNumF(double num, byte dec, int x, int y, char divider='.', int length=0, char    gotoXY(14,5);
           break;
      
           case 1:
        // imprimint al lcd la segona pantalla amb totes les dades
            
           gotoXY(0,1);
           LcdString("lat:");
           char latitud [10];  
           dtostrf(gps.location.lat(),6,5,latitud);     // dtostrf(float_a_convertir, digits_totals, digits_despres_dela_coma, string_convertida); // #include stdlib.h
           LcdString(latitud);
             
           gotoXY(0,2); 
           LcdString("lon:");
           char longitud [10];  //="12345";
           dtostrf(gps.location.lng(),8,5,longitud);     // dtostrf(float_a_convertir, digits_totals, digits_despres_dela_coma, string_convertida); // #include stdlib.h
           LcdString(longitud); 
      
           gotoXY(0,3);
           LcdString("alt: ");
           char alt [6];
           dtostrf(gps.altitude.meters(),7,0,alt);     // dtostrf(float_a_convertir, digits_totals, digits_despres_dela_coma, string_convertida); // #include stdlib.h
           LcdString(alt);
      
           gotoXY(0,4);  
           LcdString("Km/h:    ");
           char velocitat [3];
           dtostrf(gps.speed.mps()*3.3,3,0,velocitat);     // km/h   //    dtostrf(gps.speed.mps(),7,0,velocitat);     // metres per segon
           LcdString(velocitat);
          
           break;
           }
          
           counter = 0;
           c=1;
          }                        // if linea 346
          else counter++;
  
        }                       // if linea 345
      }                          // if linea 344
    }                            // while linea 343

