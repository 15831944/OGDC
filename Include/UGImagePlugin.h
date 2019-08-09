// UGImagePlugIn.h: interface for the UGImagePulgIn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGIMAGEPLUGIN_H__8C978A6D_1011_4B0F_A221_C9BEDA07CCD8__INCLUDED_)
#define AFX_UGIMAGEPLUGIN_H__8C978A6D_1011_4B0F_A221_C9BEDA07CCD8__INCLUDED_
//////////////////////////////////////////////////////////////////////////
//!  \file UGImagePlugin.h
//!  \brief UGImagePlugin �Ľӿڶ��塣
//!  \details ����Ӱ�����Ľӿڶ��塣
//!  \Modified Date: 2013-4-7
//!  \Modified Author:Conversion-zby
//!  \Details Comments:����UGImagePlugin�ӿڲ����Լ��ӿ���ɣ���ҪĿ������UGImagePlugin�ӿ�����Ӷನ��դ�����ݼ�����չ֧��;
//!  \Details Comments:���ε�����Ҫ��������������:(1) ����ԭ�нӿ����Ӳ�����������֧��;(2) ���Ӷನ��դ�����ݼ����нӿ�
//!  \Details Comments:�˴ε����漰����դ�����ݼ��ṹ�ĵ��������ڼ�����Աˮƽ�����Լ�ʱ��Ĳִ٣�����������������������,������
//!  \Details Comments:����Conversion-zby��ϵ!
//!  \Version OGDC-1-1(2013-4-7)
#define MAXIMGAEPALETTEENTRY 256
#ifdef WIN32
	#include <Windows.h>
	#define IMAGEEXPORT __declspec(dllexport)
#else
	#define IMAGEEXPORT
#endif

#include "Stream/ugplatform.h"
#include "Stream/ugdefs.h"
#include "Toolkit/UGPalette.h"
#include "NetToolkit/UGDownloadListener.h"
#include "Geometry/UGDataCodec.h"
#include "FileParser/UGExchangeFileType.h"
#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGFileParseRaster.h"
#include "CacheFile/UGCacheFileCommon.h"
#include "CacheFile/UGMapCacheFile.h"


//! \brief ���ظ�ʽ����.
enum ImagePixelFormat 
{
	PF_ERROR = 0,		// 0λ,��֧�ֵ����ظ�ʽ
	PF_MONO = 1,		// 1λ,��ɫ
	PF_FBIT = 4,		// 4λ,16ɫ
	PF_BYTE = 8,		// 8λ,256ɫ
	PF_TBYTE= 16,		// 16λ,��ɫ
	PF_RGB = 24,		// 24λ,���ɫ
	PF_RGBA = 32,		// 32λ,��ǿ���ɫ
	PF_LONGLONG = 64,	// 64λ,������
	PF_LONG = 320,
	PF_FLOAT = 3200,	// 32λ,������
	PF_DOUBLE = 6400,	// 64λ,˫���ȸ�����
};

//! \brief ���岻ͬ���ظ�ʽ��λ��.
enum ImagePixelBits
{
	PB_MONO = 1,
	PB_FBIT = 4,
	PB_BYTE = 8,
	PB_TBYTE = 16,
	PB_RGB = 24,
	PB_RGBA = 32,
	PB_FLOAT = 3200,
};

//! \brief ɫ�ʿռ��ʽ����.
enum ImageColorSpace
{
	CS_RGB = 0,		// ��ʾϵͳʹ��.
	CS_RGBA = 1,	// ��ʾϵͳʹ��.
	CS_CMY = 2,		// ӡˢϵͳʹ��(Cyan,Magenta,Yellow).
	CS_CMYK = 3,	// ӡˢϵͳʹ��(Cyan,Magenta,Yellow,Black)
	CS_YIQ = 4,		// ��������ϵͳʹ��(NTSC,Y:Luminance,Chrominance).
	CS_YUV = 5,		// ŷ�޵���ϵͳʹ��(PAL).
	CS_YCC = 6		// ��YUV����,JPEGʹ��.
} ;

//! \brief ��������뵥λ���� - ��׼��ʽ
enum  ImageUnit
{
	EU_DEGREE		= 0,		// Radian����
	EU_MILIMETER	= 10,		// mm����
	EU_CENTIMETER	= 100,		// ����
	EU_DECIMETER	= 1000,		// ����
	EU_METER		= 10000,	// ��
	EU_KILOMETER	= 10000000,	// ����
	EU_MILE			= 16090000,	// Ӣ��
	EU_INCH			= 254,		// Ӣ��
	EU_YARD			= 9144,		// Yard��
	EU_FOOT			= 3048,		// FeetӢ��
};

//! \brief Ӱ�����ݵ�ɫ������
struct IMAGEEXPORT UGImagePaletteEntry
{
	unsigned char peRed;
	unsigned char peGreen;
	unsigned char peBlue;
	unsigned char peAlpha;
};

