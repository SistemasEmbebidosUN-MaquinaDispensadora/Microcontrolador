void sensors(void*){          
  
  VOID SETUP(){             
    Serial.println("Iniciando sensores de temperatura y humedad"); 
    //Iniciar el DHT1
    dht.begin();
    //Iniciar el DHT2
    dht2.begin();
    delay(50);
    //iniciar sensores de distancia
    pinMode(SHT_LOX1, OUTPUT);
    pinMode(SHT_LOX2, OUTPUT);
    Serial.println("Shutdown pins inited...");
    digitalWrite(SHT_LOX1, LOW);
    digitalWrite(SHT_LOX2, LOW);
    Serial.println("Both in reset mode...(pins are low)");
    Serial.println("Starting...");
    setID();
  }

  VOID LOOP() { 
    dht_function();
    delay(50);
    read_dual_sensors();
    delay(50);
  }

}
//FUNCIONES DHT 1

float  ReadDHTTemperature(){
  float t =  dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return 0;
    }
    else {
      Serial.println(t);
      return t;
      }
  }

float  ReadDHTHumidity() {
   float h = dht.readHumidity();
   if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return 0; 
    }
     else {
      Serial.println(h);
      return h;
      }
  }

//FUNCIONES DHT 2

float  ReadDHTTemperature2(){
  float t2 =  dht2.readTemperature();
  if (isnan(t2)) {
    Serial.println("Failed to read from DHT sensor!");
    return 0;
    }
    else {
      Serial.println(t2);
      return t2;
      }
  }

float  ReadDHTHumidity2() {
   float h2 = dht2.readHumidity();
   if (isnan(h2)) {
    Serial.println("Failed to read from DHT sensor!");
    return 0;  
    }
     else {
      Serial.println(h2);
      return h2;
      }
  }
 	
void dht_function(){
  //Temperatura.publish (ReadDHTTemperature());
   dht_msm= dtostrf(ReadDHTTemperature(), 6, 2, msm_to_send_mqtt);
   client.publish("DHT22/t", dht_msm);
   //Humedad.publish (ReadDHTHumidity());
   dht_msm= dtostrf(ReadDHTHumidity(), 6, 2, msm_to_send_mqtt);
   client.publish("DHT22/h", dht_msm);
   delay(1000);
   //Temperatura2.publish (ReadDHTTemperature2());
   dht_msm= dtostrf(ReadDHTTemperature2(), 6, 2, msm_to_send_mqtt);
   client.publish("DHT22/t2", dht_msm);
   //Humedad2.publish (ReadDHTHumidity2());
   dht_msm= dtostrf(ReadDHTHumidity2(), 6, 2, msm_to_send_mqtt);
   client.publish("DHT22/h2", dht_msm);
   delay(1000);
}

//Funciones sensores distancia 

void setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  // activating LOX1 and reseting LOX2
  digitalWrite(SHT_LOX2, LOW);
  delay(10);

  // initing LOX1
  Wire.begin();
  lox1.begin(LOX1_ADDRESS);
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);
  
  //initing LOX2
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
}

void read_dual_sensors() {
  
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!

  // print sensor one reading
  Serial.print("1: ");
  if(measure1.RangeStatus != 4) {     // if not out of range
    sensor1 = measure1.RangeMilliMeter;    
    Serial.print(sensor1);
    Serial.print("mm");    
  } else {
    Serial.print("Out of range");
  }
  
  Serial.print(" ");

  // print sensor two reading
  Serial.print("2: ");
  if(measure2.RangeStatus != 4) {
    sensor2 = measure2.RangeMilliMeter;
    Serial.print(sensor2);
    Serial.print("mm");
  } else {
    Serial.print("Out of range");
  }
  
  Serial.println();
}
