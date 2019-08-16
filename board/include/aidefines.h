#ifndef __AI_DEFINES_H_
#define __AI_DEFINES_H_
#include "nsddefines.h"

#define MAX_POLYGON_NUMBER				8
#define MAX_POLYGON_POINT_NUMBER		8
#define MAX_TRIPWIRE_LINE_NUMBER		8
#define MAX_FACE_ROI_AREA_NUMBER		8
#define MAX_FACE_FILTER_AREA_NUMBER		8

typedef enum _NSD_FACE_SNAP_TYPE_E
{
	NSDFACE_MODE_ENTRY,
	NSDFACE_MODE_LEAVE,
	NSDFACE_MODE_OPTIMAL,
	NSDFACE_MODE_NUMBER,
}NSD_FACE_SNAP_TYPE_E;

typedef enum _NSD_FACE_SCENE_TYPE_E
{
	NSDFACE_SCENE_NORMAL,
	NSDFACE_SCENE_HALL,
	NSDFACE_SCENE_HIGHLIGHT,
}NSD_FACE_SCENE_TYPE_E;

typedef enum _NSD_AUTOTRACK_TYPE_E
{
    NSDAUTO_TRACK_WORKMODE_MANUAL,
    NSDAUTO_TRACK_WORKMODE_AUTO,
    NSDAUTO_TRACK_WORKMODE_SEMIAUTO,
    NSDAUTO_TRACK_WORKMODE_CALIBRATION,
}NSD_AUTOTRACK_TYPE_E;

//polygon
typedef struct _NSD_POLYGON_S
{
	NSD_POINT_S			 point[MAX_POLYGON_POINT_NUMBER];  //The polygon area, -1 represents the illegal point. The value is as wide as a percentage.
}PACKED NSD_POLYGON_S, *LPNSD_POLYGON_S;

//tripwire line
typedef struct _NSD_TRIPWIRE_LINE_S
{
	unsigned char		 u8DoubleDirection;				//0: one-way detection; 1: bi-directional detection
	unsigned char		 rsvd[3];	
	unsigned int		 u32ForbiddenDirection;			//In the case of one-way detection, the detection direction needs to be set.
	NSD_POINT_S			 startPoint;				    //The starting point of a line. The value is as wide as a percentage.
	NSD_POINT_S			 endPoint;						//The end point of a line. The value is as wide as a percentage.
}PACKED NSD_TRIPWIRE_LINE_S, *LPNSD_TRIPWIRE_LINE_S;

//perimeter
typedef struct _NSD_AI_PERIMETER_S
{
	unsigned char		 u8Open;						//1:Enable
	unsigned char		 u8DrawLineFlag;				//0: non - line; 1: line
	unsigned char		 u8Sensitivity;					//Sensitivity(0~100)
	unsigned char		 rsvd2[61];	
	NSD_SEGMENT_S		 segment[MAX_SEGMENT_NUM];		//Detection time period
	unsigned int		 u32ActionId[8];				//Action ID, -1 invalid
	NSD_POLYGON_S		 polygon[MAX_POLYGON_NUMBER];	//polygon
}PACKED NSD_AI_PERIMETER_S,*LPNSD_AI_PERIMETER_S;

//tripwire detection
typedef struct _NSD_AI_TRIPWIRE_S
{
	unsigned char		 u8Open;						//1:Enable
	unsigned char		 u8DrawLineFlag;				//0: non - line; 1: line
	unsigned char		 u8Sensitivity;					//Sensitivity(0~100)
	unsigned char		 rsvd2[61];
	NSD_SEGMENT_S		 segment[MAX_SEGMENT_NUM];		//Detection time period
	unsigned int		 u32ActionId[8];				//Action ID, -1 invalid
	NSD_TRIPWIRE_LINE_S	 line[MAX_TRIPWIRE_LINE_NUMBER];//tripwire line
}PACKED NSD_AI_TRIPWIRE_S,*LPNSD_AI_TRIPWIRE_S;

typedef struct _NSD_AI_S
{
	unsigned short		u16AiImageWidth;
	unsigned short		u16AiImageHeight;
	unsigned char		u8PixelFormat;
	unsigned char		u8FrameAllocType;				//0: ��CPU   1: ��CPU
    unsigned char       u8CacheNumber;                  //�������� 2 - 8
    unsigned char       u8CacheNumberForVout;           //�������� 2 - 8
	unsigned char		rsvd[124];
}PACKED NSD_AI_S,*LPNSD_AI_S;

//����ʶ��
typedef struct _NSD_AI_FACE_S
{
	unsigned char		 u8Open;								//���ñ�ʶ
	unsigned char		 u8DrawLineFlag;						//�Ƿ��� 0:������  1:����
	unsigned char		 u8Sensitivity;							//������(0~100,�����ȵ���)
	unsigned char		 u8CaptureFaceFlag;						//�Ƿ�ץȡ���� 0:��ץȡ���� 1:ץȡ���� 2:��ԭͼ 3:����+ԭͼ 
	unsigned short		 u16MinFacePixel;						//��С��������
	unsigned char		 u8Blur;								//ģ��ֵ��С�ڸ�ֵ��ץ��
	unsigned char		 u8Front;								//����ֵ��С�ڸ�ֵ��ץ��
	unsigned char		 u8SnapMode;							//ץ��ģʽ NSD_FACE_SNAP_TYPE_E
	unsigned char		 u8SnapNumber;							//ץ�������� ��ģʽΪNSDFACE_MODE_NUMBERʱ��Ч
	unsigned char		 u8MaxFaceNumber;						//���������
	unsigned char		 u8LeaveInterval;						//�뿪�����������ֵ���뿪����λ100ms	//u8SceneMode;	//����ģʽ
	unsigned short		 u16MaxFacePixel;						//�����������
	unsigned char		 u8FaceAreaCoefficient;					//����������չϵ��
	unsigned char		 u8PictureEncodeQuality;				//ץͼ��������
	unsigned char		 rsvd2[48];	
	NSD_SEGMENT_S		 segment[MAX_SEGMENT_NUM];				//ʱ���
	unsigned int		 u32ActionId[8];						//����id,-1��Ч
	NSD_AREA_S			 roiArea[MAX_FACE_ROI_AREA_NUMBER];		//�����ļ������
	NSD_AREA_S			 filterArea[MAX_FACE_FILTER_AREA_NUMBER];	//���������������
	char				 algVersion[NAME_LEN_64];
	char				 swVersion[NAME_LEN_64];
	unsigned char		 rsvd3[64];	
}PACKED NSD_AI_FACE_S,*LPNSD_AI_FACE_S;

typedef struct _NSD_AI_PLATE_NUMBER_S
{
	unsigned char		u8Open;							//�������Ʒ���
	unsigned char		rsvd[127];
}PACKED NSD_AI_PLATE_NUMBER_S,*LPNSD_AI_PLATE_NUMBER_S;

typedef struct _NSD_AI_OBJECT_S
{
	unsigned char		u8Open;							//����Ŀ�����
	unsigned char		rsvd[127];
}PACKED NSD_AI_OBJECT_S,*LPNSD_AI_OBJECT_S;

typedef struct _NSD_AI_OCCLUSION_S
{
	unsigned char		u8Open;							//�����ڵ����
	unsigned char		u8Sensitivity;					//������
	unsigned char		rsvd[62];
	NSD_SEGMENT_S		segment[MAX_SEGMENT_NUM];		//Detection time period
	unsigned int		u32ActionId[8];					//Action ID, -1 invalid
}PACKED NSD_AI_OCCLUSION_S,*LPNSD_AI_OCCLUSION_S;

typedef struct _NSD_AI_FIRE_DETECT_S
{
	unsigned char		u8Open;							//�����̻���
	unsigned char		u8Sensitivity;					//������
	unsigned char		u8LensType;						//��ͷ����
	unsigned char		rsvd[61];
	NSD_SEGMENT_S		segment[MAX_SEGMENT_NUM];		//Detection time period
	unsigned int		u32ActionId[8];					//Action ID, -1 invalid
}PACKED NSD_AI_FIRE_DETECT_S,*LPNSD_AI_FIRE_DETECT_S;

typedef struct _NSD_AI_VIDEO_LOST_S
{
	unsigned char		u8Open;							//������Ƶ��ʧ
	unsigned char		u8Sensitivity;					//������
	unsigned char		rsvd[62];
	NSD_SEGMENT_S		segment[MAX_SEGMENT_NUM];		//Detection time period
	unsigned int		u32ActionId[8];					//Action ID, -1 invalid
}PACKED NSD_AI_VIDEO_LOST_S,*LPNSD_AI_VIDEO_LOST_S;

typedef struct _NSD_AI_AUTO_TRACK_S
{
    unsigned char    u8SettingMask;                     //0x1: ����NSD_AI_AUTO_TRACK_S  0x2:���±궨���� 0x3:ȫ������
    unsigned char    u8AlgmControl;                     //�㷨������: 1~5��Ĭ��3
    unsigned char    u8NumFramePropa;                   //�����ӳٲ���:2��12��Ĭ��8
    unsigned char    u8MinFollowDuration;               //Ŀ����С����ʱ��:0��Ŀ�����ʱ�䣬Ĭ��3
    unsigned int 	 u32FollowDuration;                 //Ŀ�����ʱ��:  1��1000�룬Ĭ��10��
    unsigned char    u8MaxTargetSizeX;                  //ˮƽ��չ����: 3��30��Ĭ��10
    unsigned char    u8MaxTargetSizeY;                  //��ֱ��չ����: 3~60��Ĭ��15
    unsigned char    u8PtzZoomMin;                      //���������С����
    unsigned char    u8PtzZoomMax;                      //������������
    unsigned short   u16IdleTimeout;                    //�ָ�����ʱ��: 300
    unsigned short   u16PtzHigh;                        //�����װ�߶�
    double           dbPtzZoomFactor;                   //����Ŵ�ϵ��: 0.2~2��Ĭ��0.4
    unsigned char    u8WorkMode;                        //NSD_AUTOTRACK_TYPE_E
    char             rsvd[63];
}PACKED NSD_AI_AUTO_TRACK_S,*LPNSD_AI_AUTO_TRACK_S;

typedef struct _NSD_FACE_BEHAVIOUR_CFG_S
{
    unsigned char    u8LiveDetectEnable;                //�������Ƿ���
    unsigned char    u81_1Matching;                     //1:1�ȶ�
    unsigned char    u81_NMatching;                     //1:n�ȶ�
    unsigned char    rsvd[129];
}PACKED NSD_FACE_BEHAVIOUR_CFG_S,* LPNSD_FACE_BEHAVIOUR_CFG_S;

#endif //__AI_DEFINES_H_
