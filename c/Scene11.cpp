#include "Scene11.h"
#include "Scene12.h"
#include "Scene10.h"
#include "Scene08.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"
int textNum = 1;
bool doorsOpen = false;
Scene* Scene11::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene11 class that inherits from Layer class
	auto layer = Scene11::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene11::init() {
    doorsOpen = false;
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
    
    auto bkgd = Sprite::create(ORDOORSBKGD);
    
    bkgd->setPosition(center);
    bkgd->setScale(1.1*visibleSize.width / bkgd->getContentSize().width, 1.1*visibleSize.height / bkgd->getContentSize().height);
    this->addChild(bkgd, 1);
    
    auto doors = MenuItemImage::create(
                                           S11DOORS,
                                           S11DOORS,
                                           CC_CALLBACK_1(Scene11::openDoors, this)
                                           );
    doors->setPosition(Vec2(0.5*visibleSize.width, 0.5*visibleSize.height));
    doors->setScale(0.43*visibleSize.width / doors->getContentSize().width,
                    0.54*visibleSize.height / doors->getContentSize().width);
    
    this->doorhandle = Sprite::create(S11DOORHANDLES);
    doorhandle->setPosition(Vec2(0.475*visibleSize.width, 0.49*visibleSize.height));
    doorhandle->setScale(0.245*visibleSize.width / doors->getContentSize().width,
                    0.28*visibleSize.height / doors->getContentSize().width);
    this->addChild(doorhandle, 2);
    
    this->doorhandle2 = Sprite::create(S11DOORHANDLES);
    doorhandle2->setPosition(Vec2(0.525*visibleSize.width, 0.49*visibleSize.height));
    doorhandle2->setScale(0.245*visibleSize.width / doors->getContentSize().width,
                    0.28*visibleSize.height / doors->getContentSize().width);
    this->addChild(doorhandle2, 2);
    
    this->glow = Sprite::create(GLOW);
    glow->setPosition(Vec2(0.5*visibleSize.width, 0.5*visibleSize.height));
    glow->setScale(0.25 * (visibleSize.width / glow->getContentSize().width),
                    0.25 * (visibleSize.width / glow->getContentSize().width));
    glow->setAnchorPoint(Vec2(0.5, 0.5));
    glow->setOpacity(0);
    glow->setTag(99);
    glowon = true;
    this->addChild(glow, 1);
    
    auto doormenu = Menu::create(doors, NULL);
    doormenu->setPosition(origin.x, origin.y);
    this->addChild(doormenu, -1);
    
	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
	FrameNav frameNav;
	frameNav.addFrameNav(this);
    frameNav.bkgdMusic(2);
    
    UserDefault* def = UserDefault::getInstance();
    
    // Scripts
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "Scene11");

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene11::gotoNextScene, this)
	);
    
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
    
    auto Scene11Done = def->getBoolForKey("Scene11Done");
     if (Scene11Done){
         nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                 visibleSize.height* SCALEY1 + origin.y));
     }
     else{
         nextScene->setPosition(Vec2(-1*visibleSize.width * SCALEX2 + origin.x,
                                     -1*visibleSize.height* SCALEY1 + origin.y));
     }
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(Scene11::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);
    
    auto nextPage = MenuItemImage::create(
        PAGEFWD,
        PAGEFWD,
        CC_CALLBACK_1(Scene11::nextText, this)
    );
    nextPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.845 + origin.x,
                                visibleSize.height* SCALEY1 * 2.49 + origin.y));

    nextPage->setScale(0.15*w / nextPage->getContentSize().width,
                       0.2*h / nextPage->getContentSize().height);
    
    auto prevPage = MenuItemImage::create(
        PAGEBWD,
        PAGEBWD,
        CC_CALLBACK_1(Scene11::prevText, this)
    );
    prevPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x,
                                visibleSize.height* SCALEY1 * 2.49 + origin.y));

    prevPage->setScale(0.15*w / nextPage->getContentSize().width,
                        0.2*h / nextPage->getContentSize().height);

	// Create the menu
	menu = Menu::create(nextScene, prevScene, nextPage, prevPage, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there

    this->textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                           0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                   0.2*visibleSize.height / textBox->getContentSize().height);

    auto textString1 = Json_getString(script, "11.1", "Go Gators!");
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.56);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.45*textBox->getContentSize().height));
    boxText->setColor(cocos2d::Color3B::BLACK);
    boxText->setAlignment(TextHAlignment::CENTER);
    
    textBox->addChild(boxText, 1);
    
    this->addChild(textBox, FRAMEDRAW + 5);
    textNum = 1;
	return true;
}

