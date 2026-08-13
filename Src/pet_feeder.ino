/*
 * Automatic Pet Feeding System
 * University of Khartoum - Faculty of Engineering
 * Department of Electrical and Electronic Engineering
 * Microprocessor System Design Course
 *
 * Group 34:
 *   Alshaima Abdullahi Mohmed Elbashir - 194029
 *   Mohamed Abubaker Elsir Gafar       - 204097
 * Supervised by: Dr. Magdi B. M. Amien
 *
 * Live simulation: https://wokwi.com/projects/471244750730611713
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <Servo.h>
#include <Keypad.h>

#define TRIG_PIN 6
#define ECHO_PIN 5
#define SERVO_PIN 9
#define BUZZER_PIN A0
#define RED_LED_PIN A3

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 rtc;
Servo feederServo;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {4, 7, 8, 10};
byte colPins[COLS] = {11, 12, A1, A2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const byte feedHour1 = 8;
const byte feedMinute1 = 0;
const byte feedHour2 = 18;
const byte feedMinute2 = 0;
const float emptyDistance = 20.0;

long duration;
float distance;
bool fedThisMinute = false;

void measureFoodLevel();
void updateDisplay(DateTime now);
void checkFoodLevel();
void checkAutomaticFeeding(DateTime now);
void checkManualFeeding();
void dispenseFood();

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Wire.begin();
  rtc.begin();

  if (!rtc.isrunning())
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  digitalWrite(RED_LED_PIN, LOW);

  feederServo.attach(SERVO_PIN);
  feederServo.write(0);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Automatic Pet");
  lcd.setCursor(0, 1);
  lcd.print("Feeder System");
  delay(2000);
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();
  measureFoodLevel();
  updateDisplay(now);
  checkFoodLevel();
  checkAutomaticFeeding(now);
  checkManualFeeding();
  delay(200);
}

void measureFoodLevel() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.0343 / 2.0;
}

void updateDisplay(DateTime now) {
  lcd.setCursor(0, 0);
  char timeBuffer[17];
  sprintf(timeBuffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  lcd.print("Time:");
  lcd.print(timeBuffer);
  lcd.print(" ");

  lcd.setCursor(0, 1);
  if (distance > emptyDistance) {
    lcd.print("Food: LOW ");
  } else {
    lcd.print("Food: OK  ");
  }
}

void checkFoodLevel() {
  if (distance > emptyDistance) {
    digitalWrite(RED_LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
  } else {
    digitalWrite(RED_LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }
}

void checkAutomaticFeeding(DateTime now) {
  bool feedingTime =
    (now.hour() == feedHour1 && now.minute() == feedMinute1) ||
    (now.hour() == feedHour2 && now.minute() == feedMinute2);

  if (feedingTime) {
    if (!fedThisMinute) {
      dispenseFood();
      fedThisMinute = true;
    }
  } else {
    fedThisMinute = false;
  }
}

void checkManualFeeding() {
  char key = keypad.getKey();
  if (key == 'A') {
    dispenseFood();
  }
}

void dispenseFood() {
  noTone(BUZZER_PIN);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Feeding Pet...");
  lcd.setCursor(0, 1);
  lcd.print("Please Wait");

  tone(BUZZER_PIN, 2000, 300);
  feederServo.write(90);
  delay(2000);
  feederServo.write(0);
  delay(500);

  lcd.clear();
}
