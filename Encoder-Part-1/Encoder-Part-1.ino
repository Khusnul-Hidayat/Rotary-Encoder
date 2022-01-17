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
  attachInterrupt(digitalPinToInterrupt(pEchA), ISR_Encoder_A, RISING); //Rising Edge --> low to high
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();
  float deltaTime = currentTime - lastTime;
  if(deltaTime>=TimeSampling){
    float freqSignal = (float)countPulses/(deltaTime/1.0e3); //(deltaTime/1.0e3) --> convert ms to s
    countPulses = 0;
    float rpm = freqSignal * 60.0 / 224.4; //224.4 = p*N; p=step-up gear ratio; N=pulses per revolution
//    Serial.print(0);
//    Serial.print(" ");
//    Serial.print(600);
//    Serial.print(" ");
    Serial.println(rpm);
    lastTime = currentTime;
  }
}

void ISR_Encoder_A(){
  if(digitalRead(pEchB)){
    //clockwise
    countPulses++;
  }else{
    //counter clockwise
    countPulses--;
  }
}
