void master_joystick(){
  
  if( joystickReady == true && millis() > mlsOfJoystickUpdate ){
    //Serial.println(Joystick.Up());
    joystickReady = false;
  }
  
  /*
  Joystick.readX();
  Joystick.readY();
  Joystick.readX();
  Joystick.readY();
  joystickUpdate = false
  Joystick.Up()
  Joystick.Down()
  Joystick.Right()
  Joystick.Left()
  Joystick.readButton()
  */
  if((joystickReady == false)){
    joystickNavMenu();
  }
}
void joystickNavMenu(){
  //bool Up = false;
  //bool Down = false;
  //bool Left = false;
  //bool Right = false;
  bool Up = Joystick.Left();
  bool Down = Joystick.Right();
  bool Left = Joystick.Down();
  bool Right = Joystick.Up();
  bool Button = Joystick.readButton();

  switch(page){
    case 1://Nav Home
      if(Right == HIGH){
        page =2;selector = 1;joystickUsed();
      }
      if(Left == HIGH){
        page =5;selector = 1;joystickUsed();
      }
      break;
    case 2:
      if(Right == HIGH){
        page =3;selector = 1;joystickUsed();
      }
      if(Left == HIGH){
        page =1;selector = 1;joystickUsed();
      }
      if(Button == HIGH){
        page = 21;joystickUsed();
      }
      break;
    case 21:
      if(Up == HIGH){
        selector-=1;
        if(selector < 1){
          selector =7;
        }
        joystickUsed();
      }
      if(Down == HIGH){
        selector+=1;joystickUsed();
        if(selector > 7 ){
          selector = 1;
        }
      }
      if(Left == HIGH){
        page = 2;joystickUsed();
      }
      
      break;
    
    case 3:
      if(Right == HIGH){
        page =4;selector = 1;joystickUsed();
      }
      if(Left == HIGH){
        page =2;selector = 1;joystickUsed();
      }
      if(Button == HIGH){
        page = 31;joystickUsed();
      }
      break;
    
    case 31:
      if(Up == HIGH){
        selector-=1;
        if(selector< 1){
          selector = 7;
        }
        joystickUsed();
      }
      if(Down == HIGH){
        selector+=1;joystickUsed();
        if(selector > 7 ){
          selector = 1;
        }
      }
      if(selector == 7 && Button == HIGH){
        page = 3;
        joystickUsed();
      }
      break;
    case 4:
      if(Right == HIGH){
        page =5;selector = 1;joystickUsed();
      }
      if(Left == HIGH){
        page =3;selector = 1;joystickUsed();
      }
      break;
    case 5:
      if(Right == HIGH){
        page = 1;selector = 1;joystickUsed();
      }
      if(Left == HIGH){
        page = 4;selector = 1;joystickUsed();
      }
      break;
  }
  
}
void joystickUsed(){
  joystickReady = true;
  displayUpdate = true;
  tone(8,2500,50);
  mlsOfJoystickUpdate = millis() + 200;
}