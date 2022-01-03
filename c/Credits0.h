#ifndef __CREDITS_H__
#define __CREDITS_H__

#include "ResourceDefinitions.h"
#include "editor-support/spine/Json.h"

class Credits : public Layer
{
public:
	bool _actionComplete = true;// Added variable to ensure un-interrupted run actions
	static Scene* createScene();
	virtual bool init();
	void gotoNextScene(Ref* pSender);
    void gotoCredits(float dt);
    void gotoMenu(float dt);
    
    Json *script;
    
	CREATE_FUNC(Credits);
};
#endif // __CREDITS_H__
