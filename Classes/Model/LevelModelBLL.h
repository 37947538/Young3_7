#ifndef __MyProjectName_LevelModelBLL_H__
#define __MyProjectName_LevelModelBLL_H__

#include "LevelModel.h"

/**
 k_ClassDes
 */

#define LevelModel_MaxData 50


class LevelModelBLL : public Ref
{
public:
    static LevelModelBLL *create(const std::string& localPath)
    {
        LevelModelBLL *pRet = new(std::nothrow) LevelModelBLL();
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

    ~LevelModelBLL()
    {
        if(modelData)
        {
            delete[] modelData;
        }
    }
    
    LevelModelBLL()
    {
        modelData=new LevelModel[LevelModel_MaxData];
    }
    
    //获取数据源的大小
    int getModelSize() { return LevelModel_MaxData; };
    
    //加载资源数据
    bool loadResData(const std::string& resPath)
    {
        
        //bool result=false;
        //FILE *readFile = fopen(resPath.c_str(), "rb");
        //if (readFile)
        //{
        //    fread(modelData, sizeof(LevelModel), LevelModel_MaxData, readFile);
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
        unsigned char* currBuff=&buff[22552];    //22552 内存文件存在位置
        
        //判断对象大小
        memcpy(modelData, currBuff, LevelModel_MaxData*sizeof(LevelModel));
        return true;
    }
    
    //保存沙箱数据
    bool saveData()
    {
        bool result=false;
        
        //读取内存
        Data dt=FileUtils::getInstance()->getDataFromFile(localData.c_str());
        unsigned char* buff= dt.getBytes();
        unsigned char* currBuff=&buff[22552];    //22552 内存文件存在位置
        memcpy(currBuff,modelData, LevelModel_MaxData*sizeof(LevelModel));
        
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
               printf("LevelID[%d]",m->LevelID);
               printf("LevelState[%d]",m->LevelState);
               printf("LevelName[%s]",m->LevelName);
               printf("MapFile[%s]",m->MapFile);
               printf("LevelHigth[%0.2f]",m->LevelHigth);
               printf("LevelWidth[%d]",m->LevelWidth);
               printf("BackgroundFile[%s]",m->BackgroundFile);
               printf("Interval[%d]",m->Interval);
               printf("AttackTimer[%s]",m->AttackTimer);
             }

    }

    LevelModel *modelData;
    std::string localData;
};

#endif 

