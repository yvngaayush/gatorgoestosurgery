#include "Scene08.h"
#include "Scene09.h"
#include "Scene11.h"
#include "Scene07.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"
bool hasBounced = false;
int textNum08 = 1;

Scene* Scene08::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene08 class that inherits from Layer class
	auto layer = Scene08::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene08::init() {
    textNum08 = 1;
    hasBounced = false;
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
    
	auto bkgd = Sprite::create(ROOMBKGD);
	bkgd->setPosition(center);
	bkgd->setScale(w / bkgd->getContentSize().width,
                   h / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);
	
    FrameNav frameNav;
    frameNav.addFrameNav(this);
    frameNav.bkgdMusic(2);
    
    UserDefault* def = UserDefault::getInstance();
    auto tookalook = def->getBoolForKey("CLOSERLOOK", false);
    
    // Scripts
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "Scene08");
    
    // Menu Item to go to next scene
    auto nextScene = MenuItemImage::create(
                                           MOVEFWD,
                                           MOVEFWD,
                                           CC_CALLBACK_1(Scene08::gotoNextScene, this)
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
    
    auto Scene8Done = def->getBoolForKey("Scene8Done");
     if (Scene8Done){
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
                                           CC_CALLBACK_1(Scene08::gotoPreviousScene, this)
                                           );
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);
    
        auto nextPage = MenuItemImage::create(
            PAGEFWD,
            PAGEFWD,
            CC_CALLBACK_1(Scene08::nextText, this)
        );
        nextPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.845 + origin.x,
                                    visibleSize.height* SCALEY1 * 2.49 + origin.y));

        nextPage->setScale(0.15*w / nextPage->getContentSize().width,
                           0.2*h / nextPage->getContentSize().height);
        
        auto prevPage = MenuItemImage::create(
            PAGEBWD,
            PAGEBWD,
            CC_CALLBACK_1(Scene08::prevText, this)
        );
        prevPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x,
                                    visibleSize.height* SCALEY1 * 2.49 + origin.y));

        prevPage->setScale(0.15*w / nextPage->getContentSize().width,
                            0.2*h / nextPage->getContentSize().height);
        
        if (tookalook != true)
        {
            prevPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 10.22 + origin.x,
                                        visibleSize.height* SCALEY1 * 2.49 + origin.y));
            nextPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 10.845 + origin.x,
                                        visibleSize.height* SCALEY1 * 2.49 + origin.y));
        }
    menu = Menu::create(nextScene, prevScene, nextPage, prevPage, NULL);
    
    // Create the menu
    
    menu->setPosition(Vec2::ANCHOR_MIDDLE);
    this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there
    
    if (!tookalook==true) {
        
        this->textBox = Sprite::create(TEXTBOX);
        
        textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                               0.15*visibleSize.height + origin.y));
        textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                       0.2*visibleSize.height / textBox->getContentSize().height);
        
        this->meetContainer = Sprite::create();
        
        meetContainer->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                               0.37*visibleSize.height + origin.y));
        meetContainer->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                       0.2*visibleSize.height / textBox->getContentSize().height);
        

        auto textString1 = Json_getString(script, "8.1", "Go Gators!");
        
        auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.61);
        boxText->setDimensions(0.9*textBox->getContentSize().width,
                                   0.85*textBox->getContentSize().height);
        boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.4*textBox->getContentSize().height));
        boxText->setColor(cocos2d::Color3B::BLACK);
        boxText->setAlignment(TextHAlignment::CENTER);
        
        
        textBox->addChild(boxText, 1);
        
        this->addChild(textBox, FRAMEDRAW + 5);
        this->addChild(meetContainer, FRAMEDRAW + 6);
        this->scheduleOnce(schedule_selector(Scene08::closerlookAppears), 0);
        
    } else {
        
        auto visibleSize = Director::getInstance()->getVisibleSize();
        this->textBox = Sprite::create(TEXTBOX);
        
        textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                               0.15*visibleSize.height + origin.y));
        textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                       0.2*visibleSize.height / textBox->getContentSize().height);

        this->meetContainer = Sprite::create();
        
        meetContainer->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                               0.37*visibleSize.height + origin.y));
        meetContainer->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                       0.2*visibleSize.height / textBox->getContentSize().height);
        
        
        auto textString1 = Json_getString(script, "8.2", "Go Gators!");
        
        auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.57);
        boxText->setDimensions(0.92*textBox->getContentSize().width,
                                   0.85*textBox->getContentSize().height);
        boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.4*textBox->getContentSize().height));
        boxText->setColor(cocos2d::Color3B::BLACK);
        boxText->setAlignment(TextHAlignment::CENTER);
        
        textBox->addChild(boxText, 1);
        
        this->addChild(textBox, FRAMEDRAW + 5);
        this->addChild(meetContainer, FRAMEDRAW + 6);
        this->scheduleOnce(schedule_selector(Scene08::surgeonAppears), 0);
    
    }
    
	return true;
}

