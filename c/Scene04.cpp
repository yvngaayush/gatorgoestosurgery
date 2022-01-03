#include "Scene04.h"
#include "Scene06.h"
#include "Scene02.h"
#include "FrameNav.h"
#include "editor-support/spine/Json.h"
#include "PuzzleScene.h"

Scene* Scene04::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	//create an instance of our Scene04 class that inherits from Layer class
	auto layer = Scene04::create();

	// Add layer to our scene
	scene->addChild(layer);

	// scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool Scene04::init() {

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

	auto bkgd = Sprite::create(WAITINGBKGD);
	bkgd->setAnchorPoint(Vec2(0, 0));
	bkgd->setPosition(Vec2(origin.x, origin.y));
	bkgd->setScale(visibleSize.width / bkgd->getContentSize().width,
				   visibleSize.height / bkgd->getContentSize().height);
	this->addChild(bkgd);
    
    auto textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                              0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                      0.2*visibleSize.height / textBox->getContentSize().height);
    this->addChild(textBox, FRAMEDRAW + 1);

    // Scripts
    UserDefault* def = UserDefault::getInstance();
    def->setIntegerForKey("CURRENTCHAPTER", 2);
    def->setBoolForKey("Bounced", false);
    auto language = def->getStringForKey("LANGUAGE", "English");
    def->flush();
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, language.c_str()); //convert string to const char
    script = Json_getItem(chapterScript, "Scene04");
    
	// ************** Menu Items for Scene **************

	// Adds home button and volume control to the scene
	FrameNav frameNav;
	frameNav.addFrameNav(this);
    frameNav.bkgdMusic(1);

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		MOVEFWD,
		MOVEFWD,
		CC_CALLBACK_1(Scene04::gotoNextScene, this)
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
    
    auto Scene4Done = def->getBoolForKey("Scene4Done");
    if (Scene4Done){
        nextScene->setPosition(Vec2(visibleSize.width * SCALEX2 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    }
    else{
        nextScene->setPosition(Vec2(-1*visibleSize.width * SCALEX2 + origin.x,
                                    -1*visibleSize.height* SCALEY1 + origin.y));
    }
    
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);
    nextScene->setScale(0.09*w / nextScene->getContentSize().width,
                        0.1*h / nextScene->getContentSize().height);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		MOVEBWD,
		MOVEBWD,
		CC_CALLBACK_1(Scene04::gotoPreviousScene, this)
	);
    prevScene->setPosition(Vec2(visibleSize.width * SCALEX1 + origin.x,
                                visibleSize.height* SCALEY1 + origin.y));
    prevScene->setScale(0.09*w / prevScene->getContentSize().width,
                        0.1*h / prevScene->getContentSize().height);
    
    auto nextPage = MenuItemImage::create(
        PAGEFWD,
        PAGEFWD,
        CC_CALLBACK_1(Scene04::nextText, this)
    );
    auto puzzled2 = def->getBoolForKey("PUZZLED", false);
    
    nextPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.845 + origin.x,
                                visibleSize.height* SCALEY1 * 2.49 + origin.y));

    nextPage->setScale(0.15*w / nextPage->getContentSize().width,
                       0.2*h / nextPage->getContentSize().height);
    
    auto prevPage = MenuItemImage::create(
        PAGEBWD,
        PAGEBWD,
        CC_CALLBACK_1(Scene04::prevText, this)
    );
    prevPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x,
                                visibleSize.height* SCALEY1 * 2.49 + origin.y));

    prevPage->setScale(0.15*w / nextPage->getContentSize().width,
                        0.2*h / nextPage->getContentSize().height);
    
    if (puzzled2 == true)
    {
        nextPage->setOpacity(0);
        prevPage->setOpacity(0);
    }
    else
    {
        nextPage->setOpacity(255);
        prevPage->setOpacity(255);
    }

	// Create the menu
	menu = Menu::create(nextScene, prevScene,nextPage, prevPage, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there
    
    this->scheduleOnce(schedule_selector(Scene04::textAppears), 0);

	return true;
}

