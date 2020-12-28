//  Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif

#if (defined(__APPLE__) && TARGET_OS_IPHONE)
#include <Agora/iOS/Include/IAgoraRtcChannel.h>
#include <Agora/iOS/Include/IAgoraRtcEngine.h>
#else
#include <Agora/IAgoraRtcEngine.h>
#include <Agora/IAgoraRtcChannel.h>
#endif

#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

namespace agora
{

namespace media
{
namespace ue4
{
class AgoraMediaEngine;
}
}

namespace blueprints
{
class AgoraAudioManager;
class AgoraVideoManager;
}

namespace rtc
{
namespace ue4
{
class AParameter;

/** @~chinese
 * AgoraRtcEngine 类是基于 IRtcEngine 封装的类。
 */
/** @~english
* Wrapper around agora::rtc::IRtcEngine.
*/
class AGORAPLUGIN_API AgoraRtcEngine
{
public:
	AgoraRtcEngine() = delete;
	AgoraRtcEngine(const AgoraRtcEngine& other);
	AgoraRtcEngine(AgoraRtcEngine&& other) noexcept;
	AgoraRtcEngine& operator=(const AgoraRtcEngine& other);
	AgoraRtcEngine& operator=(AgoraRtcEngine&& other) noexcept;
	~AgoraRtcEngine();

public:
  /** @~chinese
   * 创建 AgoraRtcEngine 对象。
   * @return
   * - 方法调用成功：返回 AgoraRtcEngine 对象的指针。
   * - 方法调用失败：返回一个空指针。
   */
   /** @~english
   * @brief    Creates the \ref AgoraRtcEngine object and returns the pointer.
   * @return   \arg Success: Pointer to the AgoraRtcEngine object.
   *           \arg Failure: A null pointer.
   */
	static AgoraRtcEngine* createAgoraRtcEngine();

   /** @~chinese
   * 初始化 Agora SDK 服务。
   * @note 请确保在调用任何其他 API 前先调用 \ref createAgoraRtcEngine 和 \ref initialize。
   * @param rtcEngineContext AgoraRtcEngine 的配置：RtcEngineContext。
   * @return
   * - 0: 方法调用成功
   * - < 0: 方法调用失败
   */
   /** @~english
   * @brief                   Initializes the Agora SDK service.
   * @note                    Ensure that you call the \ref createAgoraRtcEngine and \ref initialize methods before calling any other API.
   * @param  rtcEngineContext Pointer to the RTC engine context. See \ref RtcEngineContext.
   * @return                  \arg 0: Success.
   *                          \arg < 0: Failure.
   */
	int initialize(const agora::rtc::RtcEngineContext& rtcEngineContext);

	//TODO:?
	void setSyncForRelease(bool sync);


   /** @~chinese
   设置频道场景。
   *
   * 该方法用于设置 Agora 频道场景。Agora 会针对不同的使用场景采用不同的优化策略，如通信场景偏好流畅，直播场景偏好画质。
   *
   * @note
   * - 为保证实时音视频质量，我们建议相同频道内的用户使用同一种频道场景。
   * - 该方法必须在 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 前调用和进行设置，进入频道后无法再设置。
   * - 不同的频道场景下，SDK 的默认音频路由和默认视频编码码率是不同的，详见 \ref IRtcEngine::setDefaultAudioRouteToSpeakerphone "setDefaultAudioRouteToSpeakerphone"
   * 和 \ref IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" 方法中的说明。
   *
   * @param profile 频道使用场景: #CHANNEL_PROFILE_TYPE
   *
   * @return
   * - 0(ERR_OK): 方法调用成功。
   * - < 0: 方法调用失败。
   *  - -2 (ERR_INVALID_ARGUMENT): 参数无效。
   *  - -7(ERR_NOT_INITIALIZED): SDK 尚未初始化。
   */
   /** @~english
   * Sets the channel profile of AgoraRtcEngine.
   *
   * The AgoraRtcEngine object differentiates channel profiles and applies optimization algorithms accordingly.
   * For example, it prioritizes smoothness and low latency for a video call, and prioritizes video quality for the interactive live video streaming.
   *
   * @warning
   * - To ensure the quality of real-time communication, we recommend that all users in a channel use the same channel profile.
   * - Call this method before calling \ref joinChannel. You cannot set the channel profile once you have joined the channel.
   * - The default audio route and video encoding bitrate are different in different channel profiles. For details, see
   * \ref setDefaultAudioRouteToSpeakerphone and \ref setVideoEncoderConfiguration.
   *
   * @param profile The channel profile of the AgoraRtcEngine. See #CHANNEL_PROFILE_TYPE.
   * @return
   * - 0(ERR_OK): Success.
   * - < 0: Failure.
   *  - -2 (ERR_INVALID_ARGUMENT): The parameter is invalid.
   *  - -7(ERR_NOT_INITIALIZED): The SDK is not initialized.
   */
	int setChannelProfile(agora::rtc::CHANNEL_PROFILE_TYPE profile);

   /** @~chinese
    设置用户角色。
    *
    * 在加入频道前，用户需要通过本方法设置观众（默认）或主播。在加入频道后，用户可以通过本方法切换用户角色。
    *
    * 直播场景下，如果你在加入频道后调用该方法切换用户角色，调用成功后，本地会触发 \ref agora::rtc::IRtcEngineEventHandler::onClientRoleChanged "onClientRoleChanged" 回调；
    * 远端会触发 \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" 回调或 \ref agora::rtc::IRtcEngineEventHandler::onUserOffline "onUserOffline" (BECOME_AUDIENCE) 回调。
    *
    * @note 该方法仅适用于直播场景。
    *
    * @param role 直播场景里的用户角色: #CLIENT_ROLE_TYPE
    *
    * @return
    * - 0(ERR_OK): 方法调用成功。
    * - < 0: 方法调用失败。
    *  - -1(ERR_FAILED): 一般性的错误（未明确归类）。
    *  - -2(ERR_INALID_ARGUMENT): 参数无效。
    *  - -7(ERR_NOT_INITIALIZED): SDK 尚未初始化。
    */
   /** @~english
    * @brief       Sets the role of the user, such as a host or an audience (default), before joining a channel in a live broadcast.
    * @brief       In the Live Broadcast profile, when a user switches user roles after joining a channel, a successful \ref setClientRole method call triggers the following callbacks:
    *              \arg  The local client: \ref agora::rtc::IRtcEngineEventHandler::onClientRoleChanged "onClientRoleChanged"
    *              \arg  The remote client: \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" or \ref agora::rtc::IRtcEngineEventHandler::onUserOffline "onUserOffline" (BECOME_AUDIENCE)
    * @brief       This method can be used to switch the user role in a live broadcast after the user joins a channel.
    * @note        This method applies only to the Live-broadcast profile.
    * @param  role Sets the role of the user. See #CLIENT_ROLE_TYPE.
    * @return
    * - 0(ERR_OK): Success.
    * - < 0: Failure.
    *   - -1(ERR_FAILED): A general error occurs (no specified reason).
    *   - -2(ERR_INALID_ARGUMENT): The parameter is invalid.
    *   - -7(ERR_NOT_INITIALIZED): The SDK is not initialized.
    */
	int setClientRole(agora::rtc::CLIENT_ROLE_TYPE role);

   /** @~chinese
   加入频道。

   该方法让用户加入通话频道，在同一个频道内的用户可以互相通话，多个用户加入同一个频道，可以群聊。 使用不同 App ID 的 App 是不能互通的。如果已在通话中，用户必须调用 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 退出当前通话，才能进入下一个频道。
   成功调用该方加入频道后，本地会触发 \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" 回调；通信场景下的用户和直播场景下的主播加入频道后，远端会触发 \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" 回调。
   在网络状况不理想的情况下，客户端可能会与 Agora 的服务器失去连接；SDK 会自动尝试重连，重连成功后，本地会触发 \ref agora::rtc::IRtcEngineEventHandler::onRejoinChannelSuccess "onRejoinChannelSuccess" 回调。

   用户成功加入频道后，默认订阅频道内所有其他用户的音频流和视频流，因此产生用量并影响计费。如果想取消订阅，可以通过调用相应的 `mute` 方法实现。

   @note
   - 频道内每个用户的用户 ID 必须是唯一的。如果将 uid 设为 0，系统将自动分配一个 uid。如果想要从不同的设备同时接入同一个频道，请确保每个设备上使用的 uid 是不同的。
   - 请务必确保用于生成 Token 的 App ID 和 \ref agora::rtc::IRtcEngine::initialize "initialize" 方法初始化引擎时用的是同一个 App ID，否则会造成旁路推流失败。

   @param token 动态秘钥。
   - 安全要求不高: 将值设为 NULL。
   - 安全要求高: 将值设置为 Token。如果你已经启用了 App Certificate, 请务必使用 Token。
   @param channelId 标识通话的频道名称，长度在 64 字节以内的字符串。以下为支持的字符集范围（共 89 个字符）:
   - 26 个小写英文字母 a~z；
   - 26 个大写英文字母 A~Z；
   - 10个数字 0~9；
   - 空格；
   - "!"、"#"、"$"、"%"、"&"、"("、")"、"+"、"-"、":"、";"、"<"、"="、"."、">"、"?"、"@"、"["、"]"、"^"、"_"、" {"、"}"、"|"、"~"、","。
   @param info (非必选项) 开发者需加入的任何附加信息。一般可设置为空字符串，或频道相关信息。该信息不会传递给频道内的其他用户。
   @param uid (非必选项) 用户ID，32位无符号整数。建议设置范围：1 到 2<sup>32</sup>-1，并保证唯一性。如果不指定（即设为0），SDK 会自动分配一个，并在 \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" 回调方法中返回，App 层必须记住该返回值并维护，SDK不对该返回值进行维护。

   @return
   - 0(ERR_OK): 方法调用成功。
   - < 0: 方法调用失败。
     - -2(ERR_INALID_ARGUMENT): 参数无效。
     - -3(ERR_NOT_READY): SDK 初始化失败，请尝试重新初始化 SDK。
     - -5(ERR_REFUSED): 调用被拒绝。可能有如下两个原因：
       - 已经创建了一个同名的 IChannel 频道。
       - 已经通过 IChannel 加入了一个频道，并在该 IChannel 频道中发布了音视频流。
   */
   /** @~english
   * @brief             Allows a user to join a channel.
   * @brief             Users in the same channel can talk to each other, and multiple users in the same channel can start a group chat. Users with different App IDs cannot call each other.
   * @brief             You must call the \ref leaveChannel method to exit the current call before entering another channel.
   * @brief             A successful \ref joinChannel method call triggers the following callbacks:
   *                    \arg  The local client: \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess"
   *                    \arg  The remote client: \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined", if the user joining the channel is in the Communication profile, or is a BROADCASTER in the Live Broadcast profile.
   * @brief             When the connection between the client and Agora's server is interrupted due to poor network conditions, the SDK tries reconnecting to the server. When the local client successfully rejoins the channel, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onRejoinChannelSuccess "onRejoinChannelSuccess" callback on the local client.
   * @brief             Once a user joins the channel, the user subscribes to the audio and video streams of all the other users in the channel by default, giving rise to usage and billing calculation. If you do not want to subscribe to a specified stream or all remote streams, call the `mute` methods accordingly.
   * @note              A channel does not accept duplicate uids, such as two users with the same uid. If you set uid as 0, the system automatically assigns a uid. If you want to join a channel from different devices, ensure that each device has a different uid.
   * @warning           Ensure that the App ID used for creating the token is the same App ID used by the \ref initialize method for initializing the RTC engine. Otherwise, the CDN live streaming may fail.
   * @param token       The token generated at your server:
                        \arg  For low-security requirements: You can use the temporary token generated in Console.
                        \arg  For high-security requirements: Use the token generated at your server.
   * @param channelId   Pointer to the unique channel name for the Agora RTC session in the string format smaller than 64 bytes. Supported characters:
   *                    \arg The 26 lowercase English letters: a to z
   *                    \arg The 26 uppercase English letters: A to Z
   *                    \arg The 10 numbers: 0 to 9
   *                    \arg The space
   *                    \arg "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ","
   * @param info        (Optional) Pointer to additional information about the channel. This parameter can be set to NULL or contain channel related information. Other users in the channel will not receive this message.
   * @param uid         (Optional) User ID. A 32-bit unsigned integer with a value ranging from 1 to 2^32-1. The uid must be unique. If a uid is not assigned (or set to 0), the SDK assigns and returns a uid in the \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" callback. Your application must record and maintain the returned `uid` since the SDK does not do so.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   *                       - \ref ERR_INVALID_ARGUMENT (-2)
   *                       - \ref ERR_NOT_READY (-3)
   *                       - \ref ERR_REFUSED (-5)
   *                         - You have created an AgoraRtcChannel object with the same channel name.
   *                         - You have joined and published a stream in a channel created by the AgoraRtcChannel object.
   */
	int joinChannel(const char* token, const char* channelId, const char* info, agora::rtc::uid_t uid);

   /** @~chinese
   * 快速切换直播频道。
   *
   * 当直播频道中的观众想从一个频道切换到另一个频道时，可以调用该方法，实现快速切换。
   *
   * 成功调用该方切换频道后，本地会先收到离开原频道的回调
   * \ref agora::rtc::IRtcEngineEventHandler::onLeaveChannel
   * "onLeaveChannel"，再收到成功加入新频道的回调
   * \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess
   * "onJoinChannelSuccess"。
   *
   * 用户成功切换频道后，默认订阅频道内所有其他用户的音频流和视频流，因此产生用量并影响计费。如果想取消订阅，可以通过调用相应的 `mute` 方法实现。
   *
   * @note 该方法仅适用于直播场景中，角色为观众的用户。
   *
   * @param token 在服务器端生成的用于鉴权的 Token：
   * - 安全要求不高：你可以使用控制台生成的临时 Token，详见
   * [获取临时 Token](https://docs.agora.io/cn/Agora%20Platform/token?platfor%20*%20m=All%20Platforms#获取临时-token)。
   * - 安全要求高：将值设为你的服务端生成的正式 Token，详见
   * [获取正式 Token](https://docs.agora.io/cn/Agora%20Platform/token?platfor%20*%20m=All%20Platforms#获取正式-token)。
   * @param channelId 标识频道的频道名，最大不超过 64 字节。以下为支持的字符集范围
   * （共 89 个字符）：
   * - 26 个小写英文字母 a-z
   * - 26 个大写英文字母 A-Z
   * - 10 个数字 0-9
   * - 空格
   * - "!"，"#"，"$"，"%"，"&"，"("，")"，"+"，"-"，":"，";"，"<"，"="，"."，">"，
   * "?"，"@"，"["，"]"，"^"，"_"，" {"， "}"，"|"，"~"，","
   *
   * @return
   * - 0(ERR_OK): 方法调用成功。
   * - < 0: 方法调用失败。
   *  - -1(ERR_FAILED): 一般性的错误（未明确归类）。
   *  - -2(ERR_INALID_ARGUMENT): 参数无效。
   *  - -5(ERR_REFUSED): 调用被拒绝。可能因为用户角色不是观众。
   *  - -7(ERR_NOT_INITIALIZED): SDK 尚未初始化。
   *  - -102(ERR_INVALID_CHANNEL_NAME): 频道名无效。请更换有效的频道名。
   *  - -113(ERR_NOT_IN_CHANNEL): 用户不在频道内。
   */
   /** @~english
   * @brief             Switches to a different channel.
   * @brief             This method allows the audience of a Live-broadcast channel to switch to a different channel.
   * @brief             After the user successfully switches to another channel, the \ref agora::rtc::IRtcEngineEventHandler::onLeaveChannel "onLeaveChanenl" and \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" callbacks are triggered to indicate that the user has left the original channel and joined a new one.
   * @brief             Once the user switches to another channel, the user subscribes to the audio and video streams of all the other users in the channel by default, giving rise to usage and billing calculation. If you do not want to subscribe to a specified stream or all remote streams, call the `mute` methods accordingly.
   * @note              This method applies to the audience role in a Live-broadcast channel only.
   * @param token       The token generated at your server:
                        \arg  For low-security requirements: You can use the temporary token generated in Console.
                        \arg  For high-security requirements: Use the token generated at your server.
   * @param channelId   Pointer to the unique channel name for the Agora RTC session in the string format smaller than 64 bytes. Supported characters:
   *                    \arg The 26 lowercase English letters: a to z
   *                    \arg The 26 uppercase English letters: A to Z
   *                    \arg The 10 numbers: 0 to 9
   *                    \arg The space
   *                    \arg "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", "{", "}", "|", "~", ","
   * @return
   * - 0(ERR_OK): Success.
   * - < 0: Failure.
   *   - -1(ERR_FAILED): A general error occurs (no specified reason).
   *   - -2(ERR_INALID_ARGUMENT): The parameter is invalid.
   *   - -5(ERR_REFUSED): The request is rejected, probably because the user is not an audience.
   *   - -7(ERR_NOT_INITIALIZED): The SDK is not initialized.
   *   - -102(ERR_INVALID_CHANNEL_NAME): The channel name is invalid.
   *   - -113(ERR_NOT_IN_CHANNEL): The user is not in the channel.
   */
	int switchChannel(const char* token, const char* channelId);

   /** @~chinese
   离开频道。

   离开频道，即挂断或退出通话。

   当调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 方法后，必须调用 leaveChannel 结束通话，否则无法开始下一次通话。 不管当前是否在通话中，都可以调用 leaveChannel，没有副作用。该方法会把会话相关的所有资源释放掉。
   该方法是异步操作，调用返回时并没有真正退出频道。在真正退出频道后，SDK 会触发 \ref agora::rtc::IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel" 回调。
   成功调用该方法离开频道后，本地会触发 \ref agora::rtc::IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel" 回调；通信场景下的用户和直播场景下的主播离开频道后，远端会触发 \ref agora::rtc::IRtcEngineEventHandler::onUserOffline "onUserOffline" 回调。

   @note
   - 如果你调用了 leaveChannel 后立即调用 \ref agora::rtc::IRtcEngine::release "release"，SDK 将无法触发 \ref agora::rtc::IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel" 回调。
   - 如果你在旁路推流时调用 leaveChannel 方法， SDK 将自动调用 \ref IRtcEngine::removePublishStreamUrl "removePublishStreamUrl" 方法。

   @return
   - 0(ERR_OK): 方法调用成功。
   - < 0: 方法调用失败。
     - -1(ERR_FAILED): 一般性的错误（未明确归类）。
     - -2(ERR_INALID_ARGUMENT): 参数无效。
     - -7(ERR_NOT_INITIALIZED): SDK 尚未初始化。
   */
   /** @~english
   * @brief    Allows a user to leave a channel, such as hanging up or exiting a call.
   * @brief    After joining a channel, the user must call the leaveChannel method to end the call before joining another channel.
   * @brief    This method returns 0 if the user leaves the channel and releases all resources related to the call.
   * @brief    This method call is asynchronous, and the user has not left the channel when the method call returns. Once the user leaves the channel, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel" callback.
   * @brief    A successful \ref leaveChannel method call triggers the following callbacks:
   *           \arg  The local client: \ref agora::rtc::IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel"
   *           \arg  The remote client: \ref agora::rtc::IRtcEngineEventHandler::onUserOffline "onUserOffline", if the user leaving the channel is in the Communication channel, or is a BROADCASTER in the Live Broadcast profile.
   * @note     \arg  If you call the \ref release method immediately after the `leaveChannel` method, the `leaveChannel` process interrupts, and the `onLeaveChannel` callback is not triggered.
   *           \arg  If you call the `leaveChannel` method during a CDN live streaming, the SDK triggers the \ref removePublishStreamUrl method.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   *                 - -1(ERR_FAILED): A general error occurs (no specified reason).
   *                 - -2(ERR_INALID_ARGUMENT): The parameter is invalid.
   *                 - -7(ERR_NOT_INITIALIZED): The SDK is not initialized.
   */
	int leaveChannel();

   /** @~chinese
   更新 Token。

   该方法用于更新 Token。如果启用了 Token 机制，过一段时间后使用的 Token 会失效。当：

   - 发生 \ref agora::rtc::IRtcEngineEventHandler::onTokenPrivilegeWillExpire "onTokenPrivilegeWillExpire" 回调时，或发生
   - \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" 回调报告 CONNECTION_CHANGED_TOKEN_EXPIRED(9) 时。

   App 应重新获取 Token，然后调用该方法更新 Token，否则 SDK 无法和服务器建立连接。

   @param token 新的 Token。

   @return
   - 0(ERR_OK): 方法调用成功。
   - < 0: 方法调用失败。
     - -1(ERR_FAILED): 一般性的错误（未明确归类）。
     - -2(ERR_INALID_ARGUMENT): 参数无效。
     - -7(ERR_NOT_INITIALIZED): SDK 尚未初始化。
   */
  /** @~english
   * @brief       Gets a new token when the current token expires after a period of time.
   * @brief       The \a token expires after a period of time once the token schema is enabled when:
   *              \arg  The SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onTokenPrivilegeWillExpire "onTokenPrivilegeWillExpire" callback, or
   *              \arg  The \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" reports `CONNECTION_CHANGED_TOKEN_EXPIRED(9)`.
   * @brief       The application should call this method to get a new token. Failure to do so will result in the SDK disconnecting from the server.
   * @param token Pointer to the new token.
   * @return      \arg  0: Success.
   *              \arg  < 0: Failure.
   *                    - -1(ERR_FAILED): A general error occurs (no specified reason).
   *                    - -2(ERR_INALID_ARGUMENT): The parameter is invalid.
   *                    - -7(ERR_NOT_INITIALIZED): The SDK is not initialized.
   */
	int renewToken(const char* token);

