#ifndef __MyProjectName_PlayerModelBLL_H__
#define __MyProjectName_PlayerModelBLL_H__

#include "PlayerModel.h"

/**
 k_ClassDes
 */

#define PlayerModel_MaxData 1


class PlayerModelBLL : public Ref
{
public:
    static PlayerModelBLL *create(const std::string& localPath)
    {
        PlayerModelBLL *pRet = new(std::nothrow) PlayerModelBLL();
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

    ~PlayerModelBLL()
    {
        if(modelData)
        {
            delete[] modelData;
        }
    }
    
    PlayerModelBLL()
    {
        modelData=new PlayerModel[PlayerModel_MaxData];
    }
    
    //获取数据源的大小
    int getModelSize() { return PlayerModel_MaxData; };
    
    //加载资源数据
    bool loadResData(const std::string& resPath)
    {
        
        //bool result=false;
        //FILE *readFile = fopen(resPath.c_str(), "rb");
        //if (readFile)
        //{
        //    fread(modelData, sizeof(PlayerModel), PlayerModel_MaxData, readFile);
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
        unsigned char* currBuff=&buff[0];    //0 内存文件存在位置
        
        //判断对象大小
        memcpy(modelData, currBuff, PlayerModel_MaxData*sizeof(PlayerModel));
        return true;
    }
    
    //保存沙箱数据
    bool saveData()
    {
        bool result=false;
        
        //读取内存
        Data dt=FileUtils::getInstance()->getDataFromFile(localData.c_str());
        unsigned char* buff= dt.getBytes();
        unsigned char* currBuff=&buff[0];    //0 内存文件存在位置
        memcpy(currBuff,modelData, PlayerModel_MaxData*sizeof(PlayerModel));
        
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
               printf("PlayerID[%d]",m->PlayerID);
               printf("Dia[%d]",m->Dia);
               printf("Gold[%d]",m->Gold);
               printf("SelectHeroID[%d]",m->SelectHeroID);
               printf("BuyHeroID[%d]",m->BuyHeroID);
               printf("OpenLevelID[%d]",m->OpenLevelID);
               printf("OpenBossLevelID[%d]",m->OpenBossLevelID);
             }

    }

    PlayerModel *modelData;
    std::string localData;
};

#endif 

