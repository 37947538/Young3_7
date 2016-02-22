#ifndef __MyProjectName_DayRewardModelBLL_H__
#define __MyProjectName_DayRewardModelBLL_H__

#include "DayRewardModel.h"

/**
 k_ClassDes
 */

#define DayRewardModel_MaxData 7


class DayRewardModelBLL : public Ref
{
public:
    static DayRewardModelBLL *create(const std::string& localPath)
    {
        DayRewardModelBLL *pRet = new(std::nothrow) DayRewardModelBLL();
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

    ~DayRewardModelBLL()
    {
        if(modelData)
        {
            delete[] modelData;
        }
    }
    
    DayRewardModelBLL()
    {
        modelData=new DayRewardModel[DayRewardModel_MaxData];
    }
    
    //获取数据源的大小
    int getModelSize() { return DayRewardModel_MaxData; };
    
    //加载资源数据
    bool loadResData(const std::string& resPath)
    {
        
        //bool result=false;
        //FILE *readFile = fopen(resPath.c_str(), "rb");
        //if (readFile)
        //{
        //    fread(modelData, sizeof(DayRewardModel), DayRewardModel_MaxData, readFile);
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
        unsigned char* currBuff=&buff[140352];    //140352 内存文件存在位置
        
        //判断对象大小
        memcpy(modelData, currBuff, DayRewardModel_MaxData*sizeof(DayRewardModel));
        return true;
    }
    
    //保存沙箱数据
    bool saveData()
    {
        bool result=false;
        
        //读取内存
        Data dt=FileUtils::getInstance()->getDataFromFile(localData.c_str());
        unsigned char* buff= dt.getBytes();
        unsigned char* currBuff=&buff[140352];    //140352 内存文件存在位置
        memcpy(currBuff,modelData, DayRewardModel_MaxData*sizeof(DayRewardModel));
        
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
               printf("DayRewardID[%d]",m->DayRewardID);
               printf("Name[%s]",m->Name);
               printf("Func[%s]",m->Func);
             }

    }

    DayRewardModel *modelData;
    std::string localData;
};

#endif 

