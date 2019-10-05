void sendSensor(){
  data = "temperature=";
    data.concat(t);
    data.concat("&humidity=");
    data.concat(h);
    data.concat("&light=");
    data.concat(light_send);
    data.concat("&flame=");
    data.concat(flame_sensorReading);
    data.concat("&motion=");
    data.concat(motion_send);
    data.concat("&water=");
    data.concat(water_distance);
    
    //delay(1000);
    if(client.connect(host, httpPort)){
      Serial.println("connected data");
      //request client
    client.println("POST /ihome/api/arduino/insertdata.php HTTP/1.1");
    client.println( "Host: ucstaungoo.000webhostapp.com");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
    if(motion_send==1){motion_send=0;}
    }else {
    Serial.println("connection failed");
    }
    if(client.connected()){
      data="";
      client.stop();
    }
}

