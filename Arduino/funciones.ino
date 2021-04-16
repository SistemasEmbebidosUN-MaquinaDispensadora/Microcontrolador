//###################################################################################################################################
void start(){
  tft.fillScreen(BLACK);
  square(0, 0, 319, 240, 8, BACK, WHITE); 
  write_txt(65, 40, 4, C_GREEN, "ECOVERRE");
  write_txt(55, 100, 2, WHITE, "Ingresa tu envase");
  square(60, 150, 200, 40, 8, SILVER, SILVER);
  write_txt(70, 165, 2, WHITE, "COMENZAR COMPRA");
}

//###################################################################################################################################
void load(){
  write_txt(30, 70, 2, YELLOW, "Creado por:");
  write_txt(30, 100, 2, YELLOW, "Embebidos grupo 5.");
  write_txt(50, 140, 3, WHITE, "Cargando...");
  delay(1000); 
}

//###################################################################################################################################
void error(String msm_1, String msm_2){
  square(0, 0, 319, 240, 8, WHITE, WHITE);
  bmpDraw("img3.bmp", 120, 40); 
  write_txt(115, 140, 3, BLACK, msm_1);
  write_txt(95, 180, 3, BLACK, msm_2);
  code.Clear();
}

//###################################################################################################################################
void thanks(){
  tft.fillScreen(BLACK);
  square(0, 0, 319, 240, 8, BACK, WHITE); 
  write_txt(65, 40, 4, C_GREEN, "ECOVERRE");
  write_txt(65, 100, 2, WHITE, "Retira el envase");
  square(60, 150, 200, 40, 8, GREEN, GREEN);
  write_txt(120, 165, 2, WHITE, "GRACIAS");
  delay(5000); 
}

//###################################################################################################################################
void llenado(char *img, int space, String productos[5], String accion){
  square(0, 0, 319, 240, 8, BACK, WHITE);
  square(5, 5, 310, 170, 8, WHITE, BLACK);
  write_txt(110, 200, 2, WHITE, accion);
  for (int i = 0; i < 5; i++){
    write_txt(175, space=space+20, 1, BLACK, productos[i]);
  }
  bmpDraw(img, 7, 10); 
}

//###################################################################################################################################
void second_page(){   
  char *img[] = {"img1.bmp", "img2.bmp", "img4.bmp", "img5.bmp"};   
  square(0, 0, 319, 240, 8, BACK, WHITE);
  write_txt(110, 215, 2, WHITE, "cargando...");
  
  for (int16_t i = 0; i <= 0; i++){
    for (int16_t n = 5; n <= 105; n=n+100) {
      for (int16_t k = 50; k <= 165; k=k+115) {
        square(k, n, 110, 97, 8, WHITE, WHITE);
        bmpDraw(img[i++], k+13, n+8);
      }
    }
  }
  square(80, 207, 170, 15, 8, BACK, BACK);
  square(80, 205, 160, 30, 8, SILVER, SILVER);
  write_txt(120, 214, 2, WHITE, "VOLVER");
}

//###################################################################################################################################
void third_page(String accion){
  tft.fillScreen(BLACK);
  square(0, 0, 319, 240, 8, BACK, WHITE);
  write_txt(30, 5, 2, WHITE, accion);
  square(65, 26, 190, 25, 8, WHITE, WHITE);
  for (int16_t i = 1; i <= 1; i++) {
    for (int16_t n = 61; n <= 149; n=n+44) {
      for (int16_t k = 20; k <= 160; k=k+70){
        square(k, n, 60, 40, 8, SILVER, WHITE);
        write_txt(k+10, n+15, 2, WHITE, String(i++));
      }
    }
  } 
  square(90, 193, 60, 40, 8, SILVER, WHITE);
  write_txt(100, 208, 2, WHITE, "0");
  square(230, 61, 75, 53, 8, RED, RED);
  write_txt(250, 83, 1, WHITE, "BORRAR");
  square(230, 120, 75, 53, 8, GREEN, GREEN);
  write_txt(240, 143, 1, WHITE, "CONFIRMAR");  
  square(230, 180, 75, 53, 8, YELLOW, YELLOW);
  write_txt(250, 204, 1, WHITE, "VOLVER");
}

