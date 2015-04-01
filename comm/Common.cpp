#include "stdafx.h"

//#define _USE_CRC_TABLE

#include "common.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>

#ifdef _USE_CRC_TABLE
#include "baseinclude.h"
#endif

	//==========================
	bool  CKIsCharPointerIsFloat(char *str)
	{
		int len=0;
		len =strlen(str);
		bool onlyOneDot=0;

		if (len == 0)   //�S����J�ƭ�
			return false;

		//�����J��L�r��
		for (int i = 0; i < len; ++i)
		{	
			char ch=str[i];
			if (ch==45 || ch == 46 || ch >= 48 && ch <= 57 )//45�O - 46�O"." 48~57 ��0~9  
			{


				if(ch==46 && onlyOneDot==true)
					return false;

				if(ch==46)
					onlyOneDot=true;			
				continue;
			}
			else//�J��Ĥ@�ӫD�Ʀr�άO�D�p���I���r���N���}
				return false;
		}
		return true;
	
	}
	char *CKCharPointerFIxtoFloatNumCharPoint(char* str,char *out_str)
	{
		int len=0;
		int i=0;
		len =strlen(str);
		bool onlyOneDot=0;

		if (len == 0)   //�S����J�ƭ�
			return false;


		//�����J��L�r��
		for ( i = 0; i < len; ++i)
		{	
			
			char ch=str[i];

			//�Y�p�ƮɥX�{�b�̫e�� . �N�]�� 0.
			if(i==0 && ch==46)
			{
				strcpy(out_str, "0");
			}
			
			if (ch == 46 || ch >= 48 && ch <= 57)//46�O"." 48~57 ��0~9  
			{
				
				ch=str[i];
				//�X�{��2�� . �N���z��
				if(ch==46 && onlyOneDot==true)
					continue;
			
				strcat(out_str, &ch);
				
				//�X�{�Ĥ@��  . �n�O�d�U��
				if(ch==46)
					onlyOneDot=true;			
				continue;
			}
			else//�J��Ĥ@�ӫD�Ʀr�άO�D�p���I���r���N���}
				continue;
		}
		//������. �令 .0
		i=strlen(out_str);
		char ch=out_str[i-1];
		if(ch==46)
		 strcat(out_str,"0\0");
		return out_str;
		
	}
	//========================�r���ഫ

	unsigned char HexTextConvert(const char cCh)
	{
		if (cCh >= '0' && cCh <= '9') return cCh - '0';

		if (cCh >= 'A' && cCh <= 'F') return (cCh - 'A') + 10;

		return 0;
	}

	unsigned long CharToUN(char *pcStr)
	{
		unsigned long unRet = 0;
		if (pcStr)
		{
			strupr((char *)pcStr);
			char *pcStrReg;
			unsigned long i, unLen, unN, unDouble, unTotal;
			unLen = (unsigned long)strlen(pcStr);
			if (unLen >= 8) unLen = 8;
			unTotal = 0;
			unDouble = 1;
			for (i = 1; i <= unLen; i ++)
			{
				pcStrReg = (char *)pcStr + (unLen - i);

				unN = HexTextConvert(*pcStrReg);
				unN *= unDouble;
				unTotal += unN;

				unDouble = (unsigned long)pow(16.0f, (float)i);
			}
			unRet = unTotal;
			return unRet;
		}
		return 0;
	}



