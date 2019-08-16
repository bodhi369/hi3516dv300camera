
#include "customer.h"

/////////////////////////////////////////////////////
//
CCustomerLib::CCustomerLib()
{
}

CCustomerLib::~CCustomerLib()
{	

}

int CCustomerLib::InitLib(M_INTERFACE * lpInterface)
{
	if(lpInterface==NULL)
		return -1;

    //����ִ�и���䣬 ֮��CCustomerLib����ʹ���м�ӿ�
	_Copy(lpInterface);
	
    printf("Customer Platform: CCustomerLib::InitLib\n");
	return 0;
}

void CCustomerLib::UnInitLib()
{
    printf("Customer Platform: CCustomerLib::UnInitLib\n");
}

CCustomerLib & CCustomerLib::GetInstance()
{
	static CCustomerLib s_obj;
	return s_obj;
}

/////////////////////////////////
//
extern "C"
{
int PLATFORM_GetVersion()
{
    //����汾��nsd�汾��ͬ�� �򲻻���ظö�̬��
	return CORE_VERSION;
}

int PLATFORM_GetType()
{
    //���뷵�ظ�ֵ
	return PTTYPE_CUSTOMER;
}

int PLATFORM_InitLib(M_INTERFACE *lpInterface)
{
    //��ʼ���ÿ⣬ nsd��������ʱ�����øýӿڣ� lpInterfaceΪ�м�ӿڲ�ָ��
    if(NULL==lpInterface)
		return -1;

	return CCustomerLib::GetInstance().InitLib(lpInterface);
}

int PLATFORM_ChangeParam(NSD_CONFIG_TYPE_E nParamType, void * lpParam,unsigned long nCh,unsigned long nRsvd)
{
    //�����仯ʱ����øýӿ�
	if(nParamType==NSDCFG_PLATFORM && nRsvd==PTTYPE_CUSTOMER)
    {
        printf("Customer Platform: PLATFORM_ChangeParam\n");
    }
	return 0;
}

void PLATFORM_DispatchAlarm(NSD_ALARM_OUTPUT_STATUS_S & aos)
{
    //�б�������������ʱ����øýӿ�
}

int PLATFORM_UnInitLib()
{
    //nsd�˳�ʱ����øýӿ�
	return 0;
}

int PLATFORM_OnHttpData(const char * szBuf,char * szOutBuf,int nOutBufSize)
{
    //������øýӿڣ� ���Ըýӿ�
	return 0;
}

int	PLATFORM_OnSDCardStatusChange(unsigned int nStatus)
{
    //SD����ʼ��ʽ���� �͸�ʽ�����ʱ����øýӿ�
	return 0;
}

int PLATFORM_OnNetworkReady(int nNetworkType)
{
    //��������仯����Ҫ��������ʱ����õ��ýӿ�
	return 0;
}

}