//###################################################################################################################################
void fourth_page(char *img, int space, String productos[5], String accion){
  square(0, 0, 319, 240, 8, BACK, WHITE);
  square(5, 5, 310, 170, 8, WHITE, BLACK);
  write_txt(110, 215, 2, WHITE, accion);
  for (int i = 0; i < 5; i++){
    write_txt(175, space=space+20, 1, BLACK, productos[i]);
  }
  bmpDraw(img, 7, 10);
  square(80, 207, 170, 25, 8, BACK, BACK);
  square(80, 180, 75, 53, 8, SILVER, SILVER);
  write_txt(100, 204, 1, WHITE, "LLENAR");  
  square(170, 180, 75, 53, 8, SILVER, SILVER);
  write_txt(185, 204, 1, WHITE, "CANCELAR");
}

//###################################################################################################################################
void square(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color1, uint16_t color2) {
tft.fillRoundRect(x0, y0, w, h, radius, color1);
tft.drawRoundRect(x0, y0, w, h, radius, color2);
}

//###################################################################################################################################
void write_txt(int16_t x, int16_t y, uint8_t size, uint16_t color, String frase){
tft.setCursor(x, y);
tft.setTextSize(size);
tft.setTextColor(color);
tft.println(frase);
}

//###################################################################################################################################
void rst_page(int cp) {
  delay(100);
  currentpage = cp;  
}

//###################################################################################################################################  
void keyboard(int x, int y, int n){
  if (x > 560 && x < 690) {//3c
          if (y > 290 && y < 377) {//9
              code.Add(9);
            }else if (y > 438 && y < 535) { //6
              code.Add(6);
             }else if (y > 603 && y < 700) { //3
              code.Add(3);
              }
         }else if (x > 386 && x < 514) { //2c
           if (y > 137 && y < 225) {//0
            code.Add(0);
           }else if (y > 290 && y < 377) { //8
              code.Add(8);
            }else if (y > 438 && y < 535) { //5
              code.Add(5);
             }else if (y > 603 && y < 700) { //2
              code.Add(2);
              }
          }else if (x > 199 && x < 325) { //1c
            if (y > 290 && y < 377) {//7
              code.Add(7);
            }else if (y > 438 && y < 535) { //4
              code.Add(4);
             }else if (y > 603 && y < 700) { //1
              code.Add(1);
              }
           }else if (x == 0 && y == 0) {
              square(65, 26, 190, 25, 8, WHITE, BLACK);
              code.RemoveLast();
            }else if (x == 1 && y == 1) {
              int* number = code.ToArray();
              String h;
              for (int q = 0; q < code.Count(); q++){
                 h = h + String(number[q]);
              }
              //h="["+h+"|"+String(producto)+"]";
              h="["+h+"]";
              h.toCharArray(msm_to_send, 14);
              //Se envía enable al ESP32 
              digitalWrite(act , HIGH);
              delay(500);
              digitalWrite(act, LOW);
              
              Serial.println("msm to send: " + h);
              while(msm_rcd == "null"){
              //Serial.println("waiting for confirmation from mqtt broker: " + msm_rcd);
              square(65, 26, 190, 25, 8, WHITE, WHITE); 
              write_txt(75, 32, 2, BLACK, "buscando...");
              delay (1000);
              }
              
              if(check_user == false){
               if(msm_rcd == "true"){
                check_user = true;
                code.Clear();
                square(65, 26, 190, 25, 8, WHITE, WHITE);
                square(65, 2, 250, 20, 8, BACK, BACK);
                write_txt(30, 5, 2, WHITE, "Ingrese clave usuario");
                msm_rcd = "null";
               }else if(msm_rcd == "false"){
                code.Clear();
                msm_rcd = "null";
                rst_page(4);
                error("USUARIO", "INVALIDO");
               }
             }else if(check_user == true){
                if(msm_rcd == "true"){
                  code.Clear();
                  rst_page(1);
                  if (producto == 0){
                    check_user = false;
                    msm_rcd = "null";
                    //digitalWrite(liquido, HIGH);
                    llenado(sel_img[producto], 30, producto_2,"Llenando..."); //Acá es para poner un loop mientras se llena el recipiente.
                    Serial1.write(1);
                    delay(10000);
                    Serial1.write(0);
                    //digitalWrite(liquido, LOW);
                  }else if (producto == 1){
                    check_user = false;
                    msm_rcd = "null";
                    //digitalWrite(solido, HIGH);
                    llenado(sel_img[producto], 30, producto_1,"Llenando..."); //Acá es para poner un loop mientras se llena el recipiente.
                    Serial1.write(2);
                    delay(10000);
                    Serial1.write(0);
                    //digitalWrite(solido, LOW);
                  }
                  thanks();
                  start(); 
                }else{
                  check_user = false;
                  code.Clear();
                  msm_rcd = "null";
                  rst_page(4);
                  error("CODIGO", "INVALIDO");
                }
              }
            }
 if (x != 1 && y != 1){           
  for (int i = 0; i < code.Count(); i++){
    write_txt(n=n+15, 32, 2, BLACK, String(code[i]));
  }          
 delay(300);
 }          
}

