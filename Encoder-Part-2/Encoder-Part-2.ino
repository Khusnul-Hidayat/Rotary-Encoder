const int pEchA = PB7; //2 for Arduino Uno Board
const int pEchB = PB8; //3 for Arduino Uno Board

volatile long countPulses = 0;
const int TimeSampling = 10; //ms
unsigned long lastTime = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pEchA, INPUT);
  pinMode(pEchB, INPUT);
  attachInterrupt(digitalPinToInterrupt(pEchA), ISR_Encoder_A, CHANGE); //CHANGE --> low to high & high to low
  attachInterrupt(digitalPinToInterrupt(pEchB), ISR_Encoder_B, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();
  float deltaTime = currentTime - lastTime;
  if(deltaTime>=TimeSampling){
    float freqSignal = (float)countPulses/(deltaTime/1.0e3); //(deltaTime/1.0e3) --> convert ms to s
    countPulses = 0;
    float rpm = freqSignal * 60.0 / 897.6; //897.6 = p*4*N; p=step-up gear ratio (20.4) ratio; N=pulses per revolution (11)
    Serial.print(0);
    Serial.print(" ");
    Serial.print(600);
    Serial.print(" ");
    Serial.println(rpm);
    lastTime = currentTime;
  }
}

void ISR_Encoder_A(){
  bool chA = digitalRead(pEchA);
  bool chB = digitalRead(pEchB);
  
  if(chA){
    if(chB){
      countPulses++;
    }else{
      countPulses--;
    }
  }else{
    if(chB){
      countPulses--;
    }else{
      countPulses++;
    }
  }
}

void ISR_Encoder_B(){
  bool chA = digitalRead(pEchA);
  bool chB = digitalRead(pEchB);
  
  if(chB){
    if(chA){
      countPulses--;
    }else{
      countPulses++;
    }
  }else{
    if(chA){
      countPulses++;
    }else{
      countPulses--;
    }
  }
}
