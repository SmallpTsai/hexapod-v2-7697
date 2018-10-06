#include <Arduino.h>
#include "ui_controls.h"

namespace {
  const static int kRepeatPeriod1 = 500;
  const static int kRepeatPeriod1Count = 4;
  const static int kRepeatPeriod2 = 100;
}

void ButtonGroup::addControl(Button &button) {
  // prevent duplicated entry
  for (const auto control : controls_) {
    if (control == &button) {
      return;
    }
  }
  controls_.push_back(&button);
};

void ButtonGroup::addControl(Button *button) {
  // prevent duplicated entry
  for (const auto control : controls_) {
    if (control == button) {
      return;
    }
  }
  controls_.push_back(button);
};

void ButtonGroup::addControls(std::vector<Button *> lists) {
  for (auto button : lists) {
    addControl(button);
  }
}

void ButtonGroup::process() {
  if (!callback_)
    return;

  if (pressed_) {
    if (pressed_->isValueChanged() && pressed_->getValue() == 0) {
      callback_(pressed_->_id, UP);
      pressed_ = nullptr;
    }
    else if (millis() >= time_repeat_) {
      callback_(pressed_->_id, REPEAT);
      count_repeat_ += 1;
      if (count_repeat_ < kRepeatPeriod1Count)
        time_repeat_ = millis() + kRepeatPeriod1;
      else
        time_repeat_ = millis() + kRepeatPeriod2;
    }
  }
  else {
    for (auto control : controls_) {
      if (control->isValueChanged() && control->getValue() == 1) {
        // only 1 button can be pressed at the same time within the same group
        pressed_ = control;
        time_repeat_ = millis() + kRepeatPeriod1;
        count_repeat_ = 0;
        callback_(control->_id, DOWN);
        return;
      }
    }
  }
}

int ButtonGroup::getPressFlag() {
  int flag = 0;
  for (auto control : controls_) {
    if (control->getValue() == 1) {
      if (control->_id < 32)
        flag |= (1<<control->_id);
    }
  }
  return flag;
}

void LRemote_addControls(std::vector<LRemoteUIControl *> lists) {
  for (auto control : lists) {
    LRemote.addControl(*control);
  }
}