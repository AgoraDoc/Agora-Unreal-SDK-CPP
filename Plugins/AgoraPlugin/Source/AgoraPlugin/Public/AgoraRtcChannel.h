#pragma once
#include "CoreMinimal.h"
#include "AgoraRtcEngine.h"
#include <memory>

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif


#if (defined(__APPLE__) && TARGET_OS_IPHONE)
#include <Agora/iOS/Include/IAgoraRtcChannel.h>
#else
#include <Agora/IAgoraRtcChannel.h>
#endif

#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

namespace agora {
namespace rtc {
namespace ue4 {

/** @~chinese
 * AgoraRtcChannel 类。
 */
/** @~english
* Wrapper around agora::rtc::IRtcChannel
*/
class AGORAPLUGIN_API AgoraRtcChannel
{
public:
   AgoraRtcChannel() = delete;
   AgoraRtcChannel( const AgoraRtcChannel& other );
   AgoraRtcChannel( AgoraRtcChannel&& other ) noexcept;
   AgoraRtcChannel& operator=( const AgoraRtcChannel& other );
   AgoraRtcChannel& operator=( AgoraRtcChannel&& other ) noexcept;
   ~AgoraRtcChannel();

public:

   /** @~chinese
   * 创建 IChannel 对象。
   * @param channel IChannel 对象的指针。
   * @return
   * - 方法调用成功：返回 IChannel 对象指针。
   * - 方法调用失败：返回一个空指针。
   */
   /** @~english
   Creates the \ref IChannel object and returns the pointer.
   @return   \arg Success: Pointer to the \ref IChannel object.
             \arg Failure: nullptr.
   */
   static AgoraRtcChannel* createAgoraRtcChannel( agora::rtc::IChannel *channel );

   /** @~chinese
    * 设置 AgoraRtcChannel 频道事件句柄。
    *
    * 设置 AgoraRtcChannel 频道事件句柄后，你可以监听 AgoraRtcChannel 的频道事件，以及相关质量数据报告。
    *
    * @param channelEh AgoraRtcChannel 对象的事件句柄。详见 \ref agora::rtc::IChannelEventHandler "IChannelEventHandler"。
    */
   /** @~english
    Sets the channel event handler.

     After setting the channel event handler, you can listen for channel events and receive the statistics of the corresponding `AgoraRtcChannel` object.

     @param channelEh The event handler of the `AgoraRtcChannel` object. For details, see IChannelEventHandler.

     @return
     - 0: Success.
     - < 0: Failure.
     */
   int setChannelEventHandler( agora::rtc::IChannelEventHandler *channelEh );

    /** @~chinese
     * 通过 UID 加入频道。

     该方法与 IRtcEngine 类下的 `joinChannel` 方法有以下区别：

     | IChannel::joinChannel                                                                                                                    | IRtcEngine::joinChannel                                                                                      |
     |------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------|
     | 无 `channelId` 参数。因为创建 IChannel 对象时已指定了 `channelId`。                         | 需要填入可以标识频道的 `channelId`。                         |
     | 加了 `options` 参数，可在加入频道前通过该参数设置是否订阅该频道的音视频流。                            | 无 `options` 参数。加入频道即默认订阅频道内的音视频流。 |
     | 通过创建多个 IChannel 对象，并调用相应对象的 \ref IChannel joinChannel "joinChannel" 方法，实现同时加入多个频道。                    |只允许加入一个频道。|
     | 通过该方法加入频道后，SDK 默认不发布本地音视频流到本频道，用户需要调用 \ref IChannel publish "publish" 方法进行发布。  |通过该方法加入频道后，SDK 默认发布音视频流发布到本频道。|

     用户成功加入（切换）频道后，默认订阅频道内所有其他用户的音频流和视频流，因此产生用量并影响计费。如果想取消订阅，可以通过调用相应的 `mute` 方法实现。

     @note
     - 该方法不支持相同的用户重复加入同一个频道。
     - 我们建议不同频道中使用不同的 UID。
     - 如果想要从不同的设备同时接入同一个频道，请确保每个设备上使用的 UID 是不同的。
     - 请确保用于生成 Token 的 App ID 和创建 IRtcEngine 对象时用的 App ID 一致。

     @param token 在 App 服务器端生成的用于鉴权的 Token：
     - 安全要求不高：你可以使用控制台生成的临时 Token，详见 [获取临时 Token](https://docs.agora.io/cn/Agora%20Platform/token?platform=All%20Platforms#生成-token).
     - 安全要求高：将值设为你的服务端生成的正式 Token，详见 [获取正式 Token](https://docs.agora.io/cn/Interactive%20Broadcast/token_server?platform=All%20Platforms).
     @param info （非必选项）开发者需加入的任何附加信息。一般可设置为空字符串，或频道相关信息。该信息不会传递给频道内的其他用户。
     @param uid  用户 ID，32 位无符号整数。建议设置范围：1 到 2<sup>32</sup>-1，并保证唯一性。如果不指定（即设为 0），SDK 会自动分配一个，并在 \ref agora::rtc::IChannelEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" 回调中返回，App 层必须记住该返回值并维护，SDK 不对该返回值进行维护。
     @param options 频道媒体设置选项: \ref agora::rtc::ChannelMediaOptions "ChannelMediaOptions"。

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
    Joins the channel with a user ID.

    This method differs from the `joinChannel` method in the `AgoraRtcEngine` class in the following aspects:

    | AgoraRtcChannel::joinChannel                                                                                                                        | AgoraRtcEngine::joinChannel                                                                                    |
    |-----------------------------------------------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------|
    | Does not contain the `channelId` parameter, because `channelId` is specified when creating the `AgoraRtcChannel` object.                            | Contains the `channelId` parameter, which specifies the channel to join.                                       |
    | Contains the `options` parameter, which decides whether to subscribe to all streams before joining the channel.                                     | Does not contain the `options` parameter. By default, users subscribe to all streams when joining the channel. |
    | Users can join multiple channels simultaneously by creating multiple `AgoraRtcChannel` objects and calling the `joinChannel` method of each object. | Users can join only one channel.                                                                               |
    | By default, the SDK does not publish any stream after the user joins the channel. You need to call the publish method to do that.                   | By default, the SDK publishes streams once the user joins the channel.                                         |

    @note
    - If you are already in a channel, you cannot rejoin it with the same `uid`.
    - We recommend using different UIDs for different channels.
    - If you want to join the same channel from different devices, ensure that the UIDs in all devices are different.
    - Ensure that the app ID you use to generate the token is the same with the app ID used when creating the `AgoraRtcChannel` object.

    @param token The token for authentication:
    - In situations not requiring high security: You can use the temporary token generated at Console. For details, see [Get a temporary token](https://docs.agora.io/en/Agora%20Platform/token?platfor%20*%20m=All%20Platforms#get-a-temporary-token).
    - In situations requiring high security: Set it as the token generated at your server. For details, see [Generate a token](https://docs.agora.io/en/Agora%20Platform/token?platfor%20*%20m=All%20Platforms#get-a-token).
    @param info (Optional) Additional information about the channel. This parameter can be set as null. Other users in the channel do not receive this information.
    @param uid The user ID. A 32-bit unsigned integer with a value ranging from 1 to (232-1). This parameter must be unique. If `uid` is not assigned (or set as `0`), the SDK assigns a `uid` and reports it in the \ref agora::rtc::IChannelEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" callback. The app must maintain this user ID.
    @param options The channel media options: \ref ChannelMediaOptions

    @return
    - 0: Success.
    - < 0: Failure.
       - #ERR_INVALID_ARGUMENT (-2)
       - #ERR_NOT_READY (-3)
       - #ERR_REFUSED (-5)
    */
   int joinChannel( const char* token,
                    const char* info,
                    agora::rtc::uid_t uid,
                    const agora::rtc::ChannelMediaOptions& options );

