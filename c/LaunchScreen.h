#ifndef __LAUNCH_H__
#define __LAUNCH_H__

#include "ResourceDefinitions.h"

class Launch : public Layer
{
public:
	bool _actionComplete = true;// Added variable to ensure un-interrupted run actions
	static Scene* createScene();
	virtual bool init();
	void gotoNextScene(Ref* pSender);
    void gotoCredits(float dt);
	CREATE_FUNC(Launch);
};
#endif // __LAUNCH_H__