//! \breif Ӱ��������
enum PluginClass {
	PC_UNKNOWN,
	PC_MAPCACHE,
	PC_MAPCACHE50,
	PC_MAPCACHEV70,
	PC_SIT,
	PC_GLOBALCACHE,
	PC_GRIDCACHE,
	PC_COMMON,
	PC_GECACHE,
	PC_WEBCACHE,
	PC_ECW,
	PC_SPI,
};

using namespace UGC;
namespace UGC
{	
	typedef void (UGSTDCALL * DownloadResponseFunc) (UGDownloadTileInfo result, UGlong pWnd);
	typedef void (UGSTDCALL * DataChangedProc) (const UGDataChangeInfo& ChangeInfo, UGlong pWnd);

	typedef void (UGSTDCALL * CheckStatusProc) (UGlong pWnd);// ����ʮ������ʧ�ܣ�����������״̬

	typedef void (UGSTDCALL * MapCacheProgressProc) (UGlong pWnd, UGint nStep);// ������Ϣ

	typedef void (UGSTDCALL * MapCachePerGroupCompleteProc) (UGlong pWnd);// ��Ƭ�������Ϣ

	typedef void (UGSTDCALL * MapCacheStatusProc) (UGlong pWnd, UGint nCompleteCount, UGlong nTotalCount);// ������������
}


class IMAGEEXPORT UGImagePlugin : public UGC::UGDownloadListener
{
public:

	//! \brief ͼ��������͡�
	enum UGImageServiceType
	{	
		//! \brief ��ͼ��
		IST_NONE				= 0,	
		//! \brief SuperMap Ӱ���ļ���������ͼ��
		IST_FILE				= 1, 
		//! \brief WMSͼ��
		IST_WMS					= 2,
		//! \brief WMTSͼ��
		IST_WMTS				= 3,
		//! \brief TMSͼ��
		IST_TMS                 = 4,
	};
    
	//! \brief ����๹�캯��
	UGImagePlugin()
	{
		m_nCurBandIndex = -1;
		m_dNoValue = -9999; 
		m_nPluginClass = PC_UNKNOWN;
		m_bBackTransparent = FALSE; 
		m_nImageServiceType = IST_NONE;
		m_bIsOpenAsOneBand  = FALSE;
		m_bSaveLocalCache = TRUE;
	}

	//! \brief �������������
	virtual ~UGImagePlugin(){}

public:

	//! \brief �ر��ļ���
	virtual void Close() = 0;
	//! \brief  ��ȡͼƬ���ֵ
	//! \param 
	//! \attention 
	virtual UGdouble GetMax(){return 0.0;}
	//! \brief ��ȡͼƬ��Сֵ
	//! \param  
	//! \attention 
	virtual UGdouble GetMin(){return 0.0;}
	//! \brief ���Ӱ���ļ������ظ�ʽ��
	//! \param  nPixelformat ���ظ�ʽ����RGB,�Ҷȵ�[out]
	virtual UGbool GetPixelFormat(ImagePixelFormat& nPixelformat) = 0;

	//! \brief �������λ��
	//! \param  nPixelbits,���ظ�ʽλ������RGBһ����24λ[out]
	virtual UGbool GetPixelBits(ImagePixelBits& nPixelbits)= 0;

	//! \brief �õ�Ӱ��Ĵ�С
	//! \param  nWidth Ӱ����[out]
	//! \param  nHeight Ӱ��߶�[out]
	virtual UGbool GetImageSize(UGlong&  nWidth, UGlong&  nHeight)= 0;

	//!  \brief �õ���ǰ������Ӱ���С
	//!  \param nWidth Ӱ����
	//!  \param nHeight Ӱ��߶�
	//!  \param dScale ���浱ǰ������
	//!  \remark �˺�����ҪӦ���ڻ�ȡ�����ʷֻ����Ӧ�����ߵ�Ӱ����
	virtual UGbool GetImageSize(UGint& nWidth,UGint& nHeight,UGdouble dScale){return FALSE;}

	//! \brief �õ�Ӱ��ͼƬ��ʽ
	virtual UGFileType::EmType GetImageType(){return UGFileType::none;}

	//!  \brief  �Ƿ���ȫ�򻺴�
	//! \return true
	virtual UGbool IsGlobalCache(){return TRUE;}

	//! \brief �жϲ���Ƿ��
	virtual UGbool IsOpen(){return FALSE;}

	//! \brief �жϲ���Ƿ����������
	virtual UGbool IsNetCache(){return FALSE;}

	//! \return �������
	virtual PluginClass GetPluginClass() { return m_nPluginClass; }

	//! \brief  �����������ƣ����� ECW �ļ����.
	//! \param  strName,�ַ���,���������ռ�.[out]
	//! \param  nMaxLength �ַ�������[in]
	virtual UGbool GetPluginName(UGchar* strName, UGint nMaxLength) = 0;

	//! \brief  
	//! \param 
	//! \attention
	virtual void GetExtremum(UGdouble &dMaxZ, UGdouble &dMinZ, UGint nBandIndex = 0){return;}

