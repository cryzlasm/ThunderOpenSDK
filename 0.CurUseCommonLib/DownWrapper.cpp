#include "DownWrapper.h"

namespace DownEngine
{

    CDownWrapper::CDownWrapper(LPCWSTR sPath)
    {
        m_hModule = LoadLibraryW(sPath);
        if (m_hModule == NULL)
        {
            throw L"can not load xldl.dll";
        }
        WCHAR szModulePath[MAX_PATH] = { 0 };
        GetModuleFileNameW(NULL, szModulePath, MAX_PATH);
        PathRemoveFileSpecW(szModulePath);  // 拆分路径        新版使用PathCchRemoveFileSpec

        WCHAR szDllpath[MAX_PATH] = { 0 };
        PathCombineW(szDllpath, szModulePath, L"xldl.dll");  // 连接路径, 新版建议使用 PathCchCombine
        m_Init                      = (fn_Init)                         GetProcAddress(m_hModule, "XL_Init");
        m_UnInit                    = (fn_UnInit)                       GetProcAddress(m_hModule, "XL_UnInit");
        m_TaskCreate                = (fn_TaskCreate)                   GetProcAddress(m_hModule, "XL_CreateTask");
        m_TaskDelete                = (fn_TaskDelete)                   GetProcAddress(m_hModule, "XL_DeleteTask");
        m_TaskStart                 = (fn_TaskStart)                    GetProcAddress(m_hModule, "XL_StartTask");
        m_TaskStop                  = (fn_TaskStop)                     GetProcAddress(m_hModule, "XL_StopTask");
        m_ForceStopTask             = (fn_ForceStopTask)                GetProcAddress(m_hModule, "XL_ForceStopTask");
        m_QueryTaskInfo             = (fn_QueryTaskInfo)                GetProcAddress(m_hModule, "XL_QueryTaskInfo");
        m_QueryTaskInfoEx           = (fn_QueryTaskInfoEx)              GetProcAddress(m_hModule, "XL_QueryTaskInfoEx");
        m_DelTempFile               = (fn_DelTempFile)                  GetProcAddress(m_hModule, "XL_DelTempFile");
        m_SetSpeedLimit             = (fn_SetSpeedLimit)                GetProcAddress(m_hModule, "XL_SetSpeedLimit");
        m_SetUploadSpeedLimit       = (fn_SetUploadSpeedLimit)          GetProcAddress(m_hModule, "XL_SetUploadSpeedLimit");
        m_SetProxy                  = (fn_SetProxy)                     GetProcAddress(m_hModule, "XL_SetProxy");
        m_SetUserAgent              = (fn_SetUserAgent)                 GetProcAddress(m_hModule, "XL_SetUserAgent");
        m_ParseThunderPrivateUrl    = (fn_ParseThunderPrivateUrl)       GetProcAddress(m_hModule, "XL_ParseThunderPrivateUrl");
        m_GetFileSizeWithUrl        = (fn_GetFileSizeWithUrl)           GetProcAddress(m_hModule, "XL_GetFileSizeWithUrl");
        m_SetFileIdAndSize          = (fn_SetFileIdAndSize)             GetProcAddress(m_hModule, "XL_SetFileIdAndSize");
        m_SetAdditionInfo           = (fn_SetAdditionInfo)              GetProcAddress(m_hModule, "XL_SetAdditionInfo");
        m_CreateTaskByURL           = (fn_CreateTaskByURL)              GetProcAddress(m_hModule, "XL_CreateTaskByURL");
        m_CreateTaskByThunder       = (fn_CreateTaskByThunder)          GetProcAddress(m_hModule, "XL_CreateTaskByThunder");
        m_CreateBTTaskByThunder     = (fn_CreateBTTaskByThunder)        GetProcAddress(m_hModule, "XL_CreateBTTaskByThunder");
    }

    CDownWrapper::~CDownWrapper()
    {
        if (m_hModule)
        {
            FreeLibrary(m_hModule);
        }
    }