   /** @~chinese
   注册本地用户 User Account。

   该方法为本地用户注册一个 User Account。注册成功后，该 User Account 即可标识该本地用户的身份，用户可以使用它加入频道。成功注册 User Account 后，本地会触发 \ref agora::rtc::IRtcEngineEventHandler::onLocalUserRegistered "onLocalUserRegistered" 回调，告知本地用户的 UID 和 User Account。

   该方法为可选。如果你希望用户使用 User Account 加入频道，可以选用以下两种方式：

   - 先调用 \ref agora::rtc::IRtcEngine::registerLocalUserAccount "registerLocalUserAccount" 方法注册 Account，再调用 \ref agora::rtc::IRtcEngine::joinChannelWithUserAccount "joinChannelWithUserAccount" 方法加入频道
   - 直接调用 \ref agora::rtc::IRtcEngine::joinChannelWithUserAccount "joinChannelWithUserAccount" 方法加入频道

   两种方式的区别在于，提前调用 \ref agora::rtc::IRtcEngine::registerLocalUserAccount "registerLocalUserAccount"，可以缩短使用 \ref agora::rtc::IRtcEngine::joinChannelWithUserAccount "joinChannelWithUserAccount" 进入频道的时间。

   @note
   - `userAccount` 不能为空，否则该方法不生效。
   - 请确保在该方法中设置的 `userAccount` 在频道中的唯一性。
   - 为保证通信质量，请确保频道内使用同一类型的数据标识用户身份。即同一频道内需要统一使用 UID 或 User Account。如果有用户通过 Agora Web SDK 加入频道，请确保 Web 加入的用户也是同样类型。

   @param appId 你的项目在 Agora 控制台注册的 App ID
   @param userAccount 用户 User Account。该参数为必填，最大不超过 255 字节，不可填 `null`。请确保注册的 User Account 的唯一性。以下为支持的字符集范围（共 89 个字符）：
   - 26 个小写英文字母 a-z
   - 26 个大写英文字母 A-Z
   - 10 个数字 0-9
   - 空格
   - "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@",
   "[", "]", "^", "_", " {", "}", "|", "~", ","

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Registers a user account.
   * @brief             Once registered, the user account can be used to identify the local user when the user joins the channel. After the user successfully registers a user account, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onLocalUserRegistered "onLocalUserRegistered" callback on the local client, reporting the user ID and user account of the local user.
   * @brief             To join a channel with a user account, you can choose either of the following:
   *                    \arg  Call the \ref registerLocalUserAccount method to create a user account, and then the \ref joinChannelWithUserAccount method to join the channel.
   *                    \arg  Call the \ref joinChannelWithUserAccount method to join the channel.
   * @brief             The difference between the two is that for the former, the time elapsed between calling the \ref joinChannelWithUserAccount method and joining the channel is shorter than the latter.
   * @note              \arg  Ensure that you set the userAccount parameter. Otherwise, this method does not take effect.
   *                    \arg  Ensure that the value of the userAccount parameter is unique in the channel.
   *                    \arg  To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account. If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.
   * @param appId       The App ID of your project.
   * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
   *                    \arg The 26 lowercase English letters: a to z
   *                    \arg The 26 uppercase English letters: A to Z
   *                    \arg The 10 numbers: 0 to 9
   *                    \arg The space
   *                    \arg "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", "{", "}", "|", "~", ","
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int registerLocalUserAccount(const char* appId, const char* userAccount);


   /** @~chinese
   使用 User Account 加入频道。

   该方法允许本地用户使用 User Account 加入频道。成功加入频道后，会触发以下回调：

   - 本地：\ref agora::rtc::IRtcEngineEventHandler::onLocalUserRegistered "onLocalUserRegistered" 和 \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" 回调
   - 远端：通信场景下的用户和直播场景下的主播加入频道后，远端会依次触发 \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" 和 \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" 回调

   用户成功加入（切换）频道后，默认订阅频道内所有其他用户的音频流和视频流，因此产生用量并影响计费。如果想取消订阅，可以通过调用相应的 `mute` 方法实现。

   @note 为保证通信质量，请确保频道内使用同一类型的数据标识用户身份。即同一频道内需要统一使用 UID 或 User Account。
   如果有用户通过 Agora Web SDK 加入频道，请确保 Web 加入的用户也是同样类型。

   @param token 在 App 服务器端生成的用于鉴权的 Token：
   - 安全要求不高：你可以使用控制台生成的临时 Token，详见 [获取临时 Token](https://docs.agora.io/cn/Audio%20Broadcast/token?platform=All%20Platforms#获取临时-token)。
   - 安全要求高：将值设为你的服务端生成的正式 Token，详见 [获取正式 Token](https://docs.agora.io/cn/Audio%20Broadcast/token?platform=All%20Platforms#获取正式-token)。
   @param channelId 标识频道的频道名，最大不超过 64 字节。以下为支持的字符集范围（共 89 个字符）：
   - 26 个小写英文字母 a-z
   - 26 个大写英文字母 A-Z
   - 10 个数字 0-9
   - 空格
   - "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ","
   @param userAccount 用户 User Account。该参数为必需，最大不超过 255 字节，不可为 `null`。请确保注册的 User Account 的唯一性。以下为支持的字符集范围（共 89 个字符）：
   - 26 个小写英文字母 a-z
   - 26 个大写英文字母 A-Z
   - 10 个数字 0-9
   - 空格
   - "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@",
   "[", "]", "^", "_", " {", "}", "|", "~", ","

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
     - #ERR_INVALID_ARGUMENT (-2)
     - #ERR_NOT_READY (-3)
     - #ERR_REFUSED (-5)
   */
   /** @~english
   * @brief             Joins the channel with a user account.
   * @brief             After the user successfully joins the channel, the SDK triggers the following callbacks:
   *                    <ul>
   *                    <li> The local client: \ref agora::rtc::IRtcEngineEventHandler::onLocalUserRegistered "onLocalUserRegistered" and \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess". The remote client: \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" and \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated", if the user joining the channel is in the Communication profile, or is a BROADCASTER in the Live Broadcast profile.
   *                    </ul>
   * @note              To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account. If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.
   * @param token 	   The token generated at your server:
   *                    \arg  For low-security requirements: You can use the temporary token generated at Console. For details, see Get a temporary toke.
   *                    \arg  For high-security requirements: Set it as the token generated at your server. For details, see Get a token.
   * @param channelId   The channel name. The maximum length of this parameter is 64 bytes. Supported character scopes are:
   *                    \arg The 26 lowercase English letters: a to z
   *                    \arg The 26 uppercase English letters: A to Z
   *                    \arg The 10 numbers: 0 to 9
   *                    \arg The space
   *                    \arg "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", "{", "}", "|", "~", ","
   * @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
   *                    \arg The 26 lowercase English letters: a to z
   *                    \arg The 26 uppercase English letters: A to Z
   *                    \arg The 10 numbers: 0 to 9
   *                    \arg The space
   *                    \arg "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", "{", "}", "|", "~", ","
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int joinChannelWithUserAccount(const char* token, const char* channelId, const char* userAccount);

   /** @~chinese
   通过 User Account 获取用户信息。

   远端用户加入频道后，SDK 会获取到该远端用户的 UID 和 User Account，然后缓存一个包含了远端用户 UID 和 User Account 的 Mapping 表，
   并在本地触发 \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" 回调。收到这个回调后，你可以调用该方法，
   通过传入 User Account 获取包含了指定用户 UID 的 `UserInfo` 对象。

   @param userAccount 用户 User Account。该参数为必填
   @param[in, out] userInfo 标识用户信息的 `UserInfo` 对象:
   - 输入值：一个 `UserInfo` 对象
   - 输出值：一个包含了用户 User Account 和 UID 的 `UserInfo` 对象

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Gets the user information by passing in the user account.
   * @brief             After a remote user joins the channel, the SDK gets the user ID and user account of the remote user, caches them in a mapping table object (userInfo), and triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" callback on the local client.
   * @brief             After receiving the `onUserInfoUpdated` callback, you can call this method to get the user ID of the remote user from the userInfo object by passing in the user account.
   * @param userAccount The user account of the user. Ensure that you set this parameter.
   * @param userInfo    userInfo A userInfo object that identifies the user:
   *                    \arg  Input: A userInfo object.
   *                    \arg  Output: A userInfo object that contains the user account and user ID of the user.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int getUserInfoByUserAccount(const char* userAccount, UserInfo* userInfo);

   /** @~chinese
   通过 UID 获取用户信息。

   远端用户加入频道后， SDK 会获取到该远端用户的 UID 和 User Account，然后缓存一个包含了远端用户 UID 和 User Account 的 Mapping 表，
   并在本地触发 \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" 回调。收到这个回调后，你可以调用该方法，
   通过传入 UID 获取包含了指定用户 User Account 的 `UserInfo` 对象。

   @param uid 用户 UID。该参数为必填
   @param[in, out] userInfo 标识用户信息的 `UserInfo` 对象:
   - 输入值：一个 `UserInfo` 对象
   - 输出值：一个包含了用户 User Account 和 UID 的 `UserInfo` 对象

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Gets the user information by passing in the user ID.
   * @brief             After a remote user joins the channel, the SDK gets the user ID and user account of the remote user, caches them in a mapping table object (userInfo), and triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" callback on the local client.
   * @brief             After receiving the `onUserInfoUpdated` callback, you can call this method to get the user account of the remote user from the userInfo object by passing in the user ID.
   * @param uid         The user ID of the remote user. Ensure that you set this parameter.
   * @param userInfo    userInfo A userInfo object that identifies the user:
   *                    \arg  Input: A userInfo object.
   *                    \arg  Output: A userInfo object that contains the user account and user ID of the user.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int getUserInfoByUid(uid_t uid, UserInfo* userInfo);
   /** @~chinese
   开始语音通话回路测试。

   该方法启动语音通话测试，目的是测试系统的音频设备（耳麦、扬声器等）和网络连接是否正常。
   在测试过程中，用户先说一段话，声音会在设置的时间间隔（单位为秒）后回放出来。
   如果用户能正常听到自己刚才说的话，就表示系统音频设备和网络连接都是正常的。

   @note
   - 请在加入频道前调用该方法。
   - 调用 startEchoTest 后必须调用 \ref agora::rtc::IRtcEngine::stopEchoTest "stopEchoTest" 以结束测试，否则不能进行下一次回声测试，也无法加入频道。
   - 直播场景下，该方法仅能由用户角色为主播的用户调用。

   @param intervalInSeconds 设置返回语音通话回路测试结果的时间间隔，取值范围为 [2, 10]，单位为秒，默认为 10 秒。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief                   Starts an audio call test.
   * @brief                   This method starts an audio call test to determine whether the audio devices (for example, headset and speaker) and the network connection are working properly.
   * @brief                   In the audio call test, you record your voice. If the recording plays back within the set time interval, the audio devices and the network connection are working properly.
   * @note                    \arg  Call this method before joining a channel.
   *                          \arg  After calling this method, call the \ref stopEchoTest method to end the test. Otherwise, the app cannot run the next echo test, or call the \ref joinChannel method.
   *                          \arg  In the Live-broadcast profile, only a host can call this method.
   * @param intervalInSeconds The time interval (s) between when you speak and when the recording plays back.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int startEchoTest(int intervalInSeconds);

   /** @~chinese
   停止语音通话回路测试。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Stops the audio call test.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int stopEchoTest();

   /** @~chinese
   启用视频模块。

   该方法可以在加入频道前或者通话中调用，在加入频道前调用则自动开启视频模块；在通话中调用则由音频模式切换为视频模式。 调用 \ref agora::rtc::IRtcEngine::disableVideo "disableVideo" 方法可关闭视频模式。
   成功调用该方法后，远端会触发 \ref agora::rtc::IRtcEngineEventHandler::onUserEnableVideo "onUserEnableVideo" (true) 回调。
   @note
   - 该方法设置内部引擎为启用状态，在 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 后仍然有效。
   - 该方法重置整个引擎，响应时间较慢，因此 Agora 建议使用如下方法来控制视频模块：
     - \ref agora::rtc::IRtcEngine::enableLocalVideo "enableLocalVideo": 是否启动摄像头采集并创建本地视频流。
     - \ref agora::rtc::IRtcEngine::muteLocalVideoStream "muteLocalVideoStream": 是否发布本地视频流。
     - \ref agora::rtc::IRtcEngine::muteRemoteVideoStream "muteRemoteVideoStream": 是否接收并播放远端视频流。
     - \ref agora::rtc::IRtcEngine::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams": 是否接收并播放所有远端视频流。

     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Enables the video module.
   * @brief    Call this method either before joining a channel or during a call. If this method is called before joining a channel, the call starts in the video mode. If this method is called during an audio call, the audio mode switches to the video mode. To disable the video module, call the \ref disableVideo method.
   * @brief    A successful \ref enableVideo method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserEnableVideo "onUserEnableVideo" (true) callback on the remote client.
   * @note     <ul>
   *           <li> This method affects the internal engine and can be called after the \ref leaveChannel method.
   *           <li> This method resets the internal engine and takes some time to take effect. We recommend using the following API methods to control the video engine modules separately:
   *           <ul>
   *              <li> \ref enableLocalVideo "enableLocalVideo": Whether to enable the camera to create the local video stream.
   *              <li> \ref muteLocalVideoStream "muteLocalVideoStream": Whether to publish the local video stream.
   *              <li> \ref muteRemoteVideoStream "muteRemoteVideoStream": Whether to subscribe to and play the remote video stream.
   *              <li> \ref muteAllRemoteVideoStreams "muteAllRemoteVideoStreams": Whether to subscribe to and play all remote video streams.
   *           </ul>
   *           </ul>
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int enableVideo();

   /** @~chinese
   关闭视频模块。

   该方法可以在加入频道前或者通话中调用，在加入频道前调用，则自动开启纯音频模式，在通话中调用则由视频模式切换为纯音频频模式。 调用 \ref agora::rtc::IRtcEngine::enableVideo "enableVideo" 方法可开启视频模式。
   成功调用该方法后，远端会触发 \ref agora::rtc::IRtcEngineEventHandler::onUserEnableVideo "onUserEnableVideo" (false) 回调
   @note
   - 该方法设置内部引擎为禁用状态，在 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 后仍然有效。
   - 该方法重置整个引擎，响应时间较慢，因此声网建议使用如下方法来控制视频模块：
     - \ref agora::rtc::IRtcEngine::enableLocalVideo "enableLocalVideo": 是否启动摄像头采集并创建本地视频流。
     - \ref agora::rtc::IRtcEngine::muteLocalVideoStream "muteLocalVideoStream": 是否发布本地视频流。
     - \ref agora::rtc::IRtcEngine::muteRemoteVideoStream "muteRemoteVideoStream": 是否接收并播放远端视频流。
     - \ref agora::rtc::IRtcEngine::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams": 是否接收并播放所有远端视频流。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Disables the video module.
   * @brief    This method can be called before joining a channel or during a call. If this method is called before joining a channel, the call starts in audio mode. If this method is called during a video call, the video mode switches to the audio mode. To enable the video module, call the \ref enableVideo method.
   * @brief    A successful \ref disableVideo method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserEnableVideo "onUserEnableVideo" (false) callback on the remote client.
   * @note     <ul>
   *           <li> This method affects the internal engine and can be called after the \ref leaveChannel method.
   *           <li> This method resets the internal engine and takes some time to take effect. We recommend using the following API methods to control the video engine modules separately:
   *           <ul>
   *              <li> \ref enableLocalVideo "enableLocalVideo": Whether to enable the camera to create the local video stream.
   *              <li> \ref muteLocalVideoStream "muteLocalVideoStream": Whether to publish the local video stream.
   *              <li> \ref muteRemoteVideoStream "muteRemoteVideoStream": Whether to subscribe to and play the remote video stream.
   *              <li> \ref muteAllRemoteVideoStreams "muteAllRemoteVideoStreams": Whether to subscribe to and play all remote video streams.
   *           </ul>
   *           </ul>
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int disableVideo();

   /** @~chinese
   设置视频编码属性。

   设置本地视频的编码属性。视频编码属性包含视频分辨率、帧率、码率等影响视频质量的参数设置。

   该方法设置的值均为理想情况下的最大值。如果因网络环境等原因无法达到设置的值时，会取最接近最大值的那个值。

   @note 该方法在加入频道前后都能调用。

   @param config 视频编码参数配置。详见: VideoEncoderConfiguration。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the video encoder configuration.
   * @brief          Each video encoder configuration corresponds to a set of video parameters, including the resolution, frame rate, bitrate, and video orientation.
   * @brief          The parameters specified in this method are the maximum values under ideal network conditions. If the video engine cannot render the video using the specified parameters due to poor network conditions, the parameters further down the list are considered until a successful configuration is found.
   * @note           If you do not need to set the video encoder configuration after joining the channel, you can call this method before the \ref enableVideo method to reduce the render time of the first video frame.
   * @param config   Sets the local video encoder configuration. See \ref VideoEncoderConfiguration.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int setVideoEncoderConfiguration(const VideoEncoderConfiguration& config);

   /** @~chinese
   设置摄像头采集偏好。

   一般的视频通话或直播中，默认由 SDK 自动控制摄像头的输出参数。在如下特殊场景中，默认的参数通常无法满足需求，或可能引起设备性能问题，我们推荐调用该方法设置摄像头的采集偏好：

   - 使用原始音视频数据自采集接口时，如果 SDK 输出的分辨率和帧率高于 \ref agora::rtc::IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" 中指定的参数，在后续处理视频帧的时候，比如美颜功能时，会需要更高的 CPU 及内存，容易导致性能问题。在这种情况下，我们推荐将摄像头采集偏好设置为 CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = 1，避免性能问题。
   - 如果没有本地预览功能或者对预览质量没有要求，我们推荐将采集偏好设置为 CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = 1，以优化 CPU 和内存的资源分配。
   - 如果用户希望本地预览视频比实际编码发送的视频清晰，可以将采集偏好设置为 CAPTURER_OUTPUT_PREFERENCE_PREVIEW = 2。

   @note 请在启动摄像头之前调用该方法，如 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel"，\ref agora::rtc::IRtcEngine::enableVideo "enableVideo" 或者 \ref agora::rtc::IRtcEngine::enableLocalVideo "enableLocalVideo" 之前。

   @param config 摄像头采集偏好，详见 CameraCapturerConfiguration 。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the camera capture configuration.
   * @brief          For a video call or live broadcast, generally the SDK controls the camera output parameters. When the default camera capturer settings do not meet special requirements or cause performance problems, we recommend using this method to set the camera capturer configuration:
   *                 <ul>
   *                 <li> If the resolution or frame rate of the captured raw video data are higher than those set by \ref setVideoEncoderConfiguration, processing video frames requires extra CPU and RAM usage and degrades performance. We recommend setting config as CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = 1 to avoid such problems.
   *                 <li> If you do not need local video preview or are willing to sacrifice preview quality, we recommend setting config as CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = 1 to optimize CPU and RAM usage.
   *                 <li> If you want better quality for the local video preview, we recommend setting config as CAPTURER_OUTPUT_PREFERENCE_PREVIEW = 2.
   *                 </ul>
   * @note           Call this method before enabling the local camera. That said, you can call this method before calling \ref joinChannel, \ref enableVideo, or \ref enableLocalVideo, depending on which method you use to turn on your local camera.
   * @param config   Sets the camera capturer configuration. See \ref CameraCapturerConfiguration.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int setCameraCapturerConfiguration(const CameraCapturerConfiguration& config);

   /** @~chinese
   初始化本地视图。

   该方法初始化本地视图并设置本地用户视频显示信息，只影响本地用户看到的视频画面，不影响本地发布视频。调用该方法绑定本地视频流的显示视窗(view)，并设置本地用户视图的渲染模式和镜像模式。

   在 App 开发中，通常在初始化后调用该方法进行本地视频设置，然后再加入频道。退出频道后，绑定仍然有效，如果需要解除绑定，可以指定空(NULL)View 调用 setupLocalVideo。

   @note
   - 该方法在加入频道前后都能调用。
   - 如果你希望在通话中更新本地用户视图的渲染或镜像模式，请使用 \ref agora::rtc::IRtcEngine::setLocalRenderMode(RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) "setLocalRenderMode" 方法。

   @param canvas 视频画布信息: VideoCanvas。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the local video view and configures the video display settings on the local machine.
   * @brief          The application calls this method to bind each video window (view) of the local video streams and configures the video display settings. Call this method after initialization to configure the local video display settings before joining a channel. The binding is still valid after the user leaves the channel, which means that the window still displays. To unbind the view, set the view in \ref VideoCanvas to NULL.
   *
   * @note
   * - You can call this method either before or after joining a channel.
   * - During a call, you can call this method as many times as necessary to update the display mode of the local video view.   * @param canvas   Pointer to the local video view and settings. See \ref VideoCanvas.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int setupLocalVideo(const VideoCanvas& canvas);

   /** @~chinese
   初始化远端用户视图。

   该方法绑定远端用户和显示视图，并设置远端用户视图在本地显示时的渲染模式和镜像模式，只影响本地用户看到的视频画面。

   调用该接口时需要指定远端视频的 uid，一般可以在进频道前提前设置好。

   如果 App 不能事先知道对方的 uid，可以在 APP 收到 \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" 事件时设置。
   如果启用了视频录制功能，视频录制服务会做为一个哑客户端加入频道，因此其他客户端也会收到它的 \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" 事件，App
   不应给它绑定视图（因为它不会发送视频流），如果 App 不能识别哑客户端，可以在 \ref agora::rtc::IRtcEngineEventHandler::onFirstRemoteVideoDecoded "onFirstRemoteVideoDecoded" 事件时再绑定视图。
   解除某个用户的绑定视图可以把 view 设置为空。退出频道后，SDK 会把远端用户的绑定关系清除掉。

   @note 如果你希望在通话中更新远端用户视图的渲染或镜像模式，请使用 \ref IRtcEngine::setRemoteRenderMode(uid_t userId, RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) "setRemoteRenderMode" 方法。

   @param canvas 视频画布信息: VideoCanvas 。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the remote video view.
   * @brief          This method binds the remote user to the video display window (sets the view for the remote user by the specified uid in \ref VideoCanvas).
   * @brief          The application specifies the uid of the remote video in this method before the remote user joins the channel.
   * @brief          If the remote uid is unknown to the application, set it after the application receives the \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" callback.
   * @brief          If the Video Recording function is enabled, the Video Recording Service joins the channel as a dummy client, causing other clients to also receive the \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" callback. Do not bind the dummy client to the application view because the dummy client does not send any video streams. If your application does not recognize the dummy client, bind the remote user to the view when the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onFirstRemoteVideoDecoded "onFirstRemoteVideoDecoded" callback.
   * @brief          To unbind the remote user from the view, set the view in \ref VideoCanvas to NULL. Once the remote user leaves the channel, the SDK unbinds the remote user.
   * @param canvas   Pointer to the remote video view and settings. See \ref VideoCanvas.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int setupRemoteVideo(const VideoCanvas& canvas);

   /** @~chinese
   开启视频预览。

   该方法用于在进入频道前启动本地视频预览。调用该 API 前，必须：

   - 调用 \ref agora::rtc::IRtcEngine::setupLocalVideo "setupLocalVideo" 设置预览窗口及属性；
   - 调用 \ref agora::rtc::IRtcEngine::enableVideo "enableVideo" 开启视频功能。

   启用了本地视频预览后，如果调用 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 退出频道，本地预览依然处于启动状态，如需要关闭本地预览，需要调用 \ref agora::rtc::IRtcEngine::stopPreview "stopPreview"。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Starts the local video preview before joining the channel.
   * @brief    Before calling this method, you must:
   *           <ul>
   *           <li> Call the \ref setupLocalVideo method to set up the local preview window and configure the attributes.
   *           <li> Call the \ref enableVideo method to enable video.
   *           </ul>
   * @note     Once the startPreview method is called to start the local video preview, if you leave the channel by calling the \ref leaveChannel method, the local video preview remains until you call the \ref stopPreview method to disable it.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int startPreview();

   /** @~chinese
   设置远端用户流的优先级。
   *
   * 设置远端用户的优先级。如果将某个用户的优先级设为高，那么发给这个用户的音视频流的优先级就会高于其他用户。
   * 弱网下 SDK 会优先保证高优先级用户收到的流的质量。
   *
   * @note
   * - 目前 Agora SDK 仅允许将一名远端用户设为高优先级。
   * - 该方法需要在加入频道前调用。
   *
   * @param uid  远端用户的 ID。
   * @param userPriority 远端用户的需求优先级。详见: #PRIORITY_TYPE 。
   *
   * @return
   * - 0: 方法调用成功
   * - < 0: 方法调用失败
   */
   /** @~english
   * @brief                Prioritizes a remote user's stream.
   * @brief                Use this method with the \ref setRemoteSubscribeFallbackOption method. If the fallback function is enabled for a subscribed stream, the SDK ensures the high-priority user gets the best possible stream quality.
   * @note
   * - The Agora SDK supports setting `userPriority` as high for one user only.
   * - Ensure that you call this method before joining a channel.
   * @param uid            The ID of the remote user.
   * @param userPriority   Sets the priority of the remote user. See \ref PRIORITY_TYPE.
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   */
	int setRemoteUserPriority(agora::rtc::uid_t uid, agora::rtc::PRIORITY_TYPE userPriority);

   /** @~chinese
   停止视频预览。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Stops the local video preview and disables video.
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   */
	int stopPreview();

   /** @~chinese
   启用音频模块。

   启用音频模块（默认为开启状态）。

   @note
   - 该方法设置音频模块为启用状态，在频道内和频道外均可调用。在 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 后仍然有效。
   - 该方法开启整个音频模块，响应时间较慢，因此 Agora 建议使用如下方法来控制音频模块：
     - \ref agora::rtc::IRtcEngine::enableLocalAudio "enableLocalAudio": 是否启动麦克风采集并创建本地音频流。
     - \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream": 是否发布本地音频流。
     - \ref agora::rtc::IRtcEngine::muteRemoteAudioStream "muteRemoteAudioStream": 是否接收并播放远端音频流。
     - \ref agora::rtc::IRtcEngine::muteAllRemoteAudioStreams "muteAllRemoteAudioStreams": 是否接收并播放所有远端音频流。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Enables the audio module.
   * @brief    The audio mode is enabled by default.
   * @note     <ul>
   *           <li> This method affects the internal engine and can be called after the \ref leaveChannel method.
   *           <li> This method resets the internal engine and takes some time to take effect. We recommend using the following API methods to control the video engine modules separately:
   *           <ul>
   *              <li> \ref enableLocalVideo "enableLocalVideo": Whether to enable the camera to create the local video stream.
   *              <li> \ref muteLocalVideoStream "muteLocalVideoStream": Whether to publish the local video stream.
   *              <li> \ref muteRemoteVideoStream "muteRecordingVideoStream": Whether to subscribe to and play the remote video stream.
   *              <li> \ref muteAllRemoteVideoStreams "muteAllRemoteVideoStreams": Whether to subscribe to and play all remote video streams.
   *           </ul>
   *           </ul>
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int enableAudio();

   /** @~chinese
   开关本地音频采集。
   *
   * 当用户加入频道时，语音功能默认是开启的。该方法可以关闭或重新开启本地语音功能，即停止或重新开始本地音频采集。
   *
   * 该方法不影响接收或播放远端音频流，\ref agora::rtc::IRtcEngine::enableLocalAudio "enableLocalAudio"(false) 适用于只听不发的用户场景。
   *
   * 语音功能关闭或重新开启后，会收到回调 \ref agora::rtc::IRtcEngineEventHandler::onLocalAudioStateChanged "onLocalAudioStateChanged"，
   * 并报告 `LOCAL_AUDIO_STREAM_STATE_STOPPED(0)` 或 `LOCAL_AUDIO_STREAM_STATE_RECORDING(1)`。
   *
   * @note
   * - 该方法与 \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream" 的区别在于：
   *   - \ref agora::rtc::IRtcEngine::enableLocalAudio "enableLocalAudio": 开启或关闭本地语音采集及处理。使用 `enableLocalAudio` 关闭或开启本地采集后，本地听远端播放会有短暂中断。
   *   - \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream": 停止或继续发送本地音频流。
   * - 该方法在加入频道前后都能调用。
   *
   * @param enabled
   * - true: 重新开启本地语音功能，即开启本地语音采集（默认）；
   * - false: 关闭本地语音功能，即停止本地语音采集。
   *
   * @return
   * - 0: 方法调用成功
   * - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Disables/Re-enables the local audio function.
   * @brief          The audio function is enabled by default. This method disables or re-enables the local audio function, that is, to stop or restart local audio capturing.
   * @brief          This method does not affect receiving or playing the remote audio streams, and enableLocalAudio(false) is applicable to scenarios where the user wants to receive remote audio streams without sending any audio stream to other users in the channel.
   * @brief          Once the local audio function is disabled or re-enabled, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onLocalAudioStateChanged "onLocalAudioStateChanged" callback,
   * which reports `LOCAL_AUDIO_STREAM_STATE_STOPPED(0)` or `LOCAL_AUDIO_STREAM_STATE_RECORDING(1)`.
   * @note
   * - This method is different from the \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream" method:
   *   - \ref enableLocalAudio: Disables/Re-enables the local audio capturing and processing.
   *     If you disable or re-enable local audio capturing using the `enableLocalAudio` method, the local user may hear a pause in the remote audio playback.
   *   - \ref muteLocalAudioStream: Sends/Stops sending the local audio streams.
   * - You can call this method either before or after joining a channel.
   * @param enabled  Sets whether to disable/re-enable the local audio function:
   *                 \arg  true: (Default) Re-enable the local audio function, that is, to start the local audio capturing device (for example, the microphone).
   *                 \arg  false: Disable the local audio function, that is, to stop local audio capturing.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int enableLocalAudio(bool enabled);

   /** @~chinese
   关闭音频模块。

   @note
   - 该方法设置内部引擎为禁用状态，在频道内和频道外均可调用。在 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 后仍然有效。
   - 该方法重置整个引擎，响应时间较慢，因此声网建议使用如下方法来控制音频模块：
     - \ref agora::rtc::IRtcEngine::enableLocalAudio "enableLocalAudio": 是否启动麦克风采集并创建本地音频流。
     - \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream": 是否发布本地音频流。
     - \ref agora::rtc::IRtcEngine::muteRemoteAudioStream "muteRemoteAudioStream": 是否接收并播放远端音频流。
     - \ref agora::rtc::IRtcEngine::muteAllRemoteAudioStreams "muteAllRemoteAudioStreams": 是否接收并播放所有远端音频流。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Disables the audio module.
   * @note     \arg  This method affects the internal engine and can be called after the \ref leaveChannel method. You can call this method either before or after joining a channel.
   *           \arg  This method resets the internal engine and takes some time to take effect. We recommend using the \ref enableLocalAudio and \ref muteLocalAudioStream methods to capture, process, and send the local audio streams.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int disableAudio();

	/** @~chinese
   设置音频编码属性。

   @note
   - 该方法需要在 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 之前设置好， \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 之后设置不生效。
   - 通信和直播场景下，音质（码率）会有网络自适应的调整，通过该方法设置的是一个最高码率。
   - 在有高音质需求的场景（例如音乐教学场景）中，建议将 profile 设置为 #AUDIO_PROFILE_MUSIC_HIGH_QUALITY (4)，scenario 设置为 #AUDIO_SCENARIO_GAME_STREAMING (3)。

   @param  profile 设置采样率，码率，编码模式和声道数: #AUDIO_PROFILE_TYPE 。
   @param  scenario 设置音频应用场景: #AUDIO_SCENARIO_TYPE 。不同的音频场景下，设备的音量类型是不同的。详见[如何区分媒体音量和通话音量](https://docs.agora.io/cn/faq/system_volume)。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the audio parameters and application scenarios.
   * @note           \arg  The \a setAudioProfile method must be called before the \ref joinChannel method.
   *                 \arg  In the Communication and Live-broadcast profiles, the bitrate may be different from your settings due to network self-adaptation.
   *                 \arg  In scenarios involving music education, we recommend setting profile as \ref AUDIO_PROFILE_MUSIC_HIGH_QUALITY (4) and scenario as \ref AUDIO_SCENARIO_GAME_STREAMING (3).
   * @param profile  Sets the sample rate, bitrate, encoding mode, and the number of channels. See \ref AUDIO_PROFILE_TYPE.
   * @param scenario Sets the audio application scenario. See \ref AUDIO_SCENARIO_TYPE. Under different audio scenarios, the device uses different volume tracks, i.e. either the in-call volume or the media volume. For details, see What is the difference between the in-call volume and the media volume?.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int setAudioProfile(agora::rtc::AUDIO_PROFILE_TYPE profile, agora::rtc::AUDIO_SCENARIO_TYPE scenario);

   /** @~chinese
   开关本地音频发送。
   *
   * 该方法用于允许/禁止往网络发送本地音频流。
   * 成功调用该方法后，远端会触发 \ref agora::rtc::IRtcEngineEventHandler::onUserMuteAudio "onUserMuteAudio" 回调。
   *
   * @note
   * - 该方法不影响音频采集状态，因为并没有禁用音频采集设备。
   * - 该方法在加入频道前后都能调用。如果你在该方法后调用 \ref agora::rtc::IRtcEngine::setChannelProfile "setChannelProfile" 方法，SDK 会根据你设置的频道场景以及用户角色，重新设置是否停止发送本地音频。因此我们建议在 `setChannelProfile` 后调用该方法。
   *
   * @param mute
   * - true: 停止发送本地音频流；
   * - false: 继续发送本地音频流（默认）。
   *
   * @return
   * - 0: 方法调用成功
   * - < 0: 方法调用失败
   */
   /** @~english
   * @brief       Stops/Resumes sending the local audio stream.
   * @brief       A successful \ref muteLocalAudioStream method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserMuteAudio "onUserMuteAudio" callback on the remote client.
   * @note        \arg When `mute` is set as `true`, this method does not disable the microphone, which does not affect any ongoing recording.
   *              \arg If you call \ref setChannelProfile after this method, the SDK resets whether or not to mute the local audio according to the channel profile and user role. Therefore, we recommend calling this method after the \a setChannelProfile method.
   * @param mute  Sets whether to send/stop sending the local audio stream:
   *              \arg  true: Stops sending the local audio stream.
   *              \arg  false: (Default) Sends the local audio stream.
   * @return      \arg  0: Success.
   *              \arg  < 0: Failure.
   */
	int muteLocalAudioStream(bool mute);

