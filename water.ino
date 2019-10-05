void WaterRead(){
  client.setTimeout(1000);
  if (!client.connect(host, 80)) {
    Serial.println(F("Connection failed"));
    return;
  }

  Serial.println(F("Connected!"));

  client.print(String("GET ") + path_water + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" +
    "Connection: keep-alive\r\n\r\n");

    delay(500);

 String section = "header";
 
  while(client.available()){
    String line = client.readStringUntil('\r');
    if(section == "header"){
      Serial.print(".");
      if(line == "\n"){
        section = "json";
      }
    }else if(section == "json"){
      section = "ignore";
      String result = line.substring(1);

      int size = result.length() + 1;
      char json[size];

      result.toCharArray(json,size);
      
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      if(!json_parsed.success()){
        Serial.println("parseObject() failed");
        return;
      }
      Serial.println(" ");
          int min = json_parsed["min"];
          int max = json_parsed["max"];
        if(json_parsed["auto"] == "1"){
          
          if(water_distance >= max){
            flag = true;
          }
          if(water_distance <= min){
            flag = false;
          }
          if(flag){
            digitalWrite(pump, LOW);
            Serial.println("Mode : Auto >> Pump : ON");
          }else{
            digitalWrite(pump,HIGH);
            Serial.println("Mode : Auto >> Pump : OFF");
          }
        }else if(json_parsed["auto"] == "0"){
          if(json_parsed["pump"] == "1"){
            digitalWrite(pump, LOW);
            Serial.println("Mode : Manual >> Pump : ON");
          }
          if(json_parsed["pump"] == "0"){
            digitalWrite(pump, HIGH);
            Serial.println("Mode : Manual >> Pump : OFF");
          }
        }
      }
  }
  client.stop();
  Serial.println("close connection");
}
