#include "Shala.h"

CShala::CShala()
{
    m_eFoodType = FT_ORIGIN;
}

CShala::~CShala()
{
    
}

CShala* CShala::create(const char *pszFileName)
{
    CShala* pRet = new (std::nothrow) CShala();
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


bool CShala::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    
    schedule(schedule_selector(CShala::myUpdate));
    return true;
}

void CShala::myUpdate(float fEscapeTime)
{
    
}