void Scene11::openDoors(Ref* pSender) {
    if(doorsOpen != true)
    {
    doorsOpen = true;
    textNum = 3;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->textBox->removeAllChildren();
    auto textString2 = Json_getString(script, "11.3", "Go Gators!");
    
    auto boxText1 = Label::createWithTTF(textString2, BOLD, visibleSize.height * TEXTSIZE*0.56);
    boxText1->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.35*textBox->getContentSize().height));
    boxText1->setColor(cocos2d::Color3B::BLACK);
    boxText1->setAlignment(TextHAlignment::CENTER);
    
    this->textBox->addChild(boxText1, 1);
    auto ppl = Sprite::create(S11PPL);
        
    // hide the doors
    doorhandle->setOpacity(0);
    doorhandle2->setOpacity(0);
    glow->setOpacity(0);
    removeChildByTag(99);
    glowon = false;
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    ppl->setPosition(Vec2(0.5*visibleSize.width + origin.x, 0.5*visibleSize.height + origin.y));
    ppl->setScale(0.43*visibleSize.width / ppl->getContentSize().width,
                    0.54*visibleSize.height / ppl->getContentSize().width);
    ppl->setOpacity(0);
    this->addChild(ppl, 0);
    
    ppl->runAction(Sequence::create(DelayTime::create(0.1),
                                      FadeIn::create(0.4),
                                      nullptr));
    auto nextPage = this->menu->getChildren().at(2);
    nextPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.845 + origin.x,
                                visibleSize.height* SCALEY1 * 2.49 + origin.y));
    auto prevPage = this->menu->getChildren().at(3);
    prevPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
}
}

// Callback function to move on to the next scene
void Scene11::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene10::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move on to the previous scene
void Scene11::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene08::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void Scene11::waitNextScene(float dt) {
    auto nextScene = Scene10::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2, nextScene));
}

void Scene11::nextText(Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto center = Vec2(0.5*visibleSize.width + origin.x,
                       0.5*visibleSize.height + origin.y);
    auto w = visibleSize.width;
    auto h = visibleSize.height;
    log("testing1");

    
    this->textBox->removeAllChildren();
    if ((textNum <= 3 && doorsOpen == true) || textNum == 1)
    {
        textNum = textNum + 1;
    }
    auto textString1 = Json_getString(script, "11.1", "Go Gators!");
    if (textNum == 1)
    {
        textString1 = Json_getString(script, "11.1", "Go Gators!");
    }
    if (textNum == 2)
    {
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        auto prevPage = this->menu->getChildren().at(3);
        prevPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
        textString1 = Json_getString(script, "11.2", "Go Gators!");
        if(doorsOpen == false)
        {
            Vec2 origin = Director::getInstance()->getVisibleOrigin();
            auto prevPage = this->menu->getChildren().at(3);
            prevPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
            auto nextPage = this->menu->getChildren().at(2);
            nextPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
        }
    }
    if (textNum == 3)
    {
        textString1 = Json_getString(script, "11.3", "Go Gators!");
    }
    if (textNum == 4)
    {
        textString1 = Json_getString(script, "11.4", "Go Gators!");
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        auto prevPage = this->menu->getChildren().at(3);
        prevPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
        auto nextPage = this->menu->getChildren().at(2);
        nextPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
        this->scheduleOnce(schedule_selector(Scene11::nextButtonAppears), 0.1);
    }
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.56);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    if (textNum == 1)
    {
        boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.45*textBox->getContentSize().height));
    }
    else
    {
        boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.35*textBox->getContentSize().height));
    }
    boxText->setColor(cocos2d::Color3B::BLACK);
    boxText->setAlignment(TextHAlignment::CENTER);
    
    this->textBox->addChild(boxText, 1);
    
    if (glowon)
    {
        this->glow->runAction(RepeatForever::create(RotateBy::create(2, 360.0f)));
        this->glow->setOpacity(255);
    }
}

