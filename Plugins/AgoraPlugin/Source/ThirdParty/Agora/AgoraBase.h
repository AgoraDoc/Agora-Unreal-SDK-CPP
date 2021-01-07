//  Agora Engine SDK
//
//  Copyright (c) 2019 Agora.io. All rights reserved.
//

#ifndef AGORA_BASE_H
#define AGORA_BASE_H

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define AGORA_CALL __cdecl
#if defined(AGORARTC_EXPORT)
#define AGORA_API extern "C" __declspec(dllexport)
#define AGORA_CPP_API __declspec(dllexport)
#else
#define AGORA_API extern "C" __declspec(dllimport)
#define AGORA_CPP_API __declspec(dllimport)
#endif
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#define AGORA_API __attribute__((visibility("default"))) extern "C"
#define AGORA_CPP_API __attribute__((visibility("default")))
#define AGORA_CALL
#elif defined(__ANDROID__) || defined(__linux__)
#define AGORA_API extern "C" __attribute__((visibility("default")))
#define AGORA_CPP_API __attribute__((visibility("default")))
#define AGORA_CALL
#else
#define AGORA_API extern "C"
#define AGORA_CPP_API
#define AGORA_CALL
#endif

namespace agora {
namespace util {

template<class T>
class AutoPtr {
    typedef T value_type;
    typedef T* pointer_type;
public:
    AutoPtr(pointer_type p=0)
        :ptr_(p)
    {}
    ~AutoPtr() {
        if (ptr_)
            ptr_->release();
    }
    operator bool() const { return ptr_ != (pointer_type)0; }
    value_type& operator*() const {
        return *get();
    }

    pointer_type operator->() const {
        return get();
    }

    pointer_type get() const {
        return ptr_;
    }

    pointer_type release() {
        pointer_type tmp = ptr_;
        ptr_ = 0;
        return tmp;
    }

    void reset(pointer_type ptr = 0) {
        if (ptr != ptr_ && ptr_)
            ptr_->release();
        ptr_ = ptr;
    }
    template<class C1, class C2>
    bool queryInterface(C1* c, C2 iid) {
        pointer_type p = NULL;
        if (c && !c->queryInterface(iid, (void**)&p))
        {
            reset(p);
        }
        return p != NULL;
	}
private:
    AutoPtr(const AutoPtr&);
    AutoPtr& operator=(const AutoPtr&);
private:
    pointer_type ptr_;
};
class IString {
protected:
    virtual ~IString(){}
public:
    virtual bool empty() const = 0;
    virtual const char* c_str() = 0;
    virtual const char* data() = 0;
    virtual size_t length() = 0;
    virtual void release() = 0;
};
typedef AutoPtr<IString> AString;

}//namespace util

enum INTERFACE_ID_TYPE
{
    AGORA_IID_AUDIO_DEVICE_MANAGER = 1,
    AGORA_IID_VIDEO_DEVICE_MANAGER = 2,
    AGORA_IID_RTC_ENGINE_PARAMETER = 3,
    AGORA_IID_MEDIA_ENGINE = 4,
    AGORA_IID_SIGNALING_ENGINE = 8,
};
/** @~chinese
警告代码

警告代码意味着 SDK 遇到问题，但有可能恢复，警告代码仅起告知作用，一般情况下应用程序可以忽略警告代码。

*/
/** @~english Warning code.
 */
enum WARN_CODE_TYPE
{
  /** @~chinese
   8: 指定的 view 无效，使用视频功能时需要指定 view，如果 view 尚未指定，则返回该警告。
  */
  /** @~english 8: The specified view is invalid. Specify a view when using the video call function.
  */
    WARN_INVALID_VIEW = 8,
    /** @~chinese 16: 初始化视频功能失败。有可能是因视频资源被占用导致的。用户无法看到视频画面，但不影响语音通信。
    */
    /** @~english 16: Failed to initialize the video function, possibly caused by a lack of resources. The users cannot see the video while the voice communication is not affected.
    */
    WARN_INIT_VIDEO = 16,
    /** @~chinese 20: 请求处于待定状态。一般是由于某个模块还没准备好，请求被延迟处理。
    */
    /** @~english 20: The request is pending, usually due to some module not being ready, and the SDK postponed processing the request.
    */
    WARN_PENDING = 20,
    /** @~chinese 103: 没有可用的频道资源。可能是因为服务端没法分配频道资源。
    */
    /** @~english 103: No channel resources are available. Maybe because the server cannot allocate any channel resource.
    */
    WARN_NO_AVAILABLE_CHANNEL = 103,
    /** @~chinese 104: 查找频道超时。在加入频道时 SDK 先要查找指定的频道，出现该警告一般是因为网络太差，连接不到服务器。
    */
    /** @~english 104: A timeout occurs when looking up the channel. When joining a channel, the SDK looks up the specified channel. This warning usually occurs when the network condition is too poor for the SDK to connect to the server.
    */
    WARN_LOOKUP_CHANNEL_TIMEOUT = 104,
    /** @~chinese
     **已废弃** 105: 查找频道请求被服务器拒绝。服务器可能没有办法处理这个请求或请求是非法的。从 v2.4.1 起废弃。请改用 \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" 回调中的 CONNECTION_CHANGED_REJECTED_BY_SERVER(10)。
     */
    /** @~english **DEPRECATED** 105: The server rejects the request to look up the channel. The server cannot process this request or the request is illegal.
     
     Deprecated as of v2.4.1. Use CONNECTION_CHANGED_REJECTED_BY_SERVER(10) in the \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback instead.
    */
    WARN_LOOKUP_CHANNEL_REJECTED = 105,
    /** @~chinese 106: 打开频道超时。查找到指定频道后，SDK 接着打开该频道，超时一般是因为网络太差，连接不到服务器。
    */
    /** @~english 106: A timeout occurs when opening the channel. Once the specific channel is found, the SDK opens the channel. This warning usually occurs when the network condition is too poor for the SDK to connect to the server.
    */
    WARN_OPEN_CHANNEL_TIMEOUT = 106,
    /** @~chinese 107: 打开频道请求被服务器拒绝。服务器可能没有办法处理该请求或该请求是非法的。
    */
    /** @~english 107: The server rejects the request to open the channel. The server cannot process this request or the request is illegal.
    */
    WARN_OPEN_CHANNEL_REJECTED = 107,

