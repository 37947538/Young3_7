#ifndef __MyProjectName_EquipmentBLL_H__
#define __MyProjectName_EquipmentBLL_H__

#include "Equipment.h"

/**
 k_ClassDes
 */

#define Equipment_MaxData 1


class EquipmentBLL : public Ref
{
public:
    static EquipmentBLL *create(const std::string& localPath)
    {
        EquipmentBLL *pRet = new(std::nothrow) EquipmentBLL();
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

    ~EquipmentBLL()
    {
        if(modelData)
        {
            delete[] modelData;
        }
    }
    
    EquipmentBLL()
    {
        modelData=new Equipment[Equipment_MaxData];
    }
    
    //获取数据源的大小
    int getModelSize() { return Equipment_MaxData; };
    
    //加载资源数据
    bool loadResData(const std::string& resPath)
    {
        
        //bool result=false;
        //FILE *readFile = fopen(resPath.c_str(), "rb");
        //if (readFile)
        //{
        //    fread(modelData, sizeof(Equipment), Equipment_MaxData, readFile);
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
        unsigned char* currBuff=&buff[216008];    //216008 内存文件存在位置
        
        //判断对象大小
        memcpy(modelData, currBuff, Equipment_MaxData*sizeof(Equipment));
        return true;
    }
    
    //保存沙箱数据
    bool saveData()
    {
        bool result=false;
        
        //读取内存
        Data dt=FileUtils::getInstance()->getDataFromFile(localData.c_str());
        unsigned char* buff= dt.getBytes();
        unsigned char* currBuff=&buff[216008];    //216008 内存文件存在位置
        memcpy(currBuff,modelData, Equipment_MaxData*sizeof(Equipment));
        
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
               printf("EquipmentID[%d]",m->EquipmentID);
               printf("HeroID[%d]",m->HeroID);
               printf("WeaponName[%s]",m->WeaponName);
               printf("WeaponID[%d]",m->WeaponID);
               printf("CurrLv[%d]",m->CurrLv);
               printf("MaxLv[%d]",m->MaxLv);
               printf("Seat[%d]",m->Seat);
               printf("CurrPrice[%d]",m->CurrPrice);
               printf("UpPrice[%d]",m->UpPrice);
               printf("ImgFile[%s]",m->ImgFile);
               printf("Type[%d]",m->Type);
               printf("Price[%d]",m->Price);
               printf("PriceAddRate[%0.2f]",m->PriceAddRate);
               printf("AttributeRate[%0.2f]",m->AttributeRate);
               printf("AddAttack[%d]",m->AddAttack);
               printf("AddDef[%d]",m->AddDef);
               printf("AddHp[%d]",m->AddHp);
               printf("AddAttackHit[%0.2f]",m->AddAttackHit);
             }

    }

    Equipment *modelData;
    std::string localData;
};

#endif 