   /** @~chinese
   接收／停止接收所有音频流。

   @note 该方法在加入频道前后都能调用。

   @param mute
   - true: 停止接收所有音频流；
   - false: 继续接收所有音频流（默认）。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief       Stops/Resumes receiving all remote users' audio streams.
   * @param mute  Sets whether to receive/stop receiving all remote users' audio streams.
   *              \arg  true: Stops receiving all remote users' audio streams.
   *              \arg  false: (Default) Receives all remote users' audio streams.
   * @return      \arg  0: Success.
   *              \arg  < 0: Failure.
   */
	int muteAllRemoteAudioStreams(bool mute);

   /** @~chinese
   设置是否默认接收所有音频流。

   该方法在加入频道前后都可调用。如果在加入频道后调用 `setDefaultMuteAllRemoteAudioStreams(true)`，
   会接收不到后面加入频道的用户的音频流。

   @note
   停止接收音频流后，如果想要恢复接收，请调用 `muteRemoteAudioStream(false)`，并指定你想要接收的远端用户的 ID。
   如果想恢复接收多个用户的音频流，则需要多次调用 `muteRemoteAudioStream`。 `setDefaultMuteAllRemoteAudioStreams(false)`
   只能恢复接收后面加入频道的用户的音频流。

   @param mute
   - true:  默认停止接收所有音频流；
   - false: 默认接收所有音频流（默认）。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief       Stops/Resumes receiving all remote users' audio streams by default.
   *
   *  You can call this method either before or after joining a channel. If you call `setDefaultMuteAllRemoteAudioStreams (true)` after joining a channel, the remote audio streams of all subsequent users are not received.
   *
   * @note If you want to resume receiving the audio stream, call \ref muteRemoteAudioStream (false),
   * and specify the ID of the remote user whose audio stream you want to receive.
   * To receive the audio streams of multiple remote users, call `muteRemoteAudioStream (false)` as many times.
   * Calling `setDefaultMuteAllRemoteAudioStreams (false)` resumes receiving the audio streams of subsequent users only.   
   * @param mute  Sets whether to receive/stop receiving all remote users' audio streams by default:
   *              \arg  true: Stops receiving all remote users' audio streams by default.
   *              \arg  false: (Default) Receives all remote users' audio streams by default.
   * @return      \arg  0: Success.
   *              \arg  < 0: Failure.
   */
	int setDefaultMuteAllRemoteAudioStreams(bool mute);

   /** @~chinese
   调节本地播放的指定远端用户信号音量。

   @since v3.0.0

   你可以在通话中调用该方法调节指定远端用户在本地播放的音量。如需调节多个用户在本地播放的音量，则需多次调用该方法。

   @note
   - 请在加入频道后，调用该方法。
   - 该方法调节的是本地播放的指定远端用户混音后的音量。

   @param uid 远端用户 ID。
   @param volume 播放音量，取值范围为 [0,100]:
   - 0: 静音
   - 100: 原始音量

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
    Adjusts the playback volume of a specified remote user.

     You can call this method as many times as necessary to adjust the playback volume of different remote users, or to repeatedly adjust the playback volume of the same remote user.

     @note
     - Call this method after joining a channel.
     - The playback volume here refers to the mixed volume of a specified remote user.
     - This method can only adjust the playback volume of one specified remote user at a time. To adjust the playback volume of different remote users, call the method as many times, once for each remote user.

     @param uid The ID of the remote user.
     @param volume The playback volume of the specified remote user. The value ranges from 0 to 100:
     - 0: Mute.
     - 100: Original volume.

     @return
     - 0: Success.
    - < 0: Failure.
     */
    int adjustUserPlaybackSignalVolume( unsigned int uid, int volume );

   /** @~chinese
   接收／停止接收指定音频流。

   @note
   - 如果之前有调用过 \ref agora::rtc::IRtcEngine::muteAllRemoteAudioStreams "muteAllRemoteAudioStreams" (true) 停止订阅所有远端音频，在调用本 API 之前请确保你已调用 \ref agora::rtc::IRtcEngine::muteAllRemoteAudioStreams "muteAllRemoteAudioStreams" (false)。 muteAllRemoteAudioStreams 是全局控制，muteRemoteAudioStream 是精细控制。
   - 该方法在加入频道前后都能调用。如果在加入频道前调用，需要自行维护远端用户的 `uid`。

   @param userId 指定用户的 ID
   @param mute
   - true: 停止接收指定音频流；
   - false: 继续接收指定音频流（默认）。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Stops/Resumes receiving a specified remote user's audio stream.
   * @note
   * - You can call this method either before or after joining a channel. If you call it before joining a channel, you need to maintain the `uid` of the remote user on your app level.
   * - If you called the \ref muteAllRemoteAudioStreams method and set \a mute as \a true to stop receiving all remote users' audio streams, call the \a muteAllRemoteAudioStreams method and set \a mute as \a false before calling this method. The \a muteAllRemoteAudioStreams method sets all remote audio streams, while the \a muteRemoteAudioStream method sets a specified remote audio stream.
   * @param userId   User ID of the specified remote user sending the audio.
   * @param mute     Sets whether to receive/stop receiving a specified remote user's audio stream:
   *                 \arg  true: Stops receiving the specified remote user's audio stream.
   *                 \arg  false: (Default) Receives the specified remote user's audio stream.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int muteRemoteAudioStream(agora::rtc::uid_t userId, bool mute);

   /** @~chinese
   开关本地视频发送。

   成功调用该方法后，远端会触发 \ref agora::rtc::IRtcEngineEventHandler::onUserMuteVideo "onUserMuteVideo" 回调。

   @note
   - 调用该方法时，SDK 不再发送本地视频流，但摄像头仍然处于工作状态。相比于 \ref agora::rtc::IRtcEngine::enableLocalVideo "enableLocalVideo" (false) 用于控制本地视频流发送的方法，该方法响应速度更快。该方法不影响本地视频流获取，没有禁用摄像头。
   - 该方法在加入频道前后都能调用。如果你在该方法后调用 \ref agora::rtc::IRtcEngine::setChannelProfile "setChannelProfile" 方法，SDK 会根据你设置的频道场景以及用户角色，重新设置是否停止发送本地视频。因此我们建议在 `setChannelProfile` 后调用该方法。

   @param mute
   - true: 不发送本地视频流
   - false: 发送本地视频流（默认）。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief       Stops/Resumes sending the local video stream.
   * @brief       A successful \ref muteLocalVideoStream method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserMuteVideo "onUserMuteVideo" callback on the remote client.
   * @note        \arg  When set to `true`, this method does not disable the camera which does not affect the retrieval of the local video streams. This method executes faster than the \ref enableLocalVideo method which controls the sending of the local video stream.
   *              \arg  If you call `setChannelProfile` after this method, the SDK resets whether or not to mute the local video according to the channel profile and user role. Therefore, we recommend calling this method after the \a setChannelProfile method.
   * @param mute  Sets whether to send/stop sending the local video stream:
   *              \arg  true: Stop sending the local video stream.
   *              \arg  false: (Default) Send the local video stream.
   * @return      \arg  0: Success.
   *              \arg  < 0: Failure.
   */
	int muteLocalVideoStream(bool mute);

   /** @~chinese
   开关本地视频采集。

   该方法禁用或重新启用本地视频采集，不影响接收远端视频。

   调用 \ref agora::rtc::IRtcEngine::enableVideo "enableVideo" 后，本地视频即默认开启。你可以调用 \ref agora::rtc::IRtcEngine::enableLocalVideo "enableLocalVideo(false)" 关闭本地视频采集。关闭后如果想要重新开启，则可调用 \ref agora::rtc::IRtcEngine::enableLocalVideo "enableLocalVideo(true)"。

   成功禁用或启用本地视频采集后，远端会触发 \ref agora::rtc::IRtcEngineEventHandler::onUserEnableLocalVideo "onUserEnableLocalVideo" 回调。

   @note
   - 该方法在加入频道前后都能调用。
   - 该方法设置内部引擎为启用状态，在 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 后仍然有效。

   @param  enabled
   - true: 开启本地视频采集和渲染 (默认)；
   - false: 关闭使用本地摄像头设备。关闭后，远端用户会接收不到本地用户的视频流；但本地用户依然可以接收远端用户的视频流。设置为 false 时，该方法不需要本地有摄像头。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Enables/Disables the local video capture.
   * @brief          This method disables or re-enables the local video capturer, and does not affect receiving the remote video stream.
   * @brief          After you call the \ref enableVideo method, the local video capturer is enabled by default. You can call \ref enableLocalVideo "enableLocalVideo"(false) to disable the local video capturer. If you want to re-enable it, call `enableLocalVideo(true)`.
   * @brief          After the local video capturer is successfully disabled or re-enabled, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserEnableLocalVideo "onUserEnableLocalVideo" callback on the remote client.
   * @note           This method affects the internal engine and can be called after the \ref leaveChannel method.
   * @param enabled  Sets whether to disable/re-enable the local video, including the capturer, renderer, and sender:
   *                 \arg  true: (Default) Re-enable the local video.
   *                 \arg  false: Disable the local video. Once the local video is disabled, the remote users can no longer receive the video stream of this user, while this user can still receive the video streams of the other remote users.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int enableLocalVideo(bool enabled);

   /** @~chinese
   接收／停止接收所有远端视频流。

   @note 该方法在加入频道前后都能调用。

   @param  mute
   - true: 停止接收所有远端视频流；
   - false: 允许接收所有远端视频流（默认）。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief       Stops/Resumes receiving all video stream from a specified remote user.
   * @note You can call this method either before or after joining a channel.
   * @param mute  Sets whether to receive/stop receiving all remote users' video streams:
   *              \arg  true: Stop receiving all remote users' video streams.
   *              \arg  false: (Default) Receive all remote users' video streams.
   * @return      \arg  0: Success.
   *              \arg  < 0: Failure.
   */
	int muteAllRemoteVideoStreams(bool mute);

   /** @~chinese
   设置是否默认停止接收视频流。

   该方法在加入频道前后都可调用。如果在加入频道后调用 `setDefaultMuteAllRemoteVideoStreams (true)`，会接收不到设置后加入频道的用户的视频流。

   @note 停止接收视频流后，如果想要恢复接收，请调用 \ref agora::rtc::IRtcEngine::muteRemoteVideoStream "muteRemoteVideoStream (false)"，并指定你想要接收的远端用户 `uid`；
   如果想恢复接收多个用户的视频流，则需要多次调用 `muteRemoteVideoStream`。`setDefaultMuteAllRemoteVideoStreams (false)` 只能恢复接收后面加入频道的用户的视频流。

   @param mute
   - true: 默认停止接收所有远端视频；
   - false: 默认接收所有远端视频（默认）。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief       Stops/Resumes receiving all remote users' video streams by default.
   * @note If you want to resume receiving the video stream, call \ref muteRemoteVideoStream (false), and specify the ID of the remote user whose video stream you want to receive. To receive the video streams of multiple remote users, call `muteRemoteVideoStream (false)` as many times. Calling `setDefaultMuteAllRemoteVideoStreams (false)` resumes receiving the video streams of subsequent users only.
   * @param mute  Sets whether to receive/stop receiving all remote users' video streams by default:
   *              \arg  true: Stop receiving all remote users' video streams by default.
   *              \arg  false: (Default) Receive all remote users' video streams by default.
   * @return      \arg  0: Success.
   *              \arg  < 0: Failure.
   */
	int setDefaultMuteAllRemoteVideoStreams(bool mute);

   /** @~chinese
   接收／停止接收指定远端用户的视频流。

   @note
   - 该方法在加入频道前后都能调用。如果在加入频道前调用，需要自行维护远端用户的 `uid`。
   - 如果之前调用过 \ref agora::rtc::IRtcEngine::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams" (true) 停止接收放所有远端视频流，在调用本 API 之前请确保你已调用 \ref agora::rtc::IRtcEngine::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams" (false) 。\ref agora::rtc::IRtcEngine::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams" 是全局控制，\ref agora::rtc::IRtcEngine::muteRemoteVideoStream "muteRemoteVideoStream" 是精细控制。

   @param userId 指定用户的用户 ID。
   @param mute
   - true: 停止接收指定远端用户的视频流；
   - false: 允许接收指定远端用户的视频流（默认）。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @english
   * @brief          Stops/Resumes receiving the video stream from a specified remote user.
   * @note           If you called the \ref muteAllRemoteVideoStreams method and set mute as true to stop receiving all remote video streams, call the \a muteAllRemoteVideoStreams method and set \a mute as \a false before calling this method.
   * @param userId   User ID of the specified remote user.
   * @param mute     Sets whether to stop/resume receiving the video stream from a specified remote user:
   *                 \arg  true: Stop receiving the specified remote user's video stream.
   *                 \arg  false: (Default) Receive the specified remote user's video stream.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int muteRemoteVideoStream(agora::rtc::uid_t userId, bool mute);

   /** @~chinese
   设置订阅的视频流类型。

   在网络条件受限的情况下，如果发送端没有调用 \ref agora::rtc::IRtcEngine::enableDualStreamMode "enableDualStreamMode" (false) 关闭双流模式，接收端可以选择接收大流还是小流。其中，大流可以接为高分辨率高码率的视频流， 小流则是低分辨率低码率的视频流。

   正常情况下，用户默认接收大流。如需接收小流，可以调用本方法进行切换。SDK 会根据视频窗口的大小动态调整对应视频流的大小，以节约带宽和计算资源。

   视频小流默认的宽高比和视频大流的宽高比一致。根据当前大流的宽高比，系统会自动分配小流的分辨率、帧率及码率。

   调用本方法的执行结果将在 \ref agora::rtc::IRtcEngineEventHandler::onApiCallExecuted "onApiCallExecuted" 中返回。

   @note 该方法需要在加入频道后调用。如果既调用了 `setRemoteVideoStreamType`，也调用了
   \ref IRtcEngine::setRemoteDefaultVideoStreamType "setRemoteDefaultVideoStreamType"，则 SDK
   以 `setRemoteVideoStreamType` 中的设置为准。

   @param userId 用户 ID。
   @param streamType 视频流类型: #REMOTE_VIDEO_STREAM_TYPE。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Sets the remote user's video stream type received by the local user when the remote user sends dual streams.
   * @brief             This method allows the application to adjust the corresponding video-stream type based on the size of the video window to reduce the bandwidth and resources.
   *                    \arg  If the remote user enables the dual-stream mode by calling the \ref enableDualStreamMode method, the SDK receives the high-stream video by default.
   *                    \arg  If the dual-stream mode is not enabled, the SDK receives the high-stream video by default.
   * @brief             The method result returns in the \ref agora::rtc::IRtcEngineEventHandler::onApiCallExecuted "onApiCallExecuted" callback. The SDK receives the high-stream video by default to reduce the bandwidth. 
   *                    If needed, users may use this method to switch to the low-stream video. By default, the aspect ratio of the low-stream video is the same as the high-stream video. 
   *                    Once the resolution of the high-stream video is set, the system automatically sets the resolution, frame rate, and bitrate of the low-stream video.
   * @note You can call this method either before or after joining a channel. If you call both
   * \ref setRemoteVideoStreamType and \ref setRemoteDefaultVideoStreamType, the SDK applies the settings in
   *  the `setRemoteVideoStreamType` method.
   * @param userId      ID of the remote user sending the video stream.
   * @param streamType 	Sets the video-stream type. See \ref REMOTE_VIDEO_STREAM_TYPE.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int setRemoteVideoStreamType(agora::rtc::uid_t userId, agora::rtc::REMOTE_VIDEO_STREAM_TYPE streamType);

   /** @~chinese
   设置默认订阅的视频流类型。

   在网络条件受限的情况下，如果发送端没有调用 \ref agora::rtc::IRtcEngine::enableDualStreamMode "enableDualStreamMode" (false) 关闭双流模式，
   接收端可以选择接收大流还是小流。其中，大流可以接为高分辨率高码率的视频流， 小流则是低分辨率低码率的视频流。

   正常情况下，用户默认接收大流。如需默认接收所有用户的视频小流，可以调用本方法进行切换。SDK 会根据视频窗口的大小动态调整对应视频流的大小，以节约带宽和计算资源。视频小流默认
   的宽高比和视频大流的宽高比一致。根据当前大流的宽高比，系统会自动分配小流的分辨率、帧率及码率。

   调用本方法的执行结果将在 \ref agora::rtc::IRtcEngineEventHandler::onApiCallExecuted "onApiCallExecuted" 中返回。

   @note 该方法需要在加入频道后调用。如果既调用了 `setRemoteVideoStreamType`，也调用了
   \ref IRtcEngine::setRemoteDefaultVideoStreamType "setRemoteDefaultVideoStreamType"，则 SDK
   以 `setRemoteVideoStreamType` 中的设置为准。

   @param streamType 视频流类型: #REMOTE_VIDEO_STREAM_TYPE 。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Sets the default video-stream type for the video received by the local user when the remote user sends dual streams.
   *                    \arg  If the dual-stream mode is enabled by calling the \ref enableDualStreamMode method, the user receives the high-stream video by default. The `setRemoteDefaultVideoStreamType` method allows the application to adjust the corresponding video-stream type according to the size of the video window, reducing the bandwidth and resources.
   *                    \arg  If the dual-stream mode is not enabled, the user receives the high-stream video by default.
   * @brief             The result after calling this method is returned in the \ref agora::rtc::IRtcEngineEventHandler::onApiCallExecuted "onApiCallExecuted" callback. The Agora SDK receives the high-stream video by default to reduce the bandwidth. If needed, users can switch to the low-stream video through this method.
   *
   * @note You can call this method either before or after joining a channel. If you call both
   * \ref setRemoteVideoStreamType and \ref setRemoteDefaultVideoStreamType, the SDK applies the settings in
   *  the `setRemoteVideoStreamType` method.
   *
   * @param streamType  Sets the default video-stream type. See \ref REMOTE_VIDEO_STREAM_TYPE.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int setRemoteDefaultVideoStreamType(agora::rtc::REMOTE_VIDEO_STREAM_TYPE streamType);

   /** @~chinese
   启用用户音量提示。

   该方法允许 SDK 定期向 app 报告本地发流用户和瞬时音量最高的远端用户（最多 3 位）的音量相关信息。启用该方法后，只要频道内有发流用户，
   SDK 会在加入频道后按设置的时间间隔触发 \ref agora::rtc::IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" 回调。

   @note 该方法在加入频道前后都能调用。

   @param interval 指定音量提示的时间间隔：
   - &le; 0: 禁用音量提示功能。
   - > 0: 返回音量提示的间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒，否则会
   收不到 \ref agora::rtc::IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" 回调。
   @param smooth 平滑系数，指定音量提示的灵敏度。取值范围为 [0,10]，建议值为 3。数字越大，波动越灵敏；数字越小，波动越平滑。
   @param report_vad
   - true：开启本地人声检测功能。开启后，`onAudioVolumeIndication` 回调的 `vad` 参数会报告是否在本地检测到人声。
   - false：（默认）关闭本地人声检测功能。除引擎自动进行本地人声检测的场景外，`onAudioVolumeIndication` 回调的 `vad` 参数不会报告是否在本地检测到人声。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Enables the reporting of users' volume indication.
   * @brief             This method enables the SDK to regularly report the volume information of the local user who sends a stream and
   * remote users (up to three) whose instantaneous volumes are the highest to the app. Once you call this method and
   * users send streams in the channel, the SDK triggers the
   * \ref IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" callback at the time interval set
   * in this method.
   * @note You can call this method either before or after joining a channel.
   * @param interval    Sets the time interval between two consecutive volume indications:
   *                    \arg  ≤ 0: Disables the volume indication.
   *                    \arg  > 0: Time interval (ms) between two consecutive volume indications. We recommend setting interval > 200 ms. Do not set interval < 10 ms, or the `onAudioVolumeIndication` callback will not be triggered.
   * @param smooth      Smoothing factor sets the sensitivity of the audio volume indicator. The value ranges between 0 and 10. The greater the value, the more sensitive the indicator. The recommended value is 3.
   * @param report_vad  \arg  true: Enable the voice activity detection of the local user. Once it is enabled, the vad parameter of the `onAudioVolumeIndication` callback reports the voice activity status of the local user.
   *                    \arg  false: (Default) Disable the voice activity detection of the local user. Once it is disabled, the vad parameter of the `onAudioVolumeIndication` callback does not report the voice activity status of the local user, except for the scenario where the engine automatically detects the voice activity of the local user.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int enableAudioVolumeIndication(int interval, int smooth, bool report_vad);

   /** @~chinese
   开始客户端录音。

   Agora SDK 支持通话过程中在客户端进行录音。调用该方法后，你可以录制频道内所有用户的音频，并得到一个包含所有用户声音的录音文件。录音文件格式可以为:
   - .wav: 文件大，音质保真度较高。
   - .aac: 文件小，音质保真度较低。

   @note
   - 请确保你在该方法中指定的路径存在并且可写。
   - 该接口需在 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 之后调用。如果调用 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 时还在录音，录音会自动停止。
   - 为保证录音效果，当 `sampleRate` 设为 44.1 kHz 或 48 kHz 时，建议将 `quality` 设为 #AUDIO_RECORDING_QUALITY_MEDIUM 或 #AUDIO_RECORDING_QUALITY_HIGH 。

   @param filePath 录音文件在本地保存的绝对路径，由用户自行指定，需精确到文件名及格式，例如：c:/music/audio.aac。
   @param sampleRate 录音采样率（Hz），可以设为以下值：
   - 16000
   - 32000（默认）
   - 44100
   - 48000
   @param quality 录音音质。详见 #AUDIO_RECORDING_QUALITY_TYPE 。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Starts an audio recording on the client.
   * @brief             The SDK allows recording during a call. After successfully calling this method, you can record the audio of all the users in the channel and get an audio recording file. Supported formats of the recording file are as follows:
   *                    <ul>
   *                    <li> .wav: Large file size with high fidelity.
   *                    <li> .aac: Small file size with low fidelity.
   *                    </ul>
   * @note              \arg  Ensure that the directory you use to save the recording file exists and is writable.
   *                    \arg  This method is usually called after the \ref joinChannel method. The recording automatically stops when you call the \ref leaveChannel method.
   *                    \arg  For better recording effects, set quality as \ref AUDIO_RECORDING_QUALITY_MEDIUM or \ref AUDIO_RECORDING_QUALITY_HIGH when sampleRate is 44.1 kHz or 48 kHz.
   * @param filePath    Pointer to the absolute file path of the recording file. The string of the file name is in UTF-8.
   * @param sampleRate  Sample rate (Hz) of the recording file. Supported values are as follows:
   *                    \arg  16000
   *                    \arg  (Default) 32000
   *                    \arg  44100
   *                    \arg  48000
   * @param quality     Sets the audio recording quality. See \ref AUDIO_RECORDING_QUALITY_TYPE.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int startAudioRecording(const char* filePath, int sampleRate, AUDIO_RECORDING_QUALITY_TYPE quality);

   /** @~chinese
   停止客户端录音。

   停止录音。该接口需要在 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 之前调用，不然会在调用 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 时自动停止。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Stops an audio recording on the client.
   * @brief    You can call this method before calling the \ref leaveChannel method else, the recording automatically stops when the \ref leaveChannel method is called.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int stopAudioRecording();

   /** @~chinese
   开始播放音乐文件。

   指定本地或在线音频文件来和麦克风采集的音频流进行混音和替换。替换是指用音频文件替换音频采集设备采集的音频流。该方法可以选择是否让对方听到本地播
   放的音频并指定循环播放的次数。成功调用该方法后，本地会触发
   \ref agora::rtc::IRtcEngineEventHandler::onAudioMixingStateChanged "onAudioMixingStateChanged" (PLAY) 回调。播放结束后，
   会收到 \ref agora::rtc::IRtcEngineEventHandler::onAudioMixingStateChanged "onAudioMixingStateChanged" (STOPPED) 回调。

   @note
   - 请在频道内调用该方法，如果在频道外调用该方法可能会出现问题。
   - 如果本地音乐文件不存在、文件格式不支持、无法访问在线音乐文件 URL 都会返回警告码 WARN_AUDIO_MIXING_OPEN_ERROR = 701。

   @param filePath 指定需要混音的本地或在线音频文件的绝对路径，例如：c:/music/audio.mp4。建议填写文件后缀名。若无法确定文件后缀名，可不填。
   支持的音频格式包括：3GP、ASF、ADTS、AVI、MP3、MP4、MPEG-4、SAMI 和 WAVE。
   详见 [Supported Media Formats in Media Foundation](https://docs.microsoft.com/zh-cn/windows/desktop/medfound/supported-media-formats-in-media-foundation) 。
   @param loopback
   - true: 只有本地用户可以听到混音的音频；
   - false: 本地用户和远端用户都能听到混音的音频。
   @param replace
   - true: 只推送指定的本地音频文件或者线上音频文件，不传输麦克风收录的音频。
   - false: 本地音频文件与来自麦克风的音频流混音。
   @param cycle 循环播放次数：
   - 正整数: 循环播放的次数；
   - -1: 无限循环。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Starts playing and mixing the music file.
   * @brief             This method mixes the specified local audio file with the audio stream from the microphone, or replaces the microphone's audio stream with the specified local audio file. 
   *                    You can choose whether the other user can hear the local audio playback and specify the number of playback loops. This method also supports online music playback.
   * @brief             A successful \ref startAudioMixing method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onAudioMixingStateChanged "onAudioMixingStateChanged" (PLAY) callback on the local client.
   * @brief             When the audio mixing file playback finishes, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onAudioMixingStateChanged "onAudioMixingStateChanged" (STOPPED) callback on the local client.
   * @note              \arg  Call this method after joining a channel, otherwise issues may occur.
   *                    \arg  If the local audio mixing file does not exist, or if the SDK does not support the file format or cannot access the music file URL, the SDK returns WARN_AUDIO_MIXING_OPEN_ERROR = 701.
   *                    \arg  If you want to play an online music file, ensure that the time interval between calling this method is more than 100 ms, or the AUDIO_MIXING_ERROR_TOO_FREQUENT_CALL(702) error code occurs.
   * @param filePath    Pointer to the absolute path of the local or online audio file to mix. Supported audio formats: 3GP, ASF, ADTS, AVI, MP3, MPEG-4, SAMI, and WAVE. For more information, see Supported Media Formats in Media Foundation.
   * @param loopback    Sets which user can hear the audio mixing:
   *                    \arg  true: Only the local user can hear the audio mixing.
   *                    \arg  false: Both users can hear the audio mixing.
   * @param replace     Sets the audio mixing content:
   *                    \arg  true: Only the specified audio file is published; the audio stream received by the microphone is not published.
   *                    \arg  false: The local audio file is mixed with the audio stream from the microphone.
   * @param cycle       Sets the number of playback loops:
   *                    \arg  Positive integer: Number of playback loops.
   *                    \arg  -1: Infinite playback loops.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int startAudioMixing(const char* filePath, bool loopback, bool replace, int cycle);
   /** @~chinese
   停止播放音乐文件。

   该方法停止播放音乐文件。请在频道内调用该方法。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Stops playing and mixing the music file.
   * @brief    Call this method when you are in a channel.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int stopAudioMixing();
   /** @~chinese
   暂停播放音乐文件。

   该方法暂停播放音乐文件。请在频道内调用该方法。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Pauses playing and mixing the music file.
   * @brief    Call this method when you are in a channel.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int pauseAudioMixing();
   /** @~chinese
   恢复播放音乐文件。

   该方法恢复混音，继续播放音乐文件。请在频道内调用该方法。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Resumes playing and mixing the music file.
   * @brief    Call this method when you are in a channel.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int resumeAudioMixing();
   /** @~chinese
   调节音乐文件的播放音量。

   该方法调节混音音乐文件在本端和远端的播放音量大小。

   @note
   - 该方法需要在 \ref IRtcEngine::startAudioMixing "startAudioMixing" 后调用。
   - 调用该方法不影响调用 \ref agora::rtc::IRtcEngine::playEffect "playEffect" 播放音效文件的音量。

   @param volume 音乐文件音量范围为 0~100。100 （默认值）为原始文件音量。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Adjusts the volume during audio mixing.
   * @note
   * - Calling this method does not affect the volume of audio effect file playback invoked by the \ref playEffect method.
   * - Ensure that this method is called after \ref startAudioMixing.
   * @param volume   Audio mixing volume. The value ranges between 0 and 100 (default).
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int adjustAudioMixingVolume(int volume);

   /** @~chinese
   调节音乐文件本端播放音量。

   该方法调节混音音乐文件在本端的播放音量大小。

   @note 该方法需要在 \ref IRtcEngine::startAudioMixing "startAudioMixing" 后调用。

   @param volume 音乐文件音量范围为 0~100。100 （默认值） 为原始文件音量。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Adjusts the audio mixing volume for local playback.
   * @note           Ensure that this method is called after \ref startAudioMixing.
   * @param volume   Audio mixing volume for local playback. The value ranges between 0 and 100 (default).
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int adjustAudioMixingPlayoutVolume(int volume);

   /** @~chinese
   获取音乐文件的本地播放音量。

   该方法获取混音的音乐文件本地播放音量，方便排查音量相关问题。

   @note 请在频道内调用该方法。

   @return
   - &ge; 0: 方法调用成功则返回音量值，范围为 [0,100]
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Retrieves the audio mixing volume for local playback.
   * @brief    This method helps troubleshoot audio volume related issues.
   * @note     Call this method when you are in a channel.
   * @return   \arg  ≥ 0: The audio mixing volume, if this method call succeeds. The value range is [0,100].
   *           \arg  < 0: Failure.
   */
	int getAudioMixingPlayoutVolume();
   /** @~chinese
   调节音乐文件远端播放音量。

   该方法调节混音音乐文件在远端的播放音量大小。

   @note 该方法需要在 \ref IRtcEngine::startAudioMixing "startAudioMixing" 后调用。

   @param volume 音乐文件音量范围为 0~100。100 （默认值） 为原始文件音量。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Adjusts the audio mixing volume for publishing (for remote users).
   * @note           Call this method when you are in a channel.
   * @param volume   Audio mixing volume for publishing. The value ranges between 0 and 100 (default).
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int adjustAudioMixingPublishVolume(int volume);

   /**
   * @brief    Retrieves the audio mixing volume for publishing.
   * @brief    This method helps troubleshoot audio volume related issues.
   * @note     Ensure that this method is called after \ref startAudioMixing.
   * @return   \arg  ≥ 0: The audio mixing volume for publishing, if this method call succeeds. The value range is [0,100].
   *           \arg  < 0: Failure.
   */
	int getAudioMixingPublishVolume();

