#include "Scene09.h"
#include "Scene10.h"
#include "Scene08.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

enum {PICKCUFF, PICKTHERMO, PICKPULSE, PICKELEC};
int foundTally = 0;
int itemNum = 0;
Scene* Scene09::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene09 class that inherits from Layer class
	auto layer = Scene09::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene09::init() {
    foundTally = 0;
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

	auto bkgd = Sprite::create(CLOSERLOOKBKGD);
	bkgd->setAnchorPoint(Vec2(0, 0));
	bkgd->setPosition(Vec2(origin.x, origin.y));
	bkgd->setScale(visibleSize.width / bkgd->getContentSize().width, visibleSize.height / bkgd->getContentSize().height);
	this->addChild(bkgd);
    
    auto Cuff = MenuItemImage::create(
                                           cuff,
                                           cuff,
                                           CC_CALLBACK_1(Scene09::ispyCallBack, this, PICKCUFF)
                                           );
    
	Cuff->setAnchorPoint(Vec2(0,0));
	Cuff->setPosition(Vec2(origin.x + w * 0.08,
                           origin.y + h * 0.35));
	Cuff->setScale(0.6 * h / bkgd->getContentSize().height,
                   0.6 * h / bkgd->getContentSize().height);
    Cuff->setTag(PICKCUFF);
	
    auto Thermo = MenuItemImage::create(
                                      thermometer,
                                      thermometer,
                                      CC_CALLBACK_1(Scene09::ispyCallBack, this, PICKTHERMO)
                                      );
    
	Thermo->setAnchorPoint(Vec2(0,0));
	Thermo->setPosition(Vec2(origin.x + w * 0.2,
                             origin.y + h * 0.49));
	Thermo->setScale(0.6*h / bkgd->getContentSize().height,
                     0.6*h / bkgd->getContentSize().height);
    Thermo->setTag(PICKTHERMO);

    auto Pulse = MenuItemImage::create(
                                      pulseox,
                                      pulseox,
                                      CC_CALLBACK_1(Scene09::ispyCallBack, this, PICKPULSE)
                                      );
    
	Pulse->setAnchorPoint(Vec2(0,0));
	Pulse->setPosition(Vec2(origin.x + w * 0.38,
                            origin.y + h * 0.26));
    Pulse->setScale(0.6*h / bkgd->getContentSize().height,
                    0.6*h / bkgd->getContentSize().height);
    Pulse->setTag(PICKPULSE);

    auto Elec = MenuItemImage::create(
                                       electrodes,
                                       electrodes,
                                       CC_CALLBACK_1(Scene09::ispyCallBack, this, PICKELEC)
                                       );
    
	Elec->setAnchorPoint(Vec2(0,0));
	Elec->setPosition(Vec2(origin.x + w * 0.22,
                           origin.y + h * 0.28));
    Elec->setScale(0.6*h / bkgd->getContentSize().height,
                   0.6*h / bkgd->getContentSize().height);
    Elec->setTag(PICKELEC);
    
    auto grow = ScaleBy::create(0.5, 1.1);
    auto normal = ScaleBy::create(3, 1);
    auto shrink = ScaleBy::create(0.5, 1/1.1);
    
    auto action = Sequence::create(normal,grow,shrink, nullptr);
    
    Cuff->runAction(RepeatForever::create(action));
    Thermo->runAction(RepeatForever::create(action->clone()));
    Pulse->runAction(RepeatForever::create(action->clone()));
    Elec->runAction(RepeatForever::create(action->clone()));

    this->menu = Menu::create(Cuff, Thermo, Pulse, Elec, NULL);
    
    this->menu->setPosition(Vec2::ANCHOR_MIDDLE);
    this->menu->setEnabled(false);
    this->addChild(this->menu, (FRAMEDRAW + 1)); // Please note that the one must be there
    
    // Scripts
    UserDefault* def = UserDefault::getInstance();
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "Scene09");
    
	//add textbox
    this->textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                           0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                   0.2*visibleSize.height / textBox->getContentSize().height);

    auto textString1 = Json_getString(script, "9.0", "Go Gators!");
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.75);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.8*textBox->getContentSize().height);
    boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.35*textBox->getContentSize().height));
    boxText->setColor(cocos2d::Color3B::BLACK);
    boxText->setAlignment(TextHAlignment::CENTER);
    
    textBox->addChild(boxText, 1);
    
    this->addChild(textBox, FRAMEDRAW + 5);
	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
    FrameNav temp;
    temp.addFrameNav(this);
    this->frameNav = &temp;
    this->frameNav->bkgdMusic(2);
    
    
    
    
    
    //Set the debug state here
    def->setBoolForKey("CLOSERLOOK", true);
    def->flush();

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene09::gotoNextScene, this)
	);
    auto isDebug = def->getBoolForKey("IsDebug", false);
    
    if (!isDebug) {
        nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                    visibleSize.height* SCALEY1 + origin.y));
    }
    else
    {
        bool tempBp = def->getBoolForKey("ISPYBPFOUND", false);
        bool tempThermo = def->getBoolForKey("ISPYTHERMOFOUND", false);
        bool tempOx = def->getBoolForKey("ISPYPULSEOXFOUND", false);
        bool tempElec = def->getBoolForKey("ISPYELECFOUND", false);
        if(tempBp && tempThermo && tempOx && tempElec)
        {
            nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                    visibleSize.height* SCALEY1 + origin.y));
        }
        else
        {
            nextScene->setPosition(Vec2(-1*visibleSize.width * SCALEX2 + origin.x,
                                        -1*visibleSize.height* SCALEY1 + origin.y));
        }
    }
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(Scene09::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);

	// Create the menu
	auto menu2 = Menu::create(nextScene, prevScene, NULL);
	menu2->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu2, (FRAMEDRAW + 1)); // Please note that the one must be there
    
    this->scheduleOnce(schedule_selector(Scene09::textAppears), 0.5);

	return true;
}