    // sdk: 100~1000
    /** @~chinese 111: 切换直播视频超时。
    */
    /** @~english 111: A timeout occurs when switching to the live video.
    */
    WARN_SWITCH_LIVE_VIDEO_TIMEOUT = 111,
    /** @~chinese 118: 直播场景下设置用户角色超时。
    */
    /** @~english 118: A timeout occurs when setting the client role in the live broadcast profile.
    */
    WARN_SET_CLIENT_ROLE_TIMEOUT = 118,
    /** @~chinese 121: TICKET 非法，打开频道失败。
    */
    /** @~english 121: The ticket to open the channel is invalid.
    */
    WARN_OPEN_CHANNEL_INVALID_TICKET = 121,
    /** @~chinese 122: 尝试打开另一个服务器。
    */
    /** @~english 122: Try connecting to another server.
    */
    WARN_OPEN_CHANNEL_TRY_NEXT_VOS = 122,
    /** @~chinese 131: 频道连接不可恢复。
     */
    /** @~english 131: The channel connection cannot be recovered. */
    WARN_CHANNEL_CONNECTION_UNRECOVERABLE = 131,
    /** @~chinese 132: IP 已改变。
     */
    /** @~english 132: The IP address has changed. */
    WARN_CHANNEL_CONNECTION_IP_CHANGED = 132,
    /** @~chinese 133: 端口已改变。
     */
    /** @~english 133: The port has changed. */
    WARN_CHANNEL_CONNECTION_PORT_CHANGED = 133,
    /** @~chinese 701: 打开伴奏出错。
    */
    /** @~english 701: An error occurs in opening the audio mixing file.
    */
    WARN_AUDIO_MIXING_OPEN_ERROR = 701,
    /** @~chinese 1014: 音频设备模块：运行时播放设备出现警告。
    */
    /** @~english 1014: Audio Device Module: a warning occurs in the playback device.
    */
    WARN_ADM_RUNTIME_PLAYOUT_WARNING = 1014,
    /** @~chinese 1016: 音频设备模块：运行时音频采集设备出现警告。
    */
    /** @~english 1016: Audio Device Module: a warning occurs in the recording device.
    */
    WARN_ADM_RUNTIME_RECORDING_WARNING = 1016,
    /** @~chinese 1019: 音频设备模块：没有采集到有效的声音数据。
    */
    /** @~english 1019: Audio Device Module: no valid audio data is collected.
    */
    WARN_ADM_RECORD_AUDIO_SILENCE = 1019,
    /** @~chinese 1020: 音频设备模块：播放频率异常，可能造成音频卡顿。该异常原因为系统 CPU 占用率高，建议结束其他可能占用 CPU 的 app。
    */
    /** @~english 1020: Audio Device Module: the playback device fails.
    */
    WARN_ADM_PLAYOUT_MALFUNCTION = 1020,
    /** @~chinese 1021: 音频设备模块：采集频率异常，可能造成音频卡顿。该异常原因为系统 CPU 占用率高，建议结束其他可能占用 CPU 的 app。
    */
    /** @~english 1021: Audio Device Module: the recording device fails.
    */
    WARN_ADM_RECORD_MALFUNCTION = 1021,
    /** @~chinese 1025: 播放或采集音频时被系统事件（如来电）干扰。
    */
    /** @~english 1025: The audio playback or recording is interrupted by system events (such as a phone call).
    */
    WARN_ADM_CALL_INTERRUPTION = 1025,
    /** @~chinese 1029：在通话过程中，Audio Session 的 category 必须设置成 AVAudioSessionCategoryPlayAndRecord，RtcEngine 会监控这个属性值。当这个值被修改成其他值的时候会触发这个告警，并强制设置回 AVAudioSessionCategoryPlayAndRecord。
    */
    /** @~english 1029: During a call, the audio session category should be set to
     * AVAudioSessionCategoryPlayAndRecord, and RtcEngine monitors this value.
     * If the audio session category is set to other values, this warning code
     * is triggered and RtcEngine will forcefully set it back to
     * AVAudioSessionCategoryPlayAndRecord.
    */
    WARN_ADM_IOS_CATEGORY_NOT_PLAYANDRECORD = 1029,