    /** @~chinese
     * 通过 User account 加入频道。

     该方法与 IRtcEngine 类下的 `joinChannelWithUserAccount` 方法有以下区别：

     | IChannel::joinChannelWithUserAccount                                                                                                     | IRtcEngine::joinChannelWithUserAccount                                                                                      |
     |------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------|
     | 无 `channelId` 参数。因为创建 IChannel 对象时已指定了 `channelId`。                         | 需要填入可以标识频道的 `channelId`。                         |
     | 加了 `options` 参数，可在加入频道前通过该参数设置是否订阅该频道的音视频流。                            | 无 `options` 参数。加入频道即默认订阅频道内的音视频流。 |
     | 通过创建多个 IChannel 对象，并调用相应对象的 \ref IChannel joinChannelWithUserAccount "joinChannelWithUserAccount" 方法，实现同时加入多个频道。                    |只允许加入一个频道。|
     | 通过该方法加入频道后，SDK 默认不发布本地音视频流到本频道，用户需要调用 \ref IChannel publish "publish" 方法进行发布。  |通过该方法加入频道后，SDK 默认发布音视频流发布到本频道。|

     用户成功加入（切换）频道后，默认订阅频道内所有其他用户的音频流和视频流，因此产生用量并影响计费。如果想取消订阅，可以通过调用相应的 `mute` 方法实现。

     @note
     - 该方法不支持相同的用户重复加入同一个频道。
     - 我们建议不同频道中使用不同的 user account。
     - 如果想要从不同的设备同时接入同一个频道，请确保每个设备上使用的 user account 是不同的。
     - 请确保用于生成 Token 的 App ID 和创建 IChannel 对象时用的 App ID 一致。

     @param token 在 App 服务器端生成的用于鉴权的 Token：
     - 安全要求不高：你可以使用控制台生成的临时 Token，详见 [获取临时 Token](https://docs.agora.io/cn/Agora%20Platform/token?platform=All%20Platforms#生成-token).
     - 安全要求高：将值设为你的服务端生成的正式 Token，详见 [获取正式 Token](https://docs.agora.io/cn/Interactive%20Broadcast/token_server?platform=All%20Platforms).
     @param userAccount 用户 User Account。该参数为必需，最大不超过 255 字节，不可为 null。请确保加入频道的 User Account 的唯一性。 以下为支持的字符集范围（共 89 个字符）：
     - 26 个小写英文字母 a-z
     - 26 个大写英文字母 A-Z
     - 10 个数字 0-9
     - 空格
     - "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ","
     @param options 频道媒体设置选项: ChannelMediaOptions。

     @return
     - 0: 方法调用成功
     - < 0: 方法调用失败
        - #ERR_INVALID_ARGUMENT (2)
        - #ERR_NOT_READY (3)
        - #ERR_REFUSED (5)
     */
    /** @~english
    Joins the channel with a user account.

    After the user successfully joins the channel, the SDK triggers the following callbacks:

    - The local client: \ref agora::rtc::IChannelEventHandler::onJoinChannelSuccess "onJoinChannelSuccess"
    - The remote client: \ref agora::rtc::IChannelEventHandler::onUserJoined "onUserJoined"

    @note To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account.
    If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.

    @param token The token generated at your server:
    - For low-security requirements: You can use the temporary token generated at Console. For details, see [Get a temporary toke](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-temporary-token).
    - For high-security requirements: Set it as the token generated at your server. For details, see [Get a token](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-token).
    @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
    - All lowercase English letters: a to z.
    - All uppercase English letters: A to Z.
    - All numeric characters: 0 to 9.
    - The space character.
    - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
    @param options The channel media options: \ref ChannelMediaOptions.

    @return
    - 0: Success.
    - < 0: Failure.
       - #ERR_INVALID_ARGUMENT (-2)
       - #ERR_NOT_READY (-3)
       - #ERR_REFUSED (-5)
    */
   int joinChannelWithUserAccount( const char* token,
                                   const char* userAccount,
                                   const agora::rtc::ChannelMediaOptions& options );

    /** @~chinese
     * 离开频道。

     离开频道，即挂断或退出通话。

     当调用 \ref agora::rtc::IChannel::joinChannel "joinChannel" 方法后，必须调用 leaveChannel 结束通话，否则无法开始下一次通话。 不管当前是否在通话中，都可以调用 leaveChannel，没有副作用。该方法会把会话相关的所有资源释放掉。
     该方法是异步操作，调用返回时并没有真正退出频道。在真正退出频道后，SDK 会触发 \ref agora::rtc::IChannelEventHandler::onLeaveChannel "onLeaveChannel" 回调。
     成功调用该方法离开频道后，本地会触发 \ref agora::rtc::IChannelEventHandler::onLeaveChannel "onLeaveChannel" 回调；通信场景下的用户和直播场景下的主播离开频道后，远端会触发 \ref agora::rtc::IChannelEventHandler::onUserOffline "onUserOffline" 回调。

     @note
     - 如果你调用了 leaveChannel 后立即调用 \ref agora::rtc::IChannel::release "release"，SDK 将无法触发 \ref agora::rtc::IChannelEventHandler::onLeaveChannel "onLeaveChannel" 回调。
     - 如果你在旁路推流时调用 leaveChannel 方法， SDK 将自动调用 \ref IChannel::removePublishStreamUrl "removePublishStreamUrl" 方法。

     @return
     - 0(ERR_OK): 方法调用成功。
     - < 0: 方法调用失败。
        - -1(ERR_FAILED): 一般性的错误（未明确归类）。
        - -2(ERR_INALID_ARGUMENT): 参数无效。
        - -7(ERR_NOT_INITIALIZED): SDK 尚未初始化。
     */
    /** @~english
     Allows a user to leave a channel, such as hanging up or exiting a call.

    After joining a channel, the user must call the *leaveChannel* method to end the call before joining another channel.

    This method returns 0 if the user leaves the channel and releases all resources related to the call.

    This method call is asynchronous, and the user has not left the channel when the method call returns. Once the user leaves the channel, the SDK triggers the \ref agora::rtc::IChannelEventHandler::onLeaveChannel "onLeaveChannel" callback.

    A successful `leaveChannel` method call triggers the following callbacks:
    - The local client: \ref agora::rtc::IChannelEventHandler::onLeaveChannel "onLeaveChannel"
    - The remote client: \ref agora::rtc::IChannelEventHandler::onUserOffline "onUserOffline", if the user leaving the channel is in the Communication channel, or is a BROADCASTER in the Live Broadcast profile.

    @note
    - If you call the \ref release method immediately after the *leaveChannel* method, the `leaveChannel` process interrupts, and the \ref agora::rtc::IChannelEventHandler::onLeaveChannel "onLeaveChannel" callback is not triggered.
    - If you call the `leaveChannel` method during a CDN live streaming, the SDK triggers the \ref removePublishStreamUrl method.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int leaveChannel();

   /** @~chinese
    将本地音视频流发布到本频道。

    该方法的调用需满足以下要求，否则 SDK 会返回 #ERR_REFUSED (5) :
    - 该方法仅支持将音视频流发布到当前 IChannel 类所对应的频道。
    - 直播场景下，该方法仅适用于角色为主播的用户。你可以调用该 IChannel 类下的 \ref agora::rtc::IChannel::setClientRole "setClientRole" 方法设置用户角色。
    - SDK 只支持用户同一时间在一个频道发布一路音视频流。详情请参考进阶功能《加入多频道》。

    @return
    - 0: 方法调用成功
    - < 0: 方法调用失败
      - ERR_REFUSED (5): 调用被拒绝
    */
   /** @~english
    Publishes the local stream to the channel.

    You must keep the following restrictions in mind when calling this method. Otherwise, the SDK returns the #ERR_REFUSED (5):
    - This method publishes one stream only to the channel corresponding to the current `IChannel` object.
    - In a Live Broadcast channel, only a broadcaster can call this method. To switch the client role, call \ref setClientRole of the current `AgoraRtcChannel` object.
    - You can publish a stream to only one channel at a time. For details on joining multiple channels, see the advanced guide *Join Multiple Channels*.

    @return
    - 0: Success.
    - < 0: Failure.
       - #ERR_REFUSED (5): The method call is refused.
    */
   int publish();

