#include "Scene15.h"
#include "Scene14.h"
#include "PopsicleScene.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"

enum {P1, P2, P3, P4};

Scene* Popsicle::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	// Create an instance of our DrawScene class that inherits from layer class
	auto layer = Popsicle::create();

	// Add layer to our scene
	scene->addChild(layer);

	// Scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Popsicle::init() {

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
    
    // Scripts
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "PopsicleScene");

	auto bkgd = Sprite::create(POPSICLEBKGD);
	bkgd->setPosition(center);
	bkgd->setScale(w / bkgd->getContentSize().width,
				   h / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);
    
    // background for the popsicle
    
    auto purpleCircle = DrawNode::create();
    
    purpleCircle->drawSolidCircle(Vec2(visibleSize.width*0.5 + origin.x, 0.55*visibleSize.height + origin.y), 0.25*visibleSize.width, 360.0f, 150, 1.0f, 1.0f, Color4F(0.58, 0.15, 0.68, 1.0));
    
    this->addChild(purpleCircle, 2);
    
    auto pop = Sprite::create(POP0);
    pop->setPosition(Vec2(origin.x, origin.y));
    pop->setScale(0.5*visibleSize.width / pop->getContentSize().height,
                   0.5*visibleSize.height / pop->getContentSize().height);
    pop->setRotation(-45);
    pop->setOpacity(0);
    
    this->addChild(pop, 2);
    
    pop->runAction(Spawn::create(ScaleBy::create(0.8, 1/1.2, 1/1.2), RotateBy::create(1, 360+45+20), EaseIn::create(MoveTo::create(1, Vec2(visibleSize.width*0.5 + origin.x, 0.55*visibleSize.height + origin.y)), 1), FadeIn::create(0.6), nullptr));
    pop->runAction(RepeatForever::create(Sequence::create(
                                                          DelayTime::create(0.5),
                                                          ScaleBy::create(0.5, 1.1, 1.1),
                                                          ScaleTo::create(0.3, 0.5*visibleSize.width / pop->getContentSize().height,                                                          0.5*visibleSize.height / pop->getContentSize().height), nullptr)));
    auto yum = Sprite::create(YUM);
    
    yum->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                          0.5*visibleSize.height + origin.y));
    yum->setScale(0.2*visibleSize.width / yum->getContentSize().height,
                  0.2*visibleSize.height / yum->getContentSize().height);
    yum->setOpacity(0);
    
    this->addChild(yum, 2);
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);    
    
    listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        pop->runAction(EaseIn::create(RotateBy::create(0.4, 360), 1));
        
        switch (this->bites) {
            case 0:
                pop->setTexture(POP1);
                this->bites++;
                break;
            case 1:
                pop->setTexture(POP2);
                this->bites++;
                break;
            case 2:
                pop->setTexture(POP3);
                this->bites++;
                break;
            case 3:
                pop->setTexture(POP4);
                this->bites++;
                break;
            case 4:
                pop->setTexture(POP5);
                this->bites++;
                pop->runAction(Spawn::create(DelayTime::create(0.2),
                                             MoveBy::create(0.8, Vec2(0.2*visibleSize.width, 0.1*visibleSize.width)),
                                             RotateBy::create(0.8, 720),
                                             ScaleBy::create(0.8, 2),
                                             FadeOut::create(0.8),
                                             nullptr));
                
                yum->runAction(Spawn::create(MoveBy::create(0.8, Vec2(0, 0.1*visibleSize.height)),
                                             EaseOut::create(ScaleBy::create(0.8, 2.5, 2.5), 0.8), Sequence::create(FadeIn::create(0.2), DelayTime::create(0.2), FadeOut::create(0.6), nullptr),
                                             nullptr));
                
                _eventDispatcher->removeEventListener(listener);
                
                this->scheduleOnce(schedule_selector(Popsicle::doneCallBack), 1.2);
                break;
            default:
                pop->setTexture(POP0);
                this->bites=0;
                break;
        }
        
        return false;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
	FrameNav frameNav;
	frameNav.addFrameNav(this);
	frameNav.toggleIconBar(ISPYTAG, this);
    frameNav.bkgdMusic(4);

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		DONEBUTTON,
		DONEBUTTON,
		CC_CALLBACK_1(Popsicle::gotoNextScene, this)
	);
    auto isDebug = def->getBoolForKey("IsDebug", false);
    
    if (!isDebug) {
        nextScene->setPosition(Vec2(visibleSize.width * 0.88 + origin.x,
                                    visibleSize.height* 0.2 + origin.y));
    }
    else
    {
        nextScene->setPosition(Vec2(-1*visibleSize.width * 0.88 + origin.x,
                                    -1*visibleSize.height* 0.2 + origin.y));
    }
    
    nextScene->setScale(0.15*w / nextScene->getContentSize().width,
                        0.15*w / nextScene->getContentSize().width);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		BACKBUTTON,
		BACKBUTTON,
		CC_CALLBACK_1(Popsicle::gotoPreviousScene, this)
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

    auto textString1 = Json_getString(script, "pop.1", "Go Gators!");
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*1);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.3*textBox->getContentSize().height));
    boxText->setColor(cocos2d::Color3B::BLACK);
    boxText->setAlignment(TextHAlignment::CENTER);
    
    textBox->addChild(boxText, 1);
    
    this->addChild(textBox, FRAMEDRAW + 5);

	return true;
}

// Callback function to move on to the next scene
void Popsicle::gotoNextScene(Ref * pSender) {
	auto nextScene = Scene15::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
	SpriteFrameCache::getInstance()->removeSpriteFrames();
}

// Callback function to move on to the previous scene
void Popsicle::gotoPreviousScene(Ref * pSender) {
	auto nextScene = Scene14::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
	SpriteFrameCache::getInstance()->removeSpriteFrames();
}


void Popsicle::doneCallBack(float dt) {
    auto nextScene = Scene15::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, nextScene));
    SpriteFrameCache::getInstance()->removeSpriteFrames();
}