void Scene04::gameButtonCallBack(float dt){
    
    // Get size of the window being displayed to
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    UserDefault* def = UserDefault::getInstance();
    auto temp = def->getBoolForKey("Bounced", false);
    if(temp == false){
        auto clipboard = MenuItemImage::create(
                                               GAMEBUTTON04,
                                               GAMEBUTTON04,
                                               CC_CALLBACK_1(Scene04::gotoGameCallback, this));
        clipboard->setScale(0.17*visibleSize.width / clipboard->getContentSize().width,
                            0.18*visibleSize.width / clipboard->getContentSize().width);
        clipboard->setPosition(Vec2(0.5*visibleSize.width,
                                    0.5*visibleSize.height));
        auto playlabel = Label::createWithTTF("Play", BLACK, visibleSize.height * TEXTSIZE*1.5);
        auto playText = MenuItemLabel::create(playlabel, CC_CALLBACK_1(Scene04::gotoGameCallback, this));
        playText->setPosition(Vec2(0.5*visibleSize.width,
                                   0.505*visibleSize.height));
        
        auto braceletMenu = Menu::create(clipboard, playText, NULL);
        braceletMenu->setOpacityModifyRGB(0);
        braceletMenu->setPosition(origin.x, origin.y);
        
        this->addChild(braceletMenu, 2); // Please note that the one must be there
    braceletMenu->runAction(Spawn::create(FadeIn::create(0.2),
                                          ScaleBy::create(0.2, 1.1),
                                          EaseBounceOut::create(MoveBy::create(0.6,Vec2(0,-0.05*visibleSize.height))), nullptr));}
    def->setBoolForKey("Bounced", true);
    def->flush();
};
bool tempPuzz = false;
void Scene04::textAppears(float dt)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    UserDefault * def = UserDefault::getInstance();
    auto puzzled = def->getBoolForKey("PUZZLED", false);
    
    if (!puzzled) {
        
        //// get text from json script object
        
        this->textBox = Sprite::create(TEXTBOX);
        
        textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                               0.15*visibleSize.height + origin.y));
        textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                       0.2*visibleSize.height / textBox->getContentSize().height);

        auto textString1 = Json_getString(script, "4.1", "Go Gators!");
        
        auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.65);
        boxText->setDimensions(0.9*textBox->getContentSize().width,
                                   0.85*textBox->getContentSize().height);
        boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.4*textBox->getContentSize().height));
        boxText->setColor(cocos2d::Color3B::BLACK);
        boxText->setAlignment(TextHAlignment::CENTER);
        
        textBox->addChild(boxText, 1);
        tempPuzz = false;
        
        this->addChild(textBox, FRAMEDRAW + 5);
        
    } else {
        def->setBoolForKey("PUZZLED", false);
        def->flush();
        tempPuzz = true;
        this->textBox = Sprite::create(TEXTBOX);
        
        textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                               0.15*visibleSize.height + origin.y));
        textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                       0.2*visibleSize.height / textBox->getContentSize().height);

        auto textString1 = Json_getString(script, "4.4", "Go Gators!");
        
        auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.75);
        boxText->setDimensions(0.9*textBox->getContentSize().width,
                                   1*textBox->getContentSize().height);
        boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                      0.5*textBox->getContentSize().height));
        boxText->setColor(cocos2d::Color3B::BLACK);
        boxText->setAlignment(TextHAlignment::CENTER);
        
        textBox->addChild(boxText, 1);
        
        this->addChild(textBox, FRAMEDRAW + 5);
        
    }
}

// Callback function to move on to the next scene
void Scene04::gotoNextScene(Ref* pSender) {
	auto nextScene = Scene06::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move on to the previous scene
void Scene04::gotoPreviousScene(Ref* pSender) {
	auto nextScene = Scene02::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move to the puzzle game scene
void Scene04::gotoGameCallback(Ref* pSender) {
	auto nextScene = PuzzleScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
};

void Scene04::waitNextScene(float dt) {
    auto nextScene = Scene06::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
    
}

void Scene04::nextText(Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    if (!tempPuzz) {
    this->textBox->removeAllChildren();
    auto textString1 = Json_getString(script, "4.2", "Go Gators!");
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.65);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.4*textBox->getContentSize().height));
    boxText->setColor(cocos2d::Color3B::BLACK);
    boxText->setAlignment(TextHAlignment::CENTER);
    
    this->textBox->addChild(boxText, 1);
    this->scheduleOnce(schedule_selector(Scene04::gameButtonCallBack), 0);
    
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        auto prevPage = this->menu->getChildren().at(3);
        prevPage->setPosition(Vec2(visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
        auto nextPage = this->menu->getChildren().at(2);
        nextPage->setPosition(Vec2(-1*visibleSize.width * SCALEX2 * 0.22 + origin.x, visibleSize.height* SCALEY1 * 2.49 + origin.y));
    }
}

void Scene04::prevText(Ref* pSender) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    if (!tempPuzz) {
    this->textBox->removeAllChildren();
    auto textString2 = Json_getString(script, "4.1", "Go Gators!");
    
    auto boxText1 = Label::createWithTTF(textString2, BOLD, visibleSize.height * TEXTSIZE*0.65);
    boxText1->setDimensions(0.9*textBox->getContentSize().width,
                               0.85*textBox->getContentSize().height);
    boxText1->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.4*textBox->getContentSize().height));
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
}
