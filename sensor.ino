void flame_sensor_read(){
  flame_sensorReading = analogRead(flame_sensor);
  Serial.print("Flame     : ");
  Serial.println(flame_sensorReading);
  
   if(flame_sensorReading < 200){
    fireSound();
    call_direct();
  }
  else{
    noTone(buzz);
  }
}
void light_sensor_read(){
   light_sensorReading = analogRead(light_sensor);
   light_send = map (light_sensorReading,0,1023,0,100);
   Serial.print("Light       : ");
   Serial.println(light_sensorReading);
   if(light_sensorReading<500){
    digitalWrite(out_light,LOW);
   }else{
    digitalWrite(out_light,HIGH);
   }
   delay(1);
}
void temp_sensor_read(){
  //delay(2000);
  h = dht.readHumidity();
  t = dht.readTemperature();
  
    if (isnan(h) || isnan(t)) {
    Serial.print("ERROR");
    return;
  }
  Serial.print("Temperature : ");
  Serial.println(t);
  Serial.print("Humidity    : ");
  Serial.println(h);
}
void pir_sensor_read(){
  pir_sensorReading=digitalRead(pir_sensor);
  Serial.print("Motion      : ");
  Serial.println(pir_sensorReading);
  if(pir_sensorReading == HIGH){
    motionSound();
    motion_send = 1;
    call_back();     
  }
  if(pir_sensorReading == LOW){
    noTone(buzz);
  }
}
void water_ultrasonic(){
  water_distance = water_level.Ranging(CM);
  Serial.print("Distance    : ");
  Serial.print(water_distance);
  Serial.println("cm");
}
void window_magnet(){
  win = "";
  for(int i=0;i<4;i++){
    win += String(!digitalRead(window[i]));
  }
  Serial.print("Window      : ");
  Serial.println(win);
}