   /** @~chinese
   获取音乐文件总时长。

   该方法获取音乐文件总时长，单位为毫秒。请在频道内调用该方法。

   @return
   - &ge; 0: 方法调用成功返回音乐文件时长。
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Retrieves the duration (ms) of the music file.
   * @brief    Call this method when you are in a channel.
   * @return   \arg  ≥ 0: The audio mixing duration, if this method call succeeds.
   *           \arg  < 0: Failure.
   */
	int getAudioMixingDuration();
   /** @~chinese
   获取音乐文件的播放进度。

   该方法获取当前音乐文件播放进度，单位为毫秒。请在频道内调用该方法。

   @return
   - &ge; 0: 方法调用成功返回音乐文件播放进度。
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Retrieves the playback position (ms) of the music file.
   * @brief    Call this method when you are in a channel.
   * @return   \arg  ≥ 0: The current playback position of the audio mixing, if this method call succeeds.
   *           \arg  < 0: Failure.
   */
	int getAudioMixingCurrentPosition();

   /** @~chinese
   设置音乐文件的播放位置。

   该方法可以设置音频文件的播放位置，这样你可以根据实际情况播放文件，而非从头到尾播放整个文件。

   @note 该方法需要在 \ref IRtcEngine::startAudioMixing "startAudioMixing" 后调用。

   @param pos 整数。进度条位置，单位为毫秒。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief       Sets the playback position of the music file to a different starting position (the default plays from the beginning).
   * @param pos   The playback starting position (ms) of the music file.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int setAudioMixingPosition(int pos /*in ms*/);

   /** @~chinese
     * 调整本地播放的音乐文件的音调。
     *
     * 本地人声和播放的音乐文件混音时，调用该方法可以仅调节音乐文件的音调。
     * @note
     * 该方法需在 `startAudioMixing` 后调用。
     * @param pitch 按半音音阶调整本地播放的音乐文件的音调，默认值为 0，即不调整音调。取值范围为 [-12,12]，
     * 每相邻两个值的音高距离相差半音。取值的绝对值越大，音调升高或降低得越多。
     * @return
     * - 0：方法调用成功
     * - < 0：方法调用失败
     */
   /** @~english
    * @brief Sets the pitch of the local music file.
    * @note
    * Call this method after calling `startAudioMixing`.
    *
    * @param pitch Sets the pitch of the local music file by chromatic scale. The default value is 0,
    * which means keeping the original pitch. The value ranges from -12 to 12, and the pitch value between
    * consecutive values is a chromatic value. The greater the absolute value of this parameter, the
    * higher or lower the pitch of the local music file.
    *
    * @return         \arg  0: Success.
    *                 \arg  < 0: Failure.
    */
   int setAudioMixingPitch( int pitch );
   /** @~chinese
   获取音效文件的播放音量。

   音量范围为 0~100。100 （默认值）为原始文件音量。

   @note 该方法需要在 \ref IRtcEngine::playEffect "playEffect" 后调用。

   @return
   - 音效文件的音量。
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Retrieves the volume of the audio effects.
   * @brief    The value ranges between 0 and 100.
   * @note Ensure that this method is called after \ref playEffect.
   * @return   \arg  ≥ 0: Volume of the audio effects, if this method call succeeds.
   *           \arg  < 0: Failure.
   */
	int getEffectsVolume();
   /** @~chinese
   设置音效文件的播放音量。

   音量范围为 0~100。100 （默认值）为原始文件音量。

   @note 该方法需要在 \ref IRtcEngine::playEffect "playEffect" 后调用。

   @param volume 该方法设置音效的音量。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the volume of the audio effects.
   * @note Ensure that this method is called after \ref playEffect.
   * @param volume   Sets the volume of the audio effects. The value ranges between 0 and 100 (default).
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int setEffectsVolume(int volume);

   /** @~chinese
   实时调整音效文件的播放音量。

   @note 该方法需要在 \ref IRtcEngine::playEffect "playEffect" 后调用。

   @param soundId 指定音效的 ID。每个音效均有唯一的 ID。
   @param volume 播放音量。音量范围为 0~100。100 （默认值）为原始文件音量。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the volume of a specified audio effect.
   * @note Ensure that this method is called after \ref playEffect.
   * @param soundId  ID of the audio effect. Each audio effect has a unique ID.
   * @param volume   Sets the volume of the specified audio effect. The value ranges between 0 and 100 (default).
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int setVolumeOfEffect(int soundId, int volume);

   /** @~chinese
   播放指定音效文件。

   你可以多次调用该方法，通过传入不同的音效文件的 `soundID` 和 `filePath`，同时播放多个音效文件，实现音效叠加。为获得最佳用户体验，我们建议同时播放的音效文件不要超过 3 个。在 macOS 和 Windows 上，该方法不支持同时播放多个在线音效文件。

   @note 该方法需要在加入频道后调用。

   @param soundId 指定音效的 ID。每个音效均有唯一的 ID。
   @note 如果你已通过 \ref agora::rtc::IRtcEngine::preloadEffect "preloadEffect" 将音效加载至内存，确保这里设置的 soundId 与 \ref agora::rtc::IRtcEngine::preloadEffect "preloadEffect" 设置的 soundId 相同。
   @param filePath 音效文件的绝对路径或 URL 地址，例如：c:/music/audio.mp4。建议填写文件后缀名。若无法确定文件后缀名，可不填。
   支持的音频格式包括：mp3、mp4、m4a、aac、3gp、mkv 及 wav。
   详见 [Supported Media Formats in Media Foundation](https://docs.microsoft.com/zh-cn/windows/desktop/medfound/supported-media-formats-in-media-foundation) 。
   @param loopCount 设置音效循环播放的次数：
   - 0: 播放音效一次；
   - 1: 播放音效两次；
   - -1: 无限循环播放音效，直至调用 \ref agora::rtc::IRtcEngine::stopEffect "stopEffect" 或 \ref agora::rtc::IRtcEngine::stopAllEffects "stopAllEffects" 后停止。
   @param pitch 设置音效的音调 取值范围为 [0.5, 2]。默认值为 1.0，表示不需要修改音调。取值越小，则音调越低。
   @param pan 设置是否改变音效的空间位置。取值范围为 [-1.0, 1.0]:
   - 0.0: 音效出现在正前方；
   - 1.0: 音效出现在右边；
   - -1.0: 音效出现在左边。
   @param gain 设置是否改变单个音效的音量。取值范围为 [0.0, 100.0]。默认值为 100.0。取值越小，则音效的音量越低。
   @param publish 设置是否将音效传到远端：
   - true: 音效在本地播放的同时，会发布到 Agora 云端，因此远端用户也能听到该音效；
   - false: 音效不会发布到 Agora 云端，因此只能在本地听到该音效。

   @return
   - 0：方法调用成功
   - < 0：方法调用失败
   */
   /** @~english
   * @brief             Plays a specified local or online audio effect file.
   * @brief             This method allows you to set the loop count, pitch, pan, and gain of the audio effect file, as well as whether the remote user can hear the audio effect.
   * @brief             To play multiple audio effect files simultaneously, call this method multiple times with different soundIds and filePaths. We recommend playing no more than three audio effect files at the same time.
   * @param soundId     ID of the specified audio effect. Each audio effect has a unique ID.
   * @note              \arg  If the audio effect is preloaded into the memory through the \ref preloadEffect method, the value of \a soundID must be the same as that in the \a preloadEffect method.
   *                    \arg  Playing multiple online audio effect files simultaneously is not supported on macOS and Windows.
   * @param filePath    The absolute path to the local audio effect file or the URL of the online audio effect file.
   * @param loopCount   Sets the number of times the audio effect loops:
   *                    \arg  0: Play the audio effect once.
   *                    \arg  1: Play the audio effect twice.
   *                    \arg  -1: Play the audio effect in an indefinite loop until the \ref stopEffect or \ref stopAllEffects method is called.
   * @param pitch       Sets the pitch of the audio effect. The value ranges between 0.5 and 2. The default value is 1 (no change to the pitch). The lower the value, the lower the pitch.
   * @param pan         Sets the spatial position of the audio effect. The value ranges between -1.0 and 1.0:
   *                    \arg  0.0: The audio effect displays ahead.
   *                    \arg  1.0: The audio effect displays to the right.
   *                    \arg  -1.0: The audio effect displays to the left.
   * @param gain        Sets the volume of the audio effect. The value ranges between 0 and 100 (default). The lower the value, the lower the volume of the audio effect.
   * @param publish     Sets whether or not to publish the specified audio effect to the remote stream:
   *                    \arg  true: The locally played audio effect is published to the Agora Cloud and the remote users can hear it.
   *                    \arg  false: The locally played audio effect is not published to the Agora Cloud and the remote users cannot hear it.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int playEffect(
		int soundId,
		const char* filePath,
		int loopCount,
		double pitch,
		double pan,
		int gain,
		bool publish = false);

   /** @~chinese
   停止播放指定音效文件。

   @param soundId 指定音效文件的 ID。每个音效文件均有唯一的 ID。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Stops playing a specified audio effect.
   * @param soundId  ID of the audio effect to stop playing. Each audio effect has a unique ID.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int stopEffect(int soundId);
   /** @~chinese
   停止播放所有音效文件。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Stops playing all audio effects.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int stopAllEffects();

   /** @~chinese
   将音效文件加载至内存。

   该方法将指定音效文件预加载至内存。

   @note 该方法不支持在线音频文件。

   为保证通信畅通，请注意控制预加载音效文件的大小，并在 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 前就使用该方法完成音效预加载。音频文件支持以下音频格式: mp3、aac、m4a、3gp，和 wav。

   @param soundId 指定音效文件的 ID。每个音效文件均有唯一的 ID。
   @param filePath 音效文件的绝对路径。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Preloads a specified audio effect file into the memory.
   * @note           This method does not support online audio effect files.
   * @brief          To ensure smooth communication, limit the size of the audio effect file. We recommend using this method to preload the audio effect before calling the \ref joinChannel method.
   * @brief          Supported audio formats: mp3, aac, m4a, 3gp, and wav.
   * @param soundId  ID of the audio effect. Each audio effect has a unique ID.
   * @param filePath Pointer to the absolute path of the audio effect file.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int preloadEffect(int soundId, const char* filePath);

   /** @~chinese
   从内存释放某个预加载的音效文件。

   @param soundId 指定音效文件的 ID。每个音效文件均有唯一的 ID
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Releases a specified preloaded audio effect from the memory.
   * @param soundId  ID of the audio effect. Each audio effect has a unique ID.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int unloadEffect(int soundId);

   /** @~chinese
   暂停音效文件播放。

   @param soundId 指定音效文件的 ID。每个音效文件均有唯一的 ID。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Pauses a specified audio effect.
   * @param soundId  ID of the audio effect. Each audio effect has a unique ID.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int pauseEffect(int soundId);
   /** @~chinese
   暂停所有音效文件播放。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Pauses all audio effects.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int pauseAllEffects();
   /** @~chinese
   恢复播放指定音效文件。

   @param soundId 指定音效文件的 ID。每个音效文件均有唯一的 ID。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Resumes playing a specified audio effect.
   * @param soundId  ID of the audio effect. Each audio effect has a unique ID.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int resumeEffect(int soundId);
   /** @~chinese
   恢复播放所有音效文件。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Resumes playing all audio effects.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int resumeAllEffects();
   /** @~chinese
   开启/关闭远端用户的语音立体声。

   如果想调用 \ref agora::rtc::IRtcEngine::setRemoteVoicePosition "setRemoteVoicePosition" 实现听声辨位的功能，请确保在加入频道前调用该方法开启远端用户的语音立体声。

   @param enabled 是否开启远端用户语音立体声：
   - true: 开启
   - false: 关闭

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Enables/Disables stereo panning for remote users.
   * @brief          Ensure that you call this method before joinChannel to enable stereo panning for remote users so that the local user can track the position of a remote user by calling \ref setRemoteVoicePosition.
   * @param enabled  Sets whether or not to enable stereo panning for remote users:
   *                 \arg  true: enables stereo panning.
   *                 \arg  false: disables stereo panning.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int enableSoundPositionIndication(bool enabled);

   /** @~chinese
   设置远端用户的语音位置。

   设置远端用户声音的空间位置和音量，方便本地用户听声辨位。

   通过调用该接口设置远端用户声音出现的位置，左右声道的声音差异会产生声音的方位感，从而判断出远端用户的实时位置。在多人在线游戏场景，如吃鸡游戏中，该方法能有效增加游戏角色的方位感，模拟真实场景。

   @note
   - 为获得最佳听觉体验，我们建议使用该方法时使用立体声外放。
   - 该方法需要在加入频道后调用。

   @param uid 远端用户的 ID
   @param pan 设置远端用户声音的空间位置，取值范围为 [-1.0,1.0]:
   - (默认）0.0: 声音出现在正前方。
   - -1.0: 声音出现在左边。
   - 1.0: 声音出现在右边。

   @param gain 设置远端用户声音的音量，取值范围为 [0.0,100.0]，默认值为 100.0，表示该用户的原始音量。取值越小，则音量越低。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief       Sets the sound position and gain of a remote user.
   * @brief       When the local user calls this method to set the sound position of a remote user, the sound difference between the left and right channels allows the local user to track the real-time position of the remote user, creating a real sense of space. This method applies to massively multiplayer online games, such as Battle Royale games.
   * @note        \arg  For this method to work, enable stereo panning for remote users by calling the \ref enableSoundPositionIndication method before joining a channel.
                  \arg  This method requires hardware support. For the best sound positioning, we recommend using a stereo speaker.
   * @param uid   The ID of the remote user.
   * @param pan   The sound position of the remote user. The value ranges from -1.0 to 1.0:
   *              \arg  0.0: the remote sound comes from the front.
   *              \arg  -1.0: the remote sound comes from the left.
   *              \arg  1.0: the remote sound comes from the right.
   * @param gain  Gain of the remote user. The value ranges from 0.0 to 100.0. The default value is 100.0 (the original gain of the remote user). The smaller the value, the less the gain.
   * @return      \arg  0: Success.
   *              \arg  < 0: Failure.
   */
	int setRemoteVoicePosition(uid_t uid, double pan, double gain);

   /** @~chinese
   设置本地语音音调。

   @note 该方法在加入频道前后都能调用。

   @param pitch 语音频率可以 [0.5,2.0] 范围内设置。取值越小，则音调越低。默认值为 1.0，表示不需要修改音调。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief       Changes the voice pitch of the local speaker.
   * @param pitch Sets the voice pitch. The value ranges between 0.5 and 2.0. The lower the value, the lower the voice pitch. The default value is 1.0 (no change to the local voice pitch).
   * @return      \arg  0: Success.
   *              \arg  < 0: Failure.
   */
	int setLocalVoicePitch(double pitch);

   /** @~chinese
   设置本地语音音效均衡。

   @note 该方法在加入频道前后都能调用。

   @param bandFrequency 频谱子带索引。取值范围是 [0,9]，分别代表音效的 10 个频带。对应的中心频率为 [31，62，125，250，500，1k，2k，4k，8k，16k] Hz。详见 #AUDIO_EQUALIZATION_BAND_FREQUENCY 。
   @param bandGain  每个 band 的增益，单位是 dB，每一个值的范围是 [-15,15]。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief                Sets the local voice equalization effect.
   * @param bandFrequency  Sets the band frequency. The value ranges between 0 and 9, representing the respective 10-band center frequencies of the voice effects, including 31, 62, 125, 500, 1k, 2k, 4k, 8k, and 16k Hz. See \ref AUDIO_EQUALIZATION_BAND_FREQUENCY.
   * @param bandGain       Sets the gain of each band in dB. The value ranges between -15 and 15.
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   */
	int setLocalVoiceEqualization(agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain);
   /** @~chinese
   设置本地音效混响。

   @note 该方法在加入频道前后都能调用。

   @param reverbKey 混响音效 Key。该方法共有 5 个混响音效 Key:  #AUDIO_REVERB_TYPE 。
   @param value 各混响音效 Key 所对应的值：
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Sets the local voice reverberation.
   * @brief             v2.4.0 adds the \ref setLocalVoiceReverbPreset method, a more user-friendly method for setting the local voice reverberation. You can use this method to set the local reverberation effect, such as pop music, R&B, rock music, and hip-hop.
   * @param reverbKey   Sets the reverberation key. See \ref AUDIO_REVERB_TYPE.
   * @param value       Sets the value of the reverberation key.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int setLocalVoiceReverb(agora::rtc::AUDIO_REVERB_TYPE reverbKey, int value);

   /** @~chinese
   设置本地语音变声、美音或语聊美声效果。
   *
   * @deprecated 该方法从 v3.2.0 起废弃，请改用 \ref IRtcEngine::setAudioEffectPreset "setAudioEffectPreset" 或 \ref IRtcEngine::setVoiceBeautifierPreset "setVoiceBeautifierPreset"。
   *
   * 通信场景下的用户或直播场景下的主播均可调用该方法为本地语音设置以下效果。成功设置以后，频道内的所有用户均可听到声音效果。
   * - 变声效果：枚举值以 `VOICE_CHANGER` 为前缀。效果包括老男人、小男孩、小女孩、猪八戒、空灵和绿巨人，通常用于语聊场景。
   * - 美音效果：枚举值以 `VOICE_BEAUTY` 为前缀。效果包括浑厚、低沉、圆润、假音、饱满、清澈、高亢、嘹亮和空旷，通常用于语聊和唱歌场景。
   * - 语聊美声效果：枚举值以 `GENERAL_BEAUTY_VOICE` 为前缀。效果包括磁性（男）、清新（女）和活力（女），通常用于语聊场景。该功能主要细化了男声和女声各自的特点。
   *
   * @note
   * - 为达到更好的声音效果，Agora 推荐在调用该方法前将 \ref IRtcEngine::setAudioProfile "setAudioProfile" 的 `profile` 参数设置为 #AUDIO_PROFILE_MUSIC_HIGH_QUALITY (4) 或 #AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO (5)
   * - 该方法对人声的处理效果最佳，Agora 不推荐调用该方法处理含人声和音乐的音频数据。
   * - 该方法不能与 \ref IRtcEngine::setLocalVoiceReverbPreset "setLocalVoiceReverbPreset" 方法一同使用，否则先调的方法会不生效。更多注意事项，详见进阶功能《变声与混响》。
   * - 该方法在加入频道前后都能调用。
   *
   * @param voiceChanger 预设本地语音变声、美音或语聊美声效果选项，默认值为 #VOICE_CHANGER_OFF ，即原声。详见 #VOICE_CHANGER_PRESET 。
   * 设置语聊美声效果时，Agora 推荐使用 #GENERAL_BEAUTY_VOICE_MALE_MAGNETIC 处理男声，使用 #GENERAL_BEAUTY_VOICE_FEMALE_FRESH 或 #GENERAL_BEAUTY_VOICE_FEMALE_VITALITY 处理女声，否则音频可能会产生失真。
   * @return
   * - 0: 方法调用成功
   * - < 0: 方法调用失败
   */
   /** @~english
   * @brief                Sets the local voice changer option.
   *
   * This method can be used to set the local voice effect for users in a `COMMUNICATION` channel or hosts in a `LIVE_BROADCASTING` channel.
   * Voice changer options include the following voice effects:
   *
   * - `VOICE_CHANGER_XXX`: Changes the local voice to an old man, a little boy, or the Hulk. Applies to the voice talk scenario.
   * - `VOICE_BEAUTY_XXX`: Beautifies the local voice by making it sound more vigorous, resounding, or adding spacial resonance. Applies to the voice talk and singing scenario.
   * - `GENERAL_VOICE_BEAUTY_XXX`: Adds gender-based beautification effect to the local voice. Applies to the voice talk scenario.
   *   - For a male voice: Adds magnetism to the voice.
   *   - For a female voice: Adds freshness or vitality to the voice.
   * @note
   * - To achieve better voice effect quality, Agora recommends setting the profile parameter in \ref IRtcEngine::setAudioProfile "setAudioProfile" as #AUDIO_PROFILE_MUSIC_HIGH_QUALITY (4) or #AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO (5)
   * - This method works best with the human voice, and Agora does not recommend using it for audio containing music and a human voice.
   * - Do not use this method with \ref IRtcEngine::setLocalVoiceReverbPreset "setLocalVoiceReverbPreset" , because the method called later overrides the one called earlier. For detailed considerations, see the advanced guide *Voice Changer and Reverberation*.
   * - You can call this method either before or after joining a channel.
   * @param voiceChanger   Sets the local voice changer option. The default value is #VOICE_CHANGER_OFF, which means the original voice. See details in #VOICE_CHANGER_PRESET
   * Gender-based beatification effect works best only when assigned a proper gender:
   * - For male: #GENERAL_BEAUTY_VOICE_MALE_MAGNETIC
   * - For female: #GENERAL_BEAUTY_VOICE_FEMALE_FRESH or #GENERAL_BEAUTY_VOICE_FEMALE_VITALITY
   * Failure to do so can lead to voice distortion.
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   */
	int setLocalVoiceChanger(agora::rtc::VOICE_CHANGER_PRESET voiceChanger);
   /** @~chinese
   设置本地语音混响（含虚拟立体声效果）。

   @deprecated 该方法从 v3.2.0 起废弃，请改用 \ref IRtcEngine::setAudioEffectPreset "setAudioEffectPreset" 或 \ref IRtcEngine::setVoiceBeautifierPreset "setVoiceBeautifierPreset"。

   通信场景下的用户或直播场景下的主播均可调用该方法设置本地语音混响。成功设置以后，频道内的所有用户均可听到声音效果。

   @note
   - 当使用以 `AUDIO_REVERB_FX` 为前缀的枚举值时，请确保在调用该方法前将 \ref IRtcEngine::setAudioProfile "setAudioProfile" 的 `profile` 参数设置为 #AUDIO_PROFILE_MUSIC_HIGH_QUALITY (4) 或 #AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO (5) ，否则该方法设置无效。
   - 当使用 #AUDIO_VIRTUAL_STEREO 时，Agora 推荐在调用该方法前将 `setAudioProfile` 的 `profile` 参数设置为 #AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO (5)
   - 该方法对人声的处理效果最佳，Agora 不推荐调用该方法处理含人声和音乐的音频数据。
   - 该方法不能与 \ref IRtcEngine::setLocalVoiceChanger "setLocalVoiceChanger" 方法一同使用，否则先调的方法会不生效。更多注意事项，详见进阶功能《变声与混响》。
   - 该方法在加入频道前后都能调用。

   @param reverbPreset 本地语音混响选项，默认值为 #AUDIO_REVERB_OFF ，即原声。详见 #AUDIO_REVERB_PRESET 。
   为达到更好的混响效果，Agora 推荐使用以 `AUDIO_REVERB_FX` 为前缀的枚举值。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief                Sets the preset local voice reverberation effect.
   * @note                 \arg  Do not use this method together with \ref setLocalVoiceReverb.
   *                       \arg  Do not use this method together with the \ref setLocalVoiceChanger method, because the method called later overrides the one called earlier.
   * @param reverbPreset   Sets the preset audio reverberation configuration. See \ref AUDIO_REVERB_PRESET.
   * @return               \arg  Success: 0.
   *                       \arg  Failure: <0.
   */
   /** @~english
    * Sets the local voice reverberation option, including the virtual stereo.
    *
    * @deprecated Deprecated from v3.2.0. Use \ref setAudioEffectPreset  or
    * \ref setVoiceBeautifierPreset instead.
    *
    * This method sets the local voice reverberation for users in a `COMMUNICATION` channel or hosts in a `LIVE_BROADCASTING` channel.
    * After successfully calling this method, all users in the channel can hear the voice with reverberation.
    *
    * @note
    * - When calling this method with enumerations that begin with `AUDIO_REVERB_FX`, ensure that you set profile in `setAudioProfile` as
    * `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`; otherwise, this methods cannot set the corresponding voice reverberation option.
    * - When calling this method with `AUDIO_VIRTUAL_STEREO`, Agora recommends setting the `profile` parameter in `setAudioProfile` as `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`.
    * - This method works best with the human voice, and Agora does not recommend using it for audio containing music and a human voice.
    * - Do not use this method with `setLocalVoiceChanger`, because the method called later overrides the one called earlier.
    * For detailed considerations, see the advanced guide *Voice Changer and Reverberation*.
    * - You can call this method either before or after joining a channel.
    *
    * @param reverbPreset The local voice reverberation option. The default value is `AUDIO_REVERB_OFF`,
    * which means the original voice.  See #AUDIO_REVERB_PRESET.
    * To achieve better voice effects, Agora recommends the enumeration whose name begins with `AUDIO_REVERB_FX`.
    *
    * @return
    * - 0: Success.
    * - < 0: Failure.
    */
	int setLocalVoiceReverbPreset(agora::rtc::AUDIO_REVERB_PRESET reverbPreset);

