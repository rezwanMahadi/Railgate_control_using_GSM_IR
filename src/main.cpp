#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

#define forcePin 14
#define ir_1 23
#define ir_2 19
#define ir_3 4
#define ir_4 26
#define ir_5 25
#define ir_6 33
#define ir_7 32
#define ir_8 35
#define ir_9 27
#define buzzerPin 13
#define servoPin 18

String mobileNumber = "01844894278";
String msg = "Check the gate. Train is coming.";

LiquidCrystal_I2C lcd(0x27,16,2);
Servo gate;
HardwareSerial serialsms(1);


void send_message(String number, String message)
{
  serialsms.println("AT+CMGF=1");
  delay(1000);

  // Send new SMS command and phone number
  serialsms.print("AT+CMGS=\"");
  serialsms.print(number);
  serialsms.println("\"");
  delay(1000);

  // Send the SMS message
  serialsms.print(message);
  serialsms.write((char)26); // Ctrl+Z to send the message
  delay(1000);
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.print("Welcome");
  serialsms.begin(9600, SERIAL_8N1, 18, 5);
  pinMode(forcePin, INPUT);
  pinMode(ir_1, INPUT);
  pinMode(ir_2, INPUT);
  pinMode(ir_3, INPUT);
  pinMode(ir_4, INPUT);
  pinMode(ir_5, INPUT);
  pinMode(ir_6, INPUT);
  pinMode(ir_7, INPUT);
  pinMode(ir_8, INPUT);
  pinMode(ir_9, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);
  analogSetAttenuation(ADC_11db);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  gate.attach(servoPin, 500, 2000);
  gate.write(115);
  delay(1000);
  gate.detach();
}

void loop() {
  if(analogRead(forcePin) >= 2000){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Train is Coming");
    digitalWrite(buzzerPin, LOW); 
    send_message(mobileNumber, msg);
    delay(2000);
    while(true)
    {
      if(digitalRead(ir_1) == LOW)
      {
        lcd.clear();
        lcd.print("Distance:19.5in");
        while (true)
        {
          if (digitalRead(ir_2) == LOW)
          {
            lcd.clear();
            lcd.print("Distance:17.5in");
            while (true)
            {
              if (digitalRead(ir_3) == LOW)
              {
                lcd.clear();
                lcd.print("Distance:14.8in");
                while (true)
                {
                  if (digitalRead(ir_4) == LOW)
                  {
                    lcd.clear();
                    lcd.print("Distance:12in");
                    while (true)
                    {
                      if (digitalRead(ir_5) == LOW)
                      {
                        lcd.clear();
                        lcd.print("Distance:9.5in");
                        while (true)
                        {
                          if (digitalRead(ir_6) == LOW)
                          {
                            lcd.clear();
                            lcd.print("Distance:7in");
                            while (true)
                            {
                              if (digitalRead(ir_7) == LOW)
                              {
                                lcd.clear();
                                lcd.print("Distance:4.5in");
                                while (true)
                                {
                                  if (digitalRead(ir_8) == LOW)
                                  {
                                    lcd.clear();
                                    lcd.print("Distance:2.5in");
                                    gate.attach(servoPin, 500, 2000);
                                    gate.write(0);
                                    delay(1000);
                                    gate.detach();
                                    while (true)
                                    {
                                      digitalWrite(buzzerPin, LOW);
                                      if (digitalRead(ir_9) == LOW)
                                      {
                                        digitalWrite(buzzerPin, HIGH);
                                        gate.attach(servoPin, 500, 2000);
                                        gate.write(115);
                                        delay(1000);
                                        gate.detach();
                                        break;
                                      }
                                    }
                                    break;
                                  }
                                }
                                break;
                              }
                            }
                            break;
                          }
                        }
                        break;
                      }
                    }
                    break;
                  }
                }
                break;
              }
            }
            break;
          }
        }
        break;
      }
    }
  }
}