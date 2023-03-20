void master_dht(){
  int h = dht.readHumidity()*10;
  int t = dht.readTemperature()*10;
  int hic = dht.computeHeatIndex((float)t/10, (float)h/10, false)*10;
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  int dataH = (sizeof(dhtLogH)/sizeof(dhtLogH[0]));
  for( int16_t i = 0 ; i < dataH ; i++ ){
    if(i==dataH-1){
      dhtLogH[i] = h;
    }else{
      dhtLogH[i] = dhtLogH[i+1];
    }
  }
  int dataT = (sizeof(dhtLogT)/sizeof(dhtLogT[0]));
  for( int16_t i = 0 ; i < dataT ; i++ ){
    if(i==dataT-1){
      dhtLogT[i] = t;
    }else{
      dhtLogT[i] = dhtLogT[i+1];
    }
  }
  int dataHI = (sizeof(dhtLogHI)/sizeof(dhtLogHI[0]));
  for( int16_t i = 0 ; i < dataHI ; i++ ){
    if(i==dataHI-1){
      dhtLogHI[i] = t;
    }else{
      dhtLogHI[i] = dhtLogHI[i+1];
    }
  }
}