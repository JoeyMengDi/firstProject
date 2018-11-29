/** 
**	A Template for developing new terminal application
**/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>

BYTE const Key_3DES_1000_0001[] = "3DES_1000_0001_0";
BYTE const Key_3DES_1000_0002[] = "3DES_1000_0002_0";
BYTE const Key_3DES_1000_000A[] = "3DES_1000_000A_0";
BYTE const Key_3DES_2000_0001[] = "3DES_2000_0001_0";

BYTE const Key_3DES_1001_0001[] = "3DES_1001_0001_0";
BYTE const Key_3DES_1001_0002[] = "3DES_1001_0002_0";
BYTE const Key_3DES_1001_000A[] = "3DES_1001_000A_0";
BYTE const Key_3DES_2001_0001[] = "3DES_2001_0001_0";
//BYTE const Key_3DES_2001_0003[] = "3DES_2001_0003_0";
//BYTE const Key_3DES_2001_0004[] = "3DES_2001_0004_0";

BYTE const Key_3DES_1002_0001[] = "3DES_1002_0001_0";

BYTE const Key_3DESDUKPT_1010_0001[] = "3DES_1010_0001_0";
BYTE const Key_3DESDUKPT_1010_0002[] = "3DES_1010_0002_0";
BYTE const Key_3DESDUKPT_1010_000A[] = "3DES_1010_000A_0";
BYTE const Key_3DESDUKPT_2010_0001[] = "3DES_2010_0001_0";

BYTE const KSN[] = "\xFF\xFF\x12\x34\x56\x32\x10\xE0\x00\x00";

BYTE const Key_AES_1020_0001[] = "AES_1020_0001_00";
BYTE const Key_AES_1020_0002[] = "AES_1020_0002_00";
BYTE const Key_AES_1020_000A[] = "AES_1020_000A_00";
BYTE const Key_AES_2020_0001[] = "AES_2020_0001_00";

//BYTE const Key_AES_1021_0001[] = "AES_1021_0001_00";
//BYTE const Key_AES_1021_0002[] = "AES_1021_0002_00";
//BYTE const Key_AES_1021_000A[] = "AES_1021_000A_00";
BYTE const Key_AES_2021_0001[] = "AES_2021_0001_00";
BYTE const Key_AES_2021_0003[] = "AES_2021_0003_00";
BYTE const Key_AES_2021_0004[] = "AES_2021_0004_00";

typedef struct
{
	USHORT M_Len;
	BYTE *pModulus;
	USHORT E_Len;
	BYTE *Exponent;
}RSA_KEY;

RSA_KEY Key_RSA_1030_0001_1024R = 
{
	128,
	"A7A93F7BB662791E41F43BBE3FE39C534DC372834EA454691094ABF77F39F470CF32B08BC18065E8DF1B6A094634AB40F61A0F233F776D07EA4169C7964C955E2DF39C1C2E28F856B589A302C631C58B25413B1F5A5B9C69FD81BF06365686974E1133BF85ADF031BCEF5C4BAA8EF347F77C7E28CEE7D1E43CD7DC370009814F", 
	128,
	"03BECC243F56C3CDE13B4B7A5C830122FB41BA752474974E2188B0AEBEB0D4BD1063D97DC5BCD089FB31E9947B7501BE59C10B45864D6CAA18998D7B5FE8260E0347320750836C2932967C1E8F9E34A41D3FFF56C86C27EF9783C9C3C488C9E4620441C327DC76632C94A9A0EB3E3704B045965F2D961AF80C3EDD9B04732B81"
};
RSA_KEY Key_RSA_1030_0002_1024P = 
{
	128,
	"A7A93F7BB662791E41F43BBE3FE39C534DC372834EA454691094ABF77F39F470CF32B08BC18065E8DF1B6A094634AB40F61A0F233F776D07EA4169C7964C955E2DF39C1C2E28F856B589A302C631C58B25413B1F5A5B9C69FD81BF06365686974E1133BF85ADF031BCEF5C4BAA8EF347F77C7E28CEE7D1E43CD7DC370009814F", 
	3,
	"010001"
};
RSA_KEY Key_RSA_1030_000A_2048R = 
{
	256,
	"B5F4FD7307C24FB47F9012DC47AE8BCCEAA3B5F84CB5D878302A84D3AA3E054ED1A0C2174505B1174011FBD86E308F3A349F1F51A2C317D68F5966A7FE4F1C39566AE5EAAEBBBEEB57AEFC8DD168E2072665271DA7DEE67F033A30E508BB4DF9A54F658E144A89B3A0182B39E8AD0337373BC817A48DEBC7BE0FF43519BF1320AED5CD956053DBCDB6CD6A8739A59BC2CEA0556A2748FA68993005D80C67C89AE2FBD464216DBD2F0076E53A0E0FA04E4A75A71F2380949401DAFAC571244ACF35F163C5CF48546BB865B67C50F5E9576AEFE61C5A89D1B32675693C58E86364DB9188923EFBD41413297A2E9EEEA74ADFB12CF499BAADEF32437BE10BB603A1", 
	256,
	"02E3E656BA6BD2BA4A406E9C432339A342A2E114159BD9D966E27603AAB39B7FFA0274B2CBECE0383F5349CDD14A422C2983D18A896C51E79D954CF5242BFB85C9A29F0E5042393121CE6CC28FEDFB912381FDD211C58FA1BADA64C66E921316011336C8BFF7C322304BD1FBF47F330AE07CB99BEE88369390A84E37BDB5F446CCC17D4F162F03A96231825A99618EFEC8C96056BE7C9A9EBFD28BB1E5334FEBEAA21D70041E470795ADD776252A83F418545271CC8FE2C3DF87556733AAED917409261956E5FFB91312485C750D64755D4FB13695792161648DC89D9403BA1417846B3A45F3E225B642FBCCF939618547DFA4AA7B3B29BFF8A54D45DC582E55"
};
RSA_KEY Key_RSA_2030_0001_2048P = 
{
	256,
	"B5F4FD7307C24FB47F9012DC47AE8BCCEAA3B5F84CB5D878302A84D3AA3E054ED1A0C2174505B1174011FBD86E308F3A349F1F51A2C317D68F5966A7FE4F1C39566AE5EAAEBBBEEB57AEFC8DD168E2072665271DA7DEE67F033A30E508BB4DF9A54F658E144A89B3A0182B39E8AD0337373BC817A48DEBC7BE0FF43519BF1320AED5CD956053DBCDB6CD6A8739A59BC2CEA0556A2748FA68993005D80C67C89AE2FBD464216DBD2F0076E53A0E0FA04E4A75A71F2380949401DAFAC571244ACF35F163C5CF48546BB865B67C50F5E9576AEFE61C5A89D1B32675693C58E86364DB9188923EFBD41413297A2E9EEEA74ADFB12CF499BAADEF32437BE10BB603A1", 
	3,
	"010001"
};


BYTE const SK_24[] = "0123456789ABCDEFGHIJKLMN";
BYTE const TestPAN[] = "4067111122223333";
BYTE const TestLine1Msg[] = "Require 123456";
BYTE const TestLine2Msg[] = "Enter PIN :";
BYTE const TestProcMsg[] = "Get PIN OK";

//==========================================================================================

BYTE ith(BYTE c)
{
	if(c >= '0' && c <= '9')
	{
		return c - '0';
	}
	else if(c >= 'A' && c <= 'F')
	{
		return c - 'A' + 10;
	}
	else if(c >= 'a' && c <= 'f')
	{
		return c - 'a' + 10;
	}
	
	return 0;
}