   /** @~chinese
    停止将本地音视频流发布到本频道。

    请确保你想要 `unpublish` 音视频流的频道 `channelId`，与当前正在 \ref IChannel publish "publish" 音视频流的频道 `channelId` 一致，否则 SDK 会返回 ERR_REFUSED (5)

    @return
    - 0: 方法调用成功
    - < 0: 方法调用失败
      - ERR_REFUSED (5): 调用被拒绝
    */
   /** @~english
    Stops publishing a stream to the channel.

    If you call this method in a channel where you are not publishing streams, the SDK returns #ERR_REFUSED (5).

    @return
    - 0: Success.
    - < 0: Failure.
       - #ERR_REFUSED (5): The method call is refused.
    */
   int unpublish();


   /** @~chinese
    获取当前频道的频道名。

    @return
    - 方法调用成功，返回 `channelId`，即当前频道的频道名。
    - 方法调用失败，返回空字符串 ""。
    */
   /** @~english
   Gets the channel ID of the current `AgoraRtcChannel` object.

    @return
    - The channel ID of the current `AgoraRtcChannel` object, if the method call succeeds.
    - The empty string "", if the method call fails.
    */
   const char *channelId();


   /** @~chinese
    获取当前通话 ID。

    @note 该方法需要在加入频道后调用。

    客户端在每次 \ref agora::rtc::IChannel::joinChannel "joinChannel" 后会生成一个对应的 callId，标识该客户端的此次通话。
    有些方法如 \ref agora::rtc::IRtcEngine::rate "rate" 、 \ref agora::rtc::IRtcEngine::complain "complain" 需要在通话结束后调用，向 SDK 提交反馈，这些方法必须指定 CallId 参数。使用这些反馈方法，需要在通话过程中调用 \ref agora::rtc::IChannel::getCallId "getCallId" 方法获取 CallId，在通话结束后在反馈方法中作为参数传入。

    @param[out] callId 当前的通话 ID。
    @return
    - 0: 方法调用成功，返回当前通话 ID
    - < 0: 方法调用失败
    */
   /** @~english
    Retrieves the current call ID.

    When a user joins a channel on a client, a `callId` is generated to identify the call from the client.
    Feedback methods, such as \ref AgoraRtcEngine::rate "rate" and \ref AgoraRtcEngine::complain "complain", must be called after the call ends to submit feedback to the SDK.

    The `rate` and `complain` methods require the `callId` parameter retrieved from the `getCallId` method during a call. `callId` is passed as an argument into the `rate` and `complain` methods after the call ends.

    @param callId The current call ID.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int getCallId( agora::util::AString& callId );

   /** @~chinese
    更新 Token。

    该方法用于更新 Token。如果启用了 Token 机制，过一段时间后使用的 Token 会失效。当：

    - 发生 \ref agora::rtc::IChannelEventHandler::onTokenPrivilegeWillExpire "onTokenPrivilegeWillExpire" 回调时，或发生
    - \ref agora::rtc::IChannelEventHandler::onConnectionStateChanged "onConnectionStateChanged" 回调报告 CONNECTION_CHANGED_TOKEN_EXPIRED(9) 时。

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
    Gets a new token when the current token expires after a period of time.

    The `token` expires after a period of time once the token schema is enabled when:

    - The SDK triggers the \ref agora::rtc::IChannelEventHandler::onTokenPrivilegeWillExpire "onTokenPrivilegeWillExpire" callback, or
    - The \ref agora::rtc::IChannelEventHandler::onConnectionStateChanged "onConnectionStateChanged" reports `CONNECTION_CHANGED_TOKEN_EXPIRED(9)`.

    The application should call this method to get a new token. Failure to do so will result in the SDK disconnecting from the server.

    @param token Pointer to the new token.
    @return
    - 0: Success.
    - < 0: Failure.
    */
   int renewToken( const char* token );

   /** @~chinese
    启用内置加密，并设置数据加密密码。

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
    Enables built-in encryption with an encryption password before users join a channel.

    All users in a channel must use the same encryption password. The encryption password is automatically cleared once a user leaves the channel.

    If an encryption password is not specified, the encryption functionality will be disabled.

    @note
    - Do not use this method for CDN live streaming.
    - For optimal transmission, ensure that the encrypted data size does not exceed the original data size + 16 bytes. 16 bytes is the maximum padding size for AES encryption.

    @param secret Pointer to the encryption password.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int setEncryptionSecret( const char* secret );

   /** @~chinese
    启用内置的加密方案。

    Agora Video SDK 支持内置加密方案，默认支持 AES-128-XTS。如需采用其他加密方案，可以调用本方法。同一频道内的所有用户必须设置相同的加密方式和 secret 才能进行通话。关于这几种加密方式的区别，请参考 AES 加密算法的相关资料。

    @note 在调用本方法前，请先调用 \ref agora::rtc::IChannel::setEncryptionSecret "setEncryptionSecret" 启用内置加密功能。

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
    Sets the built-in encryption mode.

    The Agora SDK supports built-in encryption, which is set to the `aes-128-xts` mode by default. Call this method to use other encryption modes.

    All users in the same channel must use the same encryption mode and password.

    Refer to the information related to the AES encryption algorithm on the differences between the encryption modes.

    @note Call the \ref setEncryptionSecret method to enable the built-in encryption function before calling this method.

    @param encryptionMode The set encryption mode:
    - "aes-128-xts": (Default) 128-bit AES encryption, XTS mode.
    - "aes-128-ecb": 128-bit AES encryption, ECB mode.
    - "aes-256-xts": 256-bit AES encryption, XTS mode.
    - "": When encryptionMode is set as NULL, the encryption mode is set as "aes-128-xts" by default.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int setEncryptionMode( const char* encryptionMode );

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
    Registers a packet observer.

    The Agora SDK allows your application to register a packet observer to receive callbacks for voice or video packet transmission.

    @note
    - The size of the packet sent to the network after processing should not exceed 1200 bytes, otherwise, the packet may fail to be sent.
    - Ensure that both receivers and senders call this method, otherwise, you may meet undefined behaviors such as no voice and black screen.
    - When you use CDN live streaming, recording or storage functions, Agora doesn't recommend calling this method.

    @param observer The registered packet observer. See \ref IPacketObserver.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int registerPacketObserver( agora::rtc::IPacketObserver* observer );

   /** @~chinese
    注册媒体 metadata 观测器用于接收或发送 metadata。

    @note
    - 请在 \ref agora::rtc::IChannel::joinChannel "joinChannel" 前调用该方法。
    - 该方法仅适用于直播场景。

    @param observer 指向已注册的 metadata 观测器的指针。详见：IMetadataObserver。
    @param type 用户希望在观测器中使用的 METADATA 类型 。目前仅支持 VIDEO_METADATA。详见：\ref IMetadataObserver::METADATA_TYPE "METADATA_TYPE" 。
    @return
    - 0: 方法调用成功
    - < 0: 方法调用失败
    */
   /** @~english
    Registers the metadata observer.

    Registers the metadata observer. You need to implement the IMetadataObserver class and specify the metadata type in this method. A successful call of this method triggers the \ref IMetadataObserver::getMaxMetadataSize "getMaxMetadataSize" callback.
    This method enables you to add synchronized metadata in the video stream for more diversified live broadcast interactions, such as sending shopping links, digital coupons, and online quizzes.

    @note
    - Call this method before the joinChannel method.
    - This method applies to the Live-broadcast channel profile.

    @param observer The IMetadataObserver class. See the definition of \ref IMetadataObserver for details.
    @param type See \ref IMetadataObserver::METADATA_TYPE "METADATA_TYPE". The SDK supports VIDEO_METADATA (0) only for now.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int registerMediaMetadataObserver( agora::rtc::IMetadataObserver *observer, agora::rtc::IMetadataObserver::METADATA_TYPE type );

   /** @~chinese
    设置直播场景下的用户角色。
    *
    * 在加入频道前，用户需要通过本方法设置观众（默认）或主播。在加入频道后，用户可以通过本方法切换用户角色。
    *
    * 直播场景下，如果你在加入频道后调用该方法切换用户角色，调用成功后，本地会触发 \ref agora::rtc::IChannelEventHandler::onClientRoleChanged "onClientRoleChanged" 回调；远端会触发 \ref agora::rtc::IChannelEventHandler::onUserJoined "onUserJoined" 回调或 \ref agora::rtc::IChannelEventHandler::onUserOffline "onUserOffline" (BECOME_AUDIENCE) 回调。
    *
    * @note 该方法仅适用于直播场景。
    *
    * @param role 直播场景里的用户角色: #CLIENT_ROLE_TYPE
    *
    * @return
    * - 0: 方法调用成功
    * - < 0: 方法调用失败
    */
   /** @~english
    Sets the role of the user, such as a host or an audience (default), before joining a channel in a live broadcast.

    This method can be used to switch the user role in a live broadcast after the user joins a channel.

    In the Live Broadcast profile, when a user switches user roles after joining a channel, a successful \ref setClientRole method call triggers the following callbacks:
    - The local client: \ref agora::rtc::IChannelEventHandler::onClientRoleChanged "onClientRoleChanged"
    - The remote client: \ref agora::rtc::IChannelEventHandler::onUserJoined "onUserJoined" or \ref agora::rtc::IChannelEventHandler::onUserOffline "onUserOffline" (BECOME_AUDIENCE)

    @note
    This method applies only to the Live-broadcast profile.

    @param role Sets the role of the user. See #CLIENT_ROLE_TYPE.
    @return
    - 0: Success.
    - < 0: Failure.
    */
   int setClientRole( agora::rtc::CLIENT_ROLE_TYPE role );

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
    Prioritizes a remote user's stream.

