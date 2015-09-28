#include "Soup.h"

CSoup::CSoup()
{
    m_eFoodType = FT_ORIGIN;
}

CSoup::~CSoup()
{
    
}

CSoup* CSoup::create(const char *pszFileName)
{
    CSoup* pRet = new (std::nothrow) CSoup();
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


bool CSoup::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    
    schedule(schedule_selector(CSoup::myUpdate));
    return true;
}

void CSoup::myUpdate(float fEscapeTime)
{
    
}