   /** @~chinese
   设置 Agora SDK 输出的日志文件。
   *
   * 默认情况下，SDK 会生成 `agorasdk.log`、`agorasdk_1.log`、`agorasdk_2.log`、`agorasdk_3.log`、`agorasdk_4.log` 这 5 个日志文件。
   * 每个文件的默认大小为 1024 KB。日志文件为 UTF-8 编码。最新的日志永远写在 `agorasdk.log` 中。`agorasdk.log` 写满后，SDK 会从 1-4 中删除修改时间最早的一个文件，
   * 然后将 `agorasdk.log` 重命名为该文件，并建立新的 `agorasdk.log` 写入最新的日志。
   *
   * @note 如需调用本方法，请在调用 \ref agora::rtc::IRtcEngine::initialize "initialize" 方法初始化 IRtcEngine 对象后立即调用，否则可能造成输出日志不完整。
   *
   * @see \ref IRtcEngine::setLogFileSize "setLogFileSize"
   * @see \ref IRtcEngine::setLogFilter "setLogFilter"
   *
   * @param filePath 日志文件的完整路径。默认路径为 `C:\Users\<user_name>\AppData\Local\Agora\<process_name>\agorasdk.log`。请确保指定的目录存在而且可写。你可通过该参数修改日志文件名。
   *
   * @return
   * - 0: 方法调用成功
   * - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Specifies an SDK output log file.
   * @brief          By default, the SDK outputs five log files, `agorasdk.log`, `agorasdk_1.log`, `agorasdk_2.log`, `agorasdk_3.log`, `agorasdk_4.log`, each with a default size of 1024 KB.
   * These log files are encoded in UTF-8. The SDK writes the latest logs in `agorasdk.log`. When `agorasdk.log` is full, the SDK deletes the log file with the earliest
   * modification time among the other four, renames `agorasdk.log` to the name of the deleted log file, and create a new `agorasdk.log` to record latest logs.
   * @note           Ensure that you call this method immediately after calling the \ref initialize method, otherwise the output log may not be complete.
   * @param filePath The absolute path of log files. The default file path is `C: \Users\<user_name>\AppData\Local\Agora\<process_name>\agorasdk.log`.
   * Ensure that the directory for the log files exists and is writable. You can use this parameter to rename the log files.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int setLogFile(const char* filePath);

   /** @~chinese
   设置日志输出等级。

   设置 Agora SDK 的输出日志输出等级。不同的输出等级可以单独或组合使用。日志级别顺序依次为 OFF、CRITICAL、ERROR、WARNING、INFO 和 DEBUG。选择一个级别，你就可以看到在该级别之前所有级别的日志信息。

   例如，你选择 WARNING 级别，就可以看到在 CRITICAL、ERROR 和 WARNING 级别上的所有日志信息。

   @see \ref IRtcEngine::setLogFile "setLogFile"
   @see \ref IRtcEngine::setLogFileSize "setLogFileSize"

   @param filter 设置过滤等级: #LOG_FILTER_TYPE 。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the output log level of the SDK.
   * @brief          You can use one or a combination of the log filter levels. The log level follows the sequence of OFF, CRITICAL, ERROR, WARNING, INFO, and DEBUG. Choose a level to see the logs preceding that level.
   * @brief          If you set the log level to WARNING, you see the logs within levels CRITICAL, ERROR, and WARNING.
   * @param filter   Sets the log filter level. See \ref LOG_FILTER_TYPE.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int setLogFilter(unsigned int filter);
   /** @~chinese
   设置 Agora SDK 输出的单个日志文件大小。
   *
   * 默认情况下，SDK 会生成 `agorasdk.log`、`agorasdk_1.log`、`agorasdk_2.log`、`agorasdk_3.log`、`agorasdk_4.log` 这 5 个日志文件。
   * 每个文件的默认大小为 1024 KB。日志文件为 UTF-8 编码。最新的日志永远写在 `agorasdk.log` 中。`agorasdk.log` 写满后，SDK 会从 1-4 中删除修改时间最早的一个文件，
   * 然后将 `agorasdk.log` 重命名为该文件，并建立新的 `agorasdk.log` 写入最新的日志。
   *
   * @note 如果想要设置日志文件的大小，则需要在 \ref IRtcEngine::setLogFile "setLogFile" 前调用该方法，否则日志会被清空。
   *
   * @see \ref IRtcEngine::setLogFile "setLogFile"
   * @see \ref IRtcEngine::setLogFilter "setLogFilter"
   *
   * @param fileSizeInKBytes 单个日志文件的大小，单位为 KB。默认值为 1024 KB。如果你将 `fileSizeInKByte` 设为 1024 KB，SDK 会最多输出 5 MB 的日志文件。如果你将 `fileSizeInKByte` 设为小于 1024 KB，单个日志文件最大仍为 1024 KB。
   *
   * @return
   * - 0: 方法调用成功
   * - < 0: 方法调用失败
   */
   /** @~english
   * @brief                   Sets the log file size (KB).
   *
   * @note If you want to set the log file size, ensure that you call
   * this method before \ref IRtcEngine::setLogFile "setLogFile", or the logs are cleared.
   *
   * By default, the SDK outputs five log files, `agorasdk.log`, `agorasdk_1.log`, `agorasdk_2.log`, `agorasdk_3.log`, `agorasdk_4.log`, each with a default size of 1024 KB.
   * These log files are encoded in UTF-8. The SDK writes the latest logs in `agorasdk.log`. When `agorasdk.log` is full, the SDK deletes the log file with the earliest
   * modification time among the other four, renames `agorasdk.log` to the name of the deleted log file, and create a new `agorasdk.log` to record latest logs.
   *
   * @param fileSizeInKBytes  The size (KB) of a log file. The default value is 1024 KB. If you set `fileSizeInKByte` to 1024 KB,
   * the SDK outputs at most 5 MB log files; if you set it to less than 1024 KB, the maximum size of a log file is still 1024 KB.
   * @return                  \arg  0: Success.
   *                          \arg  < 0: Failure.
   */
	int setLogFileSize(unsigned int fileSizeInKBytes);
   /** @~chinese
   @deprecated 该方法已废弃，请改用 \ref IRtcEngine::setLocalRenderMode(RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) "setLocalRenderMode"2。

   设置本地视图显示模式。

   该方法设置本地视图显示模式。 App 可以多次调用此方法更改显示模式。
   @param renderMode #RENDER_MODE_TYPE 。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @deprecated        This method is deprecated, use the \ref  AgoraRtcEngine::setLocalRenderMode( RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode ) "setLocalRenderMode"2 method instead.
   * @brief             Sets the local video display mode.
   * @brief             This method can be called multiple times during a call to change the display mode.
   * @param renderMode  Sets the local video display mode. See \ref RENDER_MODE_TYPE.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int setLocalRenderMode(agora::rtc::RENDER_MODE_TYPE renderMode);

   /** @~chinese
   更新本地视图显示模式。

   初始化本地用户视图后，你可以调用该方法更新本地用户视图的渲染和镜像模式。该方法只影响本地用户看到的视频画面，不影响本地发布视频。

   @note
   - 请在调用 \ref IRtcEngine::setupLocalVideo "setupLocalVideo" 方法初始化本地视图后，调用该方法。
   - 你可以在通话中多次调用该方法，多次更新本地用户视图的显示模式。

   @param renderMode 本地视图的渲染模式，详见 #RENDER_MODE_TYPE
   @param mirrorMode
   - 本地视图的镜像模式，详见 #VIDEO_MIRROR_MODE_TYPE
   - **Note**: 如果你使用前置摄像头，默认启动本地用户视图镜像模式；如果你使用后置摄像头，默认关闭本地视图镜像模式。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Updates the display mode of the local video view.
   *
   * After initializing the local video view, you can call this method to update its rendering and mirror modes. It affects only the video view that the local user sees, not the published local video stream.
   * @note
   * - Ensure that you have called the \ref setupLocalVideo method to initialize the local video view before calling this method.
   * - During a call, you can call this method as many times as necessary to update the display mode of the local video view.
   * @param renderMode  The rendering mode of the local video view. See \ref RENDER_MODE_TYPE.
   * @param mirrorMode  The mirror mode of the local video view. See  \ref VIDEO_MIRROR_MODE_TYPE.
                        If you use a front camera, the SDK enables the mirror mode by default; if you use a rear camera, the SDK disables the mirror mode by default.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
    int setLocalRenderMode( agora::rtc::RENDER_MODE_TYPE renderMode, agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode );
   /** @~chinese
   @deprecated 该方法已废弃，请使用 \ref IRtcEngine::setRemoteRenderMode(uid_t userId, RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) "setRemoteRenderMode"2。

   设置远端视图显示模式。

   该方法设置远端视图显示模式。App 可以多次调用此方法更改显示模式。

   @param userId 远端用户 ID。
   @param renderMode  #RENDER_MODE_TYPE 。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @deprecated        This method is deprecated, use the \ref AgoraRtcEngine::setRemoteRenderMode(agora::rtc::uid_t userId, agora::rtc::RENDER_MODE_TYPE renderMode, agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode) "setRemoteRenderMode"2 method instead.
   * @brief             Sets the video display mode of a specified remote user.
   * @brief             This method can be called multiple times during a call to change the display mode.
   * @param userId      ID of the remote user.
   * @param renderMode  Sets the video display mode. See \ref RENDER_MODE_TYPE.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int setRemoteRenderMode(agora::rtc::uid_t userId, agora::rtc::RENDER_MODE_TYPE renderMode);

   /** @~chinese

   更新远端视图显示模式。

   初始化远端用户视图后，你可以调用该方法更新远端用户视图在本地显示时的渲染和镜像模式。该方法只影响本地用户看到的视频画面。

   @note
   - 请在调用 \ref IRtcEngine::setupRemoteVideo "setupRemoteVideo" 方法初始化远端视图后，调用该方法。
   - 你可以在通话中多次调用该方法，多次更新远端用户视图的显示模式。

   @param userId 远端用户 ID。
   @param renderMode 远端用户视图的渲染模式，详见 #RENDER_MODE_TYPE
   @param mirrorMode
   - 远端用户视图的镜像模式，详见 #VIDEO_MIRROR_MODE_TYPE
   - **Note**: 默认关闭远端用户的镜像模式。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Updates the display mode of the video view of a remote user.
   *
   * After initializing the video view of a remote user, you can call this method to update its rendering and mirror modes. This method affects only the video view that the local user sees.
   * @note
   * - Ensure that you have called the \ref setupRemoteVideo method to initialize the remote video view before calling this method.
   * - During a call, you can call this method as many times as necessary to update the display mode of the video view of a remote user.
   * @param userId      The ID of the remote user.
   * @param renderMode  The rendering mode of the remote video view. See \ref RENDER_MODE_TYPE.
   * @param mirrorMode  The mirror mode of the remote video view. See \ref VIDEO_MIRROR_MODE_TYPE. The SDK disables the mirror mode by default.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
   int setRemoteRenderMode( agora::rtc::uid_t userId, agora::rtc::RENDER_MODE_TYPE renderMode, agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode );
   /** @~chinese
   @deprecated 该方法已废弃，请改用 \ref IRtcEngine::setupLocalVideo "setupLocalVideo"
   或 \ref IRtcEngine::setLocalRenderMode(RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) "setLocalRenderMode"

   设置本地视频镜像模式。

   @warning 请在调用 \ref agora::rtc::IRtcEngine::setupLocalVideo "setupLocalVideo" 方法初始化本地视图后，调用该方法。

   @param mirrorMode  详见 #VIDEO_MIRROR_MODE_TYPE

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @deprecated This method is deprecated, use the \ref AgoraRtcEngine::setupLocalVideo "setupLocalVideo" or \ref AgoraRtcEngine::setLocalRenderMode(agora::rtc::RENDER_MODE_TYPE renderMode, agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode) "setLocalRenderMode" method instead.
   * @brief             Sets the local video mirror mode.
   * @brief             You must call this method before calling the \ref startPreview method, otherwise the mirror mode will not work.
   * @note              The SDK enables the mirror mode by default.
   * @param mirrorMode  Sets the local video mirror mode. See \ref VIDEO_MIRROR_MODE_TYPE.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int setLocalVideoMirrorMode(agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode);

   /** @~chinese
   开关双流模式。

   该方法设置单流（默认）或者双流模式。发送端开启双流模式后，接收端可以选择接收大流还是小流。其中，大流指高分辨率、高码率的视频流，小流指低分辨率、低码率的视频流。

   @note 该方法在加入频道前后都能调用。

   @param enabled
   - true: 双流。
   - false: 单流。
   */
   /** @~english
   * @brief          Sets the stream mode to the single-stream (default) or dual-stream mode. (Live broadcast only.)
   * @brief          If the dual-stream mode is enabled, the receiver can choose to receive the high stream (high-resolution and high-bitrate video stream), or the low stream (low-resolution and low-bitrate video stream).
   * @param enabled  Sets the stream mode:
   *                 \arg  true: Dual-stream mode.
   *                 \arg  false: (Default) Single-stream mode.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int enableDualStreamMode(bool enabled);
   /** @~chinese
   设置外部音频采集参数。

   @note 请在 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 和 \ref IRtcEngine::startPreview "startPreview" 前调用该方法。

   @param enabled
   - true: 开启使用外部音频源的功能；
   - false: 关闭使用外部音频源的功能（默认）。
   @param sampleRate 外部音频源的采样率 (Hz)，可设置为 8000，16000，32000，44100 或 48000。
   @param channels 外部音频源的通道数，可设置为 1 或 2:
   - 1: 单声道
   - 2: 双声道

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Sets the external audio source. Please call this method before \ref joinChannel.
   * @param enabled     Sets whether to enable/disable the external audio source:
   *                    \arg  true: Enables the external audio source.
   *                    \arg  false: (Default) Disables the external audio source.
   * @param sampleRate  Sets the sample rate (Hz) of the external audio source, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
   * @param channels    Sets the number of audio channels of the external audio source:
   *                    \arg  1: Mono.
   *                    \arg  2: Stereo.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int setExternalAudioSource(bool enabled, int sampleRate, int channels);

   /** @~chinese
   设置外部音频渲染。
   *
   * 该方法适用于需要自行渲染音频的场景。开启外部音频渲染后，你可以通过调用
   * \ref agora::media::IMediaEngine::pullAudioFrame "pullAudioFrame" 方法拉取远端音频数据。
   * App 可以对拉取到的原始音频数据进行处理后再渲染，获取想要的音频效果。
   *
   * @note
   * - 开启外部音频渲染后，App 会无法从
   * \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" 回调中获得数据。
   * - 该方法需要在加入频道前调用。
   *
   * @param enabled
   * - true: 开启外部音频渲染。
   * - false: （默认）关闭外部音频渲染。
   * @param sampleRate 外部音频渲染的采样率 (Hz)，可设置为 16000，32000，44100 或 48000。
   * @param channels 外部音频渲染的声道数，可设置为 1 或 2:
   * - 1: 单声道
   * - 2: 双声道
   *
   * @return
   * - 0: 方法调用成功
   * - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Sets the external audio sink. This method applies to scenarios where you want to use external audio data for playback. After enabling the external audio sink, you can call the \ref agora::media::ue4::AgoraMediaEngine::pullAudioFrame "pullAudioFrame" method to pull the remote audio data, process it, and play it with the audio effects that you want.
   * @note              Once you enable the external audio sink, the app will not retrieve any audio data from the \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" callback.
   * @param enabled     \arg  true: Enables the external audio sink.
   *                    \arg  false: (Default) Disables the external audio sink.
   * @param sampleRate  Sets the sample rate (Hz) of the external audio sink, which can be set as 8000, 16000, 32000, 44100 or 48000.
   * @param channels    Sets the number of audio channels of the external audio sink:
   *                    \arg  1: Mono.
   *                    \arg  2: Stereo.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int setExternalAudioSink(bool enabled, int sampleRate, int channels);

   /** @~chinese
   设置采集的音频格式。

   该方法设置 \ref agora::media::IAudioFrameObserver::onRecordAudioFrame "onRecordAudioFrame" 回调的采集音频格式。

   @note 该方法需要在加入频道前调用。

   @param sampleRate 指定 \ref agora::media::IAudioFrameObserver::onRecordAudioFrame "onRecordAudioFrame" 中返回数据的采样率，可设置为 8000、 16000、 32000、 44100 或 48000。
   @param channel 指定 \ref agora::media::IAudioFrameObserver::onRecordAudioFrame "onRecordAudioFrame" 中返回数据的通道数，可设置为 1 或 2:
   - 1: 单声道
   - 2: 双声道
   @param mode \ref agora::media::IAudioFrameObserver::onRecordAudioFrame "onRecordAudioFrame" 回调的使用模式: #RAW_AUDIO_FRAME_OP_MODE_TYPE 。
   @param samplesPerCall 指定 \ref agora::media::IAudioFrameObserver::onRecordAudioFrame "onRecordAudioFrame" 中返回数据的采样点数，如 RTMP/RTMPS 推流应用中通常为 1024。

   @note SDK 会根据该采样间隔触发 `onRecordAudioFrame` 回调。请确保采样间隔不得小于 0.01 (s)。其中，采样间隔 = samplesPerCall/(sampleRate × channel)。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief                Sets the audio recording format for the \ref agora::media::IAudioFrameObserver::onRecordAudioFrame "onRecordAudioFrame" callback.
   * @param sampleRate     Sets the sample rate (`samplesPerSec`) returned in the `onRecordAudioFrame` callback, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
   * @param channel        Sets the number of audio channels (`channels`) returned in the `onRecordAudioFrame` callback:
   *                       \arg  1: Mono.
   *                       \arg  2: Stereo.
   * @param mode           Sets the use mode (see \ref RAW_AUDIO_FRAME_OP_MODE_TYPE) of the `onRecordAudioFrame` callback.
   * @param samplesPerCall Sets the sample points (`samples`) returned in the `onRecordAudioFrame` callback. `samplesPerCall` is usually set as 1024 for stream pushing.
   * @note The SDK triggers the `onRecordAudioFrame` callback according to the sample interval. Ensure that the sample interval ≥ 0.01 (s). And, Sample interval (sec) = `samplePerCall`/(`sampleRate` × `channel`).
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   */
	int setRecordingAudioFrameParameters(
		int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall);