void Scene09::ispyCallBack(Ref* pSender, int object){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->menu->setEnabled(false);
    
    UserDefault * def = UserDefault::getInstance();
    
    auto iSpyName = 0;
    switch (object) {
        case PICKCUFF:
            iSpyName = def->getBoolForKey("ISPYBPFOUND", false);
            break;
            
        case PICKTHERMO:
            iSpyName = def->getBoolForKey("ISPYTHERMOFOUND", false);
            break;
    
        case PICKPULSE:
            iSpyName = def->getBoolForKey("ISPYPULSEOXFOUND", false);
            break;
    
        case PICKELEC:
            iSpyName = def->getBoolForKey("ISPYELECFOUND", false);
            break;
    
        default:
            break;
    }
    
    if (!iSpyName) {
        foundTally = foundTally +1;
        auto star = Sprite::create(STARSHINE);
        
        auto sprite = this->menu->getChildByTag(object);
        auto sclx = sprite->getScaleX();
        auto scly = sprite->getScaleY();
        auto pos = sprite->getPosition();
        auto listener = EventListenerTouchOneByOne::create();
        
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *event){
            return true;
            
        };
        
        listener->onTouchMoved = [=](cocos2d::Touch *touch, cocos2d::Event *event){
            
            //// move the object around
            auto temppos = touch->getLocation();
            
            sprite->setPosition(temppos);
            
            return true;
        };
        
        listener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event){
            
            if(object == PICKCUFF)
            {
                Scene09::replaceLabel("9.5", 0.62, 0.5, 5);
                auto cuffOnArm = Sprite::create(cuff);
                auto w = visibleSize.width;
                auto h = visibleSize.height;

                auto bkgd = Sprite::create(CLOSERLOOKBKGD);
                bkgd->setAnchorPoint(Vec2(0, 0));
                bkgd->setPosition(Vec2(origin.x, origin.y));
                bkgd->setScale(visibleSize.width / bkgd->getContentSize().width, visibleSize.height / bkgd->getContentSize().height);
                cuffOnArm->setOpacity(0);
                cuffOnArm->setScale(0.7 * h / bkgd->getContentSize().height,
                               0.7 * h / bkgd->getContentSize().height);
                cuffOnArm->setPosition(Vec2(origin.x + 0.56 * visibleSize.width, origin.y + 0.46 * visibleSize.height));
                
                sprite->runAction(Sequence::create(FadeOut::create(0.4),
                                                   RemoveSelf::create(),
                                                   nullptr));
                
                this->addChild(cuffOnArm, FRAMEDRAW);
                cuffOnArm->runAction(Sequence::create(DelayTime::create(0.6),
                                                          FadeIn::create(0.4),
                                                          nullptr));
                
                sprite->runAction(Sequence::create(Spawn::create(MoveTo::create(0.6, Vec2(origin.x + 0.475 * visibleSize.width, origin.y + 0.32 * visibleSize.height)),
                                                                 RotateBy::create(0.6, 360),
                                                                 ScaleBy::create(0.6, 1.45),
                                                                 nullptr),nullptr));
            }
            if(object == PICKTHERMO)
            {
                Scene09::replaceLabel("9.6", 0.75, 0.35, 4);
                sprite->stopAllActions();
                sprite->runAction(Spawn::create(ScaleTo::create(0.4, sclx, scly),
                                                MoveTo::create(0.4, pos),
                                                RotateTo::create(0.4, 0),
                                                nullptr));
            }
            if(object == PICKPULSE)
            {
                Scene09::replaceLabel("9.8", 0.48, 0.5, 3);
                auto pulseExtended = Sprite::create(pulseoxclicked);
                sprite->runAction(Sequence::create(FadeOut::create(0.4),
                                                   RemoveSelf::create(),
                                                   nullptr));
                pulseExtended->setOpacity(0);
                pulseExtended->setPosition(Vec2(origin.x + 0.49 * visibleSize.width, origin.y + 0.35 * visibleSize.height));
                pulseExtended->setScale(sclx/1, scly/1);
                this->addChild(pulseExtended, FRAMEDRAW);
                pulseExtended->runAction(Sequence::create(DelayTime::create(0.6),
                                                          FadeIn::create(0.4),
                                                          nullptr));
            }
            if(object == PICKELEC)
            {
                Scene09::replaceLabel("9.7", 0.75, 0.35, 3);
                auto elecExtended = Sprite::create(electrodesclicked); // files mislabeled
                sprite->runAction(Sequence::create(FadeOut::create(0.4),
                                                   RemoveSelf::create(),
                                                   nullptr));
                elecExtended->setOpacity(0);
                elecExtended->setPosition(Vec2(origin.x + 0.49 * visibleSize.width, origin.y + 0.38 * visibleSize.height));
                elecExtended->setScale(sclx*1.2, scly*1.2);
                elecExtended->setRotation(-5);
                this->addChild(elecExtended, FRAMEDRAW);
                elecExtended->runAction(Sequence::create(DelayTime::create(0.6),
                                                          FadeIn::create(0.4),
                                                          nullptr));
            }
            /*sprite->runAction(Spawn::create(ScaleTo::create(0.4, sclx, scly),
                                            MoveTo::create(0.4, pos),
                                            RotateTo::create(0.4, 0),
                                            nullptr));*/
            Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
            this->scheduleOnce(schedule_selector(Scene09::enableMenu), 0.4);
            return true;
        };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        
        switch (object) {
            case PICKCUFF:
                def->setBoolForKey("ISPYBPFOUND", true);
                def->flush();
                
                Scene09::replaceLabel("9.1", 0.75, 0.45, 3);
                
                star->setPosition(Vec2(origin.x + (0.15 * visibleSize.width),
                                       origin.y + (0.4 * visibleSize.height)));
                //Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
                break;
                
            case PICKTHERMO:
                def->setBoolForKey("ISPYTHERMOFOUND", true);
                def->flush();
                
                Scene09::replaceLabel("9.2", 0.65, 0.4, 3);
                
                star->setPosition(Vec2(origin.x + (0.25 * visibleSize.width),
                                       origin.y + (0.5 * visibleSize.height)));
                //Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
                break;
                
            case PICKPULSE:
                def->setBoolForKey("ISPYPULSEOXFOUND", true);
                def->flush();
                
                Scene09::replaceLabel("9.4", 0.75, 0.35, 3);
                
                star->setPosition(Vec2(origin.x + (0.42 * visibleSize.width),
                                       origin.y + (0.35 * visibleSize.height)));
                //Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
                break;
                
            case PICKELEC:
                def->setBoolForKey("ISPYELECFOUND", true);
                def->flush();
                
                Scene09::replaceLabel("9.3", 0.75, 0.35, 3);
                
                star->setPosition(Vec2(origin.x + (0.27 * visibleSize.width),
                                       origin.y + (0.37 * visibleSize.height)));
                //Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
                break;
                
            default:
                break;
        }
        
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
        
        this->scheduleOnce(schedule_selector(Scene09::toggleIcon), 3);
        this->scheduleOnce(schedule_selector(Scene09::enableMenu), 4);
    } else {
        this->menu->setEnabled(false);
        auto sprite = this->menu->getChildByTag(object);
        auto sclx = sprite->getScaleX();
        auto scly = sprite->getScaleY();
        auto pos = sprite->getPosition();
        
        auto listener = EventListenerTouchOneByOne::create();
        
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *event){
            
            return true;
            
        };
        
        listener->onTouchMoved = [=](cocos2d::Touch *touch, cocos2d::Event *event){
            
            //// move the object around
            auto temppos = touch->getLocation();
            
            sprite->setPosition(temppos);
            
            return true;
        };
         // files mislabeled
        
        listener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event){
            
            if(object == PICKCUFF)
            {
                Scene09::replaceLabel("9.5", 0.62, 0.5, 5);
                auto cuffOnArm = Sprite::create(cuff);
                auto w = visibleSize.width;
                auto h = visibleSize.height;

                auto bkgd = Sprite::create(CLOSERLOOKBKGD);
                bkgd->setAnchorPoint(Vec2(0, 0));
                bkgd->setPosition(Vec2(origin.x, origin.y));
                bkgd->setScale(visibleSize.width / bkgd->getContentSize().width, visibleSize.height / bkgd->getContentSize().height);
                cuffOnArm->setOpacity(0);
                cuffOnArm->setScale(0.7 * h / bkgd->getContentSize().height,
                               0.7 * h / bkgd->getContentSize().height);
                cuffOnArm->setPosition(Vec2(origin.x + 0.56 * visibleSize.width, origin.y + 0.46 * visibleSize.height));
                
                sprite->runAction(Sequence::create(FadeOut::create(0.4),
                                                   RemoveSelf::create(),
                                                   nullptr));
                
                this->addChild(cuffOnArm, FRAMEDRAW);
                cuffOnArm->runAction(Sequence::create(DelayTime::create(0.6),
                                                          FadeIn::create(0.4),
                                                          nullptr));
                
                sprite->runAction(Sequence::create(Spawn::create(MoveTo::create(0.6, Vec2(origin.x + 0.475 * visibleSize.width, origin.y + 0.32 * visibleSize.height)),
                                                                 RotateBy::create(0.6, 360),
                                                                 ScaleBy::create(0.6, 1.45),
                                                                 nullptr),nullptr));
            }
            if(object == PICKTHERMO)
            {
                Scene09::replaceLabel("9.6", 0.75, 0.35, 4);
                sprite->runAction(Spawn::create(ScaleTo::create(0.4, sclx, scly),
                                                MoveTo::create(0.4, pos),
                                                RotateTo::create(0.4, 0),
                                                nullptr));
            }
            if(object == PICKPULSE)
            {
                Scene09::replaceLabel("9.8", 0.48, 0.5, 3);
                auto pulseExtended = Sprite::create(pulseoxclicked);
                sprite->runAction(Sequence::create(FadeOut::create(0.4),
                                                   RemoveSelf::create(),
                                                   nullptr));
                pulseExtended->setOpacity(0);
                pulseExtended->setPosition(Vec2(origin.x + 0.49 * visibleSize.width, origin.y + 0.35 * visibleSize.height));
                pulseExtended->setScale(sclx/1, scly/1);
                this->addChild(pulseExtended, FRAMEDRAW);
                pulseExtended->runAction(Sequence::create(DelayTime::create(0.6),
                                                          FadeIn::create(0.4),
                                                          nullptr));
            }
            if(object == PICKELEC)
            {
                Scene09::replaceLabel("9.7", 0.75, 0.35, 3);
                auto elecExtended = Sprite::create(electrodesclicked); // files mislabeled
                sprite->runAction(Sequence::create(FadeOut::create(0.4),
                                                   RemoveSelf::create(),
                                                   nullptr));
                elecExtended->setOpacity(0);
                elecExtended->setPosition(Vec2(origin.x + 0.49 * visibleSize.width, origin.y + 0.38 * visibleSize.height));
                elecExtended->setScale(sclx*1.2, scly*1.2);
                elecExtended->setRotation(-5);
                this->addChild(elecExtended, FRAMEDRAW);
                elecExtended->runAction(Sequence::create(DelayTime::create(0.6),
                                                          FadeIn::create(0.4),
                                                          nullptr));
            }
            /*sprite->runAction(Spawn::create(ScaleTo::create(0.4, sclx, scly),
                                            MoveTo::create(0.4, pos),
                                            RotateTo::create(0.4, 0),
                                            nullptr));*/
            Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
            this->scheduleOnce(schedule_selector(Scene09::enableMenu), 0.4);
            return true;
        };
        
        
        
        switch (object) {
            case PICKCUFF:
                Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
                /*sprite->runAction(Sequence::create(Spawn::create(MoveTo::create(0.6, Vec2(origin.x + 0.475 * visibleSize.width, origin.y + 0.32 * visibleSize.height)),
                                                                 RotateBy::create(0.6, 360),
                                                                 ScaleBy::create(0.6, 1.45),
                                                                 nullptr),
                                                   DelayTime::create(4),
                                                   FadeOut::create(0.2),
                                                   MoveTo::create(0.08, pos),
                                                   ScaleTo::create(0.1, sclx, scly),
                                                   FadeIn::create(0.4),
                                                   nullptr));*/
                
                Scene09::replaceLabel("9.1.1", 0.75, 0.35, 3);
                this->scheduleOnce(schedule_selector(Scene09::enableMenu), 5.4);
                break;
                
            case PICKTHERMO:
                
                Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
                
                //sprite->runAction(Spawn::create(ScaleBy::create(0.4, 1.4, 1.4),
                //                                RotateBy::create(0.4, -60),
                //                                nullptr));
                
                Scene09::replaceLabel("9.2.1", 0.75, 0.35, 3);
                this->scheduleOnce(schedule_selector(Scene09::enableMenu), 5.4);
                break;
                
            case PICKPULSE:
                Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
                
                /*sprite->runAction(Sequence::create(FadeOut::create(0.4),
                                                   DelayTime::create(5.5),
                                                   FadeIn::create(0.4),
                                                   nullptr));
                pulseExtended->setOpacity(0);
                pulseExtended->setPosition(Vec2(origin.x + 0.49 * visibleSize.width, origin.y + 0.35 * visibleSize.height));
                pulseExtended->setScale(sclx/1, scly/1);
                this->addChild(pulseExtended, FRAMEDRAW);
                pulseExtended->runAction(Sequence::create(DelayTime::create(0.6),
                                                          FadeIn::create(0.4),
                                                          DelayTime::create(4.7),
                                                          FadeOut::create(0.4),
                                                          RemoveSelf::create(),
                                                          nullptr));*/
                
                Scene09::replaceLabel("9.4.1", 0.75, 0.35, 3);
                this->scheduleOnce(schedule_selector(Scene09::enableMenu), 6.4);
                
                break;
                
            case PICKELEC:
                Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
                
                /*sprite->runAction(Sequence::create(FadeOut::create(0.4),
                                                   DelayTime::create(2.5),
                                                   FadeIn::create(0.4),
                                                   nullptr));
                elecExtended->setOpacity(0);
                elecExtended->setPosition(Vec2(origin.x + 0.49 * visibleSize.width, origin.y + 0.38 * visibleSize.height));
                elecExtended->setScale(sclx*1.2, scly*1.2);
                elecExtended->setRotation(-5);
                this->addChild(elecExtended, FRAMEDRAW);
                elecExtended->runAction(Sequence::create(DelayTime::create(0.6),
                                                          FadeIn::create(0.4),
                                                          DelayTime::create(1.7),
                                                          FadeOut::create(0.4),
                                                          RemoveSelf::create(),
                                                          nullptr));*/
                
                Scene09::replaceLabel("9.3.1", 0.75, 0.35, 3);
                this->scheduleOnce(schedule_selector(Scene09::enableMenu), 3.4);
                break;
                
            default:
                break;
        }
    }
    if(foundTally == 4)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        
        // Get drawing origin of screen for sprites
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        auto center = Vec2(0.5*visibleSize.width + origin.x,
                           0.5*visibleSize.height + origin.y);
        auto w = visibleSize.width;
        auto h = visibleSize.height;
        auto nextScene = MenuItemImage::create(
                                               MOVEFWD,
                                               MOVEFWD,
                                               CC_CALLBACK_1(Scene09::gotoNextScene, this));
        nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                    visibleSize.height* SCALEY1 + origin.y));
        nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                            0.1*h / nextScene->getContentSize().height);
        
        auto menu2 = Menu::create(nextScene, NULL);
        menu2->setPosition(Vec2::ANCHOR_MIDDLE);
        this->addChild(menu2, (FRAMEDRAW + 1)); // Please note that the one must be there
        
    }
};

