//$c11
//$c10	JGM 05/22/06 Fixed some formatting typos %ls -> %s
//$c9	JGM 03/11/09 Proj 13644: fixed flxActCommonHandleGetError(), iConvErr().
//$c8	JGM 03/07/09 Proj 13644: added flxActCommonProdLicSpcFulfillmentTypeGet() and fixed some logging issues.
//$c7	JGM 02/17/09 Proj 13644: added flxActCommonLicSpcAddASRFromBuffer().
//$c6	JGM 11/13/08 Proj 13644: added lots of flxActApp*() methods.
//$c5	JGM 10/06/08 Proj 15053: added flxActCommonLicSpcProductDelete().
//$c4	JGM 10/02/08 Proj 15053: added flxActSvr{Activation,Return}VendorData{Get,Set}().
//$c3	JGM 09/26/08 Proj 15053: added more methods.
//$c2	JGM 12/18/07 Added flxActSvrActivationRespProcess().
//$c1	JGM 12/11/07 Proj 13646: created
//===========================================================//
//              Copyright 2007 (Unpublished Material)                 
//                      SolidWorks Corporation                        
//===========================================================//
//
//	File Name:		swsecflexnet.cpp
//     
//	Application:	SolidWorks FLEXnet API wrapper class
//     
//	Contents:		This class is a wrapper interface to the Macrovision/FLEXnet licensing platform
//					simplifying in places where possible where possible.
//
//					All SW FLEXnet interactions should go thru this class
//
//===========================================================//
//BEGIN PCH includes
#include "stdafx.h"
//END PCH includes

#include "swsecflexnet.h"
#include "swseceventlog.h"

swSecFLEXnet_c::swSecFLEXnet_c(swSecEventLog_c *eventLog) :
	ihFlexNETApi(NULL),
	iEventLog(eventLog)
{
}

swSecFLEXnet_c::~swSecFLEXnet_c()
{
}

/////////////////////////////////////////////////////////////////////////////

BOOL swSecFLEXnet_c::isAvailable()
{
	BOOL bRet = FALSE;

#ifdef SWSEC_FLEXNET_DEFINED
	bRet = TRUE;
#endif

	return bRet;
}

/////////////////////////////////////////////////////////////////////////////

BOOL swSecFLEXnet_c::iWriteEventLog(const int nRet, LPCTSTR msg)
{
	BOOL bRet = FALSE;
	swSecEventLog_c::eventTypes_e eventType = swSecEventLog_c::EVENT_TYPE_INFO;


	if (nRet != 1)
		eventType = swSecEventLog_c::EVENT_TYPE_ERROR;

	bRet = iEventLog->write(eventType, SWSECEVENTLOG_SRC_FLX, msg);

	return bRet;
}

/////////////////////////////////////////////////////////////////////////////