   /** @~chinese
   设置播放的声音格式。

   @note 该方法需要在加入频道前调用。

   @param sampleRate 指定 \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" 中返回数据的采样率，可设置为 8000，16000，32000，44100 或 48000。
   @param channel 指定 \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" 中返回数据的通道数，可设置为 1 或 2:
   - 1: 单声道
   - 2: 双声道
   @param mode 指定 \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" 的使用模式: #RAW_AUDIO_FRAME_OP_MODE_TYPE 。
   @param samplesPerCall 指定 \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" 中返回数据的采样点数，如RTMP推流应用中通常为 1024。

   @note SDK 会根据该采样间隔触发 `onPlaybackAudioFrame` 回调。请确保采样间隔不得小于 0.01 (s)。其中，采样间隔 = samplesPerCall/(sampleRate × channel)。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief                Sets the audio playback format for the \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" callback.
   * @param sampleRate     Sets the sample rate (`samplesPerSec`) returned in the `onPlaybackAudioFrame` callback, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
   * @param channel        Sets the number of channels (`channels`) returned in the `onPlaybackAudioFrame` callback:
   *                       \arg  1: Mono.
   *                       \arg  2: Stereo.
   * @param mode           Sets the use mode (see \ref RAW_AUDIO_FRAME_OP_MODE_TYPE) of the onPlaybackAudioFrame callback.
   * @param samplesPerCall Sets the sample points (`samples`) returned in the `onPlaybackAudioFrame` callback. `samplesPerCall` is usually set as 1024 for stream pushing.
   * @note The SDK triggers the `onPlaybackAudioFrame` callback according to the sample interval. Ensure that the sample interval ≥ 0.01 (s). And, Sample interval (sec) = `samplePerCall`/(`sampleRate` × `channel`).
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   */
	int setPlaybackAudioFrameParameters(
		int sampleRate, int channel, agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall);
   /** @~chinese
   设置采集与播放声音混音后的数据格式

   @note 该方法需要在加入频道前调用。

   @param sampleRate 指定 \ref agora::media::IAudioFrameObserver::onMixedAudioFrame "onMixedAudioFrame" 中返回数据的采样率，可设置为 8000，16000，32000，44100 或 48000。
   @param samplesPerCall 指定 \ref agora::media::IAudioFrameObserver::onMixedAudioFrame "onMixedAudioFrame" 中返回数据的采样点数，如 RTMP/RTMPS 推流应用中通常为 1024。

   @note SDK 会根据该采样间隔触发 `onMixedAudioFrame` 回调。请确保采样间隔不得小于 0.01 (s)。其中，采样间隔 = samplesPerCall/(sampleRate × channels)。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief                Sets the mixed audio format for the \ref agora::media::IAudioFrameObserver::onMixedAudioFrame "onMixedAudioFrame" callback.
   * @param sampleRate     Sets the sample rate (`samplesPerSec`) returned in the `onMixedAudioFrame` callback, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
   * @param samplesPerCall Sets the sample points (`samples`) returned in the `onMixedAudioFrame` callback. samplesPerCall is usually set as 1024 for stream pushing.
   * @note The SDK triggers the `onMixedAudioFrame` callback according to the sample interval. Ensure that the sample interval ≥ 0.01 (s). And, Sample interval (sec) = `samplePerCall`/(`sampleRate` × `channels`).
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   */
	int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall);
   /** @~chinese
   调节音频采集信号音量。

   @note 该方法在加入频道前后都能调用。

   @param volume 录音信号音量。为避免回声并提升通话质量，Agora 建议将 volume 值设为 [0,100]。如果
   volume 值需超过 100，联系[技术支持](https://agora-ticket.agora.io/):
   - 0: 静音；
   - 100: 原始音量。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Adjusts the recording volume.
   * @note You can call this method either before or after joining a channel.
   * @param volume   Recording volume. To avoid echoes and
   *  improve call quality, Agora recommends setting the value of volume between
   *  0 and 100. If you need to set the value higher than 100, contact
   *  support@agora.io first.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int adjustRecordingSignalVolume(int volume);
   /** @~chinese
   调节本地播放的所有远端用户信号音量。
   @note
   - 该方法调节的是本地播放的所有远端用户混音后的音量。
   - 从 v2.3.2 开始，静音本地音频需同时调用 `adjustPlaybackSignalVolume` 和 \ref IRtcEngine::adjustAudioMixingPlayoutVolume "adjustAudioMixingPlayoutVolume" 方法，并将 `volume` 设置为 `0`。
   - 该方法在加入频道前后都能调用。

   @param volume 播放音量。为避免回声并提升通话质量，Agora 建议将 volume 值设为 [0,100]。如果
   volume 值需超过 100，联系[技术支持](https://agora-ticket.agora.io/):
   - 0: 静音；
   - 100: 原始音量。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Adjusts the playback volume of the voice.
   * @note
   * - This method adjusts the playback volume that is the mixed volume of all remote users.
   * - You can call this method either before or after joining a channel.
   * - To mute the local audio playback, call both the `adjustPlaybackSignalVolume` and \ref adjustAudioMixingVolume methods and set the volume as `0`.
   * @param volume   The playback volume of the voice. To avoid echoes and
   * improve call quality, Agora recommends setting the value of volume between
   *  0 and 100. If you need to set the value higher than 100, contact support@agora.io first.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int adjustPlaybackSignalVolume(int volume);

   /** @~chinese
   @deprecated 该方法已废弃。自 Native SDK v3.0.0 及之后，SDK 自动开启与 Web SDK 的互通，无需调用该方法开启。

   打开直播场景下与 Agora Web SDK 的互通。

   @note
   - 该方法仅适用于直播场景。通信场景默认打开与 Web SDK 的互通。
   - 如果有用户通过 Web SDK 加入频道，请确保调用该方法，否则 Web 端用户看 Native 端的画面会是黑屏。

   @param enabled
   - true: 打开互通；
   - false: 关闭互通（默认）。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @deprecated This method is deprecated. The Native SDK automatically enables interoperability with the Web SDK, so you no longer need to call this method.
   * @brief          Enables interoperability with the Agora Web SDK.
   * @note           \arg  This method applies only to the Live-broadcast profile. In the Communication profile, interoperability with the Agora Web SDK is enabled by default.
   *                 \arg  If the channel has Web SDK users, ensure that you call this method, or the video of the Native user will be a black screen for the Web user.
   * @param enabled  Sets whether to enable/disable interoperability with the Agora Web SDK:
   *                 \arg  true: Enable.
   *                 \arg  false: (Default) Disable.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int enableWebSdkInteroperability(bool enabled);

   /** @~chinese
   设置弱网条件下发布的音视频流回退选项。

   网络不理想的环境下，实时通信音视频的质量都会下降。使用该接口并将 `option` 设置为 #STREAM_FALLBACK_OPTION_AUDIO_ONLY (2) 后，SDK 会在上行弱网且音视频质量严重受影响时，自动关断视频流，从而保证或提高音频质量。同时 SDK 会持续监控网络质量，并在网络质量改善时恢复音视频流。当本地推流回退为音频流时，或由音频流恢复为音视频流时，SDK 会触发本地发布的媒体流已回退为音频流 \ref agora::rtc::IRtcEngineEventHandler::onLocalPublishFallbackToAudioOnly "onLocalPublishFallbackToAudioOnly" 回调。

   @note
   - 视频直播场景下，旁路推流的发流用户（即主播）设置 `STREAM_FALLBACK_OPTION_AUDIO_ONLY (2)` 可能导致 CDN 观众听到的声音有所延迟。Agora 不建议主播使用视频流回退机制。
   - 该方法需要在加入频道前调用。

   @param option 本地发流回退处理选项：
   - #STREAM_FALLBACK_OPTION_DISABLED (0)：（默认）上行网络较弱时，不对音视频流作回退处理，但不能保证音视频流的质量
   - #STREAM_FALLBACK_OPTION_AUDIO_ONLY (2)：上行网络较弱时只发布音频流

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the fallback option for the locally published video stream based on the network conditions.
   * @brief          If *option* is set as `STREAM_FALLBACK_OPTION_AUDIO_ONLY(2)`, the SDK will:
   *                 \arg  Disable the upstream video but enable audio only when the network conditions deteriorate and cannot support both video and audio.
   *                 \arg  Re-enable the video when the network conditions improve.
   * @brief          When the locally published video stream falls back to audio only or when the audio-only stream switches back to the video, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onLocalPublishFallbackToAudioOnly "onLocalPublishFallbackToAudioOnly" callback.
   * @note
   * - Agora does not recommend using this method for CDN live streaming, because the remote CDN live user will have a noticeable lag when the locally published video stream falls back to audio only.
   * - Ensure that you call this method before joining a channel.
   * @param option   Sets the fallback option for the locally published video stream:
   *                 \arg  \ref STREAM_FALLBACK_OPTION_DISABLED (0): (Default) No fallback behavior for the locally published video stream when the uplink network condition is poor. The stream quality is not guaranteed.
   *                 \arg  \ref STREAM_FALLBACK_OPTION_AUDIO_ONLY (2): The locally published video stream falls back to audio only when the uplink network condition is poor.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int setLocalPublishFallbackOption(agora::rtc::STREAM_FALLBACK_OPTIONS option);

   /** @~chinese
   设置弱网条件下订阅的音视频流的回退选项。

   默认 `option` 为 #STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW (1) 。
   如果你使用本方法并将 `option` 设置为 #STREAM_FALLBACK_OPTION_AUDIO_ONLY (2)，
   SDK 会在下行弱网且音视频质量严重受影响时，将视频流切换为小流，或关断视频流，从而保证或提高音频质量。
   同时 SDK 会持续监控网络质量，并在网络质量改善时恢复音视频流。
   当远端订阅流回退为音频流时，或由音频流恢复为音视频流时，SDK 会触发 \ref agora::rtc::IRtcEngineEventHandler::onRemoteSubscribeFallbackToAudioOnly "onRemoteSubscribeFallbackToAudioOnly" 回调。

   @note 该方法需要在加入频道前调用。

   @param  option 详见 #STREAM_FALLBACK_OPTIONS 。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the fallback option for the remotely subscribed video stream based on the network conditions.
   * @brief          The default setting for @p option is \ref STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW, where the remotely subscribed video stream falls back to the low-stream video (low resolution and low bitrate) under poor downlink network conditions.
   * @brief          If *option* is set as \ref STREAM_FALLBACK_OPTION_AUDIO_ONLY, the SDK automatically switches the video from a high-stream to a low-stream, or disables the video when the downlink network conditions cannot support both audio and video to guarantee the quality of the audio. The SDK monitors the network quality and restores the video stream when the network conditions improve.
   * @brief          When the remotely subscribed video stream falls back to audio only or when the audio-only stream switches back to the video stream, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onRemoteSubscribeFallbackToAudioOnly "onRemoteSubscribeFallbackToAudioOnly" callback.
   * @note Ensure that you call this method before joining a channel.
   * @param  option  Sets the fallback option for the remotely subscribed video stream. See \ref STREAM_FALLBACK_OPTIONS.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int setRemoteSubscribeFallbackOption(agora::rtc::STREAM_FALLBACK_OPTIONS option);

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
   /** @~chinese
   切换前置/后置摄像头

   @note
   - 该方法仅适用于 Android 和 iOS 平台。
   - 该方法需要在相机启动（如通过调用 \ref IRtcEngine::startPreview "startPreview" 或 \ref IRtcEngine::joinChannel "joinChannel" 实现）后调用。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Switches between front and rear cameras.
   * @note     This method is for Android and iOS only.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int switchCamera();

   /** @~english
   * @brief             Switches between front and rear cameras.
   * @note              This method is for Android and iOS only.
   * @param direction   Sets the camera to be used:
   *                    \arg  CAMERA_DIRECTION.CAMERA_REAR: Use the rear camera.
   *                    \arg  CAMERA_DIRECTION.CAMERA_FRONT: Use the front camera.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int switchCamera(CAMERA_DIRECTION direction);

   /** @~chinese
   设置默认的语音路由。

   该方法设置接收到的语音从听筒或扬声器出声。如果用户不调用本方法，语音默认从听筒出声。

   各频道场景下默认的语音路由：
   - 语音通话：听筒
   - 视频通话：扬声器。如果有用户在频道中使用 \ref IRtcEngine::disableVideo "disableVideo" 、 \ref IRtcEngine::muteLocalVideoStream "muteLocalVideoStream" 或 \ref IRtcEngine::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams" 方法关闭视频，则语音路由会自动切换回听筒。
   - 直播：扬声器
   - 游戏语音：扬声器

   @note
   - 该方法仅适用于 Android 和 iOS 平台。
   - 在 iOS 平台上，该方法只在纯音频模式下工作，在有视频的模式下不工作。
   - 该方法需要在 \ref IRtcEngine::joinChannel "joinChannel" 前设置，否则不生效。如需在加入频道后更改默认语音路由，请调用 \ref IRtcEngine::setEnableSpeakerphone "setEnableSpeakerphone" 方法。

   @param defaultToSpeaker 设置默认的语音路由
   - true: 语音路由为外放（扬声器）。如果设备连接了耳机或蓝牙，则无法切换到外放。
   - false:（默认）语音路由为听筒。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief                   Sets the default audio playback route.
   * @brief                   This method sets whether the received audio is routed to the earpiece or speakerphone by default before joining a channel. If a user does not call this method, the audio is routed to the earpiece by default. If you need to change the default audio route after joining a channel, call the  \ref setEnableSpeakerphone method.
   *
   * The default setting for each profile:
   * - `COMMUNICATION`: In a voice call, the default audio route is the earpiece. In a video call, the default audio route is the speakerphone.
   * - `LIVE_BROADCASTING`: Speakerphone.
   *
   * @note                    \arg  This method is for Android and iOS only.
   *                          \arg  Call this method before calling the \ref joinChannel method.
   *                          \arg  Regardless of whether the audio is routed to the speakerphone or earpiece by default, once a headset is plugged in or Bluetooth device is connected, the default audio route changes. The default audio route switches to the earpiece once removing the headset or disconnecting the Bluetooth device.
   * @param defaultToSpeaker  Sets the default audio route:
   *                          -  true: Route the audio to the speakerphone. If the playback device connects to the earpiece or Bluetooth, the audio cannot be routed to the speakerphone.
   *                          -  false: (Default) Route the audio to the earpiece. If a headset is plugged in, the audio is routed to the headset.
   * @return                  \arg  0: Success.
   *                          \arg  < 0: Failure.
   */
	int setDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker);

   /** @~chinese
   启用/关闭扬声器播放

   该方法设置是否将语音路由设到扬声器（外放）。 你可以在 \ref IRtcEngine::setDefaultAudioRouteToSpeakerphone "setDefaultAudioRouteToSpeakerphone" 方法中查看默认的语音路由。

   在 Android 上，\ref IRtcEngine::setAudioProfile "setAudioProfile" 中 `scenario` 及 \ref IRtcEngine::setChannelProfile "setChannelProfile" 的设置
   会影响 `setEnableSpeakerphone` 的行为。`setEnableSpeakerphone` 不生效的情况如下：
   - 当 `scenario` 为 #AUDIO_SCENARIO_GAME_STREAMING 时，所有用户都无法切换音频播放路由。
   - 当 `scenario` 为 #AUDIO_SCENARIO_DEFAULT 或 #AUDIO_SCENARIO_SHOWROOM 时，直播场景中的观众无法切换音频播放路由，且当频道中只有一个主播时，该主播也无法切换音频播放路由。
   - 当 `scenario` 为 #AUDIO_SCENARIO_EDUCATION 时，直播场景中的观众无法切换音频播放路由。

   @note
   - 该方法仅适用于 Android 和 iOS 平台。
   - 请确保在调用此方法前已调用过 \ref IRtcEngine::joinChannel "joinChannel" 方法。
   - 调用该方法后，SDK 将返回 \ref IRtcEngineEventHandler::onAudioRouteChanged "onAudioRouteChanged" 回调提示状态已更改。

   @param speakerOn 设置是否切换语音路由到扬声器（外放）：
   - true: 切换到外放。如果设备连接了耳机或蓝牙，则无法切换到外放。
   - false: 切换到听筒。如果设备连接了耳机，则语音路由走耳机。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
    Enables/Disables the audio playback route to the speakerphone.

    This method sets whether the audio is routed to the speakerphone or earpiece.

    See the default audio route explanation in the \ref setDefaultAudioRouteToSpeakerphone method and check whether it is necessary to call this method.

    @note
    - This method is for Android and iOS only.
    - Ensure that you have successfully called the \ref joinChannel method before calling this method.
    - After calling this method, the SDK returns the \ref IRtcEngineEventHandler::onAudioRouteChanged "onAudioRouteChanged" callback to indicate the changes.
    - This method does not take effect if a headset is used.
    - Settings of \ref setAudioProfile and \ref setChannelProfile affect the call
    result of `setEnableSpeakerphone`. The following are scenarios where `setEnableSpeakerphone` does not take effect:
    - If you set `scenario` as `AUDIO_SCENARIO_GAME_STREAMING`, no user can change the audio playback route.
    - If you set `scenario` as `AUDIO_SCENARIO_DEFAULT` or `AUDIO_SCENARIO_SHOWROOM`, the audience cannot change
    the audio playback route. If there is only one broadcaster is in the channel, the broadcaster cannot change
    the audio playback route either.
    - If you set `scenario` as `AUDIO_SCENARIO_EDUCATION`, the audience cannot change the audio playback route.

    @param speakerOn Sets whether to route the audio to the speakerphone or earpiece:
    - true: Route the audio to the speakerphone. If the playback device connects to the earpiece or Bluetooth, the audio cannot be routed to the speakerphone.
    - false: Route the audio to the earpiece. If a headset is plugged in, the audio is routed to the headset.

    @return
    - 0: Success.
    - < 0: Failure.
    */
	int setEnableSpeakerphone(bool speakerOn);

   /** @~chinese
   设置耳返音量。

   @note
   - 该方法仅适用于 Android 和 iOS 平台。
   - 用户必须使用有线耳机才能听到耳返效果。
   - 该方法在加入频道前后都能调用。

   @param volume 设置耳返音量，取值范围在 [0,100]。默认值为 100

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the volume of the in-ear monitor.
   *
   * @note
   * - This method is for Android and iOS only.
   * - Users must use wired earphones to hear their own voices.
   * - You can call this method either before or after joining a channel.
   * @param volume   Sets the volume of the in-ear monitor. The value ranges between 0 and 100 (default).
   * @note           This method is for Android and iOS only.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int setInEarMonitoringVolume(int volume);

   /** @~chinese
   查询扬声器启用状态。

   @note
   - 该方法仅适用于 Android 和 iOS 平台。
   - 该方法在加入频道前后都能调用。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Checks whether the speakerphone is enabled.
   * @note
   * - This method is for Android and iOS only.
   * - You can call this method either before or after joining a channel.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	bool isSpeakerphoneEnabled();
#endif
    
#if defined(__ANDROID__)
   /** @~chinese
    * 开启/关闭本地人脸检测。仅适用于 Android 和 iOS。
    *
    * @note 该方法在加入频道前后都能调用.
    *
    * 开启本地人脸检测后，SDK 会触发 \ref IRtcEngineEventHandler::onFacePositionChanged "onFacePositionChanged" 回调向你报告人脸检测的信息：
    * - 摄像头采集的画面大小
    * - 人脸在画面中的位置
    * - 人脸距设备屏幕的距离
    *
    * @param enable 是否开启人脸检测：
    * - true：开启人脸检测
    * - false：（默认）关闭人脸检测
    * @return
    * - 0：方法调用成功
    * - < 0：方法调用失败
    */
   /** @~english
    * @brief         Enables/Disables face detection for the local user. Applies to Android and iOS only.
    * @brief         Once face detection is enabled, the SDK triggers the \ref IRtcEngineEventHandler::onFacePositionChanged "onFacePositionChanged" callback
    * @brief         to report the face information of the local user, which includes the following aspects:
    * @brief            - The width and height of the local video.
    * @brief            - The position of the human face in the local video.
    * @brief            - The distance between the human face and the device screen.
    * @param         enable Determines whether to enable the face detection function for the local user:
    *                   - true: Enable face detection.
    *                   - false: (Default) Disable face detection.
    * @return         \arg  0: Success.
    *                 \arg  < 0: Failure.
    */
   int enableFaceDetection( bool enable );
    
#endif

#if (defined(__APPLE__) && TARGET_OS_IOS)
   /** @~chinese
   设置 SDK 对 Audio Session 的控制权限

   该接口可以在任意时候调用，可以在任意时候通过该方法把控制权交还给 SDK。

   @note
   - 该方法仅适用于 iOS 平台。
   - 该方法限制 Agora SDK 对 Audio Session 的操作权限。在默认情况下，SDK 和 App 对 Audio Session 都有控制权，但某些场景下，App 会希望限制 Agora SDK 对 Audio Session 的控制权限，而使用其他应用或第三方组件对 Audio Session 进行操控。调用该方法可以实现该功能。
   - 一旦调用该方法限制了 Agora SDK 对 Audio Session 的控制权限， SDK 将无法对 Audio Session 进行相关设置，而需要用户自己或第三方组件进行维护。
   - 该方法在加入频道前后都能调用。

   @param restriction Agora SDK 对 Audio Session 的控制权限，详见: #AUDIO_SESSION_OPERATION_RESTRICTION 。该 restriction 为 Bit Mask，每个 Bit 对应一个权限。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Sets the audio session’s operational restriction.
   * @brief             The SDK and the app can both configure the audio session by default. The app may occasionally use other apps or third-party components to manipulate the audio session and restrict the SDK from doing so. This method allows the app to restrict the SDK’s manipulation of the audio session.
   * @brief             You can call this method at any time to return the control of the audio sessions to the SDK.
   * @note              \arg  This method is for iOS only.
   *                    \arg  This method restricts the SDK’s manipulation of the audio session. Any operation to the audio session relies solely on the app, other apps, or third-party components.
   * @param restriction The operational restriction (bit mask) of the SDK on the audio session. See \ref AUDIO_SESSION_OPERATION_RESTRICTION.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int setAudioSessionOperationRestriction(AUDIO_SESSION_OPERATION_RESTRICTION restriction);
#endif

#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE) || defined(_WIN32)
   /** @~chinese
   开启声卡采集。

   启用声卡采集功能后，声卡播放的声音会被合到本地音频流中，从而可以发送到远端。

   @note
   - 该方法仅适用于 macOS 和 Windows 平台。
   - macOS 系统默认声卡不支持采集功能，如需开启此功能需要 App 自己启用一个虚拟声卡，并将该虚拟声卡的名字作为 deviceName 传入 SDK。 Agora 测试并推荐 soundflower 作为虚拟声卡。
   - 该方法在加入频道前后都能调用。

   @param enabled 设置是否开启声卡采集：
   - true: 开启声卡采集
   - false: （默认）关闭声卡采集
   @param deviceName 声卡的设备名。默认设为 NULL，即使用当前声卡采集。
   如果用户使用虚拟声卡，如 “Soundflower”，可以将虚拟声卡名称 “Soundflower” 作为参数，SDK 会找到对应的虚拟声卡设备，并开始采集。
   */
   /** @~english
   * @brief             Enables loopback recording.
   * @brief             If you enable loopback recording, the output of the sound card is mixed into the audio stream sent to the other end.
   * @param enabled     Sets whether to enable/disable loopback recording.
   *                    -  true: Enable loopback recording.
   *                    -  false: (Default) Disable loopback recording.
   * @param deviceName  Pointer to the device name of the sound card. The default value is NULL (the default sound card).
   * @note              \arg  This method is for macOS and Windows only.
   *                    \arg  macOS does not support loopback recording of the default sound card. If you need to use this method, please use a virtual sound card and pass its name to the deviceName parameter. Agora has tested and recommends using soundflower.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int enableLoopbackRecording(bool enabled, const char* deviceName = nullptr);
#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
   /** @~chinese
   通过屏幕 ID 共享屏幕。

   共享一个屏幕或该屏幕的部分区域。用户需要在该方法中指定想要共享的屏幕 ID。

   @note
   - 该方法仅适用于 macOS。
   - 该方法需要在加入频道后调用。

   @param  displayId 指定待共享的屏幕 ID。开发者需要通过该参数指定你要共享的那个屏幕。关于如何获取屏幕 ID，请参考进阶功能《共享屏幕》。
   @param  regionRect （可选）指定待共享区域相对于整个屏幕的位置。如不填，则表示共享整个屏幕。详见: Rectangle 。如果设置的共享区域超出了屏幕的边界，则只共享屏幕视窗内的内容；如果宽或高为 0，则共享整个屏幕。
   @param  captureParams 屏幕共享的参数配置。默认的分辨率为 1920 x 1080，即 2073600 像素。该像素值为计费标准。详见: ScreenCaptureParameters 。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败:
     - #ERR_INVALID_ARGUMENT: 传入的参数无效。
   */
   /** @~english
   * @brief                Shares the whole or part of a screen by specifying the display ID.
   * @note                 This method is for macOS only.
   * @param displayId      The display ID of the screen to be shared. This parameter specifies which screen you want to share.
   * @param regionRect     (Optional) Sets the relative location of the region to the screen. NIL means sharing the whole screen. See \ref Rectangle. If the specified region overruns the screen, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole screen.
   * @param captureParams  Sets the screen sharing encoding parameters. The default video dimension is 1920 x 1080, that is, 2,073,600 pixels. Agora uses the value of `videoDimension` to calculate the charges.
   * For details, see descriptions in ScreenCaptureParameters.
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   *                          -  `ERR_INVALID_ARGUMENT`: the argument is invalid.
   */
	int startScreenCaptureByDisplayId(
		unsigned int displayId,
		const Rectangle& regionRect,
		const ScreenCaptureParameters& captureParams);
#endif

#if defined(_WIN32)
  /** @~chinese
   通过指定区域共享屏幕。
   *
   * 共享一个屏幕或该屏幕的部分区域。用户需要在该方法中指定想要共享的屏幕区域。
   *
   * @note
   * - 该方法需要在加入频道后调用。
   * - 该方法仅适用于 Windows 平台。
   *
   * @param  screenRect 指定待共享的屏幕相对于虚拟屏的位置。关于如何获取屏幕位置，请参考进阶功能《共享屏幕》。
   * @param  regionRect (可选）指定待共享区域相对于整个屏幕的位置。如不填，则表示共享整个屏幕。详见: Rectangle 。
   * 如果设置的共享区域超出了屏幕的边界，则只共享屏幕内的内容；如果将 width 或 height 设为 0 ，则共享整个屏幕。
   * @param  captureParams 屏幕共享的编码参数配置。默认的分辨率为 1920 x 1080，即 2073600 像素。该像素值为计费标准。详见: ScreenCaptureParameters 。
   *
   * @return
   * - 0: 方法调用成功
   * - < 0: 方法调用失败:
   *    - #ERR_INVALID_ARGUMENT: 传入的参数无效。
   */
   /** @~english
   * @brief                Shares the whole or part of a screen by specifying the screen rect.
   * @param screenRect     Sets the relative location of the screen to the virtual screen. For information on how to get screenRect, see Share the Screen.
   * @param regionRect     (Optional) Sets the relative location of the region to the screen. NULL means sharing the whole screen. See \ref Rectangle. If the specified region overruns the screen, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole screen.
   * @param captureParams  Sets the screen sharing encoding parameters. The default video dimension is 1920 x 1080, that is, 2,073,600 pixels.
   * Agora uses the value of `videoDimension` to calculate the charges. For details, see descriptions in ScreenCaptureParameters.
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   *                          -  #ERR_INVALID_ARGUMENT: the argument is invalid.
   */
	int startScreenCaptureByScreenRect(
		const Rectangle& screenRect,
		const Rectangle& regionRect,
		const ScreenCaptureParameters& captureParams);
#endif

   /** @~chinese
   通过窗口 ID 共享窗口。
   *
   * 共享一个窗口或该窗口的部分区域。用户需要在该方法中指定想要共享的窗口 ID。
   *
   * @note
   * - 该方法需要在加入频道后调用。
   * - 该方法仅适用于 macOS 和 Windows 平台。
   *
   * 自 v3.0.0 起，该方法支持共享通用 Windows 平台（UWP）应用窗口。
   *
   * 声网使用最新版 SDK 对主流的 UWP 应用进行了测试，结果如下：
   *
   * <table>
   *     <tr>
   *         <td><b>系统版本</b></td>
   *         <td><b>软件</b></td>
   *         <td><b>软件版本</b></td>
   *         <td><b>是否支持</b></td>
   *     </tr>
   *     <tr>
   *         <td rowspan="8">win10</td>
   *         <td >Chrome</td>
   *         <td>76.0.3809.100</td>
   *         <td>否</td>
   *     </tr>
   *     <tr>
   *         <td>Office Word</td>
   *         <td rowspan="3">18.1903.1152.0</td>
   *         <td>是</td>
   *     </tr>
   * 	    <tr>
   *         <td>Office Excel</td>
   *         <td>否</td>
   *     </tr>
   *     <tr>
   *         <td>Office PPT</td>
   *         <td>是</td>
   *     </tr>
   *  <tr>
   *         <td>WPS Word</td>
   *         <td rowspan="3">11.1.0.9145</td>
   *         <td rowspan="3">是</td>
   *     </tr>
   * 	    <tr>
   *         <td>WPS Excel</td>
   *     </tr>
   *     <tr>
   *         <td>WPS PPT</td>
   *     </tr>
   * 	    <tr>
   *         <td>Media Player（系统自带）</td>
   *         <td>全部</td>
   *         <td>是</td>
   *     </tr>
   * 	 <tr>
   *         <td rowspan="8">win8</td>
   *         <td >Chrome</td>
   *         <td>全部</td>
   *         <td>是</td>
   *     </tr>
   *     <tr>
   *         <td>Office Word</td>
   *         <td rowspan="3">全部</td>
   *         <td rowspan="3">是</td>
   *     </tr>
   * 	    <tr>
   *         <td>Office Excel</td>
   *     </tr>
   *     <tr>
   *         <td>Office PPT</td>
   *     </tr>
   *  <tr>
   *         <td>WPS Word</td>
   *         <td rowspan="3">11.1.0.9098</td>
   *         <td rowspan="3">是</td>
   *     </tr>
   * 	    <tr>
   *         <td>WPS Excel</td>
   *     </tr>
   *     <tr>
   *         <td>WPS PPT</td>
   *     </tr>
   * 	    <tr>
   *         <td>Media Player（系统自带）</td>
   *         <td>全部</td>
   *         <td>是</td>
   *     </tr>
   *   <tr>
   *         <td rowspan="8">win7</td>
   *         <td >Chrome</td>
   *         <td>73.0.3683.103</td>
   *         <td>否</td>
   *     </tr>
   *     <tr>
   *         <td>Office Word</td>
   *         <td rowspan="3">全部</td>
   *         <td rowspan="3">是</td>
   *     </tr>
   * 	    <tr>
   *         <td>Office Excel</td>
   *     </tr>
   *     <tr>
   *         <td>Office PPT</td>
   *     </tr>
   *  <tr>
   *         <td>WPS Word</td>
   *         <td rowspan="2">11.1.0.9098</td>
   *         <td rowspan="2">否</td>
   *     </tr>
   * 	    <tr>
   *         <td>WPS Excel</td>
   *     </tr>
   *     <tr>
   *         <td>WPS PPT</td>
   *         <td>11.1.0.9098</td>
   *         <td>是</td>
   *     </tr>
   * 	    <tr>
   *         <td>Media Player（系统自带）</td>
   *         <td>全部</td>
   *         <td>否</td>
   *     </tr>
   * </table>
   *
   * @param  windowId 指定待共享的窗口 ID。关于如何获取窗口 ID，请参考进阶功能《共享屏幕》。
   * @param  regionRect （可选）指定待共享的区域相对于整个窗口的位置。如不填，则表示共享整个窗口。详见: Rectangle 。如果设置的共享区域超出了窗口的边界，则只共享窗口内的内容；如果宽或高为 0，则共享整个窗口。
   * @param  captureParams 屏幕共享的编码参数配置。默认的分辨率为 1920 x 1080，即 2073600 像素。该像素值为计费标准。详见 ScreenCaptureParameters 。
   *
   * @return
   * - 0: 方法调用成功
   * - < 0: 方法调用失败:
   *   - #ERR_INVALID_ARGUMENT: 传入的参数无效。
   */
   /** @~english
   * @brief                Shares the whole or part of a window by specifying the window ID.
   * @brief                Since v3.0.0, this method supports sharing with common Windows platforms. Agora tests the mainstream Windows applications, see details as follows:
     <table>
         <tr>
             <td><b>OS version</b></td>
             <td><b>Software</b></td>
             <td><b>Software name</b></td>
             <td><b>Whether support</b></td>
         </tr>
         <tr>
             <td rowspan="8">win10</td>
             <td >Chrome</td>
             <td>76.0.3809.100</td>
             <td>No</td>
         </tr>
         <tr>
             <td>Office Word</td>
             <td rowspan="3">18.1903.1152.0</td>
             <td>Yes</td>
         </tr>
          <tr>
             <td>Office Excel</td>
             <td>No</td>
         </tr>
         <tr>
             <td>Office PPT</td>
             <td>No</td>
         </tr>
      <tr>
             <td>WPS Word</td>
             <td rowspan="3">11.1.0.9145</td>
             <td rowspan="3">Yes</td>
         </tr>
          <tr>
             <td>WPS Excel</td>
         </tr>
         <tr>
             <td>WPS PPT</td>
         </tr>
          <tr>
             <td>Media Player (come with the system)</td>
             <td>All</td>
             <td>Yes</td>
         </tr>
       <tr>
             <td rowspan="8">win8</td>
             <td >Chrome</td>
             <td>All</td>
             <td>Yes</td>
         </tr>
         <tr>
             <td>Office Word</td>
             <td rowspan="3">All</td>
             <td rowspan="3">Yes</td>
         </tr>
          <tr>
             <td>Office Excel</td>
         </tr>
         <tr>
             <td>Office PPT</td>
         </tr>
      <tr>
             <td>WPS Word</td>
             <td rowspan="3">11.1.0.9098</td>
             <td rowspan="3">Yes</td>
         </tr>
          <tr>
             <td>WPS Excel</td>
         </tr>
         <tr>
             <td>WPS PPT</td>
         </tr>
          <tr>
             <td>Media Player(come with the system)</td>
             <td>All</td>
             <td>Yes</td>
         </tr>
       <tr>
             <td rowspan="8">win7</td>
             <td >Chrome</td>
             <td>73.0.3683.103</td>
             <td>No</td>
         </tr>
         <tr>
             <td>Office Word</td>
             <td rowspan="3">All</td>
             <td rowspan="3">Yes</td>
         </tr>
          <tr>
             <td>Office Excel</td>
         </tr>
         <tr>
             <td>Office PPT</td>
         </tr>
      <tr>
             <td>WPS Word</td>
             <td rowspan="3">11.1.0.9098</td>
             <td rowspan="3">No</td>
         </tr>
          <tr>
             <td>WPS Excel</td>
         </tr>
         <tr>
             <td>WPS PPT</td>
         </tr>
          <tr>
             <td>Media Player(come with the system)</td>
             <td>All</td>
             <td>No</td>
         </tr>
     </table>
   * @param windowId       The ID of the window to be shared. For information on how to get the windowId, see Share the Screen.
   * @param regionRect     (Optional) The relative location of the region to the window. NULL/NIL means sharing the whole window. See \ref Rectangle. If the specified region overruns the window, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole window.
   * @param captureParams  Window sharing encoding parameters. The default video dimension is 1920 x 1080, that is, 2,073,600 pixels.
   * Agora uses the value of `videoDimension` to calculate the charges. For details, see descriptions in ScreenCaptureParameters.
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   *                          -  #ERR_INVALID_ARGUMENT: the argument is invalid.
   */
	int startScreenCaptureByWindowId(
		view_t windowId,
		const Rectangle& regionRect,
		const ScreenCaptureParameters& captureParams);

