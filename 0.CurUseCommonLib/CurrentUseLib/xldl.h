#pragma once

// 所有结构体定义按1字节对齐
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

namespace DownEngine
{
    extern "C" __declspec(dllimport) BOOL   XL_Init(void);
    extern "C" __declspec(dllimport) BOOL   XL_UnInit(void);
	extern "C" __declspec(dllimport) HANDLE XL_CreateTask(DownTaskParam &stParam);
	extern "C" __declspec(dllimport) BOOL   XL_DeleteTask(HANDLE hTask);
	extern "C" __declspec(dllimport) BOOL   XL_StartTask(HANDLE hTask);
	extern "C" __declspec(dllimport) BOOL   XL_StopTask(HANDLE hTask);
	extern "C" __declspec(dllimport) BOOL   XL_ForceStopTask(HANDLE hTask);
	extern "C" __declspec(dllimport) BOOL   XL_QueryTaskInfo(HANDLE hTask, DownTaskInfo & stTaskInfo); //旧版接口，使用Ex接口替换
	extern "C" __declspec(dllimport) BOOL   XL_QueryTaskInfoEx(HANDLE hTask, DownTaskInfo & stTaskInfo);
	extern "C" __declspec(dllimport) BOOL	XL_DelTempFile(DownTaskParam &stParam);
	extern "C" __declspec(dllimport) void	XL_SetSpeedLimit(INT32 nKBps);
	extern "C" __declspec(dllimport) void	XL_SetUploadSpeedLimit(INT32 nTcpKBps,INT32 nOtherKBps);
	extern "C" __declspec(dllimport) BOOL	XL_SetProxy(DOWN_PROXY_INFO &stProxyInfo);
	extern "C" __declspec(dllimport) void   XL_SetUserAgent(const wchar_t *pszUserAgent);
	extern "C" __declspec(dllimport) BOOL   XL_ParseThunderPrivateUrl(const wchar_t *pszThunderUrl, wchar_t *normalUrlBuffer, INT32 bufferLen);
	extern "C" __declspec(dllimport) BOOL   XL_GetFileSizeWithUrl(const wchar_t * lpURL, INT64& iFileSize);
    extern "C" __declspec(dllimport) BOOL   XL_SetFileIdAndSize(HANDLE hTask, char szFileId[40], unsigned __int64 nFileSize);
	extern "C" __declspec(dllimport) BOOL   XL_SetAdditionInfo( HANDLE task_id, WSAPROTOCOL_INFOW *sock_info, CHAR *http_resp_buf, LONG buf_len );
	extern "C" __declspec(dllimport) HANDLE XL_CreateTaskByURL(const wchar_t *url, const wchar_t *path, const wchar_t *fileName, BOOL IsResume);
	extern "C" __declspec(dllimport) LONG   XL_CreateTaskByThunder(wchar_t *pszUrl, wchar_t *pszFileName, wchar_t *pszReferUrl, wchar_t *pszCharSet, wchar_t *pszCookie);
	extern "C" __declspec(dllimport) LONG   XL_CreateBTTaskByThunder(const wchar_t *pszPath);
};
