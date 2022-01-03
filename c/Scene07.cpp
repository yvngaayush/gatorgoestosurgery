#include "Scene07.h"
#include "Scene08.h"
#include "Scene06.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"
int hasJumped = 0;

Scene* Scene07::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene07 class that inherits from Layer class
	auto layer = Scene07::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene07::init() {
    hasJumped = 0;
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
	
    UserDefault* def = UserDefault::getInstance();
    def->setBoolForKey("GOWNCLICKED", false);
    def->flush();
    
    //Set the debug state here
    def->setBoolForKey("CLOSERLOOK", false);
    def->flush();
    
	auto bkgd = Sprite::create(SCALEBKGD);
	bkgd->setAnchorPoint(Vec2(0, 0));
	bkgd->setPosition(Vec2(origin.x, origin.y));
	bkgd->setScale(visibleSize.width / bkgd->getContentSize().width, visibleSize.height / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);

	// Create Scene Sprites----------------------------------------------------------------------------------------------------------

	this->gator = Sprite::create(Gator);
	
	gator->setPosition(Vec2(origin.x + visibleSize.width * 0.27,
                            origin.y + visibleSize.height * 0.39));
	gator->setScale(0.85 * visibleSize.width / bkgd->getContentSize().width,
                    0.85 * visibleSize.height / bkgd->getContentSize().height);
	this->addChild(gator);
    
    auto gown = Sprite::create(Gown);
    
    gown->setPosition(Vec2(origin.x + visibleSize.width * 0.87,
                           origin.y + visibleSize.height * 0.4));
    gown->setScale(0.8 * visibleSize.width / bkgd->getContentSize().width,
                   0.8 * visibleSize.height / bkgd->getContentSize().height);
    this->addChild(gown);
    
    auto grow = ScaleBy::create(0.6, 1.25);
    auto normal = ScaleBy::create(1.5, 1);
    auto shrink = ScaleBy::create(0.6, 0.8);
    
    auto action = Sequence::create(normal,grow,shrink, nullptr);
    gown->runAction(RepeatForever::create(action));
    
    auto gownlistener = EventListenerTouchOneByOne::create();
    gownlistener->setSwallowTouches(true);
    gownlistener->onTouchBegan = [=](Touch *touch, Event *event) -> bool {
        auto gownBox = gown->getBoundingBox();
        //auto elevatorBox = event->getCurrentTarget()->getBoundingBox();
        if (gownBox.containsPoint(touch->getLocation())) {
            
            auto iSpy = def->getBoolForKey("ISPYSMOCKFOUND", false);
            this->scheduleOnce(schedule_selector(Scene07::textAppears), 0.2);
            def->setBoolForKey("GOWNCLICKED", true);
            def->flush();
            gown->stopAllActions();
            if (!iSpy) {
                def->setBoolForKey("ISPYSMOCKFOUND", true);
                def->flush();
                Scene07::ispyCallBack();
                return false;
            } else {
                gown->runAction(ScaleBy::create(0.2, 1.1, 1.1));
                return true;
            }
        }
        return false;
    };
    
    gownlistener->onTouchMoved = [=](Touch *touch, Event *event) -> bool {
        
        auto pos = touch->getLocation();
        gown->setPosition(pos);
        return true;
    };
    
    gownlistener->onTouchEnded = [=](Touch *touch, Event *event) -> void {
        auto gatorBox = this->gator->getBoundingBox();
        
        if (gatorBox.containsPoint(touch->getLocation())) {
            UserDefault* def = UserDefault::getInstance();
            def->setBoolForKey("Scene7Done", true);
            
            auto grow = ScaleBy::create(0.5, 1.1);
            auto normal = ScaleBy::create(3, 1);
            auto shrink = ScaleBy::create(0.5, 1/1.1);
            
            auto action = Sequence::create(normal,grow,shrink, nullptr);
            gator->runAction(RepeatForever::create(action));
            gown->runAction(Sequence::create(FadeOut::create(0.2), RemoveSelf::create(), nullptr));
            _eventDispatcher->removeEventListener(gownlistener);
            gator->setTexture(DressedGator);
            gator->setScale(0.87 * visibleSize.width / bkgd->getContentSize().width, 0.88 * visibleSize.height / bkgd->getContentSize().height);
            gator->runAction(EaseBounceOut::create(MoveBy::create(0.8, Vec2(0, 0.03*visibleSize.height))));
            
            this->textBox->removeAllChildren();
            auto textString2 = Json_getString(script, "7.3", "Go Gators!");
            
            auto boxText1 = Label::createWithTTF(textString2, BOLD, visibleSize.height * TEXTSIZE*0.62);
            boxText1->setDimensions(0.9*textBox->getContentSize().width,
                                       0.85*textBox->getContentSize().height);
            boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                          0.5*textBox->getContentSize().height));
            boxText1->setColor(cocos2d::Color3B::BLACK);
            boxText1->setAlignment(TextHAlignment::CENTER);
            
            this->textBox->addChild(boxText1, 1);
            
            this->scheduleOnce(schedule_selector(Scene07::createGatorListener), 0.5);
        } else {

            gown->runAction(Spawn::create(ScaleTo::create(1.0, 0.8 * visibleSize.width / bkgd->getContentSize().width, 0.8 * visibleSize.height / bkgd->getContentSize().height),
                                          RotateBy::create(1.0, -360),
                                          MoveTo::create(1.0, Vec2(origin.x + visibleSize.width * 0.87, origin.y + visibleSize.height * 0.4)),
                                          nullptr));
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(gownlistener, this);

	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
    FrameNav temp;
    temp.addFrameNav(this);
    this->frameNav = &temp;
    this->frameNav->bkgdMusic(2);
    
    // Scripts
    
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "Scene07");

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene07::gotoNextScene, this)
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
    
    auto Scene7Done = def->getBoolForKey("Scene7Done");
     if (Scene7Done){
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
		CC_CALLBACK_1(Scene07::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);

	// Create the menu
	auto menu = Menu::create(nextScene, prevScene, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there

    this->textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                           0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                   0.2*visibleSize.height / textBox->getContentSize().height);

    auto textString1 = Json_getString(script, "7.1", "Go Gators!");
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.62);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.5*textBox->getContentSize().height));
    boxText->setColor(cocos2d::Color3B::BLACK);
    boxText->setAlignment(TextHAlignment::CENTER);
    
    textBox->addChild(boxText, 1);
    
    this->addChild(textBox, FRAMEDRAW + 5);
    this->scheduleOnce(schedule_selector(Scene07::textAppears), 0.5);
    
	return true;
}