int swSecFLEXnet_c::flxActCommonLibraryInit(const char * runtimepath)
{
#ifdef SWSEC_FLEXNET_DEFINED
	int nRet;

	nRet = ::flxActCommonLibraryInit(runtimepath);

	if (iEventLog != NULL)
	{
		CString msg;

		msg.Format(_T("%d=flxActCommonLibraryInit()"), nRet);
		iWriteEventLog(!nRet, msg);
	}

	return nRet;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActCommonLibraryCleanup()
{
#ifdef SWSEC_FLEXNET_DEFINED
	::flxActCommonLibraryCleanup();

	if (iEventLog != NULL)
	{
		CString msg;

		msg.Format(_T("flxActCommonLibraryCleanup()"));
		iWriteEventLog(1, msg);
	}
#else
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActCommonHandleOpen(swSecFlx_FlxActHandle *handle, swSecFlx_FlxActMode mode, swSecFlx_FlxActError *err)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;


	ret = ::flxActCommonHandleOpen(handle, mode, err);

	if (iEventLog != NULL)
	{
		CString msg;

		msg.Format(_T("%lu=flxActCommonHandleOpen(%lu, %lu, [%lu, %lu, %lu])"), ret, handle, mode, err->majorErrorNo, err->minorErrorNo, err->sysErrorNo);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActCommonHandleClose(swSecFlx_FlxActHandle handle)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;

	ret = ::flxActCommonHandleClose(handle);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActCommonHandleClose(%lu)"), ret, handle);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActCommonLicSpcCreate(swSecFlx_FlxActHandle handle, swSecFlx_FlxActLicSpc *licSpc)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;

	if (handle == NULL)
		handle = ihFlexNETApi;

	ret = ::flxActCommonLicSpcCreate(handle, licSpc);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActCommonLicSpcCreate(%lu, %lu)"), ret, handle, licSpc);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActCommonLicSpcDelete(swSecFlx_FlxActLicSpc licSpc)
{
#ifdef SWSEC_FLEXNET_DEFINED
	::flxActCommonLicSpcDelete(licSpc);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActCommonLicSpcDelete(%lu)"), licSpc);
		iWriteEventLog(TRUE, msg);
	}
#endif
}


/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActCommonLicSpcPopulateFromTS(swSecFlx_FlxActLicSpc licSpc)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;

	ret = ::flxActCommonLicSpcPopulateFromTS(licSpc);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActCommonLicSpcPopulateFromTS(%lu)"), ret, licSpc);
		iWriteEventLog(TRUE, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActCommonLicSpcPopulateAllFromTS(swSecFlx_FlxActLicSpc licSpc)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;

	ret = ::flxActCommonLicSpcPopulateAllFromTS(licSpc);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActCommonLicSpcPopulateAllFromTS(%lu)"), ret, licSpc);
		iWriteEventLog(TRUE, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

uint32_t swSecFLEXnet_c::flxActCommonLicSpcGetNumberProducts(swSecFlx_FlxActLicSpc licSpc)
{
#ifdef SWSEC_FLEXNET_DEFINED
	uint32_t nRet;

	nRet = ::flxActCommonLicSpcGetNumberProducts(licSpc);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActCommonLicSpcGetNumberProducts(%lu)"), nRet, licSpc);
		iWriteEventLog(TRUE, msg);
	}

	return nRet;
#else
	return 0;
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActProdLicSpc swSecFLEXnet_c::flxActCommonLicSpcGet(swSecFlx_FlxActLicSpc licSpc, uint32_t index)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActProdLicSpc prodLicSpc;

	prodLicSpc = ::flxActCommonLicSpcGet(licSpc, index);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActCommonLicSpcGet(%lu, %lu, %lu)"), prodLicSpc, licSpc, index);
		iWriteEventLog(TRUE, msg);
	}

	return prodLicSpc;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActCommonHandleGetUniqueMachineNumber(swSecFlx_FlxActHandle handle, swSecFlx_FlxUMNType type, swSecTstring& stdtMachNum)
{
#ifdef SWSEC_FLEXNET_DEFINED
	CString machNumber;

	if (handle == NULL)
		handle = ihFlexNETApi;

	machNumber = ::flxActCommonHandleGetUniqueMachineNumber(handle, type);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%s=flxActCommonHandleGetUniqueMachineNumber(%lu, %lu)"), machNumber, handle, type);
		iWriteEventLog(TRUE, msg);
	}

	stdtMachNum = machNumber;
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActSvrActivationCreate(swSecFlx_FlxActHandle handle, swSecFlx_FlxActSvrActivation *serverAct)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;


	if (handle == NULL)
		handle = ihFlexNETApi;

	ret = ::flxActSvrActivationCreate(handle, serverAct);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActSvrActivationCreate(%lu, %lu)"), ret, handle, serverAct);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActSvrReturnCreate(swSecFlx_FlxActHandle handle, swSecFlx_FlxActSvrReturn *serverRet)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;


	if (handle == NULL)
		handle = ihFlexNETApi;

	ret = ::flxActSvrReturnCreate(handle, serverRet);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActSvrReturnCreate(%lu, %lu)"), ret, handle, serverRet);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActSvrActivationReqCreate(swSecFlx_FlxActSvrActivation serverAct, CString& xmlString)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;
	char *charXmlString=NULL;

	ret = ::flxActSvrActivationReqCreate(serverAct, &charXmlString);

	if (ret == swSecFlx_FLX_ACT_TRUE)
		xmlString = charXmlString;

	if (charXmlString != NULL)
		free(charXmlString);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActSvrActivationReqCreate(%lu, %s)"), ret, serverAct, xmlString);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActSvrReturnReqCreate(swSecFlx_FlxActSvrReturn serverRet, CString& xmlString)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;
	char *charXmlString=NULL;

	ret = ::flxActSvrReturnReqCreate(serverRet, &charXmlString);

	if (ret == swSecFlx_FLX_ACT_TRUE)
		xmlString = charXmlString;

	if (charXmlString != NULL)
		free(charXmlString);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActSvrReturnReqCreate(%lu, %s)"), ret, serverRet, xmlString);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActSvrActivationDelete(swSecFlx_FlxActSvrActivation serverAct)
{
#ifdef SWSEC_FLEXNET_DEFINED
	::flxActSvrActivationDelete(serverAct);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActSvrActivationDelete(%lu)"), serverAct);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActSvrReturnDelete(swSecFlx_FlxActSvrReturn serverRet)
{
#ifdef SWSEC_FLEXNET_DEFINED
	::flxActSvrReturnDelete(serverRet);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActSvrReturnDelete(%lu)"), serverRet);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActSvrActivationCountSet(swSecFlx_FlxActSvrActivation serverAct, swSecFlx_FlxActCountType type, uint32_t count)
{
#ifdef SWSEC_FLEXNET_DEFINED
	::flxActSvrActivationCountSet(serverAct, type, count);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActSvrActivationCountSet(%lu, %lu, %lu)"), serverAct, type, count);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActSvrActivationProductIdSet(swSecFlx_FlxActSvrActivation serverAct, LPCTSTR tProductId)
{
#ifdef SWSEC_FLEXNET_DEFINED
	char *charStr=NULL;


	int nLen = _tcslen(tProductId);
	charStr = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charStr, tProductId, nLen);
	#else
		_tcscpy(charStr, tProductId);
	#endif

	::flxActSvrActivationProductIdSet(serverAct, charStr);

	LocalFree(charStr);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActSvrActivationProductIdSet(%lu, %s)"), serverAct, tProductId);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActSvrActivationEntitlementIdSet(swSecFlx_FlxActSvrActivation serverAct, LPCTSTR tEntitlementId)
{
#ifdef SWSEC_FLEXNET_DEFINED
	char *charStr=NULL;


	int nLen = _tcslen(tEntitlementId);
	charStr = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charStr, tEntitlementId, nLen);
	#else
		_tcscpy(charStr, tEntitlementId);
	#endif

	::flxActSvrActivationEntitlementIdSet(serverAct, charStr);

	LocalFree(charStr);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActSvrActivationEntitlementIdSet(%lu, %s)"), serverAct, tEntitlementId);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActSvrActivationExpDateSet(swSecFlx_FlxActSvrActivation serverAct, LPCTSTR tExpDate)
{
#ifdef SWSEC_FLEXNET_DEFINED
	char *charStr=NULL;


	int nLen = _tcslen(tExpDate);
	charStr = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charStr, tExpDate, nLen);
	#else
		_tcscpy(charStr, tExpDate);
	#endif

	::flxActSvrActivationExpDateSet(serverAct, charStr);

	LocalFree(charStr);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActSvrActivationExpDateSet(%lu, %ls)"), serverAct, tExpDate);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActCommonHandleSetCommType(swSecFlx_FlxActHandle handle, swSecFlx_FlxActCommType commType)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;


	if (handle == NULL)
		handle = ihFlexNETApi;

	ret = ::flxActCommonHandleSetCommType(handle, commType);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActCommonHandleSetCommType(%lu, %lu)"), ret, handle, commType);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActCommonHandleSetRemoteServer(swSecFlx_FlxActHandle handle, LPCTSTR tTargetServer)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;
	char *charStr=NULL;


	int nLen = _tcslen(tTargetServer);
	charStr = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charStr, tTargetServer, nLen);
	#else
		_tcscpy(charStr, tTargetServer);
	#endif

	if (handle == NULL)
		handle = ihFlexNETApi;

	ret = ::flxActCommonHandleSetRemoteServer(handle, charStr);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActCommonHandleSetRemoteServer(%lu, %lu)"), ret, handle, tTargetServer);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

uint32_t swSecFLEXnet_c::flxActCommonProdLicSpcCountGet(swSecFlx_FlxActProdLicSpc prodSpc, swSecFlx_FlxActCountType countType)
{
#ifdef SWSEC_FLEXNET_DEFINED
	uint32_t nRet=0;


	nRet = ::flxActCommonProdLicSpcCountGet(prodSpc, countType);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActCommonProdLicSpcCountGet(%lu, %lu)"), nRet, prodSpc, countType);
		iWriteEventLog(TRUE, msg);
	}

	return nRet;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxFulfillmentType swSecFLEXnet_c::flxActCommonProdLicSpcFulfillmentTypeGet(swSecFlx_FlxActProdLicSpc prodSpc)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxFulfillmentType flxFulfillmentTypeRet=FULFILLMENT_TYPE_UNKNOWN;


	flxFulfillmentTypeRet = ::flxActCommonProdLicSpcFulfillmentTypeGet(prodSpc);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActCommonProdLicSpcFulfillmentTypeGet(%lu, %lu)"), flxFulfillmentTypeRet, prodSpc);
		iWriteEventLog(TRUE, msg);
	}

	return flxFulfillmentTypeRet;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::iConvErr(swSecFLEXnetErr_c& swSecFLEXnetErr, swSecFlx_FlxActError& err)
{
#ifdef SWSEC_FLEXNET_DEFINED
	swSecFLEXnetErr.m_nMaj = err.majorErrorNo;
	swSecFLEXnetErr.m_nMin = err.minorErrorNo;
	swSecFLEXnetErr.m_nSys = err.sysErrorNo;
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActCommonHandleGetError(swSecFlx_FlxActHandle handle, swSecFLEXnetErr_c& swSecFLEXnetErr)
{
#ifdef SWSEC_FLEXNET_DEFINED
	swSecFlx_FlxActError err;


	err.majorErrorNo=0;
	err.minorErrorNo=0;
	err.sysErrorNo=0;

	if (handle == NULL)
		handle = ihFlexNETApi;

	::flxActCommonHandleGetError(handle, &err);

	iConvErr(swSecFLEXnetErr, err);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActCommonHandleGetError(%lu, [%lu, %lu, %lu])"), handle, swSecFLEXnetErr.m_nMaj, swSecFLEXnetErr.m_nMin, swSecFLEXnetErr.m_nSys);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActCommonLicSpcAddASRFromBuffer(swSecFlx_FlxActLicSpc licSpc, LPCTSTR tBuffer)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;
	char *charStr=NULL;


	int nLen = _tcslen(tBuffer);
	charStr = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charStr, tBuffer, nLen);
	#else
		_tcscpy(charStr, tBuffer);
	#endif

	ret = ::flxActCommonLicSpcAddASRFromBuffer(licSpc, charStr);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActCommonLicSpcAddASRFromBuffer(%lu, %s)"), ret, licSpc, tBuffer);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActSvrActivationRespProcess(swSecFlx_FlxActSvrActivation serverAct, LPCTSTR tXmlString, swSecFlx_FlxActBool& bIsConfig)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;
	char *charStr=NULL;


	int nLen = _tcslen(tXmlString);
	charStr = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charStr, tXmlString, nLen);
	#else
		_tcscpy(charStr, tXmlString);
	#endif

	ret = ::flxActSvrActivationRespProcess(serverAct, charStr, &bIsConfig);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActSvrActivationRespProcess(%lu, %s, %lu)"), ret, serverAct, tXmlString, bIsConfig);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActSvrReturnProdLicSpcSet(swSecFlx_FlxActSvrReturn serverRet, swSecFlx_FlxActProdLicSpc product)
{
#ifdef SWSEC_FLEXNET_DEFINED
	::flxActSvrReturnProdLicSpcSet(serverRet, product);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActSvrReturnProdLicSpcSet(%lu, %lu)"), serverRet, product);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActSvrActivationVendorDataSet(swSecFlx_FlxActSvrActivation serverAct, LPCTSTR tKey, LPCTSTR tValue)
{
#ifdef SWSEC_FLEXNET_DEFINED
	int nLen=0;
	char *charKey=NULL, *charValue=NULL;


	nLen = _tcslen(tKey);
	charKey = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charKey, tKey, nLen);
	#else
		_tcscpy(charKey, tKey);
	#endif

	nLen = _tcslen(tValue);
	charValue = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charValue, tValue, nLen);
	#else
		_tcscpy(charValue, tValue);
	#endif

	::flxActSvrActivationVendorDataSet(serverAct, charKey, charValue);

	LocalFree(charKey);
	LocalFree(charValue);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActSvrActivationVendorDataSet(%lu, %s, %s)"), serverAct, tKey, tValue);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActSvrActivationVendorDataGet(swSecFlx_FlxActSvrActivation serverAct, LPCTSTR tKey, CString& value)
{
	int nLen=0;
	char *charKey=NULL;
	const char *charValue=NULL;


	nLen = _tcslen(tKey);
	charKey = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charKey, tKey, nLen);
	#else
		_tcscpy(charKey, tKey);
	#endif

	charValue = ::flxActSvrActivationVendorDataGet(serverAct, charKey);

	LocalFree(charKey);

	value = charValue;

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%s=flxActSvrActivationVendorDataGet(%lu, %s)"), value, serverAct, tKey);
		iWriteEventLog(TRUE, msg);
	}
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActSvrReturnVendorDataSet(swSecFlx_FlxActSvrReturn serverRet, LPCTSTR tKey, LPCTSTR tValue)
{
#ifdef SWSEC_FLEXNET_DEFINED
	int nLen=0;
	char *charKey=NULL, *charValue=NULL;


	nLen = _tcslen(tKey);
	charKey = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charKey, tKey, nLen);
	#else
		_tcscpy(charKey, tKey);
	#endif

	nLen = _tcslen(tValue);
	charValue = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charValue, tValue, nLen);
	#else
		_tcscpy(charValue, tValue);
	#endif

	::flxActSvrReturnVendorDataSet(serverRet, charKey, charValue);

	LocalFree(charKey);
	LocalFree(charValue);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActSvrReturnVendorDataSet(%lu, %s, %s)"), serverRet, tKey, tValue);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActSvrReturnVendorDataGet(swSecFlx_FlxActSvrReturn serverRet, LPCTSTR tKey, CString& value)
{
	int nLen=0;
	char *charKey=NULL;
	const char *charValue=NULL;


	nLen = _tcslen(tKey);
	charKey = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charKey, tKey, nLen);
	#else
		_tcscpy(charKey, tKey);
	#endif

	charValue = ::flxActSvrReturnVendorDataGet(serverRet, charKey);

	LocalFree(charKey);

	value = charValue;

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%s=flxActSvrReturnVendorDataGet(%lu, %s)"), value, serverRet, tKey);
		iWriteEventLog(TRUE, msg);
	}
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActCommonLicSpcProductDelete(swSecFlx_FlxActLicSpc licSpc, swSecFlx_FlxActProdLicSpc prodSpc)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;


	ret = ::flxActCommonLicSpcProductDelete(licSpc, prodSpc);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActCommonLicSpcProductDelete(%lu, %lu)"), ret, licSpc, prodSpc);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActAppActivationCreate(swSecFlx_FlxActHandle handle, swSecFlx_FlxActAppActivation *appAct)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;


	if (handle == NULL)
		handle = ihFlexNETApi;

	ret = ::flxActAppActivationCreate(handle, appAct);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActAppActivationCreate(%lu, %lu)"), ret, handle, appAct);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActAppActivationReqCreate(swSecFlx_FlxActAppActivation appAct, CString& xmlString)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;
	char *charXmlString=NULL;

	ret = ::flxActAppActivationReqCreate(appAct, &charXmlString);

	if (ret == swSecFlx_FLX_ACT_TRUE)
		xmlString = charXmlString;

	if (charXmlString != NULL)
		free(charXmlString);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActAppActivationReqCreate(%lu, %s)"), ret, appAct, xmlString);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActAppActivationDelete(swSecFlx_FlxActAppActivation appAct)
{
#ifdef SWSEC_FLEXNET_DEFINED
	::flxActAppActivationDelete(appAct);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActAppActivationDelete(%lu)"), appAct);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActAppActivationVendorDataSet(swSecFlx_FlxActAppActivation appAct, LPCTSTR tKey, LPCTSTR tValue)
{
#ifdef SWSEC_FLEXNET_DEFINED
	int nLen=0;
	char *charKey=NULL, *charValue=NULL;


	nLen = _tcslen(tKey);
	charKey = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charKey, tKey, nLen);
	#else
		_tcscpy(charKey, tKey);
	#endif

	nLen = _tcslen(tValue);
	charValue = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charValue, tValue, nLen);
	#else
		_tcscpy(charValue, tValue);
	#endif

	::flxActAppActivationVendorDataSet(appAct, charKey, charValue);

	LocalFree(charKey);
	LocalFree(charValue);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActAppActivationVendorDataSet(%lu, %s, %s)"), appAct, tKey, tValue);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActAppActivationVendorDataGet(swSecFlx_FlxActAppActivation appAct, LPCTSTR tKey, CString& value)
{
	int nLen=0;
	char *charKey=NULL;
	const char *charValue=NULL;


	nLen = _tcslen(tKey);
	charKey = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charKey, tKey, nLen);
	#else
		_tcscpy(charKey, tKey);
	#endif

	charValue = ::flxActAppActivationVendorDataGet(appAct, charKey);

	LocalFree(charKey);

	value = charValue;

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%s=flxActAppActivationVendorDataGet(%lu, %s)"), value, appAct, tKey);
		iWriteEventLog(TRUE, msg);
	}
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActAppReturnCreate(swSecFlx_FlxActHandle handle, swSecFlx_FlxActAppReturn *appRet)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;


	if (handle == NULL)
		handle = ihFlexNETApi;

	ret = ::flxActAppReturnCreate(handle, appRet);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActAppReturnCreate(%lu, %lu)"), ret, handle, appRet);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActAppReturnVendorDataSet(swSecFlx_FlxActAppReturn appRet, LPCTSTR tKey, LPCTSTR tValue)
{
#ifdef SWSEC_FLEXNET_DEFINED
	int nLen=0;
	char *charKey=NULL, *charValue=NULL;


	nLen = _tcslen(tKey);
	charKey = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charKey, tKey, nLen);
	#else
		_tcscpy(charKey, tKey);
	#endif

	nLen = _tcslen(tValue);
	charValue = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charValue, tValue, nLen);
	#else
		_tcscpy(charValue, tValue);
	#endif

	::flxActAppReturnVendorDataSet(appRet, charKey, charValue);

	LocalFree(charKey);
	LocalFree(charValue);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActAppReturnVendorDataSet(%lu, %s, %s)"), appRet, tKey, tValue);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActAppReturnVendorDataGet(swSecFlx_FlxActAppReturn appRet, LPCTSTR tKey, CString& value)
{
	int nLen=0;
	char *charKey=NULL;
	const char *charValue=NULL;


	nLen = _tcslen(tKey);
	charKey = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charKey, tKey, nLen);
	#else
		_tcscpy(charKey, tKey);
	#endif

	charValue = ::flxActAppReturnVendorDataGet(appRet, charKey);

	LocalFree(charKey);

	value = charValue;

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%s=flxActAppReturnVendorDataGet(%lu, %s)"), value, appRet, tKey);
		iWriteEventLog(TRUE, msg);
	}
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActAppReturnReqCreate(swSecFlx_FlxActAppReturn appRet, CString& xmlString)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;
	char *charXmlString=NULL;

	ret = ::flxActAppReturnReqCreate(appRet, &charXmlString);

	if (ret == swSecFlx_FLX_ACT_TRUE)
		xmlString = charXmlString;

	if (charXmlString != NULL)
		free(charXmlString);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActAppReturnReqCreate(%lu, %s)"), ret, appRet, xmlString);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActAppReturnDelete(swSecFlx_FlxActAppReturn appRet)
{
#ifdef SWSEC_FLEXNET_DEFINED
	::flxActAppReturnDelete(appRet);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActAppReturnDelete(%lu)"), appRet);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActAppReturnProdLicSpcSet(swSecFlx_FlxActAppReturn appRet, FlxActProdLicSpc product)
{
#ifdef SWSEC_FLEXNET_DEFINED
	::flxActAppReturnProdLicSpcSet(appRet, product);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActAppReturnProdLicSpcSet(%lu, %lu)"), appRet, product);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

swSecFlx_FlxActBool swSecFLEXnet_c::flxActAppActivationRespProcess(swSecFlx_FlxActAppActivation appAct, LPCTSTR tXmlString, swSecFlx_FlxActBool& bIsConfig)
{
#ifdef SWSEC_FLEXNET_DEFINED
	FlxActBool ret=swSecFlx_FLX_ACT_FALSE;
	char *charStr=NULL;


	int nLen = _tcslen(tXmlString);
	charStr = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charStr, tXmlString, nLen);
	#else
		_tcscpy(charStr, tXmlString);
	#endif

	ret = ::flxActAppActivationRespProcess(appAct, charStr, &bIsConfig);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("%lu=flxActAppActivationRespProcess(%lu, %s, %lu)"), ret, appAct, tXmlString, bIsConfig);
		iWriteEventLog(ret, msg);
	}

	return ret;
