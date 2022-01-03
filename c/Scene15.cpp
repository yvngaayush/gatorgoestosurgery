#include "Scene15.h"
#include "MainMenu.h"
#include "Scene14.h"
#include "editor-support/spine/Json.h"


Scene* Scene15::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene15 class that inherits from Layer class
	auto layer = Scene15::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene15::init() {

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
    script = Json_getItem(chapterScript, "Scene15");
    
	auto bkgd = Sprite::create(S15BKGD);
	bkgd->setPosition(center);
	bkgd->setScale(
		w / bkgd->getContentSize().width,
		h / bkgd->getContentSize().height);
	this->addChild(bkgd, -1);

	// Text bubble for iSPY game (i.e. how many stars found)
	auto tbubble = Sprite::create(bubble);
	tbubble->setPosition(Vec2(
		visibleSize.width * 0.68 + origin.x,
		visibleSize.height * 0.4 + origin.y)); // Vec2(1500,450)
	tbubble->setScale(
		visibleSize.width / bkgd->getContentSize().width,
		visibleSize.height / bkgd->getContentSize().height);
	this->addChild(tbubble, 1);

	auto Confetti = Sprite::create(confetti);
	Confetti->setPosition(Vec2(
		visibleSize.width * 0.68 + origin.x,
		visibleSize.height * 0.4 + origin.y)); // Vec2(1500,850)
	Confetti->setScale(
		visibleSize.width / bkgd->getContentSize().width,
		visibleSize.height / bkgd->getContentSize().height);
	this->addChild(Confetti, 2);
	
	// This is the thank you message box and text
	auto ty = Sprite::create(thankyou);
	ty->setPosition(Vec2(
		visibleSize.width * 0.68 + origin.x,
		visibleSize.height * 0.65 + origin.y)); // Vec2(1500,1300)
	ty->setScale(
		visibleSize.width / bkgd->getContentSize().width,
		visibleSize.height / bkgd->getContentSize().height);
	this->addChild(ty);
	

	// Gator patient giving the thumbs up
	auto gator = Sprite::create(depgator);
	gator->setPosition(Vec2(
		visibleSize.width * 0.26 + origin.x,
		visibleSize.height * 0.42 + origin.y));
	gator->setScale(
		visibleSize.width / bkgd->getContentSize().width,
		visibleSize.height / bkgd->getContentSize().height);
	this->addChild(gator);

	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
	FrameNav temp;
	temp.addFrameNav(this);
	temp.createIconBar(this);
	temp.toggleIconBar(ISPYTAG, this);
	this->frameNav = &temp;
    this->frameNav->bkgdMusic(4);

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene15::gotoNextScene, this)
	);
    auto isDebug = def->getBoolForKey("IsDebug", false);
    
    if (!isDebug) {
        nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                    visibleSize.height* SCALEY1 + origin.y));
    }
    else
    {
        nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                    visibleSize.height* SCALEY1 + origin.y));
    }
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(Scene15::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);

	// Create the menu
	auto menu = Menu::create(nextScene, prevScene, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there

	// ************** ISPY Game Logic **************
	/*
	counter = 0;
	UserDefault * def = UserDefault::getInstance();
    
    if  (def->getBoolForKey("ISPYBPFOUND", false)) {counter++;}
    if  (def->getBoolForKey("ISPYNAMEFOUND", false)) {counter++;}
    if  (def->getBoolForKey("ISPYMASKFOUND", false)) {counter++;}
    if  (def->getBoolForKey("ISPYPULSEOXFOUND", false)) {counter++;}
    if  (def->getBoolForKey("ISPYELECFOUND", false)) {counter++;}
    if  (def->getBoolForKey("ISPYSMOCKFOUND", false)) {counter++;}
    if  (def->getBoolForKey("ISPYTHERMOFOUND", false)) {counter++;}
	*/

	int counter = temp.getIconFound();
	std::string str = std::to_string(counter);

	// This part draws the actual number in the red box
	auto iSpyCounter = Label::createWithTTF(str, COUNTERFONT, 0.15*visibleSize.height);
	iSpyCounter->setPosition(Vec2(
								visibleSize.width * 0.63 + origin.x,
								visibleSize.height * 0.39 + origin.y));
	this->addChild(iSpyCounter, FRAMEDRAW);

	
	// **** This part draw's the "star" word in plural or singular ****
    // In case of multiple stars
    if (counter>1){
        auto iSpyCounter2 = Label::createWithTTF(
										"stars!",
										COUNTERFONT,
										0.04*visibleSize.height);
        iSpyCounter2->setPosition(Vec2(
										visibleSize.width * 0.73 + origin.x,
										visibleSize.height * 0.31 + origin.y));
        this->addChild(iSpyCounter2, FRAMEDRAW);

	// In case of one star
    } else if (counter==1) {
        auto iSpyCounter2 = Label::createWithTTF(
										"star!",
										COUNTERFONT,
										0.04*visibleSize.height);
        iSpyCounter2->setPosition(Vec2(
										visibleSize.width * 0.73 + origin.x,
										visibleSize.height * 0.31 + origin.y));
        this->addChild(iSpyCounter2, FRAMEDRAW);
	// In case of zero stars
    } else {
        auto iSpyCounter2 = Label::createWithTTF(
										"stars",
										COUNTERFONT,
										0.04*visibleSize.height);
        iSpyCounter2->setPosition(Vec2(
										visibleSize.width * 0.73 + origin.x,
										visibleSize.height * 0.31 + origin.y));
        this->addChild(iSpyCounter2, FRAMEDRAW);
    }
	this->scheduleOnce(schedule_selector(Scene15::textAppears), 0.5);
	return true;
}

// Callback function to move on to the next scene
void Scene15::gotoNextScene(Ref* pSender) {
	auto nextScene = MainMenu::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move on to the previous scene
void Scene15::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene14::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

void Scene15::textAppears(float dt)
{
    
    //// get text from json script object
    
    auto textString1 = Json_getString(script, "15.1", "Go Gators!");
    //auto textString2 = Json_getString(script, "15.2", "Go Gators!");
    
    //// set up text
    
    // Added a framenav function so all text displays the same
    
    FrameNav fn;
    auto label1 = fn.createText(textString1, this);
    //auto label2 = fn.createText(textString2, this);
    
    auto appear = FadeIn::create(0.1);
    auto disappear = FadeOut::create(0.1);
    auto delay = DelayTime::create(6);
    
    //label1->runAction(Sequence::create(appear, delay, disappear, nullptr));
    //label2->runAction(Sequence::create(delay, appear, nullptr));
    
}
