#include <EEPROM.h>

// Настройки
const unsigned long BAUD_RATE = 115200;
const char PREFIX[] = "eeprom";
#define MAX_TOKENS 10

// Прототипы функций операций
void handleWrite(int address, uint8_t value);
void handleRead(int address);
void handleErase(int address);
void handleDump();

void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial) {
    ; // ждём подключения Serial
  }
  Serial.println("EEPROM CLI ready");
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.length() > 0) {
      processCommand(line);
    }
  }
}

// Разбивает строку на токены по пробелам
void tokenize(const String &str, String tokens[], int &count) {
  count = 0;
  int start = 0;
  for (int i = 0; i <= str.length(); ++i) {
    if (i == str.length() || isspace(str[i])) {
      if (i - start > 0 && count < MAX_TOKENS) {
        tokens[count++] = str.substring(start, i);
      }
      start = i + 1;
    }
  }
}

void processCommand(const String &line) {
  String args[MAX_TOKENS];
  int argc;
  tokenize(line, args, argc);

  if (argc == 0 || args[0] != PREFIX) {
    Serial.println("ERROR: Unknown prefix");
    return;
  }

  bool flagW = false, flagR = false, flagE = false, flagD = false;
  int address = -1;
  uint8_t value = 0;

  for (int i = 1; i < argc; ++i) {
    String t = args[i];
    if (t == "-w") flagW = true;
    else if (t == "-r") flagR = true;
    else if (t == "-e") flagE = true;
    else if (t == "-d") flagD = true;
    else if (t == "-a" && i + 1 < argc) address = args[++i].toInt();
    else if (t == "-v" && i + 1 < argc) value = args[++i].toInt();
    else {
      Serial.print("ERROR: Unknown argument ");
      Serial.println(t);
      return;
    }
  }

  if (flagD) {
    handleDump();
    return;
  }

  if (address < 0 || address >= EEPROM.length()) {
    Serial.println("ERROR: Address out of range");
    return;
  }

  if (flagW) {
    handleWrite(address, value);
    return;
  }

  if (flagR) {
    handleRead(address);
    return;
  }

  if (flagE) {
    handleErase(address);
    return;
  }

  Serial.println("ERROR: No valid operation specified");
}

// Функции выполнения операций
void handleWrite(int address, uint8_t value) {
  EEPROM.write(address, value);
  Serial.println("OK");
}

void handleRead(int address) {
  uint8_t v = EEPROM.read(address);
  Serial.println(v);
}

void handleErase(int address) {
  EEPROM.write(address, 0xFF);
  Serial.println("OK");
}

void handleDump() {
  const int N = EEPROM.length();
  for (int i = 0; i < N; i += 8) {
    char buf[6];
    sprintf(buf, "%04X", i);
    Serial.print(buf);
    Serial.print(" :");
    for (int j = 0; j < 8 && i + j < N; ++j) {
      uint8_t b = EEPROM.read(i + j);
      char h[4];
      sprintf(h, " %02X", b);
      Serial.print(h);
    }
    Serial.println();
  }
}
