#include "Popup.h"

using namespace ui;

// General variables that can be used for any namespace
namespace {
	const float ANIMATION_TIME = 0.15f;
	const float FADE_RATIO = 150;
}


// Namespace to just control the image to the caregiver clipboard
namespace CAREGIVER {
	const char *BOARD = "Scene01/Clipboard.png"; // popup sprite
}

// Namespace to just control the image to the I-spy game 
namespace ISPYGAME {
	const char *GAME = "Scene01/IconGame.png"; // popup sprite
}


namespace UICustom {

	PopupDelegates *PopupDelegates::create()
	{
		// std::nothrow indicates that these functions shall not throw an exception 
		// on failure, but return a null pointer instead.
		PopupDelegates *node = new (std::nothrow)PopupDelegates(); 
		if (node && node->init())
		{
			node->autorelease();
			return node;
		}
		CC_SAFE_DELETE(node);
		return nullptr;
	}

	// Initialize a popup layer
	bool PopupDelegates::init()
	{
		Size winSize = Director::getInstance()->getWinSize();

		if (!LayerRadialGradient::initWithColor(Color4B(0, 0, 0, 0),
												Color4B(0, 0, 0, FADE_RATIO),
												winSize.width / 1.7f,
												winSize / 2, 0.075f))
		{
			return false;
		}

		// Set the opacity of the background to zero
		this->setOpacity(0);

		// Fade in popup
		show(true);

		// Create a listener
		this->setUpTouches();

		return true;
	}

	// Fade in popup
	void PopupDelegates::show(const bool animated)
	{
		if (animated) {
			this->runAction(FadeTo::create(ANIMATION_TIME, FADE_RATIO));
		}
		else {
			this->setOpacity(FADE_RATIO);
		}
	}

	// Remove popup from layer
	void PopupDelegates::dismiss(const bool animated)
	{
		if (animated) {
			this->runAction(Sequence::create(FadeTo::create(ANIMATION_TIME, 0), RemoveSelf::create(), NULL));
		}
		else {
			this->removeFromParentAndCleanup(true);
		}
	}

	// Create a listener to handle touches for your layer
	void PopupDelegates::setUpTouches()
	{
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [=](Touch* touch, Event* event) {
			auto box = event->getCurrentTarget()->getBoundingBox();
			if (box.containsPoint(touch->getLocation())) {
				this->dismiss(true);
			}
			return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}


	Popup *Popup::create(const float value)
	{
		Popup *node = new (std::nothrow)Popup();
		Size winSize = Director::getInstance()->getWinSize();
		if (node && node->init())
		{
			if (value == 10) { node->initBgCare(); };
			if (value == 20) { node->initBgCare(); };
			node->autorelease();
			return node;
		}

		CC_SAFE_DELETE(node);
		return nullptr;
	}

	void Popup::initBgCare()
	{
		Size winSize = Director::getInstance()->getWinSize();
		_bg = ui::ImageView::create(CAREGIVER::BOARD);
		_bg->setPosition(Point(winSize.width / 2, winSize.height / 2)); // Put it on the center of the screen
		_bg->setScale((winSize.width / _bg->getContentSize().width),
			(winSize.height / _bg->getContentSize().height));
		_bg->setScale9Enabled(true);
		this->addChild(_bg);
	}

	void Popup::initBgGame()
	{
		Size winSize = Director::getInstance()->getWinSize();

		_bg = ui::ImageView::create(ISPYGAME::GAME);
		

		_bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
		_bg->setScale((winSize.width / _bg->getContentSize().width),
			(winSize.height / _bg->getContentSize().height));
		_bg->setScale9Enabled(true);
		this->addChild(_bg);
	}
}
