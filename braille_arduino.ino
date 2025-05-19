// Braille Display using Arduino UNO
// Pins for Braille dots (using LEDs or vibration motors)
const int dot1 = 13;  // Top left
const int dot2 = 3;   // Middle left
const int dot3 = 4;   // Bottom left
const int dot4 = 5;   // Top right
const int dot5 = 6;   // Middle right
const int dot6 = 7;   // Bottom right

const byte braillePatterns[] = {
  // Letters a-j
  0b000001, // a
  0b000011, // b
  0b000101, // c
  0b000111, // d
  0b000110, // e
  0b000101, // f
  0b000111, // g
  0b000101, // h
  0b000011, // i
  0b000111, // j

  // Letters k-t
  0b001001, // k
  0b001011, // l
  0b001101, // m
  0b001111, // n
  0b001110, // o
  0b001101, // p
  0b001111, // q
  0b001101, // r
  0b001011, // s
  0b001111, // t

  // Letters u-z
  0b101001, // u
  0b101011, // v
  0b101101, // w
  0b101111, // x
  0b101110, // y
  0b101101, // z

  // Numbers 0-9 (reusing a-j)
  0b001111, // 0
  0b000001, // 1
  0b000011, // 2
  0b000101, // 3
  0b000111, // 4
  0b000110, // 5
  0b000101, // 6
  0b000111, // 7
  0b000101, // 8
  0b000011, // 9

  // Space
  0b000000  // space
};

String input = "bbbbbbb";  // Set your text here
int currentIndex = 0;

void setup() {
  // Setup Braille pins
  pinMode(dot1, OUTPUT);
  pinMode(dot2, OUTPUT);
  pinMode(dot3, OUTPUT);
  pinMode(dot4, OUTPUT);
  pinMode(dot5, OUTPUT);
  pinMode(dot6, OUTPUT);

  Serial.begin(9600);
  Serial.println("Braille Display Starting...");
}

void loop() {
  if (currentIndex < input.length()) {
    char c = input.charAt(currentIndex);
    Serial.print("Character: ");
    Serial.println(c);

    displayBrailleChar(c);
    delay(1000);  // Wait for 5 seconds
    clearDots();
    delay(200);   // Brief pause between characters

    currentIndex++;
  } else {
    // Stop after finishing the string
    while (true);
  }
}

void displayBrailleChar(char c) {
  int index = -1;

  if (c >= 'a' && c <= 'z') index = c - 'a';
  else if (c >= 'A' && c <= 'Z') index = c - 'A';
  else if (c >= '0' && c <= '9') index = 26 + (c - '0');
  else if (c == ' ') index = 36;

  if (index >= 0 && index < sizeof(braillePatterns)) {
    byte pattern = braillePatterns[index];
    digitalWrite(dot1, pattern & 0b000001);
    digitalWrite(dot2, pattern & 0b000010);
    digitalWrite(dot3, pattern & 0b000100);
    digitalWrite(dot4, pattern & 0b001000);
    digitalWrite(dot5, pattern & 0b010000);
    digitalWrite(dot6, pattern & 0b100000);

    Serial.print("Braille binary: ");
    Serial.println(pattern, BIN);
  } else {
    Serial.println("Invalid character");
  }
  delay(2000);
}

void clearDots() {
  digitalWrite(dot1, LOW);
  digitalWrite(dot2, LOW);
  digitalWrite(dot3, LOW);
  digitalWrite(dot4, LOW);
  digitalWrite(dot5, LOW);
  digitalWrite(dot6, LOW);
}