void Scene11::nextButtonAppears(float dt){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto w = visibleSize.width;
    auto h = visibleSize.height;
    
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto nextButton = Sprite::create(MOVEFWD);
    
    nextButton->setScale(0.09*w / nextButton->getContentSize().width,
    0.1*h / nextButton->getContentSize().height);
    nextButton->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
    visibleSize.height* SCALEY1 + origin.y));
    this->addChild(nextButton, FRAMEDRAW+5);
    //FRAMEDRAW
    
    auto meetListener = EventListenerTouchOneByOne::create();
    meetListener->setSwallowTouches(true);
    meetListener->onTouchBegan = [=](Touch *touch, Event *event) -> bool {
        auto meetBox = nextButton->getBoundingBox();
        //auto takeCloserLookBox = event->getCurrentTarget()->getBoundingBox();
        if (meetBox.containsPoint(touch->getLocation())) {
            
            UserDefault* def = UserDefault::getInstance();
        
            def->setBoolForKey("Scene11Done", true);
            
            // Get size of the window being displayed to
            log("testing");
            auto meetBox = nextButton->getBoundingBox();
            //auto takeCloserLookBox = event->getCurrentTarget()->getBoundingBox();
            if (meetBox.containsPoint(touch->getLocation())) {
                log("testing");
                UserDefault* def = UserDefault::getInstance();
                def->setBoolForKey("Scene11Done", true);
                CCDirector::sharedDirector()->pushScene(TransitionFade::create(0.5, Scene10::createScene()));
            }
            _eventDispatcher->removeEventListener(meetListener);
            nextButton->runAction(RemoveSelf::create());
            
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(meetListener, this);
}

void Scene11::prevText(Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->textBox->removeAllChildren();
    if (textNum >= 2)
    {
        textNum = textNum - 1;
    }
    auto textString2 = Json_getString(script, "11.1", "Go Gators!");
    if (textNum == 1)
    {
        textString2 = Json_getString(script, "11.1", "Go Gators!");
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        auto nextPage = this->menu->getChildren().at(2);
        nextPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.845 + origin.x,
                                    visibleSize.height* SCALEY1 * 2.49 + origin.y));
        auto prevPage = this->menu->getChildren().at(3);
        prevPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
    }
    if (textNum == 2)
    {
        textString2 = Json_getString(script, "11.2", "Go Gators!");
    }
    if (textNum == 3)
    {
        textString2 = Json_getString(script, "11.3", "Go Gators!");
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        auto nextPage = this->menu->getChildren().at(2);
        nextPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.845 + origin.x,
                                    visibleSize.height* SCALEY1 * 2.49 + origin.y));
    }
    if (textNum == 4)
    {
        textString2 = Json_getString(script, "11.4", "Go Gators!");
    }
    
    auto boxText1 = Label::createWithTTF(textString2, BOLD, visibleSize.height * TEXTSIZE*0.56);
    boxText1->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    if (textNum == 1)
    {
        boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.45*textBox->getContentSize().height));
    }
    else
    {
        boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.35*textBox->getContentSize().height));
    }
    
    boxText1->setColor(cocos2d::Color3B::BLACK);
    boxText1->setAlignment(TextHAlignment::CENTER);
    
    this->textBox->addChild(boxText1, 1);
}