    Use this method with the \ref AgoraRtcEngine::setRemoteSubscribeFallbackOption "setRemoteSubscribeFallbackOption" method.
    If the fallback function is enabled for a subscribed stream, the SDK ensures the high-priority user gets the best possible stream quality.

    @note The Agora SDK supports setting `serPriority` as high for one user only.

    @param  uid  The ID of the remote user.
    @param  userPriority Sets the priority of the remote user. See #PRIORITY_TYPE.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int setRemoteUserPriority( agora::rtc::uid_t uid, agora::rtc::PRIORITY_TYPE userPriority );

   /** @~chinese
    设置远端用户的语音位置。

    设置远端用户声音的空间位置和音量，方便本地用户听声辨位。

    通过调用该接口设置远端用户声音出现的位置，左右声道的声音差异会产生声音的方位感，从而判断出远端用户的实时位置。在多人在线游戏场景，如吃鸡游戏中，该方法能有效增加游戏角色的方位感，模拟真实场景。

    @note
    - 使用该方法需要在加入频道前调用 \ref agora::rtc::IRtcEngine::enableSoundPositionIndication "enableSoundPositionIndication" 开启远端用户的语音立体声。
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
    Sets the sound position and gain of a remote user.

    When the local user calls this method to set the sound position of a remote user, the sound difference between the left and right channels allows the
    local user to track the real-time position of the remote user, creating a real sense of space. This method applies to massively multiplayer online games,
    such as Battle Royale games.

    @note
    - For this method to work, enable stereo panning for remote users by calling the \ref AgoraRtcEngine::enableSoundPositionIndication "enableSoundPositionIndication" method before joining a channel.
    - This method requires hardware support. For the best sound positioning, we recommend using a stereo speaker.

    @param uid The ID of the remote user.
    @param pan The sound position of the remote user. The value ranges from -1.0 to 1.0:
    - 0.0: the remote sound comes from the front.
    - -1.0: the remote sound comes from the left.
    - 1.0: the remote sound comes from the right.
    @param gain Gain of the remote user. The value ranges from 0.0 to 100.0. The default value is 100.0 (the original gain of the remote user).
    The smaller the value, the less the gain.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int setRemoteVoicePosition( agora::rtc::uid_t uid, double pan, double gain );

   /** @~chinese
    更新远端视图显示模式。

    初始化远端用户视图后，你可以调用该方法更新远端用户视图在本地显示时的渲染和镜像模式。该方法只影响本地用户看到的视频画面。

    @note
    - 请在调用 \ref agora::rtc::IRtcEngine::setupRemoteVideo "setupRemoteVideo" 方法初始化远端视图后，调用该方法。
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
    Updates the display mode of the video view of a remote user.

    After initializing the video view of a remote user, you can call this method to update its rendering and mirror modes.
    This method affects only the video view that the local user sees.

    @note
    - Call this method after calling the \ref AgoraRtcEngine::setupRemoteVideo "setupRemoteVideo" method to initialize the remote video view.
    - During a call, you can call this method as many times as necessary to update the display mode of the video view of a remote user.

    @param userId The ID of the remote user.
    @param renderMode The rendering mode of the remote video view. See #RENDER_MODE_TYPE.
    @param mirrorMode
    - The mirror mode of the remote video view. See #VIDEO_MIRROR_MODE_TYPE.
    - **Note**: The SDK disables the mirror mode by default.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int setRemoteRenderMode( agora::rtc::uid_t userId, agora::rtc::RENDER_MODE_TYPE renderMode, agora::rtc::VIDEO_MIRROR_MODE_TYPE mirrorMode );


   /** @~chinese
    设置是否默认接收所有音频流。

    该方法在加入频道前后都可调用。如果在加入频道后调用 `setDefaultMuteAllRemoteAudioStreams (true)`，会接收不到设置后加入频道的用户的音频流。

    @note 停止接收音频流后，如果想要恢复接收，请调用 \ref agora::rtc::IChannel::muteRemoteAudioStream "muteRemoteAudioStream (false)"，
    并指定你想要接收的远端用户 `uid`；如果想恢复接收多个用户的音频流，则需要多次调用 `muteRemoteAudioStream`。
    `setDefaultMuteAllRemoteAudioStreams (false)` 只能恢复接收后面加入频道的用户的音频流。

    @param mute
    - true:  默认停止接收所有音频流；
    - false: 默认接收所有音频流（默认）。

    @return
    - 0: 方法调用成功
    - < 0: 方法调用失败
    */
   /** @~english
    Sets whether to receive all remote audio streams by default.

    You can call this method either before or after joining a channel. If you call `setDefaultMuteAllRemoteAudioStreams (true)` after joining a channel, the remote audio streams of all subsequent users are not received.

    @note If you want to resume receiving the audio stream, call \ref muteRemoteAudioStream "muteRemoteAudioStream (false)",
    and specify the ID of the remote user whose audio stream you want to receive.
    To receive the audio streams of multiple remote users, call `muteRemoteAudioStream (false)` as many times.
    Calling `setDefaultMuteAllRemoteAudioStreams (false)` resumes receiving the audio streams of subsequent users only.

    @param mute Sets whether to receive/stop receiving all remote users' audio streams by default:
    - true:  Stops receiving all remote users' audio streams by default.
    - false: (Default) Receives all remote users' audio streams by default.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int setDefaultMuteAllRemoteAudioStreams( bool mute );

   /** @~chinese
    设置是否默认停止接收视频流。

    该方法在加入频道前后都可调用。如果在加入频道后调用 `setDefaultMuteAllRemoteVideoStreams (true)`，会接收不到设置后加入频道的用户的视频流。

    @note 停止接收视频流后，如果想要恢复接收，请调用 \ref agora::rtc::IChannel::muteRemoteVideoStream "muteRemoteVideoStream (false)"，
    并指定你想要接收的远端用户 `uid`；如果想恢复接收多个用户的视频流，则需要多次调用 `muteRemoteVideoStream`。`setDefaultMuteAllRemoteVideoStreams (false)`
    只能恢复接收后面加入频道的用户的视频流。

    @param mute
    - true: 默认停止接收所有远端视频；
    - false: 默认接收所有远端视频（默认）。

    @return
    - 0: 方法调用成功
    - < 0: 方法调用失败
    */
   /** @~english
    Sets whether to receive all remote video streams by default.

    You can call this method either before or after joining a channel. If you call `setDefaultMuteAllRemoteVideoStreams (true)` after joining a channel, 
    the remote video streams of all subsequent users are not received.

    @note If you want to resume receiving the video stream, call \ref muteRemoteVideoStream "muteRemoteVideoStream (false)", 
    and specify the ID of the remote user whose video stream you want to receive.
    To receive the video streams of multiple remote users, call `muteRemoteVideoStream (false)` as many times. Calling `setDefaultMuteAllRemoteVideoStreams (false)` resumes
    receiving the video streams of subsequent users only.

    @param mute Sets whether to receive/stop receiving all remote users' video streams by default:
    - true: Stop receiving all remote users' video streams by default.
    - false: (Default) Receive all remote users' video streams by default.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int setDefaultMuteAllRemoteVideoStreams( bool mute );

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
    Stops/Resumes receiving all remote users' audio streams.

    @param mute Sets whether to receive/stop receiving all remote users' audio streams.
    - true: Stops receiving all remote users' audio streams.
    - false: (Default) Receives all remote users' audio streams.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int muteAllRemoteAudioStreams( bool mute );

   /** @~chinese
    调节本地播放的指定远端用户信号音量。

    你可以在通话中调用该方法调节指定远端用户在本地播放的音量。如需调节多个用户在本地播放的音量，则需多次调用该方法。

    @note
    - 请在加入频道后，调用该方法。
    - 该方法调节的是本地播放的指定远端用户混音后的音量。

    @param userId 远端用户 ID。
    @param volume 播放音量，取值范围为 [0,100]:
    - 0: 静音
    - 100: 原始音量

    @return
    - 0: 方法调用成功
    - < 0: 方法调用失败
    */
   /** @~english
    Adjust the playback volume of the specified remote user.

    After joining a channel, call \ref AgoraRtcEngine::adjustPlaybackSignalVolume "adjustPlaybackSignalVolume" to adjust the playback volume of different remote users,
    or adjust multiple times for one remote user.

    @note
    - Call this method after joining a channel.
    - This method adjusts the playback volume, which is the mixed volume for the specified remote user.
    - This method can only adjust the playback volume of one specified remote user at a time. If you want to adjust the playback volume of several remote users,
    call the method multiple times, once for each remote user.

    @param userId The user ID, which should be the same as the `uid` of \ref joinChannel
    @param volume The playback volume of the voice. The value ranges from 0 to 100:
    - 0: Mute.
    - 100: Original volume.

    @return
    - 0: Success.
   - < 0: Failure.
    */
   int adjustUserPlaybackSignalVolume( agora::rtc::uid_t userId, int volume );

