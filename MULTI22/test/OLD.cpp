// Juan Diego Marin Version

#include <Arduino.h>



void Automation();
void Control(float ref);
void AutomationOFF();

struct GPIO_d {
  uint8_t pin;
  bool state;
};


/***
 * Entradas y salidas del sistema
 * 
***/

GPIO_d ON = {34, false};
GPIO_d S = {12, false};
GPIO_d m = {14, false};
GPIO_d M = {27, false};

GPIO_d S1 = {18, false};
GPIO_d REVS = {4,true};

void ON_I() {
  if(digitalRead(ON.pin))
  {
    ON.state = true;
    S1.state = true;
  } 
  else {
    ON.state = false;
    S1.state = false;
  } 
}

void S_I() {
  if(digitalRead(S.pin)) 
  {
    S.state = true;
    REVS.state = false;
  }
  else{
    S.state = false;
    REVS.state = true;
  }  
}

void m_I() {
  if(digitalRead(m.pin)) m.state = true;
  else m.state = false; 
}

void M_I() {
  if(digitalRead(M.pin)) M.state = true;
  else M.state = false; 
}




/***
 * Control de la banda
 * 
***/

float ts = 5;
float VelMin = 75;
float VelMax = 160;
float u_apri = VelMin;
float u_apos = VelMin;
#define VelPWM 25



void setup() {
  
  Serial.begin(115200);

  pinMode(ON.pin,INPUT_PULLDOWN);
  pinMode(S.pin,INPUT_PULLDOWN);
  pinMode(m.pin,INPUT_PULLDOWN);
  pinMode(M.pin,INPUT_PULLDOWN);
  
  attachInterrupt(ON.pin,ON_I,CHANGE);
  attachInterrupt(S.pin,S_I,CHANGE);
  attachInterrupt(m.pin,m_I,CHANGE);
  attachInterrupt(M.pin,M_I,CHANGE);
  
  pinMode(S1.pin,OUTPUT);
  digitalWrite(S1.pin,S1.state);
  pinMode(REVS.pin,OUTPUT);
  digitalWrite(REVS.pin,REVS.state);
  
  
}

void loop() {
  if(ON.state) Automation();
  else AutomationOFF();
}

void Automation() {
  digitalWrite(S1.pin,S1.state);
  if(S.state)
  {
    digitalWrite(REVS.pin, REVS.state);
    dacWrite(VelPWM,ceil(VelMin));
  }
  else if(m.state) Control(-VelMax);
  else if(M.state) Control(VelMax);

}

void Control(float ref) {
  float Tau = ts / 5;
  float delta = 0.01;
  u_apri = u_apos;
  u_apos = (ref - u_apri) * delta / Tau + u_apri;
  u_apri = u_apos;
  if(u_apos<0) 
  {
    REVS.state = true;
    dacWrite(VelPWM, abs(ceil(-u_apos)));
  }
  else{
    dacWrite(VelPWM, abs(ceil(u_apos)));
    REVS.state = false;
  } 
  digitalWrite(REVS.pin,REVS.state);
  delay(delta * 1000);
}

void AutomationOFF()
{
  digitalWrite(S1.pin,S1.state);
  u_apri = VelMin;
  dacWrite(VelPWM, u_apri);
}
