

//#define _USE_ICONV
#ifndef __TOOL_COMMON_CPP__
#define __TOOL_COMMON_CPP__

#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include "windows.h"

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif



#ifdef _USE_ICONV
#include "iconv.h"
#endif

#define LOCALCARRAY(name, len) \
	char name[len]; \
	memset(name, 0, len); \


//檢查輸入值是否為數字(浮點數)
	bool  CKIsCharPointerIsFloat(char *str);
	char  *CKCharPointerFIxtoFloatNumCharPoint(char* str,char* out_str);


//===========================
//判斷是否為  數字字串
//==========================
bool IsNumeric(char* lstr);
//是否為正整數
bool IsNumericPInt(char* lstr);
//是否為整數
bool IsNumericInt(char* lstr);
//是否為16進位正整數
bool IsHEXNumeric(char* lstr);
//===========================
//修正非數字字串  
//==========================


/**
 *
 *  @brief  轉換 char 16 進制資料(0~f)成 10 進制資料.
 *
 *  @param  const char cCh : 16 進制資料.
 *
 *  @retval  unsigned char : 回傳的 10 進制資料.
 *
 *	@remark 從 CaXml::HexTextConvert copy 來的.
 *
 */
unsigned char HexTextConvert(const char cCh);


/**
 *
 *  @brief  把16進表示的字串(例:  1caabbff),轉成10進的unsignd long .
 *
 *  @param  char *pcStr : 16進表示的字串.
 *
 *  @retval  unsigned long : 回傳10進的unsignd long.
 *
 */
unsigned long CharToUN(char *pcStr);



#ifdef _USE_ICONV
	/**
	 *
	 *  @brief  安全的 ICONV_OPEN.
	 *
	 *  @param  iconv_t &p : handle. 
	 *  @param  char* totype : 轉成什麼code.
	 *  @param  char* fromtype : 由什麼code.
	 *
	 */
	bool SAFE_ICONV_OPEN(iconv_t &p, char* totype, char* fromtype);
	bool UTF8ToWchar(wchar_t* io_DestBuffer, long outlen, char* i_Src, long inlen);
	bool CharToWchar(wchar_t* io_DestBuffer, long outlen, char* i_Src, long inlen);
	bool WcharToUTF8(char* io_DestBuffer, long outlen, wchar_t* i_Src, long inlen);


#endif
	
	//分析出DB裡的自行定義的換行符號(\\n).
	void ParserNewLine(char* io_DestBuffer , char* i_Src);

	void ParserNewLine(wchar_t* io_DestBuffer , wchar_t* i_Src);

//由路徑中分析出副檔名.
void GetExtname(char* isrc, char* o_buffer);
void GetExtname(wchar_t* isrc, wchar_t* o_buffer);

//由路徑中分析路徑.
void GetPath(char* isrc, char* o_buffer);
void GetPath(wchar_t* isrc, wchar_t* o_buffer);

//由路徑中分析檔名.
void GetFilename(char* isrc, char* o_buffer, bool withExt = true);
void GetFilename(wchar_t* isrc, wchar_t* o_buffer, bool withExt = true);

//計算該路徑往上幾層 CalUpLevel("../../../media/sound/", &outstr), 回傳 3, outstr = media/sound/
int CalUpLevel(std::string path, std::string *outstr);

//路徑往上移. updir("d:1/2/3/4/5/", 2) , 回傳 d:/1/2/3/
std::string updir(std::string path, int lv);

//計算出相對於工作目錄, 該相對路徑的最終真實路徑
// CalFiledir("d:/work/1/2/exe", "../media/sound/a.wav"),  回傳 d:/work/1/2/media/sound/a.wav
std::string CalFiledir(std::string workdir, std::string reldir);

//===============================================================================
//utf8計算字數用. http://zh.wikipedia.org/wiki/UTF8    .
//===============================================================================
long Utf8Len(const char *utf8str);

//===============================================================================
//去除xml裡的 <font> </font> tag, 還原原文.
//===============================================================================
std::string StripFontTag(char* buffer);


inline bool	RectCollidePoint( RECT rc,POINT point )	{if(rc.left<point.x&&rc.right>point.x)if(rc.bottom>point.y&&rc.top<point.y){return true;}return false;}


/*
unsigned char* src : 來源貼圖的 buffer.
unsigned char *dest : 目地 buffer.
long textureX : 來源貼圖的大小 x.
long textureY : 來源貼圖的大小 y.
long pixelByte : 一個 pixel 佔多少 byte.
long blockPosX : 取出貼圖中 block pixel 起點的位子 x.
long blockPosY: 取出貼圖中 block pixel 起點的位子 y.
long blockSizeX : 取出貼圖中block pixel 大小 x.
long blockSizeY : 取出貼圖中block pixel 大小 Y.
*/
void CopyTextureBlockToBlock(unsigned char* src, unsigned char *dest,
							 long textureX, long textureY, long pixelByte, 
							 long blockPosX, long blockPosY, 
							 long blockSizeX, long blockSizeY);

void CopyBlockToTextureBlock(char* src, char *dest,
							 long textureX, long textureY,
							 long srcPixelByte, long destPixelByte,
							 long texturePosX, long texturePosY, 
							 long blockSizeX, long blockSizeY);




//===============================================================================
//分析 CSV 字串用.
//===============================================================================
void ParseCSVParmeters(std::string sourcestr, std::vector<std::string> *destvec);

#endif