bool IsHEXNumeric(char* lstr)
{
	for (long i = 0; i < (long)strlen(lstr); i++)
	{
		
		//0~9.
		if ( !(
				(lstr[i] >= 48) && (lstr[i] <= 57) ||
				(lstr[i] >= 65) && (lstr[i] <= 70) ||
				(lstr[i] >= 97) && (lstr[i] <= 102)
			 )
			
			)
		{
			return false;
		}

	}

	return true;
}
#ifdef _USE_ICONV	

	bool SAFE_ICONV_OPEN(iconv_t &p, char* totype, char* fromtype)
	{
		p = libiconv_open(totype, fromtype);
		if (p == (iconv_t) - 1)
		{
			p = 0;
			return false;
		}
		return true;
	};


	/**
	 *
	 *  @brief  �w���� close iconv handl.
	 *
	 *  @param  p : new �X�Ӫ��������.
	 *
	 */
	#define	SAFE_ICONV_CLOSE(p)	\
		{						\
			iconv_close(p);		\
			p = NULL;		\
		}


	/**
	 *
	 *  @brief  �ˬd��X�L�{���S�����~,�M��LOG�X��.
	 *
	 *  @param  res : ���G.
	 *
	 */
	#define ICONV_ERR_CHECK(res, file, line) {\
		if (res == (size_t)(-1))\
		{\
			if (errno == EILSEQ)\
			{\
				CaUtility::getSingleton().SystemLog("An invalid multibyte sequence has been encountered in the input.", file, line);\
			}\
			else if (errno == EINVAL)\
			{\
				CaUtility::getSingleton().SystemLog("An incomplete multibyte sequence has been encountered in the input.", file, line);\
			}\
			else if (errno == E2BIG)\
			{\
				CaUtility::getSingleton().SystemLog("There is not sufficient room at *outbuf.", file, line);\
			}\
		}\
	}

	bool CharToWchar(wchar_t* io_DestBuffer, long outlen, char* i_Src, long inlen)
	{

		iconv_t cd;
		SAFE_ICONV_OPEN(cd, "wchar_t", "char");
		
		if (!cd) return false;
		
		char *outptr = (char*)io_DestBuffer;
		size_t outsize = outlen * 2;
		char *inptr = (char*)i_Src;
		size_t insize;
		
		if (-1 == inlen)
		{
			insize = strlen(inptr);
		}
		else
		{
			insize = inlen;
		}
		
		iconv(cd, 0, 0, 0, 0);
		
		size_t res = iconv(cd, (char**) & inptr, &insize, &outptr, &outsize);
		
		SAFE_ICONV_CLOSE(cd);
		return true;
	}
	
	bool UTF8ToWchar(wchar_t* io_DestBuffer, long outlen, char* i_Src, long inlen)
	{
		iconv_t cd;
		SAFE_ICONV_OPEN(cd, "wchar_t", "UTF-8");
		
		if (!cd) return false;
		
		char *outptr = (char*)io_DestBuffer;
		size_t outsize = outlen * 2;
		char *inptr = (char*)i_Src;
		size_t insize;
		
		if (-1 == inlen)
		{
			insize = strlen(i_Src);//wcslen((wchar_t*)inptr) * 2;
		}
		else
		{
			insize = inlen;
		}
		
		iconv(cd, 0, 0, 0, 0);
		
		size_t res = iconv(cd, (char**) & inptr, &insize, &outptr, &outsize);
		
		SAFE_ICONV_CLOSE(cd);
		return true;
	}

	bool WcharToUTF8(char* io_DestBuffer, long outlen, wchar_t* i_Src, long inlen)
	{
		iconv_t cd;
		SAFE_ICONV_OPEN(cd, "UTF-8", "wchar_t");

		if (!cd) return false;

		char *outptr = (char*)io_DestBuffer;
		size_t outsize = outlen;
		char *inptr = (char*)i_Src;
		size_t insize;

		if (-1 == inlen)
		{
			insize = wcslen(i_Src) * sizeof(wchar_t);
		}
		else
		{
			insize = inlen * sizeof(wchar_t);
		}

		iconv(cd, 0, 0, 0, 0);
		size_t res = iconv(cd, (char**) & inptr, &insize, &outptr, &outsize);

		if (res == 0)
			return true;
		else
			return false;

	}

#endif
	//=====================================
	
	//=====================================

	long	KSStrToLong(const char *e_string)
	{ 
		return atol(e_string); 
	};
	//=====================================
	
	//=====================================

	long KSStrToLong(const wchar_t *e_string)
	{
		return _wtol(e_string);
	}

	//=====================================
	
	//=====================================

	int	KSStrToInt(const char *e_sz)
	{
		return atoi(e_sz);
	}

	//=====================================
	
	//=====================================

	double	KSStrToFloat(const char *e_string )
	{
		return atof(e_string); 
	};

	//=====================================
	
	//=====================================

	double	KSStrToFloat(const wchar_t *e_string )
	{
		return _wtof(e_string);
	}

	//=====================================
	
	//=====================================
	
	char *KSIntToStr(__int64 e_iValue)
	{
		char *l_string=NULL;
		return _i64toa(e_iValue,l_string,10);
	}

	//=====================================
	
	//=====================================

	char *KSDoubleToStr(double value)
	{		
		char* l_ReturnChar=new char[sizeof(value)];	
		return	_gcvt(value,15,l_ReturnChar);
	}

	//=====================================

	//=====================================

	char  *KSIntToStr(int e_iValue)
	{
		char l_tmp[15];
		return itoa(e_iValue,l_tmp,10);	
	}

	//=====================================

	//=====================================

