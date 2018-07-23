#include "stdafx.h"
#include "TdCenterSpi.h"

namespace TdCTP
{
	gcroot<TdApiClr^>*tdClr;
	TdCenterSpi::TdCenterSpi(TdApiClr^ clr_)
	{
		TdApiClr^ clr = clr_;
		tdClr = new gcroot<TdApiClr^>(clr);
		this->m_ptdapiClr = static_cast<void*>(tdClr);

		function0<void> f = boost::bind(&TdCenterSpi::processTask, this);
		thread t(f);
		this->task_thread = &t;
	}
	TdCenterSpi::~TdCenterSpi()
	{
		if (this->m_ptdapiClr)
		{
			this->m_ptdapiClr = 0;
			gcroot<TdApiClr^> *pp = static_cast<gcroot<TdApiClr^>*>(this->m_ptdapiClr);
			delete tdClr;
		}
	}
	void TdCenterSpi::OnFrontConnected()
	{
		if (this->m_ptdapiClr !=0)
		{
			Task task = Task();
			task.task_name = ONFRONTCONNECTED;
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnFrontDisconnected(int nReason)
	{
		if (this->m_ptdapiClr !=0)
		{
			Task task = Task();
			task.task_name = ONFRONTDISCONNECTED;
			task.task_id = nReason;
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField * pRspAuthenticateField, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPAUTHENTICATE;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			if (pRspAuthenticateField)
				task.task_data = *pRspAuthenticateField;
			else
			{
				CThostFtdcRspAuthenticateField empty_data = CThostFtdcRspAuthenticateField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPUSERLOGIN;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			if (pRspUserLogin)
				task.task_data = *pRspUserLogin;
			else
			{
				CThostFtdcRspUserLoginField empty_data = CThostFtdcRspUserLoginField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspUserLogout(CThostFtdcUserLogoutField * pUserLogout, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPUSERLOGOUT;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pUserLogout)
				task.task_data = *pUserLogout;
			else
			{
				CThostFtdcUserLogoutField empty_data = CThostFtdcUserLogoutField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			if (pRspInfo)
				task.task_data = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspOrderInsert(CThostFtdcInputOrderField * pInputOrder, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPORDERINSERT;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pInputOrder)
				task.task_data = *pInputOrder;
			else
			{
				CThostFtdcInputOrderField empty_data = CThostFtdcInputOrderField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspOrderAction(CThostFtdcInputOrderActionField * pInputOrderAction, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPORDERACTION;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pInputOrderAction)
				task.task_data = *pInputOrderAction;
			else
			{
				CThostFtdcInputOrderActionField empty_data = CThostFtdcInputOrderActionField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPSETTLEMENTINFOCONFIRM;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pSettlementInfoConfirm)
				task.task_data = *pSettlementInfoConfirm;
			else
			{
				CThostFtdcSettlementInfoConfirmField empty_data = CThostFtdcSettlementInfoConfirmField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspQuoteInsert(CThostFtdcInputQuoteField * pInputQuote, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPQUOTEINSERT;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pInputQuote)
				task.task_data = *pInputQuote;
			else
			{
				CThostFtdcInputQuoteField empty_data = CThostFtdcInputQuoteField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspQuoteAction(CThostFtdcInputQuoteActionField * pInputQuoteAction, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPQUOTEACTION;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pInputQuoteAction)
				task.task_data = *pInputQuoteAction;
			else
			{
				CThostFtdcInputQuoteActionField empty_data = CThostFtdcInputQuoteActionField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField * pInvestorPosition, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPQRYINVESTORPOSITION;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pInvestorPosition)
				task.task_data = *pInvestorPosition;
			else
			{
				CThostFtdcInvestorPositionField empty_data = CThostFtdcInvestorPositionField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField * pTradingAccount, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPQRYTRADINGACCOUNT;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pTradingAccount)
				task.task_data = *pTradingAccount;
			else
			{
				CThostFtdcTradingAccountField empty_data = CThostFtdcTradingAccountField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspQryInvestor(CThostFtdcInvestorField * pInvestor, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPQRYINVESTOR;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pInvestor)
				task.task_data = *pInvestor;
			else
			{
				CThostFtdcInvestorField empty_data = CThostFtdcInvestorField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspQryInstrument(CThostFtdcInstrumentField * pInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPQRYINSTRUMENT;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pInstrument)
				task.task_data = *pInstrument;
			else
			{
				CThostFtdcInstrumentField empty_data = CThostFtdcInstrumentField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField * pSettlementInfo, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPQRYSETTLEMENTINFO;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pSettlementInfo)
				task.task_data = *pSettlementInfo;
			else
			{
				CThostFtdcSettlementInfoField empty_data = CThostFtdcSettlementInfoField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField * pInvestorPositionDetail, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPQRYINVESTORPOSITIONDETAIL;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pInvestorPositionDetail)
				task.task_data = *pInvestorPositionDetail;
			else
			{
				CThostFtdcInvestorPositionDetailField empty_data = CThostFtdcInvestorPositionDetailField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPQRYSETTLEMENTINFOCONFIRM;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pSettlementInfoConfirm)
				task.task_data = *pSettlementInfoConfirm;
			else
			{
				CThostFtdcSettlementInfoConfirmField empty_settlement = CThostFtdcSettlementInfoConfirmField();
				memset(&empty_settlement, 0, sizeof(empty_settlement));
				task.task_data = empty_settlement;
			}
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField * pInvestorPositionCombineDetail, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL;
			task.task_id = nRequestID;
			task.task_last = bIsLast;
			if (pInvestorPositionCombineDetail)
				task.task_data = *pInvestorPositionCombineDetail;
			else
			{
				CThostFtdcInvestorPositionCombineDetailField empty_data = CThostFtdcInvestorPositionCombineDetailField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRSPERROR;
			task.task_id = nRequestID;
			task.task_last = bIsLast;

			if (pRspInfo)
				task.task_error = *pRspInfo;
			else
			{
				CThostFtdcRspInfoField empty_error = CThostFtdcRspInfoField();
				memset(&empty_error, 0, sizeof(empty_error));
				task.task_error = empty_error;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRtnOrder(CThostFtdcOrderField * pOrder)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRTNORDER;
			if (pOrder)
				task.task_data = *pOrder;
			else
			{
				CThostFtdcOrderField empty_data = CThostFtdcOrderField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			this->task_queue.push(task);
		}
	}
	void TdCenterSpi::OnRtnTrade(CThostFtdcTradeField * pTrade)
	{
		if (this->m_ptdapiClr !=0 )
		{
			Task task = Task();
			task.task_name = ONRTNTRADE;
			if (pTrade)
				task.task_data = *pTrade;
			else
			{
				CThostFtdcTradeField empty_data = CThostFtdcTradeField();
				memset(&empty_data, 0, sizeof(empty_data));
				task.task_data = empty_data;
			}
			this->task_queue.push(task);
		}
	}
	/////ÈÎÎñº¯Êý///////
	void TdCenterSpi::processTask()
	{
		while (true)
		{
			Task task = this->task_queue.wait_and_pop();
			switch (task.task_name)
			{
			case ONFRONTCONNECTED:
				this->processOnFrontConnected(task);
				break;
			case ONFRONTDISCONNECTED:
				this->processOnFrontDisconnected(task);
				break;
			case ONRSPUSERLOGIN:
				this->processOnRspUserLogin(task);
				break;
			case ONRSPUSERLOGOUT:
				this->processOnRspUserLogout(task);
				break;
			case ONRSPERROR:
				this->processOnRspError(task);
				break;
			case ONRSPORDERINSERT:
				this->processOnRspOrderInsert(task);
				break;
			case ONRSPORDERACTION:
				this->processOnRspOrderAction(task);
				break;
			case ONRSPAUTHENTICATE:
				this->processOnRspAuthenticate(task);
				break;

			case ONRSPQRYINVESTORPOSITION:
				this->processOnRspQryInvestorPosition(task);
				break;
			case ONRSPQRYTRADINGACCOUNT:
				this->processOnRspQryTradingAccount(task);
				break;
			case ONRSPQRYINVESTOR:
				this->processOnRspQryInvestor(task);
				break;
			case ONRSPQRYINSTRUMENT:
				this->processOnRspQryInstrument(task);
				break;
			case ONRSPQRYSETTLEMENTINFO:
				this->processOnRspQrySettlementInfo(task);
				break;
			case ONRSPQRYINVESTORPOSITIONDETAIL:
				this->processOnRspQryInvestorPositionDetail(task);
				break;
			case ONRSPSETTLEMENTINFOCONFIRM:
				this->processOnRspQrySettlementInfoConfirm(task);
				break;
			case ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL:
				this->processOnRspQryInvestorPositionCombineDetail(task);
				break;
			case ONRTNORDER:
				this->processOnRtnOrder(task);
				break;
			case ONRTNTRADE:
				this->processOnRtnTrade(task);
				break;
			}
		}
	}
	void TdCenterSpi::processOnFrontConnected(Task task)
	{
		if (this->m_ptdapiClr !=0)
			((TdApiClr^)*tdClr)->OnFrontConnected_();
	}
	void TdCenterSpi::processOnFrontDisconnected(Task task)
	{
		if (this->m_ptdapiClr !=0)
			((TdApiClr^)*tdClr)->OnFrontDisconnected_(task.task_id);
	}
	void TdCenterSpi::processOnRspUserLogin(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{

			/////////////////////////////////////////////////////////////
			CThostFtdcRspUserLoginField data_any = any_cast<CThostFtdcRspUserLoginField>(task.task_data);
			RspUserLogin^ login = gcnew RspUserLogin();
			login->FrontID = data_any.FrontID;
			login->SessionID = data_any.SessionID;
			login->BrokerID = Marshal::PtrToStringAnsi((IntPtr)data_any.BrokerID);
			login->UserID = Marshal::PtrToStringAnsi((IntPtr)data_any.UserID);
			login->CZCETime = Marshal::PtrToStringAnsi((IntPtr)data_any.CZCETime);
			login->DCETime = Marshal::PtrToStringAnsi((IntPtr)data_any.DCETime);
			login->FFEXTime = Marshal::PtrToStringAnsi((IntPtr)data_any.FFEXTime);
			login->INETime = Marshal::PtrToStringAnsi((IntPtr)data_any.INETime);
			login->SHFETime = Marshal::PtrToStringAnsi((IntPtr)data_any.SHFETime);
			login->LoginTime = Marshal::PtrToStringAnsi((IntPtr)data_any.LoginTime);
			login->MaxOrderRef = Marshal::PtrToStringAnsi((IntPtr)data_any.MaxOrderRef);
			login->TradingDay = Marshal::PtrToStringAnsi((IntPtr)data_any.TradingDay);
			CThostFtdcRspInfoField error_any = any_cast<CThostFtdcRspInfoField>(task.task_error);
			ErrorInfo^ error = gcnew ErrorInfo();
			error->ErrorID = error_any.ErrorID;
			error->ErrorMsg = Marshal::PtrToStringAnsi((IntPtr)error_any.ErrorMsg);
			if (this->m_ptdapiClr !=0)
				((TdApiClr^)*tdClr)->OnRspUserLogin_(login, error, task.task_id, task.task_last);
		}
	}
	void TdCenterSpi::processOnRspUserLogout(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcUserLogoutField logout_any = any_cast<CThostFtdcUserLogoutField>(task.task_data);
			RspUserLogout^ logout = gcnew RspUserLogout();
			logout->BrokerID = Marshal::PtrToStringAnsi((IntPtr)logout_any.BrokerID);
			logout->UserID = Marshal::PtrToStringAnsi((IntPtr)logout_any.UserID);
			CThostFtdcRspInfoField error_any = any_cast<CThostFtdcRspInfoField>(task.task_error);
			ErrorInfo^ error = gcnew ErrorInfo();
			error->ErrorID = error_any.ErrorID;
			error->ErrorMsg = Marshal::PtrToStringAnsi((IntPtr)error_any.ErrorMsg);
			((TdApiClr^)*tdClr)->OnRspUserLogout_(logout, error, task.task_id, task.task_last);
		}
	}
	void TdCenterSpi::processOnRspAuthenticate(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcRspAuthenticateField suthenticate = any_cast<CThostFtdcRspAuthenticateField>(task.task_data);
			RspAuthenticateField^ suthen = gcnew RspAuthenticateField();
			suthen->BrokerID = Marshal::PtrToStringAnsi((IntPtr)suthenticate.BrokerID);
			suthen->UserID = Marshal::PtrToStringAnsi((IntPtr)suthenticate.UserID);
			suthen->UserProductInfo = Marshal::PtrToStringAnsi((IntPtr)suthenticate.UserProductInfo);
			CThostFtdcRspInfoField error_any = any_cast<CThostFtdcRspInfoField>(task.task_error);
			ErrorInfo^ error = gcnew ErrorInfo();
			error->ErrorID = error_any.ErrorID;
			error->ErrorMsg = Marshal::PtrToStringAnsi((IntPtr)error_any.ErrorMsg);
			((TdApiClr^)*tdClr)->OnRspAuthenticate_(suthen, error, task.task_id, task.task_last);
		}
	}
	void TdCenterSpi::processOnRspError(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcRspInfoField error_any = any_cast<CThostFtdcRspInfoField>(task.task_error);
			ErrorInfo^ error = gcnew ErrorInfo();
			error->ErrorID = error_any.ErrorID;
			error->ErrorMsg = Marshal::PtrToStringAnsi((IntPtr)error_any.ErrorMsg);
			((TdApiClr^)*tdClr)->OnRspError_(error, task.task_id, task.task_last);
		}
	}
	void TdCenterSpi::processOnRspOrderInsert(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcInputOrderField orderSend = any_cast<CThostFtdcInputOrderField>(task.task_data);
			OrderInsert^ orderInsert = gcnew OrderInsert();
			orderInsert->BrokerID = Marshal::PtrToStringAnsi((IntPtr)orderSend.BrokerID);
			orderInsert->BusinessUnit = Marshal::PtrToStringAnsi((IntPtr)orderSend.BusinessUnit);
			orderInsert->CombHedgeFlag = Marshal::PtrToStringAnsi((IntPtr)orderSend.CombHedgeFlag);
			orderInsert->CombOffsetFlag = Marshal::PtrToStringAnsi((IntPtr)orderSend.CombOffsetFlag);
			orderInsert->ContingentCondition = Marshal::PtrToStringAnsi((IntPtr)orderSend.ContingentCondition);
			orderInsert->Direction = Marshal::PtrToStringAnsi((IntPtr)orderSend.Direction);
			orderInsert->ExchangeID = Marshal::PtrToStringAnsi((IntPtr)orderSend.ExchangeID);
			orderInsert->ForceCloseReason = Marshal::PtrToStringAnsi((IntPtr)orderSend.ForceCloseReason);
			orderInsert->OrderRef = Marshal::PtrToStringAnsi((IntPtr)orderSend.OrderRef);
			orderInsert->OrderPriceType = Marshal::PtrToStringAnsi((IntPtr)orderSend.OrderPriceType);
			orderInsert->RequestID = (orderSend.RequestID);
			orderInsert->StopPrice = orderSend.StopPrice;
			orderInsert->UserForceClose = orderSend.UserForceClose;
			orderInsert->UserID = Marshal::PtrToStringAnsi((IntPtr)orderSend.UserID);
			orderInsert->VolumeCondition = Marshal::PtrToStringAnsi((IntPtr)orderSend.VolumeCondition);
			orderInsert->VolumeTotalOriginal = (orderSend.VolumeTotalOriginal);
			orderInsert->TimeCondition = Marshal::PtrToStringAnsi((IntPtr)orderSend.TimeCondition);
			CThostFtdcRspInfoField error_any = any_cast<CThostFtdcRspInfoField>(task.task_error);
			ErrorInfo^ error = gcnew ErrorInfo();
			error->ErrorID = error_any.ErrorID;
			error->ErrorMsg = Marshal::PtrToStringAnsi((IntPtr)error_any.ErrorMsg);
			((TdApiClr^)*tdClr)->OnRspOrderInsert_(orderInsert, error, task.task_id, task.task_last);
		}
	}
	void TdCenterSpi::processOnRspQrySettlementInfoConfirm(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcRspInfoField error_any = any_cast<CThostFtdcRspInfoField>(task.task_error);
			ErrorInfo^ error = gcnew ErrorInfo();
			error->ErrorID = error_any.ErrorID;
			error->ErrorMsg = Marshal::PtrToStringAnsi((IntPtr)error_any.ErrorMsg);
			CThostFtdcSettlementInfoConfirmField settlementInfoCon_any = any_cast<CThostFtdcSettlementInfoConfirmField>(task.task_data);
			RspSettlementInfoConfirm^ settlementInfoCon = gcnew RspSettlementInfoConfirm();
			settlementInfoCon->BrokerID = Marshal::PtrToStringAnsi((IntPtr)settlementInfoCon_any.BrokerID);
			settlementInfoCon->ConfirmDate = Marshal::PtrToStringAnsi((IntPtr)settlementInfoCon_any.ConfirmDate);
			settlementInfoCon->ConfirmTime = Marshal::PtrToStringAnsi((IntPtr)settlementInfoCon_any.ConfirmTime);
			settlementInfoCon->InvestorID = Marshal::PtrToStringAnsi((IntPtr)settlementInfoCon_any.InvestorID);
			((TdApiClr^)*tdClr)->OnRspQrySettlementInfoConfirm_(settlementInfoCon, error, task.task_id, task.task_last);
		}
	}
	void TdCenterSpi::processOnRspQryInvestorPositionCombineDetail(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcRspInfoField error_any = any_cast<CThostFtdcRspInfoField>(task.task_error);
			ErrorInfo^ error = gcnew ErrorInfo();
			error->ErrorID = error_any.ErrorID;
			error->ErrorMsg = Marshal::PtrToStringAnsi((IntPtr)error_any.ErrorMsg);
			CThostFtdcInvestorPositionCombineDetailField inPositionCom = any_cast<CThostFtdcInvestorPositionCombineDetailField>(task.task_data);
			RspInvestorPositionCombineDetailField^ inPositionComDetail = gcnew RspInvestorPositionCombineDetailField();
			inPositionComDetail->BrokerID = Marshal::PtrToStringAnsi((IntPtr)inPositionCom.BrokerID);
			inPositionComDetail->CombInstrumentID = Marshal::PtrToStringAnsi((IntPtr)inPositionCom.CombInstrumentID);
			inPositionComDetail->ComTradeID = Marshal::PtrToStringAnsi((IntPtr)inPositionCom.ComTradeID);
			inPositionComDetail->Direction = Marshal::PtrToStringAnsi((IntPtr)inPositionCom.Direction);
			inPositionComDetail->ExchangeID = Marshal::PtrToStringAnsi((IntPtr)inPositionCom.ExchangeID);
			inPositionComDetail->ExchMargin = (inPositionCom.ExchMargin);
			inPositionComDetail->HedgeFlag = Marshal::PtrToStringAnsi((IntPtr)inPositionCom.HedgeFlag);
			inPositionComDetail->InstrumentID = Marshal::PtrToStringAnsi((IntPtr)inPositionCom.InstrumentID);
			inPositionComDetail->InvestorID = Marshal::PtrToStringAnsi((IntPtr)inPositionCom.InvestorID);
			inPositionComDetail->LegID = (inPositionCom.LegID);
			inPositionComDetail->LegMultiple = inPositionCom.LegMultiple;
			inPositionComDetail->MarginRateByVolume = inPositionCom.MarginRateByVolume;
			inPositionComDetail->MarginRateByMoney = inPositionCom.MarginRateByMoney;
			inPositionComDetail->SettlementID = inPositionCom.SettlementID;
			inPositionComDetail->TotalAmt = inPositionCom.TotalAmt;
			inPositionComDetail->OpenDate = Marshal::PtrToStringAnsi((IntPtr)inPositionCom.OpenDate);
			inPositionComDetail->TradeGroupID = (inPositionCom.TradeGroupID);
			inPositionComDetail->TradeID = Marshal::PtrToStringAnsi((IntPtr)inPositionCom.TradeID);
			inPositionComDetail->TradingDay = Marshal::PtrToStringAnsi((IntPtr)inPositionCom.TradingDay);
			((TdApiClr^)*tdClr)->OnRspQryInvestorPositionCombineDetail_(inPositionComDetail, error, task.task_id, task.task_last);
		}
	}
	void TdCenterSpi::processOnRtnOrder(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcOrderField order = any_cast<CThostFtdcOrderField>(task.task_data);
			RtnOrderField^ rtnOrder = gcnew RtnOrderField();
			rtnOrder->ActiveTime = Marshal::PtrToStringAnsi((IntPtr)order.ActiveTime);
			rtnOrder->ActiveTraderID = Marshal::PtrToStringAnsi((IntPtr)order.ActiveTraderID);
			rtnOrder->ActiveUserID = Marshal::PtrToStringAnsi((IntPtr)order.ActiveUserID);
			rtnOrder->BranchID = Marshal::PtrToStringAnsi((IntPtr)order.BranchID);
			rtnOrder->BrokerID = Marshal::PtrToStringAnsi((IntPtr)order.BrokerID);
			rtnOrder->BrokerOrderSeq = (order.BrokerOrderSeq);
			rtnOrder->BusinessUnit = Marshal::PtrToStringAnsi((IntPtr)order.BusinessUnit);
			rtnOrder->CombHedgeFlag = Marshal::PtrToStringAnsi((IntPtr)order.CombHedgeFlag);
			rtnOrder->ClearingPartID = Marshal::PtrToStringAnsi((IntPtr)order.ClearingPartID);
			rtnOrder->CancelTime = Marshal::PtrToStringAnsi((IntPtr)order.CancelTime);
			rtnOrder->ClientID = Marshal::PtrToStringAnsi((IntPtr)order.ClientID);
			rtnOrder->CombOffsetFlag = Marshal::PtrToStringAnsi((IntPtr)order.CombOffsetFlag);
			rtnOrder->ContingentCondition = Marshal::PtrToStringAnsi((IntPtr)order.ContingentCondition);
			rtnOrder->Direction = Marshal::PtrToStringAnsi((IntPtr)order.Direction);
			rtnOrder->ExchangeID = Marshal::PtrToStringAnsi((IntPtr)order.ExchangeID);
			rtnOrder->ExchangeInstID = Marshal::PtrToStringAnsi((IntPtr)order.ExchangeInstID);
			rtnOrder->ForceCloseReason = Marshal::PtrToStringAnsi((IntPtr)order.ForceCloseReason);
			rtnOrder->FrontID = (order.FrontID);
			rtnOrder->NotifySequence = (order.NotifySequence);
			rtnOrder->InsertDate = Marshal::PtrToStringAnsi((IntPtr)order.InsertDate);
			rtnOrder->InsertTime = Marshal::PtrToStringAnsi((IntPtr)order.InsertTime);
			rtnOrder->InstallID = (order.InstallID);
			rtnOrder->InstrumentID = Marshal::PtrToStringAnsi((IntPtr)order.InstrumentID);
			rtnOrder->InvestorID = Marshal::PtrToStringAnsi((IntPtr)order.InvestorID);
			rtnOrder->MinVolume = (order.MinVolume);
			rtnOrder->LimitPrice = (order.LimitPrice);
			rtnOrder->OrderLocalID = Marshal::PtrToStringAnsi((IntPtr)order.OrderLocalID);
			rtnOrder->OrderPriceType = Marshal::PtrToStringAnsi((IntPtr)order.OrderPriceType);
			rtnOrder->OrderRef = Marshal::PtrToStringAnsi((IntPtr)order.OrderRef);
			rtnOrder->OrderSource = Marshal::PtrToStringAnsi((IntPtr)order.OrderSource);
			rtnOrder->OrderStatus = Marshal::PtrToStringAnsi((IntPtr)order.OrderStatus);
			rtnOrder->OrderSubmitStatus = Marshal::PtrToStringAnsi((IntPtr)order.OrderSubmitStatus);
			rtnOrder->OrderSysID = Marshal::PtrToStringAnsi((IntPtr)order.OrderSysID);
			rtnOrder->OrderType = Marshal::PtrToStringAnsi((IntPtr)order.OrderType);
			rtnOrder->RelativeOrderSysID = Marshal::PtrToStringAnsi((IntPtr)order.RelativeOrderSysID);
			rtnOrder->RequestID = order.RequestID;
			rtnOrder->StopPrice = order.StopPrice;
			rtnOrder->SequenceNo = order.SequenceNo;
			rtnOrder->SessionID = order.SessionID;
			rtnOrder->SettlementID = order.SettlementID;
			rtnOrder->StatusMsg = Marshal::PtrToStringAnsi((IntPtr)order.StatusMsg);
			rtnOrder->SuspendTime = Marshal::PtrToStringAnsi((IntPtr)order.SuspendTime);
			rtnOrder->UserForceClose = order.UserForceClose;
			rtnOrder->UserID = Marshal::PtrToStringAnsi((IntPtr)order.UserID);
			rtnOrder->UpdateTime = Marshal::PtrToStringAnsi((IntPtr)order.UpdateTime);
			rtnOrder->UserProductInfo = Marshal::PtrToStringAnsi((IntPtr)order.UserProductInfo);
			rtnOrder->VolumeCondition = Marshal::PtrToStringAnsi((IntPtr)order.VolumeCondition);
			rtnOrder->VolumeTotal = order.VolumeTotal;
			rtnOrder->VolumeTotalOriginal = order.VolumeTotalOriginal;
			rtnOrder->VolumeTraded = order.VolumeTraded;
			rtnOrder->ZCETotalTradedVolume = order.ZCETotalTradedVolume;
			((TdApiClr^)*tdClr)->OnRtnOrder_(rtnOrder);
		}
	}
	void TdCenterSpi::processOnRtnTrade(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcTradeField trade_any = any_cast<CThostFtdcTradeField>(task.task_data);
			RtnTradeField^ rtnTrade = gcnew RtnTradeField();
			rtnTrade->BrokerID = Marshal::PtrToStringAnsi((IntPtr)trade_any.BrokerID);
			rtnTrade->BrokerOrderSeq = (trade_any.BrokerOrderSeq);
			rtnTrade->BusinessUnit = Marshal::PtrToStringAnsi((IntPtr)trade_any.BusinessUnit);
			rtnTrade->ClearingPartID = Marshal::PtrToStringAnsi((IntPtr)trade_any.ClearingPartID);
			rtnTrade->ClientID = Marshal::PtrToStringAnsi((IntPtr)trade_any.ClientID);
			rtnTrade->Direction = Marshal::PtrToStringAnsi((IntPtr)trade_any.Direction);
			rtnTrade->ExchangeID = Marshal::PtrToStringAnsi((IntPtr)trade_any.ExchangeID);
			rtnTrade->ExchangeInstID = Marshal::PtrToStringAnsi((IntPtr)trade_any.ExchangeInstID);
			rtnTrade->HedgeFlag = Marshal::PtrToStringAnsi((IntPtr)trade_any.HedgeFlag);
			rtnTrade->InstrumentID = Marshal::PtrToStringAnsi((IntPtr)trade_any.InstrumentID);
			rtnTrade->InvestorID = Marshal::PtrToStringAnsi((IntPtr)trade_any.InvestorID);
			rtnTrade->OrderLocalID = Marshal::PtrToStringAnsi((IntPtr)trade_any.OrderLocalID);
			rtnTrade->OrderRef = Marshal::PtrToStringAnsi((IntPtr)trade_any.OrderRef);
			rtnTrade->OrderSysID = Marshal::PtrToStringAnsi((IntPtr)trade_any.OrderSysID);
			rtnTrade->OffsetFlag = Marshal::PtrToStringAnsi((IntPtr)trade_any.OffsetFlag);
			rtnTrade->PriceSource = Marshal::PtrToStringAnsi((IntPtr)trade_any.PriceSource);
			rtnTrade->Price = (trade_any.Price);
			rtnTrade->ParticipantID = Marshal::PtrToStringAnsi((IntPtr)trade_any.ParticipantID);
			rtnTrade->TradeType = Marshal::PtrToStringAnsi((IntPtr)trade_any.TradeType);
			rtnTrade->TradeDate = Marshal::PtrToStringAnsi((IntPtr)trade_any.TradeDate);
			rtnTrade->TradeID = Marshal::PtrToStringAnsi((IntPtr)trade_any.TradeID);
			rtnTrade->TraderID = Marshal::PtrToStringAnsi((IntPtr)trade_any.TraderID);
			rtnTrade->TradeSource = Marshal::PtrToStringAnsi((IntPtr)trade_any.TradeSource);
			rtnTrade->TradeTime = Marshal::PtrToStringAnsi((IntPtr)trade_any.TradeTime);
			rtnTrade->TradingDay = Marshal::PtrToStringAnsi((IntPtr)trade_any.TradingDay);
			rtnTrade->TradingRole = Marshal::PtrToStringAnsi((IntPtr)trade_any.TradingRole);
			((TdApiClr^)*tdClr)->OnRtnTrade_(rtnTrade);
		}
	}
	void TdCenterSpi::processOnRspOrderAction(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcInputOrderActionField action = any_cast<CThostFtdcInputOrderActionField>(task.task_data);
			OrderAction^ orderAction = gcnew OrderAction();
			orderAction->ActionFlag = Marshal::PtrToStringAnsi((IntPtr)action.ActionFlag);
			orderAction->BrokerID = Marshal::PtrToStringAnsi((IntPtr)action.BrokerID);
			orderAction->ExchangeID = Marshal::PtrToStringAnsi((IntPtr)action.ExchangeID);
			orderAction->FrontID = (action.FrontID);
			orderAction->InstrumentID = Marshal::PtrToStringAnsi((IntPtr)action.InstrumentID);
			orderAction->InvestorID = Marshal::PtrToStringAnsi((IntPtr)action.InvestorID);
			orderAction->LimitPrice = action.LimitPrice;
			orderAction->OrderActionRef = (action.OrderActionRef);
			orderAction->OrderRef = Marshal::PtrToStringAnsi((IntPtr)action.OrderRef);
			orderAction->OrderSysID = Marshal::PtrToStringAnsi((IntPtr)action.OrderSysID);
			orderAction->SessionID = (action.SessionID);
			orderAction->UserID = Marshal::PtrToStringAnsi((IntPtr)action.UserID);
			CThostFtdcRspInfoField error_any = any_cast<CThostFtdcRspInfoField>(task.task_error);
			ErrorInfo^ error = gcnew ErrorInfo();
			error->ErrorID = error_any.ErrorID;
			error->ErrorMsg = Marshal::PtrToStringAnsi((IntPtr)error_any.ErrorMsg);
			((TdApiClr^)*tdClr)->OnRspOrderAction_(orderAction, error, task.task_id, task.task_last);
		}
	}
	void TdCenterSpi::processOnRspQryInvestorPosition(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcRspInfoField error_any = any_cast<CThostFtdcRspInfoField>(task.task_error);
			ErrorInfo^ error = gcnew ErrorInfo();
			error->ErrorID = error_any.ErrorID;
			error->ErrorMsg = Marshal::PtrToStringAnsi((IntPtr)error_any.ErrorMsg);
			CThostFtdcInvestorPositionField investorPosition_any = any_cast<CThostFtdcInvestorPositionField>(task.task_data);
			RspInvestorPositionField^ investorPosition = gcnew RspInvestorPositionField();
			investorPosition->AbandonFrozen = (investorPosition_any.AbandonFrozen);
			investorPosition->BrokerID = Marshal::PtrToStringAnsi((IntPtr)investorPosition_any.BrokerID);
			investorPosition->CashIn = investorPosition_any.CashIn;
			investorPosition->CloseAmount = (investorPosition_any.CloseAmount);
			investorPosition->CloseProfit = investorPosition_any.CloseProfit;
			investorPosition->CloseProfitByDate = investorPosition_any.CloseProfitByDate;
			investorPosition->CloseVolume = investorPosition_any.CloseVolume;
			investorPosition->CombLongFrozen = investorPosition_any.CombLongFrozen;
			investorPosition->CombPosition = investorPosition_any.CombPosition;
			investorPosition->CombShortFrozen = investorPosition_any.CombShortFrozen;
			investorPosition->Commission = investorPosition_any.Commission;
			investorPosition->ExchangeID = Marshal::PtrToStringAnsi((IntPtr)investorPosition_any.ExchangeID);
			investorPosition->ExchangeMargin = investorPosition_any.ExchangeMargin;
			investorPosition->FrozenCash = investorPosition_any.FrozenCash;
			investorPosition->FrozenCommission = investorPosition_any.FrozenCommission;
			investorPosition->FrozenMargin = investorPosition_any.FrozenMargin;
			investorPosition->LongFrozen = investorPosition_any.LongFrozen;
			investorPosition->LongFrozenAmount = investorPosition_any.LongFrozenAmount;
			investorPosition->MarginRateByVolume = investorPosition_any.MarginRateByVolume;
			investorPosition->MarginRateByMoney = investorPosition_any.MarginRateByMoney;
			investorPosition->OpenAmount = investorPosition_any.OpenAmount;
			investorPosition->OpenCost = investorPosition_any.OpenCost;
			investorPosition->OpenVolume = investorPosition_any.OpenVolume;
			investorPosition->PosiDirection = Marshal::PtrToStringAnsi((IntPtr)investorPosition_any.PosiDirection);
			investorPosition->Position = investorPosition_any.PosiDirection;
			investorPosition->PositionCost = investorPosition_any.PositionCost;
			investorPosition->PositionDate = Marshal::PtrToStringAnsi((IntPtr)investorPosition_any.PositionDate);
			investorPosition->PositionProfit = investorPosition_any.PositionProfit;
			investorPosition->PreMargin = investorPosition_any.PreMargin;
			investorPosition->PreSettlementPrice = investorPosition_any.PreSettlementPrice;
			investorPosition->SettlementPrice = investorPosition_any.SettlementPrice;
			investorPosition->SettlementID = Marshal::PtrToStringAnsi((IntPtr)investorPosition_any.SettlementID);
			investorPosition->UseMargin = investorPosition_any.UseMargin;
			investorPosition->YdPosition = investorPosition_any.YdPosition;
			investorPosition->TodayPosition = investorPosition_any.TodayPosition;
			investorPosition->TradingDay = Marshal::PtrToStringAnsi((IntPtr)investorPosition_any.TradingDay);

			((TdApiClr^)*tdClr)->OnRspQryInvestorPosition_(investorPosition, error, task.task_id, task.task_last);
		}
	}
	void TdCenterSpi::processOnRspQryTradingAccount(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcRspInfoField error_any = any_cast<CThostFtdcRspInfoField>(task.task_error);
			ErrorInfo^ error = gcnew ErrorInfo();
			error->ErrorID = error_any.ErrorID;
			error->ErrorMsg = Marshal::PtrToStringAnsi((IntPtr)error_any.ErrorMsg);
			CThostFtdcTradingAccountField account_any = any_cast<CThostFtdcTradingAccountField>(task.task_data);
			RspTradingAccountField^ account = gcnew RspTradingAccountField();
			account->AccountID = Marshal::PtrToStringAnsi((IntPtr)account_any.AccountID);
			account->Available = (account_any.Available);
			account->Balance = (account_any.Balance);
			account->BizType = Marshal::PtrToStringAnsi((IntPtr)account_any.BizType);
			account->BrokerID = Marshal::PtrToStringAnsi((IntPtr)account_any.BrokerID);
			account->FundMortgageAvailable = (account_any.FundMortgageAvailable);
			account->CloseProfit = (account_any.CloseProfit);
			account->CashIn = account_any.CashIn;
			account->Commission = account_any.Commission;
			account->Credit = account_any.Credit;
			account->CurrencyID = Marshal::PtrToStringAnsi((IntPtr)account_any.CurrencyID);
			account->CurrMargin = account_any.CurrMargin;
			account->ExchangeDeliveryMargin = (account_any.ExchangeDeliveryMargin);
			account->ExchangeMargin = (account_any.ExchangeMargin);
			account->DeliveryMargin = account_any.DeliveryMargin;
			account->Deposit = account_any.Deposit;
			account->FrozenCash = account_any.FrozenCash;
			account->FrozenCommission = account_any.FrozenCommission;
			account->FrozenMargin = account_any.FrozenMargin;
			account->FundMortgageAvailable = account_any.FundMortgageAvailable;
			account->FundMortgageIn = account_any.FundMortgageIn;
			account->FundMortgageOut = account_any.FundMortgageOut;
			account->MortgageableFund = account_any.MortgageableFund;
			account->Mortgage = account_any.Mortgage;
			account->PreFundMortgageIn = account_any.PreFundMortgageIn;
			account->PreFundMortgageOut = account_any.PreFundMortgageOut;
			account->PositionProfit = account_any.PositionProfit;
			account->PreBalance = account_any.PreBalance;
			account->PreCredit = account_any.PreCredit;
			account->PreDeposit = account_any.PreDeposit;
			account->PreMargin = account_any.PreMargin;
			account->PreMortgage = account_any.PreMortgage;
			account->SpecProductCloseProfit = account_any.SpecProductCloseProfit;
			account->Reserve = account_any.Reserve;
			account->ReserveBalance = account_any.ReserveBalance;
			account->SettlementID = Marshal::PtrToStringAnsi((IntPtr)account_any.SettlementID);
			account->SpecProductCommission = account_any.SpecProductCommission;
			account->SpecProductExchangeMargin = account_any.SpecProductExchangeMargin;
			account->SpecProductFrozenCommission = account_any.SpecProductFrozenCommission;
			account->SpecProductFrozenMargin = account_any.SpecProductFrozenMargin;
			account->SpecProductMargin = account_any.SpecProductMargin;
			account->SpecProductPositionProfit = account_any.SpecProductPositionProfit;
			account->SpecProductPositionProfitByAlg = account_any.SpecProductPositionProfitByAlg;
			account->TradingDay = Marshal::PtrToStringAnsi((IntPtr)account_any.TradingDay);
			account->Withdraw = (account_any.Withdraw);
			account->WithdrawQuota = (account_any.WithdrawQuota);
			((TdApiClr^)*tdClr)->OnRspQryTradingAccount_(account, error, task.task_id, task.task_last);
		}
	}
	void TdCenterSpi::processOnRspQryInvestor(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcRspInfoField error_any = any_cast<CThostFtdcRspInfoField>(task.task_error);
			ErrorInfo^ error = gcnew ErrorInfo();
			error->ErrorID = error_any.ErrorID;
			error->ErrorMsg = Marshal::PtrToStringAnsi((IntPtr)error_any.ErrorMsg);
			CThostFtdcInvestorField investor_any = any_cast<CThostFtdcInvestorField>(task.task_data);
			RspInvestorField^ investor = gcnew RspInvestorField();
			investor->Address = Marshal::PtrToStringAnsi((IntPtr)investor_any.Address);
			investor->BrokerID = Marshal::PtrToStringAnsi((IntPtr)investor_any.BrokerID);
			investor->CommModelID = Marshal::PtrToStringAnsi((IntPtr)investor_any.CommModelID);
			investor->IdentifiedCardNo = Marshal::PtrToStringAnsi((IntPtr)investor_any.IdentifiedCardNo);
			investor->IdentifiedCardType = Marshal::PtrToStringAnsi((IntPtr)investor_any.IdentifiedCardType);
			investor->InvestorGroupID = Marshal::PtrToStringAnsi((IntPtr)investor_any.InvestorGroupID);
			investor->InvestorID = Marshal::PtrToStringAnsi((IntPtr)investor_any.InvestorID);
			investor->InvestorName = Marshal::PtrToStringAnsi((IntPtr)investor_any.InvestorName);
			investor->IsActive = investor_any.IsActive;
			investor->MarginModelID = Marshal::PtrToStringAnsi((IntPtr)investor_any.MarginModelID);
			investor->Mobile = Marshal::PtrToStringAnsi((IntPtr)investor_any.Mobile);
			investor->OpenDate = Marshal::PtrToStringAnsi((IntPtr)investor_any.OpenDate);
			investor->Telephone = Marshal::PtrToStringAnsi((IntPtr)investor_any.Telephone);
			((TdApiClr^)*tdClr)->OnRspQryInvestor_(investor, error, task.task_id, task.task_last);
		}
	}
	void TdCenterSpi::processOnRspQryInstrument(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcInstrumentField instrumentID = any_cast<CThostFtdcInstrumentField>(task.task_data);
			RspInstrumentField^ instrument = gcnew RspInstrumentField();
			instrument->InstrumentID = Marshal::PtrToStringAnsi((IntPtr)instrumentID.InstrumentID);
			instrument->CombinationType = Marshal::PtrToStringAnsi((IntPtr)instrumentID.CombinationType);
			instrument->CreateDate = Marshal::PtrToStringAnsi((IntPtr)instrumentID.ExchangeID);
			instrument->DeliveryMonth = instrumentID.DeliveryMonth;
			instrument->DeliveryYear = instrumentID.DeliveryYear;
			instrument->EndDelivDate = Marshal::PtrToStringAnsi((IntPtr)instrumentID.EndDelivDate);
			instrument->ExchangeID = Marshal::PtrToStringAnsi((IntPtr)instrumentID.ExchangeID);
			instrument->ExchangeInstID = Marshal::PtrToStringAnsi((IntPtr)instrumentID.ExchangeInstID);
			instrument->ExpireDate = Marshal::PtrToStringAnsi((IntPtr)instrumentID.ExpireDate);
			instrument->InstLifePhase = Marshal::PtrToStringAnsi((IntPtr)instrumentID.InstLifePhase);
			instrument->InstrumentCode = Marshal::PtrToStringAnsi((IntPtr)instrumentID.InstrumentCode);
			instrument->InstrumentID = Marshal::PtrToStringAnsi((IntPtr)instrumentID.InstrumentID);
			instrument->InstrumentName = Marshal::PtrToStringAnsi((IntPtr)instrumentID.InstrumentName);
			instrument->MaxMarginSideAlgorithm = Marshal::PtrToStringAnsi((IntPtr)instrumentID.MaxMarginSideAlgorithm);
			instrument->MaxLimitOrderVolume = (instrumentID.MaxLimitOrderVolume);
			instrument->LongMarginRatio = (instrumentID.LongMarginRatio);
			instrument->MaxMarketOrderVolume = instrumentID.MaxMarketOrderVolume;
			instrument->MinBuyVolume = (instrumentID.MinBuyVolume);
			instrument->MinLimitOrderVolume = instrumentID.MinLimitOrderVolume;
			instrument->MinMarketOrderVolume = instrumentID.MinMarketOrderVolume;
			instrument->MinSellVolume = instrumentID.MinSellVolume;
			instrument->ShortMarginRatio = instrumentID.ShortMarginRatio;
			instrument->StartDelivDate = Marshal::PtrToStringAnsi((IntPtr)instrumentID.StartDelivDate);
			instrument->StrikePrice = instrumentID.StrikePrice;
			instrument->UnderlyingInstrID = Marshal::PtrToStringAnsi((IntPtr)instrumentID.UnderlyingInstrID);
			instrument->UnderlyingMultiple = (instrumentID.UnderlyingMultiple);
			instrument->VolumeMultiple = instrumentID.VolumeMultiple;
			CThostFtdcRspInfoField error_any = any_cast<CThostFtdcRspInfoField>(task.task_error);
			ErrorInfo^ error = gcnew ErrorInfo();
			error->ErrorID = error_any.ErrorID;
			error->ErrorMsg = Marshal::PtrToStringAnsi((IntPtr)error_any.ErrorMsg);
			((TdApiClr^)*tdClr)->OnRspQryInstrument_(instrument, error, task.task_id, task.task_last);
		}
	}
	void TdCenterSpi::processOnRspQrySettlementInfo(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcRspInfoField error_any = any_cast<CThostFtdcRspInfoField>(task.task_error);
			ErrorInfo^ error = gcnew ErrorInfo();
			error->ErrorID = error_any.ErrorID;
			error->ErrorMsg = Marshal::PtrToStringAnsi((IntPtr)error_any.ErrorMsg);
			CThostFtdcSettlementInfoField settlement_any = any_cast<CThostFtdcSettlementInfoField>(task.task_data);
			RspSettlementInfoField^ settlement = gcnew RspSettlementInfoField();
			settlement->BrokerID = Marshal::PtrToStringAnsi((IntPtr)settlement_any.BrokerID);
			settlement->Content = Marshal::PtrToStringAnsi((IntPtr)settlement_any.Content);
			settlement->InvestorID = Marshal::PtrToStringAnsi((IntPtr)settlement_any.InvestorID);
			settlement->SettlementID = (settlement_any.SettlementID);
			settlement->SequenceNo = (settlement_any.SequenceNo);
			((TdApiClr^)*tdClr)->OnRspQrySettlementInfo_(settlement, error, task.task_id, task.task_last);
		}
	}
	void TdCenterSpi::processOnRspQryInvestorPositionDetail(Task task)
	{
		if (this->m_ptdapiClr !=0)
		{
			CThostFtdcRspInfoField error_any = any_cast<CThostFtdcRspInfoField>(task.task_error);
			ErrorInfo^ error = gcnew ErrorInfo();
			error->ErrorID = error_any.ErrorID;
			error->ErrorMsg = Marshal::PtrToStringAnsi((IntPtr)error_any.ErrorMsg);
			CThostFtdcInvestorPositionDetailField inPositionDetail_any = any_cast<CThostFtdcInvestorPositionDetailField>(task.task_error);
			RspInvestorPositionDelailField^ inPositionDelail = gcnew RspInvestorPositionDelailField();
			inPositionDelail->BrokerID = Marshal::PtrToStringAnsi((IntPtr)inPositionDetail_any.BrokerID);
			inPositionDelail->CloseAmount = inPositionDetail_any.CloseAmount;
			inPositionDelail->CloseProfitByDate = inPositionDetail_any.CloseProfitByDate;
			inPositionDelail->CloseProfitByTrade = inPositionDetail_any.CloseProfitByTrade;
			inPositionDelail->CloseVolume = inPositionDetail_any.CloseVolume;
			inPositionDelail->Direction = Marshal::PtrToStringAnsi((IntPtr)inPositionDetail_any.Direction);
			inPositionDelail->ExchangeID = Marshal::PtrToStringAnsi((IntPtr)inPositionDetail_any.ExchangeID);
			inPositionDelail->ExchMargin = inPositionDetail_any.ExchMargin;
			inPositionDelail->HedgeFlag = Marshal::PtrToStringAnsi((IntPtr)inPositionDetail_any.HedgeFlag);
			inPositionDelail->InstrumentID = Marshal::PtrToStringAnsi((IntPtr)inPositionDetail_any.InstrumentID);
			inPositionDelail->InvestorID = Marshal::PtrToStringAnsi((IntPtr)inPositionDetail_any.InvestorID);
			inPositionDelail->LastSettlementPrice = inPositionDetail_any.LastSettlementPrice;
			inPositionDelail->MarginRateByVolume = inPositionDetail_any.MarginRateByVolume;
			inPositionDelail->Margin = inPositionDetail_any.Margin;
			inPositionDelail->MarginRateByMoney = inPositionDetail_any.MarginRateByMoney;
			inPositionDelail->OpenDate = Marshal::PtrToStringAnsi((IntPtr)inPositionDetail_any.OpenDate);
			inPositionDelail->OpenPrice = inPositionDetail_any.OpenPrice;
			inPositionDelail->PositionProfitByDate = inPositionDetail_any.PositionProfitByDate;
			inPositionDelail->PositionProfitByTrade = inPositionDetail_any.PositionProfitByTrade;
			inPositionDelail->SettlementPrice = inPositionDetail_any.SettlementPrice;
			inPositionDelail->SettlementID = inPositionDetail_any.SettlementID;
			inPositionDelail->TradeID = Marshal::PtrToStringAnsi((IntPtr)inPositionDetail_any.TradeID);
			inPositionDelail->TradeType = Marshal::PtrToStringAnsi((IntPtr)inPositionDetail_any.TradeType);
			inPositionDelail->TradingDay = Marshal::PtrToStringAnsi((IntPtr)inPositionDetail_any.TradingDay);
			((TdApiClr^)*tdClr)->OnRspQryInvestorPositionDetail_(inPositionDelail, error, task.task_id, task.task_last);
		}
	}
}