void Scene08::anethesiologistAppears(float dt){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto meetButton = Sprite::create(meetyouranestesiologist);
    
    meetButton->setScaleX((visibleSize.width * 0.3) / meetButton->getContentSize().width);
    meetButton->setScaleY(meetButton->getScaleX());
    meetButton->setPosition(0.5*visibleSize.width + origin.x,
                            0.4*visibleSize.height + origin.y);
    auto meetText = Label::createWithTTF("      Meet Your \nAnesthesiologist!", BLACK, visibleSize.height * TEXTSIZE * 1.1);
    meetText->setPosition(0.4993*visibleSize.width + origin.x,
                          0.415*visibleSize.height + origin.y);
    this->addChild(meetButton, 5);
    this->addChild(meetText, 5);
    
    
    auto meetListener = EventListenerTouchOneByOne::create();
    meetListener->setSwallowTouches(true);
    meetListener->onTouchBegan = [=](Touch *touch, Event *event) -> bool {
        auto meetBox = meetButton->getBoundingBox();
        //auto takeCloserLookBox = event->getCurrentTarget()->getBoundingBox();
        if (textNum08 == 2 && meetBox.containsPoint(touch->getLocation())) {
            
            UserDefault* def = UserDefault::getInstance();
        
            //this->scheduleOnce(schedule_selector(Scene08::nextButtonAppears), 0);
            
            
            // Get size of the window being displayed to
            auto visibleSize = Director::getInstance()->getVisibleSize();
            
            // Get drawing origin of screen for sprites
            Vec2 origin = Director::getInstance()->getVisibleOrigin();
            
            auto clipboard = Sprite::create(HIANES);
            auto clip = Sprite::create(GAMEGOTIT);
            clipboard->addChild(clip);
            
            clipboard->setPosition(Vec2(origin.x + (visibleSize.width) * 0.49,
                                        origin.y + (visibleSize.height) * 0.52));
            clipboard->setScale(0.9*visibleSize.height / clipboard->getContentSize().height,
                                0.9*visibleSize.height / clipboard->getContentSize().height);
            clipboard->setOpacityModifyRGB(0);
            clip->setPosition(Vec2(clipboard->getContentSize().width * 0.5,
                                   clipboard->getContentSize().height * 0.14));
            clip->setScale(0.28*visibleSize.width/clip->getContentSize().width,
                           0.28*visibleSize.width/clip->getContentSize().width);
            
            auto gotItText = Label::createWithTTF("Got It!", BLACK, visibleSize.height * TEXTSIZE*1.4);
            gotItText->setPosition(Vec2(origin.x + (visibleSize.width) * 0.483,
                                        origin.y + (visibleSize.height) * 0.198));
            
            this->addChild(gotItText, (FRAMEDRAW + 12346));
            clipboard->runAction(FadeIn::create(0.2));
            gotItText->runAction(FadeIn::create(0.2));
            
            auto textBox2 = Sprite::create(TEXTBOX);
            
            textBox2->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                                       0.15*visibleSize.height + origin.y));
            textBox2->setScale(0.6*visibleSize.width / textBox2->getContentSize().width,
                               0.2*visibleSize.height / textBox2->getContentSize().height);
            textBox2->setOpacityModifyRGB(0);
            textBox2->runAction(FadeIn::create(0.2));
            
            auto listen = EventListenerTouchOneByOne::create();
            
            //listen->setSwallowTouches(true);
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
                clipboard->runAction(Sequence::create(RemoveSelf::create(),
                                                      nullptr));
                gotItText->runAction(Sequence::create(RemoveSelf::create(),
                                                      nullptr));
                textBox2->runAction(Sequence::create(RemoveSelf::create(),
                                                     nullptr));
                //SCENE CHANGE HERE-----------------------------------------------------------------------------------
//                CCDirector::sharedDirector()->pushScene(TransitionFade::create(4, Scene11::createScene()));
            };
            // Add listener
            Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, clipboard);
            this->addChild(clipboard, (FRAMEDRAW + 20));
            this->addChild(textBox2, (FRAMEDRAW + 19));
            
