#include "FrameNav.h"
#include "MainMenu.h"

using namespace std;

enum {CHLAUNCH, CHWAIT, CHPREOP, CHOR, CHPOSTOP};

// Defining Constructor
FrameNav::FrameNav() {}

// Defining Destructor
FrameNav::~FrameNav() {}

// All this does is create a frame border, Home and Volume button
void FrameNav::addFrameNav(Layer* layer) {

	// Get size of the window being displayed to
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Get drawing origin of screen for sprites
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto center = Vec2(0.5*visibleSize.width + origin.x,
                       0.5*visibleSize.height + origin.y);
    auto w = visibleSize.width;
    auto h = visibleSize.height;

	auto frameframe = Sprite::create(FRAMEFRAME);
	frameframe->setScale(1.05 * visibleSize.width / frameframe->getContentSize().width,
						 1.05 * visibleSize.height / frameframe->getContentSize().height);
	frameframe->setPosition(Vec2(0.5 * visibleSize.width + origin.x, 0.52 * visibleSize.height + origin.y));
	frameframe->setOpacity(128);
	frameframe->setColor(Color3B(20, 40, 150));
	frameframe->setTag(BORDERTAG);
	layer->addChild(frameframe, FRAMEDRAW); // Frame draw == 1000

	
	// ************ Create menu items for the frame ************

	// Menu Item to go to main menu
	auto mainMenuButton = MenuItemImage::create(
		HOMEBUTTON,
		HOMEBUTTON,
		CC_CALLBACK_0(FrameNav::gotoMainMenu, this, layer)
	);

	auto volumeButton = MenuItemImage::create(
		VOLUMEBUTTON,
		VOLUMEBUTTON,
		CC_CALLBACK_1(FrameNav::toggleSound, this, layer)
	);

	// Set position and scale of volume button
	volumeButton->setPosition(Vec2(
									0.95*w + origin.x,
									visibleSize.height * SCALEY2 + origin.y)
	);
	volumeButton->setScale(
							0.08*visibleSize.width / mainMenuButton->getContentSize().width,
							0.08*visibleSize.width / mainMenuButton->getContentSize().width
	);

	// Set position and scale of main menu button
	mainMenuButton->setPosition(Vec2(
									w * 0.045 + origin.x,
									visibleSize.height * SCALEY2 + origin.y));
    mainMenuButton->setScale(0.07*w / mainMenuButton->getContentSize().width,
							 0.07*w / mainMenuButton->getContentSize().width);

	// Create the menu (it's an autorelease object) <----IDK meaning but it is
	auto menu = Menu::create(mainMenuButton, volumeButton, NULL);
	menu->setPosition(Vec2::ANCHOR_MIDDLE);
	layer->addChild(menu, (FRAMEDRAW + 1)); // Please note that the one must be there
}

// Callback function to return to main menu
void FrameNav::gotoMainMenu(Ref* pSender) {
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->stopAllEffects();
    UserDefault* def = UserDefault::getInstance();
    def->setBoolForKey("PUZZLED", false);
    def->flush();

	auto mainMenuScene = MainMenu::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(2, mainMenuScene));
}

// Ghost hint hand to know what you can touch on the scene
void FrameNav::tapScreen(cocos2d::Layer *chapterLayer)
{
	auto tapSprite = Sprite::create(TAPTHESCREEN);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	tapSprite->setPosition(Vec2(visibleSize.width*0.5 + origin.x,
								visibleSize.height*0.5 + origin.y));
	tapSprite->setScale(0.05*visibleSize.width / tapSprite->getContentSize().width,
						0.05*visibleSize.width / tapSprite->getContentSize().height);
	chapterLayer->addChild(tapSprite, 5);
	tapSprite->setOpacity(0);
	tapSprite->runAction(Sequence::create(
									FadeIn::create(0.4),
									DelayTime::create(0.2),
									FadeOut::create(0.4),
									FadeIn::create(0.4),
									DelayTime::create(0.2),
									FadeOut::create(0.4),
									FadeIn::create(0.4),
									DelayTime::create(0.2),
									FadeOut::create(0.4),
									RemoveSelf::create(),
									nullptr));
}