#ifdef _USE_CRC_TABLE

unsigned long GetCRC(FILE *fp)
{
    register unsigned long crc;
    int c;

    crc = 0xFFFFFFFF;
    while( (c=getc(fp)) != EOF )
	{
         crc = ((crc>>8) & 0x00FFFFFF) ^ una_CRCTable[ (crc^c) & 0xFF ];
    }

    return( crc^0xFFFFFFFF );
}

unsigned long GetCRC(char *cp, unsigned long len)
{
    register unsigned long crc;

    crc = 0xFFFFFFFF;
	char c = *(cp);
    while(0 != len)
	{
        crc = ((crc>>8) & 0x00FFFFFF) ^ una_CRCTable[ (crc^c) & 0xFF ];

		c = *(cp++);
		len--;
    }

    return( crc^0xFFFFFFFF );
}

#endif

	//���R�XDB�̪��ۦ�w�q������Ÿ�(\\n).
	void ParserNewLine(char* io_DestBuffer , char* i_Src)
	{

		//���R�XDB�̪��ۦ�w�q������Ÿ�(\\n).
		long newlones = 0;
		long descsize = (long)strlen(i_Src);
		
		
		char *p = i_Src;
		char *nextp = 0;
		for (long i = 0 ; i < descsize; i++)
		{
			if (i + 1 >= descsize)
				nextp = p;
			else
				nextp = p + 1;
				
			if ((*p == '\\') && (*nextp == 'n'))
			{
				newlones++;
				strcat(io_DestBuffer, "\n");
				p++;
				i++;
			}
			else
			{
				char c;
				c = *p;
				sprintf(io_DestBuffer, "%s%c", io_DestBuffer, c);
			}
			
			p++;
		}
		
	}

	void ParserNewLine(wchar_t* io_DestBuffer , wchar_t* i_Src)
	{

		//���R�XDB�̪��ۦ�w�q������Ÿ�(\\n).
		long newlones = 0;
		long descsize = (long)wcslen(i_Src);
		
		wchar_t *p = i_Src;
		wchar_t *nextp = 0;
		for (long i = 0 ; i < descsize; i++)
		{
			if (i + 1 >= descsize)
				nextp = p;
			else
				nextp = p + 1;
				
			if ((*p == L'\\') && (*nextp == L'n'))
			{
				newlones++;
				wcscat(io_DestBuffer, L"\n");
				p++;
				i++;
			}
			else
			{
				wchar_t c;
				c = *p;
				swprintf(io_DestBuffer, L"%s%c", io_DestBuffer, c);
			}
			
			p++;
		}
	}

	
//===========================
//�P�_�O�_��  �Ʀr�r��
//==========================
bool IsNumeric(char* lstr)
{
    char szTmp[MAX_PATH]="";
    if(!*lstr)
        return false;
    sscanf(lstr," %[.,0-9,-]",szTmp);
    if(strcmp(lstr,szTmp))
        return false;
    if(char *p=strstr(szTmp,"."))
        if(p=strstr(p+1 , "."))
            return false;

	if(char *p=strstr(szTmp,"-"))
        if(p=strstr(p+1 , "-"))
            return false;
	
	//�Y�Ĥ@��Ƭ�-��(.��),�B���׬�1�h��J���~
	char ch=lstr[0],ch2;
	if(( ch==45 || ch==46 ) && strlen(lstr)==1  )
	 return false;
	//�Y��2��~�}�l��- ,�p 0-�h���~
	if(char* p=strstr(szTmp+1,"-"))
		return false;

	//�Y- .���Ʀb�@�_,�h��J���~
	if(strlen(lstr)>1)
	{
		int len=strlen(lstr);
		for(int i=0;i<len;i++)
		{
			ch=lstr[i];
			ch2=lstr[i+1];
			if( (ch ==45 || ch ==46 ) && (ch2==45 || ch2==46 ))
			return false;
		}
	}
    return true;
}