//            _eventDispatcher->removeEventListener(meetListener);
//            meetButton->runAction(RemoveSelf::create());
            
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(meetListener, this);
}

void Scene08::resAppears(float dt){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto meetButton = Sprite::create(meetyouranestesiologist3);
    
    meetButton->setScaleX((visibleSize.width * 0.3) / meetButton->getContentSize().width);
    meetButton->setScaleY(meetButton->getScaleX());
    meetButton->setPosition(0.5*visibleSize.width + origin.x,
                            0.4*visibleSize.height + origin.y);
    auto meetText = Label::createWithTTF("  Meet Your \n  Residents!", BLACK, visibleSize.height * TEXTSIZE * 1.1);
    meetText->setPosition(0.495*visibleSize.width + origin.x,
                          0.415*visibleSize.height + origin.y);
    this->addChild(meetButton, 5);
    this->addChild(meetText, 5);
    
    
    auto meetListener2 = EventListenerTouchOneByOne::create();
    meetListener2->setSwallowTouches(true);
    meetListener2->onTouchBegan = [=](Touch *touch, Event *event) -> bool {
        auto meetBox = meetButton->getBoundingBox();
        //auto takeCloserLookBox = event->getCurrentTarget()->getBoundingBox();
        if (textNum08 == 3 && meetBox.containsPoint(touch->getLocation())) {
            
            UserDefault* def = UserDefault::getInstance();
        
            //this->scheduleOnce(schedule_selector(Scene08::nextButtonAppears), 0);
            
            
            // Get size of the window being displayed to
            auto visibleSize = Director::getInstance()->getVisibleSize();
            
            // Get drawing origin of screen for sprites
            Vec2 origin = Director::getInstance()->getVisibleOrigin();
            
            auto clipboard = Sprite::create(HIRESIDENTS);
            auto clip = Sprite::create(GAMEGOTIT);
            clipboard->addChild(clip);
            
            clipboard->setPosition(Vec2(origin.x + (visibleSize.width) * 0.49,
                                        origin.y + (visibleSize.height) * 0.52));
            clipboard->setScale(0.9*visibleSize.height / clipboard->getContentSize().height,
                                0.9*visibleSize.height / clipboard->getContentSize().height);
            clipboard->setOpacityModifyRGB(0);
            clip->setPosition(Vec2(clipboard->getContentSize().width * 0.5,
                                   clipboard->getContentSize().height * 0.14));
            clip->setScale(0.28*visibleSize.width/clip->getContentSize().width,
                           0.28*visibleSize.width/clip->getContentSize().width);
            
            auto gotItText = Label::createWithTTF("Got It!", BLACK, visibleSize.height * TEXTSIZE*1.4);
            gotItText->setPosition(Vec2(origin.x + (visibleSize.width) * 0.483,
                                        origin.y + (visibleSize.height) * 0.198));
            
            this->addChild(gotItText, (FRAMEDRAW + 12346));
            clipboard->runAction(FadeIn::create(0.2));
            gotItText->runAction(FadeIn::create(0.2));
            
            auto textBox2 = Sprite::create(TEXTBOX);
            
            textBox2->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                                       0.15*visibleSize.height + origin.y));
            textBox2->setScale(0.6*visibleSize.width / textBox2->getContentSize().width,
                               0.2*visibleSize.height / textBox2->getContentSize().height);
            textBox2->setOpacityModifyRGB(0);
            textBox2->runAction(FadeIn::create(0.2));
            
            auto listen = EventListenerTouchOneByOne::create();
            
            //listen->setSwallowTouches(true);
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
                clipboard->runAction(Sequence::create(RemoveSelf::create(),
                                                      nullptr));
                gotItText->runAction(Sequence::create(RemoveSelf::create(),
                                                      nullptr));
                textBox2->runAction(Sequence::create(RemoveSelf::create(),
                                                     nullptr));
                //SCENE CHANGE HERE-----------------------------------------------------------------------------------
//                CCDirector::sharedDirector()->pushScene(TransitionFade::create(4, Scene11::createScene()));
            };
            // Add listener
            Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, clipboard);
            this->addChild(clipboard, (FRAMEDRAW + 20));
            this->addChild(textBox2, (FRAMEDRAW + 19));
            
