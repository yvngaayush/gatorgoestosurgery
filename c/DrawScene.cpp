#include "Scene04.h"
#include "Scene02.h"
#include "DrawScene.h"
#include "FrameNav.h"
#include "ResourceDefinitions.h"
#include "editor-support/spine/Json.h"

Scene* DrawScene::createScene() {

	// Create a scene object
	auto scene = Scene::create();

	// Create an instance of our DrawScene class that inherits from layer class
	auto layer = DrawScene::create();

	// Add layer to our scene
	scene->addChild(layer);

	// Scene passed to AppDelegate to run in Director->runScene();
	return scene;
}

bool DrawScene::init() {
    
    UserDefault* def = UserDefault::getInstance();
    
	// Ensure layer from createScene() was created
	if (!Layer::init()) {
		return false;
	}

	// Scripts
	def->setIntegerForKey("CURRENTCHAPTER", 2);
	auto language = def->getStringForKey("LANGUAGE", "English");
	def->flush();

	auto scriptString = cocos2d::__String::createWithContentsOfFile(SCRIPT);
	auto fullScript = Json_create(scriptString->getCString());
	auto chapterScript = Json_getItem(fullScript, "English"); // fixed - had funky " marks
	script = Json_getItem(chapterScript, "Scene02");

	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto center = Vec2(0.5*visibleSize.width + origin.x,
                       0.5*visibleSize.height + origin.y);
    auto w = visibleSize.width;
    auto h = visibleSize.height;

	auto bkgd = Sprite::create(DRAWBACKGROUND);
	bkgd->setAnchorPoint(Vec2(0, 0));
	bkgd->setPosition(Vec2(origin.x, origin.y));
	bkgd->setScale(visibleSize.width / bkgd->getContentSize().width,
				   visibleSize.height / bkgd->getContentSize().height);
	this->addChild(bkgd);

    // Adds home button and volume control to the scene
    FrameNav frameNav;
    frameNav.addFrameNav(this); // Addling layer to scene
    frameNav.bkgdMusic(1);
    
    
    this->textBox = Sprite::create(TEXTBOX);
    
    textBox->setPosition(Vec2(0.5*visibleSize.width + origin.x,
                           0.15*visibleSize.height + origin.y));
    textBox->setScale(0.6*visibleSize.width / textBox->getContentSize().width,
                   0.2*visibleSize.height / textBox->getContentSize().height);

    auto textString1 = Json_getString(script, "2.3", "Go Gators!");
    
    auto boxText = Label::createWithTTF(textString1, BOLD, visibleSize.height * TEXTSIZE*0.75);
    boxText->setDimensions(0.9*textBox->getContentSize().width,
                               0.75*textBox->getContentSize().height);
    boxText->setPosition(Vec2(0.5*textBox->getContentSize().width,
                                  0.5*textBox->getContentSize().height));
    boxText->setColor(cocos2d::Color3B::BLACK);
    boxText->setAlignment(TextHAlignment::CENTER);
    
    textBox->addChild(boxText, 1);
    
    this->addChild(textBox, FRAMEDRAW + 5);
                                      
	// ************** Menu Items for Scene **************

	// Menu Item to go to next scene
	auto nextScene = MenuItemImage::create(
		DONEBUTTON,
		DONEBUTTON,
		CC_CALLBACK_1(DrawScene::gotoNextScene, this)
	);
	nextScene->setPosition(Vec2(visibleSize.width * 0.91 + origin.x,
								visibleSize.height * 0.08 + origin.y));
    nextScene->setScale(0.15*w / nextScene->getContentSize().width,
                        0.15*w / nextScene->getContentSize().width);

	// Menu Item to go to previous scene
	auto prevScene = MenuItemImage::create(
		BACKBUTTON,
		BACKBUTTON,
		CC_CALLBACK_1(DrawScene::gotoPreviousScene, this)
	);
	prevScene->setPosition(Vec2(visibleSize.width * 0.09 + origin.x,
								visibleSize.height * 0.08 + origin.y));
    prevScene->setScale(0.15*w / prevScene->getContentSize().width,
                        0.15*w / prevScene->getContentSize().width);

	// Create the menu
	auto menu = Menu::create(nextScene, prevScene, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there
    

	// ************** Draw Stuff for Scene **************
    
    auto clearButton = Sprite::create(STARTBUTTON);
    clearButton->setPosition(Vec2(visibleSize.width * 0.5 + origin.x,
                                visibleSize.height * 0.89 + origin.y));
    clearButton->setScale(0.12 * w / clearButton->getContentSize().width,
                   0.12 * w / clearButton->getContentSize().width);
    
    auto listenClear = EventListenerTouchOneByOne::create();
    listenClear->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto clearBox = clearButton->getBoundingBox();
        if (clearBox.containsPoint(touch->getLocation())) {
            CCDirector::sharedDirector()->replaceScene(DrawScene::createScene()); return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenClear, clearButton);
    this->addChild(clearButton, (FRAMEDRAW+1));
    
    auto clearText = Label::createWithTTF("Clear", BLACK, visibleSize.height * TEXTSIZE*1.2);
    clearText->setPosition(Vec2(visibleSize.width * 0.495 + origin.x,
                                  visibleSize.height * 0.89 + origin.y));
    this->addChild(clearText, (FRAMEDRAW+2));
    
	float dotScaleX = 0.14;
    
	auto orangeDot = Sprite::create(ORANGEDOT);
	orangeDot->setPosition(
		Vec2(
			origin.x + visibleSize.width * dotScaleX,
			origin.y + visibleSize.height * 0.38)
	);
	orangeDot->setScale(w * 1.2 / bkgd->getContentSize().width, h * 1.2 / bkgd->getContentSize().height);
	auto listenOrange = EventListenerTouchOneByOne::create();
	listenOrange->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
		auto orangeBox = event->getCurrentTarget()->getBoundingBox();
		if (orangeBox.containsPoint(touch->getLocation())) {
			setInkColor(1); return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenOrange, orangeDot);
	this->addChild(orangeDot, (FRAMEDRAW + 2));
	
	auto yellowDot = Sprite::create(YELLOWDOT);
	yellowDot->setPosition(
		Vec2(
			origin.x + visibleSize.width * dotScaleX,
			origin.y + visibleSize.height * 0.47)
	);
	yellowDot->setScale(w * 1.2 / bkgd->getContentSize().width, h * 1.2 / bkgd->getContentSize().height);
	auto listenYellow = EventListenerTouchOneByOne::create();
	listenYellow->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
		auto yellowBox = event->getCurrentTarget()->getBoundingBox();
		if (yellowBox.containsPoint(touch->getLocation())) {
			setInkColor(2); return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenYellow, yellowDot);
	this->addChild(yellowDot, (FRAMEDRAW + 2));
	
	auto blueDot = Sprite::create(BLUEDOT);
	blueDot->setPosition(
		Vec2(
			origin.x + visibleSize.width * dotScaleX,
			origin.y + visibleSize.height * 0.56)
	);
	blueDot->setScale(w * 1.2 / bkgd->getContentSize().width, h * 1.2 / bkgd->getContentSize().height);
	auto listenBlue = EventListenerTouchOneByOne::create();
	listenBlue->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
		auto blueBox = event->getCurrentTarget()->getBoundingBox();
		if (blueBox.containsPoint(touch->getLocation())) {
			setInkColor(3); return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenBlue, blueDot);
	this->addChild(blueDot, (FRAMEDRAW + 2));

	auto redDot = Sprite::create(REDDOT);
	redDot->setPosition(
		Vec2(
			origin.x + visibleSize.width * dotScaleX,
			origin.y + visibleSize.height * 0.65)
	);
	redDot->setScale(w * 1.2 / bkgd->getContentSize().width, h * 1.2 / bkgd->getContentSize().height);
	auto listenRed = EventListenerTouchOneByOne::create();
	listenRed->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
		auto redBox = event->getCurrentTarget()->getBoundingBox();
		if (redBox.containsPoint(touch->getLocation())) {
			setInkColor(4); return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenRed, redDot);
	this->addChild(redDot, (FRAMEDRAW + 2));

	auto greenDot = Sprite::create(GREENDOT);
	greenDot->setPosition(
		Vec2(
			origin.x + visibleSize.width * dotScaleX,
			origin.y + visibleSize.height * 0.74)
	);
	greenDot->setScale(w * 1.2 / bkgd->getContentSize().width, h * 1.2 / bkgd->getContentSize().height);
	auto listenGreen = EventListenerTouchOneByOne::create();
	listenGreen->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
		auto greenBox = event->getCurrentTarget()->getBoundingBox();
		if (greenBox.containsPoint(touch->getLocation())) {
			setInkColor(5); return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenGreen, greenDot);
	this->addChild(greenDot, (FRAMEDRAW + 2));
	
	// Create pen that will be used to draw name 
	// (not actual pen just acts like one)
    auto pen = DrawNode::create();
    this->addChild(pen);
    
    auto listener = EventListenerTouchOneByOne::create();

    

    //listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *event){

        auto pos = touch->getLocation();

        // Should probably disallow drawing outside of the nametag...
//        CCPoint touchLocation = this->convertTouchToNodeSpace(touch);
//        CCLOG("Touch: %f %f", touchLocation.x/w, touchLocation.y/h);

		// Update color
		if (prevColor != curColor) {
			pen->updateDisplayedColor(Color3B(curColor));
		};


        if (pos.x < w * 0.1 || pos.x > w * 0.9 || pos.y > h * 0.800 || pos.y < h * 0.300 ||
            orangeDot->getBoundingBox().containsPoint(touch->getLocation()) ||
            yellowDot->getBoundingBox().containsPoint(touch->getLocation()) ||
            blueDot->getBoundingBox().containsPoint(touch->getLocation()) ||
            redDot->getBoundingBox().containsPoint(touch->getLocation()) ||
            greenDot->getBoundingBox().containsPoint(touch->getLocation()))
        {

        }
        else
        {
            pen->drawSolidCircle(
                Vec2(pos.x, pos.y),
                DRAWSCENEBRUSHSIZE * visibleSize.width,
                360,
                12,
                curColor);
        }

        return true;
    };
    

    listener->onTouchMoved = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        auto pos = touch->getLocation();
        
        auto start = touch->getLocation();
        //start = Director::getInstance()->convertToGL(start);
        auto end = touch->getPreviousLocation();
        //end = Director::getInstance()->convertToGL(end);
        
        float distance = start.getDistance(end);
        
        if (pos.x < w * 0.1 || pos.x > w * 0.9 || pos.y > h * 0.800 || pos.y < h * 0.300 || orangeDot->getBoundingBox().containsPoint(touch->getLocation()) ||
            yellowDot->getBoundingBox().containsPoint(touch->getLocation()) ||
            blueDot->getBoundingBox().containsPoint(touch->getLocation()) ||
            redDot->getBoundingBox().containsPoint(touch->getLocation()) ||
            greenDot->getBoundingBox().containsPoint(touch->getLocation()))
        {

        }
        else
        {
            if (distance > 1)
            {
                int d = (int)distance;
                for (float i = 0; i < d; i = i + 0.5)
                {
                    float difx = end.x - start.x;
                    float dify = end.y - start.y;
                    float delta = (float)i / distance;
                    pen->drawSolidCircle(
                        Vec2(start.x + (difx * delta), start.y + (dify * delta)),
                        DRAWSCENEBRUSHSIZE * visibleSize.width,
                        360,
                        12,
                        curColor);
                }
            }
        }

        return true;
    };

    listener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event){

        return true;

    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
	return true;
};


// Callback function to move on to the next scene
void DrawScene::gotoNextScene(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();
    def->setBoolForKey("Scene2Done", true);
	auto nextScene = Scene04::createScene();
	//Director::getInstance()->replaceScene(nextScene);
    Director::getInstance()->pushScene(TransitionFade::create(0.5,nextScene));
}

// Callback function to move on to the previous scene
void DrawScene::gotoPreviousScene(Ref* pSender) {
    auto previousScene = Scene02::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,previousScene));
}

void DrawScene::setInkColor(int colorVal) {
	switch (colorVal) {
	// orange
	case 1: { this->prevColor = this->curColor; this->curColor = Color4F(Color4B(234, 156, 101, 255)); break; }
	// yellow
    case 2: { this->prevColor = this->curColor; this->curColor = Color4F(Color4B(246, 231, 144, 255)); break; }
	// blue
	case 3: { this->prevColor = this->curColor; this->curColor = Color4F(Color4B(95, 192, 216, 255)); break; }
	// red
	case 4: { this->prevColor = this->curColor; this->curColor = Color4F(Color4B(202, 58, 91, 255)); break; }
	// green
	case 5: { this->prevColor = this->curColor; this->curColor = Color4F(Color4B(75, 168, 155, 255)); break; }
	}
};