   /** @~chinese
    接收／停止接收指定音频流。

    @note
    - 如果之前有调用过 \ref agora::rtc::IChannel::muteAllRemoteAudioStreams "muteAllRemoteAudioStreams" (true) 停止订阅所有远端音频，在调用本 API 之前请确保你已调用 \ref agora::rtc::IChannel::muteAllRemoteAudioStreams "muteAllRemoteAudioStreams" (false)。 muteAllRemoteAudioStreams 是全局控制，muteRemoteAudioStream 是精细控制。
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
   Stops/Resumes receiving a specified remote user's audio stream.

   @note If you called the \ref muteAllRemoteAudioStreams method and set `mute` as `true` to stop
    receiving all remote users' audio streams, call the `muteAllRemoteAudioStreams` method and set `mute` as `false` before calling this method.
    The `muteAllRemoteAudioStreams` method sets all remote audio streams, while the `muteRemoteAudioStream` method sets a specified remote audio stream.

   @param userId The user ID of the specified remote user sending the audio.
   @param mute Sets whether to receive/stop receiving a specified remote user's audio stream:
   - true: Stops receiving the specified remote user's audio stream.
   - false: (Default) Receives the specified remote user's audio stream.

   @return
   - 0: Success.
   - < 0: Failure.

   */
   int muteRemoteAudioStream( agora::rtc::uid_t userId, bool mute );

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
    Stops/Resumes receiving all video stream from a specified remote user.

    @param  mute Sets whether to receive/stop receiving all remote users' video streams:
    - true: Stop receiving all remote users' video streams.
    - false: (Default) Receive all remote users' video streams.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int muteAllRemoteVideoStreams( bool mute );

   /** @~chinese
    接收／停止接收指定远端用户的视频流。

    @note
    - 该方法在加入频道前后都能调用。如果在加入频道前调用，需要自行维护远端用户的 `uid`。
    - 如果之前调用过 \ref agora::rtc::IChannel::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams" (true) 停止接收放所有远端视频流，在调用本 API 之前请确保你已调用 \ref agora::rtc::IChannel::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams" (false) 。\ref agora::rtc::IChannel::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams" 是全局控制，\ref agora::rtc::IChannel::muteRemoteVideoStream "muteRemoteVideoStream" 是精细控制。

    @param userId 指定用户的用户 ID。
    @param mute
    - true: 停止接收指定远端用户的视频流；
    - false: 允许接收指定远端用户的视频流（默认）。

    @return
    - 0: 方法调用成功
    - < 0: 方法调用失败
    */
   /** @~english
    Stops/Resumes receiving the video stream from a specified remote user.

    @note If you called the \ref muteAllRemoteVideoStreams method and
    set `mute` as `true` to stop receiving all remote video streams, call the `muteAllRemoteVideoStreams` method and
    set `mute` as `false` before calling this method.

    @param userId The user ID of the specified remote user.
    @param mute Sets whether to stop/resume receiving the video stream from a specified remote user:
    - true: Stop receiving the specified remote user's video stream.
    - false: (Default) Receive the specified remote user's video stream.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int muteRemoteVideoStream( agora::rtc::uid_t userId, bool mute );

   /** @~chinese
    设置订阅的视频流类型。

    在网络条件受限的情况下，如果发送端没有调用 \ref agora::rtc::IRtcEngine::enableDualStreamMode "enableDualStreamMode" (false) 关闭双流模式，
    接收端可以选择接收大流还是小流。其中，大流可以接为高分辨率高码率的视频流， 小流则是低分辨率低码率的视频流。

    正常情况下，用户默认接收大流。如需接收小流，可以调用本方法进行切换。SDK 会根据视频窗口的大小动态调整对应视频流的大小，以节约带宽和计算资源。
    视频小流默认的宽高比和视频大流的宽高比一致。根据当前大流的宽高比，系统会自动分配小流的分辨率、帧率及码率。

    调用本方法的执行结果将在 \ref agora::rtc::IRtcEngineEventHandler::onApiCallExecuted "onApiCallExecuted" 中返回。

    @note 该方法需要在加入频道后调用。如果既调用了 `setRemoteVideoStreamType`，也调用了
    \ref IChannel::setRemoteDefaultVideoStreamType "setRemoteDefaultVideoStreamType"，则 SDK
    以 `setRemoteVideoStreamType` 中的设置为准。

    @param userId 用户 ID。
    @param streamType 视频流类型: #REMOTE_VIDEO_STREAM_TYPE 。

    @return
    - 0: 方法调用成功
    - < 0: 方法调用失败
    */
   /** @~english
    Sets the stream type of the remote video.

    Under limited network conditions, if the publisher has not disabled the dual-stream mode using
    \ref AgoraRtcEngine::enableDualStreamMode "enableDualStreamMode" (false),
    the receiver can choose to receive either the high-quality video stream (the high resolution, and high bitrate video stream) or
    the low-video stream (the low resolution, and low bitrate video stream).

    By default, users receive the high-quality video stream. Call this method if you want to switch to the low-video stream.
    This method allows the app to adjust the corresponding video stream type based on the size of the video window to
    reduce the bandwidth and resources.

    The aspect ratio of the low-video stream is the same as the high-quality video stream. Once the resolution of the high-quality video
    stream is set, the system automatically sets the resolution, frame rate, and bitrate of the low-video stream.

    The method result returns in the \ref agora::rtc::IRtcEngineEventHandler::onApiCallExecuted "onApiCallExecuted" callback.

    @param userId The ID of the remote user sending the video stream.
    @param streamType  Sets the video-stream type. See #REMOTE_VIDEO_STREAM_TYPE.
    @return
    - 0: Success.
    - < 0: Failure.
    */
   int setRemoteVideoStreamType( agora::rtc::uid_t userId, agora::rtc::REMOTE_VIDEO_STREAM_TYPE streamType );

