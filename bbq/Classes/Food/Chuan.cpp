#include "Chuan.h"

CChuan::CChuan()
{
    m_eFoodType = FT_ORIGIN;
}

CChuan::~CChuan()
{
    
}

CChuan* CChuan::create(const char *pszFileName)
{
    CChuan* pRet = new (std::nothrow) CChuan();
    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}


bool CChuan::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    
    schedule(schedule_selector(CChuan::myUpdate));
    return true;
}

void CChuan::myUpdate(float fEscapeTime)
{
    
}

