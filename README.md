# IoT_Quality_Monitoring_Index

                                                   🌬️Air Quality Index Monitoring System
                                                     
  The  Air Quality Index Monitoring System is an IoT-based project designed to continuously monitor atmospheric parameters such as temperature, humidity, air quality, and carbon monoxide levels. The system is built using an ESP32 microcontroller and utilizes multiple sensors for accurate environmental data acquisition. A 16x2 LCD with I2C module displays real-time readings, making it suitable for use in homes, labs, factories, and smart cities for air quality awareness and health safety.
This project provides a foundation for real-time pollution detection and environmental condition tracking using low-cost, widely available components.

                                                   🔧 Components and Their Functions
                                                   
  Component	                                  Function
  
1) ESP32                       Microcontroller	Central controller that reads sensor data, processes it, and sends output to the LCD display.
2) DHT11 Sensor              	Measures temperature and humidity. Useful for detecting climate changes or indoor comfort levels.
3) MQ135 Gas Sensor	          Detects harmful gases like ammonia (NH3), carbon dioxide (CO2), alcohol, smoke, etc. Used for air quality monitoring.
4) MQ7 Gas Sensor	            Detects carbon monoxide (CO) levels in the air. Useful for early detection of CO leaks or pollution.
5) 16x2 LCD with I2C Module  	Displays real-time sensor values (temperature, humidity, gas levels) on a compact screen. I2C makes wiring simple and efficient.
