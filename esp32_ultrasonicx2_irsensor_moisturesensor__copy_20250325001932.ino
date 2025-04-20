#include <driver/adc.h>  // Required for ADC configuration

// Buzzer
#define BUZZER_1 27 // Main Buzzer
#define BUZZER_2 32  // Close-Range Buzzer

// Vibration Motors
#define VIBRATION_MOTOR_1 15  // Main motor
#define VIBRATION_MOTOR_2 26  // Close-range motor

// Front Ultrasonic Sensor
#define FRONT_TRIG_PIN 4
#define FRONT_ECHO_PIN 5

// Back Ultrasonic Sensor
#define BACK_TRIG_PIN 18
#define BACK_ECHO_PIN 19

// Soil Moisture Sensor
#define MOISTURE_SENSOR 34  // GPIO 34 (Analog Input)

// IR Sensor
#define IR_SENSOR 14  // Digital Output

// Threshold Values
const int FRONT_OBSTACLE_THRESHOLD = 150;  // cm
const int BACK_OBSTACLE_THRESHOLD = 150;   // cm
const int CLOSE_ULTRASONIC_THRESHOLD = 20; // cm
const int DRY_THRESHOLD = 3000;           // Dry Surface
const int SLIGHTLY_WET_THRESHOLD = 2500;  // Slightly Wet Surface
const int WET_THRESHOLD = 1800;           // Wet Surface

void setup() {
  Serial.begin(115200);

  // Setup Buzzers
  pinMode(BUZZER_1, OUTPUT);
  pinMode(BUZZER_2, OUTPUT);
  digitalWrite(BUZZER_1, LOW);
  digitalWrite(BUZZER_2, LOW);

  // Setup Vibration Motors
  pinMode(VIBRATION_MOTOR_1, OUTPUT);
  pinMode(VIBRATION_MOTOR_2, OUTPUT);
  digitalWrite(VIBRATION_MOTOR_1, LOW);
  digitalWrite(VIBRATION_MOTOR_2, LOW);

  // Setup IR Sensor
  pinMode(IR_SENSOR, INPUT);

  // Setup Ultrasonic Sensors
  pinMode(FRONT_TRIG_PIN, OUTPUT);
  pinMode(FRONT_ECHO_PIN, INPUT);
  pinMode(BACK_TRIG_PIN, OUTPUT);
  pinMode(BACK_ECHO_PIN, INPUT);

  // Configure ADC for Soil Moisture Sensor
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
}

void loop() {
  int irValue = digitalRead(IR_SENSOR);
  int frontDistance = getUltrasonicDistance(FRONT_TRIG_PIN, FRONT_ECHO_PIN);
  int backDistance = getUltrasonicDistance(BACK_TRIG_PIN, BACK_ECHO_PIN);
  int moistureValue = adc1_get_raw(ADC1_CHANNEL_6);  // Read soil moisture

  Serial.print("IR Sensor: ");
  Serial.print(irValue == LOW ? "🚧 Close-Range Obstacle! " : "✅ No Close Obstacle. ");

  Serial.print("| Front Distance: ");
  Serial.print(frontDistance);
  Serial.print(" cm | Back Distance: ");
  Serial.print(backDistance);
  Serial.print(" cm | Moisture Level: ");
  Serial.println(moistureValue);

  bool alertMain = false;
  bool alertCloseRange = false;

  // Detect Front Obstacle
  if (frontDistance > 0 && frontDistance <= FRONT_OBSTACLE_THRESHOLD) {
    Serial.println("🚧 Front Obstacle Detected!");
    alertMain = true;
  }

  // Detect Back Obstacle
  if (backDistance > 0 && backDistance <= BACK_OBSTACLE_THRESHOLD) {
    Serial.println("🔙 Back Obstacle Detected!");
    alertMain = true;
  }

  // Detect Close-Range Obstacle (IR Sensor)
  if (irValue == LOW) {  
    Serial.println("⚠️ Close-Range Obstacle Detected!");
    alertCloseRange = true;
  }

  // Detect Wet or Slightly Wet Surface
  if (moistureValue < WET_THRESHOLD) {
    Serial.println("⚠️ Wet/Slippery Surface Detected!");
    alertMain = true;
    alertCloseRange = true;
  } else if (moistureValue >= WET_THRESHOLD && moistureValue < SLIGHTLY_WET_THRESHOLD) {
    Serial.println("☁️ Slightly Wet Surface Detected!");
    alertMain = true;
    alertCloseRange = true;
  } else {
    Serial.println("✅ Surface is Dry.");
  }

  // Detect Close Ultrasonic Obstacle (≤ 20 cm)
  if (frontDistance > 0 && frontDistance <= CLOSE_ULTRASONIC_THRESHOLD) {
    Serial.println("⚠️ Front Obstacle Very Close!");
    alertCloseRange = true;
  }
  if (backDistance > 0 && backDistance <= CLOSE_ULTRASONIC_THRESHOLD) {
    Serial.println("⚠️ Back Obstacle Very Close!");
    alertCloseRange = true;
  }

  // Activate Buzzer & Vibration Motors
  if (alertMain) {
    activateBuzzer1();
    activateVibration1();
  } else {
    digitalWrite(VIBRATION_MOTOR_1, LOW);
  }

  if (alertCloseRange) {
    activateBuzzer2();
    activateVibration2();
  } else {
    digitalWrite(VIBRATION_MOTOR_2, LOW);
  }

  delay(1000);
}

// Function to Measure Distance from Ultrasonic Sensors
int getUltrasonicDistance(int trigPin, int echoPin) {
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);  // Timeout at 30ms

  if (duration == 0) {
    return 999;  // No object detected (return high value)
  }

  distance = duration * 0.034 / 2;  // Convert time to cm
  return distance;
}

// Function to Activate Main Buzzer
void activateBuzzer1() {
  tone(BUZZER_1, 1000);  
  delay(500);
  noTone(BUZZER_1);
}

// Function to Activate Close-Range Buzzer
void activateBuzzer2() {
  tone(BUZZER_2, 1500);  
  delay(500);
  noTone(BUZZER_2);
}

// Function to Activate Main Vibration Motor
void activateVibration1() {
  digitalWrite(VIBRATION_MOTOR_1, HIGH);
  delay(500);
  digitalWrite(VIBRATION_MOTOR_1, LOW);
}

// Function to Activate Close-Range Vibration Motor
void activateVibration2() {
  digitalWrite(VIBRATION_MOTOR_2, HIGH);
  delay(500);
  digitalWrite(VIBRATION_MOTOR_2, LOW);
}
