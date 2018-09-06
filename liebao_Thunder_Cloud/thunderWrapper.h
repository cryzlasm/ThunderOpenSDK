#ifndef __GTC_THUNDERWRAPPER__
#define __GTC_THUNDERWRAPPER__
#pragma once
#include "AC/sysupport.h"

namespace gtc {
	//////////////////////////////////////////////////////////////////////////////////////////
	// 2016-3-4		kp007	迅雷头文件
#pragma pack(push, 1)
	struct DownTaskParam
	{
		DownTaskParam()
		{
			memset(this, 0, sizeof(DownTaskParam));
			nReserved1		 = 5;
			bReserved			 = FALSE;
			DisableAutoRename	 = FALSE;
			IsOnlyOriginal		 = FALSE;
			IsResume			 = TRUE;
		}
		int nReserved;
		wchar_t szTaskUrl[2084];          // 任务URL
		wchar_t szRefUrl[2084];           // 引用页
		wchar_t szCookies[4096];          // 浏览器cookie
		wchar_t szFilename[MAX_PATH];     // 下载保存文件名.
		wchar_t szReserved0[MAX_PATH];
		wchar_t szSavePath[MAX_PATH];     // 文件保存目录
		HWND  hReserved;
		BOOL bReserved; 
		wchar_t szReserved1[64];
		wchar_t szReserved2[64];
		BOOL IsOnlyOriginal;            // 是否只从原始地址下载
		UINT nReserved1;
		BOOL DisableAutoRename;         // 禁止智能命名
		BOOL IsResume;                  // 是否用续传
		DWORD reserved[2048];
	};
	enum  DOWN_TASK_STATUS
	{
		NOITEM = 0,
		TSC_ERROR,
		TSC_PAUSE,
		TSC_DOWNLOAD,
		TSC_COMPLETE,
		TSC_STARTPENDING,
		TSC_STOPPENDING
	};
	enum TASK_ERROR_TYPE
	{
		TASK_ERROR_UNKNOWN	   =			0x00,   // 未知错误
		TASK_ERROR_DISK_CREATE =			0x01,   // 创建文件失败
		TASK_ERROR_DISK_WRITE =				0x02,   // 写文件失败
		TASK_ERROR_DISK_READ =				0x03,   // 读文件失败
		TASK_ERROR_DISK_RENAME =			0x04,   // 重命名失败
		TASK_ERROR_DISK_PIECEHASH =			0x05,   // 文件片校验失败
		TASK_ERROR_DISK_FILEHASH =			0x06,   // 文件全文校验失败
		TASK_ERROR_DISK_DELETE =			0x07,   // 删除文件失败失败
		TASK_ERROR_DOWN_INVALID =			0x10,   // 无效的DOWN地址
		TASK_ERROR_PROXY_AUTH_TYPE_UNKOWN = 0x20,   // 代理类型未知
		TASK_ERROR_PROXY_AUTH_TYPE_FAILED = 0x21,   // 代理认证失败
		TASK_ERROR_HTTPMGR_NOT_IP =			0x30,   // http下载中无ip可用
		TASK_ERROR_TIMEOUT =				0x40,   // 任务超时
		TASK_ERROR_CANCEL =					0x41,   // 任务取消
		TASK_ERROR_TP_CRASHED=              0x42,   // MINITP崩溃
		TASK_ERROR_ID_INVALID =             0x43,   // TaskId 非法
	};
	struct DownTaskInfo
	{
		DownTaskInfo()
		{
			memset(this, 0, sizeof(DownTaskInfo));
			stat		= TSC_PAUSE;
			fail_code	= TASK_ERROR_UNKNOWN;
			fPercent = 0;
			bIsOriginUsable = false;
			fHashPercent = 0;
		}
		DOWN_TASK_STATUS	stat;
		TASK_ERROR_TYPE		fail_code;
		wchar_t		szFilename[MAX_PATH];
		wchar_t		szReserved0[MAX_PATH];
		__int64     nTotalSize;         // 该任务总大小(字节)
		__int64     nTotalDownload;     // 下载有效字节数(可能存在回退的情况)
		float		fPercent;           // 下载进度
		int			nReserved0;
		int			nSrcTotal;          // 总资源数
		int			nSrcUsing;          // 可用资源数
		int			nReserved1;
		int			nReserved2;
		int			nReserved3;
		int			nReserved4;
		__int64     nReserved5;
		__int64		nDonationP2P;       // p2p贡献字节数
		__int64		nReserved6;
		__int64		nDonationOrgin;		// 原始资源共享字节数
		__int64		nDonationP2S;		// 镜像资源共享字节数
		__int64		nReserved7;
		__int64     nReserved8;
		int			nSpeed;             // 即时速度(字节/秒)
		int			nSpeedP2S;          // 即时速度(字节/秒)
		int			nSpeedP2P;          // 即时速度(字节/秒)
		bool		bIsOriginUsable;    // 原始资源是否有效
		float		fHashPercent;       // 现不提供该值
		int			IsCreatingFile;     // 是否正在创建文件
		DWORD		reserved[64];
	};
	enum DOWN_PROXY_TYPE
	{
		PROXY_TYPE_IE	 = 0,
		PROXY_TYPE_HTTP  = 1,
		PROXY_TYPE_SOCK4 = 2,
		PROXY_TYPE_SOCK5 = 3,
		PROXY_TYPE_FTP   = 4,
		PROXY_TYPE_UNKOWN  = 255,
	};
	enum DOWN_PROXY_AUTH_TYPE
	{
		PROXY_AUTH_NONE =0,
		PROXY_AUTH_AUTO,
		PROXY_AUTH_BASE64,
		PROXY_AUTH_NTLM,
		PROXY_AUTH_DEGEST,
		PROXY_AUTH_UNKOWN,
	};
	struct DOWN_PROXY_INFO
	{
		BOOL		bIEProxy;
		BOOL		bProxy;
		DOWN_PROXY_TYPE	stPType;
		DOWN_PROXY_AUTH_TYPE	stAType;
		wchar_t		szHost[2048];
		INT32		nPort;
		wchar_t		szUser[50];
		wchar_t		szPwd[50];
		wchar_t		szDomain[2048];
	};
	struct WSAPROTOCOL_INFOW;


#pragma pack(pop)

