#include <RTClib.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <DHT.h>

#define BLYNK_PRINT Serial
#define dht_data 3
#define fan D3
#define led D4
#define us_trigger D6
#define us_echo D7
#define buzz D8
#define DHTTYPE DHT11

Servo servo;
RTC_DS3231 rtc;
DHT dht(dht_data, DHTTYPE);

char auth[] = "zXpl-OYi6yBHrULY83m5PEmCzFbETOmT";
char ssid[] = "POLAR";
char pass[] = "PerfectParadox9";
float set_temp;
int dis, portion1, portion2;
long set_time1, set_time2;

BLYNK_WRITE(V1){set_time1 = param.asLong();}
BLYNK_WRITE(V2){set_time2 = param.asLong();}
BLYNK_WRITE(V3){portion1 = param.asInt();}
BLYNK_WRITE(V4){portion2 = param.asInt();}
BLYNK_WRITE(V5){set_temp = param.asFloat();}
WidgetLED status_fan (V7);
WidgetLED status_led (V8);

void setup() 
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  Wire.begin(D1, D2);     //(SDA, SCL)
  rtc.begin();
  dht.begin();
  
  pinMode(fan, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(us_echo, INPUT);
  pinMode(us_trigger, OUTPUT);
  pinMode(buzz, OUTPUT);

  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  
  servo.attach(D5);
  servo.write(0);
}


void loop()
{  
  Blynk.run();
  
  DateTime now = rtc.now();
  long rtc_in_sec = (3600 * now.hour() + 60 * now.minute());
  float temp = dht.readTemperature();
  
  if ((rtc_in_sec == set_time1) && (now.second() < portion1)) servo_mov(portion1);
  else if((rtc_in_sec == set_time2) && (now.second() < portion2)) servo_mov(portion2);
  else servo.write(0);

  if (temp > set_temp) temp_control(LOW, HIGH);
  else if (temp < set_temp) temp_control(HIGH, LOW);
  else temp_control(HIGH, HIGH);
 
  level();
 
  Blynk.virtualWrite(V6, temp);
  Blynk.virtualWrite(V0, dis);
}

void temp_control(char fan_val, char led_val)
{
  digitalWrite(fan, fan_val);
  digitalWrite(led, led_val);

  if(fan_val == LOW && led_val == HIGH)
  {
    status_fan.on();
    status_led.off();
  }
  else if(fan_val == HIGH && led_val == LOW)
  {
    status_fan.off();
    status_led.on();
  }
  else 
  {
    status_fan.off();
    status_led.off();
  }
}

void servo_mov(int portion)
{
  int portion_delay = portion * 1000;
  
  servo.write(45);
  delay(portion_delay);
  servo.write(0);
}

int level()
{
  digitalWrite(buzz, HIGH);
  
  digitalWrite(us_trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(us_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(us_trigger, LOW);

  dis = (pulseIn(us_echo, HIGH)/58.3);

  if(dis >= 9)
  {
    digitalWrite(buzz, LOW);
    delay(250);
    digitalWrite(buzz, HIGH);
  }
  
  return dis;
}
