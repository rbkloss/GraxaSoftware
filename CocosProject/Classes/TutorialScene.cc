#include "TutorialScene.h"

#include "cocostudio/CocoStudio.h"


#include "StageOneScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

cocos2d::Scene* TutorialScene::createScene() {
  // 'scene' is an autorelease object
  auto scene = Scene::create();

  // 'layer' is an autorelease object
  auto layer = TutorialScene::create();

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool TutorialScene::init() {
  // 1. super init first
  if (!Layer::init()) {
    return false;
  }
  auto rootNode = CSLoader::createNode("TutorialScene.csb");

  state_ = 0;
  button_ = dynamic_cast<cocos2d::ui::Button*>(rootNode->getChildByName("button"));
  auto node = (rootNode->getChildByName("textBox"));
  textLabel_ = dynamic_cast<cocos2d::ui::Text*>(node);
  texts_ = {
    "Bem vindo ao time Graxa!",//0
    "Estamos desenvolvendo um jogo!",//1
    "Ainda bem que estah aqui!",//2
    "O time estah bem ocupado,",//3
    "Estavamos precisando de alguem\n\
para realizar alguns testes de \n\
aceitacao antes de enviarmos\n\
os entregaveis ao cliente",//4
    "Por favor! teste\n\
se os requisitos,\n\
apresentados na\n\
caixa a direita\n\
estao funcionando",//5
    "Para isso marque nas caixinhas\n\
quais estariam funcionando,\n\
e quais precisam de conserto",//6
     "Quando terminar clique \n\
no botao estrela,\n\
o botao cuidarah\n\
da entrega ao cliente"//7
  };
  button_->addTouchEventListener(
    [rootNode, this]
  (Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
      switch (state_) {
        case(5) : {
          auto arrow = dynamic_cast<cocos2d::Sprite*>
            (rootNode->getChildByName("arrow1"));
          arrow->setVisible(true);
          textLabel_->setString(texts_[state_++]);
          break;
        }
        case(7) : {
          auto arrow = dynamic_cast<cocos2d::Sprite*>
            (rootNode->getChildByName("arrow2"));
          arrow->setVisible(true);
          textLabel_->setString(texts_[state_++]);
          button_->setTitleText("Entendido");
          break;
        }
        case(8) : {
          auto scene = StageOneScene::createScene();
          cocos2d::Director::getInstance()->replaceScene(scene);
          break;
        }
        default:{
          textLabel_->setString(texts_[state_++]);
          break;
        }
      }
    }
  });

  addChild(rootNode);

  return true;
}