//            _eventDispatcher->removeEventListener(meetListener);
//            meetButton->runAction(RemoveSelf::create());
            
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(meetListener2, this);
}

void Scene08::surgeonAppears(float dt){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto meetButton = Sprite::create(meetyouranestesiologist2);
    
    meetButton->setScaleX((visibleSize.width * 0.3) / meetButton->getContentSize().width);
    meetButton->setScaleY(meetButton->getScaleX());
    meetButton->setPosition(0.5*visibleSize.width + origin.x,
                            0.4*visibleSize.height + origin.y);
    auto meetText = Label::createWithTTF("  Meet Your \n   Surgeon!", BLACK, visibleSize.height * TEXTSIZE * 1.1);
    meetText->setPosition(0.495*visibleSize.width + origin.x,
                          0.415*visibleSize.height + origin.y);
    this->addChild(meetButton, 5);
    this->addChild(meetText, 5);
    
    auto meetListener = EventListenerTouchOneByOne::create();
    meetListener->setSwallowTouches(true);
    meetListener->onTouchBegan = [=](Touch *touch, Event *event) -> bool {
        auto meetBox = meetButton->getBoundingBox();
        //auto takeCloserLookBox = event->getCurrentTarget()->getBoundingBox();
        if (textNum08 == 1 && meetBox.containsPoint(touch->getLocation())) {
            
            UserDefault* def = UserDefault::getInstance();
        
            //this->scheduleOnce(schedule_selector(Scene08::nextButtonAppears), 0);
            
            
            // Get size of the window being displayed to
            auto visibleSize = Director::getInstance()->getVisibleSize();
            
            // Get drawing origin of screen for sprites
            Vec2 origin = Director::getInstance()->getVisibleOrigin();
            
            auto clipboard = Sprite::create(HISURGEON);
            auto clip = Sprite::create(GAMEGOTIT);
            clipboard->addChild(clip);
            
            clipboard->setPosition(Vec2(origin.x + (visibleSize.width) * 0.49,
                                        origin.y + (visibleSize.height) * 0.52));
            clipboard->setScale(0.9*visibleSize.height / clipboard->getContentSize().height,
                                0.9*visibleSize.height / clipboard->getContentSize().height);
            clipboard->setOpacityModifyRGB(0);
            clip->setPosition(Vec2(clipboard->getContentSize().width * 0.5,
                                   clipboard->getContentSize().height * 0.14));
            clip->setScale(0.28*visibleSize.width/clip->getContentSize().width,
                           0.28*visibleSize.width/clip->getContentSize().width);
            
            auto gotItText = Label::createWithTTF("Got It!", BLACK, visibleSize.height * TEXTSIZE*1.4);
            gotItText->setPosition(Vec2(origin.x + (visibleSize.width) * 0.483,
                                        origin.y + (visibleSize.height) * 0.198));
            
            this->addChild(gotItText, (FRAMEDRAW + 12346));
            clipboard->runAction(FadeIn::create(0.2));
            gotItText->runAction(FadeIn::create(0.2));
            
            auto textBox2 = Sprite::create(TEXTBOX);
            
            textBox2->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                                       0.15*visibleSize.height + origin.y));
            textBox2->setScale(0.6*visibleSize.width / textBox2->getContentSize().width,
                               0.2*visibleSize.height / textBox2->getContentSize().height);
            textBox2->setOpacityModifyRGB(0);
            textBox2->runAction(FadeIn::create(0.2));
            
            auto listen = EventListenerTouchOneByOne::create();
            
            //listen->setSwallowTouches(true);
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
                clipboard->runAction(Sequence::create(RemoveSelf::create(),
                                                      nullptr));
                gotItText->runAction(Sequence::create(RemoveSelf::create(),
                                                      nullptr));
                textBox2->runAction(Sequence::create(RemoveSelf::create(),
                                                     nullptr));
                //SCENE CHANGE HERE-----------------------------------------------------------------------------------
//                CCDirector::sharedDirector()->pushScene(TransitionFade::create(4, Scene11::createScene()));
            };
            // Add listener
            Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, clipboard);
            this->addChild(clipboard, (FRAMEDRAW + 20));
            this->addChild(textBox2, (FRAMEDRAW + 19));
            