    WARN_ADM_IOS_SAMPLERATE_CHANGE = 1030,
    /** @~chinese 1031: 音频设备模块：录到的声音太低。
    */
    /** @~english 1031: Audio Device Module: the recorded audio voice is too low.
    */
    WARN_ADM_RECORD_AUDIO_LOWLEVEL = 1031,
    /** @~chinese 1032: 音频设备模块：播放的声音太低。
    */
    /** @~english 1032: Audio Device Module: the playback audio voice is too low.
    */
    WARN_ADM_PLAYOUT_AUDIO_LOWLEVEL = 1032,
    /** @~chinese 1033: 音频设备模块：采集设备被占用。
    */
    WARN_ADM_RECORD_AUDIO_IS_ACTIVE = 1033,
    /** @~chinese 1040: 音频设备模块：音频驱动异常。解决方案：禁用并重新启用音频设备，或者重启机器，或者更新声卡驱动
     */
    /** @~english 1040: Audio device module: An exception occurs with the audio drive.
     * Solutions:
     * - Disable or re-enable the audio device.
     * - Re-enable your device.
     * - Update the sound card drive.
     */
    WARN_ADM_WINDOWS_NO_DATA_READY_EVENT = 1040,
    /** @~chinese
     * 1042: 音频采集设备和播放设备不一致，可能引起回声，建议使用同一设备采集和播放音频。
     */
    /** @~english 1042: Audio device module: The audio recording device is different from the audio playback device,
     * which may cause echoes problem. Agora recommends using the same audio device to record and playback
     * audio.
     */
    WARN_ADM_INCONSISTENT_AUDIO_DEVICE = 1042,
    /** @~chinese 1051:（仅通信场景）音频信号处理模块：采集音频时监测到啸叫。
    */
    /** @~english 1051: (Communication profile only) audio Processing Module: howling is detected.
    */
    WARN_APM_HOWLING = 1051,
    /** @~chinese 1052: 音频设备模块：音频播放会卡顿。
    */
    /** @~english 1052: Audio Device Module: the device is in the glitch state.
    */
    WARN_ADM_GLITCH_STATE = 1052,
    /** @~chinese 1053: 音频信号处理模块：检测到残余回声，该回声可能由系统线程调度不及时或信号溢出导致。
    */
    /** @~english 1053: Audio Device Module: the underlying audio settings have changed.
    */
    WARN_ADM_IMPROPER_SETTINGS = 1053,
    /// @cond
    WARN_ADM_WIN_CORE_NO_RECORDING_DEVICE = 1322,
    /// @endcond
    /** @~chinese 1323: 音频设备模块：无可用音频播放设备。解决方案：插入音频设备
    */
    /** @~english 1323: Audio device module: No available playback device. 
     * Solution: Plug in the audio device.
    */
    WARN_ADM_WIN_CORE_NO_PLAYOUT_DEVICE = 1323,
    /** @~chinese 1324: 音频设备模块：音频采集释放有误。解决方案：禁用并重新启用音频设备，或者重启机器，或者更新声卡驱动。
     */
    /** @~english Audio device module: The capture device is released improperly. 
     * Solutions: 
     * - Disable or re-enable the audio device.
     * - Re-enable your device.
     * - Update the sound card drive.
     */
    WARN_ADM_WIN_CORE_IMPROPER_CAPTURE_RELEASE = 1324,
    /** @~chinese 1610: 超分告警：远端用户的原始视频流的分辨率超出了可以应用超分辨率算法的要求。
     */
    /** @~english 1610: Super-resolution warning: the original video dimensions of the remote user exceed 640 * 480.
    */
    WARN_SUPER_RESOLUTION_STREAM_OVER_LIMITATION = 1610,
    /** @~chinese 1611: 超分告警：已指定一个远端用户使用超分辨率算法。
     */
    /** @~english 1611: Super-resolution warning: another user is using super resolution.
    */
    WARN_SUPER_RESOLUTION_USER_COUNT_OVER_LIMITATION = 1611,
    /** @~chinese 1612: 超分告警：当前设备不支持超分算法。
     */
    /** @~english 1612: The device is not supported.
    */
    WARN_SUPER_RESOLUTION_DEVICE_NOT_SUPPORTED = 1612,
    /// @cond
    WARN_RTM_LOGIN_TIMEOUT = 2005,
    WARN_RTM_KEEP_ALIVE_TIMEOUT = 2009
    /// @endcond
};
/** @~chinese 错误代码

错误代码意味着 SDK 遇到不可恢复的错误，需要应用程序干预，例如打开摄像头失败会返回错误，应用程序需要提示用户不能使用摄像头。

*/
/** @~english Error code.
*/
enum ERROR_CODE_TYPE
{
  /** @~chinese 0: 没有错误。
  */
  /** @~english 0: No error occurs.
  */
    ERR_OK = 0,
    //1~1000
    /** @~chinese 1: 一般性的错误（没有明确归类的错误原因）。
    */
    /** @~english 1: A general error occurs (no specified reason).
    */
    ERR_FAILED = 1,
    /** @~chinese 2: API 调用了无效的参数。例如指定的频道名含有非法字符。
    */
    /** @~english 2: An invalid parameter is used. For example, the specific channel name includes illegal characters.
    */
    ERR_INVALID_ARGUMENT = 2,
    /** @~chinese 3: RTC 引擎初始化失败。处理方法：

     - 检查音频设备状态。
     - 检查程序集完整性。
     - 尝试重新初始化 RTC 引擎。
    */
    /** @~english 3: The SDK module is not ready. Possible solutions:

     - Check the audio device.
     - Check the completeness of the application.
     - Re-initialize the RTC engine.
     */
    ERR_NOT_READY = 3,
    /** @~chinese 4: RTC 引擎当前状态不支持此项操作。
    */
    /** @~english 4: The SDK does not support this function.
     */
    ERR_NOT_SUPPORTED = 4,
    /** @~chinese 5: 调用被拒绝。
    */
    /** @~english 5: The request is rejected.
     */
    ERR_REFUSED = 5,
    /** @~chinese 6: 传入的缓冲区大小不足以存放返回的数据。
    */
    /** @~english 6: The buffer size is not big enough to store the returned data.
     */
    ERR_BUFFER_TOO_SMALL = 6,
    /** @~chinese 7: SDK 尚未初始化，就调用其 API。请确认在调用 API 之前已创建 RtcEngine 对象并完成初始化。
    */
    /** @~english 7: The SDK is not initialized before calling this method.
     */
    ERR_NOT_INITIALIZED = 7,
    /** @~chinese 9: 没有操作权限，请检查用户是否授予 app 音视频设备使用权限。
    */
    /** @~english 9: No permission exists. Check if the user has granted access to the audio or video device.
     */
    ERR_NO_PERMISSION = 9,
    /** @~chinese 10: API 调用超时。有些 API 调用需要 SDK 返回结果，如果 SDK 处理事件过长，超过 10 秒没有返回，会出现此错误。
    */
    /** @~english 10: An API method timeout occurs. Some API methods require the SDK to return the execution result, and this error occurs if the request takes too long (more than 10 seconds) for the SDK to process.
     */
    ERR_TIMEDOUT = 10,
    /** @~chinese 11: 请求被取消。仅供 SDK 内部使用，不通过 API 或者回调事件返回给 App。
    */
    /** @~english 11: The request is canceled. This is for internal SDK use only, and it does not return to the application through any method or callback.
     */
    ERR_CANCELED = 11,
    /** @~chinese 12: 调用频率太高。仅供 SDK 内部使用，不通过 API 或者回调事件返回给 App。
    */
    /** @~english 12: The method is called too often. This is for internal SDK use only, and it does not return to the application through any method or callback.
     */
    ERR_TOO_OFTEN = 12,
    /** @~chinese 13: SDK 内部绑定到网络 Socket 失败。仅供 SDK 内部使用，不通过 API 或者回调事件返回给 App。
    */
    /** @~english 13: The SDK fails to bind to the network socket. This is for internal SDK use only, and it does not return to the application through any method or callback.
     */
    ERR_BIND_SOCKET = 13,
    /** @~chinese 14: 网络不可用。仅供 SDK 内部使用，不通过 API 或者回调事件返回给 App。
    */
    /** @~english 14: The network is unavailable. This is for internal SDK use only, and it does not return to the application through any method or callback.
     */
    ERR_NET_DOWN = 14,
    /** @~chinese 15: 没有网络缓冲区可用。仅供 SDK 内部使用，不通过 API 或者回调事件返回给 App。
    */
    /** @~english 15: No network buffers are available. This is for internal SDK internal use only, and it does not return to the application through any method or callback.
     */
    ERR_NET_NOBUFS = 15,
    /** @~chinese 17: 加入频道被拒绝。一般有以下原因：

     - 用户已进入频道，再次调用加入频道的 API，例如 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" ，
     会返回此错误。停止调用该方法即可。
     - 用户在调用 \ref agora::rtc::IRtcEngine::startEchoTest "startEchoTest" 进行通话测试时，尝试加入频道。通话测试开始后，
     需要先调用 \ref agora::rtc::IRtcEngine::stopEchoTest "stopEchoTest" 结束当前测试，再加入频道。
     - 使用已过期的 Token 调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 时也会返回此错误。请使用有效的 Token 重新加入频道。
     */
    /** @~english 17: The request to join the channel is rejected. This error usually occurs when the user is already in the channel, and still calls the method to join the channel, for example, \ref agora::rtc::IRtcEngine::joinChannel "joinChannel".
     */
    ERR_JOIN_CHANNEL_REJECTED = 17,
    /** @~chinese 18: 离开频道失败。一般有以下原因：

     - 用户已离开频道，再次调用退出频道的 API，例如 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" ，会返回此错误。停止调用该方法即可。
     - 用户尚未加入频道，就调用退出频道的 API。这种情况下无需额外操作。
     */
    /** @~english 18: The request to leave the channel is rejected.

     This error usually occurs:

     - When the user has left the channel and still calls \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" to leave the channel. In this case, stop calling \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel".
     - When the user has not joined the channel and still calls \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" to leave the channel. In this case, no extra operation is needed.
     */
    ERR_LEAVE_CHANNEL_REJECTED = 18,
    /** @~chinese 19: 资源已被占用，不能重复使用。
    */
    /** @~english 19: Resources are occupied and cannot be reused.
     */
    ERR_ALREADY_IN_USE = 19,
    /** @~chinese 20: SDK 放弃请求，可能由于请求次数太多。
    */
    /** @~english 20: The SDK gives up the request due to too many requests.
     */
    ERR_ABORTED = 20,
    /** @~chinese 21: Windows 下特定的防火墙设置导致 SDK 初始化失败然后崩溃。
    */
    /** @~english 21: In Windows, specific firewall settings can cause the SDK to fail to initialize and crash.
     */
    ERR_INIT_NET_ENGINE = 21,
    /** @~chinese 22: 当用户 App 占用资源过多，或系统资源耗尽时，SDK 分配资源失败会返回该错误。
    */
    /** @~english 22: The application uses too much of the system resources and the SDK fails to allocate the resources.
     */
    ERR_RESOURCE_LIMITED = 22,
    /** @~chinese 101: 不是有效的 App ID。请更换有效的 App ID 重新加入频道。
    */
    /** @~english 101: The specified App ID is invalid. Please try to rejoin the channel with a valid App ID.
     */
    ERR_INVALID_APP_ID = 101,
    /** @~chinese 102: 不是有效的频道名。请更换有效的频道名重新加入频道。
    */
    /** @~english 102: The specified channel name is invalid. Please try to rejoin the channel with a valid channel name.
     */
    ERR_INVALID_CHANNEL_NAME = 102,
    /** @~chinese
     **DEPRECATED** 109: 从 v2.4.1 起废弃。请改用 \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" 回调中的 CONNECTION_CHANGED_TOKEN_EXPIRED(9)。

     当前使用的 Token 过期，不再有效。一般有以下原因：

     - Token 授权时间戳无效：Token 授权时间戳为 Token 生成时的时间戳，自 1970 年 1 月 1 日开始到当前时间的描述。授权该 Token 在生成后的 24 小时内可以访问 Agora 服务。如果 24 小时内没有访问，则该 Token 无法再使用。需要重新在服务端申请生成 Token。
     - Token 服务到期时间戳已过期：用户设置的服务到期时间戳小于当前时间戳，无法继续使用 Agora 服务（比如正在进行的通话会被强制终止）；设置服务到期时间并不意味着 Token 失效，而仅仅用于限制用户使用当前服务的时间。需要重新在服务端申请生成 Token。
     */
    /** @~english **DEPRECATED** 109: Deprecated as of v2.4.1. Use CONNECTION_CHANGED_TOKEN_EXPIRED(9) in the \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback instead.
     
     The token expired due to one of the following reasons:
     
     - Authorized Timestamp expired: The timestamp is represented by the number of seconds elapsed since 1/1/1970. The user can use the Token to access the Agora service within 24 hours after the Token is generated. If the user does not access the Agora service after 24 hours, this Token is no longer valid.
     - Call Expiration Timestamp expired: The timestamp is the exact time when a user can no longer use the Agora service (for example, when a user is forced to leave an ongoing call). When a value is set for the Call Expiration Timestamp, it does not mean that the token will expire, but that the user will be banned from the channel.
     */
    ERR_TOKEN_EXPIRED = 109,
    /** @~chinese
     **DEPRECATED** 110: 从 v2.4.1 起废弃。请改用 \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" 回调中的 CONNECTION_CHANGED_INVALID_TOKEN(8)。

     生成的 Token 无效，一般有以下原因：

     - 用户在控制台上启用了 App Certificate，但仍旧在代码里仅使用了 App ID。当启用了 App Certificate，必须使用 Token。
     - 字段 `uid` 为生成 Token 的必须字段，用户在调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 加入频道时必须设置相同的 `uid`。
     */
    /** @~english **DEPRECATED** 110: Deprecated as of v2.4.1. Use CONNECTION_CHANGED_INVALID_TOKEN(8) in the \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback instead.
     
     The token is invalid due to one of the following reasons:
     
     - The App Certificate for the project is enabled in Console, but the user is still using the App ID. Once the App Certificate is enabled, the user must use a token.
     - The uid is mandatory, and users must set the same uid as the one set in the \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" method.
     */
    ERR_INVALID_TOKEN = 110,
    /** @~chinese 111: 网络连接中断。仅适用于 Agora Web SDK。
    */
    /** @~english 111: The internet connection is interrupted. This applies to the Agora Web SDK only.
     */
    ERR_CONNECTION_INTERRUPTED = 111, // only used in web sdk
    /** @~chinese 112: 网络连接丢失。仅适用于 Agora Web SDK。
    */
    /** @~english 112: The internet connection is lost. This applies to the Agora Web SDK only.
     */
    ERR_CONNECTION_LOST = 112, // only used in web sdk
    /** @~chinese 113: 用户不在频道内。
    */
    /** @~english 113: The user is not in the channel when calling the \ref agora::rtc::IRtcEngine::sendStreamMessage "sendStreamMessage" or \ref agora::rtc::IRtcEngine::getUserInfoByUserAccount "getUserInfoByUserAccount" method.
     */
    ERR_NOT_IN_CHANNEL = 113,
    /** @~chinese 114: 在调用 \ref agora::rtc::IRtcEngine::sendStreamMessage "sendStreamMessage" 时，当发送的数据长度大于 1024 个字节时，会发生该错误。
    */
    /** @~english 114: The size of the sent data is over 1024 bytes when the user calls the \ref agora::rtc::IRtcEngine::sendStreamMessage "sendStreamMessage" method.
     */
    ERR_SIZE_TOO_LARGE = 114,
    /** @~chinese 115: 在调用 \ref agora::rtc::IRtcEngine::sendStreamMessage "sendStreamMessage" 时，当发送的数据频率超过限制时（6 KB/s），会发生该错误。
    */
    /** @~english 115: The bitrate of the sent data exceeds the limit of 6 Kbps when the user calls the \ref agora::rtc::IRtcEngine::sendStreamMessage "sendStreamMessage" method.
     */
    ERR_BITRATE_LIMIT = 115,
    /** @~chinese 116: 在调用 \ref agora::rtc::IRtcEngine::createDataStream "createDataStream" 时，如果创建的数据通道过多（超过 5 个通道），会发生该错误。
    */
    /** @~english 116: Too many data streams (over 5 streams) are created when the user calls the \ref agora::rtc::IRtcEngine::createDataStream "createDataStream" method.
     */
    ERR_TOO_MANY_DATA_STREAMS = 116,
    /** @~chinese 117: 数据流发送超时。
    */
    /** @~english 117: The data stream transmission timed out.
     */
    ERR_STREAM_MESSAGE_TIMEOUT = 117,
    /** @~chinese 119: 切换角色失败。请尝试重新加入频道。
    */
    /** @~english 119: Switching roles fail. Please try to rejoin the channel.
     */
    ERR_SET_CLIENT_ROLE_NOT_AUTHORIZED = 119,
    /** @~chinese 120: 解密失败，可能是用户加入频道用了不同的密码。请检查加入频道时的设置，或尝试重新加入频道。
    */
    /** @~english 120: Decryption fails. The user may have used a different encryption password to join the channel. Check your settings or try rejoining the channel.
     */
    ERR_DECRYPTION_FAILED = 120,
    /** @~chinese 123: 此用户被服务器禁止。服务端踢人场景时会报这个错。
    */
    /** @~english 123: The client is banned by the server.
     */
    ERR_CLIENT_IS_BANNED_BY_SERVER = 123,
    /** @~chinese 124: 水印文件参数错误。
    */
    /** @~english 124: Incorrect watermark file parameter.
     */
    ERR_WATERMARK_PARAM = 124,
    /** @~chinese 125: 水印文件路径错误。
    */
    /** @~english 125: Incorrect watermark file path.
     */
    ERR_WATERMARK_PATH = 125,
    /** @~chinese 126: 水印文件格式错误。
    */
    /** @~english 126: Incorrect watermark file format.
     */
    ERR_WATERMARK_PNG = 126,
    /** @~chinese 127: 水印文件信息错误。
    */
    /** @~english 127: Incorrect watermark file information.
     */
    ERR_WATERMARKR_INFO = 127,c
    /** @~chinese 128: 水印文件数据格式错误。
    */
    /** @~english 128: Incorrect watermark file data format.
     */
    ERR_WATERMARK_ARGB = 128,
    /** @~chinese 129: 水印文件读取错误。
    */
    /** @~english 129: An error occurs in reading the watermark file.
     */
    ERR_WATERMARK_READ = 129,
    /** @~chinese 130: 在调用 \ref agora::rtc::IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" 时，如果开启了加密，则会返回该错误(推流不支持加密流)。
    */
    /** @~english 130: Encryption is enabled when the user calls the \ref agora::rtc::IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" method (CDN live streaming does not support encrypted streams).
     */
    ERR_ENCRYPTED_STREAM_NOT_ALLOWED_PUBLISH = 130,
    /** @~chinese 134: 无效的 User account. */
    /** @~english 134: The user account is invalid. */
    ERR_INVALID_USER_ACCOUNT = 134,
    /** @~chinese 151: CDN 相关错误。请调用 \ref agora::rtc::IRtcEngine::removePublishStreamUrl "removePublishStreamUrl" 方法删除原来的推流地址，然后调用 \ref agora::rtc::IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" 方法重新推流到新地址。
     */
    /** @~english 151: CDN related errors. Remove the original URL address and add a new one by calling the \ref agora::rtc::IRtcEngine::removePublishStreamUrl "removePublishStreamUrl" and \ref agora::rtc::IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" methods.
     */
    ERR_PUBLISH_STREAM_CDN_ERROR = 151,
    /** @~chinese 152: 单个主播的推流地址数目达到上限 10。请删掉一些不用的推流地址再增加推流地址。
     */
    /** @~english 152: The host publishes more than 10 URLs. Delete the unnecessary URLs before adding new ones.
     */
    ERR_PUBLISH_STREAM_NUM_REACH_LIMIT = 152,
    /** @~chinese 153: 操作不属于主播自己的流，如更新其他主播的流参数、停止其他主播的流。请检查 App 逻辑。
     */
    /** @~english 153: The host manipulates other hosts' URLs. Check your app logic.
     */
    ERR_PUBLISH_STREAM_NOT_AUTHORIZED = 153,
    /** @~chinese 154: 推流服务器出现错误。请调用 \ref agora::rtc::IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" 重新推流
     */
    /** @~english 154: An error occurs in Agora's streaming server. Call the addPublishStreamUrl method to publish the streaming again.
     */
    ERR_PUBLISH_STREAM_INTERNAL_SERVER_ERROR = 154,
    /** @~chinese 155: 服务器无法找到数据流。
     */
    /** @~english 155: The server fails to find the stream.
     */
    ERR_PUBLISH_STREAM_NOT_FOUND = 155,
    /** @~chinese 156: 推流地址格式有错误。请检查推流地址格式是否正确
     */
    /** @~english 156: The format of the RTMP stream URL is not supported. Check whether the URL format is correct.
     */
    ERR_PUBLISH_STREAM_FORMAT_NOT_SUPPORTED = 156,

