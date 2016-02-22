//
//  EquipmentLocalBLL.cpp
//  Zombie3_4
//
//  Created by jl on 15/7/27.
//
//

#include "EquipmentLocalBLL.h"
#include "GameHeader.h"
#include "Weapon.h"
#include "WeaponBLL.h"
#include "HeroBase.h"
#include "HeroModelBLL.h"
#include "GameObjectFactory.h"

EquipmentLocalBLL *EquipmentLocalBLL::create()
{
    EquipmentLocalBLL *pRet = new(std::nothrow) EquipmentLocalBLL();
    if (pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

EquipmentLocalBLL::~EquipmentLocalBLL()
{
    
}

EquipmentLocalBLL::EquipmentLocalBLL()
{
    std::string sCurrVersionPath=FileUtils::getInstance()->getWritablePath()+kVersion;
    if(!FileUtils::getInstance()->isDirectoryExist(sCurrVersionPath))
    {
        FileUtils::getInstance()->createDirectory(sCurrVersionPath);
    }
    
    strLocalPath=sCurrVersionPath+"/"+"EquipmentLocal.apm";
    
    resetEquipMem();
}
//重设置装备内存空间
void EquipmentLocalBLL::resetEquipMem()
{
    //删除模型指针
    if (modelData) {
        delete[] modelData;
    }
    
    localEquipNum=0;
    localEquipMaxNum=0;
    Data dt=FileUtils::getInstance()->getDataFromFile(strLocalPath.c_str());
    if (dt.isNull()) {
        localEquipNum=0;
        localEquipMaxNum=10;
        modelData=new Equipment[localEquipMaxNum];
    }else{
        localEquipNum=dt.getSize() / sizeof(Equipment);
        //最大模型数
        localEquipMaxNum=localEquipNum+10;
        modelData=new Equipment[localEquipMaxNum];
        //本地数据复制到内存
        memcpy(modelData, dt.getBytes(), localEquipNum*sizeof(Equipment));
    }
}
//重设排序背包
void EquipmentLocalBLL::reorderBackpack()
{
    int backpackSeat=0;     //背包位置
    int wearSeat=0;         //血槽位置
    for (int i=0; i<localEquipNum; i++) {
        auto equip=&(modelData[i]);
        if (equip->Seat>0) {
            wearSeat++;
            equip->Seat=wearSeat;
        }else{
            backpackSeat--;
            equip->Seat=backpackSeat;
        }
    }
}
//获得装备
void EquipmentLocalBLL::addEquip(int iWeaponID)
{
    int iWeaponIndex=iWeaponID - 1;
    WeaponBLL *wb=WeaponBLL::create(kModelWritablePath);
    CCASSERT(iWeaponIndex < wb->getModelSize(), "iWeaponIndex < wb->getModelSize");
    Weapon* w=&(wb->modelData[iWeaponIndex]);
    
    Equipment *addEquip=&(modelData[localEquipNum]);
    addEquip->EquipmentID=localEquipNum;
    addEquip->WeaponID=w->WeaponID;
    addEquip->CurrLv=1;
    addEquip->Seat=0;
    addEquip->MaxLv=w->MaxLv;
    addEquip->CurrPrice=w->Price * 0.7;
    addEquip->PriceAddRate=w->PriceAddRate;             //价格增长率
    addEquip->AttributeRate=w->AttributeRate;           //属性增长率
    addEquip->AddAttack=w->AddAttack;                   //增加攻击力
    addEquip->AddDef=w->AddDef;                         //增加防御力
    addEquip->AddHp=w->AddHp;                           //增加生命
    addEquip->AddAttackHit=w->AddAttackHit;             //增加暴击
    addEquip->Type=w->Type;
    addEquip->Price=w->Price;
    //装备的升级费用为 （初始价格*0.6）*当前等级数+初始价格,等级为1级不用计算
    addEquip->UpPrice=w->Price * w->PriceAddRate + w->Price;      //计算升级所需要的价格
    
    strcpy(addEquip->WeaponName, w->WeaponName);
    strcpy(addEquip->ImgFile, w->ImgFile);
    
    localEquipNum++;
    
    //排序
    reorderBackpack();
    saveLocalData();
}
//卖出装备
void EquipmentLocalBLL::deleEquip(int iWeaponID)
{
    int iWeaponIndex=iWeaponID - 1;
    CCASSERT(iWeaponIndex < localEquipMaxNum, "iWeaponIndex < localEquipMaxNum");
    
    for (int i=iWeaponIndex; i<localEquipNum; i++) {
        Equipment *equip=&(modelData[i+1]);
        memcpy(&(modelData[i]), equip, sizeof(Equipment));
    }
    localEquipNum--;
    //排序
    reorderBackpack();
    saveLocalData();
}
//保存沙箱数据
bool EquipmentLocalBLL::saveLocalData()
{
    bool result=false;
    
    //读取内存
    unsigned char* buff=(unsigned char*)modelData;
    int iSize=localEquipNum*sizeof(Equipment);
    
    FILE *readFile = fopen(strLocalPath.c_str(), "wb");
    if (readFile)
    {
        fwrite(buff, sizeof(unsigned char),iSize , readFile);
    }
    fclose(readFile);
    
    resetEquipMem();
    
    return result;
}
//读取背包装备
void EquipmentLocalBLL::readBackpack(Vector<ui::Button*>& bp)
{
    for (int i=0; i<localEquipNum; i++) {
        auto equip=&(modelData[i]);
        //大于零为放在装备槽中
        if (equip->Seat>0) {
            continue;
        }
        //创建装备图标
        ui::Button *btn=ui::Button::create(equip->ImgFile);
        btn->setName(equip->WeaponName);
        btn->setTag(i);
        //装备等级
        ui::Text *lvText=ui::Text::create("Lv.%d", "", 15);
        lvText->setColor(Color3B::GREEN);
        auto eqbblv = StringUtils::format("Lv.%d",equip->CurrLv);
        lvText->setString(eqbblv);
        lvText->setPosition(Vec2(16,10));
        btn->addChild(lvText);
        
        bp.pushBack(btn);
    }
}
//读取佩戴装备
void EquipmentLocalBLL::readWearpack(Vector<ui::Button*>& bp, int heroID)
{
    for (int i=0; i<localEquipNum; i++) {
        auto equip=&(modelData[i]);
        //小于等于零为放在背包槽中
        if (equip->Seat<=0 || equip->HeroID != heroID) {
            continue;
        }
        //创建装备图标
        ui::Button *btn=ui::Button::create(equip->ImgFile);
        btn->setName(equip->WeaponName);
        btn->setTag(i);
        btn->setUserData(equip);
        
        //装备等级
        ui::Text *lvText=ui::Text::create("Lv.%d", "", 15);
        lvText->setColor(Color3B::GREEN);
        auto eqbblv = StringUtils::format("Lv.%d",equip->CurrLv);
        lvText->setString(eqbblv);
        lvText->setPosition(Vec2(16,10));
        btn->addChild(lvText);
        
        bp.pushBack(btn);
    }
}
//穿戴装备
bool EquipmentLocalBLL::wearEquip(int equipID, int heroID)
{
    CCASSERT(equipID < localEquipMaxNum, "equipID < localEquipMaxNum");
    //当前准备穿戴的装备
    auto currEquip=&(modelData[equipID]);
    for (int i=0; i<localEquipNum; i++) {
        auto equip=&(modelData[i]);
        if (equip->Seat > 0 && equip->Type==currEquip->Type && equip->HeroID==heroID) {
            //把同类型已经穿戴的装备卸载
            equip->HeroID=0;
            equip->Seat=0;
            break;
        }
    }
    currEquip->Seat=1;
    currEquip->HeroID=heroID;

    reorderBackpack();
    saveLocalData();
    
    auto hero = GameObjectFactory::getHero(heroID-1);
    auto mod = hero->getHeroModel();
    updateHeroAttribute(mod->HeroID-1);
    
    return true;
}
//更新英雄属性
void EquipmentLocalBLL::updateHeroAttribute(int heroModelID)
{
    //计算装备的属性,判断equip->AttributeName,来计算是否增加Hp,Attack,Def,Hit 四个属性
    auto hbb=HeroModelBLL::create(kModelWritablePath);
    auto mod=&(hbb->modelData[heroModelID]);
    
    mod->AddAttack=0;
    mod->AddDef=0;
    mod->AddAttackHit=0;
    mod->AddHp=0;
    for (int i=0; i<localEquipNum; i++) {
        auto equip=&(modelData[i]);
        if (equip->Seat > 0 && equip->HeroID==mod->HeroID) {
            mod->AddAttack+=equip->AddAttack;
            mod->AddDef+=equip->AddDef;
            mod->AddAttackHit+=equip->AddAttackHit;
            mod->AddHp+=equip->AddHp;
        }
    }
    hbb->saveData();
}
//脱掉装备
bool EquipmentLocalBLL::removeEquip(int equipID, int heroID)
{
    CCASSERT(equipID < localEquipMaxNum, "equipID < localEquipMaxNum");
    auto equip=&(modelData[equipID]);
    equip->Seat=0;
    equip->HeroID=0;
    
    reorderBackpack();
    saveLocalData();
    
    auto hero = GameObjectFactory::getHero(heroID-1);
    auto mod = hero->getHeroModel();
    updateHeroAttribute(mod->HeroID-1);
    
    return true;
}
//中英文转换
std::string EquipmentLocalBLL::getEquipChineseName(int iEquipID)
{
    auto equip=&(modelData[iEquipID]);
    std::string str;
    if (equip->AddHp > 0)
    {
        str=StringUtils::format("%s生命值:%d\n",str.c_str(), equip->AddHp);
    }
    if (equip->AddAttack > 0) {
        str=StringUtils::format("%s攻击力:%d\n",str.c_str(), equip->AddAttack);
    }
    if (equip->AddDef > 0)
    {
        str=StringUtils::format("%s防御力:%d\n",str.c_str(), equip->AddDef);
    }
    if (equip->AddAttackHit > 0)
    {
        str=StringUtils::format("%s暴击率:%0.2f\n",str.c_str(), equip->AddAttackHit);
    }
    return str;
}
//获取装备中文名字
std::string EquipmentLocalBLL::getUpEquipChineseName(int iEquipID)
{
    auto equip=&(modelData[iEquipID]);
    std::string str;
    if (equip->AddHp > 0)
    {
        int value=equip->AddHp + (equip->AddHp * (equip->AttributeRate * 0.01));
        str=StringUtils::format("%s生命值:%d\n",str.c_str(), value);
    }
    if (equip->AddAttack > 0) {
        int value=equip->AddAttack + (equip->AddAttack * (equip->AttributeRate * 0.01));
        str=StringUtils::format("%s攻击力:%d\n",str.c_str(), value);
    }
    if (equip->AddDef > 0)
    {
        int value=equip->AddDef + (equip->AddDef * (equip->AttributeRate * 0.01));
        str=StringUtils::format("%s防御力:%d\n",str.c_str(), value);
    }
    if (equip->AddAttackHit > 0)
    {
        float value=equip->AddAttackHit + (equip->AddAttackHit * (equip->AttributeRate * 0.01));
        str=StringUtils::format("%s暴击率:%0.2f\n",str.c_str(), value);
    }
    return str;
}
//获取全部装备
void EquipmentLocalBLL::getAllEquipment(std::vector<Weapon*>& equipVector, int minQuality, int maxQuality)
{
    WeaponBLL *wb=WeaponBLL::create(kModelWritablePath);
    
    for (int i=0; i<Weapon_MaxData; i++) {
        auto equip=&(wb->modelData[i]);
        if (equip->Quality>=minQuality && equip->Quality<=maxQuality) {
            equipVector.push_back(equip);
        }
    }
}
//强化装备
void EquipmentLocalBLL::upEquip(int iEquipID)
{
    auto equip=&(modelData[iEquipID]);
    //装备属性增长
    equip->CurrLv+=1;
    if (equip->AddHp > 0) {
        int value=equip->AddHp + (equip->AddHp * (equip->AttributeRate * 0.01));
        equip->AddHp=value;
    }
    if (equip->AddAttack > 0) {
        int value=equip->AddAttack + (equip->AddAttack * (equip->AttributeRate * 0.01));
        equip->AddAttack=value;
    }
    if (equip->AddDef > 0) {
        int value=equip->AddDef + (equip->AddDef * (equip->AttributeRate * 0.01));
        equip->AddDef=value;
    }
    if (equip->AddAttackHit > 0) {
        int value=equip->AddAttackHit + (equip->AddAttackHit * (equip->AttributeRate * 0.01));
        equip->AddAttackHit=value;
    }
    int price=0;
    //计算卖出价格
    for (int i=0; i<equip->CurrLv; i++) {
        price+=equip->Price * equip->PriceAddRate * i + equip->Price;
    }
    price*=0.7;
    //卖出价格
    equip->CurrPrice=price;
    //装备的升级费用为 （初始价格*0.6）*当前等级数+初始价格
    equip->UpPrice=equip->Price * equip->PriceAddRate * equip->CurrLv + equip->Price;
    //保存装备数据
    saveLocalData();
}
//获取可掉落装备
void EquipmentLocalBLL::getDropEquipment(std::vector<Weapon*>& equipVector, int dropValue, float dropRate)
{
    WeaponBLL *wb=WeaponBLL::create(kModelWritablePath);
    for (int i=0; i<Weapon_MaxData; i++) {
        auto equip=&(wb->modelData[i]);
        if (equip->DropValue<=dropValue && equip->DropRate > dropRate) {
            equipVector.push_back(equip);
        }
    }
}
