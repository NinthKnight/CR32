#pragma once
class CRefCount
{
public:
  CRefCount();
  ~CRefCount();
  void Add();
  bool Dec();
  bool isSingle();

private:
  int m_nCount;
};