void Pack(BYTE* pData, USHORT usLen, BYTE* pResult)
{
	USHORT i;
	BYTE v;
	
	for(i = 0; i < usLen; i += 2)
	{
		v = ith(pData[i]);
		v <<= 4;
		v |= ith(pData[i+1]);
		*pResult++ = v;
	}
}

void show_ksn(BYTE* pksn, BYTE x, BYTE y)
{
	char str[100];
	char ss[3];
	int i;

	str[0] = 0;
	for(i = 0; i < 10; ++i)
	{
		sprintf(ss, "%02X", pksn[i]);
		strcat(str, ss);
	}
	CTOS_LCDTPrintXY(1, x, str);
	CTOS_LCDTPrintXY(1, y, &str[16]);
	
}

//==========================================================================================

void Write3DES_Plaintext(void)
{
	USHORT KeySet;
	USHORT KeyIndex;
	CTOS_KMS2KEYWRITE_PARA para;
	USHORT ret;
	BYTE KeyData[16];
	BYTE str[17];
	BYTE key;
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "Write 3DES PT");
	
	//---------------------------------------------------------------------
	// Write 3DES Key in plaintext	
	KeySet = 0x1000;
	KeyIndex = 0x0001;
	memcpy(KeyData, Key_3DES_1000_0001, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_3DES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC | KMS2_KEYATTRIBUTE_KPK;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = KeyData;
	para.Value.KeyLength = 16;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	//---------------------------------------------------------------------
	// Write 3DES Key in plaintext	
	KeySet = 0x1000;
	KeyIndex = 0x0002;
	memcpy(KeyData, Key_3DES_1000_0002, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_3DES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = KeyData;
	para.Value.KeyLength = 16;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	//---------------------------------------------------------------------
	// Write 3DES Key in plaintext	
	KeySet = 0x1000;
	KeyIndex = 0x000A;
	memcpy(KeyData, Key_3DES_1000_000A, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_3DES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = KeyData;
	para.Value.KeyLength = 16;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	//---------------------------------------------------------------------
	// Write 3DES Key in plaintext	
	KeySet = 0x2000;
	KeyIndex = 0x0001;
	memcpy(KeyData, Key_3DES_2000_0001, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_3DES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = KeyData;
	para.Value.KeyLength = 16;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}

	CTOS_LCDTPrintXY(1, 7, "Write Key Done");
__Leave:
	CTOS_KBDGet(&key);
}

void Write3DESDUKPT_Plaintext(void)
{
	USHORT KeySet;
	USHORT KeyIndex;
	CTOS_KMS2KEYWRITE_PARA para;
	USHORT ret;
	BYTE KeyData[16];
	BYTE str[17];
	BYTE key;
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "Write DUKPT PT");
	
	//---------------------------------------------------------------------
	// Write 3DES DUKPT Key in plaintext	
	KeySet = 0x1010;
	KeyIndex = 0x0001;
	memcpy(KeyData, Key_3DESDUKPT_1010_0001, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_3DES_DUKPT;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = KeyData;
	para.Value.KeyLength = 16;
	para.DUKPT_DATA.KSNLength = 10;
	para.DUKPT_DATA.pKSN = (BYTE*)KSN;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	//---------------------------------------------------------------------
	// Write 3DES DUKPT Key in plaintext	
	KeySet = 0x1010;
	KeyIndex = 0x0002;
	memcpy(KeyData, Key_3DESDUKPT_1010_0002, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_3DES_DUKPT;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = KeyData;
	para.Value.KeyLength = 16;
	para.DUKPT_DATA.KSNLength = 10;
	para.DUKPT_DATA.pKSN = (BYTE*)KSN;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	//---------------------------------------------------------------------
	// Write 3DES DUKPT Key in plaintext	
	KeySet = 0x1010;
	KeyIndex = 0x000A;
	memcpy(KeyData, Key_3DESDUKPT_1010_000A, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_3DES_DUKPT;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = KeyData;
	para.Value.KeyLength = 16;
	para.DUKPT_DATA.KSNLength = 10;
	para.DUKPT_DATA.pKSN = (BYTE*)KSN;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	//---------------------------------------------------------------------
	// Write 3DES DUKPT Key in plaintext	
	KeySet = 0x2010;
	KeyIndex = 0x0001;
	memcpy(KeyData, Key_3DESDUKPT_2010_0001, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_3DES_DUKPT;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = KeyData;
	para.Value.KeyLength = 16;
	para.DUKPT_DATA.KSNLength = 10;
	para.DUKPT_DATA.pKSN = (BYTE*)KSN;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	CTOS_LCDTPrintXY(1, 7, "Write Key Done");
__Leave:
	CTOS_KBDGet(&key);	
}

void WriteAES_Plaintext(void)
{
	USHORT KeySet;
	USHORT KeyIndex;
	CTOS_KMS2KEYWRITE_PARA para;
	USHORT ret;
	BYTE KeyData[16];
	BYTE str[17];
	BYTE key;
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "Write AES PT");
	
	//---------------------------------------------------------------------
	// Write AES Key in plaintext	
	KeySet = 0x1020;
	KeyIndex = 0x0001;
	memcpy(KeyData, Key_AES_1020_0001, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_AES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC | KMS2_KEYATTRIBUTE_KPK;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = KeyData;
	para.Value.KeyLength = 16;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	//---------------------------------------------------------------------
	// Write AES Key in plaintext	
	KeySet = 0x1020;
	KeyIndex = 0x0002;
	memcpy(KeyData, Key_AES_1020_0002, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_AES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = KeyData;
	para.Value.KeyLength = 16;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	//---------------------------------------------------------------------
	// Write AES Key in plaintext	
	KeySet = 0x1020;
	KeyIndex = 0x000A;
	memcpy(KeyData, Key_AES_1020_000A, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_AES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = KeyData;
	para.Value.KeyLength = 16;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	//---------------------------------------------------------------------
	// Write AES Key in plaintext	
	KeySet = 0x2020;
	KeyIndex = 0x0001;
	memcpy(KeyData, Key_AES_2020_0001, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_AES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = KeyData;
	para.Value.KeyLength = 16;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}

	CTOS_LCDTPrintXY(1, 7, "Write Key Done");
__Leave:
	CTOS_KBDGet(&key);	
}

void WriteRSA_Plaintext(void)
{
	USHORT KeySet;
	USHORT KeyIndex;
	CTOS_KMS2KEYWRITE_PARA para;
	USHORT ret;
	USHORT M_Len;
	USHORT E_Len;
	BYTE Modulus[256];
	BYTE Exponent[256];
	BYTE str[17];
	BYTE key;
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "Write RSA PT");
	
	//---------------------------------------------------------------------
	// Write RSA Key in plaintext	
	KeySet = 0x1030;
	KeyIndex = 0x0001;	
	Pack((BYTE*)Key_RSA_1030_0001_1024R.pModulus, Key_RSA_1030_0001_1024R.M_Len * 2, Modulus);
	Pack((BYTE*)Key_RSA_1030_0001_1024R.Exponent, Key_RSA_1030_0001_1024R.E_Len * 2, Exponent);
	M_Len = Key_RSA_1030_0001_1024R.M_Len;
	E_Len = Key_RSA_1030_0001_1024R.E_Len;
		
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));	
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_RSA;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = 0;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = Modulus;
	para.Value.KeyLength = M_Len;
	para.Exponent.pValue = Exponent;
	para.Exponent.Length = E_Len;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	//---------------------------------------------------------------------
	// Write RSA Key in plaintext	
	KeySet = 0x1030;
	KeyIndex = 0x0002;	
	Pack((BYTE*)Key_RSA_1030_0002_1024P.pModulus, Key_RSA_1030_0002_1024P.M_Len * 2, Modulus);
	Pack((BYTE*)Key_RSA_1030_0002_1024P.Exponent, Key_RSA_1030_0002_1024P.E_Len * 2, Exponent);
	M_Len = Key_RSA_1030_0002_1024P.M_Len;
	E_Len = Key_RSA_1030_0002_1024P.E_Len;
		
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));	
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_RSA;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = 0;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = Modulus;
	para.Value.KeyLength = M_Len;
	para.Exponent.pValue = Exponent;
	para.Exponent.Length = E_Len;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	//---------------------------------------------------------------------
	// Write RSA Key in plaintext	
	KeySet = 0x1030;
	KeyIndex = 0x000A;	
	Pack((BYTE*)Key_RSA_1030_000A_2048R.pModulus, Key_RSA_1030_000A_2048R.M_Len * 2, Modulus);
	Pack((BYTE*)Key_RSA_1030_000A_2048R.Exponent, Key_RSA_1030_000A_2048R.E_Len * 2, Exponent);
	M_Len = Key_RSA_1030_000A_2048R.M_Len;
	E_Len = Key_RSA_1030_000A_2048R.E_Len;
		
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));	
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_RSA;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = 0;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = Modulus;
	para.Value.KeyLength = M_Len;
	para.Exponent.pValue = Exponent;
	para.Exponent.Length = E_Len;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	//---------------------------------------------------------------------
	// Write RSA Key in plaintext	
	KeySet = 0x2030;
	KeyIndex = 0x0001;	
	Pack((BYTE*)Key_RSA_2030_0001_2048P.pModulus, Key_RSA_2030_0001_2048P.M_Len * 2, Modulus);
	Pack((BYTE*)Key_RSA_2030_0001_2048P.Exponent, Key_RSA_2030_0001_2048P.E_Len * 2, Exponent);
	M_Len = Key_RSA_2030_0001_2048P.M_Len;
	E_Len = Key_RSA_2030_0001_2048P.E_Len;
		
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));	
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_RSA;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = 0;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;
	para.Value.pKeyData = Modulus;
	para.Value.KeyLength = M_Len;
	para.Exponent.pValue = Exponent;
	para.Exponent.Length = E_Len;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	CTOS_LCDTPrintXY(1, 7, "Write Key Done");
__Leave:
	CTOS_KBDGet(&key);	
}

void WriteKeyInPlaintext(void)
{
	Write3DES_Plaintext();
	Write3DESDUKPT_Plaintext();
	WriteAES_Plaintext();
	WriteRSA_Plaintext();
}
	
//------------------------------------------------------------------------------------------
void Write3DES_KPK_with_3DES(void)
{
	USHORT KeySet;
	USHORT KeyIndex;
	USHORT CipherKeySet;
	USHORT CipherKeyIndex;
	CTOS_KMS2KEYWRITE_PARA para;
	USHORT ret;	
	BYTE KeyData[16];
	BYTE CipherKeyData[16];
	BYTE CipherData[24];
	BYTE Zero[16];
	BYTE CCode[16];
	BYTE str[17];
	BYTE key;
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "Write 3DES KPK");
	CTOS_LCDTPrintXY(1, 2, "    with 3DES");
	
	memset(Zero, 0x00, 16);
	
	//---------------------------------------------------------------------
	// Write 3DES Key in KPK
	KeySet = 0x1001;
	KeyIndex = 0x0001;
	memcpy(KeyData, Key_3DES_1001_0001, 16);
	CipherKeySet = 0x1000;
	CipherKeyIndex = 0x0001;
	memcpy(CipherKeyData, Key_3DES_1000_0001, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);

	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));	
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_3DES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_KPK_ECB;
	para.Protection.CipherKeySet = CipherKeySet;
	para.Protection.CipherKeyIndex = CipherKeyIndex;
	CTOS_DES(d_ENCRYPTION, CipherKeyData, 16, KeyData, 16, CipherData);
	para.Value.pKeyData = CipherData;
	para.Value.KeyLength = 16;
	para.Verification.Method = KMS2_KEYVERIFICATIONMETHOD_DEFAULT;	
	CTOS_DES(d_ENCRYPTION, KeyData, 16, Zero, 8, CCode);
	para.Verification.KeyCheckValueLength = 3;
	para.Verification.pKeyCheckValue = CCode;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}

	//---------------------------------------------------------------------
	// Write 3DES Key in KPK
	KeySet = 0x1001;
	KeyIndex = 0x0002;
	memcpy(KeyData, Key_3DES_1001_0002, 16);
	CipherKeySet = 0x1000;
	CipherKeyIndex = 0x0001;
	memcpy(CipherKeyData, Key_3DES_1000_0001, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);

	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));	
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_3DES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_KPK_ECB;
	para.Protection.CipherKeySet = CipherKeySet;
	para.Protection.CipherKeyIndex = CipherKeyIndex;
	CTOS_DES(d_ENCRYPTION, CipherKeyData, 16, KeyData, 16, CipherData);
	para.Value.pKeyData = CipherData;
	para.Value.KeyLength = 16;
	para.Verification.Method = KMS2_KEYVERIFICATIONMETHOD_DEFAULT;	
	CTOS_DES(d_ENCRYPTION, KeyData, 16, Zero, 8, CCode);
	para.Verification.KeyCheckValueLength = 3;
	para.Verification.pKeyCheckValue = CCode;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	//---------------------------------------------------------------------
	// Write 3DES Key in KPK
	KeySet = 0x1001;
	KeyIndex = 0x000A;
	memcpy(KeyData, Key_3DES_1001_000A, 16);
	CipherKeySet = 0x1000;
	CipherKeyIndex = 0x0001;
	memcpy(CipherKeyData, Key_3DES_1000_0001, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);

	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));	
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_3DES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_KPK_ECB;
	para.Protection.CipherKeySet = CipherKeySet;
	para.Protection.CipherKeyIndex = CipherKeyIndex;
	CTOS_DES(d_ENCRYPTION, CipherKeyData, 16, KeyData, 16, CipherData);
	para.Value.pKeyData = CipherData;
	para.Value.KeyLength = 16;
	para.Verification.Method = KMS2_KEYVERIFICATIONMETHOD_DEFAULT;	
	CTOS_DES(d_ENCRYPTION, KeyData, 16, Zero, 8, CCode);
	para.Verification.KeyCheckValueLength = 3;
	para.Verification.pKeyCheckValue = CCode;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}

	//---------------------------------------------------------------------
	// Write 3DES Key in KPK
	KeySet = 0x2001;
	KeyIndex = 0x0001;
	memcpy(KeyData, Key_3DES_2001_0001, 16);
	CipherKeySet = 0x1000;
	CipherKeyIndex = 0x0001;
	memcpy(CipherKeyData, Key_3DES_1000_0001, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);

	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));	
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_3DES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_KPK_ECB;
	para.Protection.CipherKeySet = CipherKeySet;
	para.Protection.CipherKeyIndex = CipherKeyIndex;
	CTOS_DES(d_ENCRYPTION, CipherKeyData, 16, KeyData, 16, CipherData);
	para.Value.pKeyData = CipherData;
	para.Value.KeyLength = 16;
	para.Verification.Method = KMS2_KEYVERIFICATIONMETHOD_DEFAULT;	
	CTOS_DES(d_ENCRYPTION, KeyData, 16, Zero, 8, CCode);
	para.Verification.KeyCheckValueLength = 3;
	para.Verification.pKeyCheckValue = CCode;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}

	CTOS_LCDTPrintXY(1, 7, "Write Key Done");
__Leave:
	CTOS_KBDGet(&key);		
}

