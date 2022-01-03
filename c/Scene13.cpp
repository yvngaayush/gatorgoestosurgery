#include "Scene13.h"
#include "Scene14.h"
#include "Scene12.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"
int textNum2 = 1;
Scene* Scene13::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene13 class that inherits from Layer class
	auto layer = Scene13::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene13::init() {

	// Ensure layer from createScene() was created
	if (!Layer::init()) {
		return false;
	}
    
    textNum2 = 1;

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
    script = Json_getItem(chapterScript, "Scene13");

	auto bkgd = Sprite::create(FLAVORBKGD);
	bkgd->setPosition(center);
	bkgd->setScale(w / bkgd->getContentSize().width,
                   h / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);
    
    auto mask = Sprite::create(ANESMASK);
    
    mask->setPosition(Vec2(origin.x + visibleSize.width * 0.18,
                           origin.y + visibleSize.height * 0.62));
    mask->setScale(0.45 * h / mask->getContentSize().height,
                   0.45 * h / mask->getContentSize().height);
    mask->setRotation(15);
    this->addChild(mask, 1);
    
    auto grow = ScaleBy::create(0.6, (1/0.75));
    auto normal = ScaleBy::create(1.5, 1);
    auto shrink = ScaleBy::create(0.6, 0.75);
    
    
    auto action = Sequence::create(normal,grow,shrink, nullptr);
    
    auto buttonSize = 0.12f;
    
    auto melon = Sprite::create(ANESMELON);
    
    melon->setPosition(Vec2(origin.x + visibleSize.width * 0.16,
                            origin.y + visibleSize.height * 0.61));
    melon->setScale(buttonSize * h / melon->getContentSize().height,
                    buttonSize * h / melon->getContentSize().height);
    this->addChild(melon, 2);
    
    auto gum = Sprite::create(ANESGUM);
    
    gum->setPosition(Vec2(origin.x + visibleSize.width * 0.16,
                          origin.y + visibleSize.height * 0.45));
    gum->setScale(buttonSize * h / gum->getContentSize().height,
                  buttonSize * h / gum->getContentSize().height);
    this->addChild(gum, 2);
    
    auto berry = Sprite::create(ANESBERRY);
    
    berry->setPosition(Vec2(origin.x + visibleSize.width * 0.16,
                            origin.y + visibleSize.height * 0.29));
    berry->setScale(buttonSize * h / berry->getContentSize().height,
                    buttonSize * h / berry->getContentSize().height);
    this->addChild(berry, 2);
    
    // pulse
    auto action1 = TargetedAction::create(melon, action);
    auto action2 = TargetedAction::create(gum, action->clone());
    auto action3 = TargetedAction::create(berry, action->clone());

    this->runAction(RepeatForever::create(Sequence::create(action1, action2, action3, nullptr)));
    
	// ************** Menu Items for Scene **************
    // Adds home button and volume control to the scene
	FrameNav frameNav;
	frameNav.addFrameNav(this);
    frameNav.bkgdMusic(3);

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene13::gotoNextScene, this)
	);
    auto isDebug = def->getBoolForKey("IsDebug", false);
    
    if (!isDebug) {
        nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                    visibleSize.height* SCALEY1 + origin.y));
    }
    else
    {
        bool tempDone = def->getBoolForKey("Scene13Done", true);
        if(tempDone)
        {
            nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                        visibleSize.height* SCALEY1 + origin.y));
        }
        else{
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
		CC_CALLBACK_1(Scene13::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);
    
    auto nextPage = MenuItemImage::create(
        PAGEFWD,
        PAGEFWD,
        CC_CALLBACK_1(Scene13::nextText, this)
    );
    nextPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.845 + origin.x,
                                visibleSize.height* SCALEY1 * 2.49 + origin.y));

    nextPage->setScale(0.15*w / nextPage->getContentSize().width,
                       0.2*h / nextPage->getContentSize().height);
    
    auto prevPage = MenuItemImage::create(
        PAGEBWD,
        PAGEBWD,
        CC_CALLBACK_1(Scene13::prevText, this)
    );
    prevPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x,
                                visibleSize.height* SCALEY1 * 2.49 + origin.y));

    prevPage->setScale(0.15*w / nextPage->getContentSize().width,
                        0.2*h / nextPage->getContentSize().height);

	// Create the menu
	menu = Menu::create(nextScene, prevScene, nextPage, prevPage, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there

    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        UserDefault* def = UserDefault::getInstance();
        def->setBoolForKey("Scene13Done", true);
        
        auto grow = ScaleBy::create(4, 1.6, 1.6);
        auto rotate = MoveBy::create(5, Vec2(0.4*visibleSize.width, 0.1*visibleSize.height));
        auto selected = Spawn::create(grow, rotate, nullptr);
        auto pos = touch->getLocation();
        auto x = (pos.x - origin.x)/visibleSize.width;
        auto y = (pos.y - origin.y)/visibleSize.height;
        
        if (std::abs(x-0.16)<0.1){
            if (std::abs(y-0.41)<0.08){
                gum->runAction(selected);
                return true;
            } else if (std::abs(y-0.61)<0.08) {
                melon->runAction(selected);
                return true;
            } else if (std::abs(y-0.3)<0.08) {
                berry->runAction(selected);
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
        return false;
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event) {
        
        this->scheduleOnce(schedule_selector(Scene13::waitNextScene), 1);
        return true;
    };
        
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    this->textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                           0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                   0.2*visibleSize.height / textBox->getContentSize().height);

    auto textString1 = Json_getString(script, "13.1", "Go Gators!");
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.65);
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