//�O�_�������
bool IsNumericPInt(char* lstr)
{
    char szTmp[MAX_PATH]="";
    if(!*lstr)
        return false;
    sscanf(lstr," %[0-9]",szTmp);
    if(strcmp(lstr,szTmp))
        return false;
    if(char *p=strstr(szTmp,"."))
        return false;

	return true;
}

//�O�_�����
bool IsNumericInt(char* lstr)
{
    char szTmp[MAX_PATH]="";
    if(!*lstr)
        return false;
    sscanf(lstr," %[0-9,-]",szTmp);
    if(strcmp(lstr,szTmp))
        return false;

	if(char *p=strstr(szTmp,"-"))
        if(p=strstr(p+1 , "-"))
            return false;
	
	//�Y�Ĥ@��Ƭ�-��(.��),�B���׬�1�h��J���~
	char ch=lstr[0],ch2;
	if(( ch==45 ) && strlen(lstr)==1  )
	 return false;
	//�Y��2��~�}�l��- ,�p 0-�h���~
	if(char* p=strstr(szTmp+1,"-"))
		return false;

    return true;
}

//=================
void GetExtname(char* isrc, char* o_buffer)
{
	char *point = strrchr(isrc,'.');
	if(!point)
	{
	}
	else
	{
		strcpy(o_buffer, point + 1);
	}
}

void GetExtname(wchar_t* isrc, wchar_t* o_buffer)
{
	wchar_t *point = wcsrchr(isrc,'.');
	if(!point)
	{
	}
	else
	{
		wcscpy(o_buffer, point + 1);
	}
}


void GetPath(char* isrc, char* o_buffer)
{
	int isrcsize = strlen(isrc);
	char *pcbuffer = new char[isrcsize + 1];
	sprintf(pcbuffer, isrc);
	char *point = strrchr(pcbuffer,'\\');
	
	if(!point)
	{
		point = strrchr(pcbuffer,'/');
	}

	if(!point)
	{
		strcpy(o_buffer, pcbuffer);
	}
	else
	{
		*(point + 1) = '\0';
		strcpy(o_buffer, pcbuffer);
	}

	delete pcbuffer;
}

void GetPath(wchar_t* isrc, wchar_t* o_buffer)
{
	int isrcsize = wcslen(isrc);
	wchar_t *pcbuffer = new wchar_t[isrcsize + 1];
	wcscpy(pcbuffer, isrc);
	wchar_t *point = wcsrchr(pcbuffer,'\\');
	
	if(!point)
	{
		point = wcsrchr(pcbuffer,'/');
	}

	if(!point)
	{
		wcscpy(o_buffer, pcbuffer);
	}
	else
	{
		*(point + 1) = '\0';
		wcscpy(o_buffer, pcbuffer);
	}

	delete pcbuffer;
}

void GetFilename(char* isrc, char* o_buffer, bool withExt)
{

	char *point = strrchr(isrc,'\\');
	if(!point)
	{
		point = strrchr(isrc,'/');
	}

	if(!point)
	{
		strcpy(o_buffer, isrc);
	}
	else
	{
		strcpy(o_buffer, point + 1);
	}

	int isrcsize = strlen(isrc);
	if (!isrcsize)
	{
		return;
	}

	if (withExt)
	{
		return;
	}

	char *pcbuffer = new char[isrcsize + 1];
	strcpy(pcbuffer, o_buffer);
	point = strrchr(pcbuffer,'.');
	if(!point)
	{
		strcpy(o_buffer, pcbuffer);
	}
	else
	{
		*(point) = '\0';
		strcpy(o_buffer, pcbuffer);
	}

	delete pcbuffer;
}

