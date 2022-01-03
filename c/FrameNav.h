#ifndef __FRAME_NAV_H__
#define __FRAME_NAV_H__

#include "ResourceDefinitions.h"
#include "MainMenu.h"

class FrameNav : public Layer {
private:
	int iconsFound = 0;

public:
	FrameNav();
	virtual ~FrameNav();
	Vector<Sprite*> icons;
	void addFrameNav(Layer* layer); // Fades in over 0.2 seconds
	void gotoMainMenu(Ref* pSender);
	void tapScreen(cocos2d::Layer *chapterLayer);
	void toggleBorder(int tag, Layer *frameLayer);
	void createIconBar(Layer* frameLayer);
	void toggleIconBar(int tag, Layer* frameLayer);
	void setIconFound();
	int getIconFound();
    
    void toggleSound(cocos2d::Ref* pSender, cocos2d::Layer *chapterLayer); // volume controls
    bool onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event,
                      cocos2d::DrawNode *node); // ugly code for volume controls
    Label* createText(const char *textString, Layer *chapterLayer);
    
    void bkgdMusic(int currentChapter);
};

#endif // __FRAME_NAV_H__