void WriteAES_KPK_with_AES(void)
{
	USHORT KeySet;
	USHORT KeyIndex;
	USHORT CipherKeySet;
	USHORT CipherKeyIndex;
	CTOS_KMS2KEYWRITE_PARA para;
	USHORT ret;	
	BYTE KeyData[16];
	BYTE CipherKeyData[16];
	BYTE CipherData[24];
	BYTE Zero[16];
	BYTE CCode[16];
	BYTE str[17];
	BYTE key;
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "Write AES KPK");
	CTOS_LCDTPrintXY(1, 2, "    with AES");
	
	memset(Zero, 0x00, 16);
	
	//---------------------------------------------------------------------
	// Write AES Key in KPK
	KeySet = 0x2021;
	KeyIndex = 0x003;
	memcpy(KeyData, Key_AES_2021_0003, 16);
	CipherKeySet = 0x1020;
	CipherKeyIndex = 0x0001;
	memcpy(CipherKeyData, Key_AES_1020_0001, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);

	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));	
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_AES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_KPK_ECB;
	para.Protection.CipherKeySet = CipherKeySet;
	para.Protection.CipherKeyIndex = CipherKeyIndex;
	CTOS_AES(d_ENCRYPTION, CipherKeyData, KeyData, 16, CipherData);
	para.Value.pKeyData = CipherData;
	para.Value.KeyLength = 16;
	para.Verification.Method = KMS2_KEYVERIFICATIONMETHOD_DEFAULT;	
	CTOS_AES(d_ENCRYPTION, KeyData, Zero, 16, CCode);
	para.Verification.KeyCheckValueLength = 3;
	para.Verification.pKeyCheckValue = CCode;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	//---------------------------------------------------------------------
	// Write AES Key in KPK
	KeySet = 0x2021;
	KeyIndex = 0x004;
	memcpy(KeyData, Key_AES_2021_0004, 16);
	CipherKeySet = 0x1020;
	CipherKeyIndex = 0x0001;
	memcpy(CipherKeyData, Key_AES_1020_0001, 16);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);

	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));	
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_AES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Protection.Mode = KMS2_KEYPROTECTIONMODE_KPK_ECB;
	para.Protection.CipherKeySet = CipherKeySet;
	para.Protection.CipherKeyIndex = CipherKeyIndex;
	CTOS_AES(d_ENCRYPTION, CipherKeyData, KeyData, 16, CipherData);
	para.Value.pKeyData = CipherData;
	para.Value.KeyLength = 16;
	para.Verification.Method = KMS2_KEYVERIFICATIONMETHOD_DEFAULT;	
	CTOS_AES(d_ENCRYPTION, KeyData, Zero, 16, CCode);
	para.Verification.KeyCheckValueLength = 3;
	para.Verification.pKeyCheckValue = CCode;

	ret = CTOS_KMS2KeyWrite(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	CTOS_LCDTPrintXY(1, 7, "Write Key Done");
__Leave:
	CTOS_KBDGet(&key);		
}

void WriteKeyInKPK(void)
{
	Write3DES_KPK_with_3DES();	
	WriteAES_KPK_with_AES();
}

//------------------------------------------------------------------------------------------

void GenerateCertificate(CTOS_KMS2KEYWRITE_PARA *pPara, BOOL IsSHA2, BYTE* CipherData, USHORT* pCipherLength)
{
	RSA_KEY *pRSAkey;
	USHORT index;
	BYTE HashLength;
	BYTE HashData[32];
	BYTE PlainData[512];	
	SHA_CTX stInfo;	
	BYTE Modulus[256];
	BYTE Exponent[256];
	
	pRSAkey = &Key_RSA_1030_0002_1024P;
			
	memset(PlainData, 0xBB, sizeof(PlainData));
	
	// 0, Header
	PlainData[0] = 0x6A;
	// 1, Format
	if(pPara->Info.KeyType == KMS2_KEYTYPE_3DES || pPara->Info.KeyType == KMS2_KEYTYPE_AES)
	{
		PlainData[1] = 0x20;
	}
	else if(pPara->Info.KeyType == KMS2_KEYTYPE_3DES_DUKPT)
	{
		PlainData[1] = 0x21;
	}
	else if(pPara->Info.KeyType == KMS2_KEYTYPE_RSA)
	{
		PlainData[1] = 0x22;
	}
	else
	{
		return;
	}
	// 2, Hash Algorithm
	if(IsSHA2)
	{
		PlainData[2] = 0x01; // SHA2
	}
	else
	{
		PlainData[2] = 0x00; // SHA1
	}
	// 3 to 22, Owner
	memset(&PlainData[3], 0x00, 20); // Current App as the owner
	// 23 to 24, KeySet
	PlainData[23] = (BYTE)(pPara->Info.KeySet >> 8);
	PlainData[24] = (BYTE)(pPara->Info.KeySet & 0xFF);
	// 25 to 26, KeyIndex
	PlainData[25] = (BYTE)(pPara->Info.KeyIndex >> 8);
	PlainData[26] = (BYTE)(pPara->Info.KeyIndex & 0xFF);
	// 27, KeyType
	PlainData[27] = pPara->Info.KeyType;
	// 28, KeyVersion
	PlainData[28] = pPara->Info.KeyVersion;
	// 29 to 32, KeyAttribute
	PlainData[29] = (BYTE)(pPara->Info.KeyAttribute >> 24);
	PlainData[30] = (BYTE)(pPara->Info.KeyAttribute >> 16);
	PlainData[31] = (BYTE)(pPara->Info.KeyAttribute >> 8);
	PlainData[32] = (BYTE)(pPara->Info.KeyAttribute & 0xFF);
	// 33 to 34, KeyLength
	PlainData[33] = (BYTE)(pPara->Value.KeyLength >> 8);
	PlainData[34] = (BYTE)(pPara->Value.KeyLength & 0xFF);
	// 35 to 50/58. KeyData
	memcpy(&PlainData[35], pPara->Value.pKeyData, pPara->Value.KeyLength);
	index = 35 + pPara->Value.KeyLength;
		
	if(pPara->Info.KeyType == KMS2_KEYTYPE_3DES_DUKPT)
	{
		// KSN
		memcpy(&PlainData[index], pPara->DUKPT_DATA.pKSN, pPara->DUKPT_DATA.KSNLength);
		index += pPara->DUKPT_DATA.KSNLength;
	}
	// CheckValueLength
	PlainData[index++] = pPara->Verification.KeyCheckValueLength;
	// CheckValue
	if(pPara->Verification.KeyCheckValueLength)
	{
		memcpy(&PlainData[index], pPara->Verification.pKeyCheckValue, pPara->Verification.KeyCheckValueLength);
		index += pPara->Verification.KeyCheckValueLength;
	}
	// Padding with 0xBB
	// => Done in the initialization of PlainData
	// Hash Data	
	if(IsSHA2)
	{
		CTOS_SHA256_CTX ctx;
		
		HashLength = 32;
		CTOS_SHA256Init(&ctx);
		CTOS_SHA256Update(&ctx, &PlainData[1], pRSAkey->M_Len - 1 - 1 - HashLength);
		CTOS_SHA256Final(&ctx, HashData);		
	}
	else
	{
		HashLength = 20;
		CTOS_SHA1Init(&stInfo);
		CTOS_SHA1Update(&stInfo, &PlainData[1], pRSAkey->M_Len - 1 - 1 - HashLength);
		CTOS_SHA1Final(HashData, &stInfo);		
	}
	memcpy(&PlainData[pRSAkey->M_Len - 1 - HashLength], HashData, HashLength);
	// Tail
	PlainData[pRSAkey->M_Len - 1] = 0xBC;
	
	Pack((BYTE*)pRSAkey->pModulus, pRSAkey->M_Len * 2, Modulus);
	Pack((BYTE*)pRSAkey->Exponent, pRSAkey->E_Len * 2, Exponent);
	
	CTOS_RSA(Modulus, pRSAkey->M_Len, 
			Exponent, pRSAkey->E_Len, PlainData, CipherData);
	
	*pCipherLength = pRSAkey->M_Len;
}

