#include "LaunchScreen.h"
#include "MainMenu.h"
#include "Credits0.h"
#include "FrameNav.h"

Scene* Launch::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene01 class that inherits from Layer class
	auto layer = Launch::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Launch::init() {
    UserDefault * def = UserDefault::getInstance();
    
    def->setBoolForKey("ISPYBPFOUND", false);
    def->setBoolForKey("ISPYNAMEFOUND", false);
    def->setBoolForKey("ISPYMASKFOUND", false);
    def->setBoolForKey("ISPYPULSEOXFOUND", false);
    def->setBoolForKey("ISPYELECFOUND", false);
    def->setBoolForKey("ISPYSMOCKFOUND", false);
    def->setBoolForKey("ISPYTHERMOFOUND", false);
    def->setBoolForKey("Scene2Done", false);
    def->setBoolForKey("Scene4Done", false);
    def->setBoolForKey("Scene6Done", false);
    def->setBoolForKey("Scene7Done", false);
    def->setBoolForKey("Scene8Done", false);
    def->setBoolForKey("Scene9Done", false);
    def->setBoolForKey("Scene10Done", false);
    def->setBoolForKey("Scene11Done", false);
    def->setBoolForKey("Scene12Done", false);
    def->setBoolForKey("Scene13Done", false);
    def->setBoolForKey("Scene14Done", false);
    def->setBoolForKey("Scene15Done", false);
    
    def->flush();

	// Ensure layer from createScene() was created
	if (!Layer::init()) {
		return false;
	}

	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    log("----------");
    FrameNav fn;
    fn.bkgdMusic(0);
    

    auto center = Vec2(0.5*visibleSize.width + origin.x,
                       0.5*visibleSize.height + origin.y);
    auto w = visibleSize.width;
    auto h = visibleSize.height;
    
    auto bkgd = MenuItemImage::create(
                                      LAUNCHIMAGE,
                                      LAUNCHIMAGE,
                                      CC_CALLBACK_1(Launch::gotoNextScene, this)
                                      );
    
	bkgd->setScale(w / bkgd->getContentSize().width,
                   h / bkgd->getContentSize().height);
    auto menu = Menu::create(bkgd, NULL);
    menu->setPosition(center);
    this->addChild(menu, -1);

	// Helicopter Sprite
	auto heli = Sprite::create(HELICOPTER);
	
	heli->setPosition(Vec2(-heli->getContentSize().width + origin.x,
                           0.9*h + origin.y));
	heli->setScale(0.15*w / heli->getContentSize().width,
                   0.15*w / heli->getContentSize().width);
	this->addChild(heli, 1);

    auto moveHeli = MoveBy::create(6, Vec2(1.5*w, 0));
    auto up = MoveBy::create(1, Vec2(0, 0.02*h));
    auto down = MoveBy::create(1, Vec2(0, -0.02*h));
    heli->runAction(Spawn::create(Sequence::create(up,down,up,down,up,down,
                                                   nullptr),
                                  moveHeli,
                                  nullptr)
                    );
    
    //Scooter
	auto scooter = Sprite::create(SCOOTER);
	scooter->setPosition(Vec2(origin.x + w + scooter->getContentSize().width,
                              0.24*h + origin.y));
	scooter->setScale(0.2*w / scooter->getContentSize().width,
                      0.2*w / scooter->getContentSize().width);
	this->addChild(scooter, 1);
    
    auto moveScooter = MoveBy::create(2.5, Vec2(-0.7*w, -0.06*h));
    scooter->runAction(Sequence::create(DelayTime::create(1.5),
                                        moveScooter,
                                        nullptr)
                       );

    
	auto welcomeButton = Sprite::create(WELCOMEBUTTON);
    welcomeButton->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                                    0.8*visibleSize.height + origin.y)
                               );
	welcomeButton->setScale(0.5*w / welcomeButton->getContentSize().width,
                            0.4*w / welcomeButton->getContentSize().width);
	this->addChild(welcomeButton, 1);
    
    auto label2 = Label::createWithTTF("WELCOME TO UF SHANDS!", BOLD, visibleSize.height * TEXTSIZE*1.3);
    label2->enableGlow(Color4B(159, 29, 53, 255));
    label2->setColor(cocos2d::Color3B::WHITE);
    label2->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                             0.8*visibleSize.height + origin.y));
    this->addChild(label2, 2);
    
    // grow and shrinking
    auto grow = ScaleBy::create(0.5, 1.1);
    auto normal = ScaleBy::create(0.5, 1);
    auto shrink = ScaleBy::create(0.5, 1/1.1);
    
    auto callbackgrow = CallFunc::create([](){
    });
    
    auto callbacknormal = CallFunc::create([](){
    });
    
    auto callbackshrink = CallFunc::create([](){
    });
    
    auto action = Sequence::create(normal, callbacknormal, grow, callbackgrow, shrink, callbackshrink, nullptr);
	

	auto startButton = Sprite::create(STARTBUTTON);
    startButton->setPosition(Vec2(0.502*visibleSize.width + origin.x,
                                  0.67*visibleSize.height + origin.y));
	startButton->setScale(0.15*w / startButton->getContentSize().width,
                          0.13*w / startButton->getContentSize().width);
    this->addChild(startButton, 1);
    
    startButton->runAction(RepeatForever::create(action));
    
    auto startText = Label::createWithTTF("START", BLACK, visibleSize.height * TEXTSIZE*1.2);
    startText->setPosition(Vec2(0.502*visibleSize.width + origin.x,
                                0.67*visibleSize.height + origin.y)
                           );
//    startText->setScale(0.12*w / startText->getContentSize().width,
//                          0.13*w / startText->getContentSize().width);
    startText->setTextColor(Color4B::YELLOW);
    
    startText->runAction(RepeatForever::create(action->clone()));
	this->addChild(startText, 1);

    //this->scheduleOnce(schedule_selector(Launch::gotoCredits), 9);
    return true;
}

// Callback function to move on to the next scene
void Launch::gotoNextScene(Ref* pSender) {
	auto nextScene = MainMenu::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void Launch::gotoCredits(float dt) {
    auto nextScene = Credits::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
    
}
