//
//  DayRewardBLL.h
//  Zombie3_4
//  每日奖励
//  Created by liuye on 15/10/20.
//
//

#ifndef __Zombie3_4__DayRewardBLL__
#define __Zombie3_4__DayRewardBLL__

#include <stdio.h>
#include "GameHeader.h"

class DayRewardBLL : public Ref
{
public:
    static DayRewardBLL* getInstance();
    static void destroyInstance();
    CC_SYNTHESIZE(bool,m_IsView,IsView);                  //是否显示
    ~DayRewardBLL();
    DayRewardBLL();
    void addLoginLog();                                   //添加登陆日志
    bool isReceive(__String* type);                       //是否已领取
    void setReceive(int i=0);                             //设置已领取
    int getLoginDateCount();                              //获取连续登陆天数
    bool getIsDayReceive();                               //今日是否已领取
    std::string putDayReward(int dayRewardID);            //发放今日奖励
private:
    __Dictionary *m_Dict;
    //保存数据
    void saveLocalData();
};

#endif /* defined(__Zombie3_4__DayRewardBLL__) */
