#include "Scene10.h"
#include "Scene11.h"
#include "Scene09.h"
#include "Scene12.h"
#include "FrameNav.h"

Scene* Scene10::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene10 class that inherits from Layer class
	auto layer = Scene10::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene10::init() {

	// Ensure layer from createScene() was created
	if (!Layer::init()) {
		return false;
	}

	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto center = Vec2(0.5*visibleSize.width + origin.x,
                       0.5*visibleSize.height + origin.y);
    auto w = visibleSize.width;
    auto h = visibleSize.height;

	auto bkgd = Sprite::create(ORBKGD);
	bkgd->setPosition(center);
	bkgd->setScale(w / bkgd->getContentSize().width,
                   h / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);


	auto sleepmach = Sprite::create(SleepMach);
	sleepmach->setPosition(0.3*w + origin.x,
                           0.55*h + origin.y);
	sleepmach->setScale(0.6*visibleSize.height / sleepmach->getContentSize().height,
                        0.6*visibleSize.height / sleepmach->getContentSize().height
                        );
	this->addChild(sleepmach, 1);

	auto nurse = Sprite::create(Nurse);
	
    nurse->setPosition(0.7*w + origin.x,
                       0.5*h + origin.y);
    nurse->setScale(0.65*h/nurse->getContentSize().height,
                    0.65*h/nurse->getContentSize().height);
	this->addChild(nurse, 2);

	auto anes = Sprite::create(Anes);
    anes->setPosition(0.1*w + origin.x,
                      0.4*h + origin.y);
    anes->setScale(0.7*h/anes->getContentSize().height,
                   0.7*h/anes->getContentSize().height);
	this->addChild(anes, 2);

	auto bed = Sprite::create(Bed);
    bed->setPosition(0.7*w + origin.x,
                     0.4*h + origin.y);
    bed->setScale(0.8*h/bed->getContentSize().height,
                  0.8*h/bed->getContentSize().height);
	this->addChild(bed, 3);
    
    auto light = Sprite::create(LightOff);
    light->setPosition(0.85*w + origin.x,
                       0.8*h + origin.y);
    light->setScale(0.2*h/light->getContentSize().height,
                    0.2*h/light->getContentSize().height);
    this->addChild(light, 4);
    
    this->on = false;
    
    auto lightlistener = EventListenerTouchOneByOne::create();
    lightlistener->setSwallowTouches(true);
    lightlistener->onTouchBegan = [=](Touch *touch, Event *event) -> bool {
        auto pos = touch->getLocation();
        auto x = (pos.x-origin.x)/w;
        auto y = (pos.y-origin.y)/h;
        
        if ((std::abs(x-0.85)<0.1) && (std::abs(y-0.8)<0.1)) {
            
            UserDefault* def = UserDefault::getInstance();
            def->setBoolForKey("Scene10Done", true);
            
            if (!this->on){
                light->setTexture(LightOn);
                light->runAction(Sequence::create(MoveBy::create(0.08, Vec2(0, 0.01*h)),
                                                  MoveBy::create(0.08, Vec2(0, -0.01*h)),
                                                  nullptr));
                this->on = true;
                
            } else {
                light->setTexture(LightOff);
                light->runAction(Sequence::create(MoveBy::create(0.08, Vec2(0, 0.01*h)),
                                                  MoveBy::create(0.08, Vec2(0, -0.01*h)),
                                                  nullptr));
                this->on = false;
            }
        }
        return false;
    };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lightlistener, this);

	FrameNav frameNav;
	frameNav.addFrameNav(this);
    frameNav.bkgdMusic(3);
    
    UserDefault* def = UserDefault::getInstance();
    
    // Scripts
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "Scene10");

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene10::gotoNextScene, this)
	);
    def->setBoolForKey("IsDebug", true);
    auto isDebug = def->getBoolForKey("IsDebug", false);
    
    if (!isDebug) {
        nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                    visibleSize.height* SCALEY1 + origin.y));
    }
    else
    {
        nextScene->setPosition(Vec2(-1*visibleSize.width * SCALEX2 + origin.x,
                                    -1*visibleSize.height* SCALEY1 + origin.y));
    }
    auto Scene10Done = def->getBoolForKey("Scene10Done");
    if (Scene10Done){
        nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    }
    else{
        nextScene->setPosition(Vec2(-1*visibleSize.width * SCALEX2 + origin.x,
                                    -1*visibleSize.height* SCALEY1 + origin.y));
    }
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(Scene10::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);

	// Create the menu
	auto menu = Menu::create(nextScene, prevScene, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there

    this->scheduleOnce(schedule_selector(Scene10::gameButtonCallBack), 2);
    this->textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                           0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                   0.2*visibleSize.height / textBox->getContentSize().height);

    auto textString1 = Json_getString(script, "10.1", "Go Gators!");
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.56);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.45*textBox->getContentSize().height));
    boxText->setColor(cocos2d::Color3B::BLACK);
    boxText->setAlignment(TextHAlignment::CENTER);
    
    textBox->addChild(boxText, 1);
    
    this->addChild(textBox, FRAMEDRAW + 5);
    
    
	return true;
}

void Scene10::gameButtonCallBack(float dt){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    UserDefault* def = UserDefault::getInstance();
    def->setBoolForKey("Scene10Done", true);
    auto clipboard = MenuItemImage::create(
                                           takeACloserLook,
                                           takeACloserLook,
                                           CC_CALLBACK_1(Scene10::gotoGameCallback, this));
    clipboard->setScale(0.3*visibleSize.width / clipboard->getContentSize().width,
                        clipboard->getScaleX());
    clipboard->setPosition(Vec2(0.35*visibleSize.width,
                                0.43*visibleSize.height));
    auto looklabel = Label::createWithTTF("Take a closer look!", BLACK, visibleSize.height * TEXTSIZE*0.9);
    auto lookText = MenuItemLabel::create(looklabel, CC_CALLBACK_1(Scene10::gotoGameCallback, this));
    lookText->setPosition(Vec2(0.35*visibleSize.width,
                               0.43*visibleSize.height));
    
    auto braceletMenu = Menu::create(clipboard, lookText, NULL);
    braceletMenu->setOpacityModifyRGB(0);
    braceletMenu->setPosition(origin.x, origin.y);
    
    this->addChild(braceletMenu, FRAMEDRAW + 2);
    
    braceletMenu->runAction(Spawn::create(FadeIn::create(0.2),
                                          ScaleBy::create(0.2, 1.1),
                                          EaseBounceOut::create(MoveBy::create(0.6,Vec2(0,-0.05*visibleSize.height))), nullptr));
    
};

// Callback function to move on to the next scene
void Scene10::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene12::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move on to the previous scene
void Scene10::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene11::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move to the puzzle game scene
void Scene10::gotoGameCallback(Ref* pSender) {
    auto nextScene = Scene12::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
};

