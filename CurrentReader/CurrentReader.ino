/* ACS712 Current Sensor Reader
   ACS712ELCTR-20A-T 100mV/A
   0~1023 => 0V~5V
   1 => 0.0049v = 4.9mV
   1A => 100mV
   A = (0.0049 * value - 2.5) / 0.1
*/
const int samplenum = 1000; //A => mA ，采样率 
float correct = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  Serial.begin(115200);
  for(int i=0;i<3000; i++){
    correct +=  (0.0049 * (float)analogRead(A0) - (float)2.5) / 0.1;
    delay(1);
  }
  correct /= 3;
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print(0.0049 * (float)analogRead(A0) - 2.5);
  //Serial.print(":");
  float average = 0;
  for (int i = 0; i < samplenum; i++) {
    average = average + (0.0049 * (float)analogRead(A0) - (float)2.5) / 0.1;
    delay(1);
  }
  Serial.print(average-correct);
  Serial.println("\t mA");
  delay(500);
}