// Callback function to move on to the next scene
void Scene13::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene14::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move on to the previous scene
void Scene13::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene12::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void Scene13::textAppears(float dt)
{
    
    //// get text from json script object
    
    auto textString1 = Json_getString(script, "13.1", "Go Gators!");
    auto textString2 = Json_getString(script, "13.2", "Go Gators!");
    
    //// set up text
    
    // Added a framenav function so all text displays the same
    
    FrameNav fn;
    auto label1 = fn.createText(textString1, this);
    auto label2 = fn.createText(textString2, this);
    
    auto appear = FadeIn::create(0.1);
    auto disappear = FadeOut::create(0.1);
    auto delay = DelayTime::create(6);
    
    label1->runAction(Sequence::create(appear, delay, disappear, nullptr));
    label2->runAction(Sequence::create(delay, appear, nullptr));
    
}

void Scene13::waitNextScene(float dt){
    auto nextScene = Scene14::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(5, nextScene));
};

void Scene13::nextText(Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto textString1 = Json_getString(script, "13.2", "Go Gators!");
    this->textBox->removeAllChildren();
    if(textNum2 == 1)
    {
        textString1 = Json_getString(script, "13.2", "Go Gators!");
    }
    else
    {
        textString1 = Json_getString(script, "13.3", "Go Gators!");
    }
    
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.65);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    if(textNum2 == 1)
    {
        boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.35*textBox->getContentSize().height));
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
    if(textNum2 == 2)
    {
        auto nextPage = this->menu->getChildren().at(2);
        nextPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
    }
    textNum2 = textNum2 + 1;
}

void Scene13::prevText(Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->textBox->removeAllChildren();
    auto textString2 = Json_getString(script, "13.1", "Go Gators!");
    if(textNum2 == 2)
    {
        textString2 = Json_getString(script, "13.1", "Go Gators!");
    }
    else
    {
        textString2 = Json_getString(script, "13.2", "Go Gators!");
    }
    
    
    auto boxText1 = Label::createWithTTF(textString2, BOLD, visibleSize.height * TEXTSIZE*0.65);
    boxText1->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.4*textBox->getContentSize().height));
    if(textNum2 == 2)
    {
        boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.4*textBox->getContentSize().height));
    }
    else
    {
        boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.35*textBox->getContentSize().height));
    }
    boxText1->setColor(cocos2d::Color3B::BLACK);
    boxText1->setAlignment(TextHAlignment::CENTER);
    
    this->textBox->addChild(boxText1, 1);
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if(textNum2 == 2)
    {
        auto prevPage = this->menu->getChildren().at(3);
        prevPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
    }
    
    auto nextPage = this->menu->getChildren().at(2);
    nextPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.845 + origin.x,
                                visibleSize.height* SCALEY1 * 2.49 + origin.y));
    textNum2 = textNum2 - 1;
}
