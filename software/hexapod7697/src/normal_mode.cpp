#include <Arduino.h>

#ifndef __LREMOTE_H__
#include <LRemote.h>
#define __LREMOTE_H__
#endif

#include "linkit_control/ui_controls.h"
#include "hexapod/debug.h"
#include "hexapod/config.h"
#include "hexapod/hexapod.h"

#define REACT_DELAY hexapod::config::movementInterval

static Button buttonForward(hexapod::MOVEMENT_FORWARD, "Forward", 1, 1, 1, 1, RC_BLUE);
static Button buttonBackward(hexapod::MOVEMENT_BACKWARD, "Backward", 1, 3, 1, 1, RC_BLUE);
static Button buttonTL(hexapod::MOVEMENT_TURNLEFT, "TurnLeft", 0, 2, 1, 1, RC_BLUE);
static Button buttonTR(hexapod::MOVEMENT_TURNRIGHT, "TurnRight", 2, 2, 1, 1, RC_BLUE);
static Button buttonSL(hexapod::MOVEMENT_SHIFTLEFT, "ShiftLeft", 0, 3, 1, 1, RC_YELLOW);
static Button buttonSR(hexapod::MOVEMENT_SHIFTRIGHT, "ShiftRight", 2, 3, 1, 1, RC_YELLOW);
static Button buttonRotateX(hexapod::MOVEMENT_ROTATEX, "RotateX", 0, 0, 1, 1, RC_YELLOW);
static Button buttonRotateY(hexapod::MOVEMENT_ROTATEY, "RotateY", 1, 0, 1, 1, RC_YELLOW);
static Button buttonRotateZ(hexapod::MOVEMENT_ROTATEZ, "RotateZ", 2, 0, 1, 1, RC_YELLOW);

static ButtonGroup btnGroup;

static void log_output(const char* log) {
  Serial.println(log);
}

void normal_setup(void) {
  LRemote.setName("Hexapod");
  LRemote.setOrientation(RC_PORTRAIT);
  LRemote.setGrid(3, 5);

  LRemote_addControls({
    &buttonForward, &buttonBackward,
    &buttonTL, &buttonTR,
    &buttonSL, &buttonSR,
    &buttonRotateX, &buttonRotateY, &buttonRotateZ,
  });
  btnGroup.addControls({
    &buttonForward, &buttonBackward,
    &buttonTL, &buttonTR,
    &buttonSL, &buttonSR,
    &buttonRotateX, &buttonRotateY, &buttonRotateZ,
  });

  LRemote.begin();
}

void normal_loop(void) {

  // check if we are connect by some 
  // BLE central device, e.g. an mobile app
  if(!LRemote.connected()) {
    delay(1000-REACT_DELAY);
  }

  auto t0 = millis();

  // Process the incoming BLE write request
  // and translate them to control events
  LRemote.process();  

  auto flag = btnGroup.getPressFlag();
  auto mode = hexapod::MOVEMENT_STANDBY;
  for (auto m = hexapod::MOVEMENT_STANDBY; m < hexapod::MOVEMENT_TOTAL; m++) {
    if (flag & (1<<m)) {
      mode = m;
      break;
    }
  }

  hexapod::Hexapod.processMovement(mode, REACT_DELAY);

  auto spent = millis() - t0;

  if(spent < REACT_DELAY) {
    // Serial.println(spent);
    delay(REACT_DELAY-spent);
  }
  else {
    Serial.println(spent);
  }
}