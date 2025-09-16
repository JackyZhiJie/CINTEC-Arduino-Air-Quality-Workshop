int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 1000;//sampe 1s ;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;
int rLed = 13;

void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT);
  pinMode(rLed,OUTPUT);
  starttime = millis();//get the current time;
}

void loop() {
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  if ((millis()-starttime) > sampletime_ms)//if the sampel time == 30s
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    Serial.print("concentration = ");
    Serial.print(concentration);
    Serial.print(" pcs/0.01cf  -  ");
    if (concentration < 1.0) {
     Serial.println("It's a smokeless and dustless environment"); 
     digitalWrite(rLed, LOW);
     delay(1000);
  }
    if (concentration > 1.0 && concentration < 20000) {
     Serial.println("It's probably only you blowing air to the sensor :)"); 
     digitalWrite(rLed, LOW);
     delay(1000);
    }
    
    if (concentration > 20000 && concentration < 315000) {
     Serial.println("Smokes from matches detected!"); 
     digitalWrite(rLed, HIGH);
     delay(1000);
    }
      if (concentration > 315000) {
     Serial.println("Smokes from cigarettes detected! Or It might be a huge fire! Beware!"); 
     digitalWrite(rLed, HIGH);
     delay(1000);
  }
    lowpulseoccupancy = 0;
    starttime = millis();
  }
}
