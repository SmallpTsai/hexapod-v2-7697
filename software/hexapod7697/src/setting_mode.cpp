#include <Arduino.h>

#ifndef __LREMOTE_H__
#include <LRemote.h>
#define __LREMOTE_H__
#endif

#include "linkit_control/ui_controls.h"
#include "hexapod/debug.h"
#include "hexapod/hexapod.h"

#define WIDTH 9
#define HEIGHT 18
#define L_W WIDTH
#define L_H 1
#define B_W 2
#define B_H 2
#define T_W 5
#define T_H 2

#define L_X(g)  0
#define L_Y(g)  (L_H+T_H)*g
#define Bl_X(g)  0
#define Bl_Y(g)  (L_H+T_H)*g+L_H
#define T_X(g)  B_W
#define T_Y(g)  (L_H+T_H)*g+L_H
#define Br_X(g)  B_W+T_W
#define Br_Y(g)  (L_H+T_H)*g+L_H

//---------------------------------------------------------------------------
// UI Group: Adjust setting

static Label label1("Select leg", L_X(0), L_Y(0), L_W, L_H);
static Label text1("", T_X(0), T_Y(0), T_W, T_H, RC_PINK);
static Button button1l(10, "<", Bl_X(0), Bl_Y(0), B_W, B_H, RC_BLUE);
static Button button1r(11, ">", Br_X(0), Br_Y(0), B_W, B_H, RC_BLUE);

static Label label2("Select joint", L_X(1), L_Y(1), L_W, L_H);
static Label text2("", T_X(1), T_Y(1), T_W, T_H, RC_PINK);
static Button button2l(20, "<", Bl_X(1), Bl_Y(1), B_W, B_H, RC_BLUE);
static Button button2r(21, ">", Br_X(1), Br_Y(1), B_W, B_H, RC_BLUE);

static Label label3("Servo offset", L_X(2), L_Y(2), L_W, L_H);
static Label text3("0", T_X(2), T_Y(2), T_W, T_H, RC_PINK);
static Button button3l(30, "-", Bl_X(2), Bl_Y(2), B_W, B_H, RC_BLUE);
static Button button3r(31, "+", Br_X(2), Br_Y(2), B_W, B_H, RC_BLUE);

static Label label4("Servo scale", L_X(3), L_Y(3), L_W, L_H);
static Label text4("0", T_X(3), T_Y(3), T_W, T_H, RC_PINK);
static Button button4l(40, "-", Bl_X(3), Bl_Y(3), B_W, B_H, RC_BLUE);
static Button button4r(41, "+", Br_X(3), Br_Y(3), B_W, B_H, RC_BLUE);

static Button buttonSave(60, "Save", 0, Bl_Y(5), WIDTH, B_H, RC_GREEN);

static ButtonGroup btnGroup;

//---------------------------------------------------------------------------
// UI Group: Test

static Label label5("Servo test", L_X(4), L_Y(4), L_W, L_H);
static Button button5l(-45, "-45°", 0, Bl_Y(4), WIDTH/3, B_H, RC_YELLOW);
static Button button5c(0, "0°", WIDTH/3, Bl_Y(4), WIDTH/3, B_H, RC_YELLOW);
static Button button5r(45, "+45°", WIDTH*2/3, Bl_Y(4), WIDTH/3, B_H, RC_YELLOW);

static ButtonGroup btnGroupTest;

//---------------------------------------------------------------------------

const static String _leg_table[] = {
  "front right",
  "right",
  "rear right",
  "rear left",
  "left",
  "front left",
};

const static String _joint_table[] = {
  "body",
  "thigh",
  "foot",
};

static int _cur_leg = 0;
static int _cur_joint = 0;
static int _cur_offset = 0;
static int _cur_scale = 0;
static int _test_angle[3*6] = {0};

void update_text(void) {
  text1.updateText(_leg_table[_cur_leg]);
  text2.updateText(_joint_table[_cur_joint]);
  text3.updateText(String(_cur_offset));
  text4.updateText(String(1+0.01*_cur_scale));
}

static uint8_t led_blink_state = 0;

