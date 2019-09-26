// UGImgToolkit.h: interface for the UGImgToolkit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGIMGTOOLKIT_H__21224E42_7983_49CB_99BC_9792CA94305F__INCLUDED_)
#define AFX_UGIMGTOOLKIT_H__21224E42_7983_49CB_99BC_9792CA94305F__INCLUDED_

#pragma warning (disable:4244)

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Toolkit/UGPalette.h"
#include "Toolkit/UGMarkup.h"
#include "Element/OgdcRasterBlock.h"
#include "Geometry/UGDataCodec.h"
#include "Geometry/UGGeoRegion.h"

#define IMAGECONFIGEFILE_HEADER			_U("SuperMapImageConfig")
#define IMAGECONFIGEFILE_PRJ			_U("SuperMapProjection")
#define IMAGECONFIGEFILE_CLIPREGION		_U("SuperMapClipRegion")
#define IMAGECONFIGEFILE_STATINFO		_U("SuperMapStatisticsInfo")

namespace UGC
{
//դ�����ݼ�ͳ����Ϣ(Ϊ�˸�FileParser��Engine�ã���Toolkit��)
class TOOLKIT_API UGRasterStatisticsInfo
{
	public:
		UGRasterStatisticsInfo();
		virtual ~UGRasterStatisticsInfo();
public:
		void SetMax(UGdouble max);
		UGdouble GetMax();
		void SetMin(UGdouble min);
		UGdouble GetMin();
		void SetMiddle(UGdouble mid);
		UGdouble GetMiddle();
		void SetAverage(UGdouble average);
		UGdouble GetAverage();
		void SetStddev(UGdouble stddev);
		UGdouble GetStddev();
		void SetVariance(UGdouble variance);
		UGdouble GetVariance();
		UGbool HasMax();
		UGbool HasMin();
		UGbool HasStddev();
		UGbool HasVariance();
		UGbool HasMiddle();
		UGbool HasAverage();
	private:
		UGdouble m_dMax;//���ֵ
		UGdouble m_dMin;//��Сֵ
		UGdouble m_dMiddle;//��ֵ
		UGdouble m_dAverage;//ƽ��ֵ
		UGdouble m_dStddev;//��׼��
		UGdouble m_dVariance;//����
		 
		//! \brief ͳ����Ϣ��һ������ȡ���������������±�ʶ�������ж���Щ��Ա����Ϣ����Ч��
		UGbool m_bHasMin;      // ��Сֵ�Ƿ���Ч
		UGbool m_bHasMax ;     // ���ֵ�Ƿ���Ч
		UGbool m_bHasMiddle;   // ��ֵ�Ƿ���Ч
		UGbool m_bHasAverage;  // ƽ��ֵ�Ƿ���Ч
		UGbool m_bHasStddev;   // ��׼���Ƿ���Ч
		UGbool m_bHasVariance; // �����Ƿ���Ч
	public:
		UGArray<UGdouble> m_arrMost;//����
		UGArray<UGdouble> m_arrLeast;//ϡ��
		UGbool IsDirty;
} ;

	  //!  \brief Toolkit
	struct UGCMYK 
	{
	  //!  \brief Toolkit
		UGuint CValue;
	  //!  \brief Toolkit
		UGuint MValue;
	  //!  \brief Toolkit
		UGuint YellowVal;
	  //!  \brief Toolkit
		UGuint KValue;
	};


class TOOLKIT_API UGImgToolkit  
{
public:
	  //!  \brief Toolkit
	enum ReflectType
	{
	  //!  \brief Toolkit
		XAXES,	//ˮƽ���߶Գ�
	  //!  \brief Toolkit
		YAXES,	//��ֱ���߶Գ�
	  //!  \brief Toolkit
		ORIGIN	//�е�Գ�
	};
public:
	  //!  \brief Toolkit
	UGImgToolkit();
	  //!  \brief Toolkit
	virtual ~UGImgToolkit();

public:
	//==============================================================
	//�������ظ�ʽ�����ؿ�ȼ���DWORD����İ���BYTE�Ƶ�ʵ����Ҫ���.
	//! \brief
	  //!  \brief Toolkit
	static UGint AlignWidth(OGDC::PixelFormat PixelFormat,UGint lPixelWidth);
	//! \brief
	  //!  \brief Toolkit
	static UGint AlignWidthByte(OGDC::PixelFormat PixelFormat,UGint lPixelWidth);
	//! \brief
	  //!  \brief Toolkit
	static UGint AlignWidthWord(OGDC::PixelFormat PixelFormat,UGint lPixelWidth);
	
