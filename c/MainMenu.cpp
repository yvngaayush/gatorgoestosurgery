#include "MainMenu.h"
#include "Scene02.h"
#include "LaunchScreen.h"
#include "Scene15.h"
#include "FrameNav.h"
#include "Credits0.h"

Scene* MainMenu::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene01 class that inherits from Layer class
	auto layer = MainMenu::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool MainMenu::init() {

	// Ensure layer from createScene() was created
	if (!Layer::init()) {
		return false;
	}
    
    // only for debug purposes
    //
    
	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto center = Vec2(0.5*visibleSize.width + origin.x,
                       0.5*visibleSize.height + origin.y);
    auto w = visibleSize.width;
    auto h = visibleSize.height;

	auto bkgd = Sprite::create(MENUBKGD);
	
	bkgd->setPosition(center);
	bkgd->setScale(w / bkgd->getContentSize().width,
				   h / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);

	auto welcomeButton = Sprite::create(WELCOMEBUTTON01);
	welcomeButton->setPosition(Vec2(0.65*w + origin.x,
									0.5*h + origin.y)
                               );
	welcomeButton->setScale(0.5 * w / welcomeButton->getContentSize().width,
							0.5 * w / welcomeButton->getContentSize().width);
	this->addChild(welcomeButton, 1);
    auto welcomeText = Label::createWithTTF("Welcome to UF Shands \n    Children's Hospital!", BLACK, visibleSize.height * TEXTSIZE*1.4);
    welcomeText->setPosition(Vec2(0.65*visibleSize.width + origin.x,
                                0.58*visibleSize.height + origin.y)
                           );
    this->addChild(welcomeText, 1);

	auto exitButton = MenuItemImage::create(
		EXITBUTTONON,
		EXITBUTTONOFF,
		CC_CALLBACK_1(MainMenu::exitCallBack, this)
	);
	exitButton->setPosition(Vec2(w * SCALEX2 + origin.x,
								 h * SCALEY2 + origin.y));
	exitButton->setScale(0.00 * w / exitButton->getContentSize().width,
						 0.00 * h / exitButton->getContentSize().width);

    auto care = MenuItemImage::create(
		CAREGIVERBUTTON01,
		CAREGIVERBUTTON01,
		CC_CALLBACK_1(MainMenu::careButtonCallBack, this)
	);
    care->setPosition(Vec2(origin.x + visibleSize.width * 0.535,
						   origin.y + visibleSize.height * 0.445));
    care->setScale(0.22 * w / care->getContentSize().width,
				   0.22 * w / care->getContentSize().width);
    auto careGiverText = Label::createWithTTF("Caregiver Zone", BLACK, visibleSize.height * TEXTSIZE);
    auto careText = MenuItemLabel::create(careGiverText, CC_CALLBACK_1(MainMenu::careButtonCallBack, this));
    careText->setPosition(Vec2(0.53*visibleSize.width + origin.x,
                              0.45*visibleSize.height + origin.y));
    

	auto game = MenuItemImage::create(
		GAMEBUTTON01,
		GAMEBUTTON01,
		CC_CALLBACK_1(MainMenu::gameButtonCallBack, this)
	);
	game->setPosition(Vec2(origin.x + visibleSize.width * 0.76,
						   origin.y + visibleSize.height * 0.445));
    game->setScale(0.22 * w / game->getContentSize().width,
                   0.22 * w / game->getContentSize().width);
    auto gametextlabel = Label::createWithTTF("I Spy Game", BLACK, visibleSize.height * TEXTSIZE);
    auto gameText = MenuItemLabel::create(gametextlabel, CC_CALLBACK_1(MainMenu::gameButtonCallBack, this));
    gameText->setPosition(Vec2(0.755*visibleSize.width + origin.x,
                                0.45*visibleSize.height + origin.y));

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		STARTBUTTON,
		STARTBUTTON,
		CC_CALLBACK_1(MainMenu::gotoNextScene, this)
	);
    
    // Pulse animation
    
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

	nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
						0.1*h / nextScene->getContentSize().height);

	nextScene->setPosition(Vec2(0.65*visibleSize.width + origin.x,
								0.27*visibleSize.height + origin.y));
    nextScene->setScale(0.15*w / nextScene->getContentSize().width,
                        0.13*w / nextScene->getContentSize().width);
    
    
    nextScene->runAction(RepeatForever::create(action));
    
    //auto startText = Sprite::create(STARTTEXT);
    
    auto startText = Label::createWithTTF("START", BLACK, visibleSize.height * TEXTSIZE*1.2);
    startText->setPosition(Vec2(0.65*visibleSize.width + origin.x,
                                0.27*visibleSize.height + origin.y)
                           );
    
    startText->runAction(RepeatForever::create(action->clone()));
    //this->addChild(startText, 10000);
    this->addChild(startText, (FRAMEDRAW + 2));
    

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(MainMenu::gotoPreviousScene, this)
	);
	prevScene->setPosition(Vec2(-1*visibleSize.width * SCALEX1 + origin.x,
								-1*visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.01*w / prevScene->getContentSize().width,
						0.01*h / prevScene->getContentSize().height);
    
    auto label = Label::createWithTTF("Credits", BOLD, visibleSize.height * TEXTSIZE);
    label->setColor(cocos2d::Color3B::WHITE);
    auto credits = MenuItemLabel::create(label, CC_CALLBACK_1(MainMenu::gotoCredits, this));
    credits->setPosition(Vec2(0.08*w + origin.x,
                              0.96*h + origin.y));
    
    auto creditsButton = MenuItemImage::create(
        STARTBUTTON,
        STARTBUTTON,
        CC_CALLBACK_1(MainMenu::gotoCredits, this)
    );
    creditsButton->setPosition(Vec2(0.08*w + origin.x,
                                    0.96*h + origin.y));
    creditsButton->setScale(0.12*w / creditsButton->getContentSize().width,
                          0.063*h / creditsButton->getContentSize().height);
    
    auto label2 = Label::createWithTTF("Reset Progress", BOLD, visibleSize.height * TEXTSIZE);
    label->setColor(cocos2d::Color3B::WHITE);
    auto reset = MenuItemLabel::create(label2, CC_CALLBACK_1(MainMenu::resetProgress, this));
    reset->setPosition(Vec2(0.8825*w + origin.x,
                              0.96*h + origin.y));
    
    auto resetButton = MenuItemImage::create(
        STARTBUTTON,
        STARTBUTTON,
        CC_CALLBACK_1(MainMenu::resetProgress, this)
    );
    resetButton->setPosition(Vec2(0.835*w + origin.x,
                                    0.96*h + origin.y)
                           );
    resetButton->setScale(0.13*w / resetButton->getContentSize().width,
                          0.063*h / resetButton->getContentSize().height);
    
    auto resetButton2 = MenuItemImage::create(
        STARTBUTTON,
        STARTBUTTON,
        CC_CALLBACK_1(MainMenu::resetProgress, this)
    );
    resetButton2->setPosition(Vec2(0.93*w + origin.x,
                                    0.96*h + origin.y)
                           );
    resetButton2->setScale(0.125*w / resetButton2->getContentSize().width,
                          0.063*h / resetButton2->getContentSize().height);
    
    
    
    

	// Create the menu
	this->menu = Menu::create(exitButton, nextScene, prevScene, care, careText, game, gameText, creditsButton, credits, resetButton, resetButton2, reset, NULL);
	this->menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(this->menu, (FRAMEDRAW + 1)); // Please note that the one must be there
    

    FrameNav fn;
    fn.bkgdMusic(0);
    
    //this->scheduleOnce(schedule_selector(MainMenu::gotoLaunch), 15);
	return true;
}

