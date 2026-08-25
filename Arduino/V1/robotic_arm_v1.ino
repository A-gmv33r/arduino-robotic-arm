#include <Servo.h>

// =====================
// JOYSTICK PINS
// =====================

const int xPin1 = A0;
const int yPin1 = A1;

const int xPin2 = A2;
const int yPin2 = A3;

// =====================
// BUTTONS
// =====================

const int button1 = 2;
const int button2 = 3;

// =====================
// SERVOS
// =====================

Servo baseServo;
Servo elbowServo;
Servo wristServo;
Servo clawServo;

// =====================
// SERVO PINS
// =====================

const int basePin = 9;
const int elbowPin = 10;
const int wristPin = 5;
const int clawPin = 6;

// =====================
// SERVO ANGLES
// =====================

float baseAngle = 90;
float elbowAngle = 90;
float wristAngle = 90;
float clawAngle = 10;

// =====================
// SERVO SPEEDS
// =====================

float baseSpeed = 1.5;
float elbowSpeed = 1.5;
float wristSpeed = 1.5;

// =====================
// SERVO LIMITS
// =====================

// Base
int baseMin = 20;
int baseMax = 160;


// Elbow
int elbowMin = 20;
int elbowMax = 160;

// Wrist
int wristMin = 20;
int wristMax = 160;

// Claw
int clawMin = 10;
int clawMax = 80;

// =====================
// JOYSTICK DEADZONE
// =====================

const int upperDeadzone = 550;
const int lowerDeadzone = 470;

// =====================
// CLAW
// =====================

bool clawOpen = false;

// =====================
// MODE
// =====================

int mode = 1; //JoYSTICK CONTROL

// =====================
// RESET
// =====================

bool resetting = false;
int resetStep = 0;

unsigned long lastResetMove = 0;
const int resetDelay = 20;

// =====================
// BUTTON STATES
// =====================

bool lastButton1 = HIGH;
bool lastButton2 = HIGH;
bool lastBoth = false;

// =====================
// CONTROL SERVO
// =====================

void controlServo(
  Servo &servo,
  int joystickValue,
  float &angle,
  float speed,
  int minimum,
  int maximum
)
{
  if (joystickValue > upperDeadzone)
  {
    angle += speed;
  }

  else if (joystickValue < lowerDeadzone)
  {
    angle -= speed;
  }

  angle = constrain(angle, minimum, maximum);

  servo.write(angle);
}

// =====================
// CLAW BUTTON
// =====================

void controlClaw()
{
  bool currentButton2 = digitalRead(button2);

  // Only react when button is newly pressed
  if (lastButton2 == HIGH && currentButton2 == LOW)
  {
    clawOpen = !clawOpen;

    if (clawOpen)
    {
      clawAngle = clawMax;
      clawServo.write(clawAngle);

      Serial.println("Claw OPEN");
    }

    else
    {
      clawAngle = clawMin;
      clawServo.write(clawAngle);

      Serial.println("Claw CLOSED");
    }

    delay(200);
  }

  lastButton2 = currentButton2;
}

// =====================
// START RESET
// =====================

void startReset()
{
  resetting = true;
  resetStep = 1;

  Serial.println("Reset started");
}

// =====================
// RESET ARM
// =====================