   /** @~chinese
   设置屏幕共享内容类型。

   设置屏幕共享的内容类型。Agora SDK 会根据不同的内容类型，使用不同的算法对共享效果进行优化。如果不调用该方法，SDK 会将屏幕共享的内容默认为 CONTENT_HINT_NONE ，即无指定的内容类型。

   @note 该方法在开始屏幕共享前后都能调用。

   @param  contentHint 指定屏幕共享的内容类型。详见: #VideoContentHint 。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Sets the content hint for screen sharing.
   * @brief             A content hint suggests the type of the content being shared, so that the SDK applies different optimization algorithm to different types of content.
   * @param contentHint Sets the content hint for screen sharing. See VideoContentHint.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int setScreenCaptureContentHint(VideoContentHint contentHint);

   /** @~chinese
   更新屏幕共享的参数配置。

   @param captureParams 屏幕共享的编码参数配置。默认的分辨率为 1920 x 1080，即 2073600 像素。该像素值为计费标准。详见: ScreenCaptureParameters 。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败:
     - #ERR_NOT_READY: 如果当前没有共享的屏幕，会返回该错误码。
   */
   /** @~english
   * @brief                Updates the screen sharing parameters.
   * @param captureParams  Sets the screen sharing encoding parameters. See \ref ScreenCaptureParameters.
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   *                          -  #ERR_NOT_READY: no screen or windows is being shared.
   */
	int updateScreenCaptureParameters(const ScreenCaptureParameters& captureParams);

   /** @~chinese
   更新屏幕共享区域。

   @param  regionRect 待共享区域相对于整个屏幕或窗口的位置，如不填，则表示共享整个屏幕或窗口。详见: Rectangle 。如果设置的共享区域超出了屏幕或窗口的边界，则只共享屏幕或窗口内的内容；如果将 width 或 height 设为 0 ，则共享整个屏幕或窗口。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败:
     - #ERR_NOT_READY: 如果当前没有共享的屏幕，会返回该错误码。
   */
   /** @~english
   * @brief             Updates the screen sharing region.
   * @param regionRect  Sets the relative location of the region to the screen or window. NULL means sharing the whole screen or window. See \ref Rectangle. If the specified region overruns the screen or window, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole screen or window.
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   *                          -  #ERR_NOT_READY: no screen or window is being shared.
   */
	int updateScreenCaptureRegion(const Rectangle& regionRect);

   /** @~chinese
   停止屏幕共享。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Stop screen sharing.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int stopScreenCapture();

#endif
   /** @~chinese
   获取当前通话 ID。

   客户端在每次 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 后会生成一个对应的 callId，标识该客户端的此次通话。有些方法如 \ref agora::rtc::IRtcEngine::rate "rate" 、 \ref agora::rtc::IRtcEngine::complain "complain" 需要在通话结束后调用，向 SDK 提交反馈，这些方法必须指定 CallId 参数。使用这些反馈方法，需要在通话过程中调用 \ref agora::rtc::IRtcEngine::getCallId "getCallId" 方法获取 CallId，在通话结束后在反馈方法中作为参数传入。

   @note 该方法需要在加入频道后调用。

   @param callId 当前的通话 ID。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Retrieves the current call ID.
   * @brief          When a user joins a channel on a client, a *callId* is generated to identify the call from the client. Feedback methods, such as \ref rate and \ref complain, must be called after the call ends to submit feedback to the SDK.
   * @brief          The \ref rate and \ref complain methods require the *callId* parameter retrieved from the \a getCallId method during a call. *callId* is passed as an argument into the \ref rate and \ref complain methods after the call ends.
   * @note Ensure that you call this method after joining a channel.
   * @param callId   Pointer to the current call ID.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int getCallId(agora::util::AString& callId);

   /** @~chinese
   给通话评分。

   该方法能够让用户为通话评分，一般在通话结束后调用。

   @note 该方法需要在离开频道后调用。

   @param callId 通话 \ref agora::rtc::IRtcEngine::getCallId "getCallId" 函数获取的通话 ID。
   @param rating  给通话的评分，最低 1 分，最高 5 分。如超过这个范围，SDK 会返回 #ERR_INVALID_ARGUMENT (2) 错误。
   @param description (非必选项) 给通话的描述，可选，长度应小于 800 字节。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Allows a user to rate a call after the call ends.
   * @note Ensure that you call this method after joining a channel.
   * @param callId      Pointer to the ID of the call, retrieved from the \ref getCallId method.
   * @param rating      Rating of the call. The value is between 1 (lowest score) and 5 (highest score). If you set a value out of this range, the \ref ERR_INVALID_ARGUMENT (2) error returns.
   * @param description (Optional) Pointer to the description of the rating, with a string length of less than 800 bytes.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int rate(const char* callId, int rating, const char* description);

   /** @~chinese
   投诉通话质量。

   该方法让用户就通话质量进行投诉。一般在通话结束后调用。

   @note 该方法需要在离开频道后调用。

   @param callId 通话 \ref agora::rtc::IRtcEngine::getCallId "getCallId" 函数获取的通话 ID。
   @param description (非必选项) 给通话的描述，可选，长度应小于 800 字节。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief             Allows a user to complain about the call quality after a call ends.
   * @note Ensure that you call this method after joining a channel.
   * @param callId      Pointer to the ID of the call, retrieved from the \ref getCallId method.
   * @param description (Optional) Pointer to the description of the complaint, with a string length of less than 800 bytes.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int complain(const char* callId, const char* description);

   /** @~chinese
   查询 SDK 版本号。

   @param build 编译号。

   @return 当前的 SDK 版本号，格式为字符串，如 2.4.0。
   */
   /** @~english
   * @brief       Retrieves the SDK version number.
   * @param build Pointer to the build number.
   * @return      The version of the current SDK in the string format. For example, 2.3.1.
   */
	const char* getVersion(int* build);

   /** @~chinese
   启动网络测试。

   该方法启用网络连接质量测试，用于检测用户目前的网络接入质量（上行网络质量）。默认该功能为关闭状态。该方法主要用于以下场景:

   - 用户加入频道前，可以调用该方法判断和预测目前的上行网络质量是否足够好。
   - 直播场景下，当用户角色由观众切换为主播时，可以调用该方法判断和预测目前的上行网络质量是否足够好。

   启用该方法会消耗网络流量，影响通话质量。用户必须在收到 \ref agora::rtc::IRtcEngineEventHandler::onLastmileQuality "onLastmileQuality"
   回调后须调用 \ref agora::rtc::IRtcEngine::disableLastmileTest "disableLastmileTest" 停止测试，再加入频道或切换为主播。

   @note
   - 该方法请勿与 \ref agora::rtc::IRtcEngine::startLastmileProbeTest "startLastmileProbeTest" 同时使用。
   - 调用该方法后，在收到 \ref agora::rtc::IRtcEngineEventHandler::onLastmileQuality "onLastmileQuality" 回调前请勿调用其他方法，否则可能由于 API 操作过于频繁导致回调无法执行。
   - 在直播场景中，如果本地用户为主播，请勿加入频道后调用该方法。
   - 加入频道前调用该方法检测网络质量后，SDK 会占用一路视频的带宽，码率与 \ref agora::rtc::IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" 中设置的码率相同。
   加入频道后，无论是否调用了 \ref IRtcEngine::disableLastmileTest "disableLastmileTest" ，SDK 均会自动停止带宽占用。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Enables the network connection quality test.
   * @brief    This method tests the quality of the users' network connections and is disabled by default.
   * @brief    Before a user joins a channel or before an audience switches to a host, call this method to check the uplink network quality.
   * @brief    This method consumes additional network traffic, and hence may affect communication quality.
   * @brief    Call the \ref disableLastmileTest method to disable this test after receiving the \ref agora::rtc::IRtcEngineEventHandler::onLastmileQuality "onLastmileQuality" callback, and before joining a channel.
   * @note     \arg  Do not call any other methods before receiving the onLastmileQuality callback. Otherwise, the callback may be interrupted by other methods, and hence may not be triggered.
   *           \arg  A host should not call this method after joining a channel (when in a call).
   *           \arg  If you call this method to test the last-mile quality, the SDK consumes the bandwidth of a video stream, whose bitrate corresponds to the bitrate you set in the setVideoEncoderConfiguration method. After you join the channel, whether you have called the disableLastmileTest method or not, the SDK automatically stops consuming the bandwidth.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int enableLastmileTest();

   /** @~chinese
   关闭网络测试。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Disables the network connection quality test.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int disableLastmileTest();

   /** @~chinese
   开始通话前网络质量探测。

   开始通话前网络质量探测，向用户反馈上下行网络的带宽、丢包、网络抖动和往返时延数据。

   启用该方法后，SDK 会依次返回如下 2 个回调：
   - \ref agora::rtc::IRtcEngineEventHandler::onLastmileQuality "onLastmileQuality"，视网络情况约 2 秒内返回。该回调通过打分反馈上下行网络质量，更贴近用户的主观感受。
   - \ref agora::rtc::IRtcEngineEventHandler::onLastmileProbeResult "onLastmileProbeResult"，视网络情况约 30 秒内返回。该回调通过具体数据反馈上下行网络质量，更加客观。

   该方法主要用于以下两种场景：
   - 用户加入频道前，可以调用该方法判断和预测目前的上行网络质量是否足够好。
   - 直播场景下，当用户角色想由观众切换为主播时，可以调用该方法判断和预测目前的上行网络质量是否足够好。

   @note
   - 该方法会消耗一定的网络流量，影响通话质量，因此我们建议不要和 \ref agora::rtc::IRtcEngine::enableLastmileTest "enableLastmileTest" 同时使用。
   - 调用该方法后，在收到 \ref agora::rtc::IRtcEngineEventHandler::onLastmileQuality "onLastmileQuality" 和 \ref agora::rtc::IRtcEngineEventHandler::onLastmileProbeResult "onLastmileProbeResult" 回调之前请不要调用其他方法，否则可能会由于 API 操作过于频繁导致此方法无法执行。
   - 在直播场景中，如果本地用户为主播，请勿加入频道后调用该方法。

   @param config Last mile 网络探测配置，详见 LastmileProbeConfig。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Starts the last-mile network probe test.
   * @brief          This method starts the last-mile network probe test before joining a channel to get the uplink and downlink last-mile network statistics, including the bandwidth, packet loss, jitter, and round-trip time (RTT).
   * @brief          Call this method to check the uplink network quality before users join a channel or before an audience switches to a host. Once this method is enabled, the SDK returns the following callbacks:
   *                 <ul>
   *                 <li> \ref agora::rtc::IRtcEngineEventHandler::onLastmileQuality "onLastmileQuality": the SDK triggers this callback within two seconds depending on the network conditions. This callback rates the network conditions and is more closely linked to the user experience.
   *                 <li> \ref agora::rtc::IRtcEngineEventHandler::onLastmileProbeResult "onLastmileProbeResult": the SDK triggers this callback within 30 seconds depending on the network conditions. This callback returns the real-time statistics of the network conditions and is more objective.
   *                 </ul>
   * @note           \arg  This method consumes extra network traffic and may affect communication quality. We do not recommend calling this method together with enableLastmileTest.
   *                 \arg  Do not call other methods before receiving the `onLastmileQuality` and `onLastmileProbeResult` callbacks. Otherwise, the callbacks may be interrupted.
   *                 \arg  In the Live-broadcast profile, a host should not call this method after joining a channel.
   * @param config   Sets the configurations of the last-mile network probe test. See \ref LastmileProbeConfig.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int startLastmileProbeTest(const LastmileProbeConfig& config);
   /** @~chinese
   停止通话前网络质量探测。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief    Stops the last-mile network probe test.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int stopLastmileProbeTest();

   /** @~chinese
   获取警告或错误描述。

   @param code \ref agora::rtc::IRtcEngineEventHandler::onWarning "onWarning" 或 \ref agora::rtc::IRtcEngineEventHandler::onError "onError" 提供的警告码或错误码。

   @return #WARN_CODE_TYPE 或 #ERROR_CODE_TYPE 。
   */
   /** @~english
   * @brief    Retrieves the warning or error description.
   * @return   code \ref WARN_CODE_TYPE or \ref ERROR_CODE_TYPE returned in the \ref agora::rtc::IRtcEngineEventHandler::onWarning "onWarning" or \ref agora::rtc::IRtcEngineEventHandler::onError "onError" callback.
   */
	const char* getErrorDescription(int code);

   /** @~chinese
    启用内置加密，并设置数据加密密码。

     @deprecated 该方法自 v3.1.0 起废弃。请改用 \ref IRtcEngine::enableEncryption "enableEncryption" 方法。

     在加入频道之前，App 需调用 setEncryptionSecret 方法指定 secret 来启用内置的加密功能，同一频道内的所有用户应设置相同的 secret。当用户离开频道时，该频道的 secret 会自动清除。如果未指定 secret 或将 secret 设置为空，则无法激活加密功能。

     @note
     - 请不要在旁路推流时调用此方法。
     - 为保证最佳传输效果，请确保加密后的数据大小不超过原始数据大小 + 16 字节。16 字节是 AES 通用加密模式下最大填充块大小。

     @param secret 加密密码。
     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
     */
   /** @~english
   * @brief          Enables built-in encryption with an encryption password before users join a channel.
   * @brief          All users in a channel must use the same encryption password. The encryption password is automatically cleared once a user leaves the channel.
   * @brief          If an encryption password is not specified, the encryption functionality will be disabled.
   * @note           \arg  Do not use this method for CDN live streaming.
   *                 \arg  For optimal transmission, ensure that the encrypted data size does not exceed the original data size + 16 bytes. 16 bytes is the maximum padding size for AES encryption.
   * @param secret   Pointer to the encryption password.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int setEncryptionSecret(const char* secret);

	/** @~chinese
    启用内置的加密方案。

     @deprecated 该方法自 v3.1.0 起废弃。请改用 \ref IRtcEngine::enableEncryption "enableEncryption" 方法。

     Agora Video SDK 支持内置加密方案，默认支持 AES-128-XTS。如需采用其他加密方案，可以调用本方法。同一频道内的所有用户必须设置相同的加密方式和 secret 才能进行通话。关于这几种加密方式的区别，请参考 AES 加密算法的相关资料。

     @note 在调用本方法前，请先调用 \ref agora::rtc::IRtcEngine::setEncryptionSecret "setEncryptionSecret" 启用内置加密功能。

     @param encryptionMode 加密模式：
     - "aes-128-xts": 128 位 AES 加密，XTS 模式；
     - "aes-128-ecb":128 位 AES 加密，ECB 模式；
     - "aes-256-xts": 256 位 AES 加密，XTS 模式；
     - "": 设置为空字符串时，默认使用加密方式 "aes-128-xts"。

     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
	 */
   /** @~english
   * @brief                Sets the built-in encryption mode.
   * @brief                The Agora SDK supports built-in encryption, which is set to the *aes-128-xts* mode by default. Call this method to use other encryption modes.
   * @brief                All users in the same channel must use the same encryption mode and password.
   * @brief                Refer to the information related to the AES encryption algorithm on the differences between the encryption modes.
   * @note                 Call the setEncryptionSecret method to enable the built-in encryption function before calling this method.
   * @param encryptionMode \arg  Pointer to the set encryption mode:
   *                       \arg  "aes-128-xts": (Default) 128-bit AES encryption, XTS mode.
   *                       \arg  "aes-128-ecb": 128-bit AES encryption, ECB mode.
   *                       \arg  "aes-256-xts": 256-bit AES encryption, XTS mode.
   *                       \arg  "": When encryptionMode is set as NULL, the encryption mode is set as "aes-128-xts" by default.
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   */
	int setEncryptionMode(const char* encryptionMode);
    /** @~chinese
     注册数据包观测器。

     该方法注册数据包观测器 (Packet Observer)。在 Agora SDK 发送/接收（语音、视频）网络包时，会回调 IPacketObserver 定义的接口，App 可用此接口对数据做处理，例如加解密。

     @note
     - 处理后发送到网络的包大小不应超过 1200 字节，否则有可能发送失败。
     - 若需调用此方法，需确保接收端和发送端都调用此方法，否则会出现未定义行为（例如音频无声或视频黑屏）。
     - 若在直播场景下使用 CDN 推流、录制或储存，Agora 不建议调用此方法。
     - 你需要在加入频道前调用该方法。

     @param observer IPacketObserver 。

     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
     */
   /** @~english
   * @brief          Registers a packet observer.
   * @brief          The Agora SDK allows your application to register a packet observer to receive callbacks for voice or video packet transmission.
   * @note           \arg  The size of the packet sent to the network after processing should not exceed 1200 bytes, otherwise, the packet may fail to be sent.
   *                 \arg  Ensure that both receivers and senders call this method, otherwise, you may meet undefined behaviors such as no voice and black screen.
   *                 \arg  When you use CDN live streaming, recording or storage functions, Agora doesn't recommend calling this method.
   *                 \arg  Call this method before joining a channel.
   * @param observer Pointer to the registered packet observer. See \ref IPacketObserver.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int registerPacketObserver(IPacketObserver* observer);
    /** @~chinese
     创建数据流。

     该方法用于创建数据流。RtcEngine 生命周期内，每个用户最多只能创建 5 个数据流。频道内数据通道最多允许数据延迟 5 秒，若超过 5 秒接收方尚未收到数据流，则数据通道会向 App 报错。

     @note
     - 将 reliable 和 ordered 同时设为 true 或 false。不要一个设为 true 另一个设为 false。
     - 该方法需要在加入频道后调用。

     @param[out] streamId 数据流 ID。
     @param reliable
     - true: 接收方 5 秒内会收到发送方所发送的数据，否则会收到 \ref agora::rtc::IRtcEngineEventHandler::onStreamMessageError "onStreamMessageError" 回调获得相应报错信息。
     - false: 接收方不保证收到，就算数据丢失也不会报错。
     @param ordered
     - true: 接收方 5 秒内会按照发送方发送的顺序收到数据包；
     - false: 接收方不保证按照发送方发送的顺序收到数据包。

     @return
     - 0: 创建数据流成功。
     - < 0: 创建数据流失败。
     */
   /**
   * @brief          Creates a data stream.
   * @brief          Each user can create up to five data streams during the lifecycle of the RtcEngine.
   * @note
   * - Set both the reliable and ordered parameters to true or false. Do not set one as true and the other as false.
   * - Ensure that you call this method after joining a channel.
   * @param streamId Pointer to the ID of the created data stream.
   * @param reliable Sets whether or not the recipients are guaranteed to receive the data stream from the sender within five seconds:
   *                 -  true: The recipients receive the data stream from the sender within five seconds. If the recipient does not receive the data stream within five seconds, an error is reported to the application.
   *                 -  false: There is no guarantee that the recipients receive the data stream within five seconds and no error message is reported for any delay or missing data stream.
   * @param ordered  Sets whether or not the recipients receive the data stream in the sent order:
   *                 -  true: The recipients receive the data stream in the sent order.
   *                 -  false: The recipients do not receive the data stream in the sent order.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int createDataStream(int* streamId, bool reliable, bool ordered);

    /** @~chinese
     发送数据流。

     该方法发送数据流消息到频道内所有用户。SDK 对该方法的实现进行了如下限制：频道内每秒最多能发送 30 个包，且每个包最大为 1 KB。 API 须对数据通道的传送速率进行控制: 每个客户端每秒最多能发送 6 KB 数据。频道内每人最多能同时有 5 个数据通道。
     成功调用该方法后，远端会触发 \ref agora::rtc::IRtcEngineEventHandler::onStreamMessage "onStreamMessage" 回调，远端用户可以在该回调中获取接收到的流消息；若调用失败，远端会触发 \ref agora::rtc::IRtcEngineEventHandler::onStreamMessageError "onStreamMessageError" 回调。
     @note
     - 请确保在调用该方法前，已调用 \ref agora::rtc::IRtcEngine::createDataStream "createDataStream" 创建了数据流。
     - 该方法仅适用于通信场景以及直播场景下的主播用户，如果直播场景下的观众调用此方法可能会造成观众变主播。

     @param  streamId  由 \ref agora::rtc::IRtcEngine::createDataStream "createDataStream" 返回的数据流 ID。
     @param data 自定义数据。
     @param length 数据长度。

     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
     */
   /** @~english
   * @brief          Sends data stream messages to all users in a channel.
   * @brief          The SDK has the following restrictions on this method:
   *                 -  Up to 30 packets can be sent per second in a channel with each packet having a maximum size of 1 kB.
   *                 -  Each client can send up to 6 kB of data per second.
   *                 -  Each user can have up to five data streams simultaneously.
   * @brief          A successful \ref sendStreamMessage method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onStreamMessage "onStreamMessage" callback on the remote client, from which the remote user gets the stream message.
   * @brief          A failed \ref sendStreamMessage method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onStreamMessage "onStreamMessage" callback on the remote client.
   * @note           This method applies only to the Communication profile or to the hosts in the Live-broadcast profile. If an audience in the Live-broadcast profile calls this method, the audience may be switched to a host.
   * @param streamId ID of the sent data stream, returned in the \ref createDataStream method.
   * @param data     Pointer to the sent data.
   * @param length   Length of the sent data.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int sendStreamMessage(int streamId, const char* data, size_t length);

    /** @~chinese
     增加旁路推流地址。

     调用该方法后，你可以向 CDN 推送 RTMP 或 RTMPS 协议的媒体流。SDK 会在本地触发 \ref agora::rtc::IRtcEngineEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" 回调，报告增加旁路推流地址的状态。

     @note
     - 请确保在成功加入频道后才能调用该接口。
     - 请确保已开通旁路推流的功能，详见进阶功能《推流到 CDN》中的前提条件。
     - 该方法每次只能增加一路旁路推流地址。若需推送多路流，则需多次调用该方法。
     - 在直播场景中，只有角色为主播的用户才能调用该方法。
     - Agora 目前仅支持转码时向 CDN 推送 RTMPS 协议的媒体流。

     @param url CDN 推流地址，格式为 RTMP。该字符长度不能超过 1024 字节。url 不支持中文字符等特殊字符。
     @param transcodingEnabled
     - true: 转码（ [转码]( https://docs.agora.io/cn/Agora%20Platform/terms?platform=All%20Platforms#转码) 是指在旁路推流时对音视频流进行转码处理后再推送到其他 CDN 服务器。多适用于频道内有多个主播，需要进行混流、合图的场景）。如果设为 `true`，需先调用 \ref agora::rtc::IRtcEngine::setLiveTranscoding "setLiveTranscoding" 方法。
     - false: 不转码。

     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
          - #ERR_INVALID_ARGUMENT (2): URL 为空或是长度为 0 的的字符串
          - #ERR_NOT_INITIALIZED (7): 推流时未初始化引擎
     */
   /** @~english
   * @brief                      Publishes the local stream to a specified CDN live RTMP address. (CDN live only.)
   * @brief                      The SDK returns the result of this method call in the \ref agora::rtc::IRtcEngineEventHandler::onStreamPublished "onStreamPublished" callback.
   * @brief                      The *addPublishStreamUrl* method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" callback on the local client to report the state of adding a local stream to the CDN.
   * @note                       \arg  Ensure that the user joins the channel before calling this method.
   *                             \arg  Ensure that you enable the RTMP Converter service before using this function. See Prerequisites in the advanced guide *Push Streams to CDN*.
   *                             \arg  This method adds only one stream RTMP URL address each time it is called.
   *                             \arg  This method applies to Live Broadcast only.
   * @param url                  The CDN streaming URL in the RTMP format. The maximum length of this parameter is 1024 bytes. The RTMP URL address must not contain special characters, such as Chinese language characters.
   * @param transcodingEnabled   Sets whether transcoding is enabled/disabled:
   *                             true: Enable transcoding, to transcode the audio or video streams when publishing them to CDN live, often used for combining the audio and video streams of multiple hosts in CDN live. If you set this parameter as true, ensure that you call the \ref setLiveTranscoding method before this method.
   *                             false: Disable transcoding.
   * @return                     \arg  0: Success.
   *                             \arg  < 0: Failure.
   *                                - \ref ERR_INVALID_ARGUMENT (2): The RTMP URL address is NULL or has a string length of 0.
   *                                - \ref ERR_NOT_INITIALIZED (7): You have not initialized the RTC engine when publishing the stream.
   */
	int addPublishStreamUrl(const char* url, bool transcodingEnabled);

