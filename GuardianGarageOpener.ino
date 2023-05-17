//Variable Declaration
int relayPin=8;
int aOut=0;//Analog out for MQ7 sensor
int dOut=7;//Digital out for MQ7 sensor
int value;// Analog Reading Value of sensor
int threshold;//Digital Reading Value of sensor
int BootUpCounter=0;//Counter for Bootup Process
int max=300;//Maxinum number of iterations of Bootup Process
int switch_pin = 4;//Pin for Manual Switch
int led_pin = 2;// Pin for Led 

void setup() {
  Serial.begin(115200);//Serial Port set to 115200 Baud
  pinMode(switch_pin, INPUT);//Switch pin behaves as Input value
  digitalWrite(relayPin,1);// Initial value of relay is 1 since relay is set to NO (Normally Open)
  pinMode(relayPin,OUTPUT);//Relay pin behaves as Output Value
  pinMode(led_pin, OUTPUT);// Led pin behaves as Output Value

  //For Loop for boot up procees
  for(BootUpCounter; BootUpCounter <= max; BootUpCounter++){
  threshold=digitalRead(dOut);//Threshold variable is set to digitalread of MQ7  
  value=analogRead(aOut);//Value variable is set to analogread of MQ7
  Serial.print("Diagnostic Digital: ");
  Serial.print(threshold);
  Serial.print(" CO: ");
  Serial.println(value);
  delay(100);//Small 100ms Delay until next iteration
  }
}

void loop() {
  digitalWrite(led_pin, HIGH);//Once Boot-up process is completed, led lights up
  digitalWrite(relayPin,1);//Initial value of relay is 1 since relay is set to NO (Normally Open)
  threshold=digitalRead(dOut);//Threshold variable is set to digitalread of MQ7  
  value=analogRead(aOut);//Value variable is set to analogread of MQ7
  printFunction();//Print function prints the values on the serial monitor

  //If CO value is greater than 0, relay activates which opens the Garage Door
  if( value >= 100){
    digitalWrite(relayPin,0);
    delay(5000);
    digitalWrite(relayPin,1);
    delay(5000);
    coChecker();//Once Garage is opened, coChecker checks if co value is still high
    }
  //If switch is used to manually open garage, relau activates which opens or closes garage  
  if(digitalRead(switch_pin) == HIGH){
    Serial.println("Switch Activated Garage..");
    digitalWrite(relayPin,0);
    delay(5000);
    }  
  }

//coChecker function uses Recursion to continiously check Carbon monoxide value
void coChecker(){
  delay(2.5 * 60 * 1000);//The function waits for minimum 2 and half minutes
  threshold=digitalRead(dOut);
  value=analogRead(aOut);
  Serial.print("Function Digital: ");
  Serial.print(threshold);
  Serial.print(" Function CO: ");
  Serial.println(value);
  delay(100);
  //If the carbon monoxide value is less than 100 (Safe), then relay will close garage once again and repeat whole program
  if(value<=100){
    digitalWrite(relayPin,0);
    delay(5000);
    }
    //Else, the function coChecker runs again
    else{
      coChecker();
    }
}

//Print function prints the value of the Carbon monoxide
void printFunction(){
  Serial.print("Digital: ");
  Serial.print(threshold);
  Serial.print(" CO: ");
  Serial.println(value);
  delay(100);
}