	//////////////////////////////////////////////////////////////////////////////////////////
	// 2016-3-4		kp007	定义函数指针
	typedef BOOL	(*fn_Init)(void);
	typedef BOOL	(*fn_UnInit)(void);
	typedef HANDLE  (*fn_TaskCreate)(DownTaskParam &stParam);
	typedef BOOL    (*fn_TaskDelete)(HANDLE hTask);
	typedef BOOL	(*fn_TaskStart) (HANDLE hTask);
	typedef BOOL	(*fn_TaskPause) (HANDLE hTask);
	typedef BOOL	(*fn_TaskQuery) (HANDLE hTask,DownTaskInfo &stTaskInfo);
	typedef BOOL	(*fn_TaskQueryEx) (HANDLE hTask,DownTaskInfo &stTaskInfo);
	typedef void	(*fn_LimitSpeed)(INT32 nKBps);
	typedef void	(*fn_LimitUploadSpeed)(INT32 nTcpBps,INT32 nOtherBps);
	typedef BOOL	(*fn_DelTempFile)(DownTaskParam &stParam);
	typedef BOOL	(*fn_SetProxy)(DOWN_PROXY_INFO &stProxy);
	typedef void    (*fn_SetUserAgent)( const TCHAR* pszUserAgent );
	typedef BOOL	(*fn_GetFileSizeWithUrl)(const wchar_t * lpURL, INT64& iFileSize);
	typedef BOOL    (*fn_ParseThunderPrivateUrl)(const TCHAR *pszThunderUrl, TCHAR *normalUrlBuffer, INT32 bufferLen);
	typedef LONG	(*fn_SetAdditionInfo)( HANDLE task_id, WSAPROTOCOL_INFOW *sock_info, CHAR *http_resp_buf, LONG buf_len );
	typedef BOOL	(*fn_SetFileIdAndSize)(HANDLE hTask, char szFileId[40], unsigned __int64 nFileSize);

#define CHECKFUNC(f, ret) if (f == NULL) return ret;
#define CHECKFUNC_(f) if (f == NULL) return;
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	thunderWrapper	类 2016-3-4	kp007
	//	迅雷下载封装类
	//	
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	class thunderWrapper
	{
	public:
		thunderWrapper(PCWSTR pDllPath = L"xldl.dll")
			: m_hModule(NULL)
			, m_hTask(NULL)
		{
			_Init					= NULL;    //  (fn_Init)						::GetProcAddress(m_hModule, "XL_Init");
			_UnInit					= NULL;    //  (fn_UnInit)					::GetProcAddress(m_hModule, "XL_UnInit");
			_TaskCreate				= NULL;    //  (fn_TaskCreate)				::GetProcAddress(m_hModule, "XL_CreateTask");
			_TaskDelete				= NULL;    //  (fn_TaskDelete)				::GetProcAddress(m_hModule, "XL_DeleteTask");
			_TaskStart				= NULL;    //  (fn_TaskStart)				::GetProcAddress(m_hModule, "XL_StartTask");
			_TaskPause				= NULL;    //  (fn_TaskPause)				::GetProcAddress(m_hModule, "XL_StopTask");
			_TaskQuery				= NULL;    //  (fn_TaskQuery)				::GetProcAddress(m_hModule, "XL_QueryTaskInfo");
			_TaskQueryEx			= NULL;    //  (fn_TaskQueryEx)				::GetProcAddress(m_hModule, "XL_QueryTaskInfoEx");
			_LimitSpeed				= NULL;    //  (fn_LimitSpeed)				::GetProcAddress(m_hModule, "XL_SetSpeedLimit");
			_LimitUploadSpeed		= NULL;    //  (fn_LimitUploadSpeed)			::GetProcAddress(m_hModule, "XL_SetUploadSpeedLimit");
			_DelTempFile			= NULL;    //  (fn_DelTempFile)				::GetProcAddress(m_hModule, "XL_DelTempFile");
			_SetProxy				= NULL;    //  (fn_SetProxy)					::GetProcAddress(m_hModule, "XL_SetProxy");
			_SetUserAgent			= NULL;    //  (fn_SetUserAgent)				::GetProcAddress(m_hModule, "XL_SetUserAgent");
			_GetFileSizeWithUrl		= NULL;    //  (fn_GetFileSizeWithUrl)		::GetProcAddress(m_hModule, "XL_GetFileSizeWithUrl");
			_ParseThunderPrivateUrl = NULL;    //  (fn_ParseThunderPrivateUrl)	::GetProcAddress(m_hModule, "XL_ParseThunderPrivateUrl");
			_SetAdditionInfo		= NULL;    //  (fn_SetAdditionInfo)			::GetProcAddress(m_hModule, "XL_SetAdditionInfo");
			_SetFileIdAndSize		= NULL;    //  (fn_SetFileIdAndSize)			::GetProcAddress(m_hModule, "XL_SetFileIdAndSize");

			//m_hModule = ::LoadLibraryW(pDllPath);
			//assert(m_hModule);
			//if (m_hModule == NULL)
			//{
			//	throw L"can not load xldl.dll";
			//}
			//_Init					= (fn_Init)						::GetProcAddress(m_hModule, "XL_Init");
			//_UnInit					= (fn_UnInit)					::GetProcAddress(m_hModule, "XL_UnInit");
			//_TaskCreate				= (fn_TaskCreate)				::GetProcAddress(m_hModule, "XL_CreateTask");
			//_TaskDelete				= (fn_TaskDelete)				::GetProcAddress(m_hModule, "XL_DeleteTask");
			//_TaskStart				= (fn_TaskStart)				::GetProcAddress(m_hModule, "XL_StartTask");
			//_TaskPause				= (fn_TaskPause)				::GetProcAddress(m_hModule, "XL_StopTask");
			//_TaskQuery				= (fn_TaskQuery)				::GetProcAddress(m_hModule, "XL_QueryTaskInfo");
			//_TaskQueryEx			= (fn_TaskQueryEx)				::GetProcAddress(m_hModule, "XL_QueryTaskInfoEx");
			//_LimitSpeed				= (fn_LimitSpeed)				::GetProcAddress(m_hModule, "XL_SetSpeedLimit");
			//_LimitUploadSpeed		= (fn_LimitUploadSpeed)			::GetProcAddress(m_hModule, "XL_SetUploadSpeedLimit");
			//_DelTempFile			= (fn_DelTempFile)				::GetProcAddress(m_hModule, "XL_DelTempFile");
			//_SetProxy				= (fn_SetProxy)					::GetProcAddress(m_hModule, "XL_SetProxy");
			//_SetUserAgent			= (fn_SetUserAgent)				::GetProcAddress(m_hModule, "XL_SetUserAgent");
			//_GetFileSizeWithUrl		= (fn_GetFileSizeWithUrl)		::GetProcAddress(m_hModule, "XL_GetFileSizeWithUrl");
			//_ParseThunderPrivateUrl = (fn_ParseThunderPrivateUrl)	::GetProcAddress(m_hModule, "XL_ParseThunderPrivateUrl");
			//_SetAdditionInfo		= (fn_SetAdditionInfo)			::GetProcAddress(m_hModule, "XL_SetAdditionInfo");
			//_SetFileIdAndSize		= (fn_SetFileIdAndSize)			::GetProcAddress(m_hModule, "XL_SetFileIdAndSize");
		}

		virtual ~thunderWrapper(void)
		{
			if (m_hModule)
			{
				::FreeLibrary(m_hModule);
			}
		}

		bool init(PCWSTR pDllPath = L"xldl.dll")
		{
			assert(!m_hModule);

			m_hModule = ::LoadLibraryW(pDllPath);
			assert(m_hModule);
			if (m_hModule == NULL)
			{
				throw L"can not load xldl.dll";
			}
			_Init					= (fn_Init)						::GetProcAddress(m_hModule, "XL_Init");
			_UnInit					= (fn_UnInit)					::GetProcAddress(m_hModule, "XL_UnInit");
			_TaskCreate				= (fn_TaskCreate)				::GetProcAddress(m_hModule, "XL_CreateTask");
			_TaskDelete				= (fn_TaskDelete)				::GetProcAddress(m_hModule, "XL_DeleteTask");
			_TaskStart				= (fn_TaskStart)				::GetProcAddress(m_hModule, "XL_StartTask");
			_TaskPause				= (fn_TaskPause)				::GetProcAddress(m_hModule, "XL_StopTask");
			_TaskQuery				= (fn_TaskQuery)				::GetProcAddress(m_hModule, "XL_QueryTaskInfo");
			_TaskQueryEx			= (fn_TaskQueryEx)				::GetProcAddress(m_hModule, "XL_QueryTaskInfoEx");
			_LimitSpeed				= (fn_LimitSpeed)				::GetProcAddress(m_hModule, "XL_SetSpeedLimit");
			_LimitUploadSpeed		= (fn_LimitUploadSpeed)			::GetProcAddress(m_hModule, "XL_SetUploadSpeedLimit");
			_DelTempFile			= (fn_DelTempFile)				::GetProcAddress(m_hModule, "XL_DelTempFile");
			_SetProxy				= (fn_SetProxy)					::GetProcAddress(m_hModule, "XL_SetProxy");
			_SetUserAgent			= (fn_SetUserAgent)				::GetProcAddress(m_hModule, "XL_SetUserAgent");
			_GetFileSizeWithUrl		= (fn_GetFileSizeWithUrl)		::GetProcAddress(m_hModule, "XL_GetFileSizeWithUrl");
			_ParseThunderPrivateUrl = (fn_ParseThunderPrivateUrl)	::GetProcAddress(m_hModule, "XL_ParseThunderPrivateUrl");
			_SetAdditionInfo		= (fn_SetAdditionInfo)			::GetProcAddress(m_hModule, "XL_SetAdditionInfo");
			_SetFileIdAndSize		= (fn_SetFileIdAndSize)			::GetProcAddress(m_hModule, "XL_SetFileIdAndSize");
			
			CHECKFUNC(_Init, false);
			return _Init() == TRUE;
		}
		bool unInit()
		{
			CHECKFUNC(_UnInit, false);
			return TRUE == _UnInit();
		}
		bool taskCreate(DownTaskParam &param)
		{
			CHECKFUNC(_TaskCreate, false);
			m_hTask = _TaskCreate(param);
			return m_hTask != NULL;
		}
		bool taskCreate(PCWSTR ptaskUrl, PCWSTR pSavePath, PCWSTR pFileName)
		{
			assert(ptaskUrl && pSavePath && pFileName);
			DownTaskParam param;
			std::wcsncpy(param.szTaskUrl, ptaskUrl, _countof(param.szTaskUrl));
			std::wcsncpy(param.szFilename, pFileName, _countof(param.szFilename));
			std::wcsncpy(param.szSavePath, pSavePath, _countof(param.szSavePath));
			
			return taskCreate(param);
		}
		bool taskDelete()
		{
			CHECKFUNC(_TaskDelete, false);
			assert(m_hTask);
			bool bl = TRUE == _TaskDelete(m_hTask);
			if(bl) m_hTask = NULL;
			return bl;
		}
		bool taskStart()
		{
			CHECKFUNC(_TaskStart, false);
			assert(m_hTask);
			return TRUE == _TaskStart(m_hTask);
		}
		bool taskPause()
		{
			CHECKFUNC(_TaskPause, false);
			assert(m_hTask);
			return TRUE == _TaskPause(m_hTask);
		}
		bool taskQuery(DownTaskInfo &stTaskInfo)
		{
			CHECKFUNC(_TaskQuery, false);
			assert(m_hTask);
			return TRUE == _TaskQuery(m_hTask, stTaskInfo);
		}
		bool taskQueryEx(DownTaskInfo &stTaskInfo)
		{
			CHECKFUNC(_TaskQueryEx, false);
			assert(m_hTask);
			return TRUE == _TaskQueryEx(m_hTask, stTaskInfo);
		}
		void limitSpeed(INT32 nBps)
		{
			CHECKFUNC_(_LimitSpeed);
			_LimitSpeed(nBps);
		}
		void limitUploadSpeed(INT32 nTcpBps,INT32 nOtherBps)
		{
			CHECKFUNC_(_LimitUploadSpeed);
			_LimitUploadSpeed(nTcpBps, nOtherBps);
		}
		bool delTempFile(DownTaskParam &stParam)
		{
			CHECKFUNC(_DelTempFile,false);
			return TRUE == _DelTempFile(stParam);
		}
		bool setProxy(DOWN_PROXY_INFO &stProxy)
		{
			CHECKFUNC(_SetProxy, false);
			return TRUE == _SetProxy(stProxy);
		}
		void setUserAgent(const TCHAR *pszUserAgent)
		{
			CHECKFUNC_(_SetUserAgent);
			_SetUserAgent(pszUserAgent);
		}
		bool getFileSizeWithUrl(const wchar_t * lpURL, INT64& iFileSize)
		{
			CHECKFUNC(_GetFileSizeWithUrl, false);
			return TRUE == _GetFileSizeWithUrl(lpURL, iFileSize);
		}
		bool parseThunderPrivateUrl(const TCHAR *pszThunderUrl, TCHAR *normalUrlBuffer, INT32 bufferLen)
		{
			//if (_ParseThunderPrivateUrl == NULL ) return FALSE;
			CHECKFUNC(_ParseThunderPrivateUrl, false);
			return TRUE == _ParseThunderPrivateUrl(pszThunderUrl, normalUrlBuffer, bufferLen);
		}
		LONG setAdditionInfo(HANDLE task_id, WSAPROTOCOL_INFOW *sock_info, CHAR *http_resp_buf, LONG buf_len)
		{
			CHECKFUNC(_SetAdditionInfo, 0);
			return _SetAdditionInfo(task_id, sock_info, http_resp_buf, buf_len);
		}
		LONG setFileIdAndSize(char szFileId[40], unsigned __int64 nFileSize)
		{
			CHECKFUNC(_SetFileIdAndSize, 0);
			assert(m_hTask);
			return _SetFileIdAndSize(m_hTask, szFileId, nFileSize);
		}

	private:
		HMODULE						m_hModule;
		HANDLE						m_hTask;

		fn_Init						_Init;
		fn_UnInit					_UnInit;
		fn_TaskCreate				_TaskCreate;
		fn_TaskDelete				_TaskDelete;
		fn_TaskStart				_TaskStart;
		fn_TaskPause				_TaskPause;
		fn_TaskQuery				_TaskQuery;
		fn_TaskQueryEx				_TaskQueryEx;
		fn_LimitSpeed				_LimitSpeed;
		fn_LimitUploadSpeed			_LimitUploadSpeed;
		fn_DelTempFile				_DelTempFile;
		fn_SetProxy					_SetProxy;
		fn_SetUserAgent				_SetUserAgent;
		fn_GetFileSizeWithUrl		_GetFileSizeWithUrl;
		fn_ParseThunderPrivateUrl	_ParseThunderPrivateUrl;
		fn_SetAdditionInfo			_SetAdditionInfo;
		fn_SetFileIdAndSize			_SetFileIdAndSize;
	};
}

#endif	// __GTC_THUNDERWRAPPER__