void FrameNav::toggleBorder(int tag, Layer *frameLayer) {
	frameLayer->removeChildByTag(tag);
}

void FrameNav::toggleIconBar(int tag, Layer* frameLayer) {
	frameLayer->removeChildByTag(tag);
}

void FrameNav::setIconFound() {
	this->iconsFound++;
}

int FrameNav::getIconFound() {
	return this->iconsFound++;
}

void FrameNav::createIconBar(Layer* frameLayer) {
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    // ************ Create static frame images ************
    
    // Get drawing origin of screen for sprites
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    UserDefault * def = UserDefault::getInstance();
    
    bool foundIt[7] = {
        def->getBoolForKey("ISPYBPFOUND", false),
        def->getBoolForKey("ISPYNAMEFOUND", false),
        def->getBoolForKey("ISPYMASKFOUND", false),
        def->getBoolForKey("ISPYPULSEOXFOUND", false),
        def->getBoolForKey("ISPYELECFOUND", false),
        def->getBoolForKey("ISPYSMOCKFOUND", false),
        def->getBoolForKey("ISPYTHERMOFOUND", false)
    };
    
    def->flush();
    
    auto iconBar = Sprite::create(ICONBAR); // parent sprite
    iconBar->setTag(ISPYTAG);
    iconBar->setPosition(Vec2(origin.x + visibleSize.width * 0.5,
                              origin.y + visibleSize.height * 0.9));
    iconBar->setScale(0.7*visibleSize.width / iconBar->getContentSize().width,
                      0.7*visibleSize.width / iconBar->getContentSize().width
                      );
    
    const float STARTPOSFACTORX = 0.11;
    const float STARTPOSFACTORY = 0.5;
    const float SHIFT = 0.13;
    const std::string iconImgs[7] = { CUFF, BRACE, MASK, PULSEOX, EKG, GOWN, THERMO };
    
    
    for (int i = 0; i < 7; i++) {
        
        auto temp = Sprite::create(iconImgs[i]);
        temp->setScale(
                       (iconBar->getContentSize().width / temp->getContentSize().width) * 0.11,
                       (iconBar->getContentSize().width / temp->getContentSize().width) * 0.11);
		// This conditional checks to see if icon was found. If yes, replace with star
        if (foundIt[i]){
			auto temp2 = Sprite::create(STARSHINE);
			temp = temp2;
            temp->setScale(
                           (iconBar->getContentSize().width / temp->getContentSize().width) * 0.17,
                           (iconBar->getContentSize().width / temp->getContentSize().width) * 0.17);
			setIconFound();
            log(foundIt[i]);
        }
        temp->setAnchorPoint(iconBar->getAnchorPoint());
        temp->setPosition(Vec2(
                               0.9*iconBar->getContentSize().width * (STARTPOSFACTORX + i * SHIFT),
                               1.4*iconBar->getContentSize().height * STARTPOSFACTORY));
       
        temp->setOpacity(0);
        iconBar->addChild(temp);
        temp->runAction(Sequence::create(
							DelayTime::create(i*0.1),
							Spawn::create(
								FadeIn::create(0.4),
								EaseBounceOut::create(
									MoveTo::create(
										0.6,
										Vec2(
											iconBar->getContentSize().width * (STARTPOSFACTORX + i * SHIFT),
											iconBar->getContentSize().height * STARTPOSFACTORY))), 
								nullptr), 
							nullptr));
    }
    
    frameLayer->addChild(iconBar, (FRAMEDRAW + 1)); // Set draw priorty high
    iconBar->runAction(Sequence::create(DelayTime::create(3),
                                        FadeOut::create(0.2),
                                        RemoveSelf::create(),
                                        nullptr));
}

void FrameNav::toggleSound(cocos2d::Ref* pSender, cocos2d::Layer *chapterLayer)
{
    
    auto vol = 0.7f*(CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()/VOLUMEMUSIC)+0.15f;
    //auto volEffects = 0.7f*CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume()+0.15f;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto volumeControl = DrawNode::create();
    
    // background color for volume bars
    volumeControl->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, 0.85*visibleSize.height + origin.y), Color4F(0,0,0.2,1.0));
    
    //volumeControl->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, 0.85*visibleSize.height + origin.y), Color4F(0,0,0.2,1.0));
    
    // volume level for music
    volumeControl->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, clampf(vol,0.2,0.85)*visibleSize.height + origin.y), Color4F(vol,0.5*(vol-0.1),0.6*(1-vol),1.0));
    
    // volume level for effects
    //volumeControl->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, clampf(volEffects,0.2,0.85)*visibleSize.height + origin.y), Color4F(volEffects,0.5*(volEffects-0.1),0.6*(1-volEffects),1.0));
    
    volumeControl->setOpacity(0);
    
    chapterLayer->addChild(volumeControl,12345);
    
    auto eventDispatcher = chapterLayer->getEventDispatcher();
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [volumeControl, origin](cocos2d::Touch *touch, cocos2d::Event *event){
        
        auto vol = 0.7f*(CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()/VOLUMEMUSIC)+0.15f;
        //auto volEffects = 0.7f*CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume()+0.15f;
        
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto audioLevel = clampf((touch->getLocation().y - origin.y)/visibleSize.height,0.0f,1.0f);
        volumeControl->stopAllActions();
        
        volumeControl->clear();
        
        // background color for volume bars
        volumeControl->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, 0.85*visibleSize.height + origin.y), Color4F(0,0,0.2,1.0));
        
        //volumeControl->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, 0.85*visibleSize.height + origin.y), Color4F(0,0,0.2,1.0));
        
        if (touch->getLocation().x/visibleSize.width>0.845){
            
            // volume level for music
            volumeControl->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, clampf(audioLevel,0.2f, 0.85f)*visibleSize.height + origin.y), Color4F(audioLevel,0.5*(audioLevel),0.6*(1-audioLevel),1.0));
            
            // volume level for effects
            //volumeControl->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, clampf(volEffects,0.2,0.85)*visibleSize.height + origin.y), Color4F(volEffects,0.5*(volEffects-0.1),0.6*(1-volEffects),1.0));
            
            CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(VOLUMEMUSIC*(clampf(audioLevel,0.15f,0.85f)-0.15f)/0.7f);
            
        } else if (touch->getLocation().x/visibleSize.width>0.745){
            
            // volume level for music
            volumeControl->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, clampf(vol,0.2,0.85)*visibleSize.height + origin.y), Color4F(vol,0.5*(vol-0.1),0.6*(1-vol),1.0));
            
            // volume level for effects
            //volumeControl->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, clampf(audioLevel,0.2f, 0.85f)*visibleSize.height + origin.y), Color4F(audioLevel,0.5*(audioLevel),0.6*(1-audioLevel),1.0));
            
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((clampf(audioLevel,0.15f,0.85f)-0.15f)/0.7f);
            
        } else {
            
            volumeControl->clear();
            return false;
        }
        
        return true;
    };
    
    listener->onTouchMoved = CC_CALLBACK_2(FrameNav::onTouchMoved, this, volumeControl);
    
    listener->onTouchEnded = [volumeControl](cocos2d::Touch *touch, cocos2d::Event *event){
        
        auto vol = CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()/VOLUMEMUSIC;
        auto volEffects = CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume();
        
        UserDefault * def = UserDefault::getInstance();
        def->setFloatForKey("MUSICVOLUME", vol);
        def->setFloatForKey("EFFECTSVOLUME", volEffects);
        def->flush();
        
        volumeControl->runAction(Sequence::create(FadeOut::create(0.4), RemoveSelf::create(), nullptr));
        
        return true;
    };
    
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, volumeControl);
    
    volumeControl->runAction(Sequence::create(FadeIn::create(0.4), DelayTime::create(0.6), FadeOut::create(0.4), RemoveSelf::create(), nullptr));
   
}

bool FrameNav::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event, cocos2d::DrawNode *node)
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto vol = 0.7f*(CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()/VOLUMEMUSIC)+0.15f;
    //auto volEffects = 0.7f*CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume()+0.15f;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto audioLevel = clampf((touch->getLocation().y - origin.y)/visibleSize.height,0.0f,1.0f);
    node->clear();
    // background color for volume bars
    node->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, 0.85*visibleSize.height + origin.y), Color4F(0,0,0.2,1.0));
    
    //node->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, 0.85*visibleSize.height + origin.y), Color4F(0,0,0.2,1.0));
    
    if (touch->getLocation().x/visibleSize.width>0.845){
        
        // volume level for music
        node->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, clampf(audioLevel,0.2f, 0.85f)*visibleSize.height + origin.y), Color4F(audioLevel,0.5*(audioLevel),0.6*(1-audioLevel),1.0));
        
        // volume level for effects
        //node->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, clampf(volEffects,0.2,0.85)*visibleSize.height + origin.y), Color4F(volEffects,0.5*(volEffects-0.1),0.6*(1-volEffects),1.0));
        
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(VOLUMEMUSIC*(clampf(audioLevel,0.15f,0.85f)-0.15f)/0.7f);
        
    } else if (touch->getLocation().x/visibleSize.width>0.745){
        
        // volume level for music
        node->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, clampf(vol,0.2,0.85)*visibleSize.height + origin.y), Color4F(vol,0.5*(vol-0.1),0.6*(1-vol),1.0));
        
        // volume level for effects
       // node->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, clampf(audioLevel,0.2f, 0.85f)*visibleSize.height + origin.y), Color4F(audioLevel,0.5*(audioLevel),0.6*(1-audioLevel),1.0));
        
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((clampf(audioLevel,0.15f,0.85f)-0.15f)/0.7f);
        
    } else {
        
        // volume level for music
        node->drawSolidRect(Vec2(visibleSize.width*0.85, 0.15*visibleSize.height + origin.y), Vec2(0.9*visibleSize.width, clampf(vol,0.2,0.85)*visibleSize.height + origin.y), Color4F(vol,0.5*(vol-0.1),0.6*(1-vol),1.0));
        
        // volume level for effects
        //node->drawSolidRect(Vec2(visibleSize.width*0.79, 0.15*visibleSize.height + origin.y), Vec2(0.84*visibleSize.width, clampf(volEffects,0.2,0.85)*visibleSize.height + origin.y), Color4F(volEffects,0.5*(volEffects-0.1),0.6*(1-volEffects),1.0));
    }
    
    return true;
}

cocos2d::Label* FrameNav::createText(const char* textString, cocos2d::Layer* chapterLayer) {

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF(textString, BOLD, visibleSize.height * TEXTSIZE);

	label->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.15 + origin.y));
	label->setDimensions(visibleSize.width * 0.55, 0); // Allows for multi-line text
	label->setColor(cocos2d::Color3B::BLACK); // Default black text, change in scene for new color
	label->setLineHeight(2.2 * visibleSize.height * TEXTSIZE);
	label->setOpacity(0);

	chapterLayer->addChild(label, FRAMEDRAW + 2);
	return label;

}

void FrameNav::bkgdMusic(int currentChapter) {
    
    UserDefault * def = UserDefault::getInstance();
    auto pastChapter = def->getIntegerForKey("CHAPTER", 0);
    auto sameChapter = pastChapter == currentChapter;
    def->setIntegerForKey("CHAPTER", currentChapter);
    def->flush();
    
    if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()
        || !sameChapter)
    {
        
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        
        switch (currentChapter) {
            case CHLAUNCH:
                
                CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSICLAUNCH);
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSICLAUNCH, true);
                break;
                
            case CHWAIT:
                CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSICWAIT);
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSICWAIT, true);
                break;
                
            case CHPREOP:
                CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSICPREOP);
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSICPREOP, true);
                break;
                
            case CHOR:
                CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSICOR);
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSICOR, true);
                break;
                
            case CHPOSTOP:
                CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSICPOSTOP);
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSICPOSTOP, true);
                break;
                
            default:
                CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSICLAUNCH);
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSICLAUNCH, true);
                break;
        }
    }
    
}