void Write3DES_byCertificate(void)
{
	CTOS_KMS2KEYWRITE_PARA para;
	BYTE CCode[8];
	BYTE Certifcate[256];
	USHORT CertificateLength;
	CTOS_KMS2KEYWRITEBYCERTIFICATE_PARA CertPara;
	USHORT ret;
	BYTE str[17];
	BYTE key;
	USHORT KeySet;
	USHORT KeyIndex;
	//BYTE Zero[8];
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "Write 3DES");
	CTOS_LCDTPrintXY(1, 2, "   with Ceri");
	
	KeySet = 0x1002;
	KeyIndex = 0x0001;
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYWRITE_PARA));	
	para.Version = 0x01;
	para.Info.KeySet = KeySet;
	para.Info.KeyIndex = KeyIndex;
	para.Info.KeyType = KMS2_KEYTYPE_3DES;
	para.Info.KeyVersion = 0x01;
	para.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN | KMS2_KEYATTRIBUTE_ENCRYPT | KMS2_KEYATTRIBUTE_MAC;
	para.Value.KeyLength = 16;
	para.Value.pKeyData = (BYTE*)Key_3DES_1002_0001;
	para.Verification.KeyCheckValueLength = 0;
	para.Verification.pKeyCheckValue = CCode;

	//memset(Zero, 0x00, 8);
	//CTOS_DES(d_ENCRYPTION, (BYTE*)Key_3DES_1002_0001, 16, Zero, 8, CCode);
	
	sprintf(str, "KeySet = %04X", KeySet);
	CTOS_LCDTPrintXY(1, 3, str);
	sprintf(str, "KeyIndex = %04X", KeyIndex);
	CTOS_LCDTPrintXY(1, 4, str);
	
	GenerateCertificate(&para, FALSE, Certifcate, &CertificateLength);
		
	CertPara.Version = 0x01;
	CertPara.Protection.CipherKeySet = 0x1030;
	CertPara.Protection.CipherKeyIndex = 0x0001;
	CertPara.Certificate.Length = CertificateLength;
	CertPara.Certificate.pData = Certifcate;
	
	ret = CTOS_KMS2KeyWriteByCertificate(&CertPara);	
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	CTOS_LCDTPrintXY(1, 7, "Write Key Done");
__Leave:
	CTOS_KBDGet(&key);
}

void WriteKeyInCertificate(void)
{
	Write3DES_byCertificate();
}

//==========================================================================================

void EncryptData_with_3DES(void)
{
	USHORT ret;
	CTOS_KMS2DATAENCRYPT_PARA para;
	BYTE *pCihperKey;
	BYTE CihperKeyLength;
	BYTE str[17];
	BYTE key;	
	BYTE SK_Ciphered[24];
	BYTE plaindata[256];
	BYTE cipherdata[256];	
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "EncryptData");
	CTOS_LCDTPrintXY(1, 2, "    with 3DES");
		
	//---------------------------------------------------------------------	
	CTOS_LCDTPrintXY(1, 3, "ECB");
	pCihperKey = (BYTE*)Key_3DES_1000_0001;
	CihperKeyLength = 16;
	
	memset(&para, 0x00, sizeof(CTOS_KMS2DATAENCRYPT_PARA));
	para.Version = 0x01;
	para.Protection.CipherKeySet = 0x1000;
	para.Protection.CipherKeyIndex = 0x0001;
	para.Protection.CipherMethod = KMS2_DATAENCRYPTCIPHERMETHOD_ECB;
	para.Protection.SK_Length = 0;

	memset(plaindata, 0x00, sizeof(plaindata));
	para.Input.Length = sizeof(plaindata);
	para.Input.pData = plaindata;
	para.Output.pData = cipherdata;

	ret = CTOS_KMS2DataEncrypt(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	CTOS_LCDTPrintXY(1, 3, "ECB OK");
	
	
	//---------------------------------------------------------------------	
	CTOS_LCDTPrintXY(1, 4, "ECB with SK");
	pCihperKey = (BYTE*)SK_24;
	CihperKeyLength = strlen(SK_24);
	CTOS_DES(d_ENCRYPTION, (BYTE*)Key_3DES_1000_0002, 16, pCihperKey, CihperKeyLength, SK_Ciphered);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2DATAENCRYPT_PARA));	
	para.Version = 0x01;
	para.Protection.CipherKeySet = 0x1000;
	para.Protection.CipherKeyIndex = 0x0002;
	para.Protection.CipherMethod = KMS2_DATAENCRYPTCIPHERMETHOD_ECB;
	para.Protection.SK_Length = strlen(SK_24);
	para.Protection.pSK = SK_Ciphered;
		
	memset(plaindata, 0x00, sizeof(plaindata));
	para.Input.Length = sizeof(plaindata);
	para.Input.pData = plaindata;
	para.Output.pData = cipherdata;

	ret = CTOS_KMS2DataEncrypt(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}

	CTOS_LCDTPrintXY(1, 4, "ECB with SK OK");
	
	//---------------------------------------------------------------------	
	CTOS_LCDTPrintXY(1, 3, "ECB");
	pCihperKey = (BYTE*)Key_3DES_1002_0001;
	CihperKeyLength = 16;
	
	memset(&para, 0x00, sizeof(CTOS_KMS2DATAENCRYPT_PARA));
	para.Version = 0x01;
	para.Protection.CipherKeySet = 0x1002;
	para.Protection.CipherKeyIndex = 0x0001;
	para.Protection.CipherMethod = KMS2_DATAENCRYPTCIPHERMETHOD_ECB;
	para.Protection.SK_Length = 0;

	memset(plaindata, 0x00, sizeof(plaindata));
	para.Input.Length = sizeof(plaindata);
	para.Input.pData = plaindata;
	para.Output.pData = cipherdata;

	ret = CTOS_KMS2DataEncrypt(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	CTOS_LCDTPrintXY(1, 5, "ECB OK");
	
	CTOS_LCDTPrintXY(1, 7, "EncryptData Done");
__Leave:
	CTOS_KBDGet(&key);	
}


void EncryptData_with_AES(void)
{
	USHORT ret;
	CTOS_KMS2DATAENCRYPT_PARA para;
	BYTE *pCihperKey;
	BYTE CihperKeyLength;
	BYTE str[17];
	BYTE key;	
	BYTE SK_Ciphered[16];
	BYTE plaindata[256];
	BYTE cipherdata[256];
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "EncryptData");
	CTOS_LCDTPrintXY(1, 2, "    with AES");
		
	//---------------------------------------------------------------------	
	CTOS_LCDTPrintXY(1, 3, "ECB");
	pCihperKey = (BYTE*)Key_AES_1020_0001;
	CihperKeyLength = 16;
	
	memset(&para, 0x00, sizeof(CTOS_KMS2DATAENCRYPT_PARA));
	para.Version = 0x01;
	para.Protection.CipherKeySet = 0x1020;
	para.Protection.CipherKeyIndex = 0x0001;
	para.Protection.CipherMethod = KMS2_DATAENCRYPTCIPHERMETHOD_ECB;
	para.Protection.SK_Length = 0;

	memset(plaindata, 0x00, sizeof(plaindata));
	para.Input.Length = sizeof(plaindata);
	para.Input.pData = plaindata;
	para.Output.pData = cipherdata;

	ret = CTOS_KMS2DataEncrypt(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	CTOS_LCDTPrintXY(1, 3, "ECB OK");	
	
	//---------------------------------------------------------------------	
	CTOS_LCDTPrintXY(1, 4, "ECB with SK");
	pCihperKey = (BYTE*)SK_24;
	CihperKeyLength = 16;
	CTOS_AES(d_ENCRYPTION, (BYTE*)Key_AES_1020_0002, pCihperKey, CihperKeyLength, SK_Ciphered);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2DATAENCRYPT_PARA));	
	para.Version = 0x01;
	para.Protection.CipherKeySet = 0x1020;
	para.Protection.CipherKeyIndex = 0x0002;
	para.Protection.CipherMethod = KMS2_DATAENCRYPTCIPHERMETHOD_ECB;
	para.Protection.SK_Length = CihperKeyLength;
	para.Protection.pSK = SK_Ciphered;
		
	memset(plaindata, 0x00, sizeof(plaindata));
	para.Input.Length = sizeof(plaindata);
	para.Input.pData = plaindata;
	para.Output.pData = cipherdata;

	ret = CTOS_KMS2DataEncrypt(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}

	CTOS_LCDTPrintXY(1, 4, "ECB with SK OK");	
	
	CTOS_LCDTPrintXY(1, 7, "EncryptData Done");
