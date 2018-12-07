#include "stdafx.h"
#include "Imagebuf.h"

CImageBuf::CImageBuf()
{
	CountSmallImage=0;
	SmallImageBufSize=50;
	pSmallImageBuf=new unsigned char *[50];
	BufPtr=NULL;
}

CImageBuf::~CImageBuf()
{
	if(BufPtr!=NULL)
	{
		delete []BufPtr;
		BufPtr=NULL;
	}
}


bool CImageBuf::LoadPcx(char sFile[])
{
	if(BufPtr!=NULL)
	{
		delete []BufPtr;
		BufPtr=NULL;
	}


	unsigned char *TempBuf;
	FILE *fp;
	fp=fopen(sFile,"rb");
	if(fp==NULL)
	{
		return false;
	}
	PcxStruct PcxHead;
	fread(&PcxHead,sizeof(PcxHead),1,fp);
	
	Width=PcxHead.pixel_per_line;
	Height=PcxHead.ymax;

	int GOffset=Width;
	int BOffset=Width*2;



	BufPtr=new unsigned char[Width*4*Height];
	int Byte_per_line=Width*3;		
	TempBuf=new unsigned char[Byte_per_line];		

	fseek(fp,128,SEEK_SET);
	for(int i=0;i<PcxHead.ymax;i++)
	{
		int Sum=0;
		int CountByte;
		unsigned char c;
		do
		{
			fread(&c,1,1,fp);
			c=c&0xff;
			if((c&0xc0)==0xc0)
			{
				CountByte=c&0x3f;
				fread(&c,1,1,fp);
				while(CountByte--)
				{
					TempBuf[Sum++]=c;

				}
			}
			else
			{
				TempBuf[Sum++]=c;
			}
		}while(Sum<Byte_per_line);

		for(int j=0;j<Width;j++)
		{
			long TempPos=(Height-i-1)*Width*4+j*4;
	//		int TempPos=(PcxHead.ymax-i-1)*PcxHead.pixel_per_line*4+j*4;
			BufPtr[TempPos++]=TempBuf[j];
			BufPtr[TempPos++]=TempBuf[j+GOffset];
			BufPtr[TempPos++]=TempBuf[j+BOffset];
			if((TempBuf[j]==0)&&(TempBuf[j+GOffset]==0)&&(TempBuf[j+BOffset]==0))
			{
				BufPtr[TempPos++]=0;
			}
			else
			{
				BufPtr[TempPos++]=255;
			}
		}
	}
	delete []TempBuf;
	return true;
}



bool CImageBuf::CopyImage(int x, int y, int w, int h, unsigned char *&buf)
{
	register int i;
	if(x+w>Width)
	{
		w=Width-x;
	}
	if(y+h>Height)
	{
		h=Height-y;
	}
	buf=new unsigned char[w*h*4];
	
	if(!buf)
	{
		return false;
	}
	long TempPos2=0,TempPos;
	long tempx=x*4;
	TempPos=y*Width*4+tempx;

	long LineByte=Width*4;
	int TempLineByte;
	TempLineByte=w*4;
	for(i=0;i<h;i++)
	{
		memcpy(&buf[TempPos2],&BufPtr[TempPos],TempLineByte);
		TempPos2+=TempLineByte;
		TempPos+=LineByte;
	}

	return true;
}

void CImageBuf::FreeBuf()
{
	if(BufPtr!=NULL)
	{
		delete []BufPtr;
		BufPtr=NULL;
	}
}

