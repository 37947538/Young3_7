//
//  APPath.cpp
//  Knight3_4
//
//  Created by jl on 15/4/23.
//
//

#include "APPath.h"

//获取路径
std::string APPath::getPath(const std::string& kVersion)
{
    std::string sCurrVersionPath=FileUtils::getInstance()->getWritablePath()+kVersion;
    if(!FileUtils::getInstance()->isDirectoryExist(sCurrVersionPath))
    {
        FileUtils::getInstance()->createDirectory(sCurrVersionPath);
    }
    return sCurrVersionPath+"/"+"data.apm";
}