#else
	return -1;
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActAppActivationExpDateSet(swSecFlx_FlxActAppActivation appAct, LPCTSTR tExpDate)
{
#ifdef SWSEC_FLEXNET_DEFINED
	char *charStr=NULL;


	int nLen = _tcslen(tExpDate);
	charStr = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charStr, tExpDate, nLen);
	#else
		_tcscpy(charStr, tExpDate);
	#endif

	::flxActAppActivationExpDateSet(appAct, charStr);

	LocalFree(charStr);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActAppActivationExpDateSet(%lu, %ls)"), appAct, tExpDate);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActAppActivationProductIdSet(swSecFlx_FlxActAppActivation appAct, LPCTSTR tProductId)
{
#ifdef SWSEC_FLEXNET_DEFINED
	char *charStr=NULL;


	int nLen = _tcslen(tProductId);
	charStr = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charStr, tProductId, nLen);
	#else
		_tcscpy(charStr, tProductId);
	#endif

	::flxActAppActivationProductIdSet(appAct, charStr);

	LocalFree(charStr);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActAppActivationProductIdSet(%lu, %ls)"), appAct, tProductId);
		iWriteEventLog(TRUE, msg);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////

void swSecFLEXnet_c::flxActAppActivationEntitlementIdSet(swSecFlx_FlxActAppActivation appAct, LPCTSTR tEntitlementId)
{
#ifdef SWSEC_FLEXNET_DEFINED
	char *charStr=NULL;


	int nLen = _tcslen(tEntitlementId);
	charStr = (char *) LocalAlloc(LPTR, (nLen+1)*2);

	#ifdef _UNICODE
		wcstombs(charStr, tEntitlementId, nLen);
	#else
		_tcscpy(charStr, tEntitlementId);
	#endif

	::flxActAppActivationEntitlementIdSet(appAct, charStr);

	LocalFree(charStr);

	if (iEventLog != NULL)
	{
		CString msg;
		msg.Format(_T("flxActAppActivationEntitlementIdSet(%lu, %s)"), appAct, tEntitlementId);
		iWriteEventLog(TRUE, msg);
	}
#endif
}
