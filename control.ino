void JsonRead(){
  client.setTimeout(1000);
  if (!client.connect(host, 80)) {
    Serial.println(F("Connection failed"));
    return;
  }

  Serial.println(F("Connected!"));

  client.print(String("GET ") + path_switch + " HTTP/1.1\r\n" +
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
      Serial.print("Devices : >> ");
      for(int i=0;i<10;i++){
        Serial.print(json_parsed[String(devices[i])].as<char*>());
        Serial.print(" ");
        if(strcmp(json_parsed[String(devices[i])],"0") == 0){
          digitalWrite(devices[i], HIGH);
        }else{
          digitalWrite(devices[i],LOW);
        }
      }
    }
  }
  client.stop();
  Serial.println(" ");
  Serial.println("close connection");
}
