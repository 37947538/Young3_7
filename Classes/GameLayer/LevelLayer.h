#ifndef __MyProjectName_LevelLayer_H__
#define __MyProjectName_LevelLayer_H__

#include "GameHeader.h"
#include "PopBase.h"

/**
 k_ClassDes
 */

class LevelLayer : public PopBase, public cocos2d::extension::ScrollViewDelegate
{
public:
    CREATE_FUNC(LevelLayer);
    virtual bool init();
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);
    virtual void setWorldID(int worldID) { m_WorldID=worldID; }                 //设置地图ID
protected:
    Text* m_TitleLabel;
    APScrollView* m_ScrollView;
    int m_MaxWorldID=0;
    int m_WorldID=0;
    int m_CurrPageIndex=0;
    bool m_IsBeginDrag=false;                                                   //是否开始拖拽
    Button* Button_fanye_1;
    Button* Button_fanye_2;
private:
    void Button_Close_BtnOnTouch(Ref* sender,Widget::TouchEventType type);      //
    void Button_fanye_1_BtnOnTouch(Ref* sender,Widget::TouchEventType type);    //
    void Button_fanye_2_BtnOnTouch(Ref* sender,Widget::TouchEventType type);    //
    void setPageShow();                                                         //设置页显示
    void setPageButtonVisible();
    void LevelButton_OnTouch(Ref* sender,Widget::TouchEventType type);
};

#endif
