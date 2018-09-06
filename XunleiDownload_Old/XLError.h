#pragma once

#define XL_SUCCESS                     0
#define XL_ERROR_FAIL                  0x10000000

// 尚未进行初始化
#define XL_ERROR_UNINITAILIZE          XL_ERROR_FAIL+1

// 不支持的协议，目前只支持HTTP
#define XL_ERROR_UNSPORTED_PROTOCOL    XL_ERROR_FAIL+2

// 初始化托盘图标失败
#define XL_ERROR_INIT_TASK_TRAY_ICON_FAIL  XL_ERROR_FAIL+3

// 添加托盘图标失败
#define XL_ERROR_ADD_TASK_TRAY_ICON_FAIL   XL_ERROR_FAIL+4

// 指针为空
#define XL_ERROR_POINTER_IS_NULL    XL_ERROR_FAIL+5

// 字符串是空串
#define XL_ERROR_STRING_IS_EMPTY    XL_ERROR_FAIL+6

// 传入的路径没有包含文件名
#define XL_ERROR_PATH_DONT_INCLUDE_FILENAME    XL_ERROR_FAIL+7

// 创建目录失败
#define XL_ERROR_CREATE_DIRECTORY_FAIL    XL_ERROR_FAIL+8

// 内存不足
#define XL_ERROR_MEMORY_ISNT_ENOUGH    XL_ERROR_FAIL+9

// 参数不合法
#define XL_ERROR_INVALID_ARG    XL_ERROR_FAIL+10

// 任务不存在
#define XL_ERROR_TASK_DONT_EXIST    XL_ERROR_FAIL+11

// 文件名不合法
#define XL_ERROR_FILE_NAME_INVALID   XL_ERROR_FAIL+12

// 没有实现
#define XL_ERROR_NOTIMPL    XL_ERROR_FAIL+13

// 已经创建的任务数达到最大任务数，无法继续创建任务
#define XL_ERROR_TASKNUM_EXCEED_MAXNUM    XL_ERROR_FAIL+14

// 任务类型未知
#define XL_ERROR_INVALID_TASK_TYPE    XL_ERROR_FAIL+15

// 文件已经存在
#define XL_ERROR_FILE_ALREADY_EXIST   XL_ERROR_FAIL+16

// 文件不存在
#define XL_ERROR_FILE_DONT_EXIST      XL_ERROR_FAIL+17

// 读取cfg文件失败
#define XL_ERROR_READ_CFG_FILE_FAIL   XL_ERROR_FAIL+18

// 写入cfg文件失败
#define XL_ERROR_WRITE_CFG_FILE_FAIL   XL_ERROR_FAIL+19

// 无法继续任务，可能是不支持断点续传，也有可能是任务已经失败
// 通过查询任务状态，确定错误原因。
#define XL_ERROR_CANNOT_CONTINUE_TASK  XL_ERROR_FAIL+20

// 无法暂停任务，可能是不支持断点续传，也有可能是任务已经失败
// 通过查询任务状态，确定错误原因。
#define XL_ERROR_CANNOT_PAUSE_TASK  XL_ERROR_FAIL+21

// 缓冲区太小
#define XL_ERROR_BUFFER_TOO_SMALL   XL_ERROR_FAIL+22

// 调用XLInitDownloadEngine的线程，在调用XLUninitDownloadEngine之前已经结束。
// 初始化下载引擎线程，在调用XLUninitDownloadEngine之前，必须保持执行状态。
#define XL_ERROR_INIT_THREAD_EXIT_TOO_EARLY XL_ERROR_FAIL+23

// TP崩溃
#define XL_ERROR_TP_CRASH XL_ERROR_FAIL+24

// 任务不合法，调用XLContinueTaskFromTdFile继续任务。内部任务切换失败时，会产生这个错误。
#define XL_ERROR_TASK_INVALID XL_ERROR_FAIL+25
