#include <Time.h>
#include <TimeLib.h>

#include <Wire.h>
#include <RtcDS3231.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Config Firebase
#define FIREBASE_HOST "autofeed-dc380.firebaseio.com"
#define FIREBASE_AUTH "WHVpaKSF6JsAQJtb0fF38vCvHGx1zSDydSqag3lR"

// Config connect WiFi
#define WIFI_SSID "Mi"
#define WIFI_PASSWORD "bbbbbbbb"

RtcDS3231<TwoWire> Rtc(Wire);

int motorPin1 = D0;// Blue   - 28BYJ48 pin 1

int motorPin2 = D3;// Pink   - 28BYJ48 pin 2

int motorPin3 = D4;// Yellow - 28BYJ48 pin 3

int motorPin4 = D5;// Orange - 28BYJ48 pin 4

// Red    - 28BYJ48 pin 5 (VCC)

int motoropen1 = 0;

void setup ()
{
  Serial.begin(9600);
  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  if (!Rtc.IsDateTimeValid())
  {
    Serial.println("RTC lost confidence in the DateTime!");
    Rtc.SetDateTime(compiled);
  }
  Rtc.SetDateTime(compiled);
  RtcDateTime now = Rtc.GetDateTime();

  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
  pinMode(motorPin1, OUTPUT);

  pinMode(motorPin2, OUTPUT);

  pinMode(motorPin3, OUTPUT);

  pinMode(motorPin4, OUTPUT);
  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop ()
{
  int motor1 = Firebase.getBool("motor1");
  if (motor1 == true) {
    Serial.println("RUN MOTOR FROM FIREBASE");
    Serial.println("CCW");
    counterclockwise();
    Serial.println("CW");
    delay(500);
    clockwise();
    Firebase.setBool("motor1", false);
  }
  if ( motoropen1 == 1) {
    Firebase.setBool("motor2", true);
    motoropen1 = 0;
  }
  RtcDateTime now = Rtc.GetDateTime();
  //Print RTC time to Serial Monitor
  char nowTime[] = "00:00";
  nowTime[0] = now.Hour()/10 + '0';
  nowTime[1] = now.Hour()%10 + '0'; 
  nowTime[3] = now.Minute()/10 + '0'; 
  nowTime[4] = now.Minute()%10 + '0';
  Firebase.setString("time", nowTime);
  Serial.print("Date:");
  Serial.print(now.Year(), DEC);
  Serial.print('/');
  Serial.print(now.Month(), DEC);
  Serial.print('/');
  Serial.print(now.Day(), DEC);
  Serial.print(" Time:");
  Serial.print(now.Hour(), DEC);
  Serial.print(':');
  Serial.print(now.Minute(), DEC);
  Serial.print(':');
  Serial.print(now.Second(), DEC);
  Serial.println("");
  if (now.Second() == 30) {
    Firebase.setBool("motor1", true);
    Serial.println("RUN MOTOR FROM TIME");
    Serial.println("CCW");
    counterclockwise();
    Serial.println("CW");
    delay(500);
    clockwise();
    motoropen1 = 1;
    Firebase.setBool("motor1", false);
    Firebase.setBool("motor2", true);
    delay(500);
  }
  delay(500);
}


void counterclockwise () {
  RtcDateTime t = Rtc.GetDateTime();
  int  t_2 = t.Second() + 10;
  if (t_2 >= 60) {
    t_2 -= 60;
  }
  while (true) {
    RtcDateTime t = Rtc.GetDateTime();
    if (t.Second() >= 40 or t.Second() >= t_2) {
      break;
    }
    int motorSpeed = 10;
    // 1

    digitalWrite(motorPin4, HIGH);

    digitalWrite(motorPin3, LOW);

    digitalWrite(motorPin2, LOW);

    digitalWrite(motorPin1, LOW);

    delay(motorSpeed);

    // 2

    digitalWrite(motorPin4, HIGH);

    digitalWrite(motorPin3, HIGH);

    digitalWrite(motorPin2, LOW);

    digitalWrite(motorPin1, LOW);

    delay (motorSpeed);

    // 3

    digitalWrite(motorPin4, LOW);

    digitalWrite(motorPin3, HIGH);

    digitalWrite(motorPin2, LOW);

    digitalWrite(motorPin1, LOW);

    delay(motorSpeed);

    // 4

    digitalWrite(motorPin4, LOW);

    digitalWrite(motorPin3, HIGH);

    digitalWrite(motorPin2, HIGH);

    digitalWrite(motorPin1, LOW);

    delay(motorSpeed);

    // 5

    digitalWrite(motorPin4, LOW);

    digitalWrite(motorPin3, LOW);

    digitalWrite(motorPin2, HIGH);

    digitalWrite(motorPin1, LOW);

    delay(motorSpeed);

    // 6

    digitalWrite(motorPin4, LOW);

    digitalWrite(motorPin3, LOW);

    digitalWrite(motorPin2, HIGH);

    digitalWrite(motorPin1, HIGH);

    delay (motorSpeed);

    // 7

    digitalWrite(motorPin4, LOW);

    digitalWrite(motorPin3, LOW);

    digitalWrite(motorPin2, LOW);

    digitalWrite(motorPin1, HIGH);

    delay(motorSpeed);

    // 8

    digitalWrite(motorPin4, HIGH);

    digitalWrite(motorPin3, LOW);

    digitalWrite(motorPin2, LOW);

    digitalWrite(motorPin1, HIGH);

    delay(motorSpeed);

  }

}
void clockwise () {
  RtcDateTime t = Rtc.GetDateTime();
  int  t_2 = t.Second() + 10;
  if (t_2 >= 60) {
    t_2 -= 60;
  }
  while (true) {
    RtcDateTime t = Rtc.GetDateTime();
    if (t.Second() >= t_2) {
      break;
    }
    int motorSpeed = 10;
    // 1

    digitalWrite(motorPin1, HIGH);

    digitalWrite(motorPin2, LOW);

    digitalWrite(motorPin3, LOW);

    digitalWrite(motorPin4, LOW);

    delay(motorSpeed);

    // 2

    digitalWrite(motorPin1, HIGH);

    digitalWrite(motorPin2, HIGH);

    digitalWrite(motorPin3, LOW);

    digitalWrite(motorPin4, LOW);

    delay (motorSpeed);

    // 3

    digitalWrite(motorPin1, LOW);

    digitalWrite(motorPin2, HIGH);

    digitalWrite(motorPin3, LOW);

    digitalWrite(motorPin4, LOW);

    delay(motorSpeed);

    // 4

    digitalWrite(motorPin1, LOW);

    digitalWrite(motorPin2, HIGH);

    digitalWrite(motorPin3, HIGH);

    digitalWrite(motorPin4, LOW);

    delay(motorSpeed);

    // 5

    digitalWrite(motorPin1, LOW);

    digitalWrite(motorPin2, LOW);

    digitalWrite(motorPin3, HIGH);

    digitalWrite(motorPin4, LOW);

    delay(motorSpeed);

    // 6

    digitalWrite(motorPin1, LOW);

    digitalWrite(motorPin2, LOW);

    digitalWrite(motorPin3, HIGH);

    digitalWrite(motorPin4, HIGH);

    delay (motorSpeed);

    // 7

    digitalWrite(motorPin1, LOW);

    digitalWrite(motorPin2, LOW);

    digitalWrite(motorPin3, LOW);

    digitalWrite(motorPin4, HIGH);

    delay(motorSpeed);

    // 8

    digitalWrite(motorPin1, HIGH);

    digitalWrite(motorPin2, LOW);

    digitalWrite(motorPin3, LOW);

    digitalWrite(motorPin4, HIGH);

    delay(motorSpeed);

  }
}
