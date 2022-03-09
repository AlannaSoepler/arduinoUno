const int sensorPin = A0;
// room temperature in Celsius
const float baselineTemp = 20.0;

void setup(){
  // open a serial connection to display values
  Serial.begin(9600);
  // set the LED pins as outputs
  // the for() loop saves some extra coding
  for(int pinNumber = 2; pinNumber<5; pinNumber++){
    pinMode(pinNumber,OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop(){
  // read the value on AnalogIn pin 0 
  // stores data from A0 and store it in a variable
  int sensorVal = analogRead(sensorPin);

  // send the 10-bit sensor value out the serial port
  delay(2000);
  Serial.println("sensor Value: ");
  Serial.println(sensorVal); 

  // convert the ADC reading to voltage
  float voltage = (sensorVal/1024.0) * 5.0;

  // Send the voltage level out the Serial port
  Serial.println(", Volts: ");
  Serial.println(voltage);

  // convert the voltage to temperature in degrees C
  // the sensor changes 10 mV per degree
  // the datasheet says there's a 500 mV offset
  // ((volatge - 500mV) times 100)
  Serial.println(", degrees C: "); 
  // turnes the voltage to temperature in degrees C
  float temperature = (voltage - .5) * 100;
  Serial.println(temperature);
  delay(2000);

  // if the current temperature is lower than the baseline
  // turn off all LEDs
  if(temperature < baselineTemp){
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } // if the temperature rises 2-4 degrees, turn an LED on 
  else if(temperature >= baselineTemp+1 && temperature < baselineTemp+2){
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } // if the temperature rises 4-6 degrees, turn a second LED on  
  else if(temperature >= baselineTemp+3 && temperature < baselineTemp+4){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } // if the temperature rises more than 6 degrees, turn all LEDs on
  else if(temperature >= baselineTemp+5){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  delay(100);
}