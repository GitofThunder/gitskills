#include "MacroVariable.h"

USING_NS_CC;

const SMaterialConfig MATERIAL_CONFIG[MI_MAX] =
{
    {MI_XIANGJIAO, "xiangjiao.png", 0, 200, "xihongshi_pian.png", 5, "banana.csb"},
    {MI_XIHONGSHI, "xihongshi.png", 0, 200, "xihongshi_pian.png", 5, "tamato.csb"},
    {MI_JITUI, "xiangjiao.png", 0, 200, "xihongshi_pian.png", 5, "banana.csb"},
    {MI_BOLUO, "boluo.png", 0, 300, "boluo_pian.png", 5, "tamato.csb"}
};

const MATERIAL_ID FRIDGE_CONFIG[FOOD_COUNT] =
{
    MI_XIANGJIAO, MI_XIANGJIAO, MI_XIANGJIAO,
    MI_BOLUO, MI_BOLUO, MI_XIANGJIAO,
    MI_XIANGJIAO, MI_XIANGJIAO, MI_XIANGJIAO,
    MI_BOLUO, MI_BOLUO, MI_XIANGJIAO,
    MI_BOLUO, MI_BOLUO, MI_XIANGJIAO,
    MI_XIANGJIAO, MI_XIANGJIAO, MI_XIANGJIAO
};