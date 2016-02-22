#ifndef __MyProjectName_ChooseCharacterLayer_H__
#define __MyProjectName_ChooseCharacterLayer_H__

#include "GameHeader.h"

/**
 k_ClassDes
 */

class ChooseCharacterLayer : public Layer
{
public:
    static Scene* createScene();
    CREATE_FUNC(ChooseCharacterLayer);
    ~ChooseCharacterLayer();
    ChooseCharacterLayer();
    virtual bool init();
    //重设按钮状态
    void playerBtnOnTouch(Ref* sender, Widget::TouchEventType type);
protected:
    Layout* m_RootNode;
private:
    void Button_juese_2_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //
    void Button_juese_1_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //
    void Button_fanhui_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //
    void Button_kaishi_BtnOnTouch(Ref* sender,Widget::TouchEventType type);   //
    void setDataView();
    void testHero(Ref* sender);
};

#endif
