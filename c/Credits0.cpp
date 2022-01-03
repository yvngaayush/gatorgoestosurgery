#include "LaunchScreen.h"
#include "MainMenu.h"
#include "Credits0.h"
#include "editor-support/spine/Json.h"
#include "FrameNav.h"

Scene* Credits::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene01 class that inherits from Layer class
	auto layer = Credits::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Credits::init() {

	// Ensure layer from createScene() was created
	if (!Layer::init()) {
		return false;
	}

	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    FrameNav fn;
    fn.bkgdMusic(0);

    auto center = Vec2(0.5*visibleSize.width + origin.x,
                       0.5*visibleSize.height + origin.y);
    auto w = visibleSize.width;
    auto h = visibleSize.height;
    
    auto bkgd = MenuItemImage::create(
                                      S15BKGD,
                                      S15BKGD,
                                      CC_CALLBACK_1(Credits::gotoNextScene, this)
                                      );
    
	bkgd->setScale(w / bkgd->getContentSize().width,
                   h / bkgd->getContentSize().height);
    auto menu = Menu::create(bkgd, NULL);
    menu->setPosition(center);
    this->addChild(menu, -1);

    auto textBox = Sprite::create(TEXTBOX);
    textBox->setPosition(Vec2(origin.x + visibleSize.width/2,
                              origin.y + visibleSize.height/1.9));
    textBox->setScale(0.8*visibleSize.width / textBox->getContentSize().width,
                      0.4*visibleSize.height / textBox->getContentSize().height);
    
    UserDefault* def = UserDefault::getInstance();
    auto language = def->getStringForKey("LANGUAGE", "English");
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    auto script = Json_getItem(chapterScript, "Credits");
    
    auto textString1 = Json_getString(script, "Credits.1", "Go Gators!");

    auto creditsText1 = Label::createWithTTF(textString1, BLACK, visibleSize.height * TEXTSIZE*0.5);
//    creditsText1->setDimensions(0.5*w,
//                               0.5*textBox->getContentSize().height);
    creditsText1->setPosition(Vec2(0.3*w,
                                  0.66*h));
    creditsText1->setColor(cocos2d::Color3B::BLACK);
    creditsText1->setAlignment(TextHAlignment::LEFT);
    
    this->addChild(creditsText1, (FRAMEDRAW + 1));
    
    auto textString2 = Json_getString(script, "Credits.2", "Go Gators!");
    auto creditsText2 = Label::createWithTTF(textString2, LIGHT, visibleSize.height * TEXTSIZE * 0.8);
    creditsText2->setPosition(Vec2(0.315*w,
                                   0.61*h));
    creditsText2->setColor(cocos2d::Color3B::BLACK);
//    creditsText2->setAlignment(TextHAlignment::LEFT);
    
    this->addChild(creditsText2, (FRAMEDRAW + 1));
    
    auto textString3 = Json_getString(script, "Credits.3", "Go Gators!");
    auto creditsText3 = Label::createWithTTF(textString3, LIGHT, visibleSize.height * TEXTSIZE*0.5);
    creditsText3->setPosition(Vec2(0.3275*w,
                                   0.58*h));
    creditsText3->setColor(cocos2d::Color3B::BLACK);
//    creditsText3->setAlignment(TextHAlignment::LEFT);

    this->addChild(creditsText3, (FRAMEDRAW + 1));
    
    auto textString4 = Json_getString(script, "Credits.4", "Go Gators!");
    auto creditsText4 = Label::createWithTTF(textString4, BLACK, visibleSize.height * TEXTSIZE*0.5);
    creditsText4->setPosition(Vec2(0.235*w,
                                  0.5*h));
    creditsText4->setColor(cocos2d::Color3B::BLACK);

    this->addChild(creditsText4, (FRAMEDRAW + 1));
    
    auto textString5 = Json_getString(script, "Credits.5", "Go Gators!");
    auto creditsText5 = Label::createWithTTF(textString5, LIGHT, visibleSize.height * TEXTSIZE * 0.8);
    creditsText5->setPosition(Vec2(0.235*w,
                                   0.45*h));
    creditsText5->setColor(cocos2d::Color3B::BLACK);
//    creditsText2->setAlignment(TextHAlignment::LEFT);
    
    this->addChild(creditsText5, (FRAMEDRAW + 1));
    
    auto textString6 = Json_getString(script, "Credits.6", "Go Gators!");
    auto creditsText6 = Label::createWithTTF(textString6, LIGHT, visibleSize.height * TEXTSIZE * 0.8);
    creditsText6->setPosition(Vec2(0.2475*w,
                                   0.42*h));
    creditsText6->setColor(cocos2d::Color3B::BLACK);
//    creditsText2->setAlignment(TextHAlignment::LEFT);
    
    this->addChild(creditsText6, (FRAMEDRAW + 1));
    
    auto textString7 = Json_getString(script, "Credits.7", "Go Gators!");
    auto creditsText7 = Label::createWithTTF(textString7, LIGHT, visibleSize.height * TEXTSIZE*0.5);
    creditsText7->setPosition(Vec2(0.375*w,
                                   0.45*h));
    creditsText7->setColor(cocos2d::Color3B::BLACK);
    this->addChild(creditsText7, (FRAMEDRAW + 1));
    
    auto textString8 = Json_getString(script, "Credits.8", "Go Gators!");
    auto creditsText8 = Label::createWithTTF(textString8, LIGHT, visibleSize.height * TEXTSIZE*0.5);
    creditsText8->setPosition(Vec2(0.41*w,
                                   0.42*h));
    creditsText8->setColor(cocos2d::Color3B::BLACK);
    this->addChild(creditsText8, (FRAMEDRAW + 1));
    
    auto textString9 = Json_getString(script, "Credits.9", "Go Gators!");
    auto creditsText9 = Label::createWithTTF(textString9, BLACK, visibleSize.height * TEXTSIZE*0.5);
    creditsText9->setPosition(Vec2(0.66*w,
                                  0.66*h));
    creditsText9->setColor(cocos2d::Color3B::BLACK);
    creditsText9->setAlignment(TextHAlignment::LEFT);
    
    this->addChild(creditsText9, (FRAMEDRAW + 1));
    
    auto textString10 = Json_getString(script, "Credits.10", "Go Gators!");
    auto creditsText10 = Label::createWithTTF(textString10, LIGHT, visibleSize.height * TEXTSIZE * 0.7);
    creditsText10->setDimensions(0.3*w, 0);
    creditsText10->setPosition(Vec2(0.695*w,
                                   0.54*h));
    creditsText10->setColor(cocos2d::Color3B::BLACK);
//    creditsText2->setAlignment(TextHAlignment::LEFT);
    
    this->addChild(creditsText10, (FRAMEDRAW + 1));
    
    auto textString11 = Json_getString(script, "Credits.11", "Go Gators!");
    auto creditsText11 = Label::createWithTTF(textString11, LIGHT, visibleSize.height * TEXTSIZE*0.5);
    creditsText11->setPosition(Vec2(0.605*w,
                                   0.42*h));
    creditsText11->setColor(cocos2d::Color3B::BLACK);
    this->addChild(creditsText11, (FRAMEDRAW + 1));
    
    
    this->addChild(textBox, FRAMEDRAW);
    
    //this->scheduleOnce(schedule_selector(Credits::gotoMenu), 9);
    return true;
}

// Callback function to move on to the next scene
void Credits::gotoNextScene(Ref* pSender) {
	auto nextScene = MainMenu::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void Credits::gotoMenu(float dt) {
    auto nextScene = MainMenu::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
    
}