void GetFilename(wchar_t* isrc, wchar_t* o_buffer, bool withExt)
{

	wchar_t *point = wcsrchr(isrc,'\\');
	if(!point)
	{
		point = wcsrchr(isrc,'/');
	}

	if(!point)
	{
		wcscpy(o_buffer, isrc);
	}
	else
	{
		wcscpy(o_buffer, point + 1);
	}

	int isrcsize = wcslen(o_buffer);
	if (!isrcsize)
	{
		return;
	}

	if (withExt)
	{
		return;
	}

	wchar_t *pcbuffer = new wchar_t[isrcsize + 1];
	wcscpy(pcbuffer, o_buffer);
	point = wcsrchr(pcbuffer,'.');
	if(!point)
	{
		wcscpy(o_buffer, pcbuffer);
	}
	else
	{
		*(point) = '\0';
		wcscpy(o_buffer, pcbuffer);
	}

	delete pcbuffer;
}

int CalUpLevel(std::string path, std::string *outstr)
{
	std::string tmpstr = path;
	int skipch = 3;
	int idx = tmpstr.find("../");
	if (idx == std::string::npos || idx > 0)
	{
		idx = tmpstr.find("..\\");
	}

	int updircount = 0;
	while (idx != std::string::npos)
	{
		updircount++;
		if ((idx + skipch) < tmpstr.size())
		{
			tmpstr = tmpstr.substr(idx + skipch);
		}

		idx = tmpstr.find("../");
		if (idx == std::string::npos || idx > 0)
		{
			idx = tmpstr.find("..\\");
		}

	}

	if (outstr)
	{
		*outstr = tmpstr;
	}

	return updircount;
}

std::string updir(std::string path, int lv)
{
	std::string tmpstr = path;
	
	//�����ɤW / ,
	int idxlast1 = tmpstr.find_last_of("/");
	int idxlast2 = tmpstr.find_last_of("\\");
	int idxmaxlast = max(idxlast1, idxlast2);
	if (idxmaxlast != std::string::npos && idxmaxlast != tmpstr.size() - 1)
	{
		tmpstr.append("/");
	}
	
	int idx = -1;
	int idx1 = tmpstr.find_last_of("/");
	int idx2 = tmpstr.find_last_of("\\");
	idx = max(idx1, idx2);
	
	int lvcount = 0;
	while (lvcount < lv && idx != std::string::npos)
	{
		lvcount++;
		if (idx < tmpstr.size())
		{
			tmpstr = tmpstr.substr(0, idx - 1);
		}

		idx1 = tmpstr.find_last_of("/");
		idx2 = tmpstr.find_last_of("\\");
		idx = max(idx1, idx2);

	}

	return tmpstr;
}

std::string CalFiledir(std::string workdir, std::string reldir)
{
	std::string tmpstr1;
	std::string tmpstr2;
	int uplv = CalUpLevel(reldir, &tmpstr1);
	tmpstr2 = updir(workdir, uplv);

	return tmpstr2 + tmpstr1;
}

