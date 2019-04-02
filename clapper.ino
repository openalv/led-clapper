//RGB Led Clapper Project
//o.penalver
//01.02.2019

//...Pin IN/OUT
int redPin = 9;
int bluePin = 10;
int greenPin = 11;
int micPin = A2;    
int pot0Pin= A0;
int pot1Pin = A1;

//...Variables
int redVal = 0;
int greenVal = 0;
int blueVal = 0;
int micVal = 0;
int pot0Val = 0;
int newPot0Val = 0;
int pot1Val = 0;

int maxVal = 100;
int micFiltered = 0;

int lvl1 = 0;
int lvl2 = 0;
int lvl3 = 0;
int lvl4 = 0;

void setup() {
  pinMode(redPin, OUTPUT);  
  pinMode(bluePin, OUTPUT); 
  pinMode(greenPin, OUTPUT); 
}

void loop() {

  //analog readings of potentiometers and microphone
  micVal = analogRead(micPin);
  pot0Val = analogRead(pot0Pin);
  pot1Val = analogRead(pot1Pin);

  //amplification of microphone value
  if (micVal > maxVal) maxVal = micVal;
  micFiltered = (int)((micVal*1./maxVal)*1023);
   
  //definition of different lightening modes levels in respect with the values of potentiometers
  lvl1 = pot0Val;
  lvl2 = (int)(((pot1Val-pot0Val)*1./3)+ pot0Val);
  lvl3 = (int)(((pot1Val-pot0Val)*2*1./3)+ pot0Val);
  lvl4 = pot1Val;
  
  //computation of inputs for RGB leds
  if(micFiltered <= lvl1){
    redVal = 0;
    greenVal = 0;
    blueVal = 0;
  }
  else if((micFiltered>lvl1) && (micFiltered<=lvl2)){
    redVal = 0;
    greenVal = 0;
    blueVal = (int)(((micFiltered-lvl1)*1./(lvl2-lvl1))*255); 
  }
  else if ((micFiltered>lvl2) && (micFiltered<=lvl3)){
    redVal = 0;
    greenVal = (int)(((micFiltered-lvl2)*1./(lvl3-lvl2))*255);
    blueVal = 0;
  }  
  else if ((micFiltered>lvl3) && (micFiltered<=lvl4)){
    redVal = (int)(((micFiltered-lvl3)*1./(lvl4-lvl3))*255);
    greenVal = 0;
    blueVal = 0;
  }
  else if (micFiltered > lvl4){
    redVal = (int)(((micFiltered-lvl4)*1./1023-lvl4)*255);
    greenVal = redVal;
    blueVal = redVal;
  } 
   
  //analog write
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);                 
}
