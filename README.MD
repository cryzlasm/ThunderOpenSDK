# 版权
**版权与最终解释权归迅雷公司所有**

---

 # 迅雷下载引擎

分别由  小米, 猎豹, 360极速浏览器等软件提取

不承担软件无毒, 均为网络搜集, 自行校验签名


# 相关项目

[MFC --- MiniThunder] : (https://github.com/intlinfo/MiniThunder)  
此代码 编译之后, 扔给需要的动态库, 可直接下载使用, 看资源数, 来决定下载速度, 貌似无限速

[C# --- ThunderDownloader] : (https://github.com/VTS2018/ThunderDownloader)

---
SDK 接口文档

# 全局接口

| 接口名称 | 功能说明 |
| :--- | :--- |
| [XL\_Init](http://open.xunlei.com/wiki/api_doc.html#1) | 初始化SDK，并使其为处理后续操作做好准备。 |
| [XL\_UnInit](http://open.xunlei.com/wiki/api_doc.html#2) | 反初始化SDK，释放模块运行期间申请的资源。 |
| [XL\_DelTempFile](http://open.xunlei.com/wiki/api_doc.html#3) | 删除临时文件 |
| [XL\_SetSpeedLimit](http://open.xunlei.com/wiki/api_doc.html#4) | 设置最大下载速度 |
| [XL\_SetProxy](http://open.xunlei.com/wiki/api_doc.html#5) | 设置全局代理 |
| [XL\_SetUserAgent](http://open.xunlei.com/wiki/api_doc.html#6) | 设置HTTP请求时客户端信息 |
| [XL\_ParseThunderPrivateUrl](http://open.xunlei.com/wiki/api_doc.html#g7) | 将迅雷专用链转成实际URL |
| [XL\_SetUploadSpeedLimit](http://open.xunlei.com/wiki/api_doc.html#g8) | 限制上传速度 |
| [XL\_CreateTaskByURL](http://open.xunlei.com/wiki/api_doc.html#g9) | 简单封装了XL\_CreateTask接口 |
| [XL\_CreateTaskByThunder](http://open.xunlei.com/wiki/api_doc.html#g10) | 拉起迅雷7创建下载任务 |
| [XL\_ForceStopTask](http://open.xunlei.com/wiki/api_doc.html#g11) | 强制暂停任务 |

# 任务接口

| 接口名称 | 功能说明 |
| :--- | :--- |
| [XL\_CreateTask](http://open.xunlei.com/wiki/api_doc.html#7) | 创建任务 |
| [XL\_DeleteTask](http://open.xunlei.com/wiki/api_doc.html#8) | 销毁任务 |
| [XL\_StartTask](http://open.xunlei.com/wiki/api_doc.html#9) | 开始任务 |
| [XL\_StopTask](http://open.xunlei.com/wiki/api_doc.html#10) | 停止任务 |
| [XL\_QueryTaskInfoEx](http://open.xunlei.com/wiki/api_doc.html#11) | 查询任务信息 |

# 接口详细说明
#### XL\_Init
##### BOOLXL\_Init(void)初始化下载引擎，并使其为处理后续操作做好准备。
* *返回值：*TRUE表示成功，FALSE表示失败。一些特殊情况会导致初始化失败，如：二进制文件缺失。
* *说明：*该接口必须与XL\_Unint(void)成对出现。调用该接口的时，xldl.dll会拉起MiniThunderPlatform.exe子进程。
#### XL\_UnInit
##### BOOL XL\_UnInit(void)反初始化下载引擎，释放模块运行期间申请的资源。
* *返回值：*TRUE表示成功，FALSE表示失败。
* *说明：*调用该接口后，会通知MiniThunderPlatform.exe子进程退出。
#### XL\_CreateTask
##### HANDLE XL\_CreateTask(DownTaskParam &stParam)创建任务。可以新建任务也可以续传任务，参数中IsResume用于表示任务是否是续传任务。其他信息请参考DownTaskParam的定义。
* *参数：* [in] stParam，创建任务需要的参数。
* *DownTaskParam参考：*
    ```cpp
    struct DownTaskParam
    {
    	int nReserved1;
    	TCHAR szTaskUrl[2084];          // 任务URL，支持http,https,ftp,ftps格式
    	TCHAR szRefUrl[2084];           // 可空，HTTP下载所在的网页URL
    	TCHAR szCookies[4096];          // 可空，浏览器cookie
    	TCHAR szFilename[MAX_PATH];    // 下载保存文件名.
    	TCHAR szReserved[MAX_PATH];
    	TCHAR szSavePath[MAX_PATH];    // 文件保存目录
    	HWND  hReserved;
    	BOOL bReserved1;
    	TCHAR szReserved1[64];
    	TCHAR szReserved2[64];
    	BOOL IsOnlyOriginal;            //是否只从原始地址下载
    	UINT nReserved2;
    	BOOL bReserved2;
    	BOOL IsResume;                 // 是否用续传
    	DWORD reserved[2048];
    }
    
    ```
* *返回值：*返回任务的句柄。
* *说明：*任务创建后，是不会马上就下载的，需要调用XL\_StartTask。异步执行。
#### XL\_DeleteTask
##### BOOL XL\_DeleteTask(HANDLE hTask)销毁任务，释放任务在运行期间申请的资源。
* *参数：* [in]hTask，任务句柄
* *返回值：*TRUE表示成功，FALSE表示失败。当任务不存在时，调用会失败。
* *说明：*在任务暂停、成功以及删除任务的时候都需要调用该接口，保证资源尽快的释放。 异步执行,如果任务出于pending状态则不能调用该接口。
#### XL\_StartTask
##### BOOL XL\_StartTask(HANDLE hTask);开始下载。任务创建成功后，不会马上开始下载，需调用此接口才会开始下载。
* *参数：* [in]hTask，任务句柄
* *返回值：*TRUE表示成功，FALSE表示失败。当任务不存在时，调用会失败。
* *说明：*异步执行,如果任务出于pending状态则不能调用该接口。
#### XL\_StopTask
##### BOOL XL\_StopTask(HANDLE hTask)停止下载
* *参数：* [in]hTask，任务句柄
* *返回值：*TRUE表示成功，FALSE表示失败。当任务不存在时，调用会失败。
* *说明：*获取任务信息是使用轮询方式的，最终任务下载了多少数据在任务停止下载后查询才是正确的。调用后任务不会立即停止，需轮询到任务状态为PAUSE之后，才能获取到。
#### XL\_QueryTaskInfoEx
##### BOOL XL\_QueryTaskInfoEx(HANDLE hTask, DownTaskInfo & stTaskInfo);查询任务当前信息。
* *参数：* [in]hTask，任务句柄 [out] stTaskInfo, 任务信息。
* *DownTaskInfo参考：*
    ```cpp
    struct DownTaskInfo
    {
    	DOWN_TASK_STATUS	stat;					//任务状态
    	TASK_ERROR_TYPE		fail_code;			//错误码
    	TCHAR		szFilename[MAX_PATH];			//文件名
    	TCHAR		szReserved[MAX_PATH];
    	__int64     nTotalSize;         		// 该任务总大小(字节)
    	__int64     nTotalDownload;     		// 下载有效字节数(可能存在回退的情况)
    	float		fPercent;           		// 下载进度
    	int			nTotalTime;         		// 不提供该值
    	int			nSrcTotal;          		// 总资源数
    	int			nSrcUsing;          		// 可用资源数
    	int			nReserved1;
    	int			nReserved2;
    	int			nReserved3;
    	int			nReserved;
    	__int64     nTotalUpload;       		// 现不提供该值
    	__int64		nDonationP2P;       		// p2p资源贡献的数据长度
    	__int64		nReserved4;
    	__int64		nDonationOrgin;     		// 原始资源贡献的数据长度
    	__int64		nDonationP2S;       		// 镜像资源贡献的数据长度
    	__int64		nReserved5;
    	__int64     nReserved6;
    	int			nSpeed;             		// 速度(字节/秒)
    	int			nSpeedP2S;          		// 加速服务器资源的下载速度
    	int			nSpeedP2P;          		// peer下载速度
    	bool		IsOriginUsable;     		   // 原始资源是否可用
    	float		fReserved;
    	int			bReserved;
    	DWORD		reserved[64];
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
    
    ```
* *返回值：*TRUE表示成功，FALSE表示失败。
* *说明：*IsOriginUsable，原始资源是否可用，是一个布尔型的参数，但是原始连接原始资源是一个耗时的操作，意味着中间有段时间原始资源是否有效是未知的。这个参数的初始态是false，所以就存在原始资源是有效，但在任务刚开始时这个参数是false的问题。上层在使用该值的时候需要根据业务逻辑再做处理。
#### XL\_DelTempFile
##### BOOL XL\_DelTempFile(DownTaskParam &stParam)删除任务的临时文件。下载引擎会创建 .td 、 .td.cfg后缀的文件用来保存已下载的数据。
* *参数：* [in]stParam，任务参数，参考创建任务中的参数。但是这里只有文件保存的目录和文件名是必须。
* *返回值：*TRUE表示成功，FALSE表示失败。
* *说明：*文件名是最后真正保存到磁盘的文件名，不带临时文件后缀名。最终保存的文件名会和创建任务不一样，所以这个文件名要以查询任务信息返回的文件名为准。在保存路径下已经存在相同文件名的文件时，最终保存的文件名就会自动改变文件名：filename.zip → filename（1）.zip。 异步执行。
#### XL\_SetSpeedLimit
##### void XL\_SetSpeedLimit(INT32 nKBps)设置最大下载速度。
* *参数：* [in]nKBps, 速度上限值
* *说明：*异步执行
#### XL\_SetProxy
##### BOOL XL\_SetProxy(DOWN\_PROXY\_INFO &stProxyInfo)设置下载代理，全局任务代理信息。
* *参数：* [in]stProxyIfno 代理信息
* *DOWN\_PROXY\_INFO参考：*
    ```cpp
    enum DOWN_PROXY_TYPE
    {
    	PROXY_TYPE_IE	 = 0,
    	PROXY_TYPE_HTTP  = 1,
    	PROXY_TYPE_RESERVED= 2,		//不支持该代理
    	PROXY_TYPE_SOCK5 = 3,
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
    	DOWN_PROXY_AUTH_TYPE	stResverd;
    	TCHAR		szHost[2048];
    	INT32		nPort;
    	TCHAR		szUser[50];
    	TCHAR		szPwd[50];
    	TCHAR		szDomain[2048];
    };
    
    ```
* *返回值：*TRUE表示成功，FALSE表示失败。参数非法返回FALSE
#### XL\_SetUserAgent
##### void XL\_SetUserAgent(const TCHAR \*pszUserAgent)设置向原始资源的Http任务请求的UserAgent。
* *参数：* [in]pszUserAgent，客户端UserAgent字符串
* *说明：*在调用该方法后创建的任务的才会使用新的UserAgent。
#### XL\_ParseThunderPrivateUrl
##### BOOL XL\_ParseThunderPrivateUrl(const wchar\_t \*pszThunderUrl, wchar\_t \*normalUrlBuffer, INT32 bufferLen)迅雷专用链是根据一定逻辑从普通URL转成的。
* *参数：* [in] pszThunderUrl，迅雷专用链URL [out] normalUrlBuffer，存储转化后的普通URL的缓冲区 [out] bufferLen，normalUrlBuffer的缓冲区大小，单位字符数
* *返回值：*TRUE表示成功，FALSE表示失败
* *说明：*此函数功能独立，和其他函数没有依赖关系，可随时单独使用
#### XL\_SetUploadSpeedLimit
##### void XL\_SetUploadSpeedLimit(INT32 nTcpKBps, INT32 nOtherKBps)可根据实际情况设置外网和内网的上传速度。
* *参数：* [in] nTcpKBps, 内网上传速度，单位为KB/s [in] nOtherKBps, 外网上传速度，单位为KB/s
* *返回值：*无
#### XL\_CreateTaskByURL
##### HANDLE XL\_CreateTaskByURL(const wchar\_t \*url, const wchar\_t \*path, const wchar\_t \*fileName, BOOL IsResume)通过任务URL、路径、文件名创建任务。
* *参数：* [in] url, 任务URL，不能为空，包括空字符字符长度不能超过2084 [in] path, 任务路径，不能为空，包括空字符字符长度不能超过260 [in] fileName, 任务文件名，不能为空，包括空字符字符长度不能超过260 [in] IsResume, 是否是续传任务
* *返回值：*返回任务的句柄
#### XL\_CreateTaskByThunder
##### LONG XL\_CreateTaskByThunder(wchar\_t \*pszUrl, wchar\_t \*pszFileName, wchar\_t \*pszReferUrl, wchar\_t \*pszCharSet, wchar\_t \*pszCookie)通过传递URL和文件名等信息拉起迅雷7的新建面板创建下载任务。
* *参数：* [in] pszUrl，任务URL [in] pszFileName，下载保存的文件名 [in] pszReferUrl，引用页URL [in] pszCharSet，当前网页的字符集 [in] pszCookie，下载数据所需的cookie
* *返回值：*0成功，其他为失败
#### XL\_ForceStopTask
##### BOOL XL\_ForceStopTask(HANDLE hTask)强制暂停任务
* *参数：* [in] hTask，任务句柄
* *返回值：*TRUE表示成功，FALSE表示失败。当任务不存在时，调用会失败
* *说明：*在开启UAC下载大文件时，调用XL\_StopTask可能需要消耗比较长的时间。这种情况下如果需要快速暂停任务，可以调用XL\_ForceStopTask，不过有可能导致已经下载的还没写到磁盘的数据丢失。
## 注意事项
1. 全局接口是线程不安全的，且XL\_Init外的其他接口必须在该函数成功返回后才能调用； 
2. 如果任务处于TSC\_STARTPENDING或TSC\_STOPPENDING，关于任务的操作只能调用查询任务信息的接口。
# 接口逻辑说明
## 任务异步操作
任务的操作是异步执行的。调用接口有两个操作:  
1. 操作上层xldl.dll中的虚任务 
2. 在命令队列对push一条相关操作的命令

接口层可以操作的任务都是虚任务，真实任务是在MiniThunderPlatfom进程创建的。

## 任务创建的流程
1. Xldl创建虚任务； 
2. 将操作与参数push到命令队列；
3. 命令处理线程负责执行队列中的命令，与MiniThunderPlatfom同步通信； 
4. MiniThunderPlatfom创建任务成功后，虚任务就可以和实任务映射。 
之后所有对virtual task 的操作都将映射到真正的task，并在MiniTP执行真正的操作。 任务信息查询，任务信息的更新需要调用者驱动，需要调用者每隔1s调用一次该接口。

## 任务信息查询和更新的流程
1. 调用接口查询信息时，先从虚任务查询任务信息，第一次调用的时候肯定没有信息 
2. 将查询操作与参数push到命令队列； 
3. 命令处理线程负责执行队列中的命令，与MiniThunderPlatfom同步通信； 
4. 查询到真实任务信息后，将信息存储到虚任务中； 
5. 第二次查询就可以直接查询到任务信息，这些信息是上一次查询到的。 
这里就会出现这样的情况，第一次查询操作不能获取到任务信息，即任务处于pause/start\_pending状态中。更极端的情况，任务下载完成前一次查询没有调用过，在任务完成后再调用该接口会发现任务进度为0。

## 子进程异常退出
这种情况是不被欢迎的，但又不可避免。子进程异常退出后MiniThunderPlatfom创建的任务会销毁。这样，虚任务除了与真实任务的映射关系，其实并无意义。这时候，查询任务信息就会返回任务出错，错误码为TASK\_ERROR\_ID\_INVALID（任务id非法）。这时需要重新创建续传任务，接口为XL\_CreateTask，结构体中其他参数与创建普通任务相同，参数IsResume设为TRUE。
# 其它
### SDK文件说明Sdk总共有10个二进制文件。二进制文件之间的依赖关系如下图所示：
各个文件功能介绍：

| 文件名 | 功能 |
| :--- | :--- |
| xldl.dll | 导出MiniTP接口 |
| MiniThunderPlatform.exe | 独立进程 |
| download\_engine.dll | MiniTP核心库 |
| zlib1.dll | 压缩通信数据 |
| dl\_peer\_id.dll | 获取迅雷客户端标识 |
| XLBugReport.exe | 负责上报捕获到的崩溃 |
| XLBugHandler.dll | 负责拉起XLBugReport .exe |
| minizip.dll、mini\_unzip.dll | 用于压缩文件崩溃堆栈 |
| atl71.dll | 微软提供的程序库 |





