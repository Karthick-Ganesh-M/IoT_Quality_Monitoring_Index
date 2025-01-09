#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 25          
#define DHTTYPE DHT11       
#define MQ135_PIN 35       
#define MQ7_PIN 34   


LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE); 
float R0_MQ135 = 8.50;  
float R0_MQ7 = 0.39;  
unsigned long sendDataPrevMillis = 0;


void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  dht.begin(); 
  Serial.println("Starting Air Quality Monitoring...");
  lcd.setCursor(0, 0);
  lcd.print("Air Quality Init");
  delay(2000);
  lcd.clear();
}

float getNH3PPM(float Rs_Ratio) {
  float ppm = 1.5 * pow((Rs_Ratio / R0_MQ135), 3.8);
  return ppm;
}
float getCO2PPM(float Rs_Ratio) {
  float ppm = 116.6020682 * pow((Rs_Ratio / R0_MQ135), 2.3);
  return ppm;
}
float calculateRs_MQ7(int mq7_raw) {
  return ((1023.0 / mq7_raw) - 1) * R0_MQ7;
}

float getCO(float Rs) {
  float ratio = Rs / R0_MQ7;
  return pow(ratio, -2.2) * 1000; 
}


void loop() {
  
  if (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0) {
    sendDataPrevMillis = millis();

    
    int mq135_raw = analogRead(MQ135_PIN);
    float Rs_MQ135 = ((1023.0 / mq135_raw) - 1) * R0_MQ135;

    // Calculate PPM values
    float nh3_ppm = getNH3PPM(Rs_MQ135);
    float co2_ppm = getCO2PPM(Rs_MQ135);

    
    int mq7_raw = analogRead(MQ7_PIN);
    float Rs_MQ7 = calculateRs_MQ7(mq7_raw);
    float co_ppm = getCO(Rs_MQ7);

    
    float temperature = dht.readTemperature();

    
    Serial.printf("CO2: %.2f ppm\n", co2_ppm);
    Serial.printf("NH3: %.2f ppm\n", nh3_ppm);
    Serial.printf("CO: %.2f ppm\n", co_ppm);
    Serial.printf("Temperature: %.2f C\n", temperature);
    Serial.println();

    
    lcd.setCursor(0, 1);
    lcd.print("Temp:");
    lcd.print(temperature);
    lcd.print("C   "); 

    // Display gas values on LCD
    for (int i = 0; i < 3; i++) {
      lcd.setCursor(0, 0); 
      lcd.clear();
      if (i == 0) {
        lcd.print("CO2:");
        lcd.print(co2_ppm);
      } else if (i == 1) {
        lcd.print("NH3:");
        lcd.print(nh3_ppm);
      } else if (i == 2) {
        lcd.print("CO:");
        lcd.print(co_ppm);
      }

     
      lcd.setCursor(0, 1);
      lcd.print("Temp:");
      lcd.print(dht.readTemperature());
      lcd.print("C   ");  
      
      delay(3000); 
    }
  }
}