	//! \brief  �õ������֧�ֵ�Ӱ���ļ�����չ������".BMP",".JPG"�ȡ�
	//! \param  nIndex �ڼ�����չ��������ͨ��GetExtNameCountȡ��֧�ֵ���չ����Ŀ��[in]
	//! \param  strExtName ��չ���ַ��������������ռ䡣[out]
	//! \param  nMaxLength �ַ������ȡ�[in]
	virtual UGbool GetExtName(UGchar* strExtName, UGint nMaxLength, UGint nExtNameIndex = 0) = 0;



	//! \brief ���õ�ǰ��ʾ��Χ��,������ʾ��Χ��Ӱ�����ݵĿ�ȡ�
	//! \remarks ���ڶ�ֱ���ͼ�󣬿��ܴ�����һ���ȡ���ݣ���������Ŀ�ȿ��ܺ���ʾ��Χ�Ŀ�Ȳ�һ��
	//! \param  nViewWidth ��ʾ����Ӱ���ȡ�[out]
	//! \param  nViewHeight ��ʾ����Ӱ��߶ȡ�[out]
	virtual UGbool GetViewImageSize(UGint&  nViewWidth, UGint&  nViewHeight)= 0;

	//! \brief ���õ�ǰ��ʾ��Χ��,������ʾ��Χ�����ݵĴ�С��
	virtual UGint GetViewImageDataSize() = 0; 

	//! \brief ���õ�ǰ��ʾ��Χ��,��ȡ��ʾ��Χ�ڵ�Ӱ������,�ⲿȡ�������Ժ󣬿���������ʾ
	//! \param  pDataBuffer Ӱ�����ݣ����������ռ䡣[in]
	//! \param  nSize ���ݴ�С(�ֽ�������һ�����GetViewImageDataSize��������ֵ[in]
	virtual UGbool GetViewImageData(UGbyte* pDataBuffer, UGint nSize)= 0;

	//! \brief ���õ�ͼ�Ĺ̶������ߡ�ĳЩ����Դ�������ͼ������Ҫ�����õ�ͼ�Ĺ̶�������

	//! \brief ���ļ���
	//! \param  strFileName,�ļ�·������[in]
	//! \param  nFlags,�򿪷�ʽ����ֻ��������ȣ��ο�CFile�ı�־��[in]
	virtual UGbool Open(const UGchar* strFileName, UGuint nFlags, const UGchar * strPassword) = 0;

	//! \brief ���õ�ǰ��ʾ��Χ���������ͨ�� GetViewImageData() ���
	//! \param  nLeft, nTop,��ʾ��Χ����ߺ��ϱߡ�nLeft < nRight��nTop < nBottom.[in]
	//! \param  nRight, nBottom ��ʾ��Χ���ұߺ��±ߡ����Ǹ�ֵ��������������[in]
	//! \param  nDeviceWidth, nDeviceHeight ��ʵ��ʾ���ڵĴ�С����Ļ���ص�λ��[in]
	//! \param  bLoadEveryPicEntirely load��ÿ��ͼƬ�������ģ�ȫ�����غ�����ƫ�ƣ�ȱʡ��false[in]
	//! \remarks ���ڶ�ֱ��ʵ�ͼ�󣬿��԰��մ��ڴ�С����ʾ��Χ��С��ȷ��ͼ��ķֱ���,�Ӷ���������һ��ȡ��Ӱ������
	virtual UGbool SetViewPort(UGint nLeft,UGint nTop, UGint nRight, UGint nBottom, UGint nDeviceWidth, UGint nDeviceHeight) = 0;

	//! \brief ���õ�ǰ��ʾ��Χ���������ͨ�� GetViewImageData() ���
	//! \param  dLeft, dTop,��ʾ��Χ����ߺ��ϱߡ�dLeft < dRight��dTop < dBottom.[in]
	//! \param  dRight, dBottom ��ʾ��Χ���ұߺ��±ߡ����Ǹ�ֵ�����ǵ�������[in]
	//! \param  nDeviceWidth, nDeviceHeight,��ʵ��ʾ���ڵĴ�С����Ļ���ص�λ��[in]
	//! \remarks ���ڶ�ֱ��ʵ�ͼ�󣬿��԰��մ��ڴ�С����ʾ��Χ��С��ȷ��ͼ��ķֱ���,�Ӷ���������һ��ȡ��Ӱ������
	virtual UGbool SetViewPort(UGdouble dLeft,UGdouble dTop, UGdouble dRight, UGdouble dBottom, UGint nDeviceWidth, UGint nDeviceHeight,UGbool bLoadEveryPicEntirely = false) = 0;

	//! \brief �õ�Ӱ��ĵ���Χ�Լ����굥λ,�ο�enumUnit
	//! \param  dLeft, dRight ����Χ����ߺ��ұߣ�һ��dRight > dLeft.[out]
	//! \param  dButtom, dTop ����Χ���±ߺ��ϱߣ�һ��dTop > dBottom.[out]
	//! \param  nUnits ����λ���繫��׻�γ�ȡ�[out]
	virtual UGbool GetImageGeoRefrence(UGdouble& dLeft, UGdouble& dTop, UGdouble& dRight, UGdouble& dBottom, ImageUnit& nUnits)= 0;  