//            _eventDispatcher->removeEventListener(meetListener);
//            meetButton->runAction(RemoveSelf::create());
            
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(meetListener, this);
}

void Scene08::nextButtonAppears(float dt){
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
        
            def->setBoolForKey("Scene8Done", true);
            
            // Get size of the window being displayed to
            log("testing");
            auto meetBox = nextButton->getBoundingBox();
            //auto takeCloserLookBox = event->getCurrentTarget()->getBoundingBox();
            if (meetBox.containsPoint(touch->getLocation())) {
                log("testing");
                UserDefault* def = UserDefault::getInstance();
                def->setBoolForKey("Scene8Done", true);
                CCDirector::sharedDirector()->pushScene(TransitionFade::create(0.5, Scene11::createScene()));
            }
            
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(meetListener, this);
}

void Scene08::closerlookAppears(float dt){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto takeCloserLookButton = Sprite::create(takeACloserLook);
    
    takeCloserLookButton->setScaleX((visibleSize.width * 0.3) / takeCloserLookButton->getContentSize().width);
    takeCloserLookButton->setScaleY(takeCloserLookButton->getScaleX());
    takeCloserLookButton->setPosition(0.5*visibleSize.width + origin.x,
                                      0.4*visibleSize.height + origin.y
                                      );
    auto closerlookText = Label::createWithTTF("Take a closer look!", BLACK, visibleSize.height * TEXTSIZE);
    closerlookText->setPosition(0.495*visibleSize.width + origin.x,
                                0.40*visibleSize.height + origin.y
                                );
    auto grow = ScaleBy::create(0.6, (1/0.85));
    auto normal = ScaleBy::create(1.5, 1);
    auto shrink = ScaleBy::create(0.6, 0.85);
    
    auto action = Sequence::create(normal,grow,shrink, nullptr);
    takeCloserLookButton->runAction(RepeatForever::create(action));
    closerlookText->runAction(RepeatForever::create(action->clone()));
    
    this->addChild(takeCloserLookButton,4);
    this->addChild(closerlookText,4);
    
    // Touch Object
    auto takeCloserLookListener = EventListenerTouchOneByOne::create();
    takeCloserLookListener->onTouchBegan = [takeCloserLookButton, this](Touch *touch, Event *event) -> bool {
        auto takeCloserLookBox = takeCloserLookButton->getBoundingBox();
        //auto takeCloserLookBox = event->getCurrentTarget()->getBoundingBox();
        if (takeCloserLookBox.containsPoint(touch->getLocation())) {
            return true;
        }
        return false;
    };
    
    takeCloserLookListener->onTouchEnded = [takeCloserLookButton, this](Touch *touch, Event *event) -> void {
        SpriteFrameCache::getInstance()->removeSpriteFrames();
        
        UserDefault* def = UserDefault::getInstance();
        def->setBoolForKey("CLOSERLOOK", true);
        def->flush();
        
        gotoCloserLook(this);
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(takeCloserLookListener, this);
}

// Callback function to move on to the next scene
void Scene08::gotoCloserLook(Ref* pSender) {
//    UserDefault* def = UserDefault::getInstance();
//    def->setBoolForKey("Scene8Done", true);
	auto nextScene = Scene09::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void Scene08::gotoNextScene(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();
    bool tempLooked = def->getBoolForKey("CLOSERLOOK", false);
    auto nextScene = Scene11::createScene();
    if(tempLooked != true)
    {
        def->setBoolForKey("CLOSERLOOK", true);
        def->flush();
        nextScene = Scene08::createScene();
    }
    else
    {
        nextScene = Scene11::createScene();
    }
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void Scene08::waitNextScene(float dt) {
    auto nextScene = Scene11::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2, nextScene));
}

// Callback function to move on to the previous scene
void Scene08::gotoPreviousScene(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();
    bool tempLooked = def->getBoolForKey("CLOSERLOOK", false);
    auto nextScene = Scene08::createScene();
    if(tempLooked == true)
    {
        def->setBoolForKey("CLOSERLOOK", false);
        def->flush();
        nextScene = Scene08::createScene();
    }
    else
    {
        nextScene = Scene07::createScene();
    }
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void Scene08::callNext()
{
    auto nextScene = Scene11::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void Scene08::anesAppears(float dt)
{
    
    //// get text from json script object
    
    auto textString1 = Json_getString(script, "8.3", "Go Gators!");
    
    //// set up text
    
    // Added a framenav function so all text displays the same
    
    FrameNav fn;
    auto label1 = fn.createText(textString1, this);
    
    auto appear = FadeIn::create(0.2);
    
    label1->runAction(appear);
}

void Scene08::nextText2(Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->textBox->removeAllChildren();
    auto textString1 = Json_getString(script, "8.3", "Go Gators!");
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.52);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.45*textBox->getContentSize().height));
    boxText->setColor(cocos2d::Color3B::BLACK);
    boxText->setAlignment(TextHAlignment::CENTER);
    
    this->textBox->addChild(boxText, 1);
    if(hasBounced == false)
    {
        hasBounced = true;
        this->scheduleOnce(schedule_selector(Scene08::anethesiologistAppears), 0);
    }
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto prevPage = this->menu->getChildren().at(3);
    prevPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
    auto nextPage = this->menu->getChildren().at(2);
    nextPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
}

