void master_joystick(){
  if( joystickUpdate == false && millis() > mlsOfJoystickUpdate ){
    joystickUpdate = true;
  }
  /*
  readX = Joystick.readX();
  readY = Joystick.readY();
  */
  if(joystickUpdate == true){
    joystickUpdate = navigasiJoystick(
      Joystick.Up(),
      Joystick.Down(),
      Joystick.Right(),
      Joystick.Left(),
      Joystick.readButton()
    );
    mlsOfJoystickUpdate = millis() + 200;
  }
}

bool navigasiJoystick(bool _U, bool _D, bool _R, bool _L, bool _B){
  if(_U == true){
    
  }
  if(_D == true){

  }
  if(_L == true){

  }
  if(_R == true){
    
  }
  return false;
}