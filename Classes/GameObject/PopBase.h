//
//  PopBase.h
//  Tower3_4
//
//  Created by liuye on 15/5/13.
//
//

#ifndef __Tower3_4__PopBase__
#define __Tower3_4__PopBase__

#include <stdio.h>
#include "GameHeader.h"

class PopBase : public Layer
{
public:
    CREATE_FUNC(PopBase);
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    virtual void onExit();
    virtual void removeFromParentAndCleanup(bool cleanup);
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void setIsTopTouch(bool topTouch) { m_IsToptouch=topTouch; }
    virtual void setIsRunAction(bool runAction) { m_IsRunAction=runAction; }
protected:
    Size m_WinSize;                     //窗口视图大小
    Layout* m_RootNode=nullptr;
    bool m_IsToptouch=true;             //是否为最上层拦截touch
    bool m_IsRunAction=true;            //是否运行弹出动作
    Sequence *m_Sequence=nullptr;       //动作序列
};

#endif /* defined(__Tower3_4__PopBase__) */