void Scene07::createGatorListener(float dt) {
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto gatorlistener = EventListenerTouchOneByOne::create();
    gatorlistener->setSwallowTouches(true);
    
    gatorlistener->onTouchBegan = [=](Touch *touch, Event *event) -> bool {
        
        auto gatorBox = this->gator->getBoundingBox();
        
        if (gatorBox.containsPoint(touch->getLocation())) {
            return true;
        }
        return false;
    };
    
    gatorlistener->onTouchEnded = [=](Touch *touch, Event *event) -> void {
        auto w = visibleSize.width;
        auto h = visibleSize.height;
//        auto nextScene2 = Sprite::create(MOVEFWD);
//
//        //auto elevatorBox = event->getCurrentTarget()->getBoundingBox();
//        printf("here1");
//
//        auto w = visibleSize.width;
//        auto h = visibleSize.height;
//
        if(hasJumped == 0)
        {
            this->gator->stopAllActions();
        auto jumpUp = EaseIn::create(MoveTo::create(0.7, Vec2(0.40*visibleSize.width + origin.x, 0.65*visibleSize.height + origin.y)), 0.7);
        auto land = EaseOut::create(MoveTo::create(0.7, Vec2(0.46*visibleSize.width + origin.x, 0.5*visibleSize.height + origin.y)), 0.7);
        this->gator->runAction(Spawn::create(RotateBy::create(1.4, 360),
                                             Sequence::create(jumpUp, land, nullptr),
                                             nullptr));
            
            auto visibleSize = Director::getInstance()->getVisibleSize();
            this->textBox->removeAllChildren();
            auto textString2 = Json_getString(script, "7.4", "Go Gators!");
            
            UserDefault* def = UserDefault::getInstance();
            def->setBoolForKey("Scene7Done", true);
            
            auto boxText1 = Label::createWithTTF(textString2, BOLD, visibleSize.height * TEXTSIZE*0.7);
            boxText1->setDimensions(0.9*textBox->getContentSize().width,
                                       0.75*textBox->getContentSize().height);
            boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                          0.5*textBox->getContentSize().height));
            boxText1->setColor(cocos2d::Color3B::BLACK);
            boxText1->setAlignment(TextHAlignment::CENTER);
            
            this->textBox->addChild(boxText1, 1);
            
        hasJumped = 1;
            this->scheduleOnce(schedule_selector(Scene07::nextButtonAppears), 0.1);
        }

    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(gatorlistener, this);
}