__Leave:
	CTOS_KBDGet(&key);	
}


void EncryptData_with_RSA(void)
{
	CTOS_KMS2RSAENCRYPT_PARA para;
	USHORT ret;
	BYTE str[17];
	BYTE key;
	BYTE Modulus[256];
	BYTE Exponent[256];
	RSA_KEY *pRSAkey;
	USHORT CipherKeyLength;
	BYTE plaindata[256];
	BYTE cipherdata[256];
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "EncryptData");
	CTOS_LCDTPrintXY(1, 2, "    with RSA");
	

	memset(plaindata, 0xBB, sizeof(plaindata));
	plaindata[0] = 0x6A;
	memset(cipherdata, 0x00, sizeof(cipherdata));
	
	//---------------------------------------------------------------------		
	pRSAkey = &Key_RSA_1030_0001_1024R;
	CipherKeyLength = pRSAkey->M_Len;
	Pack((BYTE*)pRSAkey->pModulus, pRSAkey->M_Len * 2, Modulus);
	Pack((BYTE*)pRSAkey->Exponent, pRSAkey->E_Len * 2, Exponent);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2RSAENCRYPT_PARA));
	para.Version = 0x01;
	para.Protection.CipherKeySet = 0x1030;
	para.Protection.CipherKeyIndex = 0x0001;
	para.Protection.CipherMethod = KMS2_RSAENCRYPTCIPHERMETHOD_DEFAULT;
	para.Input.Length = CipherKeyLength;
	para.Input.pData = plaindata;
	para.Output.pData = cipherdata;
	ret = CTOS_KMS2RSAEncrypt(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	CTOS_LCDTPrintXY(1, 3, "RSA Encrypt OK");
		
	//---------------------------------------------------------------------		
	pRSAkey = &Key_RSA_1030_000A_2048R;
	CipherKeyLength = pRSAkey->M_Len;
	Pack((BYTE*)pRSAkey->pModulus, pRSAkey->M_Len * 2, Modulus);
	Pack((BYTE*)pRSAkey->Exponent, pRSAkey->E_Len * 2, Exponent);
	
	memset(&para, 0x00, sizeof(CTOS_KMS2RSAENCRYPT_PARA));
	para.Version = 0x01;
	para.Protection.CipherKeySet = 0x1030;
	para.Protection.CipherKeyIndex = 0x000A;
	para.Protection.CipherMethod = KMS2_RSAENCRYPTCIPHERMETHOD_DEFAULT;
	para.Input.Length = CipherKeyLength;
	para.Input.pData = plaindata;
	para.Output.pData = cipherdata;
	ret = CTOS_KMS2RSAEncrypt(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	CTOS_LCDTPrintXY(1, 5, "RSA Encrypt OK");	
	
	CTOS_LCDTPrintXY(1, 7, "EncryptData Done");
__Leave:
	CTOS_KBDGet(&key);		
}

void EncryptData(void)
{
	EncryptData_with_3DES();
	EncryptData_with_AES();
	EncryptData_with_RSA();
}

void GenerateMAC_with_3DES(void)
{
	CTOS_KMS2MAC_PARA para;
	USHORT ret;
	BYTE str[17];
	BYTE key;
	BYTE *pCipherKey;
	BYTE CipherKeyLength;
	BYTE Zero[8];
	BYTE plaindata[255];
	BYTE macdata[8];
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "Generate MAC");
	
	memset(Zero, 0x00, sizeof(Zero));
	memset(plaindata, 0x55, sizeof(plaindata));
		
	//---------------------------------------------------------------------		
	pCipherKey = (BYTE*)Key_3DES_1001_0001;
	CipherKeyLength = 16;
	
	memset(&para, 0x00, sizeof(CTOS_KMS2MAC_PARA));
	para.Version = 0x01;
	para.Protection.CipherKeySet = 0x1001;
	para.Protection.CipherKeyIndex = 0x0001;
	para.Protection.CipherMethod = KMS2_MACMETHOD_CBC;
	para.ICV.Length = 8;
	para.ICV.pData = Zero;
	para.Input.Length = sizeof(plaindata);
	para.Input.pData = plaindata;
	para.Output.pData = macdata;
	
	ret = CTOS_KMS2MAC(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	CTOS_LCDTPrintXY(1, 3, "GenerateMAC OK");
		
	CTOS_LCDTPrintXY(1, 7, "GenerateMAC Done");
__Leave:
	CTOS_KBDGet(&key);		
}

void MAC(void)
{
	GenerateMAC_with_3DES();
}

void GetKeyInfo(void)
{
	USHORT ret;
	BYTE str[17];
	BYTE key;	
	CTOS_KMS2KEYGETINFO_PARA para;
	BYTE *pCipherKey;	
	BYTE CipherKeyLength;	
	BYTE CCode[8];	
	BYTE Hash[32];		
	BYTE Len;
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "GetKeyInfo");
	
	
	//---------------------------------------------------------------------	
	pCipherKey = (BYTE*)Key_3DES_1000_0001;
	CipherKeyLength = 16;
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYGETINFO_PARA));
	para.Version = 0x01;	
	para.Input.KeySet = 0x1000;
	para.Input.KeyIndex = 0x0001;
	para.Input.CVLen = 3;
	para.Input.HashAlgorithm = 0x00;
	para.Output.pCV = CCode;
	para.Output.pHash = Hash;

	ret = CTOS_KMS2KeyGetInfo(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
		
	CTOS_LCDTPrintXY(1, 3, "GetInfo 3DES OK");
	//---------------------------------------------------------------------		
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYGETINFO_PARA));
	para.Version = 0x01;	
	para.Input.KeySet = 0x1030;
	para.Input.KeyIndex = 0x0001;
	para.Input.CVLen = 0;
	para.Input.HashAlgorithm = KMS2_HASH_ALGORITHM_SHA1;
	para.Output.pCV = CCode;
	para.Output.pHash = Hash;

	ret = CTOS_KMS2KeyGetInfo(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	CTOS_LCDTPrintXY(1, 4, "GetInfo RSA OK");
	
	//---------------------------------------------------------------------		
	
	memset(&para, 0x00, sizeof(CTOS_KMS2KEYGETINFO_PARA));
	para.Version = 0x01;	
	para.Input.KeySet = 0x1030;
	para.Input.KeyIndex = 0x000A;
	para.Input.CVLen = 0;
	para.Input.HashAlgorithm = KMS2_HASH_ALGORITHM_SHA2;
	para.Output.pCV = CCode;
	para.Output.pHash = Hash;

	ret = CTOS_KMS2KeyGetInfo(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	CTOS_LCDTPrintXY(1, 5, "GetInfo RSA OK");

	CTOS_LCDTPrintXY(1, 7, "GetKeyInfo Done");
__Leave:
	CTOS_KBDGet(&key);	
}

void UserData(void)
{
	USHORT ret;
	BYTE str[17];
	BYTE key;
	BYTE WriteData[16 * 1024];
	BYTE ReadData[16 * 1024];
	DWORD Offset;
	USHORT TotalLen;
	USHORT Len;
	DWORD i;

	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "UserData");
	
	
	for(i = 0; i < sizeof(WriteData); ++i)
	{
		WriteData[i] = (BYTE)i;
	}

	Offset = 0;
	TotalLen = 16 * 1024;
	while(TotalLen)
	{
		if(TotalLen > 2048)
		{
			Len = 2048;
		}
		else
		{
			Len = TotalLen;
		}
		
		ret = CTOS_KMS2UserDataWrite(FALSE, Offset, &WriteData[Offset], Len);
		if(ret != d_OK)
		{
			sprintf(str, "ret = 0x%04X", ret);
			CTOS_LCDTPrintXY(1, 8, str);
			goto __Leave;
		}
		
		Offset += Len;
		TotalLen -= Len;
	}
	
	Offset = 0;
	TotalLen = 16 * 1024;
	
	memset(ReadData, 0x00, sizeof(ReadData));
	
	while(TotalLen)
	{
		if(TotalLen > 2048)
		{
			Len = 2048;
		}
		else
		{
			Len = TotalLen;
		}
		ret = CTOS_KMS2UserDataRead(FALSE, Offset, &ReadData[Offset], Len);
		if(ret != d_OK)
		{
			sprintf(str, "ret = 0x%04X", ret);
			CTOS_LCDTPrintXY(1, 8, str);
			goto __Leave;
		}
		
		Offset += Len;
		TotalLen -= Len;
	}
	
	TotalLen = 16 * 1024;
	if(memcmp(ReadData, WriteData, TotalLen))
	{
		CTOS_LCDTPrintXY(1, 3, "Match Not OK");		
	}
	else
	{
		CTOS_LCDTPrintXY(1, 3, "Match OK");
	}

	Offset = 8 * 1024 + 8;
	Len = 1 * 1024;

	for(i = 0; i < sizeof(WriteData); ++i)
	{
		WriteData[i] = (BYTE)i;
	}

	ret = CTOS_KMS2UserDataWrite(FALSE, Offset, WriteData, Len);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	memset(ReadData, 0x00, sizeof(ReadData));

	ret = CTOS_KMS2UserDataRead(FALSE, Offset, ReadData, Len);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	if(memcmp(ReadData, WriteData, Len))
	{
		CTOS_LCDTPrintXY(1, 4, "Match Not OK");
	}
	else
	{
		CTOS_LCDTPrintXY(1, 4, "Match OK");
	}

	//----------------------------------------------------------------------------
	
	for(i = 0; i < sizeof(WriteData); ++i)
	{
		WriteData[i] = (BYTE)i;
	}

	Offset = 0;
	TotalLen = 16 * 1024;
	while(TotalLen)
	{
		if(TotalLen > 2048)
		{
			Len = 2048;
		}
		else
		{
			Len = TotalLen;
		}
		
		ret = CTOS_KMS2UserDataWrite(TRUE, Offset, &WriteData[Offset], Len);
		if(ret != d_OK)
		{
			sprintf(str, "ret = 0x%04X", ret);
			CTOS_LCDTPrintXY(1, 8, str);
			goto __Leave;
		}
		
		Offset += Len;
		TotalLen -= Len;
	}
	
	Offset = 0;
	TotalLen = 16 * 1024;
	
	memset(ReadData, 0x00, sizeof(ReadData));
	
	while(TotalLen)
	{
		if(TotalLen > 2048)
		{
			Len = 2048;
		}
		else
		{
			Len = TotalLen;
		}
		ret = CTOS_KMS2UserDataRead(TRUE, Offset, &ReadData[Offset], Len);
		if(ret != d_OK)
		{
			sprintf(str, "ret = 0x%04X", ret);
			CTOS_LCDTPrintXY(1, 8, str);
			goto __Leave;
		}
		
		Offset += Len;
		TotalLen -= Len;
	}
	
	TotalLen = 16 * 1024;
	if(memcmp(ReadData, WriteData, TotalLen))
	{
		CTOS_LCDTPrintXY(1, 5, "Match Not OK");		
	}
	else
	{
		CTOS_LCDTPrintXY(1, 5, "Match OK");
	}

	Offset = 16 * 1024 + 8;
	Len = 1 * 1024;

	for(i = 0; i < sizeof(WriteData); ++i)
	{
		WriteData[i] = (BYTE)i;
	}

	ret = CTOS_KMS2UserDataWrite(TRUE, Offset, WriteData, Len);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	memset(ReadData, 0x00, sizeof(ReadData));

	ret = CTOS_KMS2UserDataRead(TRUE, Offset, ReadData, Len);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	if(memcmp(ReadData, WriteData, Len))
	{
		CTOS_LCDTPrintXY(1, 6, "Match Not OK");
	}
	else
	{
		CTOS_LCDTPrintXY(1, 6, "Match OK");
	}
	
	CTOS_LCDTPrintXY(1, 7, "UserData Done");
__Leave:
	CTOS_KBDGet(&key);			
}