    //signaling: 400~600
    ERR_LOGOUT_OTHER = 400,  //
    ERR_LOGOUT_USER = 401,  // logout by user
    ERR_LOGOUT_NET = 402,  // network failure
    ERR_LOGOUT_KICKED = 403,  // login in other device
    ERR_LOGOUT_PACKET = 404,  //
    ERR_LOGOUT_TOKEN_EXPIRED = 405,  // token expired
    ERR_LOGOUT_OLDVERSION = 406,  //
    ERR_LOGOUT_TOKEN_WRONG = 407,
    ERR_LOGOUT_ALREADY_LOGOUT = 408,
    ERR_LOGIN_OTHER = 420,
    ERR_LOGIN_NET = 421,
    ERR_LOGIN_FAILED = 422,
    ERR_LOGIN_CANCELED = 423,
    ERR_LOGIN_TOKEN_EXPIRED = 424,
    ERR_LOGIN_OLD_VERSION = 425,
    ERR_LOGIN_TOKEN_WRONG = 426,
    ERR_LOGIN_TOKEN_KICKED = 427,
    ERR_LOGIN_ALREADY_LOGIN = 428,
    ERR_JOIN_CHANNEL_OTHER = 440,
    ERR_SEND_MESSAGE_OTHER = 440,
    ERR_SEND_MESSAGE_TIMEOUT = 441,
    ERR_QUERY_USERNUM_OTHER = 450,
    ERR_QUERY_USERNUM_TIMEOUT = 451,
    ERR_QUERY_USERNUM_BYUSER = 452,
    ERR_LEAVE_CHANNEL_OTHER = 460,
    ERR_LEAVE_CHANNEL_KICKED = 461,
    ERR_LEAVE_CHANNEL_BYUSER = 462,
    ERR_LEAVE_CHANNEL_LOGOUT = 463,
    ERR_LEAVE_CHANNEL_DISCONNECTED = 464,
    ERR_INVITE_OTHER = 470,
    ERR_INVITE_REINVITE = 471,
    ERR_INVITE_NET = 472,
    ERR_INVITE_PEER_OFFLINE = 473,
    ERR_INVITE_TIMEOUT = 474,
    ERR_INVITE_CANT_RECV = 475,


