void master_ssd1306(){
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);

  display.print(page);
  switch(1){
    case 1:
      display.print(" Home");
      ssd1306_grafik( dhtLogH, (sizeof(dhtLogH)/sizeof(dhtLogH[0])) ,100,25, 0,10,false);
      ssd1306_grafik( dhtLogT, (sizeof(dhtLogT)/sizeof(dhtLogT[0])) ,100,25, 0,36,false);
      //ssd1306_Home(dhtLogT, (sizeof(dhtLogT) / sizeof(dhtLogT[0]) ),dhtLogH, (sizeof(dhtLogH) / sizeof(dhtLogH[0]) ));
      break;
    case 2:
      display.print(" Suhu (*C)");
      ssd1306_grafik( dhtLogT, (sizeof(dhtLogT)/sizeof(dhtLogT[0])) ,100,37, 0,18, true);
      break;
    case 3:
      display.print(" Humid (%rH)");
      ssd1306_grafik( dhtLogH, (sizeof(dhtLogH)/sizeof(dhtLogH[0])) ,100,37, 0,18,true);
      break;
    case 4:
      display.print(" Heat Index");
      ssd1306_grafik( dhtLogHI, (sizeof(dhtLogHI)/sizeof(dhtLogHI[0])) ,100,37, 0,18,true);
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
void ssd1306_grafik(int angkaData[0],byte n, byte grafikL,byte grafikT, byte frameX, byte frameY, bool label){
  int maxVal = angkaData[0];
  int minVal = angkaData[0];
  for (int16_t i = 0; i < n; i++) {
    maxVal = max(angkaData[i],maxVal);
    minVal = min(angkaData[i],minVal);
  }
  int jarakAntarTitik = grafikL/n;
  int x0,y0,x1,y1;
  for(int16_t i=0; i<n-1; i++) {
    x0 = (i*jarakAntarTitik)+frameX;
    y0 = map(angkaData[i],minVal-2,maxVal+2,frameY+grafikT,frameY);
    x1 = x0+jarakAntarTitik;
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