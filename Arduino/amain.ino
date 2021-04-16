#include <Adafruit_GFX.h>    // Adafruit's core graphics library
#include <Adafruit_TFTLCD.h> // Adafruit's hardware-specific library
#include <TouchScreen.h>     //Touchscreen library
#include <SD.h>       
#include <SPI.h>
#include <Wire.h>
#include "ListLib.h"

#define YP A2                 // must be an analog pin
#define XM A3                 // must be an analog pin
#define YM 8                  // can be a digital pin
#define XP 9                  // can be a digital pin

#define TS_MINX 100
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define SD_SCK 13         
#define SD_MISO 12  
#define SD_MOSI 11
#define SD_CS 10

#define BACK       0x39C7
#define BLACK      0x0000
#define BLUE       0x64DF
#define RED        0xF800
#define WHITE      0xFFFF
#define GREY       0x9CD2
#define SILVER     0xC618
#define GREEN      0x2608
#define C_GREEN    0x07F6
#define YELLOW     0xFEA0

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

List<int> code;               //Para almacenar números

char *sel_img[] = {"fab.bmp", "ari.bmp"};
String producto_1[5] = {"Jabon en polvo", "ARIEL", "Doble Poder", "4 Kg", "$ 31.200"};
String producto_2[5] = {"Fabuloso", "Limpiador liquido", "Fresca Lavanda", "2 Litros", "$ 11.590"};
 
//int myID[] = {1, 0, 2, 4, 5, 5, 3, 2, 6, 6};
//int mycode[] = {1, 2, 3, 4};

int currentpage;
int producto;

const int act = 22;             //para habilitar comunicación con ESP32
const int liquido = 32;         //para habilitar electrovalvula y minibomba
const int solido = 33;          //para habilitar motor          
char msm_to_send[14];
String msm_rcd = "null";
bool check_user = false;

void setup(){
  Serial.begin(115200);
  Serial1.begin(9600);
  
  pinMode(act, OUTPUT);
  //pinMode(liquido, OUTPUT);
  //pinMode(solido, OUTPUT);
  digitalWrite(act, LOW);
  //digitalWrite(liquido, LOW);
  //digitalWrite(solido, LOW);
  
  Wire.begin(1);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
               
  if (!SD.begin(SD_CS, SD_MOSI, SD_MISO, SD_SCK )) 
  {
    tft.println(F("failed!"));      
    return;
  }

  tft.reset();
  tft.begin(0x9341);
  tft.fillScreen(BLACK);
  tft.setRotation(1);
  
  currentpage = 1;
  load();
  start();
}

void loop(){
  TSPoint p = ts.getPoint();     // Read touchscreen
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT); 

if (p.z > 10 && p.z < 1000) {
//###################################################################################################################################
  if (currentpage == 1){
    if (p.y > 290 && p.y < 385 && p.x > 310 && p.x < 790){
      delay(100);
      rst_page(2);
      second_page();
    }
      p.x = 0;
      p.y = 0;
  }
//###################################################################################################################################
  if (currentpage == 2){
    if (p.x > 355 && p.x < 735 && p.y > 135 && p.y < 195){
      rst_page(1);
       start();
    }else if (p.y > 234 && p.y < 535 && p.x > 580 && p.x < 835){//selecciona protex
       write_txt(180,185,2,RED,"AGOTADO"); 
     }else if (p.y > 234 && p.y < 535 && p.x > 280 && p.x < 527){//selecciona salvo
        write_txt(65,185,2,RED,"AGOTADO");
      }else if (p.y > 570 && p.y < 877 && p.x > 580 && p.x < 835){//selecciona fab
         rst_page(5);
         producto = 0;
         fourth_page(sel_img[0], 30, producto_2, "Cargando...");
       }else if (p.y > 570 && p.y < 877 && p.x > 280 && p.x < 527){//selecciona ariel
          rst_page(5);
          fourth_page(sel_img[1], 30, producto_1, "Cargando...");
          producto = 1;
        }
//    Serial.println("X " + String(p.x));
//    Serial.println("Y " + String(p.y));  
      p.x = 0;
      p.y = 0;
  }
//###################################################################################################################################  
  if (currentpage == 3){
    if(p.x > 735 && p.x < 905 && p.y > 140 && p.y < 275){
      rst_page(2);
      second_page();
    }else if (p.x > 735 && p.x < 905 && p.y > 353 && p.y < 488){
       keyboard(1, 1, 60);
      }else if(p.x > 735 && p.x < 905 && p.y > 548 && p.y < 700){
         keyboard(0, 0, 60);
        }else if (p.x > 199 && p.x < 690 && p.y > 137 && p.y < 700){
           keyboard(int(p.x), int(p.y), 60);
         }    
       p.x = 0;
       p.y = 0;
  }
//###################################################################################################################################  
  if(currentpage == 4){
    delay(1000);
    rst_page(3);
       p.x = 0;
       p.y = 0;
    third_page("Ingrese documento ID");
  }
//###################################################################################################################################  
  if(currentpage == 5){
    if(p.x > 597 && p.x < 753 && p.y > 145 && p.y < 275){ //cancelar
      rst_page(2);
      second_page();         
    }else if (p.x > 361 && p.x < 517 && p.y > 145 && p.y < 275){
       rst_page(3);
       third_page("Ingrese documento ID");
     }
  }
       p.x = 0;
       p.y = 0;
 }
//###################################################################################################################################  

}
