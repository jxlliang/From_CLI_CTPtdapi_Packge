#include "stdafx.h"
#include "TdApiClr.h"
#include<string>
#include"TdCenterSpi.h"
namespace TdCTP
{
	TdApiClr::TdApiClr():tdcspi(NULL)
	{

	}
	TdApiClr::~TdApiClr()
	{

	}

	TdApiClr ^ TdApiClr::GetInstance()
	{
		if (clrTdExsample == nullptr)
			clrTdExsample = gcnew TdApiClr();
		return clrTdExsample;
	}

	void TdApiClr::OnFrontConnected_()
	{
		this->onFrontConnectDelegate();
	}

	void TdApiClr::OnFrontDisconnected_(int nReason)
	{
		this->onFrontDisConnectDelegate(nReason);
	}

	void TdApiClr::OnRspAuthenticate_(RspAuthenticateField ^ pRspAuthenticateField, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		this->onAuthenDelegate(pRspAuthenticateField, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspUserLogin_(RspUserLogin ^ pRspUserLogin, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		this->onRspLoginDelegate(pRspUserLogin, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspUserLogout_(RspUserLogout ^ pUserLogout, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		this->onRspLogoutDelegate(pUserLogout, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspOrderInsert_(OrderInsert ^ pInputOrder, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		this->onRspOrderInsertDelegate(pInputOrder, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspOrderAction_(OrderAction ^ pInputOrderAction, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		this->onOrderActionDelegate(pInputOrderAction, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspSettlementInfoConfirm_(RspSettlementInfoConfirm ^ pSettlementInfoConfirm, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		this->onRspSettlementInfoConfirmDelegate(pSettlementInfoConfirm, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspQuoteInsert_(RspInputQuoteField ^ pInputQuote, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		this->onQuoteInsertDelegate(pInputQuote, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspQuoteAction_(RspQuoteActionField ^ pInputQuoteAction, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		onQuoteActionDelegate(pInputQuoteAction, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspQryInvestorPosition_(RspInvestorPositionField ^ pInvestorPosition, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		onRspQryInvestorPositionDelegate(pInvestorPosition, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspQryTradingAccount_(RspTradingAccountField ^ pTradingAccount, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		onRspQryTradingAccountDelegate(pTradingAccount, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspQryInvestor_(RspInvestorField ^ pInvestor, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		onRspQryInvestorDelegate(pInvestor, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspQryInstrument_(RspInstrumentField ^ pInstrument, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		onRspQryInstrumentDelegate(pInstrument, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspQrySettlementInfo_(RspSettlementInfoField ^ pSettlementInfo, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		onRspQrySettlementInfoDelegate(pSettlementInfo, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspQryInvestorPositionDetail_(RspInvestorPositionDelailField ^ pInvestorPositionDetail, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		onRspQryInvestorPositionDetailDelegate(pInvestorPositionDetail, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspQrySettlementInfoConfirm_(RspSettlementInfoConfirm ^ pSettlementInfoConfirm, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		onRspQrySettlementInfoConfirmDelegate(pSettlementInfoConfirm, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspQryInvestorPositionCombineDetail_(RspInvestorPositionCombineDetailField ^ pInvestorPositionCombineDetail, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		onRspQryInvestorPositionCombineDetailDelegate(pInvestorPositionCombineDetail, pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRspError_(ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast)
	{
		onErrorDelegate(pRspInfo, nRequestID, bIsLast);
	}

	void TdApiClr::OnRtnOrder_(RtnOrderField ^ pOrder)
	{
		onRtnOrderDelegate(pOrder);
	}

	void TdApiClr::OnRtnTrade_(RtnTradeField ^ pTrade)
	{
		onRtnTradeDelegate(pTrade);
	}

	//////////////////////主动函数//////////////////////////
	void TdApiClr::CreateCenter() //tdcspi
	{
		tdcspi = new TdCenterSpi(this);
	}

	void TdApiClr::CreateTdApi_(char * pszFlowPath)
	{
		this->api = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);
		this->api->RegisterSpi(this->tdcspi);
	}

	const char * TdApiClr::GetApiVersion_()
	{
		return this->api->GetApiVersion();
	}

	void TdApiClr::Init_()
	{
		this->api->Init();
	}

	void TdApiClr::Release_()
	{
		this->api->Release();
	}

	int TdApiClr::Join_()
	{
		this->api->Join();
		this->api->RegisterSpi(NULL);
		this->api->Release();
		this->api = NULL;
		this->tdcspi = NULL;
		return 1;
	}

	const char * TdApiClr::GetTradingDay_()
	{
		return this->api->GetTradingDay();
	}

	void TdApiClr::RegisterFront_(char * pszFrontAddress)
	{
		this->api->RegisterFront(pszFrontAddress);
	}

	void TdApiClr::RegisterNameServer_(char * pszNsAddress)
	{
		this->api->RegisterNameServer(pszNsAddress);
	}

	void TdApiClr::SubscribePrivateTopic_()
	{
		THOST_TE_RESUME_TYPE nResumeType = THOST_TE_RESUME_TYPE();
		this->api->SubscribePrivateTopic(nResumeType);
	}

	void TdApiClr::SubscribePublicTopic_()
	{
		THOST_TE_RESUME_TYPE nResumeType = THOST_TE_RESUME_TYPE();
		this->api->SubscribePrivateTopic(nResumeType);
	}

	int TdApiClr::ReqAuthenticate_(ReqAuthenticateField ^ pReqAuthenticateField, int nRequestID)
	{
		CThostFtdcReqAuthenticateField authenticate = CThostFtdcReqAuthenticateField();
		strcpy_s(authenticate.AuthCode, (char*)(void*)Marshal::StringToHGlobalAnsi(pReqAuthenticateField->AuthCode));
		strcpy_s(authenticate.BrokerID, (char*)(void*)Marshal::StringToHGlobalAnsi(pReqAuthenticateField->BrokerID));
		strcpy_s(authenticate.UserID, (char*)(void*)Marshal::StringToHGlobalAnsi(pReqAuthenticateField->UserID));
		strcpy_s(authenticate.UserProductInfo, (char*)(void*)Marshal::StringToHGlobalAnsi(pReqAuthenticateField->UserProductInfo));
		return this->api->ReqAuthenticate(&authenticate,nRequestID);
	}

	int TdApiClr::ReqUserLogin_(ReqUserLoginField ^ pReqUserLoginField, int nRequestID)
	{
		CThostFtdcReqUserLoginField userLogin = CThostFtdcReqUserLoginField();
		strcpy_s(userLogin.BrokerID, (char*)(void*)Marshal::StringToHGlobalAnsi(pReqUserLoginField->BrokerID));
		strcpy_s(userLogin.ClientIPAddress, (char*)(void*)Marshal::StringToHGlobalAnsi(pReqUserLoginField->ClientIPAddress));
		strcpy_s(userLogin.Password, (char*)(void*)Marshal::StringToHGlobalAnsi(pReqUserLoginField->Password));
		return this->api->ReqUserLogin(&userLogin, nRequestID);
	}

	int TdApiClr::ReqUserLogout_(ReqUserLogoutField ^ pUserLogout, int nRequestID)
	{
		CThostFtdcUserLogoutField userLogout = CThostFtdcUserLogoutField();
		strcpy_s(userLogout.BrokerID, (char*)(void*)Marshal::StringToHGlobalAnsi(pUserLogout->BrokerID));
		strcpy_s(userLogout.UserID, (char*)(void*)Marshal::StringToHGlobalAnsi(pUserLogout->UserID));
		return this->api->ReqUserLogout(&userLogout, nRequestID);
	}

	int TdApiClr::ReqOrderInsert_(OrderInsert ^ pInputOrder, int nRequestID)
	{
		CThostFtdcInputOrderField inputOrder = CThostFtdcInputOrderField();
		strcpy_s(inputOrder.BrokerID, (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrder->BrokerID));
		strcpy_s(inputOrder.CombHedgeFlag, (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrder->CombHedgeFlag));
		strcpy_s(inputOrder.CombOffsetFlag, (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrder->CombOffsetFlag));
		strcpy_s(inputOrder.ExchangeID, (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrder->ExchangeID));
		char * ch = (char*)inputOrder.Direction;
		strcpy_s(ch, strlen(ch), (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrder->Direction));
		strcpy_s(inputOrder.GTDDate, (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrder->GTDDate));
		strcpy_s(inputOrder.InstrumentID, (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrder->InstrumentID));
		strcpy_s(inputOrder.InvestorID, (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrder->InvestorID));
		inputOrder.LimitPrice = pInputOrder->LimitPrice;
		inputOrder.MinVolume = pInputOrder->MinVolume;
		char* vcond = (char*)inputOrder.VolumeCondition;
		strcpy_s(vcond, strlen(vcond), (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrder->VolumeCondition));
		char* orderP = (char*)inputOrder.OrderPriceType;
		strcpy_s(orderP, strlen(orderP), (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrder->OrderPriceType));
		//strcpy_s(inputOrder.OrderRef,(char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrder->OrderRef));
		strcpy_s(inputOrder.UserID, (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrder->UserID));
		inputOrder.VolumeTotalOriginal = pInputOrder->VolumeTotalOriginal;
		return this->api->ReqOrderInsert(&inputOrder, nRequestID);
	}

	int TdApiClr::ReqOrderAction_(OrderAction ^ pInputOrderAction, int nRequestID)
	{
		CThostFtdcInputOrderActionField orderAction = CThostFtdcInputOrderActionField();
		orderAction.FrontID = pInputOrderAction->FrontID;
		strcpy_s(orderAction.InstrumentID, (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrderAction->InstrumentID));
		strcpy_s(orderAction.OrderSysID, (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrderAction->OrderSysID));
		orderAction.SessionID = (pInputOrderAction->SessionID);
		strcpy_s(orderAction.UserID, (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrderAction->UserID));
		strcpy_s(orderAction.BrokerID, (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrderAction->BrokerID));
		strcpy_s(orderAction.InvestorID, (char*)(void*)Marshal::StringToHGlobalAnsi(pInputOrderAction->InvestorID));
		return this->api->ReqOrderAction(&orderAction, nRequestID);
	}

	int TdApiClr::ReqSettlementInfoConfirm_(ReqSettlementInfoConfirmField ^ pSettlementInfoConfirm, int nRequestID)
	{
		CThostFtdcSettlementInfoConfirmField settlementInfoConFirm = CThostFtdcSettlementInfoConfirmField();
		strcpy_s(settlementInfoConFirm.BrokerID, (char*)(void*)Marshal::StringToHGlobalAnsi(pSettlementInfoConfirm->BrokerID));
		strcpy_s(settlementInfoConFirm.InvestorID, (char*)(void*)Marshal::StringToHGlobalAnsi(pSettlementInfoConfirm->InvestorID));
		return this->api->ReqSettlementInfoConfirm(&settlementInfoConFirm, nRequestID);
	}

	int TdApiClr::ReqQryInvestorPosition_(ReqInvestorPositionField ^ pQryInvestorPosition, int nRequestID)
	{
		CThostFtdcQryInvestorPositionField investorPosition = CThostFtdcQryInvestorPositionField();
		strcpy_s(investorPosition.BrokerID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInvestorPosition->BrokerID));
		strcpy_s(investorPosition.InstrumentID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInvestorPosition->InstrumentID));
		strcpy_s(investorPosition.InvestorID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInvestorPosition->InvestorID));
		return this->api->ReqQryInvestorPosition(&investorPosition, nRequestID);
	}

	int TdApiClr::ReqQryTradingAccount_(ReqTradingAccountField ^ pQryTradingAccount, int nRequestID)
	{
		CThostFtdcQryTradingAccountField account = CThostFtdcQryTradingAccountField();
		memset(&account, 0, sizeof(account));
		strcpy_s(account.BrokerID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryTradingAccount->BrokerID));
		strcpy_s(account.InvestorID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryTradingAccount->InvestorID));
		return this->api->ReqQryTradingAccount(&account, nRequestID);
	}

	int TdApiClr::ReqQryInvestor_(ReqInvestorField ^ pQryInvestor, int nRequestID)
	{
		CThostFtdcQryInvestorField investor = CThostFtdcQryInvestorField();
		memset(&investor, 0, sizeof(investor));
		strcpy_s(investor.BrokerID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInvestor->BrokerID));
		strcpy_s(investor.InvestorID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInvestor->InvestorID));
		return this->api->ReqQryInvestor(&investor, nRequestID);
	}

	int TdApiClr::ReqQryInstrument_(ReqInstrumentField ^ pQryInstrument, int nRequestID)
	{
		CThostFtdcQryInstrumentField instrument = CThostFtdcQryInstrumentField();
		memset(&instrument, 0, sizeof(instrument));
		strcpy_s(instrument.ExchangeID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInstrument->ExchangeID));
		strcpy_s(instrument.InstrumentID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInstrument->InstrumentID));
		strcpy_s(instrument.ExchangeInstID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInstrument->ExchangeInstID));
		strcpy_s(instrument.ProductID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInstrument->ProductID));
		return this->api->ReqQryInstrument(&instrument, nRequestID);
	}

	int TdApiClr::ReqQrySettlementInfo_(ReqSettlementInfoField ^ pQrySettlementInfo, int nRequestID)
	{
		CThostFtdcQrySettlementInfoField settlementInfo = CThostFtdcQrySettlementInfoField();
		memset(&settlementInfo, 0, sizeof(settlementInfo));
		strcpy_s(settlementInfo.BrokerID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQrySettlementInfo->BrokerID));
		strcpy_s(settlementInfo.InvestorID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQrySettlementInfo->InvestorID));
		strcpy_s(settlementInfo.TradingDay, (char*)(void*)Marshal::StringToHGlobalAnsi(pQrySettlementInfo->TradingDay));
		return this->api->ReqQrySettlementInfo(&settlementInfo, nRequestID);
	}

	int TdApiClr::ReqQryInvestorPositionDetail_(ReqInvestorPositionDetailField ^ pQryInvestorPositionDetail, int nRequestID)
	{
		CThostFtdcQryInvestorPositionDetailField investorPositionDetail = CThostFtdcQryInvestorPositionDetailField();
		memset(&investorPositionDetail, 0, sizeof(investorPositionDetail));
		strcpy_s(investorPositionDetail.BrokerID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInvestorPositionDetail->BrokerID));
		strcpy_s(investorPositionDetail.ExchangeID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInvestorPositionDetail->ExchangeID));
		strcpy_s(investorPositionDetail.InstrumentID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInvestorPositionDetail->InstrumentID));
		strcpy_s(investorPositionDetail.InvestorID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInvestorPositionDetail->InvestorID));
		return this->api->ReqQryInvestorPositionDetail(&investorPositionDetail, nRequestID);
	}

	int TdApiClr::ReqQrySettlementInfoConfirm_(ReqSettlementInfoConfirmField ^ pQrySettlementInfoConfirm, int nRequestID)
	{
		CThostFtdcQrySettlementInfoConfirmField settlementFirm = CThostFtdcQrySettlementInfoConfirmField();
		memset(&settlementFirm, 0, sizeof(settlementFirm));
		strcpy_s(settlementFirm.BrokerID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQrySettlementInfoConfirm->BrokerID));
		strcpy_s(settlementFirm.InvestorID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQrySettlementInfoConfirm->InvestorID));
		return this->api->ReqQrySettlementInfoConfirm(&settlementFirm, nRequestID);
	}

	int TdApiClr::ReqQryInvestorPositionCombineDetail_(ReqInvestorPositionCombineDetailField ^ pQryInvestorPositionCombineDetail, int nRequestID)
	{
		CThostFtdcQryInvestorPositionCombineDetailField inpo = CThostFtdcQryInvestorPositionCombineDetailField();
		memset(&inpo, 0, sizeof(inpo));
		strcpy_s(inpo.BrokerID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInvestorPositionCombineDetail->BrokerID));
		strcpy_s(inpo.CombInstrumentID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInvestorPositionCombineDetail->CombInstrumentID));
		strcpy_s(inpo.InvestorID, (char*)(void*)Marshal::StringToHGlobalAnsi(pQryInvestorPositionCombineDetail->InvestorID));
		return this->api->ReqQryInvestorPositionCombineDetail(&inpo, nRequestID);
	}
	/////////////////////////主动函数/////////////////////////////////

	///////////////////////////委托回调函数/////////////////////////////
	void TdApiClr::SetOnFrontConnectedDelegate(OnFrontConnectedDelegate ^ connected)
	{
		onFrontConnectDelegate = connected;
	}
	void TdApiClr::SetOnFrontDisconnectedDelegate(OnFrontDisconnectedDelegate ^ disConnected)
	{
		onFrontDisConnectDelegate=disConnected;
	}
	void TdApiClr::SetOnRspUserLoginDelegate(OnRspUserLoginDelegate ^ login)
	{
		onRspLoginDelegate = login;
	}
	void TdApiClr::SetOnRspUserLogoutDelegate(OnRspUserLogoutDelegate ^ logout)
	{
		onRspLogoutDelegate = logout;
	}
	void TdApiClr::SetAuthenDelegate(OnAuthenticateDelegate ^ authen)
	{
		onAuthenDelegate = authen;
	}
	void TdApiClr::SetOnRspErrorDelegate(OnRspErrorDelegate ^ error)
	{
		onErrorDelegate = error;
	}
	void TdApiClr::SetOnRspOrderInsertDelegate(OnRspOrderInsertDelegate ^ orderInsert)
	{
		onRspOrderInsertDelegate = orderInsert;
	}
	void TdApiClr::SetOnRspOrderActionDelegate(OnRspOrderActionDelegate ^ orderAction)
	{
		onOrderActionDelegate = orderAction;
	}
	void TdApiClr::SetOnRspQuoteInsertDelegate(OnRspQuoteInsertDelegate ^ quoteInsert)
	{
		onQuoteInsertDelegate = quoteInsert;
	}
	void TdApiClr::SetOnRspQuoteActionDelegate(OnRspQuoteActionDelegate ^ quoteaction)
	{
		onQuoteActionDelegate = quoteaction;
	}
	void TdApiClr::SetOnRspQryInvestorPositionDelegate(OnRspQryInvestorPositionDelegate ^ investorPosition)
	{
		onRspQryInvestorPositionDelegate = investorPosition;
	}
	void TdApiClr::SetOnRspQryTradingAccountDelegate(OnRspQryTradingAccountDelegate ^ tradingAccount)
	{
		onRspQryTradingAccountDelegate = tradingAccount;
	}
	void TdApiClr::SetOnRspQryInvestorDelegate(OnRspQryInvestorDelegate ^ investor)
	{
		onRspQryInvestorDelegate = investor;
	}
	void TdApiClr::SetOnRspQryInstrumentDelegate(OnRspQryInstrumentDelegate ^ instrument)
	{
		onRspQryInstrumentDelegate = instrument;
	}
	void TdApiClr::SetOnRspSettlementInfoConfirmDelegate(OnRspSettlementInfoConfirmDelegate ^ settlementInfoConfirm)
	{
		onRspSettlementInfoConfirmDelegate = settlementInfoConfirm;
	}
	void TdApiClr::SetOnRspQrySettlementInfoDelegate(OnRspQrySettlementInfoDelegate ^ settlementInfo)
	{
		onRspQrySettlementInfoDelegate = settlementInfo;
	}
	void TdApiClr::SetOnRspQryInvestorPositionDetailDelegate(OnRspQryInvestorPositionDetailDelegate ^ investorPositionDetail)
	{
		onRspQryInvestorPositionDetailDelegate = investorPositionDetail;
	}
	void TdApiClr::SetOnRspQryInvestorPositionCombineDetailDelegate(OnRspQryInvestorPositionCombineDetailDelegate ^ onInvestorPositionCombineDetail)
	{
		onRspQryInvestorPositionCombineDetailDelegate = onInvestorPositionCombineDetail;
	}
	void TdApiClr::SetOnRspQrySettlementInfoConfirmDelegate(OnRspQrySettlementInfoConfirmDelegate ^ onRspQrySettlementInfoConfirm)
	{
		onRspQrySettlementInfoConfirmDelegate = onRspQrySettlementInfoConfirm;
	}
	void TdApiClr::SetOnRtnOrderDelegate(OnRtnOrderDelegate ^ rtnOrder)
	{
		onRtnOrderDelegate = rtnOrder;
	}
	void TdApiClr::SetOnRtnTradeDelegate(OnRtnTradeDelegate ^ rtnTrade)
	{
		onRtnTradeDelegate = rtnTrade;
	}
}