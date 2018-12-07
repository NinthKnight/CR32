/*请为主板类制定好接口，使得它可以兼容符合此标准接口的声卡，网卡，显卡等(都用类实现，相应的接口即为函数统一标准即为统一函数)。*/
#include <iostream>

class CMotherBoard
{
public:
    virtual void Sounding(int i) {}
    virtual void Networking(int i) {}
    virtual void Display(int i) {}
};


class CSoundCardA : public CMotherBoard
{
public:
    void Sounding(int i)
    {
        std::cout << "声卡A工作。" << std::endl;
    }
};
class CSoundCardB : public CMotherBoard
{
public:
    void Sounding(int i)
    {
        std::cout << "声卡B工作。" << std::endl;
    }
};
class CNetCardA : public CMotherBoard
{
public:
    void Networking(int i)
    {
        std::cout << "网卡A工作。" << std::endl;
    }
};
class CNetCardB : public CMotherBoard
{
public:
    void Networking(int i)
    {
        std::cout << "网卡B工作。" << std::endl;
    }
};

class CDisplayCardA : public CMotherBoard
{
public:
    void Display(int i)
    {
        std::cout << "显卡A工作。" << std::endl;
    }
};
class CDisplayCardB : public CMotherBoard
{
public:
    void Display(int i)
    {
        std::cout << "显卡B工作。" << std::endl;
    }
};
int main()
{
    CSoundCardA soundCard;
    CNetCardB netCard;
    CDisplayCardA displayCard;

    ((CMotherBoard*)&soundCard)->Sounding(1);
    ((CMotherBoard*)&netCard)->Networking(1);
    ((CMotherBoard*)&displayCard)->Display(1);

}