void Scene08::prevText2(Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->textBox->removeAllChildren();
    auto textString2 = Json_getString(script, "8.2", "Go Gators!");
    
    auto boxText1 = Label::createWithTTF(textString2, BOLD, visibleSize.height * TEXTSIZE*0.51);
    boxText1->setDimensions(0.92*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.45*textBox->getContentSize().height));
    boxText1->setColor(cocos2d::Color3B::BLACK);
    boxText1->setAlignment(TextHAlignment::CENTER);
    
    this->textBox->addChild(boxText1, 1);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto prevPage = this->menu->getChildren().at(3);
    prevPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
    auto nextPage = this->menu->getChildren().at(2);
    nextPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.845 + origin.x,
                                visibleSize.height* SCALEY1 * 2.49 + origin.y));
}

void Scene08::nextText(Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto textString1 = Json_getString(script, "8.3", "Go Gators!");
    this->textBox->removeAllChildren();
    this->meetContainer->removeAllChildren();
    if(textNum08 == 1)
    {
        textString1 = Json_getString(script, "8.3", "Go Gators!");
        this->scheduleOnce(schedule_selector(Scene08::anethesiologistAppears), 0);
        //auto meetButton = Sprite::create(meetyouranestesiologist);
        
//        meetButton->setScaleX((visibleSize.width * 0.2) / meetButton->getContentSize().width);
//        meetButton->setScaleY((visibleSize.height * 0.2) / meetButton->getContentSize().height);
//        meetButton->setScaleY(meetButton->getScaleX());
//        meetButton->setPosition(0.5*meetContainer->getContentSize().width,
//                                0.9*meetContainer->getContentSize().height);
//        auto meetText2 = Label::createWithTTF("     Meet Your \nAnesthesiologist!", BLACK, visibleSize.height * TEXTSIZE * 0.75);
//        meetText2->setPosition(0.495*meetContainer->getContentSize().width,
//                              1.2*meetContainer->getContentSize().height);
//        this->meetContainer->addChild(meetText2, 5);
//        this->meetContainer->addChild(meetButton, 4);
    }
    else
    {
        textString1 = Json_getString(script, "8.4", "Go Gators!");
        this->scheduleOnce(schedule_selector(Scene08::resAppears), 0);
        this->scheduleOnce(schedule_selector(Scene08::nextButtonAppears), 0);
    }
    
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.57);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    if(textNum08 == 1)
    {
        boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.4*textBox->getContentSize().height));
    }
    else
    {
        boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.4*textBox->getContentSize().height));
    }
    
    boxText->setColor(cocos2d::Color3B::BLACK);
    boxText->setAlignment(TextHAlignment::CENTER);
    
    this->textBox->addChild(boxText, 1);
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto prevPage = this->menu->getChildren().at(3);
    prevPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
    if(textNum08 == 2)
    {
        auto nextPage = this->menu->getChildren().at(2);
        nextPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
    }
    textNum08 = textNum08 + 1;
}

