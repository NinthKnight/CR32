#include "RefCount.h"
#include <iostream>


CRefCount::CRefCount()
{
  m_nCount = 1;
}

CRefCount::~CRefCount()
{
}

void CRefCount::Add()
{
  m_nCount++;
}

bool CRefCount::Dec()
{
  return --m_nCount == 0;
}

bool CRefCount::isSingle()
{
  return m_nCount == 1;
}
