void WindowRead(){
  window_magnet();
  if(client.connect(host, httpPort)){
    data = "window=";
    data.concat(win);
      Serial.println("connected window");
    client.println("POST /ihome/api/door/insertwin.php HTTP/1.1");
    client.println( "Host: ucstaungoo.000webhostapp.com");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
    win = "";
    }else {
    Serial.println("connection failed");
    }
    if(client.connected()){
      client.stop();
    }
}