	//! \brief pMap ����Ҫ���ù̶������ߵĵ�ͼ [in]
	//! \brief pCallBack �������ù̶������ߵĻص��������ûص�������һ������Ϊ UGMap ָ�룬�ڶ�������Ϊ����Ҫ���õĹ̶������� [in]
	virtual void ConfigureMap(void *pMap, void (*pCallBack) (void *, std::vector<UGdouble>)) { /* do nothing */ }

	//! \brief ���õ�ǰӰ�������ݼ����ڽ���������
	//! \param  viewWidth ��ʾ���ڵ����ط�Χ
	//! \param  nDeviceWidth �����豸���
	//! \remarks ���ڶ�ֱ��ʵ�ͼ��(���н�����������),���԰��մ��ڿ�Ⱥ���ʾ��Χ��ȷ��ͼ��ķֱ���,�Ӷ���������һ��(������)ȡ��Ӱ������
	virtual UGbool setPymidLevel(UGint nTierIndex/*UGint viewWidth,UGint nDeviceWidth*/){return TRUE;};

	// ******** ��Ϊ���ϵĽṹ��֧�ֶ��߳� �����Ӽ����ӿ� [ by jiangrs 2012/10/12 ]*********  

	//! \brief ͨ�����õ�ǰ��ʾ��Χ����ȡ��ʾ��Χ����Ҫ��Ӱ�����ݵĿ��
	//! \param  dLeft, dTop,��ʾ��Χ����ߺ��ϱߡ�dLeft < dRight��dTop < dBottom.[in]
	//! \param  dRight, dBottom ��ʾ��Χ���ұߺ��±ߡ����Ǹ�ֵ�����ǵ�������[in]
	//! \param  nDeviceWidth, nDeviceHeight,��ʵ��ʾ���ڵĴ�С����Ļ���ص�λ��[in]
	//! \param  nViewWidth ��ʾ����Ӱ���ȡ� [out]
	//! \param  nViewHeight ��ʾ����Ӱ��߶ȡ�[out]
	//! \param  nTierIndex ��ʾ����Ӱ������������š� [out]
	//! \remarks ��SetViewPort() + GetViewImageSize()�ĺ���
	virtual UGbool GetViewImageSize(UGint dLeft, UGint dTop, UGint dRight, UGint dBottom, UGint nDeviceWidth, UGint nDeviceHeight, UGint& nViewWidth, UGint& nViewHeight, UGint& nTierIndex){return FALSE;}

	//! \brief ͨ����ȡ��Ӱ�����ݵĿ�ߺ���ʾ��Χ  ����ImgBlock�� Ȼ�����ô�ImgBlockȥ��ȡ����
	//! \param  pResBlock Ӱ�����ݣ����������ռ䡣[out]
	//! \remarks ��GetViewImageData(unsigned char* pDataBuffer, int nSize)�ĸİ�
	virtual UGbool GetViewImageData(UGImgBlock* pResBlock, UGint nTierIndex = -1){return FALSE;}

	//  ******** ��Ϊ���ϵĽṹ��֧�ֶ��߳� �����Ӽ����ӿ� [ by jiangrs 2012/10/12 ]*********  
	//! \brief �õ�ɨ����
	virtual UGbool GetScanline(UGint nRowIndex,UGImgScanline& ScanLine, UGint nStartCol = 0, UGint nWidth = 0,UGint nBandIndex=0){return FALSE;}

	//===================================================
	//! \brief  ��ȡͼƬ���ֵ
	//! \attention 
	virtual UGdouble GetMaxZ(UGint nBandIndex = 0){return 0.0;}

	//===================================================
	//! \brief ��ȡͼƬ��Сֵ
	//! \attention 
	virtual UGdouble GetMinZ(UGint nBandIndex = 0){return 0.0;}

	//! \brief  ����ͳ��ֱ��ͼ
	//! \param 
	//! \return   
	//! \remarks 
	//! \attention
	virtual UGHistogram* GetHistogram( 
		UGdouble dMin, 
		UGdouble dMax,
		UGint nBandIndex = 0,
		UGint nBuckets = 256){return FALSE;}

	//===================================================
	//! \brief  ��ȡͼƬ�Ŀ�
	//! \param 
	//! \return   
	//! \remarks 
	//! \attention
	virtual UGint GetWidth() const{return 0;}

	//===================================================
	//! \brief  ��ȡͼƬ��
	//! \param 
	//! \return   
	//! \remarks 
	//! \attention
	virtual UGint GetHeight() const{return 0;}
    