	//! \brief
	  //!  \brief Toolkit
	static UGushort BitCount(OGDC::PixelFormat PixelFormat);		//���ݸ�ʽ����λ��.
	//! \brief
	  //!  \brief Toolkit
	static UGushort PaletteSize(OGDC::PixelFormat PixelFormat);	//�õ���Ҫ�ĵ�ɫ���С.
	//! \brief
	  //!  \brief Toolkit
	static OGDC::PixelFormat Bit2Format(UGushort wBitCount);		//����λ�����ظ�ʽ.
	
	//! \brief
	//!  \brief ��GIF�ļ�������RGBA��ʽ
	static UGbool ImageGIFToRGBA(UGImageData& imageData, UGbyte nAlpha = 255); 
	//! \brief
	  //!  \brief Toolkit
	static UGbool ImageDataToRGBA(UGImageData& imageData, UGbyte nAlpha = 255);  // �ȸ���ά�ð��Ժ������ơ�
	//! \brief 32λColors��ɫת��ΪImageData��ʽ�������ʹ��
	//! \param imageData	 Ҫת�ɵ�ImageData��ʽ[in/out]
	//! \param nWidth		 Ҫת�ɵ�ImageData�Ŀ��[in]
	//! \param nHeight		 Ҫת�ɵ�ImageData�ĸ߶�[in]
	//! \param pData		 �����32λ��ɫ��[in]
	//! \return ת���Ƿ�ɹ�
	//! \remarks �����Ϊ32λ�ַ���������ΪnWidth*32/4*nHeight,ת�����ImagedataҲΪ232λ��ʽ
	//! \brief
	static UGbool ColorsToImageData(UGImageData& imageData, UGint nWidth,UGint nHeight,UGColor* pData);  // �ȸ���ά�ð��Ժ������ơ�
	  //!  \brief Toolkit
	//! \brief
	static UGuint GetValue(const UGbyte* pByte, UGint nWidthBytes, OGDC::PixelFormat pixelFormat, UGuint x, UGuint y);
	//! \brief
	  //!  \brief Toolkit
	static void SetValue(UGbyte* pByte, UGint nWidthBytes, OGDC::PixelFormat pixelFormat, UGuint x, UGuint y, UGuint nValue);
	//! \brief ����ImageData��
	//! \param arySrcImgData [in]��
	//! \param nReflectType ��������[in]��
	//! \return ��
	//! \remarks ��
	//! \attention ��
	static UGArray<UGImageData*> ReflectImageData(UGArray<UGImageData*>& arySrcImgData,ReflectType nReflectType);	
	
	//! \brief ���������㷨 ��������
	static UGbool BilinearInterpolation(UGColor& nColor ,UGArray<UGdouble>& arrValue
		, ImgColorSpace nColorSpace,UGArray<UGdouble>&dMinZs,
		UGArray<UGdouble>&dMaxZs,UGint nBandCount );

	//! \brief ���������㷨 Ӱ�������
	//	BilinearInterpolation	CubicConvolution NearestNeighbor
	static UGbool BilinearInterpolation(UGImgBlock *pResBlock, UGArray<UGImgBlock*>& arrImgBlock
		, ImgColorSpace nColorSpace,UGArray<UGdouble>&dMinZs,
		UGArray<UGdouble>&dMaxZs,UGint nBandCount , UGbool bMaxMinStretch=true);

	//!\brief ��������ķ��㷨
	static UGbool BilinearInterpolationR(UGArray<UGdouble>& arrValue,UGColor nColor, 
		ImgColorSpace nColorSpace,UGArray<UGdouble>&dMinZs,
		UGArray<UGdouble>&dMaxZs,UGint nBandCount );

	//##ModelId=483BB7090157
	static UGbool AppendBlock(UGImgBlock* pResBlock, UGImgBlock* pSrcBlock, UGint nOpenMPNum = 0, UGbool bHasNoValue = FALSE, UGdouble dNoValue = 0.0); 

