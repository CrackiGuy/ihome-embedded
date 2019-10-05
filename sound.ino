void fireSound (){
  int i =0;
     for(i=500;i<800;i++){
     tone(buzz,i);
     delay(15);
     }
     for(i=800;i>500;i--){
     tone(buzz,i);
     delay(15);
     }
     noTone(buzz);
}
void motionSound(){
  tone(buzz,1000,1000);
}

