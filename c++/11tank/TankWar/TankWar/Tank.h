#pragma once
class CTank
{
public:
    CTank(int nType = 0, int nRotate = 0,int nCurX = 0, int nCurY = 0);
    ~CTank();

    void OnUp();
    void OnDown();
    void OnLeft();
    void OnRight();


    int CurX() { return m_nCurX; }
    int CurY() { return m_nCurY; }

    void SetCurX(int X) {
        m_nCurX = X;
    }

    void SetCurY(int Y) {
        m_nCurY = Y;
    }

public:
    int m_nRotate;
    int m_nType;

private:
    int m_nCurX;
    int m_nCurY;
};

