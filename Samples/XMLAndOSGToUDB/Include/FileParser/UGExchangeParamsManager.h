//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     7.2           
//                                                           
//!  \file UGExchangeParamsManager.h
//!  \brief ����ת����������
//!  \details ��Ҫ����UGExchangeParamsManagerת�����������ࡣ
//!  \author ����ת���顣
//!  \attention 
//!   Copyright (c)   SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 7.2
//////////////////////////////////////////////////////////////////////////

#ifndef AFX_UGEXCHANGEPARAMSMANAGER_H__INCLUDED_
#define AFX_UGEXCHANGEPARAMSMANAGER_H__INCLUDED_

#include "Stream/ugdefs.h"
#include "FileParser/UGFileParserConfigParams.h"

namespace UGC {

	//! \brief ת�����������ࡣ
	//! \remarks �������ݵ��뵼�������������ͷš���Ч�Լ�⡣
	class FILEPARSER_API UGExchangeParamsManager  
	{
	public:
		//! \brief ���캯����
		//! \remarks ����һ���µ�ת�������������
		UGExchangeParamsManager();

		//! \brief ����������
		//! \remarks �ͷ�ת�������������
		virtual ~UGExchangeParamsManager();

	public:
		//! \brief ������Ӧ��ʽ�ĵ��������
		//! \param nType [in] �ļ���ʽ���͡�
		//! \param strPwd [in] ���롣
		//! \return �ɹ����ص��������ʧ�ܷ���NULL��
		//! \remarks �û����ͷ��ڴ棬����ֻ���SIT�ļ���ʽ�����á�
		//! \attention �ļ��������С�
		static UGImportParams* MakeImportParams(UGint nType, UGString strPwd=_U(""));

		//! \brief ������Ӧ��ʽ�ĵ���������
		//! \param nType [in] �ļ���ʽ���͡�
		//! \return �ɹ����ص���������ʧ�ܷ���NULL��
		//! \remarks �û����ͷ��ڴ档
		//! \attention �ļ��������С�
		static UGExportParams* MakeExportParams(UGint nType);

		//! \brief �ͷŵ�����������
		//! \param &pImportParams [in] �����������
		static void DestoryImportParams(UGImportParams* &pImportParams);

		//! \brief �ͷŵ������������
		//! \param &pExportParams [in] ������������
		static void DestoryExportParams(UGExportParams* &pExportParams);

		//! \brief ���������Ч�Լ�顣
		//! \param nFileType [in] �ļ���ʽ���͡�
		//! \param impParams [in] �����������
		//! \return true���������Ч��false���������Ч��
		static UGbool IsValidImportParams(UGint nFileType, const UGImportParams& impParams);

		//! \brief ����������Ч�Լ�顣
		//! \param nFileType [in] �ļ���ʽ���͡�
		//! \param expParams [in] ������������
		//! \return true����������Ч��false����������Ч��
		static UGbool IsValidExportParams(UGint nFileType, const UGExportParams& expParams);
	};

}
#endif // !defined(AFX_UGEXCHANGEPARAMSMANAGER_H__AB19AA8C_B64E_42F0_BFF3_DDE67CDBA62F__INCLUDED_)

