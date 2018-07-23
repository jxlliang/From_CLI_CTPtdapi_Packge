#pragma once

#include "stdafx.h"
#include"ThostFtdcTraderApi.h"
#include<string>
#include<typeinfo.h>
#include<msclr/marshal.h>
#include<msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Threading;
using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics;
using namespace System::Text;
using namespace System::IO;
///using namespace msclr::interop;  //msclr::interop用来实现托管类型和本地类型的转化
#pragma comment (lib,"thosttraderapi.lib")
namespace TdCTP
{
	///错误回报信息
	public ref struct ErrorInfo
	{
		///错误代码
		int ErrorID;
		///错误信息 //为表示String是引用类型，所以后面加了一个^ 
		String^ ErrorMsg; //^表示句柄:指向托管资源,可以被垃圾收集器回收而不需要手动释放。
	};
	///用户登录应答
	public ref struct RspUserLogin
	{
		///交易日
		String^	TradingDay;
		///登录成功时间
		String^	LoginTime;
		///经纪公司代码
		String^ BrokerID;
		///用户代码
		String^	UserID;
		///交易系统名称
		String^	SystemName;
		///前置编号
		int	FrontID;
		///会话编号
		int	SessionID;
		///最大报单引用
		String^	MaxOrderRef;
		///上期所时间
		String^	SHFETime;
		///大商所时间
		String^	DCETime;
		///郑商所时间
		String^	CZCETime;
		///中金所时间
		String^	FFEXTime;
		///能源中心时间
		String^	INETime;
	};
	///用户登出请求
	public ref struct RspUserLogout
	{
		///经纪公司代码
		String^	BrokerID;
		///用户代码
		String^	UserID;
	};
	///报单录入请求[OderInsert]
	public ref struct OrderInsert
	{
		///经纪公司代码
		String^	BrokerID;
		///投资者代码
		String^	InvestorID;
		///合约代码
		String^	InstrumentID;
		///报单引用
		String^	OrderRef;
		///用户代码
		String^	UserID;
		///报单价格条件
		String^	OrderPriceType;
		///买卖方向
		String^	Direction;
		///组合开平标志
		String^	CombOffsetFlag;
		///组合投机套保标志
		String^	CombHedgeFlag;
		///价格
		double	LimitPrice;
		///数量
		int	VolumeTotalOriginal;
		///有效期类型
		String^	TimeCondition;
		///GTD日期
		String^	GTDDate;
		///成交量类型
		String^	VolumeCondition;
		///最小成交量
		int	MinVolume;
		///触发条件
		String^	ContingentCondition;
		///止损价
		double	StopPrice;
		///强平原因
		String^	ForceCloseReason;
		///自动挂起标志
		int	IsAutoSuspend;
		///业务单元
		String^	BusinessUnit;
		///请求编号
		int	RequestID;
		///用户强评标志
		int	UserForceClose;
		///互换单标志
		int	IsSwapOrder;
		///交易所代码
		String^	ExchangeID;
	};
	///撤单操作
	public ref struct OrderAction
	{
		///经纪公司代码
		String^	BrokerID;
		///投资者代码
		String^	InvestorID;
		///报单操作引用
		int	OrderActionRef;
		///报单引用
		String^	OrderRef;
		///请求编号
		int	RequestID;
		///前置编号
		int	FrontID;
		///会话编号
		int	SessionID;
		///交易所代码
		String^	ExchangeID;
		///报单编号
		String^	OrderSysID;
		///操作标志
		String^	ActionFlag;
		///价格
		double	LimitPrice;
		///数量变化
		int	VolumeChange;
		///用户代码
		String^	UserID;
		///合约代码
		String^	InstrumentID;
	};
	///投资者结算结果确认信息
	public ref struct RspSettlementInfoConfirm
	{
		///经纪公司代码
		String^	BrokerID;
		///投资者代码
		String^	InvestorID;
		///确认日期
		String^	ConfirmDate;
		///确认时间
		String^	ConfirmTime;
	};
	///输入的报价
	public ref struct RspInputQuoteField
	{
		///经纪公司代码
		String^	BrokerID;
		///投资者代码
		String^	InvestorID;
		///合约代码
		String^	InstrumentID;
		///报价引用
		String^	QuoteRef;
		///用户代码
		String^	UserID;
		///卖价格
		double	AskPrice;
		///买价格
		double	BidPrice;
		///卖数量
		int	AskVolume;
		///买数量
		int	BidVolume;
		///请求编号
		int	RequestID;
		///业务单元
		String^	BusinessUnit;
		///卖开平标志
		String^	AskOffsetFlag;
		///买开平标志
		String^	BidOffsetFlag;
		///卖投机套保标志
		String^	AskHedgeFlag;
		///买投机套保标志
		String^	BidHedgeFlag;
		///衍生卖报单引用
		String^	AskOrderRef;
		///衍生买报单引用
		String^	BidOrderRef;
		///应价编号
		String^	ForQuoteSysID;
		///交易所代码
		String^	ExchangeID;
	};
	///报价操作
	public ref struct RspQuoteActionField
	{
		///经纪公司代码
		String^	BrokerID;
		///投资者代码
		String^	InvestorID;
		///报价操作引用
		int	QuoteActionRef;
		///报价引用
		String^	QuoteRef;
		///请求编号
		int	RequestID;
		///前置编号
		int	FrontID;
		///会话编号
		int	SessionID;
		///交易所代码
		String^	ExchangeID;
		///报价操作编号
		String^	QuoteSysID;
		///操作标志
		String^	ActionFlag;
		///操作日期
		String^	ActionDate;
		///操作时间
		String^	ActionTime;
		///交易所交易员代码
		String^	TraderID;
		///安装编号
		int	InstallID;
		///本地报价编号
		String^	QuoteLocalID;
		///操作本地编号
		String^	ActionLocalID;
		///会员代码
		String^	ParticipantID;
		///客户代码
		String^	ClientID;
		///业务单元
		String^	BusinessUnit;
		///报单操作状态
		String^	OrderActionStatus;
		///用户代码
		String^	UserID;
		///状态信息
		String^	StatusMsg;
		///合约代码
		String^	InstrumentID;
		///营业部编号
		String^	BranchID;
	};
	///请求查询投资者持仓响应
	public ref struct RspInvestorPositionField
	{
		///合约代码
		String^	InstrumentID;
		///经纪公司代码
		String^	BrokerID;
		///投资者代码
		String^	InvestorID;
		///持仓多空方向
		String^	PosiDirection;
		///投机套保标志
		String^	HedgeFlag;
		///持仓日期
		String^	PositionDate;
		///上日持仓
		int	YdPosition;
		///今日持仓
		int	Position;
		///多头冻结
		int	LongFrozen;
		///空头冻结
		int	ShortFrozen;
		///开仓冻结金额
		double	LongFrozenAmount;
		///开仓冻结金额
		double	ShortFrozenAmount;
		///开仓量
		int	OpenVolume;
		///平仓量
		int	CloseVolume;
		///开仓金额
		double	OpenAmount;
		///平仓金额
		double	CloseAmount;
		///持仓成本
		double	PositionCost;
		///上次占用的保证金
		double	PreMargin;
		///占用的保证金
		double	UseMargin;
		///冻结的保证金
		double	FrozenMargin;
		///冻结的资金
		double	FrozenCash;
		///冻结的手续费
		double	FrozenCommission;
		///资金差额
		double	CashIn;
		///手续费
		double	Commission;
		///平仓盈亏
		double	CloseProfit;
		///持仓盈亏
		double	PositionProfit;
		///上次结算价
		double	PreSettlementPrice;
		///本次结算价
		double	SettlementPrice;
		///交易日
		String^	TradingDay;
		///结算编号
		String^	SettlementID;
		///开仓成本
		double	OpenCost;
		///交易所保证金
		double	ExchangeMargin;
		///组合成交形成的持仓
		int	CombPosition;
		///组合多头冻结
		int	CombLongFrozen;
		///组合空头冻结
		int	CombShortFrozen;
		///逐日盯市平仓盈亏
		double	CloseProfitByDate;
		///逐笔对冲平仓盈亏
		double	CloseProfitByTrade;
		///今日持仓
		int	TodayPosition;
		///保证金率
		double	MarginRateByMoney;
		///保证金率(按手数)
		double	MarginRateByVolume;
		///执行冻结
		int	StrikeFrozen;
		///执行冻结金额
		int	StrikeFrozenAmount;
		///放弃执行冻结
		int	AbandonFrozen;
		///交易所代码
		String^	ExchangeID;
		///执行冻结的昨仓
		int	YdStrikeFrozen;
	};
	///资金账户查询
	public ref struct RspTradingAccountField
	{
		///经纪公司代码
		String^	BrokerID;
		///投资者帐号
		String^	AccountID;
		///上次质押金额
		double	PreMortgage;
		///上次信用额度
		double	PreCredit;
		///上次存款额
		double	PreDeposit;
		///上次结算准备金
		double	PreBalance;
		///上次占用的保证金
		double	PreMargin;
		///利息基数
		double	InterestBase;
		///利息收入
		double	Interest;
		///入金金额
		double	Deposit;
		///出金金额
		double	Withdraw;
		///冻结的保证金
		double	FrozenMargin;
		///冻结的资金
		double	FrozenCash;
		///冻结的手续费
		double	FrozenCommission;
		///当前保证金总额
		double	CurrMargin;
		///资金差额
		double	CashIn;
		///手续费
		double	Commission;
		///平仓盈亏
		double	CloseProfit;
		///持仓盈亏
		double	PositionProfit;
		///期货结算准备金
		double	Balance;
		///可用资金
		double	Available;
		///可取资金
		double	WithdrawQuota;
		///基本准备金
		double	Reserve;
		///交易日
		String^	TradingDay;
		///结算编号
		String^	SettlementID;
		///信用额度
		double	Credit;
		///质押金额
		double	Mortgage;
		///交易所保证金
		double	ExchangeMargin;
		///投资者交割保证金
		double	DeliveryMargin;
		///交易所交割保证金
		double	ExchangeDeliveryMargin;
		///保底期货结算准备金
		double	ReserveBalance;
		///币种代码
		String^	CurrencyID;
		///上次货币质入金额
		double	PreFundMortgageIn;
		///上次货币质出金额
		double	PreFundMortgageOut;
		///货币质入金额
		double	FundMortgageIn;
		///货币质出金额
		double	FundMortgageOut;
		///货币质押余额
		double	FundMortgageAvailable;
		///可质押货币金额
		double	MortgageableFund;
		///特殊产品占用保证金
		double	SpecProductMargin;
		///特殊产品冻结保证金
		double	SpecProductFrozenMargin;
		///特殊产品手续费
		double	SpecProductCommission;
		///特殊产品冻结手续费
		double	SpecProductFrozenCommission;
		///特殊产品持仓盈亏
		double	SpecProductPositionProfit;
		///特殊产品平仓盈亏
		double	SpecProductCloseProfit;
		///根据持仓盈亏算法计算的特殊产品持仓盈亏
		double	SpecProductPositionProfitByAlg;
		///特殊产品交易所保证金
		double	SpecProductExchangeMargin;
		///业务类型
		String^	BizType;
	};
	///投资者查询
	public ref struct RspInvestorField
	{
		///投资者代码
		String^	InvestorID;
		///经纪公司代码
		String^	BrokerID;
		///投资者分组代码
		String^	InvestorGroupID;
		///投资者名称
		String^	InvestorName;
		///证件类型
		String^	IdentifiedCardType;
		///证件号码
		String^	IdentifiedCardNo;
		///是否活跃
		int	IsActive;
		///联系电话
		String^	Telephone;
		///通讯地址
		String^	Address;
		///开户日期
		String^	OpenDate;
		///手机
		String^	Mobile;
		///手续费率模板代码
		String^	CommModelID;
		///保证金率模板代码
		String^	MarginModelID;
	};
	///投资者结算结果
	public ref struct RspSettlementInfoField
	{
		///交易日
		String^	TradingDay;
		///结算编号
		int	SettlementID;
		///经纪公司代码
		String^	BrokerID;
		///投资者代码
		String^	InvestorID;
		///序号
		int	SequenceNo;
		///消息正文
		String^	Content;
	};
	///投资者持仓明细
	public ref struct RspInvestorPositionDelailField
	{
		///合约代码
		String^	InstrumentID;
		///经纪公司代码
		String^	BrokerID;
		///投资者代码
		String^	InvestorID;
		///投机套保标志
		String^	HedgeFlag;
		///买卖
		String^	Direction;
		///开仓日期
		String^	OpenDate;
		///成交编号
		String^	TradeID;
		///数量
		int	Volume;
		///开仓价
		double	OpenPrice;
		///交易日
		String^	TradingDay;
		///结算编号
		int	SettlementID;
		///成交类型
		String^	TradeType;
		///组合合约代码
		String^	CombInstrumentID;
		///交易所代码
		String^	ExchangeID;
		///逐日盯市平仓盈亏
		double	CloseProfitByDate;
		///逐笔对冲平仓盈亏
		double	CloseProfitByTrade;
		///逐日盯市持仓盈亏
		double	PositionProfitByDate;
		///逐笔对冲持仓盈亏
		double	PositionProfitByTrade;
		///投资者保证金
		double	Margin;
		///交易所保证金
		double	ExchMargin;
		///保证金率
		double	MarginRateByMoney;
		///保证金率(按手数)
		double	MarginRateByVolume;
		///昨结算价
		double	LastSettlementPrice;
		///结算价
		double	SettlementPrice;
		///平仓量
		int	CloseVolume;
		///平仓金额
		double	CloseAmount;
	};
	///投资者组合持仓明细
	public ref struct RspInvestorPositionCombineDetailField
	{
		///交易日
		String^	TradingDay;
		///开仓日期
		String^	OpenDate;
		///交易所代码
		String^	ExchangeID;
		///结算编号
		int	SettlementID;
		///经纪公司代码
		String^	BrokerID;
		///投资者代码
		String^	InvestorID;
		///组合编号
		String^	ComTradeID;
		///撮合编号
		String^	TradeID;
		///合约代码
		String^	InstrumentID;
		///投机套保标志
		String^	HedgeFlag;
		///买卖
		String^	Direction;
		///持仓量
		int	TotalAmt;
		///投资者保证金
		double	Margin;
		///交易所保证金
		double	ExchMargin;
		///保证金率
		double	MarginRateByMoney;
		///保证金率(按手数)
		double	MarginRateByVolume;
		///单腿编号
		int	LegID;
		///单腿乘数
		int	LegMultiple;
		///组合持仓合约编码
		String^	CombInstrumentID;
		///成交组号
		int	TradeGroupID;
	};
	///客户端认证响应
	public ref struct RspAuthenticateField
	{
		///经纪公司代码
		String^	BrokerID;
		///用户代码
		String^	UserID;
		///用户端产品信息
		String^	UserProductInfo;
	};
	///请求查询合约响应
	public ref struct RspInstrumentField
	{
		///合约代码
		String^	InstrumentID;
		///交易所代码
		String^	ExchangeID;
		///合约名称
		String^	InstrumentName;
		///合约在交易所的代码
		String^	ExchangeInstID;
		///产品代码
		String^	ProductID;
		///产品类型
		String^	ProductClass;
		///交割年份
		int	DeliveryYear;
		///交割月
		int	DeliveryMonth;
		///市价单最大下单量
		int	MaxMarketOrderVolume;
		///市价单最小下单量
		int	MinMarketOrderVolume;
		///限价单最大下单量
		int	MaxLimitOrderVolume;
		///限价单最小下单量
		int	MinLimitOrderVolume;
		///合约数量乘数
		int	VolumeMultiple;
		///最小变动价位
		double	PriceTick;
		///创建日
		String^	CreateDate;
		///上市日
		String^	OpenDate;
		///到期日
		String^	ExpireDate;
		///开始交割日
		String^	StartDelivDate;
		///结束交割日
		String^	EndDelivDate;
		///合约生命周期状态
		String^	InstLifePhase;
		///当前是否交易
		int	IsTrading;
		///持仓类型
		String^	PositionType;
		///持仓日期类型
		String^	PositionDateType;
		///多头保证金率
		double	LongMarginRatio;
		///空头保证金率
		double	ShortMarginRatio;
		///是否使用大额单边保证金算法
		String^	MaxMarginSideAlgorithm;
		///基础商品代码
		String^	UnderlyingInstrID;
		///执行价
		double	StrikePrice;
		///期权类型
		String^	OptionsType;
		///合约基础商品乘数
		double	UnderlyingMultiple;
		///组合类型
		String^	CombinationType;
		///最小买下单单位
		int	MinBuyVolume;
		///最小卖下单单位
		int	MinSellVolume;
		///合约标识码
		String^	InstrumentCode;
	};
	///RtnOrder(委托回报)
	public ref struct RtnOrderField
	{
		///经纪公司代码
		String^	BrokerID;
		///投资者代码
		String^	InvestorID;
		///合约代码
		String^	InstrumentID;
		///报单引用
		String^	OrderRef;
		///用户代码
		String^	UserID;
		///报单价格条件
		String^	OrderPriceType;
		///买卖方向
		String^	Direction;
		///组合开平标志
		String^	CombOffsetFlag;
		///组合投机套保标志
		String^	CombHedgeFlag;
		///价格
		double	LimitPrice;
		///数量
		int	VolumeTotalOriginal;
		///有效期类型
		String^	TimeCondition;
		///GTD日期
		String^	GTDDate;
		///成交量类型
		String^	VolumeCondition;
		///最小成交量
		int	MinVolume;
		///触发条件
		String^	ContingentCondition;
		///止损价
		double	StopPrice;
		///强平原因
		String^	ForceCloseReason;
		///自动挂起标志
		int	IsAutoSuspend;
		///业务单元
		String^	BusinessUnit;
		///请求编号
		int	RequestID;
		///本地报单编号
		String^	OrderLocalID;
		///交易所代码
		String^	ExchangeID;
		///会员代码
		String^	ParticipantID;
		///客户代码
		String^	ClientID;
		///合约在交易所的代码
		String^	ExchangeInstID;
		///交易所交易员代码
		String^	TraderID;
		///安装编号
		int	InstallID;
		///报单提交状态
		String^	OrderSubmitStatus;
		///报单提示序号
		int	NotifySequence;
		///交易日
		String^	TradingDay;
		///结算编号
		int	SettlementID;
		///报单编号
		String^	OrderSysID;
		///报单来源
		String^	OrderSource;
		///报单状态
		String^	OrderStatus;
		///报单类型
		String^	OrderType;
		///今成交数量
		int	VolumeTraded;
		///剩余数量
		int	VolumeTotal;
		///报单日期
		String^	InsertDate;
		///委托时间
		String^	InsertTime;
		///激活时间
		String^	ActiveTime;
		///挂起时间
		String^	SuspendTime;
		///最后修改时间
		String^	UpdateTime;
		///撤销时间
		String^	CancelTime;
		///最后修改交易所交易员代码
		String^	ActiveTraderID;
		///结算会员编号
		String^	ClearingPartID;
		///序号
		int	SequenceNo;
		///前置编号
		int	FrontID;
		///会话编号
		int	SessionID;
		///用户端产品信息
		String^	UserProductInfo;
		///状态信息
		String^	StatusMsg;
		///用户强评标志
		int	UserForceClose;
		///操作用户代码
		String^	ActiveUserID;
		///经纪公司报单编号
		int	BrokerOrderSeq;
		///相关报单
		String^	RelativeOrderSysID;
		///郑商所成交数量
		int	ZCETotalTradedVolume;
		///互换单标志
		int	IsSwapOrder;
		///营业部编号
		String^	BranchID;
	};
	///RtnTrade(成交回报)
	public ref struct RtnTradeField
	{
		///经纪公司代码
		String^	BrokerID;
		///投资者代码
		String^	InvestorID;
		///合约代码
		String^	InstrumentID;
		///报单引用
		String^	OrderRef;
		///用户代码
		String^	UserID;
		///交易所代码
		String^	ExchangeID;
		///成交编号
		String^	TradeID;
		///买卖方向
		String^	Direction;
		///报单编号
		String^	OrderSysID;
		///会员代码
		String^	ParticipantID;
		///客户代码
		String^	ClientID;
		///交易角色
		String^	TradingRole;
		///合约在交易所的代码
		String^	ExchangeInstID;
		///开平标志
		String^	OffsetFlag;
		///投机套保标志
		String^	HedgeFlag;
		///价格
		double	Price;
		///数量
		int	Volume;
		///成交时期
		String^	TradeDate;
		///成交时间
		String^	TradeTime;
		///成交类型
		String^	TradeType;
		///成交价来源
		String^	PriceSource;
		///交易所交易员代码
		String^	TraderID;
		///本地报单编号
		String^	OrderLocalID;
		///结算会员编号
		String^	ClearingPartID;
		///业务单元
		String^	BusinessUnit;
		///序号
		int	SequenceNo;
		///交易日
		String^	TradingDay;
		///结算编号
		int	SettlementID;
		///经纪公司报单编号
		int	BrokerOrderSeq;
		///成交来源
		String^	TradeSource;
	};

