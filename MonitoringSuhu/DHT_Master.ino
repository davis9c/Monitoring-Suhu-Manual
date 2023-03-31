void master_dht(){
  int h = dht.readHumidity()*10 + dhtLogTCal;
  int t = dht.readTemperature()*10 +dhtLogHCal;
  int hic = dht.computeHeatIndex((float)t/10, (float)h/10, false)*10;
  if (isnan(h) || isnan(t) || isnan(hic)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  for( uint8_t i = 0 ; i < dhtLog ; i++ ){
    if( i == dhtLog-1 ){
      dhtLogH[i] = h;
      dhtLogT[i] = t;
      dhtLogHI[i] = t;
    }else{
      dhtLogH[i] = dhtLogH[i+1];
      dhtLogT[i] = dhtLogT[i+1];
      dhtLogHI[i] = dhtLogHI[i+1];
    }
  }
}