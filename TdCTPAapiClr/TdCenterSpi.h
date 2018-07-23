#pragma once
#include "TdApiClr.h"
#include<queue>
#include<boost/any.hpp>        //任务队列的任务实现
#include<boost/bind.hpp>      //任务队列的线程功能
#include<boost/thread.hpp>   //任务队列的线程功能
#include<gcroot.h>

using namespace boost;

//常量
#define ONFRONTCONNECTED 1
#define ONFRONTDISCONNECTED 2
#define ONHEARTBEATWARNING 3
#define ONRSPAUTHENTICATE 4
#define ONRSPUSERLOGIN 5
#define ONRSPUSERLOGOUT 6
#define ONRSPUSERPASSWORDUPDATE 7
#define ONRSPTRADINGACCOUNTPASSWORDUPDATE 8
#define ONRSPORDERINSERT 9
#define ONRSPPARKEDORDERINSERT 10
#define ONRSPPARKEDORDERACTION 11
#define ONRSPORDERACTION 12
#define ONRSPQUERYMAXORDERVOLUME 13
#define ONRSPSETTLEMENTINFOCONFIRM 14
#define ONRSPREMOVEPARKEDORDER 15
#define ONRSPREMOVEPARKEDORDERACTION 16
#define ONRSPEXECORDERINSERT 17
#define ONRSPEXECORDERACTION 18
#define ONRSPFORQUOTEINSERT 19
#define ONRSPQUOTEINSERT 20
#define ONRSPQUOTEACTION 21
#define ONRSPLOCKINSERT 22
#define ONRSPCOMBACTIONINSERT 23
#define ONRSPQRYORDER 24
#define ONRSPQRYTRADE 25
#define ONRSPQRYINVESTORPOSITION 26
#define ONRSPQRYTRADINGACCOUNT 27
#define ONRSPQRYINVESTOR 28
#define ONRSPQRYTRADINGCODE 29
#define ONRSPQRYINSTRUMENTMARGINRATE 30
#define ONRSPQRYINSTRUMENTCOMMISSIONRATE 31
#define ONRSPQRYEXCHANGE 32
#define ONRSPQRYPRODUCT 33
#define ONRSPQRYINSTRUMENT 34
#define ONRSPQRYDEPTHMARKETDATA 35
#define ONRSPQRYSETTLEMENTINFO 36
#define ONRSPQRYTRANSFERBANK 37
#define ONRSPQRYINVESTORPOSITIONDETAIL 38
#define ONRSPQRYNOTICE 39
#define ONRSPQRYSETTLEMENTINFOCONFIRM 40
#define ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL 41
#define ONRSPQRYCFMMCTRADINGACCOUNTKEY 42
#define ONRSPQRYEWARRANTOFFSET 43
#define ONRSPQRYINVESTORPRODUCTGROUPMARGIN 44
#define ONRSPQRYEXCHANGEMARGINRATE 45
#define ONRSPQRYEXCHANGEMARGINRATEADJUST 46
#define ONRSPQRYEXCHANGERATE 47
#define ONRSPQRYSECAGENTACIDMAP 48
#define ONRSPQRYPRODUCTEXCHRATE 49
#define ONRSPQRYPRODUCTGROUP 50
#define ONRSPQRYOPTIONINSTRTRADECOST 51
#define ONRSPQRYOPTIONINSTRCOMMRATE 52
#define ONRSPQRYEXECORDER 53
#define ONRSPQRYFORQUOTE 54
#define ONRSPQRYQUOTE 55
#define ONRSPQRYLOCK 56
#define ONRSPQRYLOCKPOSITION 57
#define ONRSPQRYINVESTORLEVEL 58
#define ONRSPQRYEXECFREEZE 59
#define ONRSPQRYCOMBINSTRUMENTGUARD 60
#define ONRSPQRYCOMBACTION 61
#define ONRSPQRYTRANSFERSERIAL 62
#define ONRSPQRYACCOUNTREGISTER 63
#define ONRSPERROR 64
#define ONRTNORDER 65
#define ONRTNTRADE 66
#define ONERRRTNORDERINSERT 67
#define ONERRRTNORDERACTION 68
#define ONRTNINSTRUMENTSTATUS 69
#define ONRTNTRADINGNOTICE 70
#define ONRTNERRORCONDITIONALORDER 71
#define ONRTNEXECORDER 72
#define ONERRRTNEXECORDERINSERT 73
#define ONERRRTNEXECORDERACTION 74
#define ONERRRTNFORQUOTEINSERT 75
#define ONRTNQUOTE 76
#define ONERRRTNQUOTEINSERT 77
#define ONERRRTNQUOTEACTION 78
#define ONRTNFORQUOTERSP 79
#define ONRTNCFMMCTRADINGACCOUNTTOKEN 80
#define ONRTNLOCK 81
#define ONERRRTNLOCKINSERT 82
#define ONRTNCOMBACTION 83
#define ONERRRTNCOMBACTIONINSERT 84
#define ONRSPQRYCONTRACTBANK 85
#define ONRSPQRYPARKEDORDER 86
#define ONRSPQRYPARKEDORDERACTION 87
#define ONRSPQRYTRADINGNOTICE 88
#define ONRSPQRYBROKERTRADINGPARAMS 89
#define ONRSPQRYBROKERTRADINGALGOS 90
#define ONRSPQUERYCFMMCTRADINGACCOUNTTOKEN 91
#define ONRTNFROMBANKTOFUTUREBYBANK 92
#define ONRTNFROMFUTURETOBANKBYBANK 93
#define ONRTNREPEALFROMBANKTOFUTUREBYBANK 94
#define ONRTNREPEALFROMFUTURETOBANKBYBANK 95
#define ONRTNFROMBANKTOFUTUREBYFUTURE 96
#define ONRTNFROMFUTURETOBANKBYFUTURE 97
#define ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL 98
#define ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL 99
#define ONRTNQUERYBANKBALANCEBYFUTURE 100
#define ONERRRTNBANKTOFUTUREBYFUTURE 101
#define ONERRRTNFUTURETOBANKBYFUTURE 102
#define ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL 103
#define ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL 104
#define ONERRRTNQUERYBANKBALANCEBYFUTURE 105
#define ONRTNREPEALFROMBANKTOFUTUREBYFUTURE 106
#define ONRTNREPEALFROMFUTURETOBANKBYFUTURE 107
#define ONRSPFROMBANKTOFUTUREBYFUTURE 108
#define ONRSPFROMFUTURETOBANKBYFUTURE 109
#define ONRSPQUERYBANKACCOUNTMONEYBYFUTURE 110
#define ONRTNOPENACCOUNTBYBANK 111
#define ONRTNCANCELACCOUNTBYBANK 112
#define ONRTNCHANGEACCOUNTBYBANK 113
namespace TdCTP
{
	public struct Task
	{
		int task_name;
		any task_data;
		any task_error;
		int task_id;
		bool task_last;
	};
	///线程安全的队列
	template<typename Data>

