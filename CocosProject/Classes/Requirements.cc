
#include "Requirements.h"
#include "Requirement.h"
#include "VictoryScene.h"


Requirements& Requirements::getInstance() {
  static Requirements req;
  return req;
}


void Requirements::create(cocos2d::ui::ListView* rootNode, const std::vector<std::pair<std::string, bool>> & reqs, const std::vector<std::function<void(void)>> &callbacks) {

  rootNode_ = rootNode;
  for (size_t i = 0; i < reqs.size(); ++i) {
    auto req = reqs[i];
    auto callback = callbacks[i];
    auto r = Requirement::create();
    r->setAnchorPoint({ 0.0f, 1.0f });
    r->setPosition({ 0.0f, i*(-34.0f) });
    r->setup(req.first, req.second, callback);

    requirements_.pushBack(r);
    //rootNode_->addChild(r);
    rootNode_->pushBackCustomItem(r);
  }
  //rootNode_->doLayout();
}

void Requirements::evaluate() {
  for (auto& child : requirements_) {
    //children are all labels
    if (!child->evaluate())return;
  }
  auto gameover = VictoryScene::createScene();
  auto director = cocos2d::Director::getInstance();
  director->replaceScene(gameover);
}