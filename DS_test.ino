#include <OneWire.h>
#include <DallasTemperature.h>
OneWire oneWire(A5); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature. 

DeviceAddress tempDeviceAddress;

#define  T_RESOL 12
#define  delayInMillis 750 / (1 << (12 - T_RESOL))
//float temperature = 0.0;
unsigned long lastTempRequest = 0;

void setup(void)
{
  Serial.begin(115200);
  sensors.begin();
  
//  if (!getAddress(tempDeviceAddress, 0))
//  {
//    Serial.print("Disconnect");
//  }
  sensors.getAddress(tempDeviceAddress, 0);

  sensors.setResolution(tempDeviceAddress, T_RESOL);
  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();
  lastTempRequest = millis(); 
  
  pinMode(13, OUTPUT); 
}

void loop(void)
{ 
  
  if (millis() - lastTempRequest >= delayInMillis) // waited long enough??
  {
    digitalWrite(13, LOW);
    lastTempRequest = millis(); 
    int32_t temperature = sensors.getTemp(tempDeviceAddress);
//    temperature = sensors.getTempC(tempDeviceAddress);
  // immediately after fetching the temperature we request a new sample 
	// in the async modus
  // for the demo we let the resolution change to show differences
    sensors.requestTemperatures(); 
    Serial.println(millis() - lastTempRequest); 
    lastTempRequest = millis(); 
    Serial.print(" Temperature: ");
    Serial.println((temperature*1000)/12800); 
    digitalWrite(13, HIGH);
  }
  
  // we can do usefull things here 

}
