#include "Requirement.h"
#include "ui\CocosGUI.h"
#include "DevGameOverScene.h"
#include "ClientGameOverScene.h"

void Requirement::setup(const std::string& text, bool working_, const std::function<void()>& fixCallBack) {
  text_ = cocos2d::ui::Text::create(text, "arial.ttf", 32);
  text_->setAnchorPoint({ 0.0f, 1.0f });
  text_->setTextColor(cocos2d::Color4B(0x0, 0x0, 0x0, 0xff));
  this->addChild(text_);
  text_->setPosition(this->getPosition());
  auto textSz = text_->getContentSize();

  fixButton_ = cocos2d::ui::Button::create("Default/Button_Normal.png", "Default/Button_Press.png", "Default/Button_Disable.png");
  fixButton_->setTitleText("Fix!");
  fixButton_->setTitleColor({ 0x0, 0x0, 0x0 });
  fixButton_->setAnchorPoint({ 0.0f, 1.0f });
  fixButton_->setContentSize({ 64.0f, 32.0f });
  fixButton_->setPosition({ textSz.width + 20, getHeight() });
  fixButton_->addTouchEventListener([this, fixCallBack](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
      if (isWorking_ == false ) {
        //test is correct, it is not working and checked
        fixCallBack();
        isWorking_ = true;
      } else if (isWorking_ == true) {
        //the gamer missed the test
        auto gameover = DevGameOverScene::createScene();
        auto director = cocos2d::Director::getInstance();
        director->replaceScene(gameover);
      }
    }
  });
  //auto fixButtonSz = fixButton_->getContentSize();

  /*state_ = cocos2d::ui::CheckBox::create("Default/CheckBox_Normal.png", "Default/CheckBox_Press.png", "Default/CheckBoxNode_Normal.png",
    "Default/CheckBox_Disable.png", "Default/CheckBoxNode_Disable.png");
  state_->setAnchorPoint({ 0.0f, 1.0f });
  state_->setContentSize({ 64.0f, 32.0f });
  state_->setPosition({ textSz.width + fixButtonSz.width + 40, getHeight() });*/

  isWorking_ = working_;

  text_->addChild(fixButton_);
  //text_->addChild(state_);
}

bool Requirement::evaluate(){
  if (!isWorking_){
   //the gamer let this one pass, this requirement is not working =[
    auto gameover = ClientGameOverScene::createScene();
    auto director = cocos2d::Director::getInstance();
    director->replaceScene(gameover);
    return false;
  }
  return true;
}

float Requirement::getHeight() {
  return text_->getContentSize().height;
}