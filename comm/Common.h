

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


//�ˬd��J�ȬO�_���Ʀr(�B�I��)
	bool  CKIsCharPointerIsFloat(char *str);
	char  *CKCharPointerFIxtoFloatNumCharPoint(char* str,char* out_str);


//===========================
//�P�_�O�_��  �Ʀr�r��
//==========================
bool IsNumeric(char* lstr);
//�O�_�������
bool IsNumericPInt(char* lstr);
//�O�_�����
bool IsNumericInt(char* lstr);
//�O�_��16�i�쥿���
bool IsHEXNumeric(char* lstr);
//===========================
//�ץ��D�Ʀr�r��  
//==========================


/**
 *
 *  @brief  �ഫ char 16 �i����(0~f)�� 10 �i����.
 *
 *  @param  const char cCh : 16 �i����.
 *
 *  @retval  unsigned char : �^�Ǫ� 10 �i����.
 *
 *	@remark �q CaXml::HexTextConvert copy �Ӫ�.
 *
 */
unsigned char HexTextConvert(const char cCh);


/**
 *
 *  @brief  ��16�i��ܪ��r��(��:  1caabbff),�ন10�i��unsignd long .
 *
 *  @param  char *pcStr : 16�i��ܪ��r��.
 *
 *  @retval  unsigned long : �^��10�i��unsignd long.
 *
 */
unsigned long CharToUN(char *pcStr);



#ifdef _USE_ICONV
	/**
	 *
	 *  @brief  �w���� ICONV_OPEN.
	 *
	 *  @param  iconv_t &p : handle. 
	 *  @param  char* totype : �ন����code.
	 *  @param  char* fromtype : �Ѥ���code.
	 *
	 */
	bool SAFE_ICONV_OPEN(iconv_t &p, char* totype, char* fromtype);
	bool UTF8ToWchar(wchar_t* io_DestBuffer, long outlen, char* i_Src, long inlen);
	bool CharToWchar(wchar_t* io_DestBuffer, long outlen, char* i_Src, long inlen);
	bool WcharToUTF8(char* io_DestBuffer, long outlen, wchar_t* i_Src, long inlen);


#endif
	
	//���R�XDB�̪��ۦ�w�q������Ÿ�(\\n).
	void ParserNewLine(char* io_DestBuffer , char* i_Src);

	void ParserNewLine(wchar_t* io_DestBuffer , wchar_t* i_Src);

//�Ѹ��|�����R�X���ɦW.
void GetExtname(char* isrc, char* o_buffer);
void GetExtname(wchar_t* isrc, wchar_t* o_buffer);

//�Ѹ��|�����R���|.
void GetPath(char* isrc, char* o_buffer);
void GetPath(wchar_t* isrc, wchar_t* o_buffer);

//�Ѹ��|�����R�ɦW.
void GetFilename(char* isrc, char* o_buffer, bool withExt = true);
void GetFilename(wchar_t* isrc, wchar_t* o_buffer, bool withExt = true);

//�p��Ӹ��|���W�X�h CalUpLevel("../../../media/sound/", &outstr), �^�� 3, outstr = media/sound/
int CalUpLevel(std::string path, std::string *outstr);

//���|���W��. updir("d:1/2/3/4/5/", 2) , �^�� d:/1/2/3/
std::string updir(std::string path, int lv);

//�p��X�۹��u�@�ؿ�, �Ӭ۹���|���̲ׯu����|
// CalFiledir("d:/work/1/2/exe", "../media/sound/a.wav"),  �^�� d:/work/1/2/media/sound/a.wav
std::string CalFiledir(std::string workdir, std::string reldir);

//===============================================================================
//utf8�p��r�ƥ�. http://zh.wikipedia.org/wiki/UTF8    .
//===============================================================================
long Utf8Len(const char *utf8str);

//===============================================================================
//�h��xml�̪� <font> </font> tag, �٭���.
//===============================================================================
std::string StripFontTag(char* buffer);


inline bool	RectCollidePoint( RECT rc,POINT point )	{if(rc.left<point.x&&rc.right>point.x)if(rc.bottom>point.y&&rc.top<point.y){return true;}return false;}


/*
unsigned char* src : �ӷ��K�Ϫ� buffer.
unsigned char *dest : �ئa buffer.
long textureX : �ӷ��K�Ϫ��j�p x.
long textureY : �ӷ��K�Ϫ��j�p y.
long pixelByte : �@�� pixel ���h�� byte.
long blockPosX : ���X�K�Ϥ� block pixel �_�I����l x.
long blockPosY: ���X�K�Ϥ� block pixel �_�I����l y.
long blockSizeX : ���X�K�Ϥ�block pixel �j�p x.
long blockSizeY : ���X�K�Ϥ�block pixel �j�p Y.
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
//���R CSV �r���.
//===============================================================================
void ParseCSVParmeters(std::string sourcestr, std::vector<std::string> *destvec);

#endif