    //===================================================
	//! \brief  ͳ��դ����Ϣ
	//! \param 
	//! \return   
	//! \remarks 
	//! \attention
 	virtual UGbool BuildStatistic(UGint nBandIndex, UGRasterStatisticsInfo& inof){return FALSE;}
    	//===================================================
	//! \brief  �õ�դ����Ϣ
	//! \param 
	//! \return   
	//! \remarks 
	//! \attention
 	virtual UGbool GetStatisticsInfo(UGint nBandIndex, UGRasterStatisticsInfo &info){return FALSE;}

	//===================================================
	//! \brief  ��ȡ������Ϣ�б�
	//! \param  bandInfos[out]  Ҫ����Ĳ�����Ϣ�б�
	//! \return   
	//! \remarks 
	//! \attention ����ನ��ʱ�á�
	virtual UGbool GetBandInfos(UGArray<BandInfo>& bandInfos){return FALSE;}	

	//! \brief��ȡ����鷵�ص�׼ȷbounds
	virtual  UGRect2D GetViewImageBounds(){return m_rcViewImgBounds;} 

	//===================================================
	//! \brief   �ֲ��μ��㼫ֵ
	//! \param   dMax[O]       ���ֵ
	//! \param   dMin[O]       ��Сֵ
	//! \param   nBandIndex[I] ��������
	//! \return   
	//! \remarks 
	//! \attention
	virtual UGbool CalculateExtremum(UGdouble &dMax, UGdouble &dMin, UGint nBandIndex = 0){return FALSE;}

	//! \brief   ��ȡFileParse������
	virtual UGFileType::EmType GetFileParseType(){return UGFileType::none;}

	//! \brief   ��ȡ���ݼ�������
	virtual UGint GetDatasetType(){return 88/*UGDataset::MBImage*/;}

	//! \brief ��������
	virtual UGbool SaveImageFile(UGdouble dScale, UGint nRow, UGint nCol, UGByteArray* pByteArray) {return FALSE;}

	//�õ����ݵĸ߶ȷ�Χ
	virtual UGdouble GetTop(){return 0.0;}
	virtual UGdouble GetBottom(){return 0.0;}

	//�õ����ݵĲ㷶Χ
	virtual UGint GetBeginLevel(){return 0;}

	virtual UGint GetEndLevel(){return 0;}
public:
	/*
		�����ͼ���������ط�ʽ
	*/
	//! \brief ����Web������û��� ����ʹ��Open()��ͷ�Ľӿڰɣ�����
	virtual void SetUser(const UGString strUser){return ;}

	//! \brief ����ȡ�����ݲ��������������Ӿ��η��ظ��û��Ļص�����
	//! \param pFunc �ص�����[in]��
	//! \param pWnd ���[in]��
	//! \remarks ��άʹ�õİ�������
	virtual void SetDataChangedFunc(DataChangedProc pFunc,UGlong pWnd){return; }

	//! \brief ���ûص�����
	//! \remarks ��άʹ�õİ�������
	virtual void SetDownloadResponseFunc(DownloadResponseFunc pFunc,UGlong pWnd){return; }

	//! \brief �����������
	//! \dScale param[in] ��ǰ��ͼ�ı�����
	//! \bound param[in] ��ǰ��ͼ��Χ
	virtual UGbool Request(const UGdouble& dScale, const UGRect2D& bound, UGbool bCallBack = TRUE){return FALSE;}

	//! \brief �����������
	//! \dScale param[in] ��ǰ��ͼ�ı�����
	//! \bound param[in] ��ǰ��ͼ��Χ
	virtual UGbool GetRequests(UGArray<void*> &arrRequest, const UGdouble& dScale, const UGRect2D& bound, UGString strToken = _U("")){return FALSE;}

	//! \brief ͨ��������ת����Ƭ�߳���Ӧ�ĵ����С
	//! \param dMapScale ��ͼ������
	virtual UGSize2D GetTileMPSize(UGdouble dMapScale){return UGSize2D();}

	//! \brief ��ȡ��Ƭ��DP��С
	virtual UGSize GetTileSize(){return UGSize();}

	//! \brief ��ȡ��Ƭ��DP��С
	virtual UGuint GetTileDepth(){return 1;}

	//! \brief �������еı����߼���
	virtual const UGArray<UGdouble> GetScales() const {return UGArray<UGdouble>();}	
	
	//! \brief �ж�һ�������Ƿ��Ѿ���ɣ�Request֮�����
	//! \remarks ��IsFinished()��һ��  IsFinished()���ж�GetViewBlock()���ص��Ƿ���ȫ
	//! \return ��ɷ���True�����򷵻�False
	virtual UGbool IsCompleteRequest() {return TRUE;}

	//! \brief ���ݷ�Χ�ͱ����ߣ���ѯ��¼����
	//! \param rcMapBounds [in] ��Χ��
	//! \param dScale [in] �����ߡ�
	//! \return ���ط�Χ��������Ƭ����Ϣ 
	virtual UGTiles* QueryWithBounds(const UGRect2D& rcMapBounds, UGdouble dScale) const {return NULL;}

