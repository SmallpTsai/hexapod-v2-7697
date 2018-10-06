
#include "src/setting_mode.h"
#include "src/normal_mode.h"

#include "src/hexapod/debug.h"
#include "src/hexapod/hexapod.h"

//
//  mode
//    0:  normal mode
//    1:  setting mode (for servo calibration)
//
static int _mode = 0;

static void log_output(const char* log) {
  Serial.println(log);
}

//
// wait for N secs, enter setting mode if pressed USR button
//
void boot_wait(int wait_for = 2000) {
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(6, INPUT);
  while (wait_for > 0) {
    if (HIGH == digitalRead(6)) {
      _mode = 1;
      break;
    }
    delay(100);
    wait_for -= 100;
  }

  digitalWrite(LED_BUILTIN, LOW);
}

//
//  Do common setup and mode-specific setup
//
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  Serial.println("Starting...");

  //
  // Common setup()
  //

  // Initialize GPIO
  pinMode(LED_BUILTIN, OUTPUT);

  // Workaround for beta PCB
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  boot_wait();

  hexapod::initLogOutput(log_output, millis);
  hexapod::Hexapod.init(_mode == 1);

  //
  // Mode-specific setup()
  //

  if (_mode == 0) {
    normal_setup();
  }
  else if (_mode == 1) {
    setting_setup();
  }

  Serial.print("Started, mode=");
  Serial.println(_mode);
}

void loop() {
  if (_mode == 0) {
    normal_loop();
  }
  else if (_mode == 1) {
    setting_loop();
  }
}
