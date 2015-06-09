#ifndef _TUTORIAl_SCENE_H_
#define _TUTORIAl_SCENE_H_


#include <memory>

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Hero;
class TutorialScene : public cocos2d::Layer {
  int state_;
  std::vector<std::string> texts_;
  cocos2d::ui::Button* button_;
  cocos2d::ui::Text* textLabel_;
  public:
  // Creates An auto-release scene object for the first stage
  static cocos2d::Scene* createScene();

  // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
  virtual bool init() override;

  // implement the "static create()" method manually
  CREATE_FUNC(TutorialScene);
};
#endif