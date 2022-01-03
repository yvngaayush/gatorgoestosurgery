#include "Scene12.h"
#include "Scene13.h"
#include "Scene11.h"
#include "Scene10.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

Scene* Scene12::createScene() {
	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene12 class that inherits from Layer class
	auto layer = Scene12::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene12::init() {
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

	auto bkgd = Sprite::create(S12BKGD);
	bkgd->setAnchorPoint(Vec2(0, 0));
	bkgd->setPosition(Vec2(origin.x, origin.y));
	bkgd->setScale(visibleSize.width / bkgd->getContentSize().width, visibleSize.height / bkgd->getContentSize().height);
	this->addChild(bkgd);
	
    auto anes = Sprite::create(Anes);
    anes->setPosition(0.2*w + origin.x,
                      0.4*h + origin.y);
    anes->setScale(0.8*h/anes->getContentSize().height,
                   0.8*h/anes->getContentSize().height);
    this->addChild(anes, 3);
    
    auto mask = MenuItemImage::create(
                                       Mask32,
                                       Mask32,
                                       CC_CALLBACK_1(Scene12::maskButtonCallBack, this));
    
    
    
    mask->setPosition(Vec2(origin.x + w * 0.67,
                           origin.y + h * 0.65)
                      );
    mask->setScale(0.1 * h / mask->getContentSize().height,
                   0.1 * h/ mask->getContentSize().height);
    mask->setRotation(60);
    
    this->glow = Sprite::create(GLOW);
    glow->setPosition(Vec2(origin.x + w * 0.705,
                           origin.y + h * 0.60)
                      );
    glow->setScale(0.15 * (visibleSize.width / glow->getContentSize().width),
                    0.15 * (visibleSize.width / glow->getContentSize().width));
    glow->setAnchorPoint(Vec2(0.5, 0.5));
    glow->runAction(RepeatForever::create(RotateBy::create(2, 360.0f)));

    auto maskmenu = Menu::create(mask, NULL);
    
    auto grow = ScaleBy::create(0.6, 1.1);
    auto normal = ScaleBy::create(1.5, 1);
    auto shrink = ScaleBy::create(0.6, 1/1.1);
    
    auto action = Sequence::create(normal,grow,shrink, nullptr);
    glow->runAction(RepeatForever::create(action->clone()));
    
    maskmenu->runAction(RepeatForever::create(action));
    maskmenu->setPosition(Vec2::ANCHOR_MIDDLE);
    this->addChild(maskmenu, 4);
    this->addChild(glow, 3);
    
    auto sleepmach = Sprite::create(MACHINE);
    sleepmach->setPosition(0.65*w + origin.x,
                           0.5*h + origin.y);
    sleepmach->setScale(0.9*visibleSize.height / sleepmach->getContentSize().height,
                        0.9*visibleSize.height / sleepmach->getContentSize().height
                        );
    this->addChild(sleepmach, 2);

  	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
    FrameNav temp;
    temp.addFrameNav(this);
    this->frameNav = &temp;
    this->frameNav->bkgdMusic(3);
    
    UserDefault* def = UserDefault::getInstance();
    
    // Scripts
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "Scene12");

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		DONEBUTTON,
		DONEBUTTON,
		CC_CALLBACK_1(Scene12::gotoNextScene, this)
	);
    
    auto isDebug = def->getBoolForKey("IsDebug", false);
    
    if (!isDebug) {
        nextScene->setPosition(Vec2(0.88*w + origin.x,
                                    0.2*h + origin.y));
    }
    else
    {
        UserDefault* def = UserDefault::getInstance();
        bool tempDone = def->getBoolForKey("Scene10Done", true);
        if(tempDone)
        {
            nextScene->setPosition(Vec2(0.88*w + origin.x,
                                        0.2*h + origin.y));
        }
        else{
        nextScene->setPosition(Vec2(-0.88*w + origin.x,
                                    -0.2*h + origin.y));
        }
    }
    nextScene->setScale(0.15*w / nextScene->getContentSize().width,
                        0.15*w / nextScene->getContentSize().width);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		BACKBUTTON,
		BACKBUTTON,
		CC_CALLBACK_1(Scene12::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(0.12*w + origin.x,
                                0.2*h + origin.y));
    prevScene->setScale(0.15*w / prevScene->getContentSize().width,
                        0.15*w / prevScene->getContentSize().width);

	// Create the menu
	auto menu = Menu::create(nextScene, prevScene, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there
    
    this->textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                           0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                   0.2*visibleSize.height / textBox->getContentSize().height);

    auto textString1 = Json_getString(script, "12.1", "Go Gators!");
    
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

void Scene12::nextButtonAppears(float dt){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto w = visibleSize.width;
    auto h = visibleSize.height;
    
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto nextButton = Sprite::create(DONEBUTTON);
    
    nextButton->setScale(0.15*w / nextButton->getContentSize().width,
    0.15*w / nextButton->getContentSize().width);
    nextButton->setPosition(Vec2(0.88*w + origin.x,
    0.2*h + origin.y));
    this->addChild(nextButton, FRAMEDRAW+5);
    //FRAMEDRAW
    
    auto meetListener = EventListenerTouchOneByOne::create();
    meetListener->setSwallowTouches(true);
    meetListener->onTouchBegan = [=](Touch *touch, Event *event) -> bool {
        auto meetBox = nextButton->getBoundingBox();
        //auto takeCloserLookBox = event->getCurrentTarget()->getBoundingBox();
        if (meetBox.containsPoint(touch->getLocation())) {
            
            UserDefault* def = UserDefault::getInstance();
        
            def->setBoolForKey("Scene12Done", true);
            def->setBoolForKey("Scene10Done", true);
            
            // Get size of the window being displayed to
            log("testing");
            auto meetBox = nextButton->getBoundingBox();
            //auto takeCloserLookBox = event->getCurrentTarget()->getBoundingBox();
            if (meetBox.containsPoint(touch->getLocation())) {
                log("testing");
                UserDefault* def = UserDefault::getInstance();
                def->setBoolForKey("Scene12Done", true);
                def->setBoolForKey("Scene10Done", true);
                CCDirector::sharedDirector()->pushScene(TransitionFade::create(0.5, Scene13::createScene()));
            }
            
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(meetListener, this);
}

void Scene12::maskButtonCallBack(Ref* pSender){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // Create star for found icon once touched
    UserDefault * def = UserDefault::getInstance();
    
    auto iSpyName = def->getBoolForKey("ISPYMASKFOUND", false);
    
    if (!iSpyName) {
        def->setBoolForKey("ISPYMASKFOUND", true);
        def->flush();
        
        // This star shows up for effect once desired icon is clicked
        auto star = Sprite::create(STARSHINE);
        star->setPosition(Vec2(origin.x + (0.65 * visibleSize.width),
                               origin.y + (0.68 * visibleSize.height)));
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
        
        this->scheduleOnce(schedule_selector(Scene12::foundStarCallBack), 3);
    } else {
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        auto textString1 = Json_getString(script, "12.3", "Go Gators!");
        auto textString2 = Json_getString(script, "12.1", "Go Gators!");
        
        auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.75);
        boxText->setDimensions(0.9*textBox->getContentSize().width,
                                   0.85*textBox->getContentSize().height);
        boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.35*textBox->getContentSize().height));
        boxText->setColor(cocos2d::Color3B::BLACK);
        boxText->setAlignment(TextHAlignment::CENTER);
        
        auto boxText2 = Label::createWithTTF(textString2, BOLD, visibleSize.height * TEXTSIZE*0.56);
        boxText2->setDimensions(0.9*textBox->getContentSize().width,
                                   0.85*textBox->getContentSize().height);
        boxText2->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.45*textBox->getContentSize().height));
        boxText2->setColor(cocos2d::Color3B::BLACK);
        boxText2->setAlignment(TextHAlignment::CENTER);
        
        auto textBox2 = Sprite::create(TEXTBOX);
        
        textBox2->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                                   0.15*visibleSize.height + origin.y));
        textBox2->setScale(0.6*visibleSize.width / textBox2->getContentSize().width,
                           0.2*visibleSize.height / textBox2->getContentSize().height);
        textBox2->setOpacityModifyRGB(0);
        textBox2->runAction(FadeIn::create(0.2));
        
        
        boxText->setOpacity(0);
        boxText2->setOpacity(0);
        textBox2->addChild(boxText, FRAMEDRAW+1145);
        textBox2->addChild(boxText2, FRAMEDRAW+1146);
        boxText->runAction(Sequence::create(FadeIn::create(0), DelayTime::create(5), FadeOut::create(0), RemoveSelf::create(), nullptr));
        boxText2->runAction(Sequence::create(DelayTime::create(5), FadeIn::create(0), nullptr));
        this->addChild(textBox2, (FRAMEDRAW + 1144));
    }
};

void Scene12::foundStarCallBack(float dt){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->frameNav->createIconBar(this);
    auto textString1 = Json_getString(script, "12.2", "Go Gators!");
    auto textString2 = Json_getString(script, "12.1", "Go Gators!");
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.75);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.35*textBox->getContentSize().height));
    boxText->setColor(cocos2d::Color3B::BLACK);
    boxText->setAlignment(TextHAlignment::CENTER);
    
    auto boxText2 = Label::createWithTTF(textString2, BOLD, visibleSize.height * TEXTSIZE*0.56);
    boxText2->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText2->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.45*textBox->getContentSize().height));
    boxText2->setColor(cocos2d::Color3B::BLACK);
    boxText2->setAlignment(TextHAlignment::CENTER);
    
    auto textBox2 = Sprite::create(TEXTBOX);
    
    textBox2->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                               0.15*visibleSize.height + origin.y));
    textBox2->setScale(0.6*visibleSize.width / textBox2->getContentSize().width,
                       0.2*visibleSize.height / textBox2->getContentSize().height);
    textBox2->setOpacityModifyRGB(0);
    textBox2->runAction(FadeIn::create(0.2));
    
    
    boxText->setOpacity(0);
    boxText2->setOpacity(0);
    textBox2->addChild(boxText, FRAMEDRAW+1145);
    textBox2->addChild(boxText2, FRAMEDRAW+1146);
    boxText->runAction(Sequence::create(FadeIn::create(0), DelayTime::create(5), FadeOut::create(0), RemoveSelf::create(), nullptr));
    boxText2->runAction(Sequence::create(DelayTime::create(5), FadeIn::create(0), nullptr));
    this->addChild(textBox2, (FRAMEDRAW + 1144));
    this->scheduleOnce(schedule_selector(Scene12::nextButtonAppears), 0.1);
};

void Scene12::waitNextScene(float dt) {
    auto nextScene = Scene13::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(2,nextScene));
}

// Callback function to move on to the next scene
void Scene12::gotoNextScene(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();
    def->setBoolForKey("Scene10Done", true);
	auto nextScene = Scene13::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move on to the previous scene
void Scene12::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene10::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}
