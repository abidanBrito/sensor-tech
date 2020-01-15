[![Codacy Badge](https://api.codacy.com/project/badge/Grade/4cbd2f2216e94ec8a36303c0920299aa)](https://www.codacy.com/manual/abidanBrito/CDIO_Agriculture_Sensors?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=abidanBrito/CDIO_Agriculture_Sensors&amp;utm_campaign=Badge_Grade)
![WIP_Badge](https://img.shields.io/badge/version-1.0-blue.svg)

![Project_Logo](/Sprint2/img/projectLogo_v2.png)

Electronic prototype to **monitor several environmental magnitudes** through the usage of self-implemented sensors.

## TABLE OF CONTENTS
1.  [Motivation](#motivation)
2.  [Technologies and Frameworks](#technologies-and-frameworks)
3.  [System Design](#system-design)
4.  [Features](#features)
5.  [Documentation](#documentation)
6.  [Credits](#credits)
7.  [Acknowledgements](#acknowledgements)

## MOTIVATION
This is a team effort for our first semester class **CDIO**. This project follows an **agile software development approach** (SCRUM).

## TECHNOLOGIES AND FRAMEWORKS
### Electronic Devices and Components
*   Sparkfun **ESP8266 Thing Dev** Board.
*   Adafruit **ADS1115** 16-bit ADC.
*   DFROBOT **SEN0193** Soil Moisture Sensor.
*   Lantronix **A2235-H** GPS Receiver.
*   InvenSense **MPU-9250** Accelerometer.
*   Adafruit **BMP280** Barometric Pressure & Altitude Sensor.
*   **HC-SR04** Ultrasonic Distance Sensor. 
*   Operational amplifier.
*   Photodiode.
*   AND logic gate.
*   NTC thermistor.
*   Resistors.

### REST Servers
*   ThingSpeak - IoT Analytics and integration with MATLAB.
*   Dweet - Simple messaging and alerts. 

### Software Development 
*   Arduino IDE. 
*   Third-party text editors.

## SYSTEM DESIGN
### Sofware Architecture
![Software Architecture Diagram](/Sprint2/img/softwareArchitecture.png)

### Hardware Architecture
![Hardware Architecture Diagram](Sprint2/img/hardwareArchitecture.png)

## IMPLEMENTED FEATURES
*   [x] Salinity sensor (electrical conductivity).
*   [x] Soil Moisture sensor.
*   [x] Temperature sensor.
*   [x] Luminosity sensor.
*   [x] Barometric pressure and altitute sensor.
*   [x] Anti-theft system (Wake on Motion).
*   [x] Hibernation mode (Deep Sleep).
*   [x] Rain Gauge (experimental).
*   [x] GPS receiver.
*   [x] REST server.
*   [x] PCB Design.

## DOCUMENTATION (under construction)
It can be found in the form of a PDF file for each and every Sprint, accordingly. Those of previous Sprints may and do, in fact, contain errors (schematics, pins, etc.). Please, refer to the latest Sprint directory for an [up-to-date documentation](Sprint3/Sprint3_Documentación.pdf). 

## CREDITS
| Author                    |
|---------------------------| 
| Abidán Brito Clavijo      |
| Pablo Enguix Llopis       |
| Luis Belloch Martínez     |
| Elvira Montagud Hernandis |

## ACKNOWLEDGEMENTS
I would like to express my sincere gratitude to my teacher **Mª Asunción Pérez Pascual** for her invaluable support, feedback and encouragement throughout the development of this project, and to **Universitat Politècnica de València** for providing us with both the knowledge and the tools needed to complete it.
