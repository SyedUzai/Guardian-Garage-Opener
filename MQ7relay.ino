//Variable Declaration
int relayPin=8;
int aOut=0;//Analog out for MQ7
int dOut=7;
int limit;
int value;
int threshold;
int diagCounter=0;
int max=300;
int switch_pin = 4;
int led_pin = 2;


void setup() {
  Serial.begin(115200);
  pinMode(switch_pin, INPUT);
  digitalWrite(relayPin,1);
  pinMode(relayPin,OUTPUT);
  pinMode(led_pin, OUTPUT);

  for(diagCounter; diagCounter <= max; diagCounter++){
  threshold=digitalRead(dOut);  
  value=analogRead(aOut);  
  Serial.print("Diagnostic Digital: ");
  Serial.print(threshold);
  Serial.print(" CO: ");
  Serial.println(value);
  delay(100);
  }
}

void loop() {
  digitalWrite(led_pin, HIGH);
  digitalWrite(relayPin,1);
  threshold=digitalRead(dOut);
  value=analogRead(aOut);
  printFunction();

  if( value >= 100){
    digitalWrite(relayPin,0);
    delay(5000);
    digitalWrite(relayPin,1);
    delay(5000);
    coChecker();
    }
  if(digitalRead(switch_pin) == HIGH){
    Serial.println("Switch Activated Garage..");
    digitalWrite(relayPin,0);
    delay(5000);
    }  
  }

void coChecker(){
  delay(2.5 * 60 * 1000);
  threshold=digitalRead(dOut);
  value=analogRead(aOut);
  Serial.print("Function Digital: ");
  Serial.print(threshold);
  Serial.print(" Function CO: ");
  Serial.println(value);
  delay(100);
  if(value<=100){
    digitalWrite(relayPin,0);
    delay(5000);
    }
    else{
      coChecker();
    }
}

void printFunction(){
  Serial.print("Digital: ");
  Serial.print(threshold);
  Serial.print(" CO: ");
  Serial.println(value);
  delay(100);
}
