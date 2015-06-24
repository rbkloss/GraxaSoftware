#ifndef _GRAXA_REQUIREMENT_H_
#define _GRAXA_REQUIREMENT_H_

#include "cocos2d.h"
#include "ui\CocosGUI.h"

class Requirement : public cocos2d::ui::Widget {
  cocos2d::ui::Button* fixButton_ = nullptr;
  cocos2d::ui::Text* text_ = nullptr;
  cocos2d::ui::CheckBox* state_ = nullptr;
  bool isWorking_;




  public:
  void setup(const std::string &text, bool working_, const std::function<void(void)> &fixCallBack);
  bool evaluate();
  float getHeight();

  CREATE_FUNC(Requirement);

};

#endif