void GetPIN_With_3DES(void)
{
	CTOS_KMS2PINGET_PARA para;
	USHORT ret;
	BYTE str[17];
	BYTE key;
	BYTE PINBlock[16];
	BYTE *pCipherKey;
	BYTE CipherKeyLength;
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "GetPIN with 3DES");
	
	
	pCipherKey = (BYTE*)Key_3DES_1000_0001;
	CipherKeyLength = 16;
	
	memset(&para, 0x00, sizeof(CTOS_KMS2PINGET_PARA));
	para.Version = 0x01;
	para.PIN_Info.BlockType = KMS2_PINBLOCKTYPE_ANSI_X9_8_ISO_0;
	para.PIN_Info.PINDigitMinLength = 4;
	para.PIN_Info.PINDigitMaxLength = 12;
	para.Protection.CipherKeySet = 0x1000;
	para.Protection.CipherKeyIndex = 0x0001;
	para.Protection.CipherMethod = KMS2_PINCIPHERMETHOD_ECB;
	para.Protection.SK_Length = 0;
	para.AdditionalData.InLength = 16;
	para.AdditionalData.pInData = (BYTE*)TestPAN;
	para.PINOutput.EncryptedBlockLength = 8;
	para.PINOutput.pEncryptedBlock = PINBlock;
	para.Control.Timeout = 10;
	para.Control.AsteriskPositionX = 1;
	para.Control.AsteriskPositionY = 2;
	para.Control.NULLPIN = FALSE;
	para.Control.piTestCancel = NULL;
	ret = CTOS_KMS2PINGet(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
			
	CTOS_LCDTPrintXY(1, 3, "Get PIN OK");
	
	CTOS_LCDTPrintXY(1, 7, "GetPIN Done");
__Leave:
	CTOS_KBDGet(&key);		
}


