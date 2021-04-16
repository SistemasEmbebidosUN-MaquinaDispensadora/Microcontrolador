#include <TridentTD_EasyFreeRTOS32.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_VL53L0X.h>

#define mqttPort 1883                           //Definimos puerto de comunicación MQTT
//#define mqttUser "ESP32"
//#define mqttPassword "1234"
 
#define SHT_LOX1 32                             //Declaración de los pines de shutdown
#define SHT_LOX2 33

#define LOX1_ADDRESS 0x28
#define LOX2_ADDRESS 0x29
int sensor1,sensor2;

#define DHTPIN 25 //27	     			   //Definir puerto para DHT1
#define DHTTYPE DHT22

#define DHTPIN2 26 //26 			   //Definir puerto para DHT2
#define DHTTYPE DHT22

const char* ssid = "Familia Junco";                   // ingresamos WiFi SSID
const char* password =  "oscarJUNCO21fr";             // ingresamos WiFi password
const char* mqttServer = "192.168.0.7";        // ingresamos dirección mqtt broker
//const char* mqttServer = "10.42.0.29";

//const int timeout = 200;                              //Definir constante de tiempo máximo permitido para establecer conexión
const int act = 23;                                   // pin para habilitar comunicción con display
int id_check = 2;
char msm_to_send_mqtt [14];
char *dht_msm;

WiFiClient espClient;                           //creamos un cliente WiFi
PubSubClient client(espClient);                 //creamos un cliente mqtt

DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
//Adafruit_VL53L0X lox = Adafruit_VL53L0X();      //Declarar sensor
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;

void mqtt_reconnect();
void callback(char* topic, byte *payload, unsigned int length); 
void setup_wifi();
void receive_from_arduino();
void send_to_arduino(char msm[]);

TridentOS   task1;  // asignacipon de tareas
void sensors(void*); //iniciamos las funciones principales de cada tarea

void setup() {
  Serial.begin(115200); 
  Serial.println();

  pinMode(act, INPUT);                          //establecemos como entrada el pin para comunicación con display
  Wire.begin(21, 22);                           //Iniciamos comunicación I2C con arduino - ESP32 Master
      
  Serial.setTimeout(500);                       // Establecemos tiempo límite de espera comunicación serial 
  setup_wifi();                                 //Arrancamos WiFi
  client.setServer(mqttServer, mqttPort);       //Establecemos enlace con servidor mqtt en raspberry
  client.setCallback(callback);                 //Recibe respuesta del servidor mqtt
  mqtt_reconnect();                             //Para reconectar con mqtt
  
  pinMode(2,OUTPUT);
  task1.start(sensors);
  delay(50);
}

void loop() {
client.loop();
  if(digitalRead(act) == HIGH){
    task1.stop();
    delay(50);
    digitalWrite(2,HIGH);
      receive_from_arduino();
      while(id_check == 2){
        client.loop();
        Serial.println("esperando respuesta de mqtt");
        delay(1000);
      }
      Serial.println("ya hay respuesta");
      if(id_check == 1){
        Serial.println("enviando a arduino confirmación");
        send_to_arduino("true");
        id_check = 2;
        delay(50);
      }else if(id_check == 0){
        Serial.println("enviando a arduino negación");
        send_to_arduino("false");
        id_check = 2;
        delay(600);
      }
      task1.start(sensors);
      digitalWrite(2,LOW);
  }
}

void send_to_arduino(char msm[]){
  Wire.beginTransmission(1); /* begin with device address 8 */
  Wire.write(msm);  /* sends hello string */
  Wire.endTransmission();    /* stop transmitting */
}

void receive_from_arduino(){
  Serial.println("Voy a leer datos");
  static boolean recvInProgress = false;
  char c;
  String msm_rc;
  Wire.requestFrom(1, 14);                          //solicita a slave (1) enviar información con 10 caracteres
  if(Wire.available()){
  while(Wire.available()){                          //mientras lleguen caracteres al puerto se lee y se imprime
    c = Wire.read();
    if (recvInProgress == true){
      if (c != ']'){
        msm_rc = msm_rc + String(c);
        //Serial.println("Estoy leyendo el msm");
      }else if(msm_rc.length() == 5){
        recvInProgress = false;
        msm_rc.toCharArray(msm_to_send_mqtt, 14);
        client.publish("test/user", msm_to_send_mqtt);
        Serial.println("user_id: " + msm_rc);
      }else if(msm_rc.length() == 4){
        recvInProgress = false;
        msm_rc.toCharArray(msm_to_send_mqtt, 14);
        client.publish("test/code", msm_to_send_mqtt); 
        Serial.println("code_id: " + msm_rc);
      }else{
        recvInProgress = false;
        Serial.println("El tamaño del msm no coincide");
        Serial.println("msm_rcd: " + msm_rc);
        id_check = 0;
      }
    }else if (c == '['){
       recvInProgress = true; 
    }
  }
 }else{
  Serial.println("No hay datos");
 }
}

void callback(char* topic, byte *payload, unsigned int length) {
    Serial.println();
    Serial.println("-------new message from broker-----");
    Serial.print("channel:");
    Serial.println(topic);
    Serial.print("data:");  
    Serial.write(payload, length);
    Serial.println();
    if(!strncmp((char *)payload, "1", length)){
      Serial.println("Solicitud validada"); 
      id_check = 1;
    }else if(!strncmp((char *)payload, "0", length)){
      Serial.println("Solicitud denegada");
      id_check = 0;
    }else{
      Serial.println("Fatal error");
      delay(1000);
      id_check = 2;
    }
}

void setup_wifi() {                                 //Para realizar conexión WiFi
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void mqtt_reconnect() {                                             //Para realizar conexión con MQTT
  while (!client.connected()) {                                     // Loop until we're reconnected
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP-WROOM-32";                               // Create a random client ID
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {                         // Attempt to connect
      Serial.println("connected");
      client.publish("test/text", "Bienvenido Ecoverre");               //Once connected, publish an announcement...
      client.subscribe("test/confirm");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);                                                  // Wait 5 seconds before retrying
    }
  }
}