void MainMenu::careButtonCallBack(Ref* pSender) {

	// Disable menu
	menu->setEnabled(false);

	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto clipboard = Sprite::create(CLIPBOARD);
	clipboard->setPosition(Vec2(origin.x + (visibleSize.width) * 0.5,
								origin.y + (visibleSize.height) * 0.5));
	clipboard->setScale((visibleSize.height / clipboard->getContentSize().height) * 0.95,
						 visibleSize.height / clipboard->getContentSize().height * 0.95);
	clipboard->setOpacityModifyRGB(0);
    
    auto clip = Sprite::create(CLIPGOTIT);
	clip->setPosition(Vec2(clipboard->getContentSize().width * 0.5,
		clipboard->getContentSize().height * 0.07));
    clip->setScale((visibleSize.width / clip->getContentSize().width) * 0.1,
                   (visibleSize.width / clip->getContentSize().width) * 0.1);
    
    auto gotItText = Label::createWithTTF("Got It!", BLACK, visibleSize.height * TEXTSIZE*1.4);
    gotItText->setPosition(Vec2(origin.x + (visibleSize.width) * 0.495,
                                origin.y + (visibleSize.height) * 0.095));
    
    this->addChild(gotItText, (FRAMEDRAW + 200));
    
    clipboard->addChild(clip);
    this->addChild(clipboard, (FRAMEDRAW + 2));
    
	clipboard->runAction(FadeIn::create(0.2));

	auto listen = EventListenerTouchOneByOne::create();

	listen->onTouchBegan = [=](Touch *touch, Event *event)-> bool {
		auto gtBox = event->getCurrentTarget()->getBoundingBox();
		if (clipboard->getNumberOfRunningActions() == 0.0) {
			this->_actionComplete = true;
		}

		if (gtBox.containsPoint(touch->getLocation()) && this->_actionComplete) {
			return true;
		}
		return false;
	};

	listen->onTouchEnded = [=](Touch *touch, Event *event)-> void {
		this->_actionComplete = false;
        clipboard->runAction(RemoveSelf::create());
        gotItText->runAction(RemoveSelf::create());
		menu->setEnabled(true);
	};
	// Add listener
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, clipboard);

};