   /** @~chinese
    设置默认订阅的视频流类型。

    在网络条件受限的情况下，如果发送端没有调用 \ref agora::rtc::IRtcEngine::enableDualStreamMode "enableDualStreamMode" (false) 关闭双流模式，
    接收端可以选择接收大流还是小流。其中，大流可以接为高分辨率高码率的视频流， 小流则是低分辨率低码率的视频流。

    正常情况下，用户默认接收大流。如需默认接收所有用户的视频小流，可以调用本方法进行切换。SDK 会根据视频窗口的大小动态调整对应视频流的大小，以节约带宽和计算资源。视频小流默认
    的宽高比和视频大流的宽高比一致。根据当前大流的宽高比，系统会自动分配小流的分辨率、帧率及码率。

    调用本方法的执行结果将在 \ref agora::rtc::IRtcEngineEventHandler::onApiCallExecuted "onApiCallExecuted" 中返回。

    @note 该方法需要在加入频道后调用。如果既调用了 `setRemoteVideoStreamType`，也调用了
    \ref IChannel::setRemoteDefaultVideoStreamType "setRemoteDefaultVideoStreamType"，则 SDK
    以 `setRemoteVideoStreamType` 中的设置为准。

    @param streamType 视频流类型: #REMOTE_VIDEO_STREAM_TYPE 。

    @return
    - 0: 方法调用成功
    - < 0: 方法调用失败
    */
   /** @~english
    Sets the default stream type of remote videos.

    Under limited network conditions, if the publisher has not disabled the dual-stream mode using
    \ref AgoraRtcEngine::enableDualStreamMode "enableDualStreamMode" (false),
    the receiver can choose to receive either the high-quality video stream (the high resolution, and high bitrate video stream) or
    the low-video stream (the low resolution, and low bitrate video stream).

    By default, users receive the high-quality video stream. Call this method if you want to switch to the low-video stream.
    This method allows the app to adjust the corresponding video stream type based on the size of the video window to
    reduce the bandwidth and resources. The aspect ratio of the low-video stream is the same as the high-quality video stream.
    Once the resolution of the high-quality video stream is set, the system automatically sets the resolution, frame rate, and bitrate of the low-video stream.

    The method result returns in the \ref agora::rtc::IRtcEngineEventHandler::onApiCallExecuted "onApiCallExecuted" callback.

    @param streamType Sets the default video-stream type. See #REMOTE_VIDEO_STREAM_TYPE.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int setRemoteDefaultVideoStreamType( agora::rtc::REMOTE_VIDEO_STREAM_TYPE streamType );

   /** @~chinese
    创建数据流。

    该方法用于创建数据流。RtcEngine 生命周期内，每个用户最多只能创建 5 个数据流。频道内数据通道最多允许数据延迟 5 秒，若超过 5 秒接收方尚未收到数据流，则数据通道会向 App 报错。

    @note
    - 将 reliable 和 ordered 同时设为 true 或 false。不要一个设为 true 另一个设为 false。
    - 该方法需要在加入频道后调用。

    @param[out] streamId 数据流 ID。
    @param reliable
    - true: 接收方 5 秒内会收到发送方所发送的数据，否则会收到 \ref agora::rtc::IChannelEventHandler::onStreamMessageError "onStreamMessageError" 回调获得相应报错信息。
    - false: 接收方不保证收到，就算数据丢失也不会报错。
    @param ordered
    - true: 接收方 5 秒内会按照发送方发送的顺序收到数据包；
    - false: 接收方不保证按照发送方发送的顺序收到数据包。

    @return
    - 0: 创建数据流成功。
    - < 0: 创建数据流失败。
    */
   /** @~english
    Creates a data stream.

    Each user can create up to five data streams during the lifecycle of the AgoraRtcChannel.

    @note Set both the `reliable` and `ordered` parameters to `true` or `false`. Do not set one as `true` and the other as `false`.

    @param streamId The ID of the created data stream.
    @param reliable Sets whether or not the recipients are guaranteed to receive the data stream from the sender within five seconds:
    - true: The recipients receive the data stream from the sender within five seconds. If the recipient does not receive the data stream within five seconds,
    an error is reported to the application.
    - false: There is no guarantee that the recipients receive the data stream within five seconds and no error message is reported for
    any delay or missing data stream.
    @param ordered Sets whether or not the recipients receive the data stream in the sent order:
    - true: The recipients receive the data stream in the sent order.
    - false: The recipients do not receive the data stream in the sent order.

    @return
    - Returns 0: Success.
    - < 0: Failure.
    */
   int createDataStream( int* streamId, bool reliable, bool ordered );

