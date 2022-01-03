#include "Scene06.h"
#include "Scene07.h"
#include "Scene04.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

Scene* Scene06::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene06 class that inherits from Layer class
	auto layer = Scene06::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene06::init() {

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

	auto bkgd = Sprite::create(ELEVATORBKGD);
	bkgd->setPosition(center);
	bkgd->setScale(w / bkgd->getContentSize().width,
                   h / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);

	auto mom = Sprite::create(MOM05);
	mom->setPosition(0.15*w + origin.x,
                     0.45*h + origin.y);
    mom->setScale(0.65*h/mom->getContentSize().height,
                  0.65*h/mom->getContentSize().height);
    this->addChild(mom, 1);
    
    auto patient = Sprite::create(PATIENT05);
    patient->setPosition(0.35*w + origin.x,
                         0.35*h + origin.y);
    patient->setScale(0.45*h/patient->getContentSize().height,
                      0.45*h/patient->getContentSize().height);
	this->addChild(patient, 2);

	auto nurse = Sprite::create(NURSE05);
    nurse->setPosition(0.6*w + origin.x,
                       0.45*h + origin.y);
    nurse->setScale(0.7*h/nurse->getContentSize().height,
                    0.7*h/nurse->getContentSize().height);
	this->addChild(nurse, 1);

	//add elevator buttons
	this->elevatorup = Sprite::create(ELEVATORBUTTONUP);
    elevatorup->setScale(0.05*w/elevatorup->getContentSize().width,
                         0.05*w/elevatorup->getContentSize().height);
    elevatorup->setPosition(0.93*w,
                            0.64*h);
//    auto grow = ScaleBy::create(0.6, (1/0.7));
//    auto normal = ScaleBy::create(1.5, 1);
//    auto shrink = ScaleBy::create(0.6, 0.7);
//
//    auto action = Sequence::create(normal,grow,shrink, nullptr);
//    elevatorup->runAction(RepeatForever::create(action));
	this->addChild(elevatorup, (FRAMEDRAW + 2));
    
    auto elevatordown = Sprite::create(ELEVATORBUTTONDOWN);
    elevatordown->setScale(0.05*w/elevatordown->getContentSize().width,
                         0.05*w/elevatordown->getContentSize().height);
    elevatordown->setPosition(0.93*w,0.60*h-0.045*w);
    this->addChild(elevatordown, 1);
    
    this->glow = Sprite::create(GLOW);
    glow->setPosition(0.93*w,0.64*h);
    glow->setScale(0.15 * (visibleSize.width / glow->getContentSize().width),
                    0.15 * (visibleSize.width / glow->getContentSize().width));
    glow->setAnchorPoint(Vec2(0.5, 0.5));
    glow->setOpacity(0);
    this->addChild(glow, (FRAMEDRAW + 1));
//    glow->setScale(2*(visibleSize.width / glow->getContentSize().width),
//                    2*(visibleSize.height / glow->getContentSize().height));
    
//    glow->runAction(RepeatForever::create(RotateBy::create(2, 360.0f)));

	//add elevator button
//	auto elevatorgreen = Sprite::create(GREENELEVATORBUTTON);
//    elevatorgreen->setScale(0.05*w/elevatorgreen->getContentSize().width,
//                            0.05*w/elevatorgreen->getContentSize().height);
//	elevatorgreen->setPosition(0.93*w,
//                               0.64*h);
//    elevatorgreen->runAction(RepeatForever::create(action));
//	this->addChild(elevatorgreen, 1);
//
//	elevatorgreen->setVisible(false);
    
    auto meetYourNurseButton = MenuItemImage::create(
                                      BUTTON06,
                                      BUTTON06,
                                      CC_CALLBACK_1(Scene06::careButtonCallBack, this)
                                      );
    meetYourNurseButton->setPosition(0.7*w + origin.x,
                                     0.35*h + origin.y);
    meetYourNurseButton->setScale(0.35*w/meetYourNurseButton->getContentSize().width,
                                  0.35*w/meetYourNurseButton->getContentSize().width);
    
    auto meetlabel = Label::createWithTTF("Meet Your Nurse", BLACK, visibleSize.height * TEXTSIZE*1.2);
    auto meetText = MenuItemLabel::create(meetlabel, CC_CALLBACK_1(Scene06::careButtonCallBack, this));
    meetText->setPosition(0.695*w + origin.x,
                          0.355*h + origin.y);
//Actions----------------------------------------------------------------------------------------------------
	// Touch Object
	auto elevatorlistener = EventListenerTouchOneByOne::create();
	elevatorlistener->onTouchBegan = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        auto elevatorBox = elevatorup->getBoundingBox();
        if (elevatorBox.containsPoint(locationInNode))
        {
            elevatorup->setTexture(GREENELEVATORBUTTON);
            return true;
        }
        return false;
};

	elevatorlistener->onTouchEnded = [this](Touch *touch, Event *event) -> void {
        
        UserDefault* def = UserDefault::getInstance();
        def->setBoolForKey("Scene6Done", true);
		
		//show green elevator button
//		elevatorgreen->setVisible(true);
        // go to next scene
        this->scheduleOnce(schedule_selector(Scene06::waitNextScene), 0.5);
	};

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(elevatorlistener, this);

	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
	FrameNav frameNav;
	frameNav.addFrameNav(this);
    frameNav.bkgdMusic(1);
    
    // Scripts
    UserDefault* def = UserDefault::getInstance();
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "Scene06");

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene06::gotoNextScene, this)
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
    
    auto Scene6Done = def->getBoolForKey("Scene6Done");
    if (Scene6Done){
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
		CC_CALLBACK_1(Scene06::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);
    
    auto nextPage = MenuItemImage::create(
        PAGEFWD,
        PAGEFWD,
        CC_CALLBACK_1(Scene06::nextText, this)
    );
    nextPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.845 + origin.x,
                                visibleSize.height* SCALEY1 * 2.49 + origin.y));

    nextPage->setScale(0.15*w / nextPage->getContentSize().width,
                       0.2*h / nextPage->getContentSize().height);
    
    auto nextPageListener = EventListenerTouchOneByOne::create();
    
