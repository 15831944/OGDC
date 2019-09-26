

#ifndef UGLICENSEENV_H
#define UGLICENSEENV_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stream/ugdefs.h"

namespace UGC
{			
	
	class TOOLKIT_API UGLicenseEnvironment
	{

	public:
	enum ChartLicenseState
	{
		UnEnable			= -1,	// ������
		iServerEnable		= 0,	// iServer��ɿ���
		DeskproEnable		= 1,	// ������ɿ���
		ObjectEnable		= 2,	// �����ɿ���
	};									

	protected:
		UGLicenseEnvironment();		
	public:	

		// �����Ƿ��������, 0����ʽ��ɣ�1Ϊ��ͼ������ɣ�2Ϊ����������ɣ�3Ϊ��ά�������
		static void SetIsUnregistered(UGint nType, UGbool bUnregistered);
		static UGbool GetIsUnregistered(UGint nType);

		// ���û��ȡ��ǰ��ͼ����Ƿ���� [8/31/2011 zhoujt]
		static void SetChartLicenseState(UGint nCode);
		static UGLicenseEnvironment::ChartLicenseState GetChartLicenseState();

		// ��ȡ�����õ�ǰ��Ʒ�Ƿ�������ƺ�ͼͼ�� [9/2/2011 zhoujt]
		static void SetDrawChartLayer(UGbool bEnable = false);
		static UGbool GetDrawChartLayer();

		static UGbool GetLicCheckMode();
	
		static void SetLicCheckMode(UGString mode);

		// �Ƿ�ʹ�������
		static void SetUseCloudLicense(UGbool bUse = false);
		static UGbool IsUseCloudLicense();

		// ���������ˮӡ������
		static void SetCloudLicenseText(UGString text);
		static UGString GetCloudLicenseText();
	private:

		// �Ƿ�������ɣ�Ĭ��false
		static UGbool m_bUnregisteredMap;
		static UGbool m_bUnregisteredLayout;
		static UGbool m_bUnregisteredSpace;

		// ��ǰ��ͼ��ɵ�״̬
		// iServer��ɿ��� --- 0; ������ɿ��� --- 1; �����ɿ��� -- 2; û����� --- -1;
		static UGLicenseEnvironment::ChartLicenseState m_eChartLicenseState;
		static UGbool m_bDrawCharLayer;
		static UGString g_checkMode;

		static UGbool g_bIsUseCloudLicense;
		static UGString g_strCloudLicenseText;
	};	
	
}
#endif //UGLICENSE
