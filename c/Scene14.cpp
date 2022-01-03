#include "Scene14.h"
#include "Scene15.h"
#include "Scene13.h"
#include "FrameNav.h"
#include "PopsicleScene.h"
#include "editor-support/spine/Json.h"
bool alreadyPopped = false;
Scene* Scene14::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene14 class that inherits from Layer class
	auto layer = Scene14::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene14::init() {
    alreadyPopped = false;
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
    script = Json_getItem(chapterScript, "Scene14");
    
	auto bkgd = Sprite::create(POSTOPBKGD);
	bkgd->setPosition(center);
	bkgd->setScale(w / bkgd->getContentSize().width,
                   h / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);
	
	auto doc = Sprite::create(postdoc);
    doc->setPosition(Vec2(origin.x + w * 0.16,
                          origin.y + h * 0.37)
                     );
    doc->setScale(0.8*h / doc->getContentSize().height,
                  0.8*h / doc->getContentSize().height);
	this->addChild(doc, 1);
	
	auto iv = Sprite::create(postIV);
    iv->setPosition(Vec2(origin.x + w * 0.67,
                         origin.y + h * 0.55)
                    );
    iv->setScale(0.56*h / iv->getContentSize().height,
                 0.56*h / iv->getContentSize().height);
	this->addChild(iv, 1);
	
	auto chair = Sprite::create(postchair);
	
    chair->setPosition(Vec2(origin.x + w * 0.83,
                            origin.y + h * 0.35)
                       );
	chair->setScale(0.35*h / chair->getContentSize().height,
                    0.35*h / chair->getContentSize().height);
	this->addChild(chair, 2);
	
	auto mom = Sprite::create(postmom);
	
    mom->setPosition(Vec2(origin.x + w * 0.8,
                          origin.y + h * 0.35)
                     );
	mom->setScale(0.65*h / mom->getContentSize().height,
                  0.65*h / mom->getContentSize().height);
	this->addChild(mom, 3);

	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
	FrameNav frameNav;
	frameNav.addFrameNav(this);
    frameNav.bkgdMusic(4);

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene14::gotoNextScene, this)
	);
    auto isDebug = def->getBoolForKey("IsDebug", false);
    
    if (!isDebug) {
        nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                    visibleSize.height* SCALEY1 + origin.y));
    }
    else
    {
        bool tempDone = def->getBoolForKey("Scene14Done", true);
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
		CC_CALLBACK_1(Scene14::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);
    
    auto nextPage = MenuItemImage::create(
        PAGEFWD,
        PAGEFWD,
        CC_CALLBACK_1(Scene14::nextText, this)
    );
    nextPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.845 + origin.x,
                                visibleSize.height* SCALEY1 * 2.49 + origin.y));

    nextPage->setScale(0.15*w / nextPage->getContentSize().width,
                       0.2*h / nextPage->getContentSize().height);
    
    auto prevPage = MenuItemImage::create(
        PAGEBWD,
        PAGEBWD,
        CC_CALLBACK_1(Scene14::prevText, this)
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

    auto textString1 = Json_getString(script, "14.1", "Go Gators!");
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.55);
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

// Callback function to move on to the next scene
void Scene14::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene15::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move on to the previous scene
void Scene14::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene13::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void Scene14::popsicleCallBack(float dt){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    UserDefault * def = UserDefault::getInstance();
    def->setBoolForKey("Scene14Done", true);
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto clipboard = MenuItemImage::create(
                                           TRYPOPBUTTON,
                                           TRYPOPBUTTON,
                                           CC_CALLBACK_1(Scene14::gotoPopsicleCallback, this));
    clipboard->setScale(0.24*visibleSize.width / clipboard->getContentSize().width,
                        0.2*visibleSize.height / clipboard->getContentSize().height);
    clipboard->setPosition(Vec2(0.5*visibleSize.width,
                                0.45*visibleSize.height));
    auto poplabel = Label::createWithTTF("Try Your \nPopsicle!", BLACK, visibleSize.height * TEXTSIZE*0.9);
    auto popText = MenuItemLabel::create(poplabel, CC_CALLBACK_1(Scene14::gotoPopsicleCallback, this));
    popText->setPosition(Vec2(0.49*visibleSize.width,
                              0.455*visibleSize.height));
    
    auto braceletMenu = Menu::create(clipboard, popText, NULL);
    braceletMenu->setOpacityModifyRGB(0);
    braceletMenu->setPosition(origin.x, origin.y);
    
    this->addChild(braceletMenu, 2); // Please note that the one must be there
    
    braceletMenu->runAction(Spawn::create(FadeIn::create(0.2),
                                          ScaleBy::create(0.2, 1.1),
                                          EaseBounceOut::create(MoveBy::create(0.6,Vec2(0,-0.05*visibleSize.height))), nullptr));
    
};

// Callback function to move to the popsicle scene
void Scene14::gotoPopsicleCallback(Ref* pSender) {
    auto nextScene = Popsicle::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.8, nextScene));
};

void Scene14::nextText(Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    this->textBox->removeAllChildren();
    auto textString1 = Json_getString(script, "14.2", "Go Gators!");
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.57);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.45*textBox->getContentSize().height));
    boxText->setColor(cocos2d::Color3B::BLACK);
    boxText->setAlignment(TextHAlignment::CENTER);
    
    this->textBox->addChild(boxText, 1);
    if(alreadyPopped == false)
    {
        this->scheduleOnce(schedule_selector(Scene14::popsicleCallBack), 0);
        alreadyPopped = true;
    }
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto prevPage = this->menu->getChildren().at(3);
    prevPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
    auto nextPage = this->menu->getChildren().at(2);
    nextPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
}

void Scene14::prevText(Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->textBox->removeAllChildren();
    auto textString2 = Json_getString(script, "14.1", "Go Gators!");
    
    auto boxText1 = Label::createWithTTF(textString2, BOLD, visibleSize.height * TEXTSIZE*0.55);
    boxText1->setDimensions(0.9*textBox->getContentSize().width,
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