    HANDLE CDownWrapper::TaskCreate(DownTaskParam &param)
    {
        CHECKFUNC(m_TaskCreate, NULL); return m_TaskCreate(param);
    }
    BOOL CDownWrapper::TaskDelete(HANDLE hTask)
    {
        CHECKFUNC(m_TaskDelete, FALSE); return m_TaskDelete(hTask);
    }
    BOOL CDownWrapper::TaskStart(HANDLE hTask)
    {
        CHECKFUNC(m_TaskStart, FALSE); return m_TaskStart(hTask);
    }
    BOOL CDownWrapper::TaskStop(HANDLE hTask)
    {
        CHECKFUNC(m_TaskStop, FALSE); return m_TaskStop(hTask);
    }
    BOOL CDownWrapper::TaskForceStop(HANDLE hTask)
    {
        CHECKFUNC(m_ForceStopTask, FALSE); return m_ForceStopTask(hTask);
    }
    BOOL CDownWrapper::TaskQueryInfo(HANDLE hTask, DownTaskInfo & stTaskInfo)
    {
        CHECKFUNC(m_QueryTaskInfo, FALSE); return m_QueryTaskInfo(hTask, stTaskInfo);
    }
    BOOL CDownWrapper::TaskQueryInfoEx(HANDLE hTask, DownTaskInfo & stTaskInfo)
    {
        CHECKFUNC(m_QueryTaskInfoEx, FALSE); return m_QueryTaskInfoEx(hTask, stTaskInfo);
    }
    BOOL CDownWrapper::DelTempFile(DownTaskParam &stParam)
    {
        CHECKFUNC(m_DelTempFile, FALSE); return m_DelTempFile(stParam);
    }
    void CDownWrapper::SetSpeedLimit(INT32 nBps)
    {
        CHECKFUNC_(m_SetSpeedLimit);  m_SetSpeedLimit(nBps);
    }
    void CDownWrapper::SetUploadSpeedLimit(INT32 nTcpBps, INT32 nOtherBps)
    {
        CHECKFUNC_(m_SetUploadSpeedLimit);  m_SetUploadSpeedLimit(nTcpBps, nOtherBps);
    }
    BOOL CDownWrapper::SetProxy(DOWN_PROXY_INFO &stProxyInfo)
    {
        CHECKFUNC(m_SetProxy, FALSE); return m_SetProxy(stProxyInfo);
    }
    void CDownWrapper::SetUserAgent(const wchar_t *pszUserAgent)
    {
        CHECKFUNC_(m_SetUserAgent);  m_SetUserAgent(pszUserAgent);
    }
    BOOL CDownWrapper::ParseThunderPrivateUrl(const wchar_t *pszThunderUrl, wchar_t *normalUrlBuffer, INT32 bufferLen)
    {
        CHECKFUNC(m_ParseThunderPrivateUrl, FALSE); return m_ParseThunderPrivateUrl(pszThunderUrl, normalUrlBuffer, bufferLen);
    }
    BOOL CDownWrapper::GetFileSizeWithUrl(const wchar_t * lpURL, INT64& iFileSize)
    {
        CHECKFUNC(m_GetFileSizeWithUrl, FALSE); return m_GetFileSizeWithUrl(lpURL, iFileSize);
    }
    BOOL CDownWrapper::SetFileIdAndSize(HANDLE hTask, char szFileId[40], unsigned __int64 nFileSize)
    {
        CHECKFUNC(m_SetFileIdAndSize, FALSE); return m_SetFileIdAndSize(hTask, szFileId, nFileSize);
    }
    BOOL CDownWrapper::SetAdditionInfo(HANDLE task_id, WSAPROTOCOL_INFOW *sock_info, CHAR *http_resp_buf, LONG buf_len)
    {
        CHECKFUNC(m_SetAdditionInfo, FALSE); return m_SetAdditionInfo(task_id, sock_info, http_resp_buf, buf_len);
    }
    HANDLE CDownWrapper::CreateTaskByURL(const wchar_t *url, const wchar_t *path, const wchar_t *fileName, BOOL IsResume)
    {
        CHECKFUNC(m_CreateTaskByURL, FALSE); return m_CreateTaskByURL(url, path, fileName, IsResume);
    }
    LONG CDownWrapper::CreateTaskByThunder(wchar_t *pszUrl, wchar_t *pszFileName, wchar_t *pszReferUrl, wchar_t *pszCharSet, wchar_t *pszCookie)
    {
        CHECKFUNC(m_CreateTaskByThunder, FALSE); return m_CreateTaskByThunder(pszUrl, pszFileName, pszReferUrl, pszCharSet, pszCookie);
    }
    LONG CDownWrapper::CreateBTTaskByThunder(const wchar_t *pszPath)
    {
        CHECKFUNC(m_CreateBTTaskByThunder, FALSE); return m_CreateBTTaskByThunder(pszPath);
    }
    DownTaskParam CDownWrapper::CreateDownTaskParam(const wchar_t TaskUrl[], const wchar_t Filename[], const wchar_t SavePath[], BOOL IsResume, BOOL IsOnlyOriginal, BOOL DisableAutoRename)
    {
        DownTaskParam TaskParam;
        TaskParam.DisableAutoRename = FALSE;
        StrCpyW(TaskParam.szTaskUrl, TaskUrl);
        StrCpyW(TaskParam.szFilename, Filename);
        StrCpyW(TaskParam.szSavePath, SavePath);
        return TaskParam;
    }
};
