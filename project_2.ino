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
  int motor2ccw = Firebase.getBool("motor2ccw");
  int motor2cw = Firebase.getBool("motor2cw");
  if (motor2ccw == true) {
    Serial.println("RUN MOTOR2 FROM FIREBASE");
    Serial.println("CCW");
    counterclockwise();
  }
  if (motor2cw == true) {
    Serial.println("CW");
    clockwise();
  }
}


void counterclockwise () {
  while (true) {
    if (Firebase.getBool("motor2ccw") == false) {
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
void clockwise () {
  while (true) {
    if (Firebase.getBool("motor2cw") == false) {
      break;
    }
    int motorSpeed = 3;
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