	//! \brief ���ػ���Ӱ�������
	//! \tile param ������Ƭ��Ϣ[in]
	//! \return ��Ƭ��ImageData
	virtual UGImageData* LoadTileImageData(const UGTile& tile){return NULL;}

	//! \brief ��ȡ��ӽ��ı�����
	//! \param dScale ���������
	//! \return ������ӽ��Ĺ̶�������
	virtual UGdouble ScaleToNearFixScale(UGdouble dScale){return 0.0;}

	//! \brief ����һ����Χ���ż�����Ƭ֮��ķ�Χ
	//! \param dMapScale ��ͼ������
	//! \param rcMapBounds ��ͼ��Χ
	//! \param nExtTileSize ������Ƭ�ĸ���
	//! \return ����֮��ĵ�ͼ��Χ
	virtual UGRect2D ComputeTilesBounds(UGdouble dMapScale, const UGRect2D& rcMapBounds, UGint nExtTileSize = 1){return UGRect2D();}

	//! \brief ��ȡ��ǰ������ƬDP-->LP��ת������
	virtual UGdouble GetCoordRatio() {return 3.0;}

	//! \brief ���ݷ�Χ�ͱ����ߣ��жϸ÷�Χ�ڵ���Ƭ�Ƿ�ȫ�����ڡ�
	//! \param rcMapBounds [in] ��Χ��
	//! \param dScale [in] �����ߡ�
	//! \return 
	virtual UGbool IsAllTilesExist(const UGRect2D& rcMapBounds, UGdouble dScale) const {return FALSE;}

	//! \brief ��ȡ���ػ���İ汾��(Ƕ��ʽʹ��)
	virtual UGint GetCacheVersion() const {return 0;}

	//! \brief ��ȡ��ǰ����SCI��DP-->LP��ת������(Ƕ��ʽʹ�ã���Ҫ��ʹ��GetCoordRatio�����)
	virtual UGdouble GetCacheCoordRatio(){return 0.0;}

	//! \brief ��ȡ����ֵ
	//!\param nBandIndex �洢�Ĳ�������,Ĭ�ϵĲ���������ʼֵΪ0
	virtual UGColor GetPixel(UGint X,UGint Y,UGint nBandIndex=0){return UGColor(0);};

	//! \brief ��ȡ��ֵ
	//!\param nBandIndex �洢�Ĳ�������,Ĭ�ϵĲ���������ʼֵΪ0
	virtual UGdouble GetValue(UGint X,UGint Y, UGbool bIsNeedLock = TRUE,UGint nBandIndex=0){return UGdouble(0.0);};

	//! \brief �����̳л�ȡ����ڴ����ݺ���
	//! \param nBlockRow ����б��
	//! \Param nBblockCol ����б��
	//! \param pImgBlock ָ�����ڴ��ַ
	//! \param  nlevel[int] �㼶 
	//! \Param nBandIndex ������ڲ�������λ��
	virtual UGbool GetBlockAt(UGint nBlockRow,UGint nBlockCol,
		UGImgBlock*& pImgBlock,UGint m_nLevel,UGint nBandIndex=0){return FALSE;};

	// ��ȡIndexBounds, added by XingJun, 2016.03.16
	virtual UGRect2D GetIndexBounds() const {return UGRect2D();};
public:

	//! \brief �ͷ��Լ��������������Ҫ��һ����̬���ڷ���Ķ��ڴ棬
	//! \remarks ������һ����̬�����ͷſ��ܻ�������Ը��������ͷ��Լ���
	virtual UGbool BuildPyramid(UGbool bShhowProgress){return FALSE;}
    
	//! \brief ɾ��������
	//! \param 
	//! \return ɾ���ɹ�����TRUE�����򷵻�FALSE
	virtual UGbool RemovePyramids(){return FALSE;}
    
	//! \brief �Ƿ���ڽ�����
	//! \param  
	//! \return ���ڽ���������TRUE�������ڽ���������FALSE
	virtual UGbool IsExistPyramid() const {return FALSE;}
    
	//! \brief Ϊդ���ļ��޸�����
	//! \param  bool �޸���������Ƿ�ɹ�[out]
	//! \param  strNewPassword ���õ�������[in]
	virtual UGbool ChangePassword(const UGchar* strNewPassword){return FALSE;}

	//! \brief Ϊ��ȡդ���ļ��Ļ����������
	//! \return ���������õ����룬��û�������򷵻ؿ�
	virtual const UGchar* GetPassword() {return NULL;}

	//! \brief �õ�֧�ֵ�Ӱ���ļ���չ����Ŀ��
	virtual UGint GetExtNameCount() const{return 1;}
	
	//! \brief  �õ�������Ŀ��
	virtual UGint GetBandCount() const {return 1;}

	//! \brief  ���õ�ǰȡ���ݵĲ���������
	//! \param  nBandIndex ����������[in]
	virtual void SetCurBandIndex(UGint nCurBandIndex){m_nCurBandIndex = nCurBandIndex;}

	//! \brief  �õ���ǰȡ���ݵĲ���������
	virtual UGint GetCurBandIndex() const{return m_nCurBandIndex;}

