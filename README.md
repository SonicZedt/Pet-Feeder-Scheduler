# Pet-Feeder-Scheduler

## Diagram Block
I guess, or whatever it called.

### Microcontroller:
Arduino-like such as NodeMCU ESP8266 (the one used on this project), Wemos, or anything that could use arduino IDE and ESP8266 as Wi-FI module.

### Input:
RTC DS3231, Ultrasonic, DHT11, and Blynk.

### Output:
Servo, LED, Fan, Buzzer, and Blynk. Relay is optional and needed if LED is replace with light bulb and bigger fan.

### Activator:
im using +6V adaptor, + connected to Vin and - Connected to GND on microcontroller. If you're using relay, you need a microcontroler with atleast +5V output on it's pin.

### Blynk:
Full Screenshot:
![Full Screenshot](https://i.ibb.co/HHJPJCs/Data5-blynk.jpg)

Input widget configuration :

![Input widget](https://i.ibb.co/f2xD0nr/blynk-input.png)

Output widget configuration :

![Output widget](https://i.ibb.co/B6dy1qG/blynk-output.png)

## ---------------------------------------------------------------------------------------

### RTC Time Adjustment
To adjust RTC time according to your local (PC) time, uncomment this code: `rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));` and upload it to your microcontroller.
Since the code is in `setup()` function, **it will executed everytime the microcontroller turned on** and the time will be reset back to when it first adjusted.
To overcome this, you need to upload your code twice, first with `rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));`, and second without it.
The time will only adjusted if there is `rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));` code, so the time will not be adjusted or stopped as you upload the second code and as long as the RTC has it's battery.

>PS: im not using PCB board, i use jumper cable. Please double check the line.
