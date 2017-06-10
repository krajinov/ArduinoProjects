// Pins
// Fill in the pins you used on your own setup.
// WARNING: Make sure you have resistors connected between the rows and the arduino.

#define ROW_1 14
#define ROW_2 10
#define ROW_3 9
#define ROW_4 12
#define ROW_5 4
#define ROW_6 8
#define ROW_7 5
#define ROW_8 6

#define COL_1 11
#define COL_2 7
#define COL_3 3
#define COL_4 15
#define COL_5 2
#define COL_6 13
#define COL_7 16
#define COL_8 17

const byte rows[] = {
  ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};

const byte cols[] = {
  COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8
};

// The display buffer
// It's prefilled with a smiling face (1 = ON, 0 = OFF)
const byte smile[8] = {
  B01111110, 
  B10000001, 
  B10100101, 
  B00000000, 
  B00011000, 
  B01000010, 
  B00111100, 
  B00000000};
const byte nutral[8] = {
  B11111111, 
  B10000001, 
  B10100101, 
  B10000001, 
  B10000001, 
  B10111101, 
  B10000001, 
  B11111111};
const byte angry[8] = {
  B11111111, 
  B10000001, 
  B10100101, 
  B10000001, 
  B00000000, 
  B00111100, 
  B01000010, 
  B00000000};
const byte arrow[8] = {
  B00010000,
  B00110000,
  B01111111,
  B11111111,
  B01111111,
  B00110000,
  B00010000,
  B00000000
};

float timeCount = 0;

void setup() {
  // Open serial port
  Serial.begin(9600);

  // Set all used pins to OUTPUT
  // This is very important! If the pins are set to input
  // the display will be very dim.
  for (byte i = 2; i <= 17; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  // This could be rewritten to not use a delay, which would make it appear brighter
  delay(1);
  timeCount += 1;
  if (timeCount <  200) {
    drawScreen(nutral);
  } else if (timeCount <  230) {
    // do nothing
  } else if (timeCount <  400) {
    drawScreen(smile);
  } else if (timeCount <  430) {
    // nothing
  } else if (timeCount <  600) {
    drawScreen(nutral);
  } else if (timeCount <  630) {
    // nothing
  } else if (timeCount <  800) {
    drawScreen(angry);
  } else if (timeCount <  830) {
    // nothing
  } else if (timeCount <  1000) {
    drawScreen(smile);
  } else if (timeCount <  1030) {
    // nothing
  } else if (timeCount <  1200) {
    drawScreen(angry);
  } else if (timeCount <  1230) {
    // nothing
  } else if (timeCount <  1460) {
    drawScreen(arrow);
  } else if (timeCount <  1490) {
    // nothing
  } else {
    // back to the start
    timeCount = 0;
  }
}
void  drawScreen(byte buffer2[]) {
  // Turn on each row in series
  for (byte i = 0; i < 8; i++) {
    setColumns(buffer2[i]);     // Set columns for this specific row
    digitalWrite(rows[i], LOW); // If your matrix is row anode set this to HIGH
    delayMicroseconds(1500);    // Set this to 50 or 100 if you want to see the multiplexing effect!
    digitalWrite(rows[i], HIGH);
  }
}


void setColumns(byte b) {
  for(int i = 0; i<8; i++){
    digitalWrite(cols[i], (b >> 7-i) & 0x01); // Get the "7-i" bit: 00000001 (for i = 0)
    }
  // If the polarity of your matrix is the opposite of mine
  // add the '~' above (~b >> i).
}

