#include <iostream>
/*
5.����һ���кܶ����ݳ�Ա���࣬��Щ��Ա�ֲ���public
,private��protected��ָ���������С�����һ����Ա����showMap()
,�ó�Ա������ӡ����Щ���ݳ�Ա�����ֺ����ǵĵ�ַ������п��ܣ�
�ڶ��������������ϵͳ�б�������������򣬿�Ŀ������в���
�Ƿ�һ����
*/

class classA
{
private:
  int priA;
  int priB;
protected:
  int proA;
  int proB;
public:
  int pubA;
  int pubB;

  void showMap()
  {
    printf("private:\r\n");
    printf("\tpriA\t0x%p\r\n", &this->priA);
    printf("\tpriB\t0x%p\r\n", &this->priB);

    printf("\r\nprotected:\r\n");
    printf("\tproA\t0x%p\r\n", &this->proA);
    printf("\tproB\t0x%p\r\n", &this->proB);

    printf("\r\npublic:\r\n");
    printf("\tpubA\t0x%p\r\n", &this->pubA);
    printf("\tpubA\t0x%p\r\n", &this->pubB);
  }
};

int main()
{
  classA ca;
  ca.showMap();

  getchar();
  return 0;
}