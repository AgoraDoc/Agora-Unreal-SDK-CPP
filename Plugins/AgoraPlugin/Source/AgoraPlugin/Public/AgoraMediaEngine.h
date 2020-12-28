//  Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif


#if (defined(__APPLE__) && TARGET_OS_IPHONE)
#include <Agora/iOS/Include/AgoraBase.h>
#include <Agora/iOS/Include/IAgoraRtcEngine.h>
#include <Agora/iOS/Include/IAgoraMediaEngine.h>
#else
#include <Agora/AgoraBase.h>
#include <Agora/IAgoraRtcEngine.h>
#include <Agora/IAgoraMediaEngine.h>
#endif

#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

namespace agora
{
namespace rtc
{
namespace ue4
{
class AgoraRtcEngine;
}
}
}

namespace agora
{
namespace media
{
namespace ue4
{
/** @~chinese
 * AgoraMediaEngine 类是基于 IMediaEngine 封装的类。
 */
/** @~english
 * Wrapper around agora::media::IMediaEngine.
 */
class AGORAPLUGIN_API AgoraMediaEngine
{
public:
	AgoraMediaEngine() = default;

	AgoraMediaEngine(const AgoraMediaEngine& other) = delete;
	AgoraMediaEngine(AgoraMediaEngine&& other) noexcept = delete;
	AgoraMediaEngine& operator=(const AgoraMediaEngine& other) = delete;
	AgoraMediaEngine& operator=(AgoraMediaEngine&& other) noexcept = delete;

	~AgoraMediaEngine() = default;

   /** @~chinese
   创建 AgoraMediaEngine 对象。
   @param RtcEngine RtcEngine 对象的指针。
   @return
   - 方法调用成功：返回 AgoraMediaEngine 对象的指针。
   - 方法调用失败：返回一个空指针。
   */
   /** @~english
   * @brief          Creates the MediaEngine object
   * @param          RtcEngine
   *                 Pointer to the RtcEngine object.
   * @return
   *                 -  Success: Returns a pointer to the AgoraMediaEngine object.
   *                 -  Failure: Returns nullptr.
   */
	static AgoraMediaEngine* Create(agora::rtc::ue4::AgoraRtcEngine* RtcEngine);
public:

  /** @~chinese
   注册语音观测器对象。

   该方法用于注册语音观测器对象，即注册回调。当需要引擎给出 IAudioFrameObserver 中的回调时，需要使用该方法注册回调。

   @note 该方法需要在加入频道前调用。

   @param observer 接口对象实例。详见 IAudioFrameObserver。如果传入 NULL，则表示取消注册，
   我们建议在收到 \ref agora::rtc::IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel" 后调用，来释放语音观测器对象。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Registers an audio frame observer object.
   * @brief          This method is used to register an audio frame observer object (register a callback).
   *                 This method is required to register callbacks when the engine is required to provide callbacks in IAudioFrameObserver.
   * @param          observer
   *                 Audio frame observer object instance. See IAudioFrameObserver. Set the value as `NULL` to release the
   *                 audio observer object. Agora recommends calling `registerAudioFrameObserver(NULL)` after receiving
   *                 the \ref agora::rtc::IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel" callback.
   * @return
   *                 - 0: Success.
   *                 - < 0: Failure.
   */
	int registerAudioFrameObserver(agora::media::IAudioFrameObserver* observer);

   /** @~chinese
   注册视频观测器对象。
   *
   * 你需要在该方法中实现一个 IVideoFrameObserver 类，并根据场景需要，注册该类的回调。
   * 成功注册视频观测器后，SDK 会在捕捉到每个视频帧时，触发你所注册的上述回调。
   *
   * @note
   * - 在处理回调时，你需要考虑视频帧中 `width` 和 `height` 参数的变化，因为观测得到的视频帧可能会随以下情况变化：
   *    - 当网络状况差时，分辨率会阶梯式下降。
   *    - 当用户自行调整分辨率时，回调中报告的分辨率也会变化。
   * - 该方法需要在加入频道前调用。
   *
   * @param observer 接口对象实例。如果传入 NULL，则取消注册。详见  IVideoFrameObserver。
   * @return
   * - 0: 方法调用成功
   * - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Registers a video frame observer object.
   * @brief          You need to implement the IVideoFrameObserver class in this method, and register callbacks according to your scenarios.
   * @brief          After you successfully register the video frame observer, the SDK triggers the registered callbacks each time a video frame is received.
   *
   * @note
   * - When handling the video data returned in the callbacks, pay attention to the changes in the `width` and `height` parameters,
   * which may be adapted under the following circumstances:
   *  - When the network condition deteriorates, the video resolution decreases incrementally.
   *  - If the user adjusts the video profile, the resolution of the video returned in the callbacks also changes.
   * - Ensure that you call this method before joining a channel.
   * @param          observer
   *                 Video frame observer object instance. If NULL is passed in, the registration is canceled.
   * @return
   *                 - 0: Success.
   *                 - < 0: Failure.
   */
	int registerVideoFrameObserver(agora::media::IVideoFrameObserver* observer);

   
   /** @~chinese
   推送外部音频帧。

   @param frame 音频帧指针。详见： \ref IAudioFrameObserver::AudioFrame "AudioFrame"。
   @return
   - 0：方法调用成功
   - < 0：方法调用失败
   */
   /** @~english
   * @brief          Pushes the external audio frame.
   * @param          frame 
   *                 Pointer to the audio frame: \ref IAudioFrameObserver::AudioFrame "AudioFrame".
   *  @return
   *                 - 0: Success.
   *                 - < 0: Failure.
   */
	int pushAudioFrame(agora::media::IAudioFrameObserver::AudioFrame* frame);

   /** @~chinese
   拉取远端音频数据。

   使用该方法前，你需要调用
   \ref agora::rtc::IRtcEngine::setExternalAudioSink "setExternalAudioSink(enabled: true)" 方法通知 App 开启并设置外部渲染。

   调用该方法后，App 会采取主动拉取的方式获取远端已解码和混音后的音频数据，用于音频播放。

   @note
   - 使用该方法后，App 会无法从
   \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" 回调中获得数据。
   - 该方法和 \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" 回调相比，区别在于：
     - `onPlaybackAudioFrame`：SDK 通过该回调将音频数据传输给 app。如果 app 处理延时，可能会导致音频播放抖动。
   如果 App 处理延时，可能会导致音频播放抖动。
     - `pullAudioFrame`：App 主动拉取音频数据。通过设置音频数据，
   SDK 可以调整缓存，帮助 App 处理延时，从而有效避免音频播放抖动。

   @param frame 指向 \ref agora::media::IAudioFrameObserver::AudioFrame "AudioFrame" 的指针。

   @return
   - 0：方法调用成功。
   - < 0：方法调用失败。
   */
   /** @~english
   * @brief          Pulls the remote audio data.
   * @brief          Before calling this method, call the 
   *                 \ref agora::rtc::IRtcEngine::setExternalAudioSink 
   *                 "setExternalAudioSink(enabled: true)" method to enable and set the 
   *                 external audio sink.
   * @brief          After a successful method call, the app pulls the decoded and mixed 
   *                 audio data for playback.
   * @note
   *                 - Once you call the \ref agora::media::IMediaEngine::pullAudioFrame 
   *                 "pullAudioFrame" method successfully, the app will not retrieve any audio 
   *                 data from the \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame
   *                 "onPlaybackAudioFrame" callback.
   *                 - The difference between the \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame 
   *                 "onPlaybackAudioFrame" callback and the 
   *                 \ref agora::media::IMediaEngine::pullAudioFrame "pullAudioFrame" method is as follows:
   *                  - `onPlaybackAudioFrame`: The SDK sends the audio data to the app once 
   *                 every 10 ms. Any delay in processing the audio frames may result in audio 
   *                 jitter.
   *                  - `pullAudioFrame`: The app pulls the remote audio data. After setting the 
   *                 audio data parameters, the SDK adjusts the frame buffer and avoids 
   *                 problems caused by jitter in the external audio playback.
   * 
   * @param          frame 
   *                 Pointers to the audio frame. 
   *                 See: \ref IAudioFrameObserver::AudioFrame "AudioFrame".
   * 
   * @return
   *                 - 0: Success.
   *                 - < 0: Failure.
   */
	int pullAudioFrame(agora::media::IAudioFrameObserver::AudioFrame* frame);


  /** @~chinese
   配置外部视频源

   @note 该方法需要在加入频道前调用。

   @param enable 是否使用外部视频源：
   - true：使用外部视频源
   - false：（默认）不使用外部视频源
   @param useTexture 是否使用 Texture 作为输入：
   - true：使用 texture 作为输入
   - false：（默认）不使用 texture 作为输入
   @return
   - 0：方法调用成功
   - < 0：方法调用失败
   */
   /** @~english
   * @brief         Configures the external video source.
   * @param         enable 
   *                Sets whether to use the external video source:
   *                - true: Use the external video source.
   *                - false: (Default) Do not use the external video source.
   * @param         useTexture 
   *                Sets whether to use texture as an input:
   *                - true: Use texture as an input.
   *                - false: (Default) Do not use texture as an input.
   * @return
                    - 0: Success.
                    - < 0: Failure.
   */
	int setExternalVideoSource(bool enable, bool useTexture);

   /** @~chinese
   使用 \ref ExternalVideoFrame "ExternalVideoFrame" 将视频帧数据传递给 Agora SDK。

   @note 通信场景下，不支持 Texture 格式的视频帧，只支持非 Texture 格式的视频帧。
   @param frame 待传输的视频帧。详见 \ref ExternalVideoFrame "ExternalVideoFrame"。
   @return
   - 0：方法调用成功
   - < 0：方法调用失败
   */
   /** @~english
   * @brief         Pushes the video frame using the \ref ExternalVideoFrame "ExternalVideoFrame" and passes the video frame to the Agora SDK.
   * @param         frame 
   *                Video frame to be pushed. See \ref ExternalVideoFrame "ExternalVideoFrame".
   * @note          In the Communication profile, this method does not support video frames in the Texture format.
   * @return
   *                - 0: Success.
   *                - < 0: Failure.
   */
	int pushVideoFrame(agora::media::ExternalVideoFrame* frame);

private:
   /** @~chinese
   获取接口。
   @param AgoraEngine AgoraRtcEngine 对象的指针。
   @return
   - true: 方法调用成功
   - false: 方法调用不成功
   */
   /** @~english
    * Queries the AgoraRtcEngine interface.
    * @param AgoraEngine Pointer to the AgoraRtcEngine object.
    * @return
    * - true: Success.
    * - false: Failure.
    */
	bool queryInterface(agora::rtc::ue4::AgoraRtcEngine* AgoraEngine);

   /** @~chinese
   * 释放所有 AgoraMediaEngine 的资源。
   */
   /** @~english
   * @brief         Releases all AgoraMediaEngine resources.
   */
	void release();

private:
	agora::util::AutoPtr<agora::media::IMediaEngine> m_mediaEngine;
};

}
}
}
