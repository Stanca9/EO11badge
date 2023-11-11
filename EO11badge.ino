#include <string.h>
#include <EEPROM.h>

#define M 4
#define L 5
#define R 6
#define BOOT_CTR_EEPROM_ADDR 0
#define FIRST_BOOT 0
#define SECOND_BOOT_PLUS 1
#define WRITEBYTE(x) {PORTB = ~(x & 0x0F); PORTC = ~((x & 0xF0) >> 4);}

// CONSTANT DECLARATIONS
const unsigned char *morseCode[] = {
    ".-",   // A
    "-...", // B
    "-.-.", // C
    "-..",  // D
    ".",    // E
    "..-.", // F
    "--.",  // G
    "....", // H
    "..",   // I
    ".---", // J
    "-.-",  // K
    ".-..", // L
    "--",   // M
    "-.",   // N
    "---",  // O
    ".--.", // P
    "--.-", // Q
    ".-.",  // R
    "...",  // S
    "-",    // T
    "..-",  // U
    "...-", // V
    ".--",  // W
    "-..-", // X
    "-.--", // Y
    "--.."  // Z
};
const int leds[] = {8, 9, 10, 11, A0, A1, A2, A3};
// const unsigned char animations[1][] = {{}}

// FUNCTION PROTOTYPE DECLARATIONS
void writeMorse(char c);
void sleep(unsigned long milliseconds);
void animCounting(), animFlicker(), animCharging(), animMorse(), animRotate(), animTravel();

// GLOBAL VARIABLES
unsigned long long int globalFrameCounter = 0;

// INTERRUPT SERVICE ROUTINES
ISR(PCINT2_vect){}
ISR(WDT_vect){
  globalFrameCounter++; // increment global frame counter
}

// SETUP CODE
void setup() {
  // Configs for power saving
  CLKPR = 0b10000000; // Prepare reg for clock change
  CLKPR = 0b00000100; // Divide clock by 16, slowing it down to 1MHz
  PRR0 = 0xFF; // Stop clocks to I2C0, TIM2, TIM0, USART1, TIM1, SPI0, USART0, and ADC
  PRR1 = 0xFF; // Stop clocks to I2C1, PTC, TIM4, SPI1, and TIM3
  MCUCR = (MCUCR & ~(1 << BODS)) | (1 << BODSE); // Disable BOD

  // Set up GPIOs
  pinMode(L, INPUT_PULLUP);
  pinMode(R, INPUT_PULLUP);
  pinMode(M, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  for(int i =0; i<8; i++){
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH);
  }

  // Set up interrupts on all buttons
  PCICR |= (1 << PCIE2); // Enable Pin Change interrupts
  PCMSK2 = (1 << PCINT20) | (1 << PCINT21) | (1 << PCINT22); // Set up interrupts on button pins
  sei(); // Enable global interrupts

  // Read boot counter from EEPROM
  unsigned char bootCtr = EEPROM.read(BOOT_CTR_EEPROM_ADDR);

  // Enter Power down sleep for first boot (when battery is inserted) until a button is pressed
  SMCR |= 0b00000100; // Set power mode to 'Power-down'
  SMCR |= 1; // Enable sleep
  if(bootCtr == FIRST_BOOT){
    __asm__ __volatile__("sleep");
    EEPROM.write(BOOT_CTR_EEPROM_ADDR, SECOND_BOOT_PLUS);
  }

  // Note: This code runs after a button is pressed and microcontroller returns from sleep
  PCICR &= ~(1 << PCIE2); // Disable Pin Change interrupts

  // Set up Watchdog Timer
  WDTCSR = 0x18; // Set WDE and WDCE bits
  WDTCSR = 0x00; // Set up WDT persalers for 16ms oscilator. Clear WDE and WDCE bits
  // WDTCSR = 0x05; // Set up WDT persalers for 500ms oscilator. Clear WDE and WDCE bits
  WDTCSR |= (1 << WDIE); // Enable WDT interrupt
}