void resetArm()
{
  if (!resetting)
    return;

  // Don't move too quickly
  if (millis() - lastResetMove < resetDelay)
    return;

  lastResetMove = millis();

  // =====================
  // RESET BASE
  // =====================

  if (resetStep == 1)
  {
    if (baseAngle > 90)
      baseAngle--;
    else if (baseAngle < 90)
      baseAngle++;

    baseServo.write(baseAngle);

    if (abs(baseAngle - 90) <= 0.5)
    {
      baseAngle = 90;
      resetStep = 2;
    }
  }

  // =====================
  // RESET ELBOW
  // =====================

  else if (resetStep == 3)
  {
    if (elbowAngle > 90)
      elbowAngle--;
    else if (elbowAngle < 90)
      elbowAngle++;

    elbowServo.write(elbowAngle);

    if (abs(elbowAngle - 90) <= 0.5)
    {
      elbowAngle = 90;
      resetStep = 4;
    }
  }

  // =====================
  // RESET WRIST
  // =====================

  else if (resetStep == 4)
  {
    if (wristAngle > 90)
      wristAngle--;
    else if (wristAngle < 90)
      wristAngle++;

    wristServo.write(wristAngle);

    if (abs(wristAngle - 90) <= 0.5)
    {
      wristAngle = 90;
      resetStep = 5;
    }
  }

  // =====================
  // RESET CLAW
  // =====================

  else if (resetStep == 5)
  {
    clawAngle = clawMin;
    clawServo.write(clawAngle);

    clawOpen = false;

    resetting = false;
    resetStep = 0;

    Serial.println("Reset complete");
  }
}

// =====================
// CHECK BUTTONS
// =====================

void checkButtons()
{
  bool currentButton1 = digitalRead(button1);
  bool currentButton2 = digitalRead(button2);

  bool bothPressed =
    currentButton1 == LOW &&
    currentButton2 == LOW;

  // =====================
  // BOTH BUTTONS
  // MODE CHANGE
  // =====================

  if (bothPressed && !lastBoth)
  {
    mode++;

    if (mode > 2)
      mode = 1;

    Serial.print("Mode changed to: ");
    Serial.println(mode);

    delay(300);
  }

  // =====================
  // BUTTON 1 ALONE
  // RESET
  // =====================

  else if (
    lastButton1 == HIGH &&
    currentButton1 == LOW &&
    currentButton2 == HIGH
  )
  {
    startReset();
  }

  // =====================
  // BUTTON 2 ALONE
  // CLAW
  // =====================

  else if (
    lastButton2 == HIGH &&
    currentButton2 == LOW &&
    currentButton1 == HIGH
  )
  {
    clawOpen = !clawOpen;

    if (clawOpen)
    {
      clawAngle = clawMax;
      clawServo.write(clawAngle);

      Serial.println("Claw OPEN");
    }
    else
    {
      clawAngle = clawMin;
      clawServo.write(clawAngle);

      Serial.println("Claw CLOSED");
    }
  }

  lastButton1 = currentButton1;
  lastButton2 = currentButton2;
  lastBoth = bothPressed;
}

// =====================
// SETUP
// =====================

void setup()
{
  // Attach servos

  baseServo.attach(basePin);
  elbowServo.attach(elbowPin);
  wristServo.attach(wristPin);
  clawServo.attach(clawPin);

  // Buttons

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  // Starting positions

  baseServo.write(baseAngle);
  elbowServo.write(elbowAngle);
  wristServo.write(wristAngle);
  clawServo.write(clawAngle);

  Serial.begin(9600);

  Serial.println("4 Servo Arm Ready!");
  Serial.println("Mode 1");
}

// =====================
// LOOP
// =====================

void loop()
{
  // =====================
  // CHECK BUTTONS
  // =====================

  checkButtons();

  // =====================
  // RESET
  // =====================

  if (resetting)
  {
    resetArm();

    // Don't control servos with joysticks during reset
    delay(5);
    return;
  }

  // =====================
  // READ JOYSTICKS
  // =====================

  int x1 = analogRead(xPin1);
  int y1 = analogRead(yPin1);

  int x2 = analogRead(xPin2);
  int y2 = analogRead(yPin2);

  // =====================
  // MODE 1
  // =====================

  if (mode == 1)
  {
    // Joystick 1 X → BASE

    controlServo(
      baseServo,
      x1,
      baseAngle,
      baseSpeed,
      baseMin,
      baseMax
    );


    // Joystick 2 X → ELBOW

    controlServo(
      elbowServo,
      x2,
      elbowAngle,
      elbowSpeed,
      elbowMin,
      elbowMax
    );

    // Joystick 2 Y → WRIST

    controlServo(
      wristServo,
      y2,
      wristAngle,
      wristSpeed,
      wristMin,
      wristMax
    );
  }

  delay(20);
}
