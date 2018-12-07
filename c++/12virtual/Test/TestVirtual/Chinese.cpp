#include "stdafx.h"
#include "Chinese.h"


PFN_VIRTUALCHS CChinese::m_VirTable[2] = { &CChinese::Speak, &CChinese::Eat };

CChinese::~CChinese()
{
}
