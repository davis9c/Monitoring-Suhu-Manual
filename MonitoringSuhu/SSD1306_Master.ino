void master_ssd1306(){
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);
  String dataList[6];
  display.print(page);
  display.print(selector);
  switch(page){
    case 1://Halaman Home
      display.print(" Home");
      ssd1306_grafik( dhtLogH, dhtLog ,100,25, 0,10,false);
      ssd1306_grafik( dhtLogT, dhtLog ,100,25, 0,36,false);
      break;
    case 2://Halaman Suhu
      display.print(" Suhu (*C)");
      ssd1306_grafik( dhtLogT, dhtLog ,100,37, 0,18, true);
      break;
    case 21://Halaman Suhu > Detail
      display.println(" (i)Suhu");
      dataList[0]= String((float)dhtLogT[(dhtLog-1)]/10,1);
      dataList[1]= String((float)dhtLogTCal/10,1);
      dataList[2]= String(-0.1);
      dataList[3]= String(true);
      dataList[4]= String(50.1);
      dataList[5]= String((float)1/10,1);
      dataList[6]= "<<";
      daftarPilih(dataList,7);
      break;
    case 3://Halaman Humid
      display.print(" Humid (%rH)");
      ssd1306_grafik( dhtLogH, dhtLog ,100,37, 0,18,true);
      break;
    case 31://Halaman Kelembaban > Detail
      display.println(" (i)Kelembaban");
      float kelembaban = ( dhtLogH[(dhtLog-1)] - dhtLogHCal );
      float kalibrasi = dhtLogHCal;
      dataList[0]= String( (float)(kelembaban-kalibrasi)/10, 1 ) + " | " + String( (float)calHBuff/10, 1 );
      dataList[1]= String( (float)kalibrasi/10, 1);
      dataList[2]= String(-0.1, 1);
      dataList[3]= String(true);
      dataList[4]= String(50.1, 1);
      dataList[5]= String((float)1/10, 1);
      dataList[6]= "<<";
      daftarPilih(dataList,7);break;
    case 4://Halaman Heat Index
      display.print(" Heat Index C");
      ssd1306_grafik( dhtLogHI, dhtLog ,100,37, 0,18,true);
      break;
    case 5://Halaman About
      display.print(" About");
      break;
  }
  display.display();
  displayUpdate = false;
}
void daftarPilih(String data[],byte n){
  for(uint8_t i=0; i<n; i++) {
    if( i+1 == selector ){
      display.setTextColor(BLACK, WHITE);
      display.print(">");
    }else{
      display.setTextColor(WHITE );
      display.print(" ");
    }
    display.println(data[i]);
  }
  
}
void ssd1306_grafik(int angkaData[0],uint8_t n, uint8_t grafikL,uint8_t grafikT, uint8_t frameX, uint8_t frameY, bool label){
  int maxVal = angkaData[0];
  int minVal = angkaData[0];
  for (uint8_t i = 0; i < n; i++) {
    maxVal = max(angkaData[i],maxVal);
    minVal = min(angkaData[i],minVal);
  }
  uint8_t x0,y0,x1,y1;
  for(uint8_t i=0; i<n-1; i++) {
    x0 = (i*(grafikL/n))+frameX;
    y0 = map(angkaData[i],minVal-2,maxVal+2,frameY+grafikT,frameY);
    x1 = x0+(grafikL/n);
    y1 = map(angkaData[i+1],minVal-2,maxVal+2,frameY+grafikT,frameY);  
    display.drawLine( x0, y0, x1 ,y1 , SSD1306_WHITE);
  }
  display.setCursor(x1+3, y1-3);
  display.print((float)angkaData[n-1]/10,1);
  if(label==true){
    display.setCursor(frameX, frameY-8);
    display.print((float)maxVal/10,1);
    display.setCursor(frameX, frameY+grafikT+2);
    display.print((float)minVal/10,1);
  }
}