//
//  EquipmentLocalBLL.h
//  Zombie3_4
//  本地装备存储
//  Created by jl on 15/7/27.
//
//

#ifndef __Zombie3_4__EquipmentLocalBLL__
#define __Zombie3_4__EquipmentLocalBLL__

#include <stdio.h>
#include "GameHeader.h"
#include "EquipmentBLL.h"
#include "Weapon.h"
#include "HeroModel.h"

class EquipmentLocalBLL : public EquipmentBLL
{
public:
    static EquipmentLocalBLL *create();
    virtual ~EquipmentLocalBLL();
    EquipmentLocalBLL();
    
    void addEquip(int iEquipID);                                                                    //获得装备
    void deleEquip(int iEquipID);                                                                   //删除装备
    void resetEquipMem();                                                                           //重设置装备内存空间
    void reorderBackpack();                                                                         //重设排序背包
    void readBackpack(Vector<ui::Button*>& bp);                                                     //读取背包装备
    void readWearpack(Vector<ui::Button*>& bp, int heroID);                                         //读取佩戴装备
    bool saveLocalData();                                                                           //保存沙箱数据
    bool wearEquip(int equipID, int heroID);                                                        //穿戴装备
    bool removeEquip(int equipID, int heroID);                                                      //脱掉装备
    void updateHeroAttribute(int heroModelID);                                                      //更新英雄属性
    std::string getEquipChineseName(int iEquipID);                                                  //获取装备中文名字
    std::string getUpEquipChineseName(int iEquipID);                                                //获取装备中文名字
    void getAllEquipment(std::vector<Weapon*>& equipVector, int minQuality=1, int maxQuality=5);    //获取全部装备
    void getDropEquipment(std::vector<Weapon*>& equipVector, int dropValue, float dropRate);        //获取可掉落装备
    void upEquip(int iEquipID);                                                                     //强化装备
private:
    std::string strLocalPath;                                                   //保存路径字符串
    int localEquipNum;                                                          //本地装备数量
    int localEquipMaxNum;                                                       //本地装备最大数量
};

#endif /* defined(__Zombie3_4__EquipmentLocalBLL__) */
