void master_ssd1306(){
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);

  display.print(page);
  switch(page){
    case 1:
      display.print(" Home");
      ssd1306_Home(dhtLogT, (sizeof(dhtLogT) / sizeof(dhtLogT[0]) ),dhtLogH, (sizeof(dhtLogH) / sizeof(dhtLogH[0]) ));
      break;
    case 2:
      display.print(" Suhu (*C)");
      ssd1306_grafik( dhtLogT, (sizeof(dhtLogT) / sizeof(dhtLogT[0]) ) );
      break;
    case 3:
      display.print(" Humid (%rH)");
      ssd1306_grafik( dhtLogH, (sizeof(dhtLogH) / sizeof(dhtLogH[0]) ) );
      break;
    case 4:
      display.print(" Heat Index");
      ssd1306_grafik( dhtLogHI, (sizeof(dhtLogHI) / sizeof(dhtLogHI[0]) ) );
      break;
    default:
    break;
  }
  
  display.display();
  displayUpdate = false;
}
void ssd1306_Home(int T[0],byte nT,int H[0],byte nH){
  display.setTextSize(2);
  display.println(F(""));
  display.setCursor(10, 18);
  display.print((float)T[nT-1]/10,1);display.println(F(" 'C"));
  display.setCursor(10, 35);
  display.print((float)H[nH-1]/10,1);display.println(F(" %rH"));
}
void ssd1306_grafik(int angkaData[0],byte n){
  int maxVal = angkaData[0];
  int minVal = angkaData[0];
  for (int16_t i = 0; i < n; i++) {
    maxVal = max(angkaData[i],maxVal);
    minVal = min(angkaData[i],minVal);
  }
  
  int jarakAntarTitik = (100)/n;
  int x0;
  int y0;
  int x1;
  int y1;
  for(int16_t i=0; i<n-1; i++) {
    x0 = (i*jarakAntarTitik)+5;
    y0 = map(angkaData[i],minVal-2,maxVal+2,54,17);//54,17 adalah ketinggian grafik
    x1 = (i*jarakAntarTitik)+5+jarakAntarTitik;
    y1 = map(angkaData[i+1],minVal-2,maxVal+2,54,17);  
    display.drawLine( x0, y0, x1 ,y1 , SSD1306_WHITE);
  }
  display.setCursor(x1+3, y1-3);
  display.print((float)angkaData[n-1]/10,1);
  display.setCursor(10, 10);
  display.print((float)maxVal/10,1);
  display.setCursor(10, 56);
  display.print((float)minVal/10,1);
}