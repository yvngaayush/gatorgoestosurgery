#ifndef __POPUP_H__
#define __POPUP_H__

#include "ResourceDefinitions.h"

namespace UICustom {

	// LayerRadialGradient inherits form cocos2d:Layer
	// This class controls pop-up behavior functions
	class PopupDelegates : public cocos2d::LayerRadialGradient
	{
	public:
		static PopupDelegates *create();

	protected:
		virtual bool init();
		virtual void setUpTouches();
		virtual void show(const bool animated = true);
		virtual void dismiss(const bool animated = true);
		void setAnimated(const bool animated) { _isAnimated = animated; };

		cocos2d::ui::ImageView *_bg = nullptr;
	private:
		bool _isAnimated = false;
	};

	// This class actually makes a popup
	class Popup : public PopupDelegates
	{
	public:
		static Popup* create(const float value);

	private:
		void initBgCare();
		void initBgGame();
	};
}

#endif // __POPUP_H__