// MAIN PROGRAM LOOP
void loop() {
  // array of function pointers that get called to play an animation
  static void(*animations[])(void) = {animTravel, animFlicker, animMorse, animRotate};
  static const int animationCount = 4; // keeps track of currently playing animation
  
  // animation disply loop
  for(int i = 0; i < animationCount; i++){
    animations[i](); // call the function to display the current animation
    WRITEBYTE(0); // turn off all LEDs
    sleep(1000); // delay between animations
  }
}

// FUNCTION IMPLEMENTATIONS
void writeMorse(char* s){
  while(*s != 0){
    writeMorseLetter(*s);
    s++;
  }
}

void writeMorseLetter(char c){
  char* letter = morseCode[c - 'A'];
  while(*letter != 0){
    WRITEBYTE(1 << 5);
    if(*letter == '.') sleep(200); // Dot (.) - 1s
    else sleep(600); // Dash (-) - 3s
    WRITEBYTE(0);
    sleep(200); // Space between symbols (within the same letter) - 1s
    letter++;
  }
  sleep(600); //Space between letters - 3s
}

// animation where the flickering light travels
void animTravel(){
  static const unsigned char nodeInterrconectMatrix[8][4] = {{4, 6, -1, -1}, {3, 4, 6, 7}, {3, 4, 5, -1}, {1, 2, 7, -1}, {0, 1, 2, 6}, {2, -1, -1, -1}, {0, 1, 4, 7}, {1, 3, 7, -1}};
  static const unsigned char nodeConnectionCounts[8] = {2, 4, 3, 3, 4, 1, 4, 3};

  unsigned static char node = random(8);

  for(int i = 0 ; i < 30; i++){
    WRITEBYTE(1 << node);
    node = nodeInterrconectMatrix[node][random() % nodeConnectionCounts[node]];
    sleep(100);
  }
}

// animation where the light rotates in a circle
void animRotate(){
  static unsigned char frames[] = {0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00000001, 0b00000010, 0b00000100, 0b00001000};
  
  int x = 0;
  unsigned long long int frameCounterCopy = globalFrameCounter;
  while(frameCounterCopy + 150 > globalFrameCounter){
    WRITEBYTE(frames[x]);
    x = (x + 1) % 8;
    __asm__ __volatile__("sleep");
    __asm__ __volatile__("sleep");
  }
}

// animation where lights slowly charge up
void animCharging(){
  static char vals[] = {0b10000000, 0b11000000, 0b11100000, 0b11110000, 0b11110001, 0b11110011, 0b11110111, 0b11111111, 0};
  static int x = 0;
  static long unsigned int timer = 0;
  static int delay = 40;
  while(1){
    if(millis() > timer + delay){
      WRITEBYTE(vals[x]);
      x = (x + 1) % 9;
      timer = millis();
      if(x == 0){
        if(delay == 40) delay = 2;
        else if(delay == 2) delay = 1;
        else if(delay == 1) return;
      }
    }
  }
}

// animation where lights randomnly flicker
void animFlicker(){
  static unsigned char x = 1;
  unsigned long long int frameCounterCopy = globalFrameCounter;
  while(frameCounterCopy + 100 > globalFrameCounter){
    x = 1 << (rand() % 8);
    WRITEBYTE(x);
    __asm__ __volatile__("sleep");
  }
};

void animCounting(){
  unsigned char x = 1;
  while(x){
    WRITEBYTE(x);
    x++;
    __asm__ __volatile__("sleep");
  }
}

// animation that displays a message
void animMorse(){
  writeMorse("EESTEC");
}

// sleeps for enough frames to get to aproximatly that delay
void sleep(unsigned long milliseconds){
  unsigned long sleepFrames = milliseconds / 16;
  for(unsigned long i = 0; i < sleepFrames; i++)
    __asm__ __volatile__("sleep");
}