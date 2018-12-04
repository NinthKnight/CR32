#include "stdafx.h"
#include "MyModel.h"


CMyModel::CMyModel()
{
    //初始化当前的数据
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {    
            m_mapData[i][j] = g_mapData[i][j];
        }
    
    }





}


CMyModel::~CMyModel()
{
}