//===============================================================================
//utf8�p��r�ƥ�. http://zh.wikipedia.org/wiki/UTF8    .
//===============================================================================
long Utf8Len(const char *utf8str)
{
	//�Ѧ� http://zh.wikipedia.org/wiki/UTF8    .
	//* ���UTF-8�s�X�������N�줸��B�A�p�GB���Ĥ@�쬰0�A�hB��ASCII�X�A�åBB�W�ߪ���ܤ@�Ӧr��;
    //* �p�GB���Ĥ@�쬰1�A�ĤG�쬰0�A�hB���@�ӫDASCII�r���]�Ӧr���Ѧh�Ӧ줸�ժ�ܡ^�����@�Ӧ줸�աA�åB�����r�����Ĥ@�Ӧ줸�սs�X;
    //* �p�GB���e��쬰1�A�ĤT�쬰0�A�hB���@�ӫDASCII�r���]�Ӧr���Ѧh�Ӧ줸�ժ�ܡ^�����Ĥ@�Ӧ줸�աA�åB�Ӧr���Ѩ�Ӧ줸�ժ��;
    //* �p�GB���e�T�쬰1�A�ĥ|�쬰0�A�hB���@�ӫDASCII�r���]�Ӧr���Ѧh�Ӧ줸�ժ�ܡ^�����Ĥ@�Ӧ줸�աA�åB�Ӧr���ѤT�Ӧ줸�ժ��;
    //* �p�GB���e�|�쬰1�A�Ĥ��쬰0�A�hB���@�ӫDASCII�r���]�Ӧr���Ѧh�Ӧ줸�ժ�ܡ^�����Ĥ@�Ӧ줸�աA�åB�Ӧr���ѥ|�Ӧ줸�ժ��;
	long len = strlen(utf8str);
	long count = 0;
	long index = 0;

	unsigned char Byte4 = 0xF0; //11110000.
	unsigned char Byte3 = 0xE0; //11100000.
	unsigned char Byte2 = 0xC0; //11000000.
	unsigned char Byte1 = 0x80; //10000000.

	for (long i = 0; i < len; i)
	{
		if ((utf8str[i] & Byte4) == Byte4)
		{
			count++;
			i+=4;
		}
		else if ((utf8str[i] & Byte3) == Byte3)
		{
			count++;
			i+=3;		
		}
		else if ((utf8str[i] & Byte2) == Byte2)
		{
			count++;
			i+=2;		
		}
		else if ((utf8str[i] & Byte1) == Byte1)
		{
		    //* �p�GB���Ĥ@�쬰1�A�ĤG�쬰0�A�hB���@�ӫDASCII�r���]�Ӧr���Ѧh�Ӧ줸�ժ�ܡ^�����@�Ӧ줸�աA�åB�����r�����Ĥ@�Ӧ줸�սs�X;
			//�N�O�����O�r,
			i++;			
		}
		else
		{
			//���L���s�X.
			if (utf8str[i] == '\t' || utf8str[i] == '\r' || utf8str[i] == '\n')
			{
				i++;			
			}
			else
			{
				count++;
				i++;
			}
		}
	}

	return count;
}

//===============================================================================
//�h��xml�̪� <font> </font> tag, �٭���.
//===============================================================================
std::string StripFontTag(char* buffer)
{
	unsigned char Byte4 = 0xF0; //11110000.
	unsigned char Byte3 = 0xE0; //11100000.
	unsigned char Byte2 = 0xC0; //11000000.
	unsigned char Byte1 = 0x80; //10000000.

	std::string out;
	long len = strlen(buffer);

	std::string tmp = buffer;
	std::string tagstr1;
	
	char *strbuffer = new char[len+1];
	memset(strbuffer, 0, len+1);

	long i = 0;
	long j = 0;
	long pos = 0;
	long posstart = 0;

	long starttagpos = 0;
	bool findfontstarttag = false;
	bool findfontendtag = false;
	bool findfontpair = false;
	for (i = 0; i < len;)
	{
		
		//�u�w��ANSI�r��.
		if ( ((buffer[i] & Byte4) != Byte4)
			&& ((buffer[i] & Byte3) != Byte3) 
			&& ((buffer[i] & Byte2) != Byte2) 
			&& ((buffer[i] & Byte1) != Byte1)
			)
		{
			//�u�w��ANSI�r��.
			//�o�{���b.
			if (buffer[i] == '<')
			{
				for (j = i; j < len; j++)
				{
					//�o�{�k�b.
					if (buffer[j] == '>')
					{
						tagstr1 = tmp.substr(i, j - i + 1);

						//�p�G�w���<font >.
						if (findfontstarttag)
						{
							//�N��</font >.
							if (std::string::npos != tagstr1.find("</font"))
							{
								findfontendtag = true;					
								i = j + 1;
								findfontpair = true;
								starttagpos = i;
								posstart = pos;
							}
						
						}
						else
						{
							//��<font >.
							if (std::string::npos != tagstr1.find("<font"))
							{
								findfontstarttag = true;
								starttagpos = i;
								posstart = pos;
								i = j + 1;
							}
						}
						break;
					}					
				}		
			}
		}

		//��tag�~���rcopy�i��.
		if (i < len)
		{
			strbuffer[pos] = buffer[i];
			pos++;
		}

		//���@���,�N�M�����p.
		if (findfontpair)
		{
			findfontstarttag = false;
			findfontendtag = false;	
			findfontpair = false;		
		}

		i++;

		//�����_�l��,�����̫�F�٧䤣�쵲����.
		if (findfontstarttag)
		{
			if (i >= len)
			{
				//�N�^�Y��copy.				
				pos = posstart;
				for (long k = starttagpos; k < len; k++)
				{
					strbuffer[pos] = buffer[k];
					pos++;
				}
			}
		}


	}

	out = strbuffer;

	delete [] strbuffer;
	return out;
}

