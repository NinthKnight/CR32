#ifndef CIMAGEBUF
#define CIMAGEBUF

#include <stdio.h>
#include <string.h>
#define USER 9000
#define BMP  USER+1
#define PCX  USER+2
#define JPG  USER+3
#define GIF  USER+4
#define TGA  USER+5


#define System32
#ifdef System32
	typedef short int integer;
#else
	typedef int integer;
#endif

class CImageBuf  
{
	public:
		bool LoadPcx(char sFile[]);
		void FreeBuf();
		bool CopyImage(int x, int y, int w, int h,unsigned char* &buf);
		CImageBuf();
		virtual ~CImageBuf();
		unsigned char *BufPtr;		
		int Width;			
		int Height;

	protected:
		struct PcxStruct
		{
			char manufacturer;
			char version;
			char encodeing;
			char bits_per_pixel;
			integer xmin,ymin;
			integer xmax,ymax;
			integer hres;
			integer vres;
			char palette[48];
			char reserved;
			char color_planes;
			integer pixel_per_line;
			integer palette_type;
			char filler[58];
		};
		
		
		unsigned char **pSmallImageBuf;
		int CountSmallImage;
		int SmallImageBufSize;
};



#endif 	