void Scene09::toggleIcon(float dt) {
    // If used to create an icon bar
    this->frameNav->createIconBar(this);

}

void Scene09::pulseDelay(float dt) {
    
    Scene09::replaceLabel("9.32", 0.65, 0.5, 3);
}

// Callback function to move on to the next scene
void Scene09::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene08::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move on to the previous scene
void Scene09::gotoPreviousScene(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();
    def->setBoolForKey("CLOSERLOOK", false);
	auto nextScene = Scene08::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void Scene09::enableMenu(float dt) {
    
    this->menu->setEnabled(true);
}

void Scene09::textAppears(float dt)
{
    
    this->menu->setEnabled(true);
    //// get text from json script object
    
    auto textString = Json_getString(script, "9.0", "Go Gators!");
    ;
    //// set up text
    
    // Added a framenav function so all text displays the same
    
    FrameNav fn;
    this->sceneLabel = fn.createText(textString, this);
    
    auto appear = FadeIn::create(0.2);
    
    
    this->sceneLabel->runAction(appear);
    
}

void Scene09::replaceLabel(const char* name, float size, float yScaler, float dt)
{
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->textBox->removeAllChildren();
    auto textString2 = Json_getString(script, name, "Go Gators!");
    
    auto boxText1 = Label::createWithTTF(textString2, BOLD, visibleSize.height * TEXTSIZE*size);
    boxText1->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  yScaler*textBox->getContentSize().height));
    boxText1->setColor(cocos2d::Color3B::BLACK);
    boxText1->setAlignment(TextHAlignment::CENTER);
    
    this->textBox->addChild(boxText1, 1);
}

void Scene09::nextButtonAppears(float dt){
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
        
            def->setBoolForKey("Scene9Done", true);
            
            // Get size of the window being displayed to
            log("testing");
            auto meetBox = nextButton->getBoundingBox();
            //auto takeCloserLookBox = event->getCurrentTarget()->getBoundingBox();
            if (meetBox.containsPoint(touch->getLocation())) {
                log("testing");
                UserDefault* def = UserDefault::getInstance();
                def->setBoolForKey("Scene9Done", true);
                CCDirector::sharedDirector()->pushScene(TransitionFade::create(0.5, Scene08::createScene()));
            }
            
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(meetListener, this);
}