    //1001~2000
    /** @~chinese 1001: 加载媒体引擎失败。
    */
    /** @~english 1001: Fails to load the media engine.
     */
    ERR_LOAD_MEDIA_ENGINE = 1001,
    /** @~chinese 1002: 启动媒体引擎开始通话失败。请尝试重新进入频道。
    */
    /** @~english 1002: Fails to start the call after enabling the media engine.
     */
    ERR_START_CALL = 1002,
    /** @~chinese

     **已废弃** 1003: 请改用 \ref agora::rtc::IRtcEngineEventHandler::onLocalVideoStateChanged "onLocalVideoStateChanged" 回调中的 LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE(4)。

     启动摄像头失败，请检查摄像头是否被其他应用占用，或者尝试重新进入频道。
     */
    /** @~english **DEPRECATED** 1003: Fails to start the camera.

    Deprecated as of v2.4.1. Use LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE(4) in the \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback instead.
     */
    ERR_START_CAMERA = 1003,
    /** @~chinese 1004: 启动视频渲染模块失败。
    */
    /** @~english 1004: Fails to start the video rendering module.
     */
    ERR_START_VIDEO_RENDER = 1004,
    /** @~chinese 1005: 音频设备模块：音频设备出现错误（未明确指明为何种错误）。请检查音频设备是否被其他应用占用，或者尝试重新进入频道。
    */
    /** @~english 1005: A general error occurs in the Audio Device Module (no specified reason). Check if the audio device is used by another application, or try rejoining the channel.
     */
    ERR_ADM_GENERAL_ERROR = 1005,
    /** @~chinese 1006: 音频设备模块：使用 Java 资源出现错误。
    */
    /** @~english 1006: Audio Device Module: An error occurs in using the Java resources.
     */
    ERR_ADM_JAVA_RESOURCE = 1006,
    /** @~chinese 1007: 音频设备模块：设置的采样频率出现错误。
    */
    /** @~english 1007: Audio Device Module: An error occurs in setting the sampling frequency.
     */
    ERR_ADM_SAMPLE_RATE = 1007,
    /** @~chinese 1008: 音频设备模块：初始化播放设备出现错误。请检查播放设备是否被其他应用占用，或者尝试重新进入频道。
    */
    /** @~english 1008: Audio Device Module: An error occurs in initializing the playback device.
     */
    ERR_ADM_INIT_PLAYOUT = 1008,
    /** @~chinese 1009: 音频设备模块：启动播放设备出现错误。请检查播放设备是否正常，或者尝试重新进入频道。
    */
    /** @~english 1009: Audio Device Module: An error occurs in starting the playback device.
     */
    ERR_ADM_START_PLAYOUT = 1009,
    /** @~chinese 1010: 音频设备模块：停止播放设备出现错误。
    */
    /** @~english 1010: Audio Device Module: An error occurs in stopping the playback device.
     */
    ERR_ADM_STOP_PLAYOUT = 1010,
    /** @~chinese 1011: 音频设备模块：初始化音频采集设备时出现错误。请检查音频采集设备是否正常，或者尝试重新进入频道。
    */
    /** @~english 1011: Audio Device Module: An error occurs in initializing the recording device.
     */
    ERR_ADM_INIT_RECORDING = 1011,
    /** @~chinese 1012: 音频设备模块：启动音频采集设备出现错误。请检查音频采集设备是否正常，或者尝试重新进入频道。
    */
    /** @~english 1012: Audio Device Module: An error occurs in starting the recording device.
     */
    ERR_ADM_START_RECORDING = 1012,
    /** @~chinese 1013: 音频设备模块：停止音频采集设备出现错误。
    */
    /** @~english 1013: Audio Device Module: An error occurs in stopping the recording device.
     */
    ERR_ADM_STOP_RECORDING = 1013,
    /** @~chinese 1015: 音频设备模块：运行时播放出现错误。请检查播放设备是否正常，或者尝试重新进入频道。
    */
    /** @~english 1015: Audio Device Module: A playback error occurs. Check your playback device and try rejoining the channel.
     */
    ERR_ADM_RUNTIME_PLAYOUT_ERROR = 1015,
    /** @~chinese 1017: 音频设备模块：运行时采集音频错误。请检查音频采集设备是否正常，或者尝试重新进入频道。
    */
    /** @~english 1017: Audio Device Module: A recording error occurs.
     */
    ERR_ADM_RUNTIME_RECORDING_ERROR = 1017,
    /** @~chinese 1018: 音频设备模块：采集音频失败。
    */
    /** @~english 1018: Audio Device Module: Fails to record.
     */
    ERR_ADM_RECORD_AUDIO_FAILED = 1018,
    /** @~chinese 1022: 音频设备模块：初始化 Loopback 设备错误。
    */
    /** @~english 1022: Audio Device Module: An error occurs in initializing the 
     * loopback device.
     */
    ERR_ADM_INIT_LOOPBACK = 1022,
    /** @~chinese 1023: 音频设备模块：启动 Loopback 设备错误。
    */
    /** @~english 1023: Audio Device Module: An error occurs in starting the loopback 
     * device.
     */
    ERR_ADM_START_LOOPBACK = 1023,
    /** @~chinese 1027: 音频设备模块：没有录音权限。请检查是否已经打开权限允许录音。
     */
    /** @~english 1027: Audio Device Module: No recording permission exists. Check if the
     *  recording permission is granted.
     */
    ERR_ADM_NO_PERMISSION = 1027,
    /** @~chinese 1033: 音频设备模块：采集设备被占用。
     */
    /** @~english 1033: Audio device module: The device is occupied. 
    */
    ERR_ADM_RECORD_AUDIO_IS_ACTIVE = 1033,
    /** @~chinese 1101: 音频设备模块：严重异常。
     */
    /** @~english 1101: Audio device module: A fatal exception occurs.
    */
    ERR_ADM_ANDROID_JNI_JAVA_RESOURCE = 1101,
    /** @~chinese 1108: 音频设备模块：采集频率低于 50，常见为 0，即采集未启动，建议检查录音权限。
     */
    /** @~english 1108: Audio device module: The recording frequency is lower than 50. 
     * 0 indicates that the recording is not yet started. We recommend 
     * checking your recording permission.
    */
    ERR_ADM_ANDROID_JNI_NO_RECORD_FREQUENCY = 1108,
    /** @~chinese 1109: 音频设备模块：播放频率低于 50，常见为 0，即播放未启动，建议检查是否 AudioTrack 实例过多。
     */
    /** @~english 1109: The playback frequency is lower than 50. 0 indicates that the 
     * playback is not yet started. We recommend checking if you have created 
     * too many AudioTrack instances. 
    */
    ERR_ADM_ANDROID_JNI_NO_PLAYBACK_FREQUENCY = 1109,
    /** @~chinese 1111: 音频设备模块：AudioRecord 启动失败，系统 ROM 报错，建议重启 App 或重启手机、检查录音权限。
     */
    /** @~english 1111: Audio device module: AudioRecord fails to start up. A ROM system 
     * error occurs. We recommend the following options to debug: 
     * - Restart your App.
     * - Restart your cellphone. 
     * - Check your recording permission.
     */
    ERR_ADM_ANDROID_JNI_JAVA_START_RECORD = 1111,
    /** @~chinese 1112: 音频设备模块：AudioTrack 启动失败，系统 ROM 报错，建议重启 App 或重启手机、检查播放权限。
     */
    /** @~english 1112: Audio device module: AudioTrack fails to start up. A ROM system 
     * error occurs. We recommend the following options to debug: 
     * - Restart your App.
     * - Restart your cellphone. 
     * - Check your playback permission.
    */
    ERR_ADM_ANDROID_JNI_JAVA_START_PLAYBACK = 1112,
    /** @~chinese 1115: 音频设备模块：AudioRecord 数据返回错误、SDK 会自动处理、重启 AudioRecord。
     */
    /** @~english 1115: Audio device module: AudioRecord returns error. The SDK will 
     * automatically restart AudioRecord. */
    ERR_ADM_ANDROID_JNI_JAVA_RECORD_ERROR = 1115,
    /** **DEPRECATED** */
    ERR_ADM_ANDROID_OPENSL_CREATE_ENGINE = 1151,
    /** **DEPRECATED** */
    ERR_ADM_ANDROID_OPENSL_CREATE_AUDIO_RECORDER = 1153,
    /** **DEPRECATED** */
    ERR_ADM_ANDROID_OPENSL_START_RECORDER_THREAD = 1156,
    /** **DEPRECATED** */
    ERR_ADM_ANDROID_OPENSL_CREATE_AUDIO_PLAYER = 1157,
    /** **DEPRECATED** */
    ERR_ADM_ANDROID_OPENSL_START_PLAYER_THREAD = 1160,
    /** @~chinese 1201: 音频设备模块：当前设备不支持音频输入，可能的原因是 Audio Session 的 category 配置不对或音频输入设备被占用。建议把后台所有 App 杀掉，重新加入频道。
     */
    /** @~english 1201: Audio device module: The current device does not support audio 
     * input, possibly because you have mistakenly configured the audio session
     *  category, or because some other app is occupying the input device. We 
     * recommend terminating all background apps and re-joining the channel. */
    ERR_ADM_IOS_INPUT_NOT_AVAILABLE = 1201,
    /** @~chinese 1206: 音频设备模块：Audio Session 无法被启动。
     */
    /** @~english 1206: Audio device module: Cannot activate the Audio Session.*/
    ERR_ADM_IOS_ACTIVATE_SESSION_FAIL = 1206,
    /** @~chinese 1210: 音频设备模块：初始化音频设备出错。一般出错是因为音频设备的设置参数错误。
     */
    /** @~english 1210: Audio device module: Fails to initialize the audio device, 
     * normally because the audio device parameters are wrongly set.*/
    ERR_ADM_IOS_VPIO_INIT_FAIL = 1210,
    /** @~chinese 1213: 音频设备模块：重新初始化音频设备出错。一般出错是因为音频设备的设置参数错误。
     */
    /** @~english 1213: Audio device module: Fails to re-initialize the audio device, 
     * normally because the audio device parameters are wrongly set.*/
    ERR_ADM_IOS_VPIO_REINIT_FAIL = 1213,
    /** @~chinese 1214: 音频设备模块：重新启动 Audio Unit 出错。一般出错是因为 Audio Session 的 category 设置与 Audio Unit 的设置不兼容。
     */
    /** @~english 1214: Fails to re-start up the Audio Unit, possibly because the audio 
     * session category is not compatible with the settings of the Audio Unit.
    */
    ERR_ADM_IOS_VPIO_RESTART_FAIL = 1214,
    /// @cond
    ERR_ADM_IOS_SET_RENDER_CALLBACK_FAIL = 1219,
    /// @endcond
    /** **DEPRECATED** */
    ERR_ADM_IOS_SESSION_SAMPLERATR_ZERO = 1221,
    /** @~chinese 1301: 音频设备模块：音频驱动异常或者兼容性问题 解决方案：禁用并重新启用音频设备，或者重启机器。
     */
    /** @~english 1301: Audio device module: An audio driver abnomality or a 
     * compatibility issue occurs. Solutions: Disable and restart the audio 
     * device, or reboot the system.*/
    ERR_ADM_WIN_CORE_INIT = 1301,
    /** @~chinese 1303: 音频设备模块：音频驱动异常或者兼容性问题 解决方案：禁用并重新启用音频设备，或者重启机器。
     */
    /** @~english 1303: Audio device module: A recording driver abnomality or a 
     * compatibility issue occurs. Solutions: Disable and restart the audio 
     * device, or reboot the system. */
    ERR_ADM_WIN_CORE_INIT_RECORDING = 1303,
    /** @~chinese 1306: 音频设备模块：音频驱动异常或者兼容性问题 解决方案：禁用并重新启用音频设备，或者重启机器。
     */
    /** @~english 1306: Audio device module: A playout driver abnomality or a 
     * compatibility issue occurs. Solutions: Disable and restart the audio 
     * device, or reboot the system. */
    ERR_ADM_WIN_CORE_INIT_PLAYOUT = 1306,
    /** @~chinese 1307: 音频设备模块：无可用音频设备 解决方案：插入音频设备。
     */
    /** @~english 1307: Audio device module: No audio device is available. Solutions: 
     * Plug in a proper audio device. */
    ERR_ADM_WIN_CORE_INIT_PLAYOUT_NULL = 1307,
    /** @~chinese 1309: 音频设备模块：音频驱动异常或者兼容性问题 解决方案：禁用并重新启用音频设备，或者重启机器。
     */
    /** @~english 1309: Audio device module: An audio driver abnomality or a 
     * compatibility issue occurs. Solutions: Disable and restart the audio 
     * device, or reboot the system. */
    ERR_ADM_WIN_CORE_START_RECORDING = 1309,
    /** @~chinese 1311: 音频设备模块：系统内存不足或者机器性能较差 解决方案：重启机器或者更换机器。
     */
    /** @~english 1311: Audio device module: Insufficient system memory or poor device 
     * performance. Solutions: Reboot the system or replace the device.
    */
    ERR_ADM_WIN_CORE_CREATE_REC_THREAD = 1311,
    /** @~chinese 1314: 音频设备模块：音频驱动异常 解决方案：禁用并重新启用音频设备，或者重启机器，或者更新声卡驱动。
     */
    /** @~english 1314: Audio device module: An audio driver abnormality occurs. 
     * Solutions:
     * - Disable and then re-enable the audio device.
     * - Reboot the system.
     * - Upgrade your audio card driver.*/
    ERR_ADM_WIN_CORE_CAPTURE_NOT_STARTUP = 1314,
    /** @~chinese 1319: 音频设备模块：系统内存不足或者机器性能较差 解决方案：重启机器或者更换机器。
     */
    /** @~english 1319: Audio device module: Insufficient system memory or poor device 
     * performance. Solutions: Reboot the system or replace the device. */
    ERR_ADM_WIN_CORE_CREATE_RENDER_THREAD = 1319,
    /** @~chinese 1320: 音频设备模块：音频驱动异常 解决方案：禁用并重新启用音频设备，或者重启机器，或者更新声卡驱动。
     */
    /** @~english 1320: Audio device module: An audio driver abnormality occurs. 
     * Solutions:
     * - Disable and then re-enable the audio device.
     * - Reboot the system.
     * - Replace the device. */
    ERR_ADM_WIN_CORE_RENDER_NOT_STARTUP = 1320,
    /** @~chinese 1322: 音频设备模块：无可用音频采集设备。解决方案：插入音频设备。
     */
    /** @~english 1322: Audio device module: No audio sampling device is available. 
     * Solutions: Plug in a proper recording device. */
    ERR_ADM_WIN_CORE_NO_RECORDING_DEVICE = 1322,
    /** @~chinese 1323: 音频设备模块：无可用音频播放设备。解决方案：插入音频设备。
     */
    /** @~english 1323: Audio device module: No audio playout device is available. 
     * Solutions: Plug in a proper playback device.*/
    ERR_ADM_WIN_CORE_NO_PLAYOUT_DEVICE = 1323,
    /** @~chinese 1351: 音频设备模块：音频驱动异常或者兼容性问题 解决方案：禁用并重新启用音频设备，或者重启机器，或者更新声卡驱动。
     */
    /** @~english 1351: Audio device module: An audio driver abnormality or a 
     * compatibility issue occurs. Solutions:
     * - Disable and then re-enable the audio device.
     * - Reboot the system.
     * - Upgrade your audio card driver. */
    ERR_ADM_WIN_WAVE_INIT = 1351,
    /** @~chinese 1353: 音频设备模块：音频驱动异常 解决方案：禁用并重新启用音频设备，或者重启机器，或者更新声卡驱动。
     */
    /** @~english 1353: Audio device module: An audio driver abnormality occurs. 
     * Solutions:
     * - Disable and then re-enable the audio device.
     * - Reboot the system.
     * - Upgrade your audio card driver. */
    ERR_ADM_WIN_WAVE_INIT_RECORDING = 1353,
    /** @~chinese 1354: 音频设备模块：音频驱动异常 解决方案：禁用并重新启用音频设备，或者重启机器，或者更新声卡驱动。
     */
    /** @~english 1354: Audio device module: An audio driver abnormality occurs. 
     * Solutions:
     * - Disable and then re-enable the audio device.
     * - Reboot the system.
     * - Upgrade your audio card driver. */
    ERR_ADM_WIN_WAVE_INIT_MICROPHONE = 1354,
    /** @~chinese 1355: 音频设备模块：音频驱动异常 解决方案：禁用并重新启用音频设备，或者重启机器，或者更新声卡驱动。
     */
    /** @~english 1355: Audio device module: An audio driver abnormality occurs. 
     * Solutions:
     * - Disable and then re-enable the audio device.
     * - Reboot the system.
     * - Upgrade your audio card driver. */
    ERR_ADM_WIN_WAVE_INIT_PLAYOUT = 1355,
    /** @~chinese 1356: 音频设备模块：音频驱动异常 解决方案：禁用并重新启用音频设备，或者重启机器，或者更新声卡驱动。
     */
    /** @~english 1356: Audio device module: An audio driver abnormality occurs. 
     * Solutions:
     * - Disable and then re-enable the audio device.
     * - Reboot the system.
     * - Upgrade your audio card driver. */
    ERR_ADM_WIN_WAVE_INIT_SPEAKER = 1356,
    /** @~chinese 1357: 音频设备模块：音频驱动异常 解决方案：禁用并重新启用音频设备，或者重启机器，或者更新声卡驱动。
     */
    /** @~english 1357: Audio device module: An audio driver abnormality occurs. 
     * Solutions:
     * - Disable and then re-enable the audio device.
     * - Reboot the system.
     * - Upgrade your audio card driver. */
    ERR_ADM_WIN_WAVE_START_RECORDING = 1357,
    /** @~chinese 1358: 音频设备模块：音频驱动异常 解决方案：禁用并重新启用音频设备，或者重启机器，或者更新声卡驱动。
     */
    /** @~english 1358: Audio device module: An audio driver abnormality occurs. 
     * Solutions:
     * - Disable and then re-enable the audio device.
     * - Reboot the system.
     * - Upgrade your audio card driver.*/
    ERR_ADM_WIN_WAVE_START_PLAYOUT = 1358,
    /** @~chinese 1359: 音频设备模块：无采集设备。请检查是否有可用的录放音设备或者录放音设备是否已经被其他应用占用。
    */
    /** @~english 1359: Audio Device Module: No recording device exists.
     */
    ERR_ADM_NO_RECORDING_DEVICE = 1359,
    /** @~chinese 1360: 音频设备模块：无播放设备。
    */
    /** @~english 1360: Audio Device Module: No playback device exists.
     */
    ERR_ADM_NO_PLAYOUT_DEVICE = 1360,

