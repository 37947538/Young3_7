//
//  PopTipsLayer.h
//  Zombie3_4
//
//  Created by liuye on 15/8/14.
//
//

#ifndef __Zombie3_4__PopTipsLayer__
#define __Zombie3_4__PopTipsLayer__

#include <stdio.h>
#include "PopBase.h"

class PopTipsLayer : public PopBase
{
public:
    static void addTipLayer(Node *parent, const std::string& msg);         //增加提示层
    CREATE_FUNC(PopTipsLayer);
    virtual bool init();
protected:
    Layout* m_RootNode;
    ImageView* m_TipsBg;
    Text* m_TipsText;
private:
    void setInfoString(const std::string& msg);
    void onEnter();
};

#endif /* defined(__Zombie3_4__PopTipsLayer__) */