//###################################################################################################################################  
void receiveEvent(int howMany) {
 char c;
 String msm_rc;
   while (0 <Wire.available()) {
    c = Wire.read();      /* receive byte as a character */
    msm_rc = msm_rc + String(c);
   }
  msm_rcd = msm_rc;
  Serial.println("msm_received: " + msm_rcd);
}

//###################################################################################################################################  
// function that executes whenever data is requested from master
void requestEvent() {
 Wire.write(msm_to_send);  /*send string on request */
 *msm_to_send = "";
 Serial.println("se envía a ESP32");
}

//###################################################################################################################################  
#define BUFFPIXEL 80          
void bmpDraw(char *filename, int x, int y) {
  File     bmpFile;
  int      bmpWidth, bmpHeight;   
  uint8_t  bmpDepth;              
  uint32_t bmpImageoffset;        
  uint32_t rowSize;               
  uint8_t  sdbuffer[3*BUFFPIXEL]; 
  uint16_t lcdbuffer[BUFFPIXEL];  
  uint8_t  buffidx = sizeof(sdbuffer); 
  boolean  goodBmp = false;       
  boolean  flip    = true;        
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();
  uint8_t  lcdidx = 0;
  boolean  first = true;
  if ((bmpFile = SD.open(filename)) == NULL) {
    progmemPrintln(PSTR("File not found"));
    return;
  }
  if(read16(bmpFile) == 0x4D42) { 
    progmemPrint(PSTR("File size: ")); Serial.println(read32(bmpFile));
    (void)read32(bmpFile);
    bmpImageoffset = read32(bmpFile);
    progmemPrint(PSTR("Image Offset: "));
    progmemPrint(PSTR("Header size: ")); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) {
      bmpDepth = read16(bmpFile);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) {
        goodBmp = true;
        rowSize = (bmpWidth * 3 + 3) & ~3;
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;
        tft.setAddrWindow(x, y, x+w-1, y+h-1);
        
        for (row=h-1; row>0; row--) { 
            pos = bmpImageoffset + row * rowSize;
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer);
          for (col=0; col<w; col++) {
            if(buffidx >= sizeof(sdbuffer)) {
               bmpFile.read(sdbuffer, sizeof(sdbuffer));
               buffidx = 0;
            }
            if(lcdidx > 0 ) {
               tft.pushColors(lcdbuffer, lcdidx, first);
               lcdidx = 0;
               first  = false;
            }
            lcdbuffer[lcdidx++] = tft.color565(sdbuffer[buffidx++],sdbuffer[buffidx++],sdbuffer[buffidx++]);
          }
        }  
      }
    }
  }
  bmpFile.close();
  //if(!goodBmp) progmemPrintln(PSTR("BMP format not recognized."));
}

uint16_t read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read();
  ((uint8_t *)&result)[1] = f.read();
  return result;
}
uint32_t read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read();
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read();
  return result;
}
void progmemPrint(const char *str) {
  char c;
  while(c = pgm_read_byte(str++));
}
void progmemPrintln(const char *str) {
  progmemPrint(str);
}