void setting_setup(void) {

  digitalWrite(LED_BUILTIN, HIGH);

  //
  // initialize config mode UI
  //
  LRemote.setName("Hexapod (S)");
  LRemote.setOrientation(RC_PORTRAIT);
  LRemote.setGrid(WIDTH, HEIGHT);

  LRemote_addControls({
    &label1, &text1, &button1l, &button1r,  // row1
    &label2, &text2, &button2l, &button2r,  // row2
    &label3, &text3, &button3l, &button3r,  // row3
    &label4, &text4, &button4l, &button4r,  // row4
    &label5, &button5l, &button5c, &button5r, // row5
    &buttonSave                             // row6
  });

  //
  // Button group
  //  
  btnGroup.addControls({
    &button1l, &button1r,
    &button2l, &button2r,
    &button3l, &button3r,
    &button4l, &button4r,
    &buttonSave
  });

  btnGroup.config([](int btn_id, ButtonGroup::mode mode) {
    if (mode != ButtonGroup::mode::DOWN && mode != ButtonGroup::mode::REPEAT)
      return;

    Serial.print("button id: ");
    Serial.print(String(btn_id));
    Serial.println(" is triggered");

    int g = btn_id / 10;
    int lr = btn_id % 10;

    switch(g) {
    case 1:
      _cur_leg = (_cur_leg + 6 + (lr ? 1 : -1)) % 6;
      hexapod::Hexapod.calibrationGet(_cur_leg, _cur_joint, _cur_offset, _cur_scale);
      hexapod::Hexapod.calibrationTest(_cur_leg, _cur_joint, _test_angle[_cur_leg*3+_cur_joint]);
      break;
    case 2:
      _cur_joint = (_cur_joint + 3 + (lr ? 1 : -1)) % 3;
      hexapod::Hexapod.calibrationGet(_cur_leg, _cur_joint, _cur_offset, _cur_scale);
      hexapod::Hexapod.calibrationTest(_cur_leg, _cur_joint, _test_angle[_cur_leg*3+_cur_joint]);
      break;
    case 3:
      _cur_offset += (lr ? 1 : -1);
      hexapod::Hexapod.calibrationSet(_cur_leg, _cur_joint, _cur_offset, _cur_scale);
      break;
    case 4:
      _cur_scale += (lr ? 1 : -1);
      hexapod::Hexapod.calibrationSet(_cur_leg, _cur_joint, _cur_offset, _cur_scale);
      break;
    case 6:
      hexapod::Hexapod.calibrationSave();
    }
    update_text();
  });

  //
  // Button group: Testing
  //  
  btnGroupTest.addControls({
    &button5l, &button5c, &button5r
  });

  btnGroupTest.config([](int btn_id, ButtonGroup::mode mode) {
    if (mode != ButtonGroup::mode::DOWN)
      return;
    _test_angle[_cur_leg*3+_cur_joint] = btn_id;
    hexapod::Hexapod.calibrationTest(_cur_leg, _cur_joint, _test_angle[_cur_leg*3+_cur_joint]);
    delay(20);
  });

  //
  // Ready to go
  // 
  hexapod::Hexapod.calibrationGet(_cur_leg, _cur_joint, _cur_offset, _cur_scale);
  update_text();

  for(auto i=0;i<6;i++) {
    for(auto j=0;j<3;j++) {
      hexapod::Hexapod.calibrationTest(i, j, _test_angle[i*3+j]);
    }
  }

  LRemote.begin();
}

void setting_loop(void) {

  // check if we are connect by some 
  // BLE central device, e.g. an mobile app
  if(!LRemote.connected()) {
    delay(500);
    led_blink_state = !led_blink_state;
  } else {
    // The interval between button down/up
    // can be very short - e.g. a quick tap
    // on the screen.
    // We could lose some event if we
    // delay something like 100ms.
    delay(15);
    led_blink_state = 1;
  }
  digitalWrite(LED_BUILTIN, led_blink_state ? HIGH : LOW);

  // Process the incoming BLE write request
  // and translate them to control events
  LRemote.process();  

  btnGroup.process();
  btnGroupTest.process();
}
