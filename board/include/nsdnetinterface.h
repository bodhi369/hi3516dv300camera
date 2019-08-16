

#ifndef __NSDNETINTERFACE_H_
#define __NSDNETINTERFACE_H_

#include "nsddefines.h"

#ifdef __cplusplus
extern "C" {
#endif


#if (defined(WIN32) || defined(_WIN32_WCE))
	#ifdef NsdNetSDK_EXPORTS
	#define NSDAPI __declspec(dllexport)
	#else
	#define NSDAPI __declspec(dllimport)
	#endif
#else
	#define WINAPI 
	#define NSDAPI

	typedef unsigned int WPARAM;
	typedef long LPARAM;
	typedef double DATE;
	typedef void *	HANDLE;	
	typedef int BOOL;
#endif

#define MAX_EVENT_CALLBACK_NUM		4
typedef enum _NSD_PRESET_CMD_E
{
	NSDPRESET_SET,
	NSDPRESET_CLEAR,
	NSDPRESET_CALL,
}NSD_PRESET_CMD_E;

typedef enum _NSD_TOUR_CMD_E
{
	NSDTOUR_FILL_PRE,		//��Ԥ�õ����Ѳ������
	NSDTOUR_CLE_PRE,		//��Ԥ�õ��Ѳ��������ɾ��
	NSDTOUR_RUN,			//����Ѳ��
	NSDTOUR_STOP,			//ֹͣѲ��
}NSD_TOUR_CMD_E;

typedef enum _NSD_TRACK_CMD_E
{
	NSDTRACK_REC,			//¼�ƹ켣
	NSDTRACK_SAVE,			//ֹͣ¼�ƹ켣
	NSDTRACK_RUN,			//���й켣
	NSDTRACK_STOP,			//ֹͣ���й켣
}NSD_TRACK_CMD_E;

//3���¼�����
typedef enum _NSD_EVENT_TYPE_E
{
	NSDEVENT_CONNECT_SUCCESS,			//����ģʽ���������ӳɹ�
	NSDEVENT_CONNECT_CLOSE,				//����ģʽ�����ӹر�
	NSDEVENT_LOGON_OPEN,
	NSDEVENT_LOGON_CLOSE,				//��¼���ӹر�
	NSDEVENT_PREVIEW_OPEN,
	NSDEVENT_PREVIEW_CLOSE,				//��Ƶ���ӹر�
	NSDEVENT_TALK_OPEN,
	NSDEVENT_TALK_CLOSE,				//�Խ����ӹر�
	NSDEVENT_REPLAY_OPEN,
	NSDEVENT_REPLAY_CLOSE,				//Զ�̻ط����ӹر�
	NSDEVENT_PICTURE_OPEN,
	NSDEVENT_PICTURE_CLOSE,				//ץͼ���ӹر�
	NSDEVENT_SERIAL_OPEN,
	NSDEVENT_SERIAL_CLOSE,				//͸���������ӹر�
	NSDEVENT_DV_OPEN,
	NSDEVENT_DV_CLOSE,					//�������ӹر�

	NSDEVENT_ALARM,						//�澯��Ϣ
	NSDEVENT_GPS,						//GPS��Ϣ
	NSDEVENT_SEARCH_FILE,				//������¼���ļ���Ϣ
	NSDEVENT_SEARCH_DEVICE,				//�������豸��Ϣ
	NSDEVENT_UPDATE_PROCESS,			//��������
	NSDEVENT_MOTION_STATUS,				//�ƶ����״̬����
	NSDEVENT_REPLAY_END,
	NSDEVENT_DAY_NIGHT_STATUS,			//��ҹ�л�״̬����
	NSDEVENT_LOCAL_MSG,
}NSD_EVENT_TYPE_E;

//////////////////////////////////////////////////
//�¼�֪ͨ�ص�
typedef int (WINAPI *EventNotifyCallback)(WPARAM wParam,LPARAM lParam);
//ʵʱ����Ƶ�������ص�
typedef int (WINAPI *StreamCallback)(HANDLE hOpenChannel,int nChannelNo,int nSubFlow,const char * pStreamData,unsigned long nDataLen,void * lpChannelContext);
//ʵʱ�Խ���Ƶ�������ص�
typedef int (WINAPI *TalkCallback)(HANDLE hTalk,const char * pTalkData,unsigned long nDataLen,void * lpTalkContext);
//¼��طŻص�
typedef int (WINAPI *NetReplayCallback)(HANDLE hReplay,int nType,const char * pStreamData,unsigned long nDataLen,void * lpReplayContext,long nPercent);
//ץ��ͼƬ�ص�
typedef int (WINAPI *CapturePictureCallback)(HANDLE hPicture,int nChannelNo,int nSubFlow,int nPictureFormat,const char * pPictureData,unsigned long nDataLen,void * lpPictureContext);
//�������ݻص�
typedef int (WINAPI *SerialCallback)(HANDLE hSerial,int nSerialNo,const char * pSerialData,unsigned long nDataLen,void * lpSerialContext);

//==========================================================================
//ͨ���ṹ
//==========================================================================

//1������Ƶͨ��
typedef struct _NSD_OPEN_CHANNEL_INFO
{
	unsigned short		nOpenChannelNo;					//��ͨ���ţ�base 0
	unsigned char		nSubFlow;						//������ ��base 1;
	unsigned char		nSuspend;
	unsigned char		nRecvMDInfo;
	unsigned char		nRecvAudio;
	unsigned char		rsvd[2];
	unsigned short		nTransProtocol;					//ͨѶЭ��
	StreamCallback		funcStramCallback;				//����Ƶ���ص�����
	void *				lpChannelContext;				//ͨ��������
}NSD_OPEN_CHANNEL_INFO,* LPNSD_OPEN_CHANNEL_INFO;

//2����ץͼͨ��
typedef struct _NSD_OPEN_PICTURE_INFO
{
	unsigned short		nOpenChannelNo;					//��ͨ���ţ�base 0
	unsigned short		nTransProtocol;					//ͨѶЭ��
	unsigned char		rsvd[4];
	CapturePictureCallback funcCapPictureCallback;		//ץͼ�ص�
	void *				lpPictureContext;				//ץͼ������
}NSD_OPEN_PICTURE_INFO,* LPNSD_OPEN_PICTURE_INFO;

//3����͸������ͨ��
typedef struct _NSD_OPEN_SERIAL_INFO
{
	unsigned short		nOpenSerialNo;					//���ں�
	unsigned short		nTransProtocol;					//ͨѶЭ��
	SerialCallback		funcSerialCallback;				//͸�����ݻص�
	unsigned char		nSuspend;
	unsigned char		rsvd[3];
	void *				lpSerialContext;				//͸������������
}NSD_OPEN_SERIAL_INFO,* LPNSD_OPEN_SERIAL_INFO;

//5���򿪶Խ�ͨ��
typedef struct _NSD_OPEN_TALK_INFO
{
	unsigned short		nTransProtocol;					//ͨѶЭ��
	unsigned char		nSuspend;
	unsigned char		rsvd;
	TalkCallback		funcTalkCallback;				//�Խ����ݻص�
	void *				lpTalkContext;					//�Խ�������
}NSD_OPEN_TALK_INFO,* LPNSD_OPEN_TALK_INFO;

//6����Զ�̻ط�ͨ��
typedef struct _NSD_OPEN_REPLAY_INFO
{
	unsigned short		nTransProtocol;					//ͨѶЭ��
	unsigned short		rsvd;							//����
	NetReplayCallback	funcNetRePlayCallback;			//¼��طŻص�����
	void *				lpReplayContext;				//�ط�������
}NSD_OPEN_REPLAY_INFO,*LPNSD_OPEN_REPLAY_INFO;

//==========================================================================
//�¼��ṹ
//==========================================================================

//1����Ƶͨ���¼�
typedef struct _NSD_EVENT_CHANNEL_INFO
{
	HANDLE				hChannel;						//�¼���Ӧ��ͨ�����
	char				szDeviceID[NAME_LEN_16];		//�豸ID
	unsigned short		nOpenChannelNo;					//ͨ���ţ�base 0
	unsigned short		nSubFlow;						//0:��������1:������
	char				szServerURL[NAME_LEN_64];		//���ӵ���Ƶ������IP
	unsigned short		nServerPort;					//���ӵ���Ƶ�������˿�
	void *				lpChannelContext;				//ͨ��������
}NSD_EVENT_CHANNEL_INFO,*LPNSD_EVENT_CHANNEL_INFO;

//2����¼ͨ���¼�
typedef struct _NSD_EVENT_LOGON_INFO
{
	HANDLE				hLogon;							//��¼���
	char				szDeviceID[NAME_LEN_16];		//�豸ID
	char				szServerURL[NAME_LEN_64];		//���ӵ���Ƶ������IP
	unsigned short		nServerPort;					//���ӵ���Ƶ�������˿�
	void *				lpLogonContext;					//��¼������
}NSD_EVENT_LOGON_INFO,*LPNSD_EVENT_LOGON_INFO;

//3���Խ�ͨ���¼�
typedef struct _NSD_EVENT_TALK_INFO
{
	HANDLE				hTalk;							//�Խ����
	char				szDeviceID[NAME_LEN_16];		//�豸ID
	char				szServerURL[NAME_LEN_64];		//���ӵ���Ƶ������IP
	unsigned short		nServerPort;					//���ӵ���Ƶ�������˿�
	void *				lpTalkContext;					//�Խ�������
}NSD_EVENT_TALK_INFO,*LPNSD_EVENT_TALK_INFO;

//4��ץͼͨ���¼�
typedef struct _NSD_EVENT_PICTURE_INFO
{
	HANDLE				hPicture;						//ץͼ���
	char				szDeviceID[NAME_LEN_16];		//�豸ID
	char				szServerURL[NAME_LEN_64];		//���ӵ���Ƶ������IP
	unsigned short		nServerPort;					//���ӵ���Ƶ�������˿�
	void *				lpPictureContext;				//ץͼ������
}NSD_EVENT_PICTURE_INFO,*LPNSD_EVENT_PICTURE_INFO;

//5��͸������ͨ���¼�
typedef struct _NSD_EVENT_SERIAL_INFO
{
	HANDLE				hSerial;						//͸�����ھ��
	char				szDeviceID[NAME_LEN_16];		//�豸ID
	unsigned short		nOpenSerialNo;					//���ںţ�base 0
	char				szServerURL[NAME_LEN_64];		//���ӵ���Ƶ������IP
	unsigned short		nServerPort;					//���ӵ���Ƶ�������˿�
	void *				lpSerialContext;				//����������	
}NSD_EVENT_SERIAL_INFO,*LPNSD_EVENT_SERIAL_INFO;

//6��Զ�̻ط�ͨ���¼�
typedef struct _NSD_EVENT_REPLAY_INFO
{
	HANDLE				hReplay;						//Զ�̻طž��
	char				szDeviceID[NAME_LEN_16];		//�豸ID
	char				szServerURL[NAME_LEN_64];		//���ӵ���Ƶ������IP
	unsigned short		nServerPort;					//���ӵ���Ƶ�������˿�
	void *				lpReplayContext;				//Զ�̻ط�������
}NSD_EVENT_REPLAY_INFO,*LPNSD_EVENT_REPLAY_INFO;

//7��¼�������¼�
typedef struct _NSD_EVENT_RECFILE_INFO
{
	HANDLE				hReplay;						//Զ�̻طž��
	char				szDeviceID[NAME_LEN_16];		//�豸ID
	unsigned long		nRecType;						//¼������
	unsigned short		nOpenChannelNo;					//ͨ����
	unsigned short		nSubFlow; 						//0:��������1:������
	NSD_TIME_S			tmStart;						//¼��Ŀ�ʼʱ��
	NSD_TIME_S			tmEnd;							//¼��Ľ���ʱ��
	unsigned long		nRecSize;						//¼�����ֽ���		
	char                szFileName[260];				//yyyymmddhhmmss-yyymmddhhmmss
	int					nMark;							//0:δ������1:���һ��	
	char				szServerURL[NAME_LEN_64];		//���ӵ���Ƶ������IP
	unsigned short		nServerPort;					//���ӵ���Ƶ�������˿�
	void *				lpReplayContext;				//Զ�̻ط�������
}NSD_EVENT_RECFILE_INFO,*LPNSD_EVENT_RECFILE_INFO;

//8���豸�����¼�
typedef struct _NSD_EVENT_DEVICE_INFO
{
	char				szDeviceID[NAME_LEN_16];		//�豸ID
	char				szMachineType[NAME_LEN_48];		//����
	unsigned long		nSensorType;					//Sensor����
	unsigned long		nFaceType;						//�������
	char				szServerIP[16];					//��������IP��ַ
	char				szGateWay[16];					//����
	char				szSubMask[16];					//����
	unsigned char		nMacAddr[6];					//MAC��ַ
	unsigned char		nChannelNum;					//·��
	unsigned char		rsvd;
	unsigned short		nListenPort;
	unsigned short		nHttpPort;
	char				szDeviceName[NAME_LEN_32];		//�豸����
	void *				lpSearchDeviceContext;			//�����豸������
	short				bFinish;						//��������
	unsigned short		nUpdatePort;					//
	char				szDeviceIP[16];					//�豸��������IP��ַ
	char				szVersion[NAME_LEN_48];			//�汾

	char				szDNSIP1[16];					//DNS��IP1
	char				szDNSIP2[16];					//DNS��IP2
	unsigned char		nDHCP1;							//����������DHCP����
	unsigned char		nDHCP2;							//DNS��DHCP����
	unsigned short		nOldListenPort;
}NSD_EVENT_DEVICE_INFO,*LPNSD_EVENT_DEVICE_INFO;

//9���澯�¼�
typedef struct _NSD_EVENT_ALARM_INFO
{
	HANDLE				hLogon;							//��¼���
	char				szDeviceID[NAME_LEN_16];		//�豸ID
	NSD_ALARM_OUTPUT_STATUS_S	alarmSatus;				//�澯���״̬
	char				szServerURL[NAME_LEN_64];		//���ӵ���Ƶ������IP
	unsigned short		nServerPort;					//���ӵ���Ƶ�������˿�
	void *				lpLogonContext;					//��¼������	
}NSD_EVENT_ALARM_INFO,*LPNSD_EVENT_ALARM_INFO;

//10������ģʽ�¼�
typedef struct _NSD_EVENT_CENTER_INFO
{
	char				szDeviceID[NAME_LEN_16];		//�豸ID
	char				szMachineType[NAME_LEN_48];		//����
	char				szServerIP[16];					//��Ƶ������IP��ַ
	unsigned char		nMacAddr[6];					//MAC��ַ
	unsigned char		nChannelNum;					//·��
	unsigned char		nPtzNum;
	unsigned short		nServerPort;					//��Ƶ�������˿�
	unsigned char		nDiNum;
	unsigned char		nDoNum;
	char				szDeviceName[NAME_LEN_32];			//�豸����
}NSD_EVENT_CENTER_INFO,*LPNSD_EVENT_CENTER_INFO;

typedef struct _NSD_EVENT_MOTION_INFO
{
	HANDLE				hLogon;							//��¼���
	char				szDeviceID[NAME_LEN_16];		//�豸ID
	NSD_MOTION_STATUS_S	motionStatus;					//�ƶ����״̬
	char *				lpData;							//�ƶ��������(�ڲ����䣬��Ҫ�ͷ�)
	unsigned long		nDataLen;						//�ƶ�������ݳ���
	char				szServerURL[NAME_LEN_64];		//���ӵ���Ƶ������IP
	unsigned short		nServerPort;					//���ӵ���Ƶ�������˿�
	void *				lpLogonContext;					//��¼������	
}NSD_EVENT_MOTION_INFO,*LPNSD_EVENT_MOTION_INFO;

typedef struct _NSD_EVENT_UPDATE_INFO
{
	HANDLE				hLogon;							//��¼���
	char				szDeviceID[NAME_LEN_16];		//�豸ID
	void *				lpUpdateContext;				//����������
	int					nPercent;						//��װ�ٷֱ�(nStatus=2)
	unsigned long		nTotleBytes;					//�������ֽ�(nStatus=1)
	unsigned long		nSendBytes;						//�ѷ����ֽ�(nStatus=1)
	int					nReboot;						//�Ƿ������(nStatus=0)
	int					nStatus;						//0�����ɹ���1���ڷ���(nSendBytes)��2���ڰ�װ(nPercent)��-1����ʧ��, ����ֵ���󷵻���
}NSD_EVENT_UPDATE_INFO,*LPNSD_EVENT_UPDATE_INFO;


typedef struct _NSD_EVENT_DAYNIGHT_STATUS
{
	HANDLE				hLogon;							//��¼���
	char				szDeviceID[NAME_LEN_16];		//�豸ID
	char				szServerURL[NAME_LEN_64];		//���ӵ���Ƶ������IP
	unsigned short		nServerPort;					//���ӵ���Ƶ�������˿�
	unsigned int		nChannel;
	int					nStatus;						//NSD_DAYNIGHT_STATUS_E	
	void *				lpLogonContext;					//��¼������	
}NSD_EVENT_DAYNIGHT_STATUS,*LPNSD_EVENT_DAYNIGHT_STATUS;

typedef struct _NSD_EVENT_LOCAL_MSG
{
	HANDLE				hLogon;							//��¼���
	char				szDeviceID[NAME_LEN_16];		//�豸ID
	char				szServerURL[NAME_LEN_64];		//���ӵ���Ƶ������IP
	unsigned short		nServerPort;					//���ӵ���Ƶ�������˿�
	
	unsigned int		nMsgType;
	unsigned char		rsvd[36];
	void *				pMsg;
	unsigned int		nMsgLen;

	void *				lpLogonContext;					//��¼������	
}NSD_EVENT_LOCAL_MSG,*LPNSD_EVENT_LOCAL_MSG;

//==================================================
//���ûص�����
//==================================================
#if (defined(WIN32) || defined(_WIN32_WCE))
NSDAPI int WINAPI NSDNET_SetEventMsg(HWND hNotifyWnd,unsigned long nCommandID);
#endif
NSDAPI int WINAPI NSDNET_SetEventCallback(EventNotifyCallback lpCallback);
NSDAPI int WINAPI NSDNET_SetEventCallbackEx(int nIndex,EventNotifyCallback lpCallback);

//==================================================
//��¼�����ƺ���
//==================================================
NSDAPI int WINAPI NSDNET_Login(const char * lpServerIP,unsigned short nServerPort,const char * lpUserName,const char * lpPassword,unsigned long nRsvd,void * lpLogonContext,HANDLE * lpLogin);
NSDAPI int WINAPI NSDNET_LoginEx(const char * lpServerIP,unsigned short nServerPort,const char * lpUserName,const char * lpPassword,unsigned long nRsvd,void * lpLogonContext,HANDLE * lpLogin);
#if !defined(_WIN32)
int WINAPI NSDNET_LoginLocal(const char * lpSunPath,unsigned long nRsvd,void * lpLogonContext,HANDLE * lpLogin);
int WINAPI NSDNET_SendLocalMsg(HANDLE hLogin, NSD_LOCAL_MSG_HEAD_S msgHead,const char * lpMsg,unsigned int nMsgLen);
#endif
NSDAPI int WINAPI NSDNET_Logout(HANDLE hLogin);
NSDAPI int WINAPI NSDNET_GetServerInfo(HANDLE hLogin,NSD_SYS_INFO_S * lpSysInfo);
NSDAPI int WINAPI NSDNET_GetDeviceInfo(HANDLE hLogin,NSD_DEVICE_S * lpDevice);
NSDAPI int WINAPI NSDNET_GetServerConfig(HANDLE hLogin,NSD_CONFIG_TYPE_E nConfigType,char * lpConfigBuf,unsigned long * lpBufferSize,unsigned long nAppend);
NSDAPI int WINAPI NSDNET_SetServerConfig(HANDLE hLogin,NSD_CONFIG_TYPE_E nConfigType,char * lpConfigBuf,unsigned long nBufferSize,unsigned long nAppend);
NSDAPI int WINAPI NSDNET_GetServerMultiConfig(HANDLE hLogin,const char * lpMultiCfgHead,unsigned long nHeadLen,char * lpConfigBuf,unsigned long * lpBufferSize);
NSDAPI int WINAPI NSDNET_SetServerMultiConfig(HANDLE hLogin,char * lpMultiConfigBuf,unsigned long nBufferSize);
NSDAPI int WINAPI NSDNET_PTZControl(HANDLE hLogin,NSD_PTZ_CTRL_S * lpPtzCtrl);
NSDAPI int WINAPI NSDNET_Update(HANDLE hLogin,const char * lpUpdateFileName,void * lpUpdateContext);
NSDAPI int WINAPI NSDNET_IngoreUpdateReboot(HANDLE hLogin);
NSDAPI int WINAPI NSDNET_ToDefaultParam(HANDLE hLogin);
NSDAPI int WINAPI NSDNET_ToDefaultParamEx(HANDLE hLogin,unsigned long nParam, unsigned long nReboot);
NSDAPI int WINAPI NSDNET_Reboot(HANDLE hLogin);
NSDAPI int WINAPI NSDNET_ForceKeyFrame(HANDLE hLogin,unsigned short nChannelNo,unsigned short nSubFlow);
NSDAPI int WINAPI NSDNET_GetServerCapability(HANDLE hLogin,const char * lpCapabiltyHead,unsigned long nHeadLen,char * lpCapabiltyBuf,unsigned long * lpBufferSize);
NSDAPI int WINAPI NSDNET_PTZPreset(HANDLE hLogin,NSD_PRESET_CMD_E nPresetCmd,NSD_PRESET_CFG_S * lpPtzCtrl);
NSDAPI int WINAPI NSDNET_QueryPreset(HANDLE hLogin,char * lpRecvBuf,unsigned long * lpBufferSize,unsigned long nAppend);
NSDAPI int WINAPI NSDNET_PTZTour(HANDLE hLogin,NSD_TOUR_CMD_E nTourCmd,unsigned short nChannelNo,unsigned short nTourNo,unsigned short nPointIndex,LPNSD_TOUR_POINT_S lpTourPoint);
NSDAPI int WINAPI NSDNET_QueryTour(HANDLE hLogin,char * lpRecvBuf,unsigned long * lpBufferSize,unsigned short nChannelNo,unsigned short nTourNo);
NSDAPI int WINAPI NSDNET_PTZTrack(HANDLE hLogin,NSD_TRACK_CMD_E nTrackCmd,unsigned short nChannelNo,unsigned short nTrackNo);
NSDAPI int WINAPI NSDNET_Ball3DCtrl(HANDLE hLogin,NSD_BALL_3D_S * lpBall,unsigned long nRsvd);
NSDAPI void WINAPI NSDNET_RefreshReconn(HANDLE hLogin);
NSDAPI int WINAPI NSDNET_ControlLogin(HANDLE hLogin,BOOL bRecvAlarm);
NSDAPI int WINAPI NSDNET_ManufactureTest(HANDLE hLogin,unsigned long nTestType,unsigned long nChn,unsigned long nParam1,unsigned long nParam2);
NSDAPI int WINAPI NSDNET_SearchLog(HANDLE hLogin, unsigned long nLogType, NSD_TIME_S * lpTmStart, NSD_TIME_S * lpTmEnd, char** lpBuf, unsigned long * lpBufSize);
NSDAPI int WINAPI NSDNET_VerifyParam(HANDLE hLogin,NSD_CONFIG_TYPE_E nConfigType,char * lpParamBuf,unsigned long nBufferSize, unsigned long nAppend);
NSDAPI int WINAPI NSDNET_IOCtrl(HANDLE hLogin,unsigned long nIOType, unsigned long nChn, unsigned long nValue, unsigned long nAppend);

NSDAPI int WINAPI NSDNET_PTZGetPosition(HANDLE hLogin, NSD_PTZ_POSITION_S* lpPtzPosition);
NSDAPI int WINAPI NSDNET_PTZSetPosition(HANDLE hLogin, NSD_PTZ_POSITION_S* lpPtzPosition);
NSDAPI int WINAPI NSDNET_GetCalibration(HANDLE hLogin, char** lpBuf, unsigned long * lpBufSize);

NSDAPI int WINAPI NSDNET_FormatSDCard(HANDLE hLogin, unsigned long nChn);
//Size Unit: MB
NSDAPI int WINAPI NSDNET_GetSDCardInfo(HANDLE hLogin, unsigned long nChn, unsigned long * lpTotalsize, unsigned long * lpFreesize);

NSDAPI int WINAPI NSDNET_GetVideoMediaInfo(HANDLE hLogin, short nChannelNo, short nSubFlow, char * lpMediaInfoBuf, unsigned long* lpBufferSize, unsigned long nAppend);

NSDAPI int WINAPI NSDNET_UpdateMemory(HANDLE hLogin, const char * lpUpdateBuf, unsigned long nBufferSize, void * lpUpdateContext);
NSDAPI int WINAPI NSDNET_UploadFile(HANDLE hLogin, const char* lpFile, const char* lpDst, unsigned long nAppend);
//==================================================
//Ԥ������
//==================================================
NSDAPI int WINAPI NSDNET_StartPreview(HANDLE hLogin,NSD_OPEN_CHANNEL_INFO * lpChannelInfo,HANDLE * lpPreview);
NSDAPI int WINAPI NSDNET_StartPreviewEx(HANDLE hLogin,NSD_OPEN_CHANNEL_INFO * lpChannelInfo,HANDLE * lpPreview);
NSDAPI int WINAPI NSDNET_StopPreview(HANDLE hPreview);
NSDAPI int WINAPI NSDNET_ControlPreview(HANDLE hPreview,BOOL bSuspend,BOOL bRecvMDInfo,BOOL bRecvAudio);

//==================================================
//�Խ�����
//==================================================
NSDAPI int WINAPI NSDNET_StartTalk(HANDLE hLogin,NSD_OPEN_TALK_INFO * lpTalkInfo,HANDLE * lpTalk);
NSDAPI int WINAPI NSDNET_StartTalkEx(HANDLE hLogin,NSD_OPEN_TALK_INFO * lpTalkInfo,HANDLE * lpTalk);
NSDAPI int WINAPI NSDNET_StopTalk(HANDLE hTalk);
NSDAPI int WINAPI NSDNET_SendTalkData(HANDLE hTalk,const char * lpTalkData,unsigned long nDataLen);
NSDAPI int WINAPI NSDNET_ControlTalk(HANDLE hTalk,BOOL bSuspend);

//==================================================
//����͸������
//==================================================
NSDAPI int WINAPI NSDNET_StartSerial(HANDLE hLogin,NSD_OPEN_SERIAL_INFO * lpSerialInfo,HANDLE * lpSerial);
NSDAPI int WINAPI NSDNET_StartSerialEx(HANDLE hLogin,NSD_OPEN_SERIAL_INFO * lpSerialInfo,HANDLE * lpSerial);
NSDAPI int WINAPI NSDNET_StopSerial(HANDLE hSerial);
NSDAPI int WINAPI NSDNET_ControlSerial(HANDLE hSerial,BOOL bSuspend);
NSDAPI int WINAPI NSDNET_SendSerialData(HANDLE hSerial,const char * lpSerialData,unsigned long nDataLen);

//==================================================
//ץͼ����
//==================================================
NSDAPI int WINAPI NSDNET_StartPicture(HANDLE hLogin,NSD_OPEN_PICTURE_INFO * lpPictureInfo,HANDLE * lpPicture);
NSDAPI int WINAPI NSDNET_StartPictureEx(HANDLE hLogin,NSD_OPEN_PICTURE_INFO * lpPictureInfo,HANDLE * lpPicture);
NSDAPI int WINAPI NSDNET_StopPicture(HANDLE hPicture);
NSDAPI int WINAPI NSDNET_CapturePicture(HANDLE hPicture,short nChannelNo,short nSubFlow);
NSDAPI int WINAPI NSDNET_ControlPicture(HANDLE hPicture,BOOL bSuspend);

//==================================================
//�����豸����
//==================================================
NSDAPI int WINAPI NSDNET_SearchAllDevice(unsigned long nTimeOut,void * lpSearchDeviceContext);
NSDAPI int WINAPI NSDNET_SearchAllDeviceEx(const char *szBindIP,unsigned long nTimeOut,void * lpSearchDeviceContext);
NSDAPI int WINAPI NSDNET_ConfigDevice(const char * lpUserName,const char * lpPassword,NSD_EVENT_DEVICE_INFO * lpDeviceInfo);
NSDAPI int WINAPI NSDNET_ConfigDeviceEx(const char * szBindIP,const char * lpUserName,const char * lpPassword,NSD_EVENT_DEVICE_INFO * lpDeviceInfo);

//==================================================
NSDAPI int WINAPI NSDNET_OpenReplay(HANDLE hLogin,NSD_OPEN_REPLAY_INFO * lpReplayInfo,HANDLE * lpReplay);
NSDAPI int WINAPI NSDNET_SearchRecordFile(HANDLE hReplay,int nChannelNo,int nSubFlow,NSD_TIME_S * lpTmStart,NSD_TIME_S * lpTmEnd,int nRecType);
NSDAPI int WINAPI NSDNET_PlayFile(HANDLE hReplay,int nChannelNo,int nSubFlow,NSD_TIME_S * lpTmStart,NSD_TIME_S * lpTmEnd,int nRecType);
NSDAPI int WINAPI NSDNET_SpeedFile(HANDLE hReplay,int nSpeed);
NSDAPI int WINAPI NSDNET_SeekFile(HANDLE hReplay,NSD_TIME_S * lpTmSeek,BOOL bToKeyFrame); 
NSDAPI int WINAPI NSDNET_StepFile(HANDLE hReplay,BOOL bToKeyFrame,BOOL bBack);
NSDAPI int WINAPI NSDNET_PauseFile(HANDLE hReplay,BOOL bPause);
NSDAPI int WINAPI NSDNET_StopFile(HANDLE hReplay);
NSDAPI int WINAPI NSDNET_CloseReplay(HANDLE hReplay);

NSDAPI void WINAPI NSDNET_EnableReconnect(int bEnable,unsigned short nIntervalSec);
NSDAPI void WINAPI NSDNET_SetRunParam(unsigned long nConnectTimeMillSec,unsigned long nOperateTimeMillSec,unsigned long nRsvd);
NSDAPI void WINAPI NSDNET_SetRunParamEx(long nParamType,unsigned long nValue);

NSDAPI void WINAPI NSDNET_FreeBuffer(char* lpBuffer);
NSDAPI void WINAPI NSDNET_FreeAllLogin();
#ifdef __cplusplus
}
#endif
#endif

