#pragma once

#ifndef __LREMOTE_H__
#include <LRemote.h>
#define __LREMOTE_H__
#endif

class Label : public LRemoteLabel {
public:
  Label(const String &text, uint8_t x, uint8_t y, uint8_t w, uint8_t h, RCColorType color = RC_GREY) : LRemoteLabel() {
    setText(text);
    setPos(x, y);
    setSize(w, h);
    setColor(color);
  }
};


class Button : public LRemoteButton {
public:
  Button(int id, const String &text, uint8_t x, uint8_t y, uint8_t w, uint8_t h, RCColorType color = RC_GREY) : LRemoteButton() {
    setText(text);
    setPos(x, y);
    setSize(w, h);
    setColor(color);
    _id = id;
  }

public:
  int _id;
};

#include <vector>
#include <functional>

class ButtonGroup {
public:

  enum mode {
    NONE = 0,
    DOWN,
    UP,
    REPEAT
  };

  void config(std::function<void(int, mode)> callback) {
    callback_ = callback;
  };

  void addControl(Button &button);
  void addControl(Button *button);
  void addControls(std::vector<Button *> lists);
  void process();

  int getPressFlag();

public:
  std::vector<Button *> controls_;
  std::function<void(int, mode)> callback_ = nullptr;
  Button *pressed_ = nullptr;
  int time_repeat_ = 0;
  int count_repeat_ = 0;
};

void LRemote_addControls(std::vector<LRemoteUIControl *> lists);