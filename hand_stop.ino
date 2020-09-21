#include <GyverFilters.h>
GFilterRA analog0;    // фильтр назовём analog0
GFilterRA analog1;

//#include <GyverButton.h>
#include <Bounce2.h>

int currentSensorPin = A0;
int motor_Reverse_Pin = 9;  //in1
int motor_Direct_Pin = 8;   //in2

int dirInPin = 11;

int buttonPin = 10;
int currentResistorPin = A1;

bool motorState = LOW;
bool lastState = LOW;

int previousPrint;
//GButton butt1(buttonPin);
Bounce debouncer = Bounce(); //инициализация библиотеки антидребезга


void setup() {
  debouncer.attach(buttonPin);
  debouncer.interval(10); // interval in ms
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(currentSensorPin, INPUT);
  pinMode(motor_Direct_Pin, OUTPUT);
  pinMode(motor_Reverse_Pin, OUTPUT);
  pinMode(dirInPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(buttonPin, INPUT);
}

void loop() {
  debouncer.update();
  int current = 550 - analogRead(currentSensorPin);
  int resistor = analogRead(currentResistorPin) / 2;
  int printt = resistor - current;
  runMotor(debouncer.read());
  //Serial.println(resistor);
  if (current > resistor ) {
    Serial.print("overload: ");
    Serial.println(current - resistor);
    stopMotor();
  }
}

void runMotor(bool direct) {
  if (motorState == direct) return;
  stopMotor();
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println(direct);
  digitalWrite(motor_Direct_Pin, direct);
  delay(50);
  digitalWrite(motor_Reverse_Pin, 0);
  delay(50);
  motorState = direct;
  digitalWrite(dirInPin, direct);
}

void stopMotor() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(motor_Reverse_Pin, HIGH);
  digitalWrite(motor_Direct_Pin, LOW);
  delay(1);
}