void GetPIN_With_3DESDUKPT(void)
{
	CTOS_KMS2PINGET_PARA para;
	USHORT ret;
	BYTE str[17];
	BYTE key;
	BYTE PINBlock[16];
	BYTE *pCipherKey;
	BYTE CipherKeyLength;
	BYTE DecipherPINBlock[16];
	BYTE ExpectPINBlock[16];
	BYTE ksn[10];
	BYTE ksn_Len;
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "GetPIN with ");
	CTOS_LCDTPrintXY(1, 2, "     3DES DUKPT");
		
	pCipherKey = (BYTE*)Key_3DESDUKPT_1010_0001;
	CipherKeyLength = 16;
		
	memset(&para, 0x00, sizeof(CTOS_KMS2PINGET_PARA));
	para.Version = 0x01;
	para.PIN_Info.BlockType = KMS2_PINBLOCKTYPE_ANSI_X9_8_ISO_0;
	para.PIN_Info.PINDigitMinLength = 4;
	para.PIN_Info.PINDigitMaxLength = 12;
	para.Protection.CipherKeySet = 0x1010;
	para.Protection.CipherKeyIndex = 0x0001;
	para.Protection.CipherMethod = KMS2_PINCIPHERMETHOD_ECB;
	para.Protection.SK_Length = 0;
	para.AdditionalData.InLength = 16;
	para.AdditionalData.pInData = (BYTE*)TestPAN;
	para.DUKPT_PARA.IsUseCurrentKey = FALSE;
	para.PINOutput.EncryptedBlockLength = 8;
	para.PINOutput.pEncryptedBlock = PINBlock;
	para.Control.Timeout = 10;
	para.Control.AsteriskPositionX = 1;
	para.Control.AsteriskPositionY = 2;
	para.Control.NULLPIN = FALSE;
	para.Control.piTestCancel = NULL;
	ret = CTOS_KMS2PINGet(&para);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	CTOS_LCDTPrintXY(1, 5, "Get PIN OK");
	
	ksn_Len = 10;
	ret = CTOS_KMS2DUKPTGetKSN(para.Protection.CipherKeySet, para.Protection.CipherKeyIndex, ksn, &ksn_Len);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	CTOS_LCDTPrintXY(1, 6, "Get KSN OK");
		
	CTOS_LCDTPrintXY(1, 8, "GetPIN Done");
__Leave:
	CTOS_KBDGet(&key);			
}

void GetPIN(void)
{
	GetPIN_With_3DES();
	GetPIN_With_3DESDUKPT();
}

void KeyCheck(void)
{
	USHORT ret;
	BYTE str[17];
	BYTE key;
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "Key Check");
		
	ret = CTOS_KMS2KeyCheck(0x1000, 0x0001);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	CTOS_LCDTPrintXY(1, 2, "3DES OK");
	
	ret = CTOS_KMS2KeyCheck(0x1010, 0x0001);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	CTOS_LCDTPrintXY(1, 3, "3DES DUKPT OK");
	
	ret = CTOS_KMS2KeyCheck(0x1020, 0x0001);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	CTOS_LCDTPrintXY(1, 4, "AES OK");
	
	ret = CTOS_KMS2KeyCheck(0x1030, 0x0001);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	CTOS_LCDTPrintXY(1, 5, "RSA 1024 OK");
	
	ret = CTOS_KMS2KeyCheck(0x1030, 0x000A);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	CTOS_LCDTPrintXY(1, 6, "RSA 2048 OK");	
	
	ret = CTOS_KMS2KeyCheckAll();
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	CTOS_LCDTPrintXY(1, 7, "Check All OK");	
	
	CTOS_LCDTPrintXY(1, 8, "Key Check Done");
__Leave:
	CTOS_KBDGet(&key);	
}

void KeyDelete(void)
{
	USHORT ret;
	BYTE str[17];
	BYTE key;
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "Key Delete");
			
	ret = CTOS_KMS2KeyDelete(0x1000, 0x0001);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	ret = CTOS_KMS2KeyCheck(0x1000, 0x0001);
	if(ret != d_KMS2_KEY_NOT_EXIST)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	CTOS_LCDTPrintXY(1, 2, "3DES Delete OK");
	
	ret = CTOS_KMS2KeyDelete(0x1010, 0x0001);
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	ret = CTOS_KMS2KeyCheck(0x1010, 0x0001);
	if(ret != d_KMS2_KEY_NOT_EXIST)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	CTOS_LCDTPrintXY(1, 3, "DUKPT Delete OK");
	
	ret = CTOS_KMS2KeyDeleteAll();	
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	CTOS_LCDTPrintXY(1, 7, "Delete All OK");	
	
	CTOS_LCDTPrintXY(1, 8, "Key Delete Done");
__Leave:
	CTOS_KBDGet(&key);
}

void Erase(void)
{
	USHORT ret;
	BYTE str[17];
	BYTE key;
	
	CTOS_LCDTClearDisplay();
            
	CTOS_LCDTPrintXY(1, 1, "Key Erase");
	
	ret = CTOS_KMS2Erase();
	if(ret != d_OK)
	{
		sprintf(str, "ret = 0x%04X", ret);
		CTOS_LCDTPrintXY(1, 8, str);
		goto __Leave;
	}
	
	CTOS_LCDTPrintXY(1, 8, "Key Erase Done");
__Leave:
	CTOS_KBDGet(&key);	
}

void WriteKeyMenu(void)
{
	BYTE key;
	
	while(1)
	{
		CTOS_LCDTClearDisplay();
		CTOS_LCDTPrintXY(1, 1, "Write Key");
		CTOS_LCDTPrintXY(1, 2, "1)Plaintext");
		CTOS_LCDTPrintXY(1, 3, "2)KPK");
		CTOS_LCDTPrintXY(1, 4, "3)Certificate");
		CTOS_KBDGet(&key);
		
		switch(key)
		{
			case '1':
				WriteKeyInPlaintext();
				break;
			case '2':
				WriteKeyInKPK();
				break;
			case '3':
				WriteKeyInCertificate();
				break;
			case d_KBD_CANCEL:
				return;
				break;
		}
		
	}
}

void FunctionMenu(void)
{
	BYTE key;
	
	while(1)
	{
		CTOS_LCDTClearDisplay();
		CTOS_LCDTPrintXY(1, 1, "Function");
		CTOS_LCDTPrintXY(1, 2, "1)KeyCheck");
		CTOS_LCDTPrintXY(1, 3, "2)GetKeyInfo");
		CTOS_LCDTPrintXY(1, 4, "3)GetPIN");
		CTOS_LCDTPrintXY(1, 5, "4)EncryptData");
		CTOS_LCDTPrintXY(1, 6, "5)MAC");		
		CTOS_LCDTPrintXY(1, 7, "6)UserData");
		CTOS_LCDTPrintXY(1, 8, "7)Delete");
		
		CTOS_KBDGet(&key);
		
		switch(key)
		{
			case '1':
				KeyCheck();
				break;
			case '2':
				GetKeyInfo();
				break;
			case '3':
				GetPIN();
				break;
			case '4':
				EncryptData();
				break;
			case '5':
				MAC();
				break;			
			case '6':
				UserData();
				break;			
			case '7':
				KeyDelete();
				break;
			case '8':
				Erase();
				break;
			case d_KBD_CANCEL:
				return;
				break;
		}
		
	}
}

void KMS2_Func(void)
{
	BYTE key;
	
	while(1)
	{
		CTOS_LCDTClearDisplay();
		CTOS_LCDTPrintXY(1, 1, "KMS2 Function");
		CTOS_LCDTPrintXY(1, 2, "1)Write Key");
		CTOS_LCDTPrintXY(1, 3, "2)Function ");
		CTOS_KBDGet(&key);
		
		switch(key)
		{
			case '1':
				WriteKeyMenu();
				break;
			case '2':
				FunctionMenu();
				break;					
			case d_KBD_CANCEL:
				return;
				break;
		}		
	}
}


/** 
** The main entry of the terminal application 
**/
int main(int argc,char *argv[])
{
	BYTE key;
        
	// TODO: Add your program here //
	CTOS_LCDTClearDisplay();
            
    CTOS_KMS2Init();
	
	KMS2_Func();
            
	CTOS_KBDGet(&key);
	
	exit(0);
}
