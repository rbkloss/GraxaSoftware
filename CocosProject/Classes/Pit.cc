#include "Pit.h"

#include "Hero.h"
#include "Blocks.h"

void PitBlock::setup(int x, int y, int width, int height, 
  cocos2d::Node* rootNode, const std::string &name){
  auto pitNode = cocos2d::DrawNode::create();
  auto body = cocos2d::PhysicsBody::createBox(cocos2d::Size(
    static_cast<float>(width), static_cast<float>(height)));
  pitNode->setName(name);
  body->setCollisionBitmask(0);
  body->setContactTestBitmask(Blocks::PIT_BLOCK);
  body->setDynamic(false);

  pitNode->setPhysicsBody(body);
  float w = static_cast<float>(width) / 2;
  float h = static_cast<float>(height) / 2;
  pitNode->setPosition(static_cast<float>(x)+w,
    static_cast<float>(y)+h);

  auto contactListener = cocos2d::EventListenerPhysicsContact::create();

  contactListener->onContactBegin = [](cocos2d::PhysicsContact &contact)->bool {
    auto shapeA = contact.getShapeA();
    auto bodyA = shapeA->getBody();
    auto shapeB = contact.getShapeB();
    auto bodyB = shapeB->getBody();

    auto nodeA = bodyA->getNode();
    auto nodeB = bodyB->getNode();

    bool ans = false;
    if (nodeA->getName() == Hero::getName()) {
      auto bName = nodeB->getName();
      if (bName.find("pit") != bName.npos) {
        ans = true;
        Hero::getInstance()->die();
      }

    } else if (nodeB->getName() == Hero::getName()) {
      auto aName = nodeA->getName();
      if (aName.find("pit") != aName.npos) {
        ans = true;
        Hero::getInstance()->die();
      }

    }

    return ans;
  };

  cocos2d::Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(contactListener, pitNode);

  rootNode->addChild(pitNode);  
}