void Scene08::prevText(Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->textBox->removeAllChildren();
    auto textString2 = Json_getString(script, "8.2", "Go Gators!");
    if(textNum08 == 2)
    {
        textString2 = Json_getString(script, "8.2", "Go Gators!");
        this->scheduleOnce(schedule_selector(Scene08::surgeonAppears), 0);
    }
    else
    {
        textString2 = Json_getString(script, "8.3", "Go Gators!");
        this->scheduleOnce(schedule_selector(Scene08::anethesiologistAppears), 0);
    }
    
    
    auto boxText1 = Label::createWithTTF(textString2, BOLD, visibleSize.height * TEXTSIZE*0.57);
    boxText1->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.4*textBox->getContentSize().height));
    if(textNum08 == 2)
    {
        boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.4*textBox->getContentSize().height));
    }
    else
    {
        boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.4*textBox->getContentSize().height));
    }
    boxText1->setColor(cocos2d::Color3B::BLACK);
    boxText1->setAlignment(TextHAlignment::CENTER);
    
    this->textBox->addChild(boxText1, 1);
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if(textNum08 == 2)
    {
        auto prevPage = this->menu->getChildren().at(3);
        prevPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
    }
    
    auto nextPage = this->menu->getChildren().at(2);
    nextPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.845 + origin.x,
                                visibleSize.height* SCALEY1 * 2.49 + origin.y));
    textNum08 = textNum08 - 1;
}

