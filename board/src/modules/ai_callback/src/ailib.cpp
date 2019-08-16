
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include "ailib.h"
#include "privydef.h"

static unsigned long long GetMicroSecond()
{
	struct timeval tv;
	gettimeofday(&tv, 0);
	return (tv.tv_sec*1000+tv.tv_usec/1000);
}

int AI_YUVDATA_CALLBACK(unsigned short p_ch, AI_VIDEO_FRAME_S *p_yuv)
{
	//����ú���û�е��õ��� ��鿴�豸/mnt/mtd/code/fixed/sys.def ���� externtype��ֵ��ҪΪ0x20000(���AI)����0x10000(Э������AI)
	//�ú�����������̫�ã� ����ᵼ�½�֡�� ����㷨���Ĺ����� ����������һ�����棬 ������һ���߳�ȥ����YUV����
	printf("width=%d, height=%d, pts=%ld\n", p_yuv->nWidth, p_yuv->nHeight, p_yuv->nPts);

	AI_VIDEO_FRAME_S afterScale;
	afterScale.nWidth = 1530;
	afterScale.nHeight= 1530;

	unsigned long long bt = GetMicroSecond();
	int nRet = CAiLib::GetInstance().IF_Scale(p_yuv, &afterScale);//Scale�Ŀ���Ҫ4����
	unsigned long long et = GetMicroSecond();
	if (nRet == 0)
	{
		printf("after scale width is %d, height is %d, waste time is %lld \n", afterScale.nWidth, afterScale.nHeight, et-bt);
	}
	else
	{
		printf("scale failed, ret is %d \n", nRet);
	}

	static int i = 1;
	if (i == 10)
	{
		//�ѵ�10֡�洢����
		FILE *fp = fopen("/mnt/nfs/test.yuv","wb+");
		if (fp)
		{
			fwrite(afterScale.pYUV[0], 1, afterScale.nWidth*afterScale.nHeight*3/2, fp);
			fclose(fp);
		}
	}
	i++;
	return 0;
}

CAiLib::CAiLib()
{

}

CAiLib::~CAiLib()
{

}

CAiLib & CAiLib::GetInstance()
{
	static CAiLib s_ailib;
	return s_ailib;
}

int	CAiLib::InitLib(M_INTERFACE * lpInterface)
{
	if(lpInterface==NULL)
		return NSDERR_FAIL;

	//this is necenssary
	_Copy(lpInterface);
	
	m_handle = IF_AddYuvStreamCallback(0, AI_YUVDATA_CALLBACK);
	
	return NSDERR_SUCCESS;
}

void CAiLib::UnInitLib()
{
	IF_RemoveYuvStreamCallback(0, m_handle);
}

//////////////////////////////////////////////////////////
//
extern "C"
{
int AI_GetCoreVersion()
{
    return CORE_VERSION;
}

int	AI_InitLib(M_INTERFACE * lpInterface)
{
	return CAiLib::GetInstance().InitLib(lpInterface); 
}

int	AI_UnInitLib()
{
	CAiLib::GetInstance().UnInitLib();
}

long AI_AddAnalyseCallback(unsigned short nCh,ai_analyse_callback lpCallback)
{
	return 0;
}

int	AI_RemoveAnalyseCallback(unsigned short nCh,long hHandle)
{
	return NSDERR_SUCCESS; 
}

long AI_GetCapability()
{
	//eg.if you support face detect,return NSD_AI_FACE 
	return NSD_AI_NULL; 
}

int	AI_ChangeParam(unsigned short nCh,NSD_CONFIG_TYPE_E nParamType,void * lpParam)
{
	return NSDERR_SUCCESS;
}

long AI_GetCompany()
{
	return NSD_COMPANY_UNKNOWN;
}

void AI_Reset()
{
}

int	AI_OnSDCardStatusChange(unsigned int nStatus)
{
	return 0;
}
}