	//! \brief  ���ò������ģʽ��
	//! \param  pBandIndexs �����������顣[in]
	//! \param  nColorSpace ��ɫ�ռ�ģʽ��[in]
	virtual void SetBandCombineMode(const int* pBandIndexs, ImageColorSpace nColorSpace){}

	//! \brief  �õ��������ģʽ��
	//! \param  pBandIndexs �����������飬���濪���ڴ档���Ϊ4��int��������ɫ�ռ�ģʽ������[out]
	//! \param  nColorSpace ��ɫ�ռ�ģʽ��[out]
	virtual void GetBandCombineMode(int* pBandIndexs, ImageColorSpace& nColorSpace) const{}

	//! \brief ����ͶӰ��Ϣ
	virtual void SetPrjCoordSys(const UGchar*strPrjCoordSys){}

	//! \brief XML�ַ���
	virtual const UGchar* GetPrjCoordSys(){return NULL;}

	//! \brief �����ļ��汾��Ϣ
	virtual void SetVersion(UGint nVersion){}
	virtual UGint GetVersion(){return 0;}
	
	//! \brief �õ�ָ����Χ���ݵİ汾��Ϣ
	virtual UGint GetDataVersion(UGdouble dLeft,UGdouble dTop, UGdouble dRight, UGdouble dBottom, UGint nDeviceWidth, UGint nDeviceHeight){return 0;}
	
	//! \brief �õ��ü�����,����Ҫ��������ڴ棬������Ҫ�����ͷš�
	virtual UGbool GetClipRgn(UGdouble*& pXCoord, UGdouble*& pYCoord, UGint*& pPloyCounts, UGint& nSubCount){return FALSE;}

	//! \brief �ͷ���ʱ���ݡ�
	virtual void Release(){}

	//! \brief �ͷŻ����е�����
	virtual void FreeCache() {}

	//! \brief �������ؽ���
	virtual float GetDataStreamingProgress(){return -1.0;}

	//! brief �õ���ʾ�Ľ�����������Ҫ���ڴ��(�ֽ�)
	//! param nBand ����
	//! param nTierIndex ����������
	virtual UGint GetViewPyramidDataSize(UGint nBand, UGint nTierIndex){return 0;}

	//! \brief ������ʾ�ĵ���Χ
	//! \param ��ʾ�ķ�Χ
	//! \remarks ������������UGPluginCommon�����õģ��ڷֿ��ȡRDAS��IMG��ʽ�ļ�ʱ���õ�
	//! ��UGDatasetRasterImg::GetViewBlock�����е���
	virtual void SetViewBounds(UGdouble dLeft, UGdouble dTop, UGdouble dRight, UGdouble dBottom){};

	//! \brief GetViewImageData() ��ȡ�����Ƿ��Ѿ���ȡ��ϣ�
	//! \brief���û�У���Ҫ�������� GetViewImageData() ��ȡ���ݡ���ǰֻ�� UGPluginMapCache �п���һ�����޷���ȡȫ�����ݡ�
	virtual UGbool IsFinished() { return true; }

	//!	\brief	��ȡ�����ȫ·���ļ���
	virtual const UGchar* GetPluginFileName() { return NULL; }

	//! \brief �����Ƿ񱳾�͸��
	virtual void SetBackTransparent(UGbool bBackTransparent){ m_bBackTransparent = bBackTransparent; }

	// ��ȡ�Ƿ񱳾�͸��
	virtual UGbool IsTransparentBack() { return m_bBackTransparent; }

	//! \briefͼ������
	virtual UGImageServiceType GetImageServiceType() { return m_nImageServiceType; }

	//! \brief ��������UGPluginGlobalCache��,֧������WMS����
	//! \brief ��ȡ�������ݼ�����ͼ��
	virtual UGbool GetWebSubLayersName(UGStrings& aryLayerNames) const{ return false; }

	//! \brief ��ȡ�������ݼ�����ͼ�����
	virtual UGbool GetWebSubLayersTitle(UGStrings& aryLayerTitle) const{ return false; }

	//! \brief �����������ݼ�����ͼ���Ƿ�ɼ�����
	virtual UGbool SetWebSubLayersVisible(UGStrings& arrLayersVisible){ return false; }

	//! \brief �õ��������ݼ�����ͼ���Ƿ�ɼ�����
	virtual UGbool GetWebSubLayersVisible(UGStrings& arrLayersVisible) const{ return false; }

	//! \brief ���û���Ŀ¼
	//! \param  [in]��
	//! \remarks ��Ҫ�������WMSͼ��
	virtual void SetCachePath(const UGString& strCachePath) { }

	//! \brief ��ȡ�������ĸ���
	//! \�õ��ڼ����εĽ������ĸ���
	virtual UGint GetPyramidCount(UGint nBand){return 0;}

