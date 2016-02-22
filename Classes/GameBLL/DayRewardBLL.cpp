//
//  DayRewardBLL.cpp
//  Zombie3_4
//
//  Created by liuye on 15/10/20.
//
//

#include "DayRewardBLL.h"
#include "PlayerBLL.h"
#include "WeaponBLL.h"
#include "DayRewardModelBLL.h"
#include "EquipmentLocalBLL.h"

#define kDayCount 7
#define kDayRewardPlist "DayRewardData.plist"                                   //本地数据文件
#define kReceiveKey(i) __String::createWithFormat("receive-%s",i)               //领取记录

static DayRewardBLL *_sharedDayRewardBLL;
DayRewardBLL* DayRewardBLL::getInstance()
{
    if (nullptr == _sharedDayRewardBLL)
    {
        _sharedDayRewardBLL = new DayRewardBLL();
    }
    return _sharedDayRewardBLL;
}

DayRewardBLL::~DayRewardBLL()
{
    CC_SAFE_RELEASE_NULL(m_Dict);
}

DayRewardBLL::DayRewardBLL()
{
    m_IsView=true;
    const char* path=APFile::getLocalWritePath(kDayRewardPlist);
    if(APFile::isFileExist(path)){
        m_Dict=__Dictionary::createWithContentsOfFile(path);
    }else{
        m_Dict=__Dictionary::create();
    }
    m_Dict->retain();
}
void DayRewardBLL::destroyInstance()
{
    CC_SAFE_DELETE(_sharedDayRewardBLL);
}
//保存数据
void DayRewardBLL::saveLocalData()
{
    const char* path=APFile::getLocalWritePath(kDayRewardPlist);
    m_Dict->writeToFile(path);
}
//设置已领取
void DayRewardBLL::setReceive(int i)
{
    auto date=APDateHelper::getLastDate(i);
    //设置领取记录
    auto sKey=kReceiveKey(date->getCString());
    m_Dict->setObject(ccs("1"), sKey->getCString());
    //保存数据
    saveLocalData();
}
//获取连续登陆天数
int DayRewardBLL::getLoginDateCount()
{
    int day=1;
    auto arr=m_Dict->allKeys();
    if (arr==NULL) { return day;}
    int count=arr->count();
    for (int i=1; i<=count; i++) {
        auto date=APDateHelper::getLastDate(i);
        auto sKey=kReceiveKey(date->getCString());
        auto obj=m_Dict->objectForKey(sKey->getCString());
        if (obj) {
            int iFlag=((__String*)obj)->intValue();
            if (iFlag==1) {
                day++;
                if (day>kDayCount) {
                    day=1;
                }
            }else{
                break;
            }
        }else{
            break;
        }
    }
    return day;
}

//今日是否已领取
bool DayRewardBLL::getIsDayReceive()
{
    //今日是否已领取
    auto date=APDateHelper::getDate();
    auto sKey=kReceiveKey(date->getCString());
    auto obj=m_Dict->objectForKey(sKey->getCString());
    if (obj) {
        return true;
    }else{
        return false;
    }
}
//发放今日奖励
std::string DayRewardBLL::putDayReward(int dayRewardID)
{
    int dayRewardIndex=dayRewardID - 1;
    auto dmb=DayRewardModelBLL::create(kModelWritablePath);
    auto model=&dmb->modelData[dayRewardIndex];
    
    std::string funStr=model->Func;
    std::string delim="&";
    std::vector<std::string> list;
    APStringHelper::split(funStr, delim, &list);
    
    std::string msg="恭喜你获得";
    auto pb=PlayerBLL::create();
    auto wb=WeaponBLL::create(kModelWritablePath);
    auto elb=EquipmentLocalBLL::create();
    
    //解析函数字符串 ,参数列表
    for (int i=0; i<list.size(); i++)
    {
        std::vector<std::string> listValue;
        std::string equal="=";
        std::string express=list[i];
        if(express.length()==0) continue;
        APStringHelper::split(list[i], equal, &listValue);
        CCAssert(listValue.size()==2, "Func String Error!");
        __String *key=ccs(APFile::trim(listValue[0]).c_str());
        __String *value=ccs(listValue[1].c_str());
        int ivalue=value->intValue();
        if (!apstrcmp(key->getCString(), "AddGoldCount")) {
            pb->addGold(ivalue);
            msg=StringUtils::format("%s %d金币",msg.c_str(),ivalue);
        }else if (!apstrcmp(key->getCString(), "AddDiamondCount")) {
            pb->addDia(ivalue);
            msg=StringUtils::format("%s %d钻石",msg.c_str(),ivalue);
        }else if (!apstrcmp(key->getCString(), "AddEquipmentID")) {
            elb->addEquip(ivalue);
            ivalue-=1;
            auto wmode=&wb->modelData[ivalue];
            msg=StringUtils::format("%s %s",msg.c_str(),wmode->WeaponName);
        }else{
            CCAssert(true, "Func String Error!");
        }
    }
    
    setReceive();
    
    return msg;
}