	class ConcurrentQueue
	{
	private:
		std::queue<Data> the_queue;							//标准库队列
		mutable mutex the_mutex;							//boost互斥锁
		condition_variable the_condition_variable;			//boost条件变量

	public:

		//存入新的任务
		void push(Data const& data)
		{
			mutex::scoped_lock lock(the_mutex);				//获取互斥锁
			the_queue.push(data);							//向队列中存入数据
			lock.unlock();									//释放锁
			the_condition_variable.notify_one();			//通知正在阻塞等待的线程
		}

		//检查队列是否为空
		bool empty() const
		{
			mutex::scoped_lock lock(the_mutex);
			return the_queue.empty();
		}

		//取出
		Data wait_and_pop()
		{
			mutex::scoped_lock lock(the_mutex);

			while (the_queue.empty())						//当队列为空时
			{
				the_condition_variable.wait(lock);			//等待条件变量通知
			}

			Data popped_value = the_queue.front();			//获取队列中的最后一个任务
			the_queue.pop();								//删除该任务
			return popped_value;							//返回该任务
		}

	};
	public class TdCenterSpi :public CThostFtdcTraderSpi
	{
	private:
		void* m_ptdapiClr;
		ConcurrentQueue<Task> task_queue;
		thread* task_thread;

	public:
		TdCenterSpi(TdApiClr^ clr);
		~TdCenterSpi();
		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		virtual void OnFrontConnected();
		///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
		///@param nReason 错误原因
		///        0x1001 网络读失败
		///        0x1002 网络写失败
		///        0x2001 接收心跳超时
		///        0x2002 发送心跳失败
		///        0x2003 收到错误报文
		virtual void OnFrontDisconnected(int nReason);
		///客户端认证响应
		virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///登录请求响应
		virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///登出请求响应
		virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///报单录入请求响应
		virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///报单操作请求响应
		virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///投资者结算结果确认响应
		virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///报价录入请求响应
		virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///报价操作请求响应
		virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询投资者持仓响应
		virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询资金账户响应
		virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询投资者响应
		virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询合约响应
		virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询投资者结算结果响应
		virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询投资者持仓明细响应
		virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询结算信息确认响应
		virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询投资者持仓明细响应
		virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///错误应答
		virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///报单通知
		virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);
		///成交通知
		virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);


		///任务函数列表
		void processTask();
		void processOnFrontConnected(Task task);
		void processOnFrontDisconnected(Task task);
		void processOnRspUserLogin(Task task);
		void processOnRspUserLogout(Task task);
		void processOnRspAuthenticate(Task task);///客户端认证回报
		void processOnRspError(Task task);
		void processOnRspOrderInsert(Task task);///报单错误回报
		void processOnRspOrderAction(Task task);///撤单错误回报
		void processOnRspQryInvestorPosition(Task task); ///查询投资者持仓回报
		void processOnRspQryTradingAccount(Task task);///查询资金帐号回报
		void processOnRspQryInvestor(Task task); ///查询投资者回报
		void processOnRspQryInstrument(Task task);///查询合约回报
		void processOnRspQrySettlementInfo(Task task);///查询结算回报
		void processOnRspQryInvestorPositionDetail(Task task);///查询持仓明细回报
		void processOnRspQrySettlementInfoConfirm(Task task);///查询结算信息确认回报
		void processOnRspQryInvestorPositionCombineDetail(Task task);///查询持仓明细回报
		void processOnRtnOrder(Task task);
		void processOnRtnTrade(Task task);
	};
}