	//===================================================
	//! \brief  ��ȡ���������ݼ���Ϣ�б�
	//! \param  rasterInfos[out]Ҫ����Ľ�������Ϣ�����б�
	//! \return  ��ȡ��������Ϣ�ɹ�����TRUE,���򷵻�FALSE 
	//! \attention ����ನ��ʱ�á�
	virtual UGbool GetPyramidInfos(UGArray<PyramidInfo>& pyramidInfos){return FALSE;}

	//! \brief ��ȡ����ѹ����ʽ
	//! \return ����ѹ����ʽ��
	//! \attention ��
	virtual UGDataCodec::CodecType GetTextureCodecType() {return UGDataCodec::encNONE;}

	//! \brief ����DXT��ʽ�����Ƿ���Ҫ��ѹ
	//! \param  bIsDXTEncode[in]�Ƿ��ѹ
	//! \attention ��ͼDXTZ������ص�����ά����ʱʹ��
	virtual void SetIsTextureEncode(UGbool bIsDXTEncode) {;}

	virtual UGbool GetOpenAsOneBand(){return m_bIsOpenAsOneBand;}

	virtual void SetOpenAsOneBand(UGbool bIsOpenAsOneBand = FALSE){m_bIsOpenAsOneBand = bIsOpenAsOneBand;}
	
	virtual void RemoveCallbackHandle(long handle){};WhiteBox_Ignore
	virtual UGC::UGHPDataArea GetTileDataArea(){return UGHPDataArea();};
	//! \�õ�������λ����Ƭ��MPBounds
	virtual UGRect2D ComputeTileMPBounds(double dMapScale, int nRow, int nCol){return UGRect2D();};
	virtual UGdouble GetCurrentScale(){return 0;};
	virtual UGImagePlugin* ClonePlugin(){return NULL;};
	//������ض���
	virtual void RemoveRequest(){};

	//���������Сֵ
	virtual UGdouble GetMaxValue(){return 0.0;};
	virtual UGdouble GetMinValue(){return 0.0;};

	virtual UGMapCacheFile* GetMapCacheFile() {return NULL;};

	//! \brief �õ������������
	virtual void* GetServiceStub(){return NULL;}

	//! \brief �������������Ƿ񱣴浽����
	virtual void SetSaveLocalCache(UGbool bSave){m_bSaveLocalCache = bSave;}

	//! \brief ��ȡ���������Ƿ񱣴浽����
	virtual UGbool GetSaveLocalCache(){return m_bSaveLocalCache;}

	//! \brief �����Ƿ�ʹ���ڴ�פ��
	virtual void SetMemCacheEnable(UGbool bEnable){return;}
public:
	//! \brief ���ø����û���Ƭ��������ʧ�ܵĻص�����
	//! \param pFunc �ص�����[in]��
	//! \param pWnd ���[in]��
	virtual void SetCheckStatusFunc(CheckStatusProc pFunc,UGlong pWnd){}

	//! \brief ���ø����û�Ԥ����ĳһ��������ɵĻص�����
	//! \param pFunc �ص�����[in]��
	//! \param pWnd ���[in]��
	virtual void SetMapCachePerGroupCompleteFunc(MapCachePerGroupCompleteProc pFunc,UGlong pWnd){}

	virtual void SetTotalTiles(UGint nTotalCount){}

	virtual UGint GetFailedCount(){ return 0;}

	virtual void StopMapDownloadQueue(){}
public:

	//! \brief  ��ɫ�����ݡ�
	UGArray<UGImagePaletteEntry> m_arrPalette;  

	//! \brief  ��ֵ����
	UGdouble m_dNoValue;

protected:
	//! \brief ��Ӧ���ļ����������͡�
	UGint m_nFileType;

	//! \brief ��ǰ����������
	UGint m_nCurBandIndex;

	//! \brief �ϳɲ�����������
	UGint m_bandCombine[4];
    
	//! \brief ��ɫ�ռ�
	ImageColorSpace m_nColorSpace;

	//! \brief �Ƿ񱳾�͸��
	UGbool m_bBackTransparent; 
    
	//! \brief ��ǰӰ��������
	PluginClass m_nPluginClass;	
    
	//! \brief ͼ���������
	UGImageServiceType m_nImageServiceType;
    
	//! \brief Ӱ��ĵ���bounds
	UGRect2D m_rcViewImgBounds; 

	//! \breif �Ƿ��Ѻϳɲ��εķ�ʽ��
	//! ���ӿ�Ŀǰֻ�������ݼ�����
	UGbool m_bIsOpenAsOneBand;

	//! \breif ���������Ƿ����ر��浽�����ļ�
	UGbool m_bSaveLocalCache;
};



// �����Ҫʵ��һ��������ȫ�ֺ����������� UGImagePlugin �������ࡣ
// ����һ������࣬��new һ���� UGImagePlugin �������ࡣ

extern "C" IMAGEEXPORT UGImagePlugin* CreateImagePlugin();

#endif // !defined(AFX_UGIMAGEPLUGIN_H__8C978A6D_1011_4B0F_A221_C9BEDA07CCD8__INCLUDED_)

