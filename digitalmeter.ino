#include <TM1637Display.h>
#include <HCSR04.h>

byte triggerPin = 2;
byte echoPin = 3;
#define DIO 4
#define CLK 5

int default_delay = 250; //Change this value in order to reduce or increase measurement frequency

const uint8_t SEG_KUCZ[] = {
  SEG_B | SEG_C | SEG_F | SEG_E | SEG_G,           // K
  SEG_F | SEG_B | SEG_C | SEG_D | SEG_E,           // U
  SEG_A | SEG_F | SEG_E | SEG_D,                   // C
  SEG_A | SEG_B | SEG_G | SEG_E | SEG_D            // Z
  };
  const uint8_t SEG_IS[] = {
   SEG_D ,                                               // nic
  SEG_F | SEG_E,                                  // I
  SEG_A | SEG_F | SEG_G | SEG_D | SEG_C,          // S
  SEG_D ,
                                                  // nic
  };

TM1637Display display(CLK, DIO);

void setup () {
  HCSR04.begin(triggerPin, echoPin);
  display.setBrightness(0x0f);
  display.setSegments(SEG_KUCZ);
  delay(1000);
  display.setSegments(SEG_IS);
  delay(1000);
}

void loop () {
  double* distances = HCSR04.measureDistanceCm();

  if (distances[0] > 0){
      display.showNumberDecEx(distances[0], true);
  }
   delay(default_delay);
}
