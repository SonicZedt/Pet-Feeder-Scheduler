# Pet-Feeder-Scheduler
Actually, this also comes with temperature control (fan and led/light bulb as output).

## Diagram Block
I guess, or whatever it called.

| Block        | Component |
| :--          | :--       |
|**Activator** | +6V adaptor                                |
|**Input**     | RTC DS3231, Ultrasonic, DHT11, and Blynk.  |
|**Process**   | Microcontroller                             |
|**Output**    | Servo, LED, Fan, Buzzer, Relay, and Blynk. |

* Microcontroller is any arduino-like such as NodeMCU ESP8266 (the one used on this project), Wemos, or anything that could use arduino IDE and ESP8266 as Wi-FI module.
* Relay is optional and needed if LED is replace with light bulb and bigger fan.
* Im using +6V adaptor in this project, + connected to Vin and - Connected to GND on microcontroller.

### Blynk:
Full Screenshot:
[See image](https://i.ibb.co/HHJPJCs/Data5-blynk.jpg)

Input widget configuration :
[See image](https://i.ibb.co/f2xD0nr/blynk-input.png)

Output widget configuration :
[See image](https://i.ibb.co/B6dy1qG/blynk-output.png)

### RTC Time Adjustment
To adjust RTC time according to your local (PC) time, uncomment this code: `rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));` and upload it to your microcontroller.
Since the code is in `setup()` function, **it will executed everytime the microcontroller switched on** and the time will be reset back to when it first adjusted.
To overcome this, you need to upload your code twice, first with `rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));`, and second without it. The time will not be adjusted nor stopped when you upload the second code as long the RTC has it's battery.

>PS: im not using PCB board, i use jumper cable. Please double check the line.
