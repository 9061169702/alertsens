#include<Wire.h>

int led_red = 2;    // Connected to  positive of digital  pin 2
int led_yellow = 3; // Connected to  positive of digital  pin 3
int led_orange = 4; // Connected to positive of digital   pin 4
int led_blue = 5;   // Connected to positive of  digital  pin 5
int led_green = 6;  // Connected to  positive of digital  pin 6
int ambience_maxvalue = 85; 
float flux; // To keep luminent value
bool measured_value_t_v; // to keep the measured humidity 

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Wire.begin();
Wire.beginTransmission(0x44); //slave address of opt3001 in I2C
Wire.write(0x01);
Wire.write(0xCE);
Wire.write(0x10);
Wire.endTransmission();

Wire.beginTransmission(0x43);  //Slave address of ENS210 in I2C 
Wire.write(0x21);
Wire.write(0x22);
Wire.endTransmission();

}

void loop() {
  // put your main code here, to run repeatedly:

  Wire.beginTransmission(0x44);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(100);

  Wire.requestFrom(0x44,2);
  uint16_t iData;
  uint8_t iBuff[2];

   while(Wire.available()){
    Wire.readBytes(iBuff, 2);
    iData = (iBuff[0]<< 8) | iBuff[1];
    Serial.print(iData,BIN);
    Serial.print("\t\t");
     flux = SensorOpt3001_dataconvert(iData);
    Serial.println(flux);
   }

   Wire.beginTransmission(0x43);
   Wire.write(0x21);
   Wire.endTransmission();
   delay(100);

  Wire.requestFrom(0x43,2);
  uint32_t t_val;
  uint32_t h_val;

if(isnan(flux) || isnan(measured_value_t_v)){

  digitalWrite(led_red,HIGH); // If the sensor is not returning any value or malfunction 
  
}else{
  
  if(flux = ambience_maxvalue){
    digitalWrite(led_yellow,HIGH);
   }
   
   delay(1000);

   
  }


     
}
   


float SensorOpt3001_dataconvert(uint16_t  iRawData)  // Formula to covert the sensor value to human readable value
{
  uint16_t iExponent, iMantisa;
  iMantisa = iRawData & 0x0FFF;
  iExponent = (iRawData & 0xF000)>> 12;
  return iMantisa*(0.01*pow(2, iExponent));
  
}






  
