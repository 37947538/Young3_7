#ifndef __MyProjectName_PauseLayer_H__
#define __MyProjectName_PauseLayer_H__

#include "GameHeader.h"
#include "PopBase.h"

/**
 k_ClassDes
 */

class PauseLayer : public PopBase
{
public:
    static Scene* createScene();
    CREATE_FUNC(PauseLayer);
    virtual bool init();
    virtual void onEnter();
protected:
    Layout* m_RootNode;
private:
    void effectButtonOnTouch(Ref* sender,CheckBox::EventType type);
    void musicButtonOnTouch(Ref* sender,CheckBox::EventType type);
    void Button_Resume_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //
    void Button_QUIT_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //
};

#endif