void Scene07::waitNextScene(float dt) {
    auto nextScene = Scene08::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move on to the next scene
void Scene07::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene08::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

//void Scene07::gotoNextScene2()
//    auto nextScene = Scene08::createScene();
//    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
//}

// Callback function to move on to the previous scene
void Scene07::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene06::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void Scene07::ispyCallBack(){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto textBox2 = Sprite::create(TEXTBOX);
    
    textBox2->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                               0.15*visibleSize.height + origin.y));
    textBox2->setScale(0.6*visibleSize.width / textBox2->getContentSize().width,
                       0.2*visibleSize.height / textBox2->getContentSize().height);
    textBox2->setOpacityModifyRGB(0);
    textBox2->runAction(FadeIn::create(0.2));
    this->addChild(textBox2, (FRAMEDRAW + 2));
    
    
    
    auto star = Sprite::create(STARSHINE);
    star->setPosition(Vec2(origin.x + (0.87 * visibleSize.width),
                           origin.y + (0.4 * visibleSize.height)));
    star->setScale(0.1 * (visibleSize.width / star->getContentSize().width),
                   0.1 * (visibleSize.width / star->getContentSize().width));
    this->addChild(star, FRAMEDRAW + 2);
    
    star->runAction(Sequence::create(Spawn::create(FadeIn::create(0.6),
                                                   RotateBy::create(0.8, 360),
                                                   MoveBy::create(0.8, Vec2(0.05*visibleSize.height,
                                                                            0.05*visibleSize.height)),
                                                   nullptr),
                                     Spawn::create(RotateBy::create(0.6, 360),
                                                   EaseBounceOut::create(MoveBy::create(0.6, Vec2(0.05*visibleSize.width, -0.05*visibleSize.height))), nullptr),
                                     EaseElasticIn::create(MoveBy::create(1.4, Vec2(-0.05*visibleSize.height,0.2*visibleSize.height))),
                                     RemoveSelf::create(),
                                     nullptr));
    this->scheduleOnce(schedule_selector(Scene07::toggleIcon), 3);
    
};

void Scene07::textAppears(float dt)
{
    UserDefault * def = UserDefault::getInstance();
    auto gownFound = def->getBoolForKey("GOWNCLICKED", false);
    
    FrameNav fn;
    auto appear = FadeIn::create(0.2);
    auto disappear = FadeOut::create(0.2);
    auto delay = DelayTime::create(6);
    
    if (!gownFound) {
    
        
    } else {
        UserDefault* def = UserDefault::getInstance();
        def->setBoolForKey("Scene7Done", true);
    
        auto visibleSize = Director::getInstance()->getVisibleSize();
        this->textBox->removeAllChildren();
        auto textString2 = Json_getString(script, "7.2", "Go Gators!");
        
        auto boxText1 = Label::createWithTTF(textString2, BOLD, visibleSize.height * TEXTSIZE*0.64);
        boxText1->setDimensions(0.9*textBox->getContentSize().width,
                                   0.75*textBox->getContentSize().height);
        boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.45*textBox->getContentSize().height));
        boxText1->setColor(cocos2d::Color3B::BLACK);
        boxText1->setAlignment(TextHAlignment::CENTER);
        
        this->textBox->addChild(boxText1, 1);
        
    }
}

void Scene07::toggleIcon(float dt) {
    // If used to create an icon bar
    this->frameNav->createIconBar(this);
    
}

void Scene07::nextButtonAppears(float dt){
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
        
            def->setBoolForKey("Scene7Done", true);
            
            // Get size of the window being displayed to
            log("testing");
            auto meetBox = nextButton->getBoundingBox();
            //auto takeCloserLookBox = event->getCurrentTarget()->getBoundingBox();
            if (meetBox.containsPoint(touch->getLocation())) {
                log("testing");
                UserDefault* def = UserDefault::getInstance();
                def->setBoolForKey("Scene7Done", true);
                CCDirector::sharedDirector()->pushScene(TransitionFade::create(0.5, Scene08::createScene()));
            }
            
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(meetListener, this);
}