   /** @~chinese
    发送数据流。

    该方法发送数据流消息到频道内所有用户。SDK 对该方法的实现进行了如下限制：频道内每秒最多能发送 30 个包，且每个包最大为 1 KB。 API 须对数据通道的传送速率进行控制: 每个客户端每秒最多能发送 6 KB 数据。频道内每人最多能同时有 5 个数据通道。
    成功调用该方法后，远端会触发 \ref agora::rtc::IChannelEventHandler::onStreamMessage "onStreamMessage" 回调，远端用户可以在该回调中获取接收到的流消息；若调用失败，远端会触发 \ref agora::rtc::IChannelEventHandler::onStreamMessageError "onStreamMessageError" 回调。
    @note 该方法仅适用于通信场景以及直播场景下的主播用户，如果直播场景下的观众调用此方法可能会造成观众变主播。

    @param  streamId  由 \ref agora::rtc::IChannel::createDataStream "createDataStream" 返回的数据流 ID。
    @param data 自定义数据。
    @param length 数据长度。

    @return
    - 0: 方法调用成功
    - < 0: 方法调用失败
    */
   /** @~english
    Sends data stream messages to all users in a channel.

    The SDK has the following restrictions on this method:
    - Up to 30 packets can be sent per second in a channel with each packet having a maximum size of 1 kB.
    - Each client can send up to 6 kB of data per second.
    - Each user can have up to five data streams simultaneously.

    A successful `sendStreamMessage` method call triggers
    the \ref agora::rtc::IChannelEventHandler::onStreamMessage "onStreamMessage" callback on the remote client, from which the remote user gets the stream message.

    A failed `sendStreamMessage` method call triggers
    the \ref agora::rtc::IChannelEventHandler::onStreamMessageError "onStreamMessageError" callback on the remote client.

    @note
    - This method applies only to the Communication profile or to the hosts in the Live-broadcast profile. If an audience in the Live-broadcast profile calls this method, the audience may be switched to a host.
    - Ensure that you have created the data stream using \ref createDataStream before calling this method.

    @param streamId  The ID of the sent data stream, returned in the \ref createDataStream method.
    @param data The sent data.
    @param length The length of the sent data.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int sendStreamMessage( int streamId, const char* data, size_t length );

   /** @~chinese
    增加旁路推流地址。

    调用该方法后，你可以向 CDN 推送 RTMP 或 RTMPS 协议的媒体流。SDK 会在本地触发 \ref agora::rtc::IChannelEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" 回调，报告增加旁路推流地址的状态。

    @note
    - 请确保在成功加入频道后才能调用该接口。
    - 请确保已开通旁路推流的功能，详见进阶功能《推流到 CDN》中的前提条件。
    - 该方法每次只能增加一路旁路推流地址。若需推送多路流，则需多次调用该方法。
    - 该方法仅适用于直播场景。
    - Agora 目前仅支持转码时向 CDN 推送 RTMPS 协议的媒体流。

    @param url CDN 推流地址，格式为 RTMP。该字符长度不能超过 1024 字节。url 不支持中文字符等特殊字符。
    @param  transcodingEnabled
    - true: 转码（ [转码]( https://docs.agora.io/cn/Agora%20Platform/terms?platform=All%20Platforms#转码) 是指在旁路推流时对音视频流进行转码处理后再推送到其他 CDN 服务器。多适用于频道内有多个主播，需要进行混流、合图的场景）。如果设为 `true`，需先调用 \ref agora::rtc::IChannel::setLiveTranscoding "setLiveTranscoding" 方法。
    - false: 不转码。

    @return
    - 0: 方法调用成功
    - < 0: 方法调用失败
      - #ERR_INVALID_ARGUMENT (2): URL 为空或是长度为 0 的的字符串
      - #ERR_NOT_INITIALIZED (7): 推流时未初始化引擎
    */
   /** @~english
    Publishes the local stream to a specified CDN live RTMP address.  (CDN live only.)

    The \ref addPublishStreamUrl method call triggers the \ref agora::rtc::IChannelEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" callback
    on the local client to report the state of adding a local stream to the CDN.

    @note
    - Ensure that the user joins the channel before calling this method.
    - Ensure that you enable the RTMP Converter service before using this function. See Prerequisites in the advanced guide *Push Streams to CDN*.
    - This method adds only one stream RTMP URL address each time it is called.

    @param  url The CDN streaming URL in the RTMP format. The maximum length of this parameter is 1024 bytes. The RTMP URL address must not contain special characters, such as Chinese language characters.
    @param  transcodingEnabled Sets whether transcoding is enabled/disabled:
    - true: Enable transcoding. To [transcode](https://docs.agora.io/en/Agora%20Platform/terms?platform=All%20Platforms#transcoding) the audio or video streams when publishing them to CDN live, often used for combining the audio and video streams of multiple hosts in CDN live. If you set this parameter as `true`, ensure that you call the \ref setLiveTranscoding method before this method.
    - false: Disable transcoding.

    @return
    - 0: Success.
    - < 0: Failure.
         - #ERR_INVALID_ARGUMENT (2): The RTMP URL address is NULL or has a string length of 0.
         - #ERR_NOT_INITIALIZED (7): You have not initialized `AgoraRtcChannel` when publishing the stream.
    */
   int addPublishStreamUrl( const char *url, bool transcodingEnabled );

   /** @~chinese
    删除旁路推流地址。

    调用该方法后，SDK 会在本地触发 \ref agora::rtc::IChannelEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" 回调，报告删除旁路推流地址的状态。
    @note
    - 该方法每次只能删除一路旁路推流地址。若需删除多路流，则需多次调用该方法。
    - URL 不支持中文等特殊字符。
    - 该方法仅适用于直播场景。

    @param url 待删除的旁路推流地址，格式为 RTMP。该字符长度不能超过 1024 字节。
    @return
    - 0: 方法调用成功
    - < 0: 方法调用失败
    */
   /** @~english
    Removes an RTMP stream from the CDN.

    This method removes the RTMP URL address (added by the \ref addPublishStreamUrl method) from a CDN live stream.

    The `removePublishStreamUrl` method call triggers
    the \ref agora::rtc::IChannelEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" callback on the local client to report the state of removing an RTMP stream from the CDN.

    @note
    - This method removes only one RTMP URL address each time it is called.
    - The RTMP URL address must not contain special characters, such as Chinese language characters.

    @param url The RTMP URL address to be removed. The maximum length of this parameter is 1024 bytes.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int removePublishStreamUrl( const char *url );

   /** @~chinese
    设置直播推流转码。

    该方法用于旁路推流的视图布局及音频设置等。调用该方法更新转码设置后本地会触发 \ref agora::rtc::IChannelEventHandler::onTranscodingUpdated "onTranscodingUpdated" 回调。

    @note
    - 该方法仅适用于直播场景。
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
    Sets the video layout and audio settings for CDN live. (CDN live only.)

    The SDK triggers the \ref agora::rtc::IChannelEventHandler::onTranscodingUpdated "onTranscodingUpdated" callback when you
    call the `setLiveTranscoding` method to update the transcoding setting.

    @note
    - Ensure that you enable the RTMP Converter service before using this function. See Prerequisites in the advanced guide *Push Streams to CDN*..
    - If you call the `setLiveTranscoding` method to set the transcoding setting for the first time, the SDK does not trigger the `onTranscodingUpdated` callback.

    @param transcoding Sets the CDN live audio/video transcoding settings. See LiveTranscoding.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int setLiveTranscoding( const agora::rtc::LiveTranscoding &transcoding );


   /** @~chinese
    输入在线媒体流。

    @note
    - 请确保已开通旁路推流的功能，详见进阶功能《推流到 CDN》中的前提条件。
    - 该方法适用于 Native SDK v2.4.1 及之后的版本。
    - 该方法仅适用于直播场景中的主播用户。
    - 频道内同一时间只允许输入一个在线媒体流。
    - 该方法需要在加入频道后调用。

    该方法将正在播放的音视频作为音视频源导入到正在进行的直播中。可主要应用于赛事直播、多人看视频互动等直播场景。调用该方法后，SDK 会在本地触发 \ref agora::rtc::IChannelEventHandler::onStreamInjectedStatus "onStreamInjectedStatus" 回调，报告输入在线媒体流的状态；成功输入媒体流后，该音视频流会出现在频道中，频道内所有用户都会收到 \ref agora::rtc::IChannelEventHandler::onUserJoined "onUserJoined" 回调，其中 uid 为 666。该音视频流会出现在频道中。

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
      - #ERR_NOT_INITIALIZED (7): 引擎没有初始化。请确认调用该方法前已创建 IChannel 对象并完成初始化。
    */
   /** @~english
    Adds a voice or video stream URL address to a live broadcast.

    If this method call is successful, the server pulls the voice or video stream and injects it into a live channel.
    This is applicable to scenarios where all audience members in the channel can watch a live show and interact with each other.

    The addInjectStreamUrl method call triggers the following callbacks:
    - The local client:
      - \ref agora::rtc::IChannelEventHandler::onStreamInjectedStatus "onStreamInjectedStatus", with the state of the injecting the online stream.
      - \ref agora::rtc::IChannelEventHandler::onUserJoined "onUserJoined" (uid: 666), if the method call is successful and the online media stream is injected into the channel.
    - The remote client:
      - \ref agora::rtc::IChannelEventHandler::onUserJoined "onUserJoined" (uid: 666), if the method call is successful and the online media stream is injected into the channel.

    @note
    - Ensure that you enable the RTMP Converter service before using this function. See Prerequisites in the advanced guide *Push Streams to CDN*.
    - This method applies to the Native SDK v2.4.1 and later.
    - This method applies to the Live-Broadcast profile only.
    - You can inject only one media stream into the channel at the same time.

    @param url The URL address to be added to the ongoing live broadcast. Valid protocols are RTMP, HLS, and HTTP-FLV.
    - Supported audio codec type: AAC.
    - Supported video codec type: H264 (AVC).
    @param config The InjectStreamConfig object that contains the configuration of the added voice or video stream.

    @return
    - 0: Success.
    - < 0: Failure.
       - #ERR_INVALID_ARGUMENT (2): The injected URL does not exist. Call this method again to inject the stream and ensure that the URL is valid.
       - #ERR_NOT_READY (3): The user is not in the channel.
       - #ERR_NOT_SUPPORTED (4): The channel profile is not live broadcast. Call the \ref AgoraRtcEngine::setChannelProfile "setChannelProfile" method and set the channel profile to live broadcast before calling this method.
       - #ERR_NOT_INITIALIZED (7): The SDK is not initialized. Ensure that the AgoraRtcChannel object is initialized before calling this method.
    */
   int addInjectStreamUrl( const char* url, const agora::rtc::InjectStreamConfig& config );