	//add by kangweibo,����ƶ���WMS������ʾ��������,��ʱ����ô����ֻ���ƶ���ʹ�ã�
	static UGbool AppendBlockWMS(UGImgBlock* pResBlock, UGImgBlock* pSrcBlock);

	//! \brief ��ò�ͬ��ֵ������256λ֮��ı���
	static UGdouble GetRatioPixel(UGdouble dMaxZ,UGdouble dMinZ,OGDC::PixelFormat ePixelFormat);
	//! \brief ͨ��nColor����ȡʵ�ʵ�RGBֵ
	static UGColor GetColor(UGint nColor,ImgColorSpace nColorSpace);

	#if PACKAGE_TYPE==PACKAGE_UGC
	//ɫ�ʿռ�ת��------------------------------------------------------------
	//! \brief
	  //!  \brief Toolkit
	static UGint RGB2CMY(UGint color);
	//! \brief
	  //!  \brief Toolkit
	static UGint CMY2RGB(UGint color);
	//! \brief
	  //!  \brief Toolkit
	static UGint RGB2YIQ(UGint color);
	//! \brief
	  //!  \brief Toolkit
	static UGint YIQ2RGB(UGint color);
	//! \brief
	  //!  \brief Toolkit
	static UGint RGB2YUV(UGint color);
	//! \brief
	  //!  \brief Toolkit
	static UGint YUV2RGB(UGint color);
	//! \brief
	  //!  \brief Toolkit
	static UGint RGB2YCC(UGint color);
	//! \brief
	  //!  \brief Toolkit
	static UGint YCC2RGB(UGint color);
	//! \brief CMYK��RGBת�� ��SFC���ּ���
	static UGint CMYK2RGB(UGCMYK& cmyk);
	  //!  \brief Toolkit
	static UGCMYK RGB2CMYK(UGColor color);
	//! \brief
	static void RGBtoHSL(UGColor rgb, UGdouble& H, UGdouble& S, UGdouble& L);
	//! \brief
	static UGColor HLStoRGB(const UGdouble& H, const UGdouble& L, const UGdouble& S);
	//! \brief
	static UGdouble HuetoRGB(UGdouble m1, UGdouble m2, UGdouble h);
	#endif // end declare ugc API

	//! \brief �ж���ɫ���Ƿ�8λ�Ҷ�
	static UGbool IsGrayColorset(const UGColorset &colorset);


	//! \brief ͼƬ�����2��N�η��������Ա�����ά�а�����ص����⡣
	//! \param imageData ͼƬ���� [out]��
	//! \param nRealWidth ��Ч���ݵĿ�� [out]��
	//! \param nRealHeight ��Ч���ݵĸ߶� [out]��
	//! \return ��
	//! \remarks ��
	//! \attention ��
	static void ImageDataToPowerOfTwo(UGImageData& imageData, UGint& nRealWidth, UGint& nRealHeight, UGbyte chA = 255);


	//{{Ӱ�����������ļ�(.xml)
	//׼��д�������ļ���û�о�����һ������д�������SuperMap��ǩ����;
	//����д��������
	static UGbool PrepareImageConfigFile(const UGString strFilePath);
	//���ݱ�ǩ��дxml�ַ���
	static UGbool ElementToConfigFile(const UGString strFilePath, const UGString strElemTag, UGString strContent);
	static UGString ElementFromConfigFile(const UGString strFilePath, const UGString strElemTag );

	// դ����Ϣ��ʽ����XML
	static UGString StatisticsInfoToXML(UGDict<UGint, UGRasterStatisticsInfo> &dictRasterStatInfo, UGString strDTName);
	static void StatisticsInfoFromXML(const UGString& strXML, UGArray<UGint> arrBandIndex, UGDict<UGint, UGRasterStatisticsInfo> &dictRasterStatInfo);
		static void ParserStatInfoXML(UGMarkup& markup, UGRasterStatisticsInfo& statInfo, UGbool isToXML);
	//}}Ӱ�����������ļ�(.xml)
};
}

#endif // !defined(AFX_UGIMGTOOLKIT_H__21224E42_7983_49CB_99BC_9792CA94305F__INCLUDED_)