	//////////声明委托=>委托的签名与Spi中的回调函数一致
	public delegate void OnFrontConnectedDelegate();
	public delegate void OnFrontDisconnectedDelegate(int n);
	public delegate void OnAuthenticateDelegate(RspAuthenticateField^ authen, ErrorInfo ^ pRspInfo, int nRequestID, bool bIsLast);
	public delegate void OnRspUserLoginDelegate(RspUserLogin^ pRspUserLogin, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
	public delegate void OnRspUserLogoutDelegate(RspUserLogout^ pUserLogout, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
	public delegate void OnRspErrorDelegate(ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
	public delegate void OnRspOrderInsertDelegate(OrderInsert^ orderInsert, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
	public delegate void OnRspOrderActionDelegate(OrderAction^ orderAction, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
	public delegate void OnRspSettlementInfoConfirmDelegate(RspSettlementInfoConfirm^ settelment, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
	public delegate void OnRspQuoteInsertDelegate(RspInputQuoteField^ inputQuote, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
	public delegate void OnRspQuoteActionDelegate(RspQuoteActionField^ action, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
	public delegate void OnRspQryInvestorPositionDelegate(RspInvestorPositionField^ investorPosition, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
	public delegate void OnRspQryTradingAccountDelegate(RspTradingAccountField^ tradingAccount, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
	public delegate void OnRspQryInvestorDelegate(RspInvestorField^ investor, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
	public delegate void OnRspQryInstrumentDelegate(RspInstrumentField^ code, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
	public delegate void OnRspQrySettlementInfoDelegate(RspSettlementInfoField^ settlementInfo, ErrorInfo^ pRspInfo, int pResquesID, bool bIsLast);
	public delegate void OnRspQryInvestorPositionDetailDelegate(RspInvestorPositionDelailField^ investorPositionDelail, ErrorInfo^ pRspInfo, int pRequestID, bool bIsLast);
	public delegate void OnRspQrySettlementInfoConfirmDelegate(RspSettlementInfoConfirm^ settelment, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
	public delegate void OnRspQryInvestorPositionCombineDetailDelegate(RspInvestorPositionCombineDetailField^ investorPositionCombineDetail, ErrorInfo^ pRequestID, int nRequestID, bool bIsLast);
	public delegate void OnRtnOrderDelegate(RtnOrderField^ rtnOrder);
	public delegate void OnRtnTradeDelegate(RtnTradeField^ rtnTrade);

	class TdCenterSpi;
	public ref class TdApiClr
	{
	private:
		static TdApiClr^ clrTdExsample; ///本类的私有实例
		CThostFtdcTraderApi* api;
		TdCenterSpi* tdcspi;
	public:
		TdApiClr();
		~TdApiClr();
		OnFrontConnectedDelegate^ onFrontConnectDelegate;
		OnFrontDisconnectedDelegate^ onFrontDisConnectDelegate;
		OnAuthenticateDelegate^ onAuthenDelegate;
		OnRspUserLoginDelegate^ onRspLoginDelegate;
		OnRspUserLogoutDelegate^ onRspLogoutDelegate;
		OnRspErrorDelegate^ onErrorDelegate;
		OnRspOrderInsertDelegate^ onRspOrderInsertDelegate;
		OnRspOrderActionDelegate^ onOrderActionDelegate;
		OnRspQuoteInsertDelegate^ onQuoteInsertDelegate;
		OnRspQuoteActionDelegate^ onQuoteActionDelegate;
		OnRspQryInvestorPositionDelegate^ onRspQryInvestorPositionDelegate;
		OnRspQryTradingAccountDelegate^ onRspQryTradingAccountDelegate;
		OnRspQryInvestorDelegate^ onRspQryInvestorDelegate;
		OnRspQryInstrumentDelegate^ onRspQryInstrumentDelegate;
		OnRspSettlementInfoConfirmDelegate^ onRspSettlementInfoConfirmDelegate;
		OnRspQrySettlementInfoDelegate^ onRspQrySettlementInfoDelegate;
		OnRspQryInvestorPositionDetailDelegate^ onRspQryInvestorPositionDetailDelegate;
		OnRspQryInvestorPositionCombineDetailDelegate^ onRspQryInvestorPositionCombineDetailDelegate;
		OnRspQrySettlementInfoConfirmDelegate^ onRspQrySettlementInfoConfirmDelegate;
		OnRtnOrderDelegate^ onRtnOrderDelegate;
		OnRtnTradeDelegate^ onRtnTradeDelegate;

		void SetOnFrontConnectedDelegate(OnFrontConnectedDelegate^ connected);
		void SetOnFrontDisconnectedDelegate(OnFrontDisconnectedDelegate^ disConnected);
		void SetOnRspUserLoginDelegate(OnRspUserLoginDelegate^ login);
		void SetOnRspUserLogoutDelegate(OnRspUserLogoutDelegate^ logout);
		void SetAuthenDelegate(OnAuthenticateDelegate^ authen);
		void SetOnRspErrorDelegate(OnRspErrorDelegate^ error);
		void SetOnRspOrderInsertDelegate(OnRspOrderInsertDelegate^ orderInsert);
		void SetOnRspOrderActionDelegate(OnRspOrderActionDelegate^ orderAction);
		void SetOnRspQuoteInsertDelegate(OnRspQuoteInsertDelegate^ quoteInsert);
		void SetOnRspQuoteActionDelegate(OnRspQuoteActionDelegate^ quoteaction);
		void SetOnRspQryInvestorPositionDelegate(OnRspQryInvestorPositionDelegate^ investorPosition);
		void SetOnRspQryTradingAccountDelegate(OnRspQryTradingAccountDelegate^ tradingAccount);
		void SetOnRspQryInvestorDelegate(OnRspQryInvestorDelegate^ investor);
		void SetOnRspQryInstrumentDelegate(OnRspQryInstrumentDelegate^ instrument);
		void SetOnRspSettlementInfoConfirmDelegate(OnRspSettlementInfoConfirmDelegate^ settlementInfoConfirm);
		void SetOnRspQrySettlementInfoDelegate(OnRspQrySettlementInfoDelegate^ settlementInfo);
		void SetOnRspQryInvestorPositionDetailDelegate(OnRspQryInvestorPositionDetailDelegate^ investorPositionDetail);
		void SetOnRspQryInvestorPositionCombineDetailDelegate(OnRspQryInvestorPositionCombineDetailDelegate^ onInvestorPositionCombineDetail);
		void SetOnRspQrySettlementInfoConfirmDelegate(OnRspQrySettlementInfoConfirmDelegate^ onRspQrySettlementInfoConfirm);
		void SetOnRtnOrderDelegate(OnRtnOrderDelegate^ rtnOrder);
		void SetOnRtnTradeDelegate(OnRtnTradeDelegate^ rtnTrade);

		///投资者结算结果确认信息
		ref struct ReqSettlementInfoConfirmField
		{
			///经纪公司代码
			String^	BrokerID;
			///投资者代码
			String^	InvestorID;
		};
		///查询投资者持仓
		ref struct ReqInvestorPositionField
		{
			///经纪公司代码
			String^	BrokerID;
			///投资者代码
			String^	InvestorID;
			///合约代码
			String^	InstrumentID;
			///交易所代码
			String^	ExchangeID;
		};
		///查询资金账户
		ref struct ReqTradingAccountField
		{
			///经纪公司代码
			String^	BrokerID;
			///投资者代码
			String^	InvestorID;
			///币种代码
			String^	CurrencyID;
			///业务类型
			String^	BizType;
		};
		///查询投资者
		ref struct ReqInvestorField
		{
			///经纪公司代码
			String^	BrokerID;
			///投资者代码
			String^	InvestorID;
		};
		///查询投资者结算结果
		ref struct ReqSettlementInfoField
		{
			///经纪公司代码
			String^	BrokerID;
			///投资者代码
			String^	InvestorID;
			///交易日
			String^	TradingDay;
		};
		///查询投资者持仓明显
		ref struct ReqInvestorPositionDetailField
		{
			///经纪公司代码
			String^	BrokerID;
			///投资者代码
			String^	InvestorID;
			///合约代码
			String^	InstrumentID;
			///交易所代码
			String^	ExchangeID;
		};
		///查询组合持仓明细
		ref struct ReqInvestorPositionCombineDetailField
		{
			///经纪公司代码
			String^	BrokerID;
			///投资者代码
			String^	InvestorID;
			///组合持仓合约编码
			String^	CombInstrumentID;
		};
		///用户登录请求
		ref struct ReqUserLoginField
		{
			///交易日
			String^ TradingDay;
			///经纪公司代码
			String^ BrokerID;
			///用户代码
			String^ UserID;
			///密码
			String^ Password;
			///用户端产品信息
			String^ UserProductInfo;
			///接口端产品信息
			String^ InterfaceProductInfo;
			///协议信息
			String^ ProtocolInfo;
			///Mac地址
			String^ MacAddress;
			///动态密码
			String^ OneTimePassword;
			///终端IP地址
			String^ ClientIPAddress;
		};
		///用户登出请求
		ref struct ReqUserLogoutField
		{
			///经纪公司代码
			String^	BrokerID;
			///用户代码
			String^	UserID;
		};
		///请求查询合约
		ref struct ReqInstrumentField
		{
			///合约代码
			String^	InstrumentID;
			///交易所代码
			String^	ExchangeID;
			///合约在交易所的代码
			String^	ExchangeInstID;
			///产品代码
			String^	ProductID;
		};
		///客户端认证
		ref struct ReqAuthenticateField
		{
			///经纪公司代码
			String^	BrokerID;
			///用户代码
			String^	UserID;
			///用户端产品信息
			String^	UserProductInfo;
			///认证码
			String^	AuthCode;
		};
		///请求查询合约
		ref struct ReqInstrument
		{
			///合约代码
			String^	InstrumentID;
			///交易所代码
			String^	ExchangeID;
			///合约在交易所的代码
			String^	ExchangeInstID;
			///产品代码
			String^	ProductID;
		};

		static TdApiClr^ GetInstance();  ///声明一个返回值是本类对象的方法GetInstance

										 ///回调函数
		void OnFrontConnected_();
		void OnFrontDisconnected_(int nReason);
		void OnRspAuthenticate_(RspAuthenticateField^ pRspAuthenticateField, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspUserLogin_(RspUserLogin^ pRspUserLogin, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspUserLogout_(RspUserLogout^ pUserLogout, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspOrderInsert_(OrderInsert^ pInputOrder, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspOrderAction_(OrderAction^ pInputOrderAction, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspSettlementInfoConfirm_(RspSettlementInfoConfirm^ pSettlementInfoConfirm, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspQuoteInsert_(RspInputQuoteField^ pInputQuote, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspQuoteAction_(RspQuoteActionField^ pInputQuoteAction, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspQryInvestorPosition_(RspInvestorPositionField^ pInvestorPosition, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspQryTradingAccount_(RspTradingAccountField^ pTradingAccount, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspQryInvestor_(RspInvestorField^ pInvestor, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspQryInstrument_(RspInstrumentField^ pInstrument, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspQrySettlementInfo_(RspSettlementInfoField^ pSettlementInfo, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspQryInvestorPositionDetail_(RspInvestorPositionDelailField^ pInvestorPositionDetail, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspQrySettlementInfoConfirm_(RspSettlementInfoConfirm^ pSettlementInfoConfirm, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspQryInvestorPositionCombineDetail_(RspInvestorPositionCombineDetailField^ pInvestorPositionCombineDetail, ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRspError_(ErrorInfo^ pRspInfo, int nRequestID, bool bIsLast);
		void OnRtnOrder_(RtnOrderField^ pOrder);
		void OnRtnTrade_(RtnTradeField^ pTrade);

		//////////////////主动函数///////////////////////////
		///创建TraderApi
		void CreateTdApi_(char *pszFlowPath);
		const char* GetApiVersion_();
		void Init_();
		void Release_();
		int Join_();
		const char* GetTradingDay_();
		///注册前置机网络地址
		///@param pszFrontAddress：前置机网络地址。
		///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
		///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
		void RegisterFront_(char *pszFrontAddress);
		///注册名字服务器网络地址
		///@param pszNsAddress：名字服务器网络地址。
		///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
		///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
		///@remark RegisterNameServer优先于RegisterFront
		void RegisterNameServer_(char *pszNsAddress);
		/////注册名字服务器用户信息
		/////@param pFensUserInfo：用户信息。
		// void RegisterFensUserInfo(Login pFensUserInfo);
		///订阅私有流。
		///@param nResumeType 私有流重传方式  
		///        THOST_TERT_RESTART:从本交易日开始重传
		///        THOST_TERT_RESUME:从上次收到的续传
		///        THOST_TERT_QUICK:只传送登录后私有流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
		void SubscribePrivateTopic_();
		///订阅公共流。
		///@param nResumeType 公共流重传方式  
		///        THOST_TERT_RESTART:从本交易日开始重传
		///        THOST_TERT_RESUME:从上次收到的续传
		///        THOST_TERT_QUICK:只传送登录后公共流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
		void SubscribePublicTopic_();
		///客户端认证请求
		int ReqAuthenticate_(ReqAuthenticateField^ pReqAuthenticateField, int nRequestID);
		///用户登录请求
		int ReqUserLogin_(ReqUserLoginField^ pReqUserLoginField, int nRequestID);
		///登出请求
		int ReqUserLogout_(ReqUserLogoutField^ pUserLogout, int nRequestID);
		///报单录入请求
		int ReqOrderInsert_(OrderInsert^ pInputOrder, int nRequestID);
		///报单操作请求
		int ReqOrderAction_(OrderAction^ pInputOrderAction, int nRequestID);
		///投资者结算结果确认
		int ReqSettlementInfoConfirm_(ReqSettlementInfoConfirmField^ pSettlementInfoConfirm, int nRequestID);
		///请求查询投资者持仓
		int ReqQryInvestorPosition_(ReqInvestorPositionField^ pQryInvestorPosition, int nRequestID);
		///请求查询资金账户
		int ReqQryTradingAccount_(ReqTradingAccountField^ pQryTradingAccount, int nRequestID);
		///请求查询投资者
		int ReqQryInvestor_(ReqInvestorField^ pQryInvestor, int nRequestID);
		///请求查询合约
		int ReqQryInstrument_(ReqInstrumentField^ pQryInstrument, int nRequestID);
		///请求查询投资者结算结果
		int ReqQrySettlementInfo_(ReqSettlementInfoField^ pQrySettlementInfo, int nRequestID);
		///请求查询投资者持仓明细
		int ReqQryInvestorPositionDetail_(ReqInvestorPositionDetailField^ pQryInvestorPositionDetail, int nRequestID);
		///请求查询结算信息确认
		int ReqQrySettlementInfoConfirm_(ReqSettlementInfoConfirmField^ pQrySettlementInfoConfirm, int nRequestID);
		///请求查询投资者持仓明细
		int ReqQryInvestorPositionCombineDetail_(ReqInvestorPositionCombineDetailField^ pQryInvestorPositionCombineDetail, int nRequestID);
		//////////////////主动函数///////////////////////////

		///杂项
		void CreateCenter();
	};

}