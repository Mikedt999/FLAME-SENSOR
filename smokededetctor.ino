#include <SoftwareSerial.h>
#include <Wire.h>  //wire library
#include <LiquidCrystal_I2C.h> //liquid crystal with I2C library
#include <Servo.h>
SoftwareSerial BTSerial(10, 11); 
Servo myServo;  
LiquidCrystal_I2C  lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
int red_LED_PIN = 8;
int green_LED_PIN = 9;
int buzzer = 4;
const int flameSensorPin = 2;  // Ακίδα όπου συνδέεται το DO του αισθητήρα φλόγας
int servoPin = 7; 

void setup() {
 
  pinMode(flameSensorPin, INPUT);  // Ρύθμιση της ακίδας αισθητήρα ως είσοδος
  pinMode(red_LED_PIN, OUTPUT);
  pinMode(green_LED_PIN, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.init();                      //  initialize the lcd
       // Attach the servo motor to pin 7
 
  lcd.backlight(); 
   myServo.attach(servoPin);         // Attach the servo motor to pin 7
  myServo.write(0);             // Έναρξη σειριακής επικοινωνίας για εντοπισμό σφαλμάτων//Turn on backlight     // Ρύθμιση της ακίδας LED ως έξοδος
  Serial.begin(9600); 
  BTSerial.begin(9600);  
}
 

void loop() {
  int flameState = digitalRead(flameSensorPin);  // Ανάγνωση κατάστασης από τον αισθητήρα φλόγας

  if (flameState == LOW) {  // Το LOW σημαίνει ότι ανιχνεύτηκε φλόγα
  BTSerial.println("Alert! Flame detected.");
 // Serial.println("Φλόγα ανιχνεύτηκε!");  // Εκτύπωσε μήνυμα στη σειριακή θύρα
  lcd.setCursor(1,0);
  lcd.print("FIRE DETECTED!");
  lcd.setCursor(2,1);
  lcd.print("CALLING:199");
  delay(1000);
  lcd.clear();
  delay(200);
  digitalWrite(red_LED_PIN,HIGH);
  digitalWrite(green_LED_PIN, LOW);
 tone(buzzer,1000);
 delay(100);
 tone(buzzer, 400);
  delay(50);
  myServo.write(180);      
  }
 

  
else {
  BTSerial.println("No Flame Detected.");
 //Serial.println("Καμία φλόγα.");  // Εκτύπωσε μήνυμα στη σειριακή θύρα
  digitalWrite(green_LED_PIN, HIGH);
    digitalWrite(red_LED_PIN,LOW);
 lcd.setCursor(0,0);
 lcd.print("    FIRE NOT    ");
 lcd.setCursor(4,1);
 lcd.print("DETECTED");
 delay(1000);
 lcd.clear();

 delay(200);

noTone(buzzer);
myServo.write(0); 
delay(50);
  }

  delay(50);  // Μικρή καθυστέρηση πριν την επόμενη ανάγνωση
}