   /** @~chinese
    删除导入的外部媒体流。

    @note 成功删除外部视频源 URL 地址后会触发 \ref agora::rtc::IChannelEventHandler::onUserOffline "onUserOffline" 回调，uid 为 666。

    @param url 已导入、待删除的外部视频源 URL 地址。
    @return
    - 0: 方法调用成功
    - < 0: 方法调用失败
    */
    /** @~english
    Removes the voice or video stream URL address from a live broadcast.

    This method removes the URL address (added by the \ref addInjectStreamUrl method) from the live broadcast.

    @note If this method is called successfully, the SDK triggers the \ref agora::rtc::IChannelEventHandler::onUserOffline "onUserOffline" callback and returns a stream uid of 666.

    @param url Pointer to the URL address of the added stream to be removed.

    @return
    - 0: Success.
    - < 0: Failure.
    */
   int removeInjectStreamUrl( const char* url );

   /** @~chinese
    * 开始跨频道媒体流转发。该方法可用于实现跨频道连麦等场景。
    *
    * 成功调用该方法后，SDK 会触发
    * \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayStateChanged
    *  "onChannelMediaRelayStateChanged" 和
    * \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayEvent
    * "onChannelMediaRelayEvent" 回调，并在回调中报告当前的跨频道媒体流转发状态和事件。
    * - 如果
    * \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayStateChanged
    *  "onChannelMediaRelayStateChanged" 回调报告 #RELAY_STATE_RUNNING (2) 和
    * #RELAY_OK (0)，且
    * \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayEvent
    * "onChannelMediaRelayEvent" 回调报告
    * #RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL (4)，
    * 则表示 SDK 开始在源频道和目标频道之间转发媒体流。
    * - 如果
    * \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayStateChanged
    *  "onChannelMediaRelayStateChanged" 回调报告 #RELAY_STATE_FAILURE (3)，
    * 则表示跨频道媒体流转发出现异常。
    *
    * @note
    * - 请在成功加入频道后调用该方法。
    * - 该方法仅对直播场景下的主播有效。
    * - 成功调用该方法后，若你想再次调用该方法，必须先调用
    * \ref stopChannelMediaRelay() "stopChannelMediaRelay"
    * 方法退出当前的转发状态。
    * - 跨频道媒体流转发功能需要[提交工单](https://agora-ticket.agora.io/)联系技术支持开通。
    * - 该功能不支持 String 型 UID。
    *
    * @param configuration 跨频道媒体流转发参数配置。详见
    * ChannelMediaRelayConfiguration。
    *
    * @return
    * - 0：方法调用成功。
    * - < 0：方法调用失败
    */
   /** @~english
     Starts to relay media streams across channels.

     After a successful method call, the SDK triggers the \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayStateChanged "onChannelMediaRelayStateChanged"
     and \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayEvent "onChannelMediaRelayEvent" callbacks, and these callbacks return the state and events of the media stream relay.
    - If the \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayStateChanged "onChannelMediaRelayStateChanged" callback returns #RELAY_STATE_RUNNING (2) and #RELAY_OK (0), and the \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayEvent "onChanenlMediaRelayEvent" callback 
    returns #RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL (4), the broadcaster starts sending data to the destination channel.
     - If the \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayStateChanged "onChannelMediaRelayStateChanged" callback returns #RELAY_STATE_FAILURE (3), an exception occurs during the media stream relay.

     @note
     - Call this method after the \ref joinChannel method.
     - This method takes effect only when you are a broadcaster in a Live-broadcast channel.
     - After a successful method call, if you want to call this method again, ensure that you call the \ref stopChannelMediaRelay method to quit the current relay.
     - Contact sales-us@agora.io before implementing this function.
     - We do not support string user accounts in this API.

     @param configuration The configuration of the media stream relay:
     ChannelMediaRelayConfiguration.

     @return
     - 0: Success.
     - < 0: Failure.
    */
   int startChannelMediaRelay( const agora::rtc::ChannelMediaRelayConfiguration &configuration );

   /** @~chinese
    * 更新媒体流转发的频道。
    *
    * 成功开始跨频道转发媒体流后，如果你希望将流转发到多个目标频道，
    * 或退出当前的转发频道，可以调用该方法。
    *
    * 成功调用该方法后，SDK 会触发
    * \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayEvent
    * "onChannelMediaRelayEvent" 回调，
    * 并在回调中报告状态码 #RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL (7)。
    *
    * @note
    * 请在 \ref startChannelMediaRelay() "startChannelMediaRelay"
    * 方法后调用该方法，更新媒体流转发的频道。
    *
    * @param configuration 跨频道媒体流转发参数配置。详见
    * ChannelMediaRelayConfiguration。
    *
    * @return
    * - 0：方法调用成功。
    * - < 0：方法调用失败
    */
   /** @~english
     Updates the channels for media stream relay.

     After a successful \ref startChannelMediaRelay method call, if you want to relay the media stream to more channels, or leave the current relay channel, 
     you can call the \ref updateChannelMediaRelay method.

     After a successful method call, the SDK triggers the \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayEvent "onChannelMediaRelayEvent" callback with the #RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL (7) state code.

     @note
     Call this method after the \ref startChannelMediaRelay method to update the destination channel.\

     @param configuration The media stream relay configuration: \ref ChannelMediaRelayConfiguration.

     @return
     - 0: Success.
     - < 0: Failure.
    */
   int updateChannelMediaRelay( const agora::rtc::ChannelMediaRelayConfiguration &configuration );

   /** @~chinese
    停止跨频道媒体流转发。一旦停止，主播会退出所有目标频道。
    *
    * 成功调用该方法后，SDK 会触发
    * \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayStateChanged
    * "onChannelMediaRelayStateChanged" 回调。如果报告 #RELAY_STATE_IDLE (0)
    * 和 #RELAY_OK (0)，则表示已停止转发媒体流。
    *
    * @note
    * 如果该方法调用不成功，SDK 会触发
    * \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayStateChanged
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
     Stops the media stream relay.

     Once the relay stops, the broadcaster quits all the destination channels.

     After a successful method call, the SDK triggers the \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayStateChanged "onChannelMediaRelayStateChanged" callback. If the callback returns #RELAY_STATE_IDLE (0) and #RELAY_OK (0),
     the broadcaster successfully stops the relay.

     @note
     If the method call fails, the SDK triggers the \ref agora::rtc::IChannelEventHandler::onChannelMediaRelayStateChanged "onChannelMediaRelayStateChanged" callback with the #RELAY_ERROR_SERVER_NO_RESPONSE (2) or
     #RELAY_ERROR_SERVER_CONNECTION_LOST (8) state code. You can leave the channel by calling the \ref leaveChannel method, and the media stream relay automatically stops.

     @return
     - 0: Success.
     - < 0: Failure.
    */
   int stopChannelMediaRelay();

   /** @~chinese
    * 获取 SDK 当前的连接状态。
    * @return SDK 连接状态：#CONNECTION_STATE_TYPE。
    */
   /** @~english
    Gets the current connection state of the SDK.

    @return #CONNECTION_STATE_TYPE.
    */
   agora::rtc::CONNECTION_STATE_TYPE getConnectionState();

private:
   int release();

private:
   AgoraRtcChannel( agora::rtc::IChannel* rtcChannel );

private:
   agora::rtc::IChannel* m_rtcChannel = nullptr;
};

}
}
}