   /** @~chinese
    删除旁路推流地址。
    *
    * 调用该方法后，SDK 会在本地触发 \ref agora::rtc::IRtcEngineEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" 回调，报告删除旁路推流地址的状态。
    *
    * @note
    * - 该方法每次只能删除一路旁路推流地址。若需删除多路流，则需多次调用该方法。
    * - URL 不支持中文等特殊字符。
    * - 在直播场景中，只有角色为主播的用户才能调用该方法。
    *
    * @param url 待删除的旁路推流地址，格式为 RTMP。该字符长度不能超过 1024 字节。
    * @return
    * - 0: 方法调用成功
    * - < 0: 方法调用失败
    */
   /** @~english
   * @brief       Removes an RTMP stream from the CDN. (CDN live only.)
   * @brief       This method removes the RTMP URL address (added by the \ref addPublishStreamUrl method) from a CDN live stream. The SDK returns the result of this method call in the \ref agora::rtc::IRtcEngineEventHandler::onStreamUnpublished "onStreamUnpublished" callback.
   * @brief       The \ref removePublishStreamUrl method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" callback on the local client to report the state of removing an RTMP stream from the CDN.
   * @note        \arg  This method removes only one RTMP URL address each time it is called.
   *              \arg  The RTMP URL address must not contain special characters, such as Chinese language characters.
   *              \arg  This method applies to Live Broadcast only.
   * @param url   The RTMP URL address to be removed. The maximum length of this parameter is 1024 bytes.
   * @return      \arg  0: Success.
   *              \arg  < 0: Failure.
   */
	int removePublishStreamUrl(const char* url);

    /** @~chinese
     设置直播推流转码。

     该方法用于旁路推流的视图布局及音频设置等。调用该方法更新转码设置后本地会触发 \ref agora::rtc::IRtcEngineEventHandler::onTranscodingUpdated "onTranscodingUpdated" 回调。

     @note
     - 在直播场景中，只有角色为主播的用户才能调用该方法。
     - 请确保已开通旁路推流的功能，详见进阶功能《推流到 CDN》中的前提条件。
     - 首次调用该方法更新转码设置时，不会触发 `onTranscodingUpdated` 回调。
     - 该方法需要在加入频道后调用。
     - Agora 目前仅支持转码时向 CDN 推送 RTMPS 协议的媒体流。

     @param transcoding 详见 LiveTranscoding 。
     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
    */
   /** @~english
   * @brief             Sets the video layout and audio settings for CDN live. (CDN live only.)
   * @brief             The SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onTranscodingUpdated "onTranscodingUpdated" callback when you call the `setLiveTranscoding` method to update the transcoding setting.
   * @note              \arg  This method applies to Live Broadcast only.
   *                    \arg  Ensure that you enable the RTMP Converter service before using this function. See Prerequisites in the advanced guide *Push Streams to CDN*.
   *                    \arg  If you call the `setLiveTranscoding` method to update the transcoding setting for the first time, the SDK does not trigger the `onTranscodingUpdated` callback.
   *                    \arg  Ensure that you call this method after joining a channel.
   *                    \arg  Agora supports pushing media streams in RTMPS protocol to the CDN only when you enable transcoding.
   * @param transcoding Sets the CDN live audio/video transcoding settings. See \ref LiveTranscoding.
   * @return            \arg  0: Success.
   *                    \arg  < 0: Failure.
   */
	int setLiveTranscoding(const LiveTranscoding& transcoding);

    /** @~chinese
     添加本地视频水印。

     该方法将一张 PNG 图片作为水印添加到本地发布的直播视频流上，同一直播频道中的观众、旁路直播观众和采集设备都能看到或采集到该水印图片。Agora 当前只支持在直播视频流中添加一个水印，后添加的水印会替换掉之前添加的水印。

     水印坐标和 \ref agora::rtc::IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" 方法中的设置有依赖关系：

     - 如果视频编码方向/ #ORIENTATION_MODE 固定为横屏或自适应模式下的横屏，那么水印使用横屏坐标。
     - 如果视频编码方向/ #ORIENTATION_MODE 固定为竖屏或自适应模式下的竖屏，那么水印使用竖屏坐标。
     - 设置水印坐标时，水印的图像区域不能超出 `setVideoEncoderConfiguration` 方法中设置的视频尺寸，否则超出部分将被裁剪。

     @note
     - 你需要在调用 \ref agora::rtc::IRtcEngine::enableVideo "enableVideo" 方法之后再调用本方法。
     - 如果你只是在旁路直播（推流到CDN）中添加水印，你可以使用本方法或 \ref agora::rtc::IRtcEngine::setLiveTranscoding "setLiveTranscoding" 方法设置水印。
     - 待添加水印图片必须是 PNG 格式。本方法支持所有像素格式的 PNG 图片：RGBA、RGB、Palette、Gray 和 Alpha_gray。
     - 如果待添加的 PNG 图片的尺寸与你在本方法中设置的尺寸不一致，SDK 会对 PNG 图片进行缩放或裁剪，以与设置相符。
     - 如果你已经使用 \ref agora::rtc::IRtcEngine::startPreview "startPreview" 方法开启本地视频预览，那么本方法的 `visibleInPreview` 可设置水印在预览时是否可见。
     - 如果你已设置本地视频为镜像模式，那么此处的本地水印也为镜像。为避免本地用户看本地视频时的水印也被镜像，Agora 建议你不要对本地视频同时使用镜像和水印功能，请在应用层实现本地水印功能。

     @param watermarkUrl 待添加的水印图片的本地路径。本方法支持从本地绝对/相对路径添加水印图片。
     @param options 待添加的水印图片的设置选项，详见 WatermarkOptions。

     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
     */
   /** @~english
   * @brief                Adds a watermark image to the local video.
   * @brief                This method adds a PNG watermark image to the local video in a live broadcast. Once the watermark image is added, all the audience in the channel (CDN audience included), and the recording device can see and capture it. Agora supports adding only one watermark image onto the local video, and the newly watermark image replaces the previous one.
   * @brief                The watermark position depends on the settings in the \ref setVideoEncoderConfiguration method:
   *                       <ul>
   *                       <li> If the orientation mode of the encoding video is \ref ORIENTATION_MODE_FIXED_LANDSCAPE, or the landscape mode in \ref ORIENTATION_MODE_ADAPTIVE, the watermark uses the landscape orientation.
   *                       <li> If the orientation mode of the encoding video is \ref ORIENTATION_MODE_FIXED_PORTRAIT, or the portrait mode in \ref ORIENTATION_MODE_ADAPTIVE, the watermark uses the portrait orientation.
   *                       <li> When setting the watermark position, the region must be less than the dimensions set in the *setVideoEncoderConfiguration* method. Otherwise, the watermark image will be cropped.
   *                       </ul>
   * @note                 \arg  Ensure that you have called the \ref enableVideo method to enable the video module before calling this method.
   *                       \arg  If you only want to add a watermark image to the local video for the audience in the CDN live broadcast channel to see and capture, you can call this method or the \ref setLiveTranscoding method.
   *                       \arg  This method supports adding a watermark image in the PNG file format only. Supported pixel formats of the PNG image are RGBA, RGB, Palette, Gray, and Alpha_gray.
   *                       \arg  If the dimensions of the PNG image differ from your settings in this method, the image will be cropped or zoomed to conform to your settings.
   *                       \arg  If you have enabled the local video preview by calling the \ref startPreview method, you can use the *visibleInPreview* member in the \ref WatermarkOptions class to set whether or not the watermark is visible in preview.
   *                       \arg  If you have mirrored the local video by calling the \ref setLocalVideoMirrorMode method, the watermark image in preview is also mirrored.
   * @param watermarkUrl   The local file path of the watermark image to be added. This method supports adding a watermark image from the local absolute or relative file path.
   * @param options        Pointer to the watermark's options to be added. See \ref WatermarkOptions for more infomation.
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   */
	int addVideoWatermark(const char* watermarkUrl, const WatermarkOptions& options);

    /** @~chinese
     删除已添加的视频水印。

     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
    */
   /** @~english
   * @brief    Removes the watermark image from the video stream added by the \ref addVideoWatermark method.
   * @return   \arg  0: Success.
   *           \arg  < 0: Failure.
   */
	int clearVideoWatermarks();
    /** @~chinese

    设置美颜效果选项。

    开启本地美颜功能，并设置美颜效果选项。

    @note 请在调用 \ref IRtcEngine::enableVideo "enableVideo" 方法后，调用该方法。

    @param enabled 是否开启美颜功能：
    - true: 开启。
    - false: （默认）关闭。
    @param options 美颜选项。详见: BeautyOptions 。

     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
    */
   /** @~english
   * @brief          Enables/Disables image enhancement and sets the options.
   * @note Call this method after calling the \ref enableVideo method.
   * @param enabled  Sets whether or not to enable image enhancement:
   *                 -  true: enables image enhancement.
   *                 -  false: disables image enhancement.
   * @param options  Sets the image enhancement option. See \ref BeautyOptions.
   */
	int setBeautyEffectOptions(bool enabled, BeautyOptions options);

    /** @~chinese
     输入在线媒体流。

     @note
     - 请确保已开通旁路推流的功能，详见进阶功能《推流到 CDN》中的前提条件。
     - 该方法适用于 Native SDK v2.4.1 及之后的版本。
     - 在直播场景中，只有角色为主播的用户才能调用该方法。
     - 频道内同一时间只允许输入一个在线媒体流。
     - 该方法需要在加入频道后调用。

     该方法将正在播放的音视频作为音视频源导入到正在进行的直播中。可主要应用于赛事直播、多人看视频互动等直播场景。调用该方法后，SDK 会在本地触发 \ref agora::rtc::IRtcEngineEventHandler::onStreamInjectedStatus "onStreamInjectedStatus" 回调，报告输入在线媒体流的状态；成功输入媒体流后，该音视频流会出现在频道中，频道内所有用户都会收到 \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" 回调，其中 uid 为 666。该音视频流会出现在频道中。

     @param url 添加到直播中的视频流 URL 地址。支持 RTMP、HLS、HTTP-FLV 协议传输。
     - 支持的音频编码格式：AAC；
     - 支持的视频编码格式：H.264(AVC)。
     @param config   所添加的视频流属性定义，详见: InjectStreamConfig 。

     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
        - #ERR_INVALID_ARGUMENT (2): 输入的 URL 为空。请重新调用该方法，并确认输入的媒体流的 URL 有效。
        - #ERR_NOT_READY (3): 用户没有加入频道。
        - #ERR_NOT_SUPPORTED (4): 频道非直播场景。请调用 \ref agora::rtc::IRtcEngine::setChannelProfile "setChannelProfile" 并将频道设置为直播场景再调用该方法。
        - #ERR_NOT_INITIALIZED (7): 引擎没有初始化。请确认调用该方法前已创建 IRtcEngine 对象并完成初始化。
     */
   /** @~english
   * @brief          Adds a voice or video stream URL address to a live broadcast.
   * @brief          The \ref agora::rtc::IRtcEngineEventHandler::onStreamPublished "onStreamPublished" callback returns the inject status. If this method call is successful, the server pulls the voice or video stream and injects it into a live channel. This is applicable to scenarios where all audience members in the channel can watch a live show and interact with each other.
   * @brief          The `addInjectStreamUrl` method call triggers the following callbacks:
   *                 <ul>
   *                 <li> The local client:
   *                    <ul>
   *                    <li> \ref agora::rtc::IRtcEngineEventHandler::onStreamInjectedStatus "onStreamInjectedStatus", with the state of the injecting the online stream.
   *                    <li> \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" (uid: 666), if the method call is successful and the online media stream is injected into the channel.
   *                    </ul>
   *                 <li> The remote client:
   *                    <ul>
   *                    <li> onUserJoined (uid: 666), if the method call is successful and the online media stream is injected into the channel.
   *                    </ul>
   *                 </ul>
   * @note           \arg  Ensure that you enable the RTMP Converter service before using this function. See Prerequisites in the advanced guide *Inject Online Media Streams.
   *                 \arg  This method applies to the `LIVE_BROADCASTING` profile only.
   *                 \arg You can inject only one media stream into the channel at the same time.
   *                 \arg Ensure that you call this method after joining a channel.
   * @param url      Pointer to the URL address to be added to the ongoing live broadcast. Valid protocols are RTMP, HLS, and FLV.
   *                    \arg  Supported FLV audio codec type: AAC.
   *                    \arg  Supported FLV video codec type: H264 (AVC).
   * @param config   Pointer to the InjectStreamConfig object that contains the configuration of the added voice or video stream.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   *                    -  \ref ERR_INVALID_ARGUMENT (2): The injected URL does not exist. Call this method again to inject the stream and ensure that the URL is valid.
   *                    -  \ref ERR_NOT_READY (3): The user is not in the channel.
   *                    -  \ref ERR_NOT_SUPPORTED (4): The channel profile is not live broadcast. Call the \ref setChannelProfile method and set the channel profile to live broadcast before calling this method.
   *                    -  \ref ERR_NOT_INITIALIZED (7): The SDK is not initialized. Ensure that the \ref IRtcEngine object is initialized before calling this method.
   */
	int addInjectStreamUrl(const char* url, const InjectStreamConfig& config);

    /** @~chinese
     * 开始跨频道媒体流转发。该方法可用于实现跨频道连麦等场景。
     *
     * 成功调用该方法后，SDK 会触发
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
     *  "onChannelMediaRelayStateChanged" 和
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayEvent
     * "onChannelMediaRelayEvent" 回调，并在回调中报告当前的跨频道媒体流转发状态和事件。
     * - 如果
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
     *  "onChannelMediaRelayStateChanged" 回调报告 #RELAY_STATE_RUNNING (2) 和
     * #RELAY_OK (0)，且
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayEvent
     * "onChannelMediaRelayEvent" 回调报告
     * #RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL (4)，
     * 则表示 SDK 开始在源频道和目标频道之间转发媒体流。
     * - 如果
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
     *  "onChannelMediaRelayStateChanged" 回调报告 #RELAY_STATE_FAILURE (3)，
     * 则表示跨频道媒体流转发出现异常。
     *
     * @note
     * - 请在成功加入频道后调用该方法。
     * - 在直播场景中，只有角色为主播的用户才能调用该方法。
     * - 成功调用该方法后，若你想再次调用该方法，必须先调用
     * \ref stopChannelMediaRelay() "stopChannelMediaRelay"
     * 方法退出当前的转发状态。
     * - 跨频道媒体流转发功能需要[提交工单](https://agora-ticket.agora.io/)联系技术支持开通。
     * - 该功能不支持 String 型 UID。
     *
     * @param configuration 跨频道媒体流转发参数配置。详见
     * ChannelMediaRelayConfiguration 。
     *
     * @return
     * - 0：方法调用成功。
     * - < 0：方法调用失败
     */
   /** @~english
   * @brief                Starts to relay media streams across channels.
   * @brief                After a successful method call, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged "onChannelMediaRelayStateChanged" and \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayEvent "onChannelMediaRelayEvent" callbacks, and these callbacks return the state and events of the media stream relay.
   *                       <ul>
   *                       <li> If the `onChannelMediaRelayStateChanged` callback returns \ref RELAY_STATE_RUNNING (2) and \ref RELAY_OK (0), and the `onChannelMediaRelayEvent` callback returns \ref RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL (4), the broadcaster starts sending data to the destination channel.
   *                       <li> If the `onChannelMediaRelayStateChanged` callback returns \ref RELAY_STATE_FAILURE (3), an exception occurs during the media stream relay.
   *                       </ul>
   * @note                 \arg  Call this method after the \ref joinChannel method.
   *                       \arg  This method takes effect only when you are a broadcaster in a Live-broadcast channel.
   *                       \arg  After a successful method call, if you want to call this method again, ensure that you call the \ref stopChannelMediaRelay method to quit the current relay.
   *                       \arg  Contact sales-us@agora.io before implementing this function.
   *                       \arg We do not support string user accounts in this API.
   * @param configuration  The configuration of the media stream relay: \ref ChannelMediaRelayConfiguration.
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   */
	int startChannelMediaRelay(const ChannelMediaRelayConfiguration& configuration);

    /** @~chinese
     * 更新媒体流转发的频道。
     *
     * 成功开始跨频道转发媒体流后，如果你希望将流转发到多个目标频道，
     * 或退出当前的转发频道，可以调用该方法。
     *
     * 成功调用该方法后，SDK 会触发
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayEvent
     * "onChannelMediaRelayEvent" 回调，
     * 并在回调中报告状态码 #RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL (7)。
     *
     * @note
     * 请在 \ref startChannelMediaRelay() "startChannelMediaRelay"
     * 方法后调用该方法，更新媒体流转发的频道。
     *
     * @param configuration 跨频道媒体流转发参数配置。详见
     * ChannelMediaRelayConfiguration 。
     *
     * @return
     * - 0：方法调用成功。
     * - < 0：方法调用失败
     */
   /** @~english
   * @brief                Updates the channels for media stream relay. After a successful \ref startChannelMediaRelay method call, if you want to relay the media stream to more channels, or leave the current relay channel, you can call the \ref updateChannelMediaRelay method.
   * @brief                After a successful method call, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayEvent "onChannelMediaRelayEvent" callback with the \ref RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL (7) state code.
   * @note                 Call this method after the \ref startChannelMediaRelay method to update the destination channel.
   * param  configuration  The media stream relay configuration: \ref ChannelMediaRelayConfiguration.
   * @return               \arg  0: Success.
   *                       \arg  < 0: Failure.
   */
	int updateChannelMediaRelay(const ChannelMediaRelayConfiguration& configuration);

    /** @~chinese
     * 停止跨频道媒体流转发。一旦停止，主播会退出所有目标频道。
     *
     * 成功调用该方法后，SDK 会触发
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
     * "onChannelMediaRelayStateChanged" 回调。如果报告 #RELAY_STATE_IDLE (0)
     * 和 #RELAY_OK (0)，则表示已停止转发媒体流。
     *
     * @note
     * 如果该方法调用不成功，SDK 会触发
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
     * "onChannelMediaRelayStateChanged" 回调，并报告状态码
     * #RELAY_ERROR_SERVER_NO_RESPONSE (2) 或
     * #RELAY_ERROR_SERVER_CONNECTION_LOST (8)。你可以调用
     * \ref leaveChannel() "leaveChannel" 方法离开频道，跨频道媒体流转发会自动停止。
     *
     * @return
     * - 0：方法调用成功。
     * - < 0：方法调用失败
     */
   /** @~english
   * @brief       Stops the media stream relay.
   * @brief       Once the relay stops, the broadcaster quits all the destination channels.
   * @brief       After a successful method call, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged "onChannelMediaRelayStateChanged" callback. If the callback returns \ref RELAY_STATE_IDLE (0) and \ref RELAY_OK (0), the broadcaster successfully stops the relay.
   * @note        If the method call fails, the SDK triggers the `onChannelMediaRelayStateChanged` callback with the \ref RELAY_ERROR_SERVER_NO_RESPONSE (2) or \ref RELAY_ERROR_SERVER_CONNECTION_LOST (8) state code. You can leave the channel by calling the \ref leaveChannel method, and the media stream relay automatically stops.
   * @return      \arg  0: Success.
   *              \arg  < 0: Failure.
   */
	int stopChannelMediaRelay();

    /** @~chinese
     删除导入的外部媒体流。

     @note 成功删除外部视频源 URL 地址后会触发 \ref agora::rtc::IRtcEngineEventHandler::onUserOffline "onUserOffline" 回调，uid 为 666。

     @param url 已导入、待删除的外部视频源 URL 地址。
     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
     */
   /**
   * @brief       Removes the voice or video stream URL address from a live broadcast.
   * @brief       This method removes the URL address (added by the \ref addInjectStreamUrl method) from the live broadcast.
   * @note        If this method is called successfully, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserOffline "onUserOffline" callback and returns a stream uid of 666.
   * @param url   Pointer to the URL address of the added stream to be removed.
   * @return      \arg  0: Success.
   *              \arg  < 0: Failure.
   */
	int removeInjectStreamUrl(const char* url);

	bool registerEventHandler(IRtcEngineEventHandler* eventHandler);

	bool unregisterEventHandler(IRtcEngineEventHandler* eventHandler);

    /** @~chinese
     获取当前网络连接状态。

     @note 该方法在加入频道前后都能调用。

     @return #CONNECTION_STATE_TYPE 。
     */
   /** @~english
   * @brief    Gets the current connection state of the SDK.
   * @return   \ref  CONNECTION_STATE_TYPE.
   */
	agora::rtc::CONNECTION_STATE_TYPE getConnectionState();

    /** @~chinese
     注册媒体 metadata 观测器用于接收或发送 metadata。

     @note
     - 请在 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 前调用该方法。
     - 该方法仅使用于直播场景。

     @param observer 指向已注册的 metadata 观测器的指针。详见： IMetadataObserver 。
     @param type 用户希望在观测器中使用的 METADATA 类型 。目前仅支持 VIDEO_METADATA 。详见： \ref IMetadataObserver::METADATA_TYPE "METADATA_TYPE" 。
     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
     */
   /**
   * @brief          Registers the metadata observer.
   * @brief          Registers the metadata observer. You need to implement the \ref IMetadataObserver class and specify the metadata type in this method. A successful call of this method triggers the \ref agora::rtc::IMetadataObserver::getMaxMetadataSize "getMaxMetadataSize" callback. This method enables you to add synchronized metadata in the video stream for more diversified live broadcast interactions, such as sending shopping links, digital coupons, and online quizzes.
   * @note           \arg  Call this method before the joinChannel method.
   *                 \arg  This method applies to the Live-broadcast channel profile.
   * @param observer The \ref IMetadataObserver class. See the definition of \ref IMetadataObserver for details.
   * @param type     See \ref agora::rtc::IMetadataObserver::METADATA_TYPE "METADATA_TYPE". The SDK supports VIDEO_METADATA (0) only for now.
   * @return         \arg  0: Success.
   *                 \arg  < 0: Failure.
   */
	int registerMediaMetadataObserver(IMetadataObserver* observer, IMetadataObserver::METADATA_TYPE type);

    /** @~chinese
     通过 JSON 配置 SDK 提供技术预览或特别定制功能。

     JSON 选项默认不公开。声网工程师正在努力寻求以标准化方式公开 JSON 选项。
     @param parameters JSON 字符串形式的参数

     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
     */
	/** @~english
    Provides technical preview functionalities or special customizations by configuring the SDK with JSON options.

	 The JSON options are not public by default. Agora is working on making commonly used JSON options public in a standard way.

	 @param parameters Sets the parameter as a JSON string in the specified format.

	 @return
	 - 0: Success.
	 - < 0: Failure.
	 */
	int setParameters( const char* parameters );

    /** @~chinese
     创建并获取一个 IChannel 对象。

     你可以多次调用该方法，创建多个 `IChannel` 对象，再调用各 `IChannel` 对象中的 \ref IChannel::joinChannel "joinChannel" 方法，实现同时加入多个频道。

     加入多个频道后，你可以同时订阅各个频道的音、视频流；但是同一时间只能在一个频道发布一路音、视频流。

     @param channelId 能标识频道的频道名，长度在 64 字节以内的字符。以下为支持的字符集范围（共 89 个字符）：
     - 26 个小写英文字母 a~z；
     - 26 个大写英文字母 A~Z；
     - 10 个数字 0~9；
     - 空格；
     - "!"、"#"、"$"、"%"、"&"、"("、")"、"+"、"-"、":"、";"、"<"、"="、"."、">"、"?"、"@"、"["、"]"、"^"、"_"、" {"、"}"、"|"、"~"、","。

     @note
     - 该参数没有默认值，请确保对参数设值。
     - 请勿将该参数设为空字符 ""，否则 SDK 会返回 `ERR_REFUSED(5)`

     @return
     - 方法调用成功，返回 IChannel 对象的指针
     - 方法调用失败，返回一个空指针 NULL
     - 如果将 `channelId` 设为空字符 ""，SDK 会返回 `ERR_REFUSED(5)`
     */
   /** @~english
    Creates and gets an `AgoraRtcChannel` object.

    To join more than one channel, call this method multiple times to create as many `AgoraRtcChannel` objects as needed, and
    call the \ref AgoraRtcChannel::joinChannel "joinChannel" method of each created `AgoraRtcChannel` object.

    After joining multiple channels, you can simultaneously subscribe to streams of all the channels, but publish a stream in only one channel at one time.
    @param channelId The unique channel name for an Agora RTC session. It must be in the string format and not exceed 64 bytes in length. Supported character scopes are:
    - All lowercase English letters: a to z.
    - All uppercase English letters: A to Z.
    - All numeric characters: 0 to 9.
    - The space character.
    - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".

    @note
    - This parameter does not have a default value. You must set it.
    - Do not set it as the empty string "". Otherwise, the SDK returns #ERR_REFUSED (5).

    @return
    - The `AgoraRtcChannel` object, if the method call succeeds.
    - An empty pointer NULL, if the method call fails.
    - `agora::rtc::ERR_REFUSED(5)`, if you set channelId as the empty string "".
    */
   agora::rtc::IChannel* createChannel( const char *channelId );

public:
	friend class agora::media::ue4::AgoraMediaEngine;
   friend class agora::blueprints::AgoraVideoManager;
   friend class agora::blueprints::AgoraAudioManager;
	friend class AgoraVideoDeviceManager;
	friend class AgoraAudioDeviceManager;
	friend class AgoraLiveEngine;
   friend class AParameter;
private:
   /**
   * @brief       Releases all \ref IRtcEngine resources.
   * @param sync  \arg  true: (Synchronous call) The result returns after the \ref IRtcEngine 
   *                    resources are released. The application should not call this method in the SDK 
   *                    generated callbacks. Otherwise, the SDK must wait for the callbacks to return to 
   *                    recover the associated \ref IRtcEngine resources, resulting in a deadlock. 
   *                    The SDK automatically detects the deadlock and converts this method into an  
   *                    asynchronous call, causing the test to take additional time.
   *              \arg  false: (Asynchronous call) The result returns immediately, even when the \ref 
   *                    IRtcEngine resources have not been released. The SDK releases all resources.
   * @note        Do not immediately uninstall the SDK's dynamic library after the call, or it may cause a 
   *              crash due to the SDK clean-up thread not quitting.
   */
	void release(bool sync = false);

private:
	AgoraRtcEngine(agora::rtc::IRtcEngine2* rtcEngine);

private:
	agora::rtc::IRtcEngine2* m_rtcEngine = nullptr;
	bool m_sync = false;
};

/**
* Wrapper around agora::rtc::AParameter. See agora::rtc::IRtcEngineParameters methods description.
*/
class AParameter : public agora::rtc::AParameter
{
public:
   AParameter( AgoraRtcEngine* agoraRtcEngine )
      : agora::rtc::AParameter( agoraRtcEngine->m_rtcEngine ) {}
};
}
}
}