    // VDM error code starts from 1500
    /** @~chinese 1501: 视频设备模块：没有摄像头使用权限。请检查是否已经打开摄像头权限。
    */
    /** 1501: Video Device Module: The camera is unauthorized.
     */
    ERR_VDM_CAMERA_NOT_AUTHORIZED = 1501,

	// VDM error code starts from 1500
	/** **DEPRECATED** 1502: Video Device Module: The camera in use.
     
     Deprecated as of v2.4.1. Use LOCAL_VIDEO_STREAM_ERROR_DEVICE_BUSY(3) in the \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback instead.
	 */
	ERR_VDM_WIN_DEVICE_IN_USE = 1502,

    // VCM error code starts from 1600
    /** @~chinese 1600: 视频设备模块：未知错误。
    */
    /** @~english 1600: Video Device Module: An unknown error occurs.
     */
    ERR_VCM_UNKNOWN_ERROR = 1600,
    /** @~chinese 1601: 视频设备模块：视频编码器初始化错误。该错误为严重错误，请尝试重新加入频道。
    */
    /** @~english 1601: Video Device Module: An error occurs in initializing the video encoder.
    */
    ERR_VCM_ENCODER_INIT_ERROR = 1601,
    /** @~chinese 1602: 视频设备模块：视频编码器错误。该错误为严重错误，请尝试重新加入频道。
    */
    /** @~english 1602: Video Device Module: An error occurs in encoding.
     */
    ERR_VCM_ENCODER_ENCODE_ERROR = 1602,
    /** @~chinese 1603: 视频设备模块：视频编码器设置错误。
    */
    /** @~english 1603: Video Device Module: An error occurs in setting the video encoder.
     */
    ERR_VCM_ENCODER_SET_ERROR = 1603,
};

/** @~chinese 日志过滤分级。 */
    /** @~english Output log filter level. */
enum LOG_FILTER_TYPE
{
/** 0: Do not output any log information. */
    LOG_FILTER_OFF = 0,
     /** @~chinese 0x080f: 输出所有 API 日志信息。
     如果你想获取最完整的日志，可以将日志级别设为该等级。
     */
     /** @~english 0x080f: Output all log information.
      Set your log filter as debug if you want to get the most complete log file.      */
    LOG_FILTER_DEBUG = 0x080f,
     /** @~chinese 0x000f: 输出 CRITICAL、ERROR、WARNING 和 INFO 级别的日志信息。
     我们推荐你将日志级别设为该等级。
     */
     /** @~english 0x000f: Output CRITICAL, ERROR, WARNING, and INFO level log information.
      We recommend setting your log filter as this level.
      */
    LOG_FILTER_INFO = 0x000f,
     /** @~chinese 0x000e: 输出 CRITICAL、ERROR 和 WARNING 级别的日志信息。
     */
     /** @~english 0x000e: Outputs CRITICAL, ERROR, and WARNING level log information.
      */
    LOG_FILTER_WARN = 0x000e,
     /** @~chinese 0x000c: 输出 CRITICAL 和 ERROR 级别的日志信息。 */
     /** @~english 0x000c: Outputs CRITICAL and ERROR level log information. */
    LOG_FILTER_ERROR = 0x000c,
     /** @~chinese 0x0008: 输出 CRITICAL 级别的日志信息。 */
     /** @~english 0x0008: Outputs CRITICAL level log information. */
    LOG_FILTER_CRITICAL = 0x0008,
    /// @cond
    LOG_FILTER_MASK = 0x80f,
    /// @endcond
};
} // namespace agora

#endif