void CopyTextureBlockToBlock(unsigned char* src, unsigned char *dest,
							 long textureX, long textureY, long pixelByte, 
							 long blockPosX, long blockPosY, 
							 long blockSizeX, long blockSizeY)
{
	
	//����t��.
	if (blockPosX < 0)
		blockPosX = 0;
	if (blockPosY < 0)
		blockPosY = 0;

	//Ū��������.
	long readblockposX = blockPosX;
	long readblockposY = blockPosY;
	unsigned char *write = dest;


	for (long col = 0; col < blockSizeY; col++ )
	{
		for (long row = 0; row < blockSizeX; row++ )
		{
			//��X�}�C����pos.
			long readpos = (readblockposX + (readblockposY * textureX)) * pixelByte;

			//���X����.
			unsigned char *srcblock = &src[readpos];

			//���XpixelByte��byte.
			for (long rb = 0; rb < pixelByte; rb++)
			{
				*write++ = *srcblock++;
			}
			//x����W�[.
			readblockposX++;
		}

		//x����_��.
		readblockposX = blockPosX;
		//y����W�[.
		readblockposY++;
	}
}

void CopyBlockToTextureBlock(char* src, char *dest,
							 long textureX, long textureY,
							 long srcPixelByte, long destPixelByte,
							 long texturePosX, long texturePosY, 
							 long blockSizeX, long blockSizeY)
{

	
	//����t��.
	if (texturePosX < 0)
		texturePosX = 0;
	if (texturePosX < 0)
		texturePosX = 0;


	//�g�J������.
	long writeblockposX = texturePosX;
	long writeblockposY = texturePosY;
	char *write = dest;


	for (long col = 0; col < blockSizeY; col++ )
	{
		for (long row = 0; row < blockSizeX; row++ )
		{
			//��X�}�C����pos.
			long writepos = (writeblockposX + (writeblockposY * textureX)) * srcPixelByte;

			//���X����.
			char *write = &dest[writepos];

			//���XpixelByte��byte.
			for (long rb = 0; rb < destPixelByte; rb++)
			{
				*write++ = *src++;
			}
			//x����W�[.
			writeblockposX++;
		}

		//x����_��.
		writeblockposX = texturePosX;
		//y����W�[.
		writeblockposY++;
	}

}

void ParseCSVParmeters(std::string sourcestr, std::vector<std::string> *destvec)
{
	destvec->clear();
	std::string s = sourcestr;
    static const std::basic_string <char>::size_type npos = -1;
    s+=","; //�קK�̫�@��O�Ŧr��ɨS���
    //Clear();
    unsigned int P=0,p,p2;
    std::string tmp;
    for(;P<s.size();)
    {
        p=static_cast<unsigned>(s.find_first_not_of(" \t",P));  //�j�M�D�ťթ�Tab
        if(p==npos) break;  //�w�L�D�ťթ�Tab�r���A�ѪR����
        tmp="";
        if(s[p]=='\"')  //���޸��}�Y
        {
            p++;
            for(;;)
            {
                p2=static_cast<unsigned>(s.find_first_of('\"',p));
                if(s[p2+1]!='\"')
                    break;
            
                tmp+=s.substr(p,p2-p+1);
                p=p2+2;
            }
            tmp+=s.substr(p,p2-p);
            destvec->push_back(tmp);
            P=p2+2;
        }
        else    //�D���޸��}�Y
        {
            p2=static_cast<unsigned>(s.find_first_of(",",p));   //�j�M�r�I
            if(p2==npos)    //�̫�@�Ӧr��
            {
                destvec->push_back(s.substr(p,s.size()-p));
                P=static_cast<unsigned>(s.size());
            }
            else    //�᭱�i���٦��r��
            {
                destvec->push_back(s.substr(p,p2-p));
                P=p2+1;
            }
        }
    }
}


