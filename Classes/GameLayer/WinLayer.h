#ifndef __MyProjectName_WinLayer_H__
#define __MyProjectName_WinLayer_H__

#include "GameHeader.h"

/**
 k_ClassDes
 */

class WinLayer : public Layer
{
public:
    static Scene* createScene();
    ~WinLayer();
    WinLayer();
    CREATE_FUNC(WinLayer);
    virtual bool init();
    void setDataView();
protected:
    Layout* m_RootNode;
    ui::ScrollView* m_ScrollView;
    ui::Button* Button_jixu;
    ui::Button* Button_fanhui;
private:
    void Button_jixu_BtnOnTouch(Ref* sender,Widget::TouchEventType type);
    void Button_fanhui_BtnOnTouch(Ref* sender,Widget::TouchEventType type);
};

#endif