//    nextPageListener->onTouchEnded = [&nextPage, this](Touch *touch, Event *event) -> void {
//        auto grow = ScaleBy::create(0.6, (1/0.7));
//        auto normal = ScaleBy::create(1.5, 1);
//        auto shrink = ScaleBy::create(0.6, 0.7);
//
//        auto action = Sequence::create(normal,grow,shrink, nullptr);
//        this->elevatorup->runAction(RepeatForever::create(action));
//
//        glow->runAction(RepeatForever::create(RotateBy::create(2, 360.0f)));
//    };
    
    auto prevPage = MenuItemImage::create(
        PAGEBWD,
        PAGEBWD,
        CC_CALLBACK_1(Scene06::prevText, this)
    );
    prevPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x,
                                visibleSize.height* SCALEY1 * 2.49 + origin.y));

    prevPage->setScale(0.15*w / nextPage->getContentSize().width,
                        0.2*h / nextPage->getContentSize().height);

	// Create the menu
	menu = Menu::create(nextScene, prevScene, meetYourNurseButton, meetText, prevPage, nextPage, NULL);
	this->menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(this->menu, (FRAMEDRAW + 1)); // Please note that the one must be there

    this->textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                           0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                   0.2*visibleSize.height / textBox->getContentSize().height);

    auto textString1 = Json_getString(script, "6.1", "Go Gators!");
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.67);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.4*textBox->getContentSize().height));
    boxText->setColor(cocos2d::Color3B::BLACK);
    boxText->setAlignment(TextHAlignment::CENTER);
    
    textBox->addChild(boxText, 1);
    
    this->addChild(textBox, FRAMEDRAW + 5);
    
	return true;
}

void Scene06::careButtonCallBack(Ref* pSender) {
    
    // Disable menu
    this->menu->setEnabled(false);
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto clipboard = Sprite::create(HINURSE);
    auto clip = Sprite::create(CLIPGOTIT);
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
        menu->setEnabled(true);
        
    };
    
    // Add listener
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, clipboard);
    this->addChild(clipboard, (FRAMEDRAW + 12345));
    this->addChild(textBox2, (FRAMEDRAW + 12344));
    
};

void Scene06::textAppears(float dt)
{
        
    //// get text from json script object
    
    auto textString1 = Json_getString(script, "6.1", "Go Gators!");
    auto textString2 = Json_getString(script, "6.2", "Go Gators!");
    
    //// set up text
    
    // Added a framenav function so all text displays the same
    
    FrameNav fn;
    auto label1 = fn.createText(textString1, this);
    auto label2 = fn.createText(textString2, this);
    
    auto appear = FadeIn::create(0.2);
    auto disappear = FadeOut::create(0.2);
    auto delay = DelayTime::create(6);
    
    label1->runAction(Sequence::create(appear, delay, disappear, nullptr));
    label2->runAction(Sequence::create(delay, appear, nullptr));
    
}

void Scene06::waitNextScene(float dt) {
    
    /// add audio for elevator ding?
    auto nextScene = Scene07::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move on to the next scene
void Scene06::gotoNextScene(Ref* pSender) {
//    UserDefault* def = UserDefault::getInstance();
//    def->setBoolForKey("Scene6Done", true);
	auto nextScene = Scene07::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move on to the previous scene
void Scene06::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene04::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void Scene06::nextText(Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->textBox->removeAllChildren();
    auto textString1 = Json_getString(script, "6.2", "Go Gators!");
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.6);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.5*textBox->getContentSize().height));
    boxText->setColor(cocos2d::Color3B::BLACK);
    boxText->setAlignment(TextHAlignment::CENTER);
    
    this->textBox->addChild(boxText, 1);
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto prevPage = this->menu->getChildren().at(4);
    prevPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
    auto nextPage = this->menu->getChildren().at(5);
    nextPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
    
    auto grow = ScaleBy::create(0.6, (1/0.7));
    auto normal = ScaleBy::create(1.5, 1);
    auto shrink = ScaleBy::create(0.6, 0.7);
    
    auto action = Sequence::create(normal,grow,shrink, nullptr);
    this->elevatorup->runAction(RepeatForever::create(action));
    
    this->glow->runAction(RepeatForever::create(RotateBy::create(2, 360.0f)));
    this->glow->setOpacity(255);
}

void Scene06::prevText(Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->textBox->removeAllChildren();
    auto textString2 = Json_getString(script, "6.1", "Go Gators!");
    
    auto boxText1 = Label::createWithTTF(textString2, BOLD, visibleSize.height * TEXTSIZE*0.67);
    boxText1->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.4*textBox->getContentSize().height));
    boxText1->setColor(cocos2d::Color3B::BLACK);
    boxText1->setAlignment(TextHAlignment::CENTER);
    
    this->textBox->addChild(boxText1, 1);
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto prevPage = this->menu->getChildren().at(4);
    prevPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
    auto nextPage = this->menu->getChildren().at(5);
    nextPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.845 + origin.x,
                                visibleSize.height* SCALEY1 * 2.49 + origin.y));
    
}