void MainMenu::gameButtonCallBack(Ref* pSender) {

	// Disable menu
	menu->setEnabled(false);

	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto gameIcon = Sprite::create(ICONGAME);
	gameIcon->setPosition(Vec2(origin.x + (visibleSize.width) * 0.5,
							   origin.y + (visibleSize.height) * 0.5));
	gameIcon->setScale((visibleSize.height / gameIcon->getContentSize().height) * 0.7,
					   (visibleSize.height / gameIcon->getContentSize().height) * 0.7);
	gameIcon->setOpacityModifyRGB(0);
    
    auto gameButton = Sprite::create(GAMEGOTIT);
	gameButton->setPosition(Vec2(gameIcon->getContentSize().width * 0.475,
								 gameIcon->getContentSize().height * 0.2));
    gameButton->setScale((visibleSize.width / gameButton->getContentSize().width) * 0.15,
                       (visibleSize.width / gameButton->getContentSize().width) * 0.15);
	
    gameIcon->addChild(gameButton);
    
    auto gotItTextGame = Label::createWithTTF("Got It!", BLACK, visibleSize.height * TEXTSIZE*1.6);
    gotItTextGame->setPosition(Vec2(origin.x + (visibleSize.width) * 0.473,
                                origin.y + (visibleSize.height) * 0.295));
    
    this->addChild(gotItTextGame, (FRAMEDRAW + 200));
    
	this->addChild(gameIcon, (FRAMEDRAW + 2));
    
    gameIcon->runAction(FadeIn::create(0.2));
    
    auto listen = EventListenerTouchOneByOne::create();
    
    //listen->setSwallowTouches(true);
    listen->onTouchBegan = [gameIcon, this](Touch * touch, Event * event)-> bool {
        auto gtBox = event->getCurrentTarget()->getBoundingBox();
        if (gameIcon->getNumberOfRunningActions() == 0.0) {
            this->_actionComplete = true;
        }
        
        if (gtBox.containsPoint(touch->getLocation()) && this->_actionComplete) {
            return true;
        }
        return false;
    };
    
    listen->onTouchEnded = [gameButton, gameIcon, gotItTextGame, this](Touch * touch, Event * event)-> void {
        this->_actionComplete = false;
        gameIcon->runAction(RemoveSelf::create());
        gotItTextGame->runAction(RemoveSelf::create());
        menu->setEnabled(true);
    };
    // Add listener
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, gameIcon);
};

// Callback function to exit the application
void MainMenu::exitCallBack(Ref* pSender) {
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // pop-up window asks people to tap the screen to exit
    auto text = Label::createWithTTF("Tap anywhere then release to exit.",
                                     BOLD, visibleSize.height*TEXTSIZE);
    text->setPosition(Vec2(visibleSize.width*0.29 + origin.x,
                           visibleSize.height*0.72 + origin.y));
    text->setWidth(0.40*visibleSize.width);
    text->setHeight(visibleSize.height*0.25);
    text->setColor(cocos2d::Color3B::BLACK);
    text->setOpacity(0);
    this->addChild(text, 43);
    
    auto appear = FadeIn::create(0.2);
    text->runAction(Sequence::create(appear, nullptr));
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *event) {
        text->stopAllActions();
        return true;
    };
    
    listener->onTouchMoved = [=](cocos2d::Touch *touch, cocos2d::Event *event) {
        return true;
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event) {
        
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        Director::getInstance()->end();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        exit(0);
#endif
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}

// Callback function to move on to the next scene
void MainMenu::gotoNextScene(Ref* pSender) {
    
    auto nextScene = Scene02::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move on to the previous scene
void MainMenu::gotoPreviousScene(Ref* pSender) {
    auto nextScene = Scene15::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void MainMenu::gotoLaunch(float dt) {
    auto nextScene = Launch::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
    
}

void MainMenu::gotoCredits(Ref* pSender) {
    auto nextScene = Credits::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void MainMenu::resetProgress(Ref* pSender) {
    auto nextScene = MainMenu::createScene();
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
    
    def->flush();
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}
