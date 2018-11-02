#pragma once
#include "./xldl.h"

#define DEF_DETOUR_FUNC( func, returntype, ...) typedef returntype ( * fn_##func )(##__VA_ARGS__); fn_##func m_##func;

#define CHECKFUNC(f, ret) if (f == NULL) return ret;
#define CHECKFUNC_(f) if (f == NULL) return;
namespace DownEngine
{
    class CDownWrapper
    {
    public:
        CDownWrapper(LPCWSTR sPath);
        virtual ~CDownWrapper();
        BOOL InitEngine()
        {
            CHECKFUNC(m_Init, FALSE); return m_Init();
        }
        BOOL UnEngine()
        {
            CHECKFUNC(m_UnInit, FALSE); return m_UnInit();
        }
        HANDLE TaskCreate(DownTaskParam &param);
        BOOL TaskDelete(HANDLE hTask);
        BOOL TaskStart(HANDLE hTask);
        BOOL TaskStop(HANDLE hTask);
        BOOL TaskForceStop(HANDLE hTask);
        BOOL TaskQueryInfo(HANDLE hTask, DownTaskInfo & stTaskInfo);
        BOOL TaskQueryInfoEx(HANDLE hTask, DownTaskInfo & stTaskInfo);
        BOOL DelTempFile(DownTaskParam &stParam);
        void SetSpeedLimit(INT32 nBps);
        void SetUploadSpeedLimit(INT32 nTcpBps, INT32 nOtherBps);
        BOOL SetProxy(DOWN_PROXY_INFO &stProxyInfo);
        void SetUserAgent(const wchar_t *pszUserAgent);
        BOOL ParseThunderPrivateUrl(const wchar_t *pszThunderUrl, wchar_t *normalUrlBuffer, INT32 bufferLen);
        BOOL GetFileSizeWithUrl(const wchar_t * lpURL, INT64& iFileSize);
        BOOL SetFileIdAndSize(HANDLE hTask, char szFileId[40], unsigned __int64 nFileSize);
        BOOL SetAdditionInfo(HANDLE task_id, WSAPROTOCOL_INFOW *sock_info, CHAR *http_resp_buf, LONG buf_len);
        HANDLE CreateTaskByURL(const wchar_t *url, const wchar_t *path, const wchar_t *fileName, BOOL IsResume);
        LONG CreateTaskByThunder(wchar_t *pszUrl, wchar_t *pszFileName, wchar_t *pszReferUrl, wchar_t *pszCharSet, wchar_t *pszCookie);
        LONG CreateBTTaskByThunder(const wchar_t *pszPath);
        DownTaskParam CreateDownTaskParam(const wchar_t TaskUrl[], const wchar_t Filename[], const wchar_t SavePath[], BOOL IsResume = TRUE, BOOL IsOnlyOriginal = FALSE, BOOL DisableAutoRename = FALSE);
    private:
        HMODULE                                 m_hModule;
        DEF_DETOUR_FUNC(Init,                   BOOL,       void);
        DEF_DETOUR_FUNC(UnInit,                 BOOL,       void);
        DEF_DETOUR_FUNC(TaskCreate,             HANDLE,     DownTaskParam &stParam);
        DEF_DETOUR_FUNC(TaskDelete,             BOOL,       HANDLE hTask);
        DEF_DETOUR_FUNC(TaskStart,              BOOL,       HANDLE hTask);
        DEF_DETOUR_FUNC(TaskStop,               BOOL,       HANDLE hTask);
        DEF_DETOUR_FUNC(ForceStopTask,          BOOL,       HANDLE hTask);
        DEF_DETOUR_FUNC(QueryTaskInfo,          BOOL,       HANDLE hTask, DownTaskInfo & stTaskInfo);
        DEF_DETOUR_FUNC(QueryTaskInfoEx,        BOOL,       HANDLE hTask, DownTaskInfo & stTaskInfo);
        DEF_DETOUR_FUNC(DelTempFile,            BOOL,       DownTaskParam &stParam);
        DEF_DETOUR_FUNC(SetSpeedLimit,          void,       INT32 nKBps);
        DEF_DETOUR_FUNC(SetUploadSpeedLimit,    void,       INT32 nTcpKBps, INT32 nOtherKBps);
        DEF_DETOUR_FUNC(SetProxy,               BOOL,       DOWN_PROXY_INFO &stProxyInfo);
        DEF_DETOUR_FUNC(SetUserAgent,           void,       const wchar_t *pszUserAgent);
        DEF_DETOUR_FUNC(ParseThunderPrivateUrl, BOOL,       const wchar_t *pszThunderUrl, wchar_t *normalUrlBuffer, INT32 bufferLen);
        DEF_DETOUR_FUNC(GetFileSizeWithUrl,     BOOL,       const wchar_t * lpURL, INT64& iFileSize);
        DEF_DETOUR_FUNC(SetFileIdAndSize,       BOOL,       HANDLE hTask, char szFileId[40], unsigned __int64 nFileSize);
        DEF_DETOUR_FUNC(SetAdditionInfo,        BOOL,       HANDLE task_id, WSAPROTOCOL_INFOW *sock_info, CHAR *http_resp_buf, LONG buf_len);
        DEF_DETOUR_FUNC(CreateTaskByURL,        HANDLE,     const wchar_t *url, const wchar_t *path, const wchar_t *fileName, BOOL IsResume);
        DEF_DETOUR_FUNC(CreateTaskByThunder,    LONG,       wchar_t *pszUrl, wchar_t *pszFileName, wchar_t *pszReferUrl, wchar_t *pszCharSet, wchar_t *pszCookie);
        DEF_DETOUR_FUNC(CreateBTTaskByThunder,  LONG,       const wchar_t *pszPath);
    };
};