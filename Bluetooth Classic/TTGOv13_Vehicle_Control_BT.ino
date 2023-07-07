#include "BluetoothSerial.h"

//#define USE_PIN // Uncomment this to use PIN during pairing. The pin is specified on the line below
const char *pin = "1234";  // Change this to more secure PIN.

String device_name = "ESP32-BT";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

int LMP = 18;  //Left Motor Positive pole
int LMN = 19;  //Left Motor Negative pole
int RMP = 16;  //Right Motor Positive pole
int RMN = 17;  //Right Motor Negative pole

unsigned int interval = 3000;
unsigned int elapsedMillis;

void setup() {
  pinMode(LMP, OUTPUT);
  pinMode(LMN, OUTPUT);
  pinMode(RMP, OUTPUT);
  pinMode(RMN, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin(device_name);  //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
//Serial.printf("The device with name \"%s\" and MAC address %s is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str(), SerialBT.getMacString()); // Use this after the MAC method is implemented
#ifdef USE_PIN
  SerialBT.setPin(pin);
  Serial.println("Using PIN");
#endif

  elapsedMillis = millis();
}  //end setup()

void loop() {
  if (SerialBT.available()) {
    String Direction = SerialBT.readString();
    // Serial.println(Direction);

    if (Direction == "F") {
      digitalWrite(LMP, HIGH);
      digitalWrite(LMN, LOW);
      digitalWrite(RMP, HIGH);
      digitalWrite(RMN, LOW);
      Serial.println("Moving forward");
    }

    else if (Direction == "B") {
      digitalWrite(LMP, LOW);
      digitalWrite(LMN, HIGH);
      digitalWrite(RMP, LOW);
      digitalWrite(RMN, HIGH);
      Serial.println("Moving backward");
    }

    else if (Direction == "L") {
      digitalWrite(LMP, LOW);
      digitalWrite(LMN, HIGH);
      digitalWrite(RMP, HIGH);
      digitalWrite(RMN, LOW);
      Serial.println("Turning left");
    }

    else if (Direction == "R") {
      digitalWrite(LMP, HIGH);
      digitalWrite(LMN, LOW);
      digitalWrite(RMP, LOW);
      digitalWrite(RMN, HIGH);
      Serial.println("Turning right");
    }

    else if (Direction == "S") {
      digitalWrite(LMP, LOW);
      digitalWrite(LMN, LOW);
      digitalWrite(RMP, LOW);
      digitalWrite(RMN, LOW);
      Serial.println("Stopping");
    }
  }

  if (millis() - elapsedMillis > interval) {
    int rnd = random(1024);
    SerialBT.println(rnd);
    Serial.println(rnd);
    elapsedMillis = millis();
  }
  delay(1);
}  // end loop()
