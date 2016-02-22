#ifndef __MyProjectName_WeaponBLL_H__
#define __MyProjectName_WeaponBLL_H__

#include "Weapon.h"

/**
 k_ClassDes
 */

#define Weapon_MaxData 30


class WeaponBLL : public Ref
{
public:
    static WeaponBLL *create(const std::string& localPath)
    {
        WeaponBLL *pRet = new(std::nothrow) WeaponBLL();
        if (pRet)
        {
            pRet->loadResData(localPath);
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

    ~WeaponBLL()
    {
        if(modelData)
        {
            delete[] modelData;
        }
    }
    
    WeaponBLL()
    {
        modelData=new Weapon[Weapon_MaxData];
    }
    
    //获取数据源的大小
    int getModelSize() { return Weapon_MaxData; };
    
    //加载资源数据
    bool loadResData(const std::string& resPath)
    {
        
        //bool result=false;
        //FILE *readFile = fopen(resPath.c_str(), "rb");
        //if (readFile)
        //{
        //    fread(modelData, sizeof(Weapon), Weapon_MaxData, readFile);
        //    result=true;
        //}
        //fclose(readFile);
        //return result;
        
        Data dt=FileUtils::getInstance()->getDataFromFile(resPath.c_str());
        if (dt.isNull()) {
            return false;
        }
        localData=resPath;
        
        unsigned char* buff= dt.getBytes();
        unsigned char* currBuff=&buff[208688];    //208688 内存文件存在位置
        
        //判断对象大小
        memcpy(modelData, currBuff, Weapon_MaxData*sizeof(Weapon));
        return true;
    }
    
    //保存沙箱数据
    bool saveData()
    {
        bool result=false;
        
        //读取内存
        Data dt=FileUtils::getInstance()->getDataFromFile(localData.c_str());
        unsigned char* buff= dt.getBytes();
        unsigned char* currBuff=&buff[208688];    //208688 内存文件存在位置
        memcpy(currBuff,modelData, Weapon_MaxData*sizeof(Weapon));
        
        FILE *readFile = fopen(localData.c_str(), "wb");
        if (readFile)
        {
            fwrite(dt.getBytes(), sizeof(unsigned char),dt.getSize() , readFile);
        }
        fclose(readFile);
        
        
        return result;
    }
    
    //打印当前数据
    void printData()
    {
         for(int i=0; i< getModelSize(); i++) {
               printf("model[%d]\n",i);
               auto m=&modelData[i];
               printf("WeaponID[%d]",m->WeaponID);
               printf("WeaponName[%s]",m->WeaponName);
               printf("Type[%d]",m->Type);
               printf("Quality[%d]",m->Quality);
               printf("ImgFile[%s]",m->ImgFile);
               printf("Price[%d]",m->Price);
               printf("PriceAddRate[%0.2f]",m->PriceAddRate);
               printf("MaxLv[%d]",m->MaxLv);
               printf("AddAttack[%d]",m->AddAttack);
               printf("AddDef[%d]",m->AddDef);
               printf("AddHp[%d]",m->AddHp);
               printf("AddAttackHit[%0.2f]",m->AddAttackHit);
               printf("AttributeRate[%0.2f]",m->AttributeRate);
               printf("DropValue[%d]",m->DropValue);
               printf("DropRate[%0.2f]",m->DropRate);
             }

    }

    Weapon *modelData;
    std::string localData;
};

#endif 

