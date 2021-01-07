//
//  AgoraRtcEngine SDK
//
//  Copyright (c) 2019 Agora.io. All rights reserved.
//

/**
 @defgroup createAgoraRtcEngine Create an AgoraRtcEngine
 */

#ifndef AGORA_RTC_ENGINE_H
#define AGORA_RTC_ENGINE_H
#include "AgoraBase.h"
#include "IAgoraService.h"

namespace agora {
namespace rtc {
    typedef unsigned int uid_t;
    typedef void* view_t;
/** @~chinese
设备 ID 的最大长度。
*/
/** @~english
Maximum length of the device ID.
*/
enum MAX_DEVICE_ID_LENGTH_TYPE
{
  /** @~chinese
  设备 ID 的最大长度为 512 字。
  */
  /** @~english
  The maximum length of the device ID is 512 bytes.
  */
    MAX_DEVICE_ID_LENGTH = 512
};
/** @~chinese
用户名的最大长度。
*/
/** @~english
Maximum length of user account.
*/
enum MAX_USER_ACCOUNT_LENGTH_TYPE
{
  /** @~chinese
  用户名的最大长度为 255 字。
  */
  /** @~english
  The maximum length of user account is 255 bytes.
  */
  MAX_USER_ACCOUNT_LENGTH = 256
};
/** @~chinese
频道名的最大长度。
*/
/** @~english
Maximum length of channel ID.
 */
enum MAX_CHANNEL_ID_LENGTH_TYPE
{
    /** @~chinese
    频道名的最大长度为 64 字。
    */
    /** @~english
    The maximum length of channel id is 64 bytes.
     */
    MAX_CHANNEL_ID_LENGTH = 65
};
/** @~chinese
质量报告的格式。
*/
/** @~english
Formats of the quality report.
*/
enum QUALITY_REPORT_FORMAT_TYPE
{
  /** @~chinese
  0: 质量报告格式为 JSON。
  */
  /** @~english
  0: The quality report in JSON format,
  */
    QUALITY_REPORT_JSON = 0,
    /** @~chinese
    1: 质量报告格式为 HTML。
    */
    /** @~english
    1: The quality report in HTML format.
    */
    QUALITY_REPORT_HTML = 1,
};

enum MEDIA_ENGINE_EVENT_CODE_TYPE
{
    /** @~chinese
     0: 仅供内部使用。
     */
    /** @~english
     0: For internal use only.
     */
    MEDIA_ENGINE_RECORDING_ERROR = 0,
    /** @~chinese
     1: 仅供内部使用。
     */
    /** @~english
     1: For internal use only.
     */
    MEDIA_ENGINE_PLAYOUT_ERROR = 1,
    /** @~chinese
     2: 仅供内部使用。
     */
    /** @~english
     2: For internal use only.
     */
    MEDIA_ENGINE_RECORDING_WARNING = 2,
    /** @~chinese
     3: 仅供内部使用。
     */
    /** @~english
     3: For internal use only.
     */
    MEDIA_ENGINE_PLAYOUT_WARNING = 3,
    /** @~chinese
     10: 仅供内部使用。
     */
    /** @~english
     10: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_FILE_MIX_FINISH = 10,
    /** @~chinese
     12: 仅供内部使用。
     */    /** @~english
     12: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_FAREND_MUSIC_BEGINS = 12,
    /** @~chinese
     13: 仅供内部使用。
     */
    /** @~english
     13: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_FAREND_MUSIC_ENDS = 13,
    /** @~chinese
     14: 仅供内部使用。
     */
    /** @~english
     14: For internal use only.
     */
    MEDIA_ENGINE_LOCAL_AUDIO_RECORD_ENABLED = 14,
    /** @~chinese
     15: 仅供内部使用。
     */
    /** @~english
     15: For internal use only.
     */
    MEDIA_ENGINE_LOCAL_AUDIO_RECORD_DISABLED = 15,
    // media engine role changed
    /** @~chinese
     20: 仅供内部使用。
     */
    /** @~english
     20: For internal use only.
     */
    MEDIA_ENGINE_ROLE_BROADCASTER_SOLO = 20,
    /** @~chinese
     21: 仅供内部使用。
     */
    /** @~english
     21: For internal use only.
     */
    MEDIA_ENGINE_ROLE_BROADCASTER_INTERACTIVE = 21,
    /** @~chinese
     22: 仅供内部使用。
     */
    /** @~english
     22: For internal use only.
     */
    MEDIA_ENGINE_ROLE_AUDIENCE = 22,
    /** @~chinese
     23: 仅供内部使用。
     */
    /** @~english
     23: For internal use only.
     */
    MEDIA_ENGINE_ROLE_COMM_PEER = 23,
    /** @~chinese
     24: 仅供内部使用。
     */
    /** @~english
     24: For internal use only.
     */
    MEDIA_ENGINE_ROLE_GAME_PEER = 24,
    // iOS adm sample rate changed
    /** @~chinese
     110: 仅供内部使用。
     */
    /** @~english
     110: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_ADM_REQUIRE_RESTART = 110,
    /** @~chinese
     111: 仅供内部使用。
     */
    /** @~english
     111: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_ADM_SPECIAL_RESTART = 111,
    /** @~chinese
     112: 仅供内部使用。
     */
    /** @~english
     112: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_ADM_USING_COMM_PARAMS = 112,
    /** @~chinese
     113: 仅供内部使用。
     */
    /** @~english
     113: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_ADM_USING_NORM_PARAMS = 113,
    // audio mix state
    /** @~chinese
     710: 仅供内部使用。
     */
    /** @~english
     710: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_EVENT_MIXING_PLAY = 710,
    /** @~chinese
     711: 仅供内部使用。
     */
    /** @~english
     711: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_EVENT_MIXING_PAUSED = 711,
    /** @~chinese
     712: 仅供内部使用。
     */
    /** @~english
     712: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_EVENT_MIXING_RESTART         = 712,
    /** @~chinese
     713: 仅供内部使用。
     */
    /** @~english
     713: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_EVENT_MIXING_STOPPED = 713,
    /** @~chinese
     714: 仅供内部使用。
     */
    /** @~english
     714: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_EVENT_MIXING_ERROR = 714,
    //Mixing error codes
    /** @~chinese
     701: 仅供内部使用。
     */
    /** @~english
     701: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_ERROR_MIXING_OPEN = 701,
    /** @~chinese
     702: 仅供内部使用。
     */
    /** @~english
     702: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_ERROR_MIXING_TOO_FREQUENT = 702,
    /** @~chinese
     703: 仅供内部使用。
     */
    /** @~english
     703: The audio mixing file playback is interrupted. For internal use only.
     */
    MEDIA_ENGINE_AUDIO_ERROR_MIXING_INTERRUPTED_EOF = 703,
    /** @~chinese
     0: 仅供内部使用。
     */
    /** @~english
     0: For internal use only.
     */
    MEDIA_ENGINE_AUDIO_ERROR_MIXING_NO_ERROR = 0,
};

/** @~chinese
本地用户的音乐文件播放状态。
*/
/** @~english
The states of the local user's audio mixing file.
*/
enum AUDIO_MIXING_STATE_TYPE{
    /** @~chinese
    710: 音乐文件正常播放。
    */
    /** @~english
    710: The audio mixing file is playing.
    */
    AUDIO_MIXING_STATE_PLAYING = 710,
    /** @~chinese
    711: 音乐文件暂停播放。
    */
    /** @~english
    711: The audio mixing file pauses playing.
    */
    AUDIO_MIXING_STATE_PAUSED = 711,
    /** @~chinese
    713: 音乐文件停止播放。
    */
    /** @~english
    713: The audio mixing file stops playing.
    */
    AUDIO_MIXING_STATE_STOPPED = 713,
    /** @~chinese
    714: 音乐文件播放失败。
    错误类型详见 #AUDIO_MIXING_ERROR_TYPE
    */
    /** @~english
    714: An exception occurs when playing the audio mixing file. See #AUDIO_MIXING_ERROR_TYPE.
    */
    AUDIO_MIXING_STATE_FAILED = 714,
};

/** @~chinese
混音音乐文件错误码。
*/
/** @~english
The error codes of the local user's audio mixing file.
*/
enum AUDIO_MIXING_ERROR_TYPE{
    /** @~chinese
    701: 音乐文件无法打开。
    */
    /** @~english
    701: The SDK cannot open the audio mixing file.
    */
    AUDIO_MIXING_ERROR_CAN_NOT_OPEN = 701,
    /** @~chinese
    702: 音乐文件打开太频繁。
    */
    /** @~english
    702: The SDK opens the audio mixing file too frequently.
    */
    AUDIO_MIXING_ERROR_TOO_FREQUENT_CALL = 702,
    /** @~chinese
    703: 音乐文件播放中断。
    */
    /** @~english
    703: The audio mixing file playback is interrupted.
     */
    AUDIO_MIXING_ERROR_INTERRUPTED_EOF = 703,
    /** @~chinese
    0: 音乐文件正常打开。
    */
    /** @~english
    0: The SDK can open the audio mixing file.
    */
    AUDIO_MIXING_ERROR_OK = 0,
};

/** @~chinese
媒体设备的状态。
*/
/** @~english
Media device states.
 */
enum MEDIA_DEVICE_STATE_TYPE
{
  /** @~chinese
  1: 设备正在使用。
  */
  /** @~english
  1: The device is active.
  */
    MEDIA_DEVICE_STATE_ACTIVE = 1,
    /** @~chinese
    2: 设备被禁用。
    */
    /** @~english
    2: The device is disabled.
    */
    MEDIA_DEVICE_STATE_DISABLED = 2,
    /** @~chinese
    4: 设备不存在。
    */
    /** @~english
    4: The device is not present.
    */
    MEDIA_DEVICE_STATE_NOT_PRESENT = 4,
    /** @~chinese
    8: 设备被拔出。
    */
    /** @~english
    8: The device is unplugged.
    */
    MEDIA_DEVICE_STATE_UNPLUGGED = 8
};

/** @~chinese
媒体设备的类型。
*/
/** @~english
Media device types.
 */
enum MEDIA_DEVICE_TYPE
{
  /** @~chinese
  -1: 未知的设备类型。
  */
  /** @~english
  -1: Unknown device type.
  */
    UNKNOWN_AUDIO_DEVICE = -1,
    /** @~chinese
    0: 音频播放设备。
    */
    /** @~english
    0: Audio playback device.
    */
    AUDIO_PLAYOUT_DEVICE = 0,
    /** @~chinese
    1: 音频采集设备。
    */
    /** @~english
    1: Audio recording device.
    */
    AUDIO_RECORDING_DEVICE = 1,
    /** @~chinese
    2: 视频渲染设备。
    */
    /** @~english
    2: Video renderer.
    */
    VIDEO_RENDER_DEVICE = 2,
    /** @~chinese
    3: 视频采集设备。
    */
    /** @~english
    3: Video capturer.
    */
    VIDEO_CAPTURE_DEVICE = 3,
    /** @~chinese
    4: 音频应用播放设备。
    */
    /** @~english
    4: Application audio playback device.
    */
    AUDIO_APPLICATION_PLAYOUT_DEVICE = 4,
};

/** @~chinese
本地视频状态。
*/
/** @~english
Local video state types
 */
enum LOCAL_VIDEO_STREAM_STATE
{
    /** @~chinese
    0: 初始状态。
    */
    /** @~english
    Initial state
    */
    LOCAL_VIDEO_STREAM_STATE_STOPPED = 0,
    /** @~chinese
    1: 本地视频采集设备成功启动。
    */
    /** @~english
    The capturer starts successfully.
    */
    LOCAL_VIDEO_STREAM_STATE_CAPTURING = 1,
    /** @~chinese
    2: 本地视频首帧编码成功。
    */
    /** @~english
    The first video frame is successfully encoded.
    */
    LOCAL_VIDEO_STREAM_STATE_ENCODING = 2,
    /** @~chinese
    3: 本地视频启动失败。
    */
    /** @~english
    The local video fails to start.
    */
    LOCAL_VIDEO_STREAM_STATE_FAILED = 3
};

/** @~chinese
本地视频出错原因。
*/
/** @~english
Local video state error codes
 */
enum LOCAL_VIDEO_STREAM_ERROR {
    /** @~chinese
    0: 本地视频状态正常。
    */
    /** @~english
    The local video is normal.
    */
    LOCAL_VIDEO_STREAM_ERROR_OK = 0,
    /** @~chinese
    1: 没有明确的出错原因。
    */
    /** @~english
    No specified reason for the local video failure.
    */
    LOCAL_VIDEO_STREAM_ERROR_FAILURE = 1,
    /** @~chinese
    2: 没有权限使用本地视频采集设备。
    */
    /** @~english
    No permission to use the local video capturing device.
    */
    LOCAL_VIDEO_STREAM_ERROR_DEVICE_NO_PERMISSION = 2,
    /** @~chinese
    3: 本地视频采集设备正在使用中。
    */
    /** @~english
    The local video capturing device is in use.
    */
    LOCAL_VIDEO_STREAM_ERROR_DEVICE_BUSY = 3,
    /** @~chinese
    4: 本地视频采集失败，建议检查采集设备是否正常工作。
    */
    /** @~english
    The local video capture fails. Check whether the capturing device is working properly.
    */
    LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE = 4,
    /** @~chinese
    5: 本地视频编码失败。
    */
    /** @~english
    The local video encoding fails.
    */
    LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE = 5
};

/** @~chinese
本地音频状态
*/
/** @~english
Local audio state types.
 */
enum LOCAL_AUDIO_STREAM_STATE
{
    /** @~chinese
    0: 初始状态。
    */
    /** @~english
    0: The local audio is in the initial state.
     */
    LOCAL_AUDIO_STREAM_STATE_STOPPED = 0,
    /** @~chinese
    1: 本地音频采集设备成功启动。
    */
    /** @~english
    1: The recording device starts successfully.
     */
    LOCAL_AUDIO_STREAM_STATE_RECORDING = 1,
    /** @~chinese
    2: 本地音频首帧编码成功。
    */
    /** @~english
    2: The first audio frame encodes successfully.
     */
    LOCAL_AUDIO_STREAM_STATE_ENCODING = 2,
    /** @~chinese
    3: 本地音频启动失败。
    */
    /** @~english
    3: The local audio fails to start.
     */
    LOCAL_AUDIO_STREAM_STATE_FAILED = 3
};

/** @~chinese
本地音频出错原因。
*/
/** @~english
Local audio state error codes.
 */
enum LOCAL_AUDIO_STREAM_ERROR
{
    /** @~chinese
    0: 本地音频状态正常。
    */
    /** @~english
    0: The local audio is normal.
     */
    LOCAL_AUDIO_STREAM_ERROR_OK = 0,
    /** @~chinese
    1: 没有明确的出错原因。
    */
    /** @~english
    1: No specified reason for the local audio failure.
     */
    LOCAL_AUDIO_STREAM_ERROR_FAILURE = 1,
    /** @~chinese
    2: 没有权限使用本地音频采集设备。
    */
    /** @~english
    2: No permission to use the local audio device.
     */
    LOCAL_AUDIO_STREAM_ERROR_DEVICE_NO_PERMISSION = 2,
    /** @~chinese
    3: 本地音频采集设备正在使用中。
    */
    /** @~english
    3: The microphone is in use.
     */
    LOCAL_AUDIO_STREAM_ERROR_DEVICE_BUSY = 3,
    /** @~chinese
    4: 本地音频采集失败，建议检查采集设备是否正常工作。
    */
    /** @~english
     * 4: The local audio recording fails. Check whether the recording device
     * is working properly.
     */
    LOCAL_AUDIO_STREAM_ERROR_RECORD_FAILURE = 4,
    /** @~chinese
    5: 本地音频编码失败。
    */
    /** @~english
    5: The local audio encoding fails.
     */
    LOCAL_AUDIO_STREAM_ERROR_ENCODE_FAILURE = 5
};

/** @~chinese
音频采集的音质。
*/
/** @~english
Audio recording qualities.
*/
enum AUDIO_RECORDING_QUALITY_TYPE
{
    /** @~chinese
    0: 低音质。采样率为 32 kHz，录制 10 分钟的文件大小为 1.2 M 左右。
    */
    /** @~english
    * 0: Low quality. The sample rate is 32 kHz, and the file size is around
    * 1.2 MB after 10 minutes of recording.
    */
    AUDIO_RECORDING_QUALITY_LOW = 0,
    /** @~chinese
    1: 中音质。采样率为 32 kHz，录制 10 分钟的文件大小为 2 M 左右。
    */
    /** @~english
    * 1: Medium quality. The sample rate is 32 kHz, and the file size is
    * around 2 MB after 10 minutes of recording.
    */
    AUDIO_RECORDING_QUALITY_MEDIUM = 1,
    /** @~chinese
    2: 高音质。采样率为 32 kHz，录制 10 分钟的文件大小为 3.75 M 左右。
    */
    /** @~english
    2: High quality. The sample rate is 32 kHz, and the file size is
    * around 3.75 MB after 10 minutes of recording.
    */
    AUDIO_RECORDING_QUALITY_HIGH = 2,
};

/** @~chinese
网络质量。
*/
/** @~english
Network quality types. */
enum QUALITY_TYPE
{
    /** @~chinese
    0: 网络质量未知。
    */
    /** @~english
    0: The network quality is unknown.
    */
    QUALITY_UNKNOWN = 0,
    /** @~chinese
    1: 网络质量极好。
    */
    /**  @~english
    1: The network quality is excellent.
    */
    QUALITY_EXCELLENT = 1,
    /** @~chinese
    2: 用户主观感觉和 excellent 差不多，但码率可能略低于 excellent。
    */
    /** @~english
    2: The network quality is quite good, but the bitrate may be slightly lower than excellent.
    */
    QUALITY_GOOD = 2,
    /** @~chinese
    3: 用户主观感受有瑕疵但不影响沟通。
    */
    /** @~english
    3: Users can feel the communication slightly impaired.
    */
    QUALITY_POOR = 3,
    /** @~chinese
    4: 用户勉强能沟通但不顺畅。
    */
    /** @~english
    4: Users cannot communicate smoothly.
    */
    QUALITY_BAD = 4,
    /** @~chinese
    5: 网络质量非常差，基本不能沟通。
    */
    /** @~english
    5: The network is so bad that users can barely communicate.
    */
    QUALITY_VBAD = 5,
    /** @~chinese
    6: 用户完全无法沟通。
    */
    /** @~english
    6: The network is down and users cannot communicate at all. */
    QUALITY_DOWN = 6,
    /** @~chinese
    7: 暂时无法检测网络质量（未使用）。
    */
    /** @~english
    7: Users cannot detect the network quality. (Not in use.) */
    QUALITY_UNSUPPORTED = 7,
    /** @~chinese
    8: 正在进行网络质量检测。
    */
    /** @~english
    8: Detecting the network quality. */
    QUALITY_DETECTING = 8,
};

/** @~chinese
视频显示模式。
*/
/** @~english
Video display modes.
*/
enum RENDER_MODE_TYPE
{
  /** @~chinese
  1: 视频尺寸等比缩放。优先保证视窗被填满。因视频尺寸与显示视窗尺寸不一致而多出的视频将被截掉。
  */
  /** @~english
1: Uniformly scale the video until it fills the visible boundaries (cropped). One dimension of the video may have clipped contents.
 */
    RENDER_MODE_HIDDEN = 1,
  /** @~chinese
  2: 视频尺寸等比缩放。优先保证视频内容全部显示。因视频尺寸与显示视窗尺寸不一致造成的视窗未被填满的区域填充黑色。
  */
    /** @~english
2: Uniformly scale the video until one of its dimension fits the boundary (zoomed to fit). Areas that are not filled due to disparity in the aspect ratio are filled with black.
 */
    RENDER_MODE_FIT = 2,
  /** @~chinese
  **DEPRECATED** 3: 该模式已废弃。
  */
    /** @~english
    **DEPRECATED** 3: This mode is deprecated.
     */
    RENDER_MODE_ADAPTIVE = 3,
  /** @~chinese
  4: 视频尺寸进行缩放和拉伸以充满显示视窗。
  */
    /**
    4: @~english
    The fill mode. In this mode, the SDK stretches or zooms the video to fill the display window.
    */
    RENDER_MODE_FILL = 4,
};

/** @~chinese
镜像模式的设置。
*/
/** @~english
Video mirror modes.
*/
enum VIDEO_MIRROR_MODE_TYPE
{
      /** @~chinese
      0: （默认）由 SDK 决定镜像模式。
      */
      /** @~english
      0: (Default) The SDK enables the mirror mode.
       */
    VIDEO_MIRROR_MODE_AUTO = 0,//determined by SDK
        /** @~chinese
        1: 启用镜像模式。
        */
        /** @~english
        1: Enable mirror mode.
        */
    VIDEO_MIRROR_MODE_ENABLED = 1,//enabled mirror
        /** @~chinese
        2: 关闭镜像模式。
        */
        /** @~english
        2: Disable mirror mode.
        */
    VIDEO_MIRROR_MODE_DISABLED = 2,//disable mirror
};

/** **DEPRECATED** Video profiles. */
enum VIDEO_PROFILE_TYPE
{
    /** 0: 160 * 120, frame rate 15 fps, bitrate 65 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_120P = 0,
    /** 2: 120 * 120, frame rate 15 fps, bitrate 50 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_120P_3 = 2,
    /** 10: 320*180, frame rate 15 fps, bitrate 140 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_180P = 10,
    /** 12: 180 * 180, frame rate 15 fps, bitrate 100 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_180P_3 = 12,
    /** 13: 240 * 180, frame rate 15 fps, bitrate 120 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_180P_4 = 13,
    /** 20: 320 * 240, frame rate 15 fps, bitrate 200 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_240P = 20,
    /** 22: 240 * 240, frame rate 15 fps, bitrate 140 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_240P_3 = 22,
    /** 23: 424 * 240, frame rate 15 fps, bitrate 220 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_240P_4 = 23,
    /** 30: 640 * 360, frame rate 15 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_360P = 30,
    /** 32: 360 * 360, frame rate 15 fps, bitrate 260 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_360P_3 = 32,
    /** 33: 640 * 360, frame rate 30 fps, bitrate 600 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_360P_4 = 33,
    /** 35: 360 * 360, frame rate 30 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_360P_6 = 35,
    /** 36: 480 * 360, frame rate 15 fps, bitrate 320 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_360P_7 = 36,
    /** 37: 480 * 360, frame rate 30 fps, bitrate 490 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_360P_8 = 37,
    /** 38: 640 * 360, frame rate 15 fps, bitrate 800 Kbps.
     @note Live broadcast profile only.
     */
    VIDEO_PROFILE_LANDSCAPE_360P_9 = 38,
    /** 39: 640 * 360, frame rate 24 fps, bitrate 800 Kbps.
     @note Live broadcast profile only.
     */
    VIDEO_PROFILE_LANDSCAPE_360P_10 = 39,
    /** 100: 640 * 360, frame rate 24 fps, bitrate 1000 Kbps.
     @note Live broadcast profile only.
     */
    VIDEO_PROFILE_LANDSCAPE_360P_11 = 100,
    /** 40: 640 * 480, frame rate 15 fps, bitrate 500 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_480P = 40,
    /** 42: 480 * 480, frame rate 15 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_480P_3 = 42,
    /** 43: 640 * 480, frame rate 30 fps, bitrate 750 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_480P_4 = 43,
    /** 45: 480 * 480, frame rate 30 fps, bitrate 600 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_480P_6 = 45,
    /** 47: 848 * 480, frame rate 15 fps, bitrate 610 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_480P_8 = 47,
    /** 48: 848 * 480, frame rate 30 fps, bitrate 930 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_480P_9 = 48,
    /** 49: 640 * 480, frame rate 10 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_480P_10 = 49,
    /** 50: 1280 * 720, frame rate 15 fps, bitrate 1130 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_720P = 50,
    /** 52: 1280 * 720, frame rate 30 fps, bitrate 1710 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_720P_3 = 52,
    /** 54: 960 * 720, frame rate 15 fps, bitrate 910 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_720P_5 = 54,
    /** 55: 960 * 720, frame rate 30 fps, bitrate 1380 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_720P_6 = 55,
    /** 60: 1920 * 1080, frame rate 15 fps, bitrate 2080 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_1080P = 60,
    /** 62: 1920 * 1080, frame rate 30 fps, bitrate 3150 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_1080P_3 = 62,
    /** 64: 1920 * 1080, frame rate 60 fps, bitrate 4780 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_1080P_5 = 64,
    /** 66: 2560 * 1440, frame rate 30 fps, bitrate 4850 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_1440P = 66,
    /** 67: 2560 * 1440, frame rate 60 fps, bitrate 6500 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_1440P_2 = 67,
    /** 70: 3840 * 2160, frame rate 30 fps, bitrate 6500 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_4K = 70,
    /** 72: 3840 * 2160, frame rate 60 fps, bitrate 6500 Kbps. */
    VIDEO_PROFILE_LANDSCAPE_4K_3 = 72,
    /** 1000: 120 * 160, frame rate 15 fps, bitrate 65 Kbps. */
    VIDEO_PROFILE_PORTRAIT_120P = 1000,
    /** 1002: 120 * 120, frame rate 15 fps, bitrate 50 Kbps. */
    VIDEO_PROFILE_PORTRAIT_120P_3 = 1002,
    /** 1010: 180 * 320, frame rate 15 fps, bitrate 140 Kbps. */
    VIDEO_PROFILE_PORTRAIT_180P = 1010,
    /** 1012: 180 * 180, frame rate 15 fps, bitrate 100 Kbps. */
    VIDEO_PROFILE_PORTRAIT_180P_3 = 1012,
    /** 1013: 180 * 240, frame rate 15 fps, bitrate 120 Kbps. */
    VIDEO_PROFILE_PORTRAIT_180P_4 = 1013,
    /** 1020: 240 * 320, frame rate 15 fps, bitrate 200 Kbps. */
    VIDEO_PROFILE_PORTRAIT_240P = 1020,
    /** 1022: 240 * 240, frame rate 15 fps, bitrate 140 Kbps. */
    VIDEO_PROFILE_PORTRAIT_240P_3 = 1022,
    /** 1023: 240 * 424, frame rate 15 fps, bitrate 220 Kbps. */
    VIDEO_PROFILE_PORTRAIT_240P_4 = 1023,
    /** 1030: 360 * 640, frame rate 15 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_PORTRAIT_360P = 1030,
    /** 1032: 360 * 360, frame rate 15 fps, bitrate 260 Kbps. */
    VIDEO_PROFILE_PORTRAIT_360P_3 = 1032,
    /** 1033: 360 * 640, frame rate 30 fps, bitrate 600 Kbps. */
    VIDEO_PROFILE_PORTRAIT_360P_4 = 1033,
    /** 1035: 360 * 360, frame rate 30 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_PORTRAIT_360P_6 = 1035,
    /** 1036: 360 * 480, frame rate 15 fps, bitrate 320 Kbps. */
    VIDEO_PROFILE_PORTRAIT_360P_7 = 1036,
    /** 1037: 360 * 480, frame rate 30 fps, bitrate 490 Kbps. */
    VIDEO_PROFILE_PORTRAIT_360P_8 = 1037,
    /** 1038: 360 * 640, frame rate 15 fps, bitrate 800 Kbps.
     @note Live broadcast profile only.
     */
    VIDEO_PROFILE_PORTRAIT_360P_9 = 1038,
    /** 1039: 360 * 640, frame rate 24 fps, bitrate 800 Kbps.
     @note Live broadcast profile only.
     */
    VIDEO_PROFILE_PORTRAIT_360P_10 = 1039,
    /** 1100: 360 * 640, frame rate 24 fps, bitrate 1000 Kbps.
     @note Live broadcast profile only.
     */
    VIDEO_PROFILE_PORTRAIT_360P_11 = 1100,
    /** 1040: 480 * 640, frame rate 15 fps, bitrate 500 Kbps. */
    VIDEO_PROFILE_PORTRAIT_480P = 1040,
    /** 1042: 480 * 480, frame rate 15 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_PORTRAIT_480P_3 = 1042,
    /** 1043: 480 * 640, frame rate 30 fps, bitrate 750 Kbps. */
    VIDEO_PROFILE_PORTRAIT_480P_4 = 1043,
    /** 1045: 480 * 480, frame rate 30 fps, bitrate 600 Kbps. */
    VIDEO_PROFILE_PORTRAIT_480P_6 = 1045,
    /** 1047: 480 * 848, frame rate 15 fps, bitrate 610 Kbps. */
    VIDEO_PROFILE_PORTRAIT_480P_8 = 1047,
    /** 1048: 480 * 848, frame rate 30 fps, bitrate 930 Kbps. */
    VIDEO_PROFILE_PORTRAIT_480P_9 = 1048,
    /** 1049: 480 * 640, frame rate 10 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_PORTRAIT_480P_10 = 1049,
    /** 1050: 720 * 1280, frame rate 15 fps, bitrate 1130 Kbps. */
    VIDEO_PROFILE_PORTRAIT_720P = 1050,
    /** 1052: 720 * 1280, frame rate 30 fps, bitrate 1710 Kbps. */
    VIDEO_PROFILE_PORTRAIT_720P_3 = 1052,
    /** 1054: 720 * 960, frame rate 15 fps, bitrate 910 Kbps. */
    VIDEO_PROFILE_PORTRAIT_720P_5 = 1054,
    /** 1055: 720 * 960, frame rate 30 fps, bitrate 1380 Kbps. */
    VIDEO_PROFILE_PORTRAIT_720P_6 = 1055,
    /** 1060: 1080 * 1920, frame rate 15 fps, bitrate 2080 Kbps. */
    VIDEO_PROFILE_PORTRAIT_1080P = 1060,
    /** 1062: 1080 * 1920, frame rate 30 fps, bitrate 3150 Kbps. */
    VIDEO_PROFILE_PORTRAIT_1080P_3 = 1062,
    /** 1064: 1080 * 1920, frame rate 60 fps, bitrate 4780 Kbps. */
    VIDEO_PROFILE_PORTRAIT_1080P_5 = 1064,
    /** 1066: 1440 * 2560, frame rate 30 fps, bitrate 4850 Kbps. */
    VIDEO_PROFILE_PORTRAIT_1440P = 1066,
    /** 1067: 1440 * 2560, frame rate 60 fps, bitrate 6500 Kbps. */
    VIDEO_PROFILE_PORTRAIT_1440P_2 = 1067,
    /** 1070: 2160 * 3840, frame rate 30 fps, bitrate 6500 Kbps. */
    VIDEO_PROFILE_PORTRAIT_4K = 1070,
    /** 1072: 2160 * 3840, frame rate 60 fps, bitrate 6500 Kbps. */
    VIDEO_PROFILE_PORTRAIT_4K_3 = 1072,
    /** Default 640 * 360, frame rate 15 fps, bitrate 400 Kbps. */
    VIDEO_PROFILE_DEFAULT = VIDEO_PROFILE_LANDSCAPE_360P,
};

/** @~chinese
音频属性。

设置采样率、码率、编码模式和声道数。 */
/** @~english
Audio profiles.

Sets the sample rate, bitrate, encoding mode, and the number of channels:
*/
enum AUDIO_PROFILE_TYPE // sample rate, bit rate, mono/stereo, speech/music codec
{
   /** @~chinese
    0: 默认值：
    - 直播场景下：48 KHz 采样率，音乐编码，单声道，编码码率最大值为 52 Kbps。
    - 通信场景下：16 KHz 采样率，音乐编码，单声道，编码码率最大值为 16 Kbps。
    */
   /** @~english
    0: Default audio profile:
    - For the live-broadcast profile: A sample rate of 48 KHz, music encoding, mono, and a bitrate of up to 52 Kbps.
    - For the communication profile: A sample rate of 16 KHz, music encoding, mono, and a bitrate of up to 16 Kbps.
    */
    AUDIO_PROFILE_DEFAULT = 0, // use default settings
    /** @~chinese
    1: 指定 32 KHz 采样率，语音编码，单声道，编码码率最大值为 18 Kbps。
    */
    /** @~english
     1: A sample rate of 32 KHz, audio encoding, mono, and a bitrate of up to 18 Kbps.
     */
    AUDIO_PROFILE_SPEECH_STANDARD = 1, // 32Khz, 18Kbps, mono, speech
    /** @~chinese
    2: 指定 48 KHz 采样率，音乐编码，单声道，编码码率最大值为 48 Kbps。
    */
    /** @~english
     2: A sample rate of 48 KHz, music encoding, mono, and a bitrate of up to 48 Kbps.
     */
    AUDIO_PROFILE_MUSIC_STANDARD = 2, // 48Khz, 48Kbps, mono, music
    /** @~chinese
     3: 指定 48 KHz 采样率，音乐编码，双声道，编码码率最大值为 56 Kbps。
    */
    /** @~english
     3: A sample rate of 48 KHz, music encoding, stereo, and a bitrate of up to 56 Kbps.
     */
    AUDIO_PROFILE_MUSIC_STANDARD_STEREO = 3, // 48Khz, 56Kbps, stereo, music
    /** @~chinese
    4: 指定 48 KHz 采样率，音乐编码，单声道，编码码率最大值为 128 Kbps。
    */
    /** @~english
     4: A sample rate of 48 KHz, music encoding, mono, and a bitrate of up to 128 Kbps.
     */
    AUDIO_PROFILE_MUSIC_HIGH_QUALITY = 4, // 48Khz, 128Kbps, mono, music
    /** @~chinese
    5: 指定 48 KHz 采样率，音乐编码，双声道，编码码率最大值为 192 Kbps。
    */
    /** @~english
     5: A sample rate of 48 KHz, music encoding, stereo, and a bitrate of up to 192 Kbps.
     */
    AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO = 5, // 48Khz, 192Kbps, stereo, music
    /** @~chinese
    6: 指定 16 KHz 采样率，语音编码，单声道，应用回声消除算法 AES。
    */
    /** @~english
     6: A sample rate of 16 KHz, audio encoding, mono, and Acoustic Echo Cancellation (AES) enabled.
     */
    AUDIO_PROFILE_IOT                       = 6,
    AUDIO_PROFILE_NUM = 7,
};

/** @~chinese
音频应用场景。
*/
/** @~english
Audio application scenarios.
*/
enum AUDIO_SCENARIO_TYPE // set a suitable scenario for your app type
{
    /** @~chinese
    0: 默认的音频应用场景。
    */
    /** @~english
    0: Default.
    */
    AUDIO_SCENARIO_DEFAULT = 0,
    /** @~chinese
    1: 娱乐场景，支持边玩游戏边语音。
    */
    /** @~english
    1: Entertainment scenario, supporting voice during gameplay.
    */
    AUDIO_SCENARIO_CHATROOM_ENTERTAINMENT = 1,
    /** @~chinese
    2: 教育场景，适用于需要高流畅度和稳定性的场景。
    */
    /** @~english
    2: Education scenario, prioritizing smoothness and stability.
    */
    AUDIO_SCENARIO_EDUCATION = 2,
    /** @~chinese
    3: 游戏直播场景，游戏音效可通过扬声器播放，适用于需要播放高保真音乐的场景。
    */
    /** @~english
    3: Live gaming scenario, enabling the gaming audio effects in the speaker mode in a live broadcast scenario. Choose this scenario for high-fidelity music playback.
    */
    AUDIO_SCENARIO_GAME_STREAMING = 3,
    /** @~chinese
    4: 秀场场景，通过外部专业设备优化音频质量。
    */
    /** @~english
    4: Showroom scenario, optimizing the audio quality with external professional equipment.
    */
    AUDIO_SCENARIO_SHOWROOM = 4,
    /** @~chinese
    5: 游戏场景。
    */
    /** @~english
    5: Gaming scenario.
    */
    AUDIO_SCENARIO_CHATROOM_GAMING = 5,
    /** @~chinese
    6: IoT（物联网）场景。
    */
    /** @~english
    6: Applicable to the IoT scenario.
    */
    AUDIO_SCENARIO_IOT = 6,
    AUDIO_SCENARIO_NUM = 7,
};

 /** @~chinese
 频道使用场景。
 */
 /** @~english
 The channel profile of the IRtcEngine.
 */
enum CHANNEL_PROFILE_TYPE
{
    /** @~chinese
    0: （默认）通信场景。该场景下，频道内所有用户都可以发布和接收音、视频流。适用于语音通话、视频群聊等应用场景。
    */
   /** @~english
   (Default) The Communication profile. Use this profile in one-on-one calls or group calls, where all users can talk freely.
    */
	CHANNEL_PROFILE_COMMUNICATION = 0,
    /** @~chinese
    1: 直播场景。该场景有主播和观众两种用户角色。主播可以发布和接收音视频流，观众直接接收流。
    */
   /** @~english
   The Live-Broadcast profile. Users in a live-broadcast channel have a role as either broadcaster or audience.
    A broadcaster can both send and receive streams; an audience can only receive streams.
    */
	CHANNEL_PROFILE_LIVE_BROADCASTING = 1,
   /** @~chinese
   2: 游戏语音场景。该场景默认使用低功耗低码率的编解码器，且频道内任何用户都可以自由发言，适用于游戏场景。
    */
   /** @~english
   2: The Gaming profile. This profile uses a codec with a lower bitrate and consumes less power. Applies to the gaming scenario, where all game players can talk freely.
    */
    CHANNEL_PROFILE_GAME = 2,
};

/** @~chinese
直播场景里的用户角色。
*/
/** @~english
Client roles in a live broadcast.
*/
enum CLIENT_ROLE_TYPE
{
    /** @~chinese
    1: 主播。主播可以发流也可以收流。
    */
    /** @~english
    1: Broadcaster. A broadcaster can both send and receive streams.
    */
    CLIENT_ROLE_BROADCASTER = 1,
    /** @~chinese
    2:（默认）观众。观众只能收流不能发流。
    */
    /** @~english
    2: Audience, the default role. An audience can only receive streams.
    */
    CLIENT_ROLE_AUDIENCE = 2,
};

/** @~chinese
用户离线原因。
*/
/** @~english
Reasons for a user being offline.
*/
enum USER_OFFLINE_REASON_TYPE
{
    /** @~chinese
    0: 用户主动离开。
    */
    /** @~english
    0: The user quits the call.
    */
    USER_OFFLINE_QUIT = 0,
    /** @~chinese
    1: 因过长时间收不到对方数据包，超时掉线。由于 SDK 使用的是不可靠通道，如果对方主动离开但本方没收到对方离开消息，可能会误判为超时掉线。
    */
    /** @~english
    1: The SDK times out and the user drops offline because no data packet is received within a certain period of time.
    If the user quits the call and the message is not passed to the SDK (due to an unreliable channel), the SDK assumes the user dropped offline.
    */
    USER_OFFLINE_DROPPED = 1,
      /** @~chinese
      2: （仅适用于直播场景）用户身份从主播切换为观众。
      */
      /** @~english
      2: (Live broadcast only.) The client role switched from the host to the audience.
      */
    USER_OFFLINE_BECOME_AUDIENCE = 2,
};
/** @~chinese
推流状态。
*/
/** @~english
 States of the RTMP streaming.
 */
enum RTMP_STREAM_PUBLISH_STATE
{
  /** @~chinese
  0: 推流未开始或已结束。成功调用 \ref IRtcEngine::removePublishStreamUrl "removePublishStreamUrl" 方法删除推流地址后，也会返回该状态。
  */
  /** @~english
  The RTMP streaming has not started or has ended. This state is also triggered after you remove an RTMP address from the CDN by calling removePublishStreamUrl.
   */
  RTMP_STREAM_PUBLISH_STATE_IDLE = 0,
  /** @~chinese
  1: 正在连接 Agora 推流服务器和 CDN 服务器。调用 \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" 方法后，会返回该状态。
  */
  /** @~english
  The SDK is connecting to Agora's streaming server and the RTMP server. This state is triggered after you call the \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" method.
   */
  RTMP_STREAM_PUBLISH_STATE_CONNECTING = 1,
  /** @~chinese
  2: 推流正在进行。成功推流后，会返回该状态。
  */
  /** @~english
  The RTMP streaming publishes. The SDK successfully publishes the RTMP streaming and returns this state.
   */
  RTMP_STREAM_PUBLISH_STATE_RUNNING = 2,
  /** @~chinese
  3: 正在恢复推流。当 CDN 出现异常，或推流短暂中断时，SDK 会自动尝试恢复推流，并返回该状态。

   - 如成功恢复推流，则进入状态 #RTMP_STREAM_PUBLISH_STATE_RUNNING (2)。
   - 如服务器出错或 60 秒内未成功恢复，则进入状态 #RTMP_STREAM_PUBLISH_STATE_FAILURE (4)。如果觉得 60 秒太长，也可以主动调用 \ref IRtcEngine::removePublishStreamUrl "removePublishStreamUrl" 和 \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" 方法尝试重连。
  */
  /** @~english
  The RTMP streaming is recovering. When exceptions occur to the CDN, or the streaming is interrupted, the SDK tries to resume RTMP streaming and returns this state.

   - If the SDK successfully resumes the streaming, #RTMP_STREAM_PUBLISH_STATE_RUNNING (2) returns.
   - If the streaming does not resume within 60 seconds or server errors occur, #RTMP_STREAM_PUBLISH_STATE_FAILURE (4) returns. You can also reconnect to the server by calling the \ref IRtcEngine::removePublishStreamUrl "removePublishStreamUrl" and \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" methods.
   */
  RTMP_STREAM_PUBLISH_STATE_RECOVERING = 3,
  /** @~chinese
  4: 推流失败。失败后，你可以通过返回的错误码排查错误原因，也可以再次调用 \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" 重新尝试推流。
  */
  /** @~english
  The RTMP streaming fails. See the errCode parameter for the detailed error information. You can also call the \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" method to publish the RTMP streaming again.
   */
  RTMP_STREAM_PUBLISH_STATE_FAILURE = 4,
};

/** @~chinese
推流错误码。
*/
/** @~english
 Error codes of the RTMP streaming.
 */
enum RTMP_STREAM_PUBLISH_ERROR
{
  /** @~chinese
  0: 推流成功。
  */
  /** @~english
  The RTMP streaming publishes successfully.
  */
  RTMP_STREAM_PUBLISH_ERROR_OK = 0,
  /** @~chinese
  1: 参数无效。例如，如果在调用 \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" 前没有调用 \ref IRtcEngine::setLiveTranscoding "setLiveTranscoding" 设置转码参数，SDK 会返回该错误。请检查输入参数是否正确。
  */
  /** @~english
  Invalid argument used. If, for example, you do not call the \ref IRtcEngine::setLiveTranscoding "setLiveTranscoding" method to configure the LiveTranscoding parameters before calling the addPublishStreamUrl method, the SDK returns this error. Check whether you set the parameters in the *setLiveTranscoding* method properly.
  */
  RTMP_STREAM_PUBLISH_ERROR_INVALID_ARGUMENT = 1,
  /** @~chinese
  2: 推流已加密，不能推流。
  */
  /** @~english
  The RTMP streaming is encrypted and cannot be published.
  */
  RTMP_STREAM_PUBLISH_ERROR_ENCRYPTED_STREAM_NOT_ALLOWED = 2,
  /** @~chinese
  3: 推流超时未成功。可调用 \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" 重新推流。
  */
  /** @~english
  Timeout for the RTMP streaming. Call the \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" method to publish the streaming again.
  */
  RTMP_STREAM_PUBLISH_ERROR_CONNECTION_TIMEOUT = 3,
  /** @~chinese
  4: 推流服务器出现错误。请调用 \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" 重新推流。
  */
  /** @~english
  An error occurs in Agora's streaming server. Call the addPublishStreamUrl method to publish the streaming again.
  */
  RTMP_STREAM_PUBLISH_ERROR_INTERNAL_SERVER_ERROR = 4,
  /** @~chinese
  5: CDN 服务器出现错误。
  */
  /** @~english
  An error occurs in the RTMP server.
  */
  RTMP_STREAM_PUBLISH_ERROR_RTMP_SERVER_ERROR = 5,
  /** @~chinese
  6: 推流请求过于频繁。
  */
  /** @~english
  The RTMP streaming publishes too frequently.
  */
  RTMP_STREAM_PUBLISH_ERROR_TOO_OFTEN = 6,
  /** @~chinese
  7: 单个主播的推流地址数目达到上线 10。请删掉一些不用的推流地址再增加推流地址。
  */
  /** @~english
  The host publishes more than 10 URLs. Delete the unnecessary URLs before adding new ones.
  */
  RTMP_STREAM_PUBLISH_ERROR_REACH_LIMIT = 7,
  /** @~chinese
  8: 主播操作不属于自己的流。例如更新其他主播的流参数、停止其他主播的流。请检查 App 逻辑。
  */
  /** @~english
  The host manipulates other hosts' URLs. Check your app logic.
  */
  RTMP_STREAM_PUBLISH_ERROR_NOT_AUTHORIZED = 8,
  /** @~chinese
  9: 服务器没有找到这个流。
  */
  /** @~english
  Agora's server fails to find the RTMP streaming.
  */
  RTMP_STREAM_PUBLISH_ERROR_STREAM_NOT_FOUND = 9,
  /** @~chinese
  10: 推流地址格式有错误。请检查推流地址格式是否正确。
  */
  /** @~english
  The format of the RTMP streaming URL is not supported. Check whether the URL format is correct.
  */
  RTMP_STREAM_PUBLISH_ERROR_FORMAT_NOT_SUPPORTED = 10,
};
/** @~english States of importing an external video stream in a live broadcast. */
/** @~chinese 直播中外部视频源的导入状态。 */
enum INJECT_STREAM_STATUS
{
    /** @~english 0: The external video stream imported successfully. */
    /** @~chinese 0: 外部视频流导入成功。 */
    INJECT_STREAM_STATUS_START_SUCCESS = 0,
    /** @~english 1: The external video stream already exists. */
    /** @~chinese 1: 外部视频流已存在。 */
    INJECT_STREAM_STATUS_START_ALREADY_EXISTS = 1,
    /** @~english 2: The external video stream to be imported is unauthorized. */
    /** @~chinese 2: 外部视频流导入未经授权。 */
    INJECT_STREAM_STATUS_START_UNAUTHORIZED = 2,
    /** @~english 3: Import external video stream timeout. */
    /** @~chinese 3: 导入外部视频流超时。 */
    INJECT_STREAM_STATUS_START_TIMEDOUT = 3,
    /** @~english 4: Import external video stream failed. */
    /** @~chinese 4: 外部视频流导入失败。 */
    INJECT_STREAM_STATUS_START_FAILED = 4,
    /** @~english 5: The external video stream stopped importing successfully. */
    /** @~chinese 5: 外部视频流停止导入成功。 */
    INJECT_STREAM_STATUS_STOP_SUCCESS = 5,
    /** @~english 6: No external video stream is found. */
    /** @~chinese 6: 未找到要停止导入的外部视频流。 */
    INJECT_STREAM_STATUS_STOP_NOT_FOUND = 6,
    /** @~english 7: The external video stream to be stopped importing is unauthorized. */
    /** @~chinese 7: 要停止导入的外部视频流未经授权。 */
    INJECT_STREAM_STATUS_STOP_UNAUTHORIZED = 7,
    /** @~english 8: Stop importing external video stream timeout. */
    /** @~chinese 8: 停止导入外部视频流超时。 */
    INJECT_STREAM_STATUS_STOP_TIMEDOUT = 8,
    /** @~english 9: Stop importing external video stream failed. */
    /** @~chinese 9: 停止导入外部视频流失败。 */
    INJECT_STREAM_STATUS_STOP_FAILED = 9,
    /** @~english 10: The external video stream is corrupted. */
    /** @~chinese 10: 导入的外部视频流被中断。 */
    INJECT_STREAM_STATUS_BROKEN = 10,
};

/** @~english Remote video stream types. */
/** @~chinese 视频流类型。 */
enum REMOTE_VIDEO_STREAM_TYPE
{
      /** @~english 0: High-stream video. */
      /** @~chinese 0: 视频大流。 */
    REMOTE_VIDEO_STREAM_HIGH = 0,
      /** @~english 1: Low-stream video. */
      /** @~chinese 1: 视频小流。 */
    REMOTE_VIDEO_STREAM_LOW = 1,
};

/** @~english The use mode of the audio data in the \ref media::IAudioFrameObserver::onRecordAudioFrame "onRecordAudioFrame" or \ref media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" callback. */
/** @~chinese \ref media::IAudioFrameObserver::onRecordAudioFrame "onRecordAudioFrame" 或 \ref media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" 回调中返回的音频数据的使用模式。 */
 enum RAW_AUDIO_FRAME_OP_MODE_TYPE
{
    /** @~english 0: Read-only mode: Users only read the \ref agora::media::IAudioFrameObserver::AudioFrame "AudioFrame" data without modifying anything. For example, when users acquire the data with the Agora SDK, then push the RTMP streams. */
    /** @~chinese 0: 只读模式，用户仅从 \ref agora::media::IAudioFrameObserver::AudioFrame "AudioFrame" 获取原始数据，不作任何修改。例如: 若用户通过 Agora SDK 采集数据，自己进行 RTMP/RTMPS 推流，则可以选择该模式。 */
    RAW_AUDIO_FRAME_OP_MODE_READ_ONLY = 0,
    /** @~english 1: Write-only mode: Users replace the \ref agora::media::IAudioFrameObserver::AudioFrame "AudioFrame" data with their own data and pass the data to the SDK for encoding. For example, when users acquire the data. */
    /** @~chinese 1: 只写模式，用户替换 \ref agora::media::IAudioFrameObserver::AudioFrame "AudioFrame" 中的数据以供 SDK 编码传输。例如: 若用户自行采集数据，可选择该模式。 */
    RAW_AUDIO_FRAME_OP_MODE_WRITE_ONLY = 1,
    /** @~english 2: Read and write mode: Users read the data from \ref agora::media::IAudioFrameObserver::AudioFrame "AudioFrame", modify it, and then play it. For example, when users have their own sound-effect processing module and perform some voice pre-processing, such as a voice change. */
    /** @~chinese 2: 读写模式, 用户从 \ref agora::media::IAudioFrameObserver::AudioFrame "AudioFrame" 获取并修改数据、修改，并返回给 SDK 进行编码传输。例如: 若用户自己有音效处理模块，且想要根据实际需要对数据进行前处理(例如变声)，则可以选择该模式。 */
    RAW_AUDIO_FRAME_OP_MODE_READ_WRITE = 2,
};

/** @~english Audio-sample rates. */
/** @~chinese 用于旁路推流的输出音频的采样率。 */
enum AUDIO_SAMPLE_RATE_TYPE
{
    /** @~english 32000: 32 kHz */
    /** @~chinese 32000: 32 kHz */
    AUDIO_SAMPLE_RATE_32000 = 32000,
    /** @~english 44100: 44.1 kHz */
    /** @~chinese 44100: 44.1 kHz */
    AUDIO_SAMPLE_RATE_44100 = 44100,
    /** @~english 48000: 48 kHz */
    /** @~chinese 48000: 48 kHz */
    AUDIO_SAMPLE_RATE_48000 = 48000,
};

/** @~english Video codec profile types. */
/** @~chinese 用于旁路推流的输出视频的编解码规格。 */
enum VIDEO_CODEC_PROFILE_TYPE
{
    /** @~english 66: Baseline video codec profile. Generally used in video calls on mobile phones. */
    /** @~chinese 66: Baseline 级别的视频编码规格，一般用于低阶或需要额外容错的应用，比如视频通话、手机视频等。 */
    VIDEO_CODEC_PROFILE_BASELINE = 66,
    /** @~english 77: Main video codec profile. Generally used in mainstream electronics such as MP4 players, portable video players, PSP, and iPads. */
    /** @~chinese 77: Main 级别的视频编码规格，一般用于主流消费类电子产品，如 mp4、便携的视频播放器、PSP 和 iPad 等。*/
    VIDEO_CODEC_PROFILE_MAIN = 77,
    /** @~english 100: (Default) High video codec profile. Generally used in high-resolution broadcasts or television. */
    /** @~chinese 100: （默认）High 级别的视频编码规格，一般用于广播及视频碟片存储，高清电视。 */
    VIDEO_CODEC_PROFILE_HIGH = 100,
};

/** @~english Video codec types */
/** @~chinese 视频编码格式 */
enum VIDEO_CODEC_TYPE {
    /** @~english Standard VP8 */
    /** @~chinese 标准 VP8 */
    VIDEO_CODEC_VP8 = 1,
    /** @~english Standard H264 */
    /** @~chinese 标准 H264 */
    VIDEO_CODEC_H264 = 2,
    /** @~english Enhanced VP8 */
    /** @~chinese 增强 VP8 */
    VIDEO_CODEC_EVP = 3,
    /** @~english Enhanced H264 */
    /** @~chinese 增强 H264 */
    VIDEO_CODEC_E264 = 4,
};

/** @~english Audio equalization band frequencies. */
/** @~chinese 语音音效均衡波段的中心频率。 */
enum AUDIO_EQUALIZATION_BAND_FREQUENCY
{
    /** @~english 0: 31 Hz */
    /** @~chinese 0: 31 Hz */
    AUDIO_EQUALIZATION_BAND_31 = 0,
      /** @~english 1: 62 Hz */
      /** @~chinese 1: 62 Hz */
    AUDIO_EQUALIZATION_BAND_62 = 1,
    /** @~english 2: 125 Hz */
    /** @~chinese 2: 125 Hz */
    AUDIO_EQUALIZATION_BAND_125 = 2,
      /** @~english 3: 250 Hz */
      /** @~chinese 3: 250 Hz */
    AUDIO_EQUALIZATION_BAND_250 = 3,
      /** @~english 4: 500 Hz */
      /** @~chinese 4: 500 Hz */
    AUDIO_EQUALIZATION_BAND_500 = 4,
        /** @~english 5: 1 kHz */
        /** @~chinese 5: 1 kHz */
    AUDIO_EQUALIZATION_BAND_1K = 5,
        /** @~english 6: 2 kHz */
        /** @~chinese 6: 2 kHz */
    AUDIO_EQUALIZATION_BAND_2K = 6,
        /** @~english 7: 4 kHz */
        /** @~chinese 7: 4 kHz */
    AUDIO_EQUALIZATION_BAND_4K = 7,
        /** @~english 8: 8 kHz */
        /** @~chinese 8: 8 kHz */
    AUDIO_EQUALIZATION_BAND_8K = 8,
      /** @~english 9: 16 kHz */
      /** @~chinese 9: 16 kHz */
    AUDIO_EQUALIZATION_BAND_16K = 9,
};

/** @~english Audio reverberation types. */
/** @~chinese 各混响音效 Key 所对应的值。 */
enum AUDIO_REVERB_TYPE
{
    /** @~english 0: The level of the dry signal (db). The value is between -20 and 10. */
    /** @~chinese 0: 取值范围 [-20,10]，单位为 dB, 原始声音强度，即所谓的 dry signal。 */
    AUDIO_REVERB_DRY_LEVEL = 0, // (dB, [-20,10]), the level of the dry signal
    /** @~english 1: The level of the early reflection signal (wet signal) (dB). The value is between -20 and 10. */
    /** @~chinese 1: 取值范围 [-20,10]，单位为 dB, 早期反射信号强度，即所谓的 wet signal。 */
    AUDIO_REVERB_WET_LEVEL = 1, // (dB, [-20,10]), the level of the early reflection signal (wet signal)
    /** @~english 2: The room size of the reflection. The value is between 0 and 100. */
    /** @~chinese 2: 所需混响效果的房间尺寸，一般房间越大，混响越强，取值范围 [0,100]。 */
    AUDIO_REVERB_ROOM_SIZE = 2, // ([0,100]), the room size of the reflection
    /** @~english 3: The length of the initial delay of the wet signal (ms). The value is between 0 and 200. */
    /** @~chinese 3: 取值范围 [0,200]，单位为毫秒, wet signal 的初始延迟长度，以毫秒为单位。 */
    AUDIO_REVERB_WET_DELAY = 3, // (ms, [0,200]), the length of the initial delay of the wet signal in ms
    /** @~english 4: The reverberation strength. The value is between 0 and 100. */
    /** @~chinese 4: 取值范围 [0,100], 混响持续的强度。 */
    AUDIO_REVERB_STRENGTH = 4, // ([0,100]), the strength of the reverberation
};

/** @~english
 * Local voice changer options.
 */
/**
 * @~chinese 预设的语音变声效果。
 */
enum VOICE_CHANGER_PRESET {
    /** @~english
     * The original voice (no local voice change).
     */
    /** @~chinese
     * 原声，即关闭语音变声。
     */
    VOICE_CHANGER_OFF = 0x00000000, //Turn off the voice changer
    /** @~english
     * The voice of an old man.
     */
    /** @~chinese
     * 变声：老年男性。
     */
    VOICE_CHANGER_OLDMAN = 0x00000001,
    /** @~english
     * The voice of a little boy.
     */
     /** @~chinese
     * 变声：小男孩。
     */
    VOICE_CHANGER_BABYBOY = 0x00000002,
    /** @~english
     * The voice of a little girl.
     */
     /** @~chinese
     * 变声：小女孩。
     */
    VOICE_CHANGER_BABYGIRL = 0x00000003,
    /** @~english
     * The voice of Zhu Bajie, a character in Journey to the West who has a voice like that of a growling bear.
     */
    /** @~chinese
     * 变声：猪八戒。
     */
    VOICE_CHANGER_ZHUBAJIE = 0x00000004,
    /** @~english
     * The ethereal voice.
     */
    /** @~chinese
     * 变声：空灵。
     */
    VOICE_CHANGER_ETHEREAL = 0x00000005,
    /** @~english
     * The voice of Hulk.
     */
    /** @~chinese
     * 变声：绿巨人。
     */
    VOICE_CHANGER_HULK = 0x00000006,
    /** @~english
     * A more vigorous voice.
     */
     /** @~chinese
     * 美音：浑厚。
     */
    VOICE_BEAUTY_VIGOROUS = 0x00100001,//7,
    /** @~english
     * A deeper voice.
     */
     /** @~chinese
     * 美音：低沉。
     */
    VOICE_BEAUTY_DEEP = 0x00100002,
    /** @~english
     * A mellower voice.
     */
     /** @~chinese
     * 美音：圆润。
     */
    VOICE_BEAUTY_MELLOW = 0x00100003,
    /** @~english
     * Falsetto.
     */
     /** @~chinese
     * 美音：假音。
     */
    VOICE_BEAUTY_FALSETTO = 0x00100004,
    /** @~english
     * A fuller voice.
     */
     /** @~chinese
     * 美音：饱满。
     */
    VOICE_BEAUTY_FULL = 0x00100005,
    /** @~english
     * A clearer voice.
     */
     /** @~chinese
     * 美音：清澈。
     */
    VOICE_BEAUTY_CLEAR = 0x00100006,
    /** @~english
     * A more resounding voice.
     */
     /** @~chinese
     * 美音：高亢。
     */
    VOICE_BEAUTY_RESOUNDING = 0x00100007,
    /** @~english
     * A more ringing voice.
     */
     /** @~chinese
     * 美音：嘹亮。
     */
    VOICE_BEAUTY_RINGING = 0x00100008,
    /** @~english
     * A more spatially resonant voice.
     */
     /** @~chinese
     * 美音：空旷。
     */
    VOICE_BEAUTY_SPACIAL = 0x00100009,
    /** @~english
     * (For male only) A more magnetic voice. Do not use it when the speaker is a female; otherwise, voice distortion occurs.
     */
     /** @~chinese
     * 语聊美声：磁性（男）。此枚举为男声定制化效果，不适用于女声。若女声使用此音效设置，则音频可能会产生失真。
     */
    GENERAL_BEAUTY_VOICE_MALE_MAGNETIC = 0x00200001,
    /** @~english
     * (For female only) A fresher voice. Do not use it when the speaker is a male; otherwise, voice distortion occurs.
     */
     /** @~chinese
     * 语聊美声：清新（女）。此枚举为女声定制化效果，不适用于男声。若男声使用此音效设置，则音频可能会产生失真。
     */
    GENERAL_BEAUTY_VOICE_FEMALE_FRESH = 0x00200002,
    /** @~english
     * 	(For female only) A more vital voice. Do not use it when the speaker is a male; otherwise, voice distortion occurs.
     */
     /** @~chinese
     * 语聊美声：活力（女）。此枚举为女声定制化效果，不适用于男声。若男声使用此音效设置，则音频可能会产生失真。
     */
    GENERAL_BEAUTY_VOICE_FEMALE_VITALITY = 0x00200003

};

/** @~english Local voice reverberation presets. */
/** @~chinese 预设的语音混响效果。 */
enum AUDIO_REVERB_PRESET {
    /** @~english
     * Turn off local voice reverberation, that is, to use the original voice.
     */
     /** @~chinese
     * 原声，即关闭本地语音混响。
     */
    AUDIO_REVERB_OFF = 0x00000000, // Turn off audio reverb
    /** @~english
     * The reverberation style typical of a KTV venue (enhanced).
     */
     /** @~chinese
     * KTV（增强版）。
     */
    AUDIO_REVERB_FX_KTV = 0x00100001,
    /** @~english
     * The reverberation style typical of a concert hall (enhanced).
     */
     /** @~chinese
     * 演唱会（增强版）。
     */
    AUDIO_REVERB_FX_VOCAL_CONCERT = 0x00100002,
    /** @~english
     * The reverberation style typical of an uncle's voice.
     */
     /** @~chinese
     * 大叔。
     */
    AUDIO_REVERB_FX_UNCLE = 0x00100003,
    /** @~english
     * The reverberation style typical of a little sister's voice.
     */
     /** @~chinese
     * 小姐姐。
     */
    AUDIO_REVERB_FX_SISTER = 0x00100004,
    /** @~english
     * The reverberation style typical of a recording studio (enhanced).
     */
     /** @~chinese
     * 录音棚（增强版）。
     */
    AUDIO_REVERB_FX_STUDIO = 0x00100005,
    /** @~english
     * The reverberation style typical of popular music (enhanced).
     */
     /** @~chinese
     * 流行（增强版）。
     */
    AUDIO_REVERB_FX_POPULAR = 0x00100006,
    /** @~english
     * The reverberation style typical of R&B music (enhanced).
     */
     /** @~chinese
     * R&B（增强版）。
     */
    AUDIO_REVERB_FX_RNB = 0x00100007,
    /** @~english
     * The reverberation style typical of the vintage phonograph.
     */
     /** @~chinese
     * 留声机。
     */
    AUDIO_REVERB_FX_PHONOGRAPH = 0x00100008,
    /** @~english
     * The reverberation style typical of popular music.
     */
     /** @~chinese
     * 流行。
     */
    AUDIO_REVERB_POPULAR = 0x00000001,
    /** @~english
     * The reverberation style typical of R&B music.
     */
     /** @~chinese
     * R&B。
     */
    AUDIO_REVERB_RNB = 0x00000002,
    /** @~english
     * The reverberation style typical of rock music.
     */
     /** @~chinese
     * 摇滚。
     */
    AUDIO_REVERB_ROCK = 0x00000003,
    /** @~english
     * The reverberation style typical of hip-hop music.
     */
     /** @~chinese
     * 嘻哈。
     */
     AUDIO_REVERB_HIPHOP = 0x00000004,
    /** @~english
     * The reverberation style typical of a concert hall.
     */
     /** @~chinese
     * 演唱会。
     */
    AUDIO_REVERB_VOCAL_CONCERT = 0x00000005,
    /** @~english
     * The reverberation style typical of a KTV venue.
     */
     /** @~chinese
     * KTV。
     */
    AUDIO_REVERB_KTV = 0x00000006,
    /** @~english
     * The reverberation style typical of a recording studio.
     */
     /** @~chinese
     * 录音棚。
     */
    AUDIO_REVERB_STUDIO = 0x00000007,
    /** @~english
     * The reverberation of the virtual stereo. The virtual stereo is an effect that renders the monophonic
     * audio as the stereo audio, so that all users in the channel can hear the stereo voice effect.
     * To achieve better virtual stereo reverberation, Agora recommends setting `profile` in `setAudioProfile`
     * as `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`.
     */
     /** @~chinese
     * 虚拟立体声。虚拟立体声是指将单声道的音轨渲染出立体声的效果，使频道内所有用户听到有空间感的声音
     * 效果。为达到更好的虚拟立体声效果，Agora 推荐在调用该方法前将 `setAudioProfile` 的 `profile` 参
     * 数设置为 `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`。
     */
    AUDIO_VIRTUAL_STEREO = 0x00200001
};
/** @~english Audio codec profile types. The default value is LC_ACC. */
/** @~chinese 用于旁路推流的输出音频的编解码规格，默认为 LC-AAC。 */
enum AUDIO_CODEC_PROFILE_TYPE
{
    /** @~english 0: LC-AAC, which is the low-complexity audio codec type. */
    /** @~chinese 0: LC-AAC 规格，表示基本音频编码规格。*/
  AUDIO_CODEC_PROFILE_LC_AAC = 0,
    /** @~english 1: HE-AAC, which is the high-efficiency audio codec type. */
    /** @~chinese 1: HE-AAC 规格，表示高效音频编码规格。*/
  AUDIO_CODEC_PROFILE_HE_AAC = 1,
};

/** @~english Remote audio states.
 */
/** @~chinese 远端音频流状态。
 */
enum REMOTE_AUDIO_STATE
{
      /** @~english 0: The remote audio is in the default state, probably due to
       * #REMOTE_AUDIO_REASON_LOCAL_MUTED (3),
       * #REMOTE_AUDIO_REASON_REMOTE_MUTED (5), or
       * #REMOTE_AUDIO_REASON_REMOTE_OFFLINE (7).
       */
       /** @~chinese 0: 远端音频流默认初始状态。在
       * #REMOTE_AUDIO_REASON_LOCAL_MUTED (3)、
       * #REMOTE_AUDIO_REASON_REMOTE_MUTED (5) 或
       * #REMOTE_AUDIO_REASON_REMOTE_OFFLINE (7) 的情况下，会报告该状态。
       */
      REMOTE_AUDIO_STATE_STOPPED = 0,  // Default state, audio is started or remote user disabled/muted audio stream
      /** @~english 1: The first remote audio packet is received.
       */
      /** @~chinese 1: 本地用户已接收远端音频首包。
       */
      REMOTE_AUDIO_STATE_STARTING = 1,  // The first audio frame packet has been received
      /** @~english 2: The remote audio stream is decoded and plays normally, probably
       * due to #REMOTE_AUDIO_REASON_NETWORK_RECOVERY (2),
       * #REMOTE_AUDIO_REASON_LOCAL_UNMUTED (4), or
       * #REMOTE_AUDIO_REASON_REMOTE_UNMUTED (6).
       */
      /** @~chinese 2: 远端音频流正在解码，正常播放。在
       * #REMOTE_AUDIO_REASON_NETWORK_RECOVERY (2)、
       * #REMOTE_AUDIO_REASON_LOCAL_UNMUTED (4) 或
       * #REMOTE_AUDIO_REASON_REMOTE_UNMUTED (6) 的情况下，会报告该状态。
       */
      REMOTE_AUDIO_STATE_DECODING = 2,  // The first remote audio frame has been decoded or fronzen state ends
      /** @~english 3: The remote audio is frozen, probably due to
       * #REMOTE_AUDIO_REASON_NETWORK_CONGESTION (1).
       */
      /** @~chinese 3: 远端音频流卡顿。在 #REMOTE_AUDIO_REASON_NETWORK_CONGESTION (1)
       * 的情况下，会报告该状态。
       */
      REMOTE_AUDIO_STATE_FROZEN = 3,    // Remote audio is frozen, probably due to network issue
      /** @~english 4: The remote audio fails to start, probably due to
       * #REMOTE_AUDIO_REASON_INTERNAL (0).
       */
      /** @~chinese 4: 远端音频流播放失败。在 #REMOTE_AUDIO_REASON_INTERNAL (0)
       * 的情况下，会报告该状态。
       */
      REMOTE_AUDIO_STATE_FAILED = 4,    // Remote audio play failed
};

/** @~english Remote audio state reasons.
 */
/** @~chinese 远端音频流状态改变的具体原因。
 */
enum REMOTE_AUDIO_STATE_REASON
{
      /** @~english 0: Internal reasons.
       */
      /** @~chinese 0: 音频状态发生改变时，会报告该原因。
       */
      REMOTE_AUDIO_REASON_INTERNAL = 0,
      /** @~english 1: Network congestion.
       */
      /** @~chinese 1: 网络阻塞。
       */
      REMOTE_AUDIO_REASON_NETWORK_CONGESTION = 1,
      /** @~english 2: Network recovery.
       */
      /** @~chinese 2: 网络恢复正常。
       */
      REMOTE_AUDIO_REASON_NETWORK_RECOVERY = 2,
      /** @~english 3: The local user stops receiving the remote audio stream or
       * disables the audio module.
       */
      /** @~chinese 3: 本地用户停止接收远端音频流或本地用户禁用音频模块。
       */
      REMOTE_AUDIO_REASON_LOCAL_MUTED = 3,
      /** @~english 4: The local user resumes receiving the remote audio stream or
       * enables the audio module.
       */
      /** @~chinese 4: 本地用户恢复接收远端音频流或本地用户启用音频模块。
       */
      REMOTE_AUDIO_REASON_LOCAL_UNMUTED = 4,
      /** @~english 5: The remote user stops sending the audio stream or disables the
       * audio module.
       */
      /** @~chinese 5: 远端用户停止发送音频流或远端用户禁用音频模块。
       */
      REMOTE_AUDIO_REASON_REMOTE_MUTED = 5,
      /** @~english 6: The remote user resumes sending the audio stream or enables the
       * audio module.
       */
      /** @~chinese 6: 远端用户恢复发送音频流或远端用户启用音频模块。
       */
      REMOTE_AUDIO_REASON_REMOTE_UNMUTED = 6,
      /** @~english 7: The remote user leaves the channel.
       */
      /** @~chinese 7: 远端用户离开频道。
       */
      REMOTE_AUDIO_REASON_REMOTE_OFFLINE = 7,
};

/** Remote video states. */
// enum REMOTE_VIDEO_STATE
// {
//     // REMOTE_VIDEO_STATE_STOPPED is not used at this version. Ignore this value.
//     // REMOTE_VIDEO_STATE_STOPPED = 0,  // Default state, video is started or remote user disabled/muted video stream
//       /** 1: The remote video is playing. */
//       REMOTE_VIDEO_STATE_RUNNING = 1,  // Running state, remote video can be displayed normally
//       /** 2: The remote video is frozen. */
//       REMOTE_VIDEO_STATE_FROZEN = 2,    // Remote video is frozen, probably due to network issue.
// };

/** @~english The state of the remote video. */
/** @~chinese 远端视频流状态。 */
enum REMOTE_VIDEO_STATE {
    /** @~english 0: The remote video is in the default state, probably due to #REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED (3), #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5), or #REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE (7).
     */
     /** @~chinese 0: 远端视频默认初始状态。在 #REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED (3)、
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5) 或
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE (7) 的情况下，会报告该状态。
     */
    REMOTE_VIDEO_STATE_STOPPED = 0,

    /** @~english 1: The first remote video packet is received.
     */
    /** @~chinese 1: 本地用户已接收远端视频首包。
     */
    REMOTE_VIDEO_STATE_STARTING = 1,

    /** @~english 2: The remote video stream is decoded and plays normally, probably due to #REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY (2), #REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED (4), #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6), or #REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY (9).
     */
    /** @~chinese 2: 远端视频流正在解码，正常播放。在
     * #REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY (2)、
     * #REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED (4)、
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6) 或
     * #REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY (9) 的情况下，
     * 会报告该状态。
     */
    REMOTE_VIDEO_STATE_DECODING = 2,

    /** @~english 3: The remote video is frozen, probably due to #REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION (1) or #REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK (8).
     */
    /** @~chinese 3: 远端视频流卡顿。在
     * #REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION (1) 或
     * #REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK (8) 的情况下，会报告该状态。
     */
    REMOTE_VIDEO_STATE_FROZEN = 3,

    /** @~english 4: The remote video fails to start, probably due to #REMOTE_VIDEO_STATE_REASON_INTERNAL (0).
     */
    /** @~chinese 4: 远端视频流播放失败。在
     * #REMOTE_VIDEO_STATE_REASON_INTERNAL (0) 的情况下，会报告该状态。
     */
    REMOTE_VIDEO_STATE_FAILED = 4
};

/** @~english The reason of the remote video state change. */
/** @~chinese 远端视频流状态切换原因。 */
enum REMOTE_VIDEO_STATE_REASON {
    /** @~english 0: Internal reasons.
     */
    /** @~chinese0: 视频状态发生改变时，会报告该原因。
     */
    REMOTE_VIDEO_STATE_REASON_INTERNAL = 0,

    /** @~english 1: Network congestion.
     */
    /** @~chinese1: 网络阻塞。
     */
    REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION = 1,

    /** @~english 2: Network recovery.
     */
    /** @~chinese 2: 网络恢复正常。
     */
    REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY = 2,

    /** @~english 3: The local user stops receiving the remote video stream or disables the video module.
     */
    /** @~chinese 3: 本地用户停止接收远端视频流或本地用户禁用视频模块。
     */
    REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED = 3,

    /** @~english 4: The local user resumes receiving the remote video stream or enables the video module.
     */
    /** @~chinese 4: 本地用户恢复接收远端视频流或本地用户启动视频模块。
     */
    REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED = 4,

    /** @~english 5: The remote user stops sending the video stream or disables the video module.
     */
    /** @~chinese 5: 远端用户停止发送视频流或远端用户禁用视频模块。
     */
    REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED = 5,

    /** @~english 6: The remote user resumes sending the video stream or enables the video module.
     */
    /** @~chinese 6: 远端用户恢复发送视频流或远端用户启用视频模块。
     */
    REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED = 6,

    /** @~english 7: The remote user leaves the channel.
     */
    /** @~chinese 7: 远端用户离开频道。
     */
    REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE = 7,

    /** @~english 8: The remote media stream falls back to the audio-only stream due to poor network conditions.
     */
    /** @~chinese 8: 弱网情况下，远端音视频流回退为音频流。
     */
    REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK = 8,

    /** @~english 9: The remote media stream switches back to the video stream after the network conditions improve.
     */
    /** @~chinese 9: 网络情况改善时，远端音频流恢复为音视频流。
     */
    REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY = 9

};

/** @~english Video frame rates. */
/** @~chinese 视频帧率。 */
enum FRAME_RATE
{
      /** @~english 1: 1 fps */
      /** @~chinese 1: 1 fps */
    FRAME_RATE_FPS_1 = 1,
        /** @~english 7: 7 fps */
        /** @~chinese 7: 7 fps */
    FRAME_RATE_FPS_7 = 7,
      /** @~english 10: 10 fps */
      /** @~chinese 10: 10 fps */
    FRAME_RATE_FPS_10 = 10,
    /** @~english 15: 15 fps */
    /** @~chinese 15: 15 fps */
    FRAME_RATE_FPS_15 = 15,
        /** @~english 24: 24 fps */
        /** @~chinese 24: 24 fps */
    FRAME_RATE_FPS_24 = 24,
    /** @~english 30: 30 fps */
    /** @~chinese 30: 30 fps */
    FRAME_RATE_FPS_30 = 30,
    /** @~english 60: 60 fps (Windows and macOS only) */
    /** @~chinese 60: 60 fps 仅适用于 Windows 和 macOS 平台。 */
    FRAME_RATE_FPS_60 = 60,
};

/** @~english Video output orientation modes.
 */
/** @~chinese 视频编码的方向模式。
 */
enum ORIENTATION_MODE {
  /** @~english 0: (Default) Adaptive mode.

   The video encoder adapts to the orientation mode of the video input device.

   - If the width of the captured video from the SDK is greater than the height, the encoder sends the video in landscape mode. The encoder also sends the rotational information of the video, and the receiver uses the rotational information to rotate the received video.
   - When you use a custom video source, the output video from the encoder inherits the orientation of the original video. If the original video is in portrait mode, the output video from the encoder is also in portrait mode. The encoder also sends the rotational information of the video to the receiver.
   */
  /** @~chinese 0: （默认）该模式下 SDK 输出的视频方向与采集到的视频方向一致。接收端会根据收到的视频旋转信息对视频进行旋转。该模式适用于接收端可以调整视频方向的场景。

   - 如果采集的视频是横屏模式，则输出的视频也是横屏模式；
   - 如果采集的视频是竖屏模式，则输出的视频也是竖屏模式。

   */
    ORIENTATION_MODE_ADAPTIVE = 0,
    /** @~english 1: Landscape mode.

     The video encoder always sends the video in landscape mode. The video encoder rotates the original video before sending it and the rotational infomation is 0. This mode applies to scenarios involving CDN live streaming.
     */
    /** @~chinese 1: 该模式下 SDK 固定输出风景（横屏）模式的视频。
    如果采集到的视频是竖屏模式，则视频编码器会对其进行裁剪。该模式适用于接收端无法调整视频方向的场景，如旁路推流。
    */
    ORIENTATION_MODE_FIXED_LANDSCAPE = 1,
    /** @~english 2: Portrait mode.

     The video encoder always sends the video in portrait mode. The video encoder rotates the original video before sending it and the rotational infomation is 0. This mode applies to scenarios involving CDN live streaming.
     */
    /** @~chinese 2: 该模式下 SDK 固定输出人像（竖屏）模式的视频。
    如果采集到的视频是横屏模式，则视频编码器会对其进行裁剪。该模式适用于接收端无法调整视频方向的场景，如旁路推流。 */

    ORIENTATION_MODE_FIXED_PORTRAIT = 2,
};

/** @~english Video degradation preferences when the bandwidth is a constraint. */
/** @~chinese 带宽受限时的视频编码降级偏好 */
enum DEGRADATION_PREFERENCE {
    /** @~english 0: (Default) Degrade the frame rate in order to maintain the video quality. */
    /** @~chinese 0:（默认）降低编码帧率以保证视频质量 */
    MAINTAIN_QUALITY = 0,
    /** @~english 1: Degrade the video quality in order to maintain the frame rate. */
    /** @~chinese 1: 降低视频质量以保证编码帧率 */
    MAINTAIN_FRAMERATE = 1,
    /** @~english 2: (For future use) Maintain a balance between the frame rate and video quality. */
    /** @~chinese 2: 预留参数，暂不支持 */
    MAINTAIN_BALANCED = 2,
};

/** @~english Stream fallback options. */
/** @~chinese 音视频流回退处理选项。 */
enum STREAM_FALLBACK_OPTIONS
{
    /** @~english 0: No fallback behavior for the local/remote video stream when the uplink/downlink network conditions are poor. The quality of the stream is not guaranteed. */
    /** @~chinese 0: 上行/下行网络较弱时，不对音视频流作回退处理，但不能保证音视频流的质量。 */
    STREAM_FALLBACK_OPTION_DISABLED = 0,
    /** @~english 1: Under poor downlink network conditions, the remote video stream, to which you subscribe, falls back to the low-stream (low resolution and low bitrate) video. You can set this option only in the \ref IRtcEngine::setRemoteSubscribeFallbackOption "setRemoteSubscribeFallbackOption" method. Nothing happens when you set this in the \ref IRtcEngine::setLocalPublishFallbackOption "setLocalPublishFallbackOption" method. */
    /** @~chinese 1: 在下行网络条件较差时只接收视频小流（低分辨率、低码率视频流）。该选项只对 \ref agora::rtc::IRtcEngine::setRemoteSubscribeFallbackOption "setRemoteSubscribeFallbackOption" 有效，对 \ref agora::rtc::IRtcEngine::setLocalPublishFallbackOption "setLocalPublishFallbackOption" 方法无效。 */
    STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW = 1,
    /** @~english 2: Under poor uplink network conditions, the published video stream falls back to audio only.
    /** @~chinese 2: 上行/下行网络较弱时，先尝试只接收视频小流（低分辨率、低码率视频流）；如果网络环境无法显示视频，则再回退到只接收远端订阅的音频流。 */
    Under poor downlink network conditions, the remote video stream, to which you subscribe, first falls back to the low-stream (low resolution and low bitrate) video; and then to an audio-only stream if the network conditions worsen.*/
    STREAM_FALLBACK_OPTION_AUDIO_ONLY = 2,
};

 /** @~english Camera capturer configuration.
 */
 /** @~chinese 摄像头采集偏好。
 */
 enum CAPTURER_OUTPUT_PREFERENCE
 {
     /** @~english 0: (Default) self-adapts the camera output parameters to the system performance and network conditions to balance CPU consumption and video preview quality.
     */
     /** @~chinese 0:（默认）自动调整采集参数。SDK 根据实际的采集设备性能及网络情况，选择合适的摄像头输出参数，在设备性能及视频预览质量之间维持平衡。
     */
     CAPTURER_OUTPUT_PREFERENCE_AUTO = 0,
     /** @~english 1: Prioritizes the system performance. The SDK chooses the dimension and frame rate of the local camera capture closest to those set by \ref IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration".
     */
     /** @~chinese 1: 优先保证设备性能。SDK 根据用户在 \ref agora::rtc::IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" 中设置编码器的分辨率和帧率，选择最接近的摄像头输出参数，从而保证设备性能。在这种情况下，预览质量接近于编码器的输出质量。
     */
     CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = 1,
     /** @~english 2: Prioritizes the local preview quality. The SDK chooses higher camera output parameters to improve the local video preview quality. This option requires extra CPU and RAM usage for video pre-processing.
     */
     /** @~chinese 2: 优先保证视频预览质量。SDK 选择较高的摄像头输出参数，从而提高预览视频的质量。在这种情况下，会消耗更多的 CPU 及内存做视频前处理。
     */
     CAPTURER_OUTPUT_PREFERENCE_PREVIEW = 2,
 };

/** @~english The priority of the remote user.
 */
/** @~chinese 远端用户的需求优先级。如果将某个用户的优先级设为高，那么发给这个用户的音视频流的优先级就会高于其他用户。
*/
enum PRIORITY_TYPE
{
  /** @~english 50: The user's priority is high.
   */
  /** @~chinese 50: 用户需求优先级为高。
   */
  PRIORITY_HIGH = 50,
  /** @~english 100: (Default) The user's priority is normal.
  */
  /** @~chinese 100:（默认）用户需求优先级为正常。
  */
  PRIORITY_NORMAL = 100,
};

/** @~english Connection states. */
/** @~chinese 网络连接状态。 */
enum CONNECTION_STATE_TYPE
{
  /** @~english 1: The SDK is disconnected from Agora's edge server.

   - This is the initial state before calling the \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" method.
   - The SDK also enters this state when the application calls the \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" method.
   */
  /** @~chinese 1: 网络连接断开。

   该状态表示 SDK 处于:
   - 调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 加入频道前的初始化阶段;
   - 或调用 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 后的离开频道阶段。
  */
  CONNECTION_STATE_DISCONNECTED = 1,
  /** @~english 2: The SDK is connecting to Agora's edge server.

   - When the application calls the \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" method, the SDK starts to establish a connection to the specified channel, triggers the \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback, and switches to the #CONNECTION_STATE_CONNECTING state.
   - When the SDK successfully joins the channel, it triggers the \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback and switches to the #CONNECTION_STATE_CONNECTED state.
   - After the SDK joins the channel and when it finishes initializing the media engine, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" callback.
   */
  /** @~chinese 2: 建立网络连接中。

   - 该状态表示 SDK 在调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 后正在与指定的频道建立连接。
   - 如果成功加入频道，App 会收到 \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" 回调，通知当前网络状态变成 #CONNECTION_STATE_CONNECTED 。
   - 建立连接后，SDK 还会初始化媒体，一切就绪后会回调 \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" 。
   */
  CONNECTION_STATE_CONNECTING = 2,
  /** @~english 3: The SDK is connected to Agora's edge server and has joined a channel. You can now publish or subscribe to a media stream in the channel.

   If the connection to the channel is lost because, for example, if the network is down or switched, the SDK automatically tries to reconnect and triggers:
   - The \ref agora::rtc::IRtcEngineEventHandler::onConnectionInterrupted "onConnectionInterrupted" callback (deprecated).
   - The \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback and switches to the #CONNECTION_STATE_RECONNECTING state.
   */
  /** @~chinese 3: 网络已连接。

   该状态表示用户已经加入频道，可以在频道内发布或订阅媒体流。

   如果因网络断开或切换而导致 SDK 与频道的连接中断，SDK 会自动重连，此时应用程序会收到：
   - \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" 回调，通知当前网络状态变成 #CONNECTION_STATE_RECONNECTING 。
   - 同时会收到 \ref agora::rtc::IRtcEngineEventHandler::onConnectionInterrupted "onConnectionInterrupted" 回调（已废弃）。
   */
  CONNECTION_STATE_CONNECTED = 3,
  /** @~english 4: The SDK keeps rejoining the channel after being disconnected from a joined channel because of network issues.

   - If the SDK cannot rejoin the channel within 10 seconds after being disconnected from Agora's edge server, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onConnectionLost "onConnectionLost" callback, stays in the #CONNECTION_STATE_RECONNECTING state, and keeps rejoining the channel.
   - If the SDK fails to rejoin the channel 20 minutes after being disconnected from Agora's edge server, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback, switches to the #CONNECTION_STATE_FAILED state, and stops rejoining the channel.
   */
  /** @~chinese 4: 重新建立网络连接中。

   该状态表示 SDK 之前曾加入过频道，但因网络等原因连接中断了，此时 SDK 会自动尝试重新接入频道。

   - 如果 SDK 无法在 10 秒内重新加入频道，则 \ref agora::rtc::IRtcEngineEventHandler::onConnectionLost "onConnectionLost" 会被触发，SDK 会一直保持在 #CONNECTION_STATE_RECONNECTING 的状态，并不断尝试重新加入频道。
   - 如果 SDK 在断开连接后，20 分钟内还是没能重新加入频道，则应用程序会收到 \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" 回调，通知的网络状态进入 #CONNECTION_STATE_FAILED ，SDK 停止尝试重连。
   */
  CONNECTION_STATE_RECONNECTING = 4,
  /** @~english 5: The SDK fails to connect to Agora's edge server or join the channel.

   You must call the \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" method to leave this state, and call the \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" method again to rejoin the channel.

   If the SDK is banned from joining the channel by Agora's edge server (through the RESTful API), the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onConnectionBanned "onConnectionBanned" (deprecated) and \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" callbacks.
   */
  /** @~chinese 5: 网络连接失败。

   该状态表示 SDK 已不再尝试重新加入频道，用户必须要调用 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 离开频道。如果用户还想重新加入频道，则需要再次调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 。

   如果 SDK 因服务器端使用 RESTful API 禁止加入频道，则应用程序会收到 \ref agora::rtc::IRtcEngineEventHandler::onConnectionBanned "onConnectionBanned" 回调（已废弃）和 \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" 回调。
   */
  CONNECTION_STATE_FAILED = 5,
};

/** @~english Reasons for a connection state change. */
/** @~chinese 引起网络连接状态发生改变的原因。 */
enum CONNECTION_CHANGED_REASON_TYPE
{
  /** @~english 0: The SDK is connecting to Agora's edge server. */
  /** @~chinese 0: 建立网络连接中。*/
  CONNECTION_CHANGED_CONNECTING = 0,
  /** @~english 1: The SDK has joined the channel successfully. */
  /** @~chinese 1: 成功加入频道。*/
  CONNECTION_CHANGED_JOIN_SUCCESS = 1,
  /** @~english 2: The connection between the SDK and Agora's edge server is interrupted. */
  /** @~chinese 2: 网络连接中断。 */
  CONNECTION_CHANGED_INTERRUPTED = 2,
  /** @~english 3: The connection between the SDK and Agora's edge server is banned by Agora's edge server. */
  /** @~chinese 3: 网络连接被服务器禁止。可能服务端踢人场景时会报这个错。*/
  CONNECTION_CHANGED_BANNED_BY_SERVER = 3,
  /** @~english 4: The SDK fails to join the channel for more than 20 minutes and stops reconnecting to the channel. */
  /** @~chinese 4: 加入频道失败。SDK 在尝试加入频道 20 分钟后还是没能加入频道，会返回该状态，并停止尝试重连。*/
  CONNECTION_CHANGED_JOIN_FAILED = 4,
  /** @~english 5: The SDK has left the channel. */
  /** @~chinese 5: 离开频道。*/
  CONNECTION_CHANGED_LEAVE_CHANNEL = 5,
  /** @~english 6: The connection failed since Appid is not valid. */
  /** @~chinese 6: 不是有效的 APP ID。请更换有效的 APP ID 重新加入频道。 */
  CONNECTION_CHANGED_INVALID_APP_ID = 6,
  /** @~english 7: The connection failed since channel name is not valid. */
  /** @~chinese 7: 不是有效的频道名。请更换有效的频道名重新加入频道。 */
  CONNECTION_CHANGED_INVALID_CHANNEL_NAME = 7,
  /** @~english 8: The connection failed since token is not valid, possibly because:

   - The App Certificate for the project is enabled in Console, but you do not use Token when joining the channel. If you enable the App Certificate, you must use a token to join the channel.
   - The uid that you specify in the \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" method is different from the uid that you pass for generating the token.
   */
  /** @~chinese 8: 生成的 Token 无效。一般有以下原因：

   - 在控制台上启用了 App Certificate，但加入频道未使用 Token。当启用了 App Certificate，必须使用 Token。
   - 在调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 加入频道时指定的 uid 与生成 Token 时传入的 uid 不一致。
   */
  CONNECTION_CHANGED_INVALID_TOKEN = 8,
  /** @~english 9: The connection failed since token is expired. */
  /** @~chinese 9: 当前使用的 Token 过期，不再有效，需要重新在你的服务端申请生成 Token。 */
  CONNECTION_CHANGED_TOKEN_EXPIRED = 9,
  /** @~english 10: The connection is rejected by server. */
  /** @~chinese 10: 此用户被服务器禁止。一般有以下原因：
   * - 用户已进入频道，再次调用加入频道的 API，例如 \ref IRtcEngine::joinChannel "joinChannel"，会返回此状态。停止调用该方法即可。
   * - 用户在调用 \ref IRtcEngine::startEchoTest "startEchoTest" 进行通话测试时尝试加入频道。等待通话测试结束后再加入频道即可。
   */
  CONNECTION_CHANGED_REJECTED_BY_SERVER = 10,
  /** @~english 11: The connection changed to reconnecting since SDK has set a proxy server. */
  /** @~chinese 11: 由于设置了代理服务器，SDK 尝试重连。 */
  CONNECTION_CHANGED_SETTING_PROXY_SERVER = 11,
  /** @~english 12: When SDK is in connection failed, the renew token operation will make it connecting. */
  /** @~chinese 12: 更新 Token 引起网络连接状态改变。 */
  CONNECTION_CHANGED_RENEW_TOKEN = 12,
  /** @~english 13: The IP Address of SDK client has changed. i.e., Network type or IP/Port changed by network operator might change client IP address. */
  /** @~chinese 13: 客户端 IP 地址变更，可能是由于网络类型，或网络运营商的 IP 或端口发生改变引起。 */
  CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED = 13,
  /** @~english 14: Timeout for the keep-alive of the connection between the SDK and Agora's edge server. The connection state changes to CONNECTION_STATE_RECONNECTING(4). */
  /** @~chinese 14: SDK 和服务器连接保活超时，进入自动重连状态 CONNECTION_STATE_RECONNECTING(4)。 */
  CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT = 14,
};

/** @~english Network type. */
/** @~chinese 网络连接类型 */
enum NETWORK_TYPE
{
  /** @~english -1: The network type is unknown. */
  /** @~chinese -1: 网络连接类型未知。 */
  NETWORK_TYPE_UNKNOWN = -1,
  /** @~english 0: The SDK disconnects from the network. */
  /** @~chinese 0: 网络连接已断开。 */
  NETWORK_TYPE_DISCONNECTED = 0,
  /** @~english 1: The network type is LAN. */
  /** @~chinese 1: 网络类型为 LAN。 */
  NETWORK_TYPE_LAN = 1,
  /** @~english 2: The network type is Wi-Fi(including hotspots). */
  /** @~chinese 2: 网络类型为 Wi-Fi(包含热点）。 */
  NETWORK_TYPE_WIFI = 2,
  /** @~english 3: The network type is mobile 2G. */
  /** @~chinese 3: 网络类型为 2G 移动网络。 */
  NETWORK_TYPE_MOBILE_2G = 3,
  /** @~english 4: The network type is mobile 3G. */
  /** @~chinese 4: 网络类型为 3G 移动网络。 */
  NETWORK_TYPE_MOBILE_3G = 4,
  /** @~english 5: The network type is mobile 4G. */
  /** @~chinese 5: 网络类型为 4G 移动网络。 */
  NETWORK_TYPE_MOBILE_4G = 5,
};

/** @~english States of the last-mile network probe test. */
/** @~chinese Last mile 质量探测结果的状态。 */
enum LASTMILE_PROBE_RESULT_STATE {
  /** @~english 1: The last-mile network probe test is complete. */
  /** @~chinese 1: 表示本次 last mile 质量探测的结果是完整的。 */
  LASTMILE_PROBE_RESULT_COMPLETE = 1,
  /** @~english 2: The last-mile network probe test is incomplete and the bandwidth estimation is not available, probably due to limited test resources. */
  /** @~chinese 2: 表示本次 last mile 质量探测未进行带宽预测，因此结果不完整。一个可能的原因是测试资源暂时受限。 */
  LASTMILE_PROBE_RESULT_INCOMPLETE_NO_BWE = 2,
  /** @~english 3: The last-mile network probe test is not carried out, probably due to poor network conditions. */
  /** @~chinese 3: 未进行 last mile 质量探测。一个可能的原因是网络连接中断。 */
  LASTMILE_PROBE_RESULT_UNAVAILABLE = 3
};
/** @~english Audio output routing. */
/** @~chinese 语音路由 */
enum AUDIO_ROUTE_TYPE {
    /** @~english Default.
     */
    /** @~chinese -1: 使用默认的语音路由 */
    AUDIO_ROUTE_DEFAULT = -1,
    /** @~english Headset.
     */
    /** @~chinese 0: 使用耳机为语音路由 */
    AUDIO_ROUTE_HEADSET = 0,
    /** @~english Earpiece.
     */
    /** @~chinese 1: 使用听筒为语音路由 */
    AUDIO_ROUTE_EARPIECE = 1,
    /** @~english Headset with no microphone.
     */
    /** @~chinese 2: 使用不带麦的耳机为语音路由 */
    AUDIO_ROUTE_HEADSET_NO_MIC = 2,
    /** @~english Speakerphone.
     */
    /** @~chinese 3: 使用手机的扬声器为语音路由 */
    AUDIO_ROUTE_SPEAKERPHONE = 3,
    /** @~english Loudspeaker.
     */
    /** @~chinese 4: 使用外接的扬声器为语音路由 */
    AUDIO_ROUTE_LOUDSPEAKER = 4,
    /** @~english Bluetooth headset.
     */
    /** @~chinese 5: 使用蓝牙耳机为语音路由 */
    AUDIO_ROUTE_BLUETOOTH = 5,
    /** @~english USB peripheral.
     */
    /** @~chinese 6: 使用 USB 外围设备为语音路由（仅适用于 macOS） */
    AUDIO_ROUTE_USB = 6,
    /** @~english HDMI peripheral.
     */
    /** @~chinese 7: 使用 HDMI 外围设备为语音路由（仅适用于 macOS） */
    AUDIO_ROUTE_HDMI = 7,
    /** @~english DisplayPort peripheral.
     */
    /** @~chinese 8: 使用 DisplayPort 外围设备为语音路由（仅适用于 macOS） */
    AUDIO_ROUTE_DISPLAYPORT = 8,
    /** @~english Apple AirPlay.
     */
    /** @~chinese 9: 使用 Apple AirPlay 为语音路由（仅适用于 macOS） */
    AUDIO_ROUTE_AIRPLAY = 9,
};

#if (defined(__APPLE__) && TARGET_OS_IOS)
/** @~english Audio session restriction. */
/** @~chinese 音频会话控制权限

Agora SDK 对 Audio Session 的控制权限
*/
enum AUDIO_SESSION_OPERATION_RESTRICTION {
    /** @~english No restriction, the SDK has full control of the audio session operations. */
    /** @~chinese 没有限制，SDK 可以完全控制 Audio Session 操作。 */
    AUDIO_SESSION_OPERATION_RESTRICTION_NONE = 0,
    /** @~english The SDK does not change the audio session category. */
    /** @~chinese SDK 不能更改 Audio Session 的 category。 */
    AUDIO_SESSION_OPERATION_RESTRICTION_SET_CATEGORY = 1,
    /** @~english The SDK does not change any setting of the audio session (category, mode, categoryOptions). */
    /** @~chinese SDK 不能更改 Audio Session 的 category，mode，categoryOptions。 */
    AUDIO_SESSION_OPERATION_RESTRICTION_CONFIGURE_SESSION = 1 << 1,
    /** @~english The SDK keeps the audio session active when leaving a channel. */
    /** @~chinese 离开某个频道时，SDK 会保持 Audio Session 处于活动状态。 */
    AUDIO_SESSION_OPERATION_RESTRICTION_DEACTIVATE_SESSION = 1 << 2,
    /** @~english The SDK does not configure the audio session anymore. */
    /** @~chinese 限制 SDK 对 Audio Session 进行任何操作，SDK 将不能再对 Audio Session 进行任何配置。 */
    AUDIO_SESSION_OPERATION_RESTRICTION_ALL = 1 << 7,
};
#endif

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
enum CAMERA_DIRECTION {
    /** @~english The rear camera. */
    /** @~chinese 0: 后置摄像头 */
    CAMERA_REAR = 0,
    /** @~english The front camera. */
    /** @~chinese 1: 前置摄像头 */
    CAMERA_FRONT = 1,
};
#endif

/** @~english The uplink or downlink last-mile network probe test result. */
/** @~chinese 上行或下行 Last mile 网络质量探测结果。 */
struct LastmileProbeOneWayResult {
  /** @~english The packet loss rate (%). */
  /** @~chinese 丢包率。 */
  unsigned int packetLossRate;
  /** @~english The network jitter (ms). */
  /** @~chinese 网络抖动 (ms)。*/
  unsigned int jitter;
  /* @~english The estimated available bandwidth (bps). */
  /** @~chinese 可用网络带宽预估 (bps)。 */
  unsigned int availableBandwidth;
};

/** @~english The uplink and downlink last-mile network probe test result. */
/** @~chinese 上行或下行 Last mile 网络质量探测结果。 */
struct LastmileProbeResult{
  /** @~english The state of the probe test. */
  /** @~chinese Last mile 质量探测结果的状态。详见: #LASTMILE_PROBE_RESULT_STATE 。
    */
  LASTMILE_PROBE_RESULT_STATE state;
  /** @~english The uplink last-mile network probe test result. */
  /** @~chinese 上行网络质量报告。详见: LastmileProbeOneWayResult 。
    */
  LastmileProbeOneWayResult uplinkReport;
  /** @~english The downlink last-mile network probe test result. */
  /** @~chinese 下行网络质量报告。详见: LastmileProbeOneWayResult 。
    */
  LastmileProbeOneWayResult downlinkReport;
  /** @~english The round-trip delay time (ms). */
  /** @~chinese 往返时延 (ms)。 */
  unsigned int rtt;
};

/** @~english Configurations of the last-mile network probe test. */
/** @~chinese Last mile 网络探测配置。 */
struct LastmileProbeConfig {
  /** @~english Sets whether or not to test the uplink network. Some users, for example, the audience in a Live-broadcast channel, do not need such a test:
  - true: test.
  - false: do not test. */
  /** @~chinese 是否探测上行网络。有些用户，如直播频道中的普通观众，不需要进行网络探测:
  - true: 探测。
  - false: 不探测。 */
  bool probeUplink;
  /** @~english Sets whether or not to test the downlink network:
  - true: test.
  - false: do not test. */
  /** @~chinese 是否探测下行网络。
  - true: 探测。
  - false: 不探测。
  */
  bool probeDownlink;
  /** @~english The expected maximum sending bitrate (bps) of the local user. The value ranges between 100000 and 5000000. We recommend setting this parameter according to the bitrate value set by \ref IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration". */
  /** @~chinese 用户期望的最高发送码率，单位为 bps，范围为 [100000, 5000000]。Agora 推荐参考 \ref agora::rtc::IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" 中的码率值设置该参数的值。  */
  unsigned int expectedUplinkBitrate;
  /** @~english The expected maximum receiving bitrate (bps) of the local user. The value ranges between 100000 and 5000000. */
  /** @~chinese 用户期望的最高接收码率，单位为 bps，范围为 [100000, 5000000]。 */
  unsigned int expectedDownlinkBitrate;
};

/** @~english Properties of the audio volume information.

 An array containing the user ID and volume information for each speaker.
 */
/** @~chinese 用户音量信息。
 */
struct AudioVolumeInfo
{
   /** @~english
    User ID of the speaker. The uid of the local user is 0.
    */
   /** @~chinese
    用户 ID。本地用户的 `uid` 为 0。
    */
    uid_t uid;
   /** @~english The volume of the speaker. The volume ranges between 0 (lowest volume) and 255 (highest volume).
    */
   /** @~chinese 用户的音量，取值范围为 [0,255]。
    */
    unsigned int volume;
    /** @~english Voice activity status of the local user.
     * - 0: The local user is not speaking.
     * - 1: The local user is speaking.
     *
     * @note
     * - The `vad` parameter cannot report the voice activity status of the remote users. In the remote users' callback, `vad` = 0.
     * - Ensure that you set `report_vad`(true) in the \ref agora::rtc::IRtcEngine::enableAudioVolumeIndication(int, int, bool) "enableAudioVolumeIndication" method to enable the voice activity detection of the local user.
     */
    /** @~chinese 本地用户的人声状态。
     * - 0：本地无人声。
     * - 1：本地有人声。
     *
     * @note
     * - `vad` 无法报告远端用户的人声状态。对于远端用户，`vad` 的值始终为 0。
     * - 如需使用此参数，请在调用 \ref agora::rtc::IRtcEngine::enableAudioVolumeIndication(int, int, bool) "enableAudioVolumeIndication" 时设置 `report_vad` 为 `true`。
     */
    unsigned int vad;
    /** @~english The channel ID, which indicates which channel the speaker is in.
     */
    /** @~chinese 用户所在频道的频道名称。
     */
    const char * channelId;
};

/** @~english Statistics of the channel.
 */
/** @~chinese 通话相关的统计信息。
 */
struct RtcStats
{
  /** @~english
   Call duration (s), represented by an aggregate value.
   */
  /** @~chinese
   本地用户通话时长（秒），累计值。
   */
    unsigned int duration;
    /** @~english
     Total number of bytes transmitted, represented by an aggregate value.
     */
    /** @~chinese
     * 发送字节数（bytes），累计值。
     */
    unsigned int txBytes;
    /** @~english
     Total number of bytes received, represented by an aggregate value.
     */
    /** @~chinese
     * 接收字节数（bytes），累计值。
     */
    unsigned int rxBytes;
     /** @~english Total number of audio bytes sent (bytes), represented
     * by an aggregate value.
     */
     /** @~chinese 发送音频字节数（bytes），累计值。
     */
    unsigned int txAudioBytes;
    /** @~english Total number of video bytes sent (bytes), represented
     * by an aggregate value.
     */
    /** @~chinese 发送视频字节数（bytes），累计值。
     */
    unsigned int txVideoBytes;
    /** @~english Total number of audio bytes received (bytes) before
     * network countermeasures, represented by an aggregate value.
     */
    /** @~chinese 接收音频字节数（bytes），累计值。
     */
    unsigned int rxAudioBytes;
    /** @~english Total number of video bytes received (bytes),
     * represented by an aggregate value.
     */
    /** @~chinese 接收视频字节数（bytes），累计值。
     */
    unsigned int rxVideoBytes;

    /** @~english
     Transmission bitrate (Kbps), represented by an instantaneous value.
     */
    /** @~chinese
     发送码率（Kbps），瞬时值。
     */
    unsigned short txKBitRate;
    /** @~english
     Receive bitrate (Kbps), represented by an instantaneous value.
     */
    /** @~chinese 接收码率（Kbps），瞬时值。
     */
    unsigned short rxKBitRate;
    /** @~english
     Audio receive bitrate (Kbps), represented by an instantaneous value.
     */
    /** @~chinese 音频接收码率 (Kbps），瞬时值。
     */
    unsigned short rxAudioKBitRate;
    /** @~english
     Audio transmission bitrate (Kbps), represented by an instantaneous value.
     */
    /** @~chinese 音频发送码率 (Kbps），瞬时值。
     */
    unsigned short txAudioKBitRate;
    /** @~english
     Video receive bitrate (Kbps), represented by an instantaneous value.
     */
    /** @~chinese 视频接收码率 (Kbps），瞬时值。
     */
    unsigned short rxVideoKBitRate;
    /** @~english
     Video transmission bitrate (Kbps), represented by an instantaneous value.
     */
    /** @~chinese 视频发送码率 (Kbps），瞬时值。
    */
    unsigned short txVideoKBitRate;
    /** @~english Client-server latency (ms)
     */
    /** @~chinese 客户端接入服务器延时 (毫秒)。
     */
    unsigned short lastmileDelay;
    /** @~english The packet loss rate (%) from the local client to Agora's edge server,
     * before using the anti-packet-loss method.
     */
    /** @~chinese 使用抗丢包技术前，客户端上行发送到服务器丢包率 (%)
     */
    unsigned short txPacketLossRate;
    /** @~english The packet loss rate (%) from Agora's edge server to the local client,
     * before using the anti-packet-loss method.
     */
    /** @~chinese 使用抗丢包技术前，服务器下行发送到客户端丢包率 (%)
     */
    unsigned short rxPacketLossRate;
    /** @~english Number of users in the channel.

     - Communication profile: The number of users in the channel.
     - Live broadcast profile:

         -  If the local user is an audience: The number of users in the channel = The number of hosts in the channel + 1.
         -  If the user is a host: The number of users in the channel = The number of hosts in the channel.
     */
    /** @~chinese 当前频道内的用户人数。

     - 通信场景下，当前频道内的用户人数。
     - 直播场景下，
         - 如果本地用户为观众，为频道内的主播人数 + 1；
         - 如果本地用户为主播，为频道内的主播人数。
     */
    unsigned int userCount;
    /** @~english
     Application CPU usage (%).
     */
    /** @~chinese 当前 App 的 CPU 使用率 (%)。 */
    double cpuAppUsage;
    /** @~english
     System CPU usage (%).

     In the multi-kernel environment, this member represents the average CPU usage.
     The value **=** 100 **-** System Idle Progress in Task Manager (%).
     */
    /** @~chinese 当前系统的 CPU 使用率 (%)。

     在多核环境中，该成员指多核 CPU 的平均使用率。
     计算方式为 100 - 任务管理中显示的系统空闲进程 CPU（%）。
     */
    double cpuTotalUsage;
    /** @~english The round-trip time delay from the client to the local router.
     */
    /** @~chinese 客户端到本地路由器的往返时延 (ms)。 */
    int gatewayRtt;
    /** @~english
     The memory usage ratio of the app (%).
     @note This value is for reference only. Due to system limitations, you may not get the value of this member.
     */
    /**
     * @~chinese 当前 App 的内存占比 (%)。
     *
     * @note 该值仅作参考。受系统限制可能无法获取。
     */
    double memoryAppUsageRatio;
    /** @~english
     The memory usage ratio of the system (%).
     @note This value is for reference only. Due to system limitations, you may not get the value of this member.
     */
    /** @~chinese
     * 当前系统的内存占比 (%)
     *
     * @note 该值仅作参考。受系统限制可能无法获取。
     */
    double memoryTotalUsageRatio;
    /** @~english
     The memory usage of the app (KB).
     @note This value is for reference only. Due to system limitations, you may not get the value of this member.
     */
    /** @~chinese
     * 当前 App 的内存大小 (KB)
     *
     * @note 该值仅作参考。受系统限制可能无法获取。
     */
    int memoryAppUsageInKbytes;
  RtcStats()
      : duration(0)
      , txBytes(0)
      , rxBytes(0)
      , txAudioBytes(0)
      , txVideoBytes(0)
      , rxAudioBytes(0)
      , rxVideoBytes(0)
      , txKBitRate(0)
      , rxKBitRate(0)
      , rxAudioKBitRate(0)
      , txAudioKBitRate(0)
      , rxVideoKBitRate(0)
      , txVideoKBitRate(0)
      , lastmileDelay(0)
      , txPacketLossRate(0)
      , rxPacketLossRate(0)
      , userCount(0)
      , cpuAppUsage(0)
      , cpuTotalUsage(0)
      , gatewayRtt(0)
      , memoryAppUsageRatio(0)
      , memoryTotalUsageRatio(0)
      , memoryAppUsageInKbytes(0) {}
};

/** @~english Quality change of the local video in terms of target frame rate and target bit rate since last count.
  */
/** @~chinese 自上次统计后本地视频质量的自适应情况（基于目标帧率和目标码率）。*/
enum QUALITY_ADAPT_INDICATION {
  /** @~english The quality of the local video stays the same. */
  /** @~chinese 本地视频质量不变。 */
  ADAPT_NONE = 0,
  /** @~english The quality improves because the network bandwidth increases. */
  /** @~chinese 因网络带宽增加，本地视频质量改善。 */
  ADAPT_UP_BANDWIDTH = 1,
  /** @~english The quality worsens because the network bandwidth decreases. */
  /** @~chinese 因网络带宽减少，本地视频质量变差。 */
  ADAPT_DOWN_BANDWIDTH = 2,
};

/** @~english The error code in CHANNEL_MEDIA_RELAY_ERROR. */
/** @~chinese 跨频道媒体流转发出错的错误码。*/
enum CHANNEL_MEDIA_RELAY_ERROR {
    /** @~english 0: The state is normal.
     */
    /** @~chinese 0: 一切正常。
     */
    RELAY_OK = 0,
    /** @~english 1: An error occurs in the server response.
     */
    /** @~chinese 1: 服务器回应出错。
     */
    RELAY_ERROR_SERVER_ERROR_RESPONSE = 1,
    /** @~english 2: No server response. You can call the
     * \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" method to
     * leave the channel.
     */
    /** @~chinese 2: 服务器无回应。
     * 你可以调用
     * \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 方法离开频道。
     */
    RELAY_ERROR_SERVER_NO_RESPONSE = 2,
    /** @~english 3: The SDK fails to access the service, probably due to limited
     * resources of the server.
     */
    /** @~chinese 3: SDK 无法获取服务，可能是因为服务器资源有限导致。
     */
    RELAY_ERROR_NO_RESOURCE_AVAILABLE = 3,
    /** @~english 4: Fails to send the relay request.
     */
    /** @~chinese 4: 发起跨频道转发媒体流请求失败。
     */
    RELAY_ERROR_FAILED_JOIN_SRC = 4,
    /** @~english 5: Fails to accept the relay request.
     */
    /** @~chinese 5: 接受跨频道转发媒体流请求失败。
     */
    RELAY_ERROR_FAILED_JOIN_DEST = 5,
    /** @~english 6: The server fails to receive the media stream.
     */
    /** @~chinese 6: 服务器接收跨频道转发媒体流失败。
     */
    RELAY_ERROR_FAILED_PACKET_RECEIVED_FROM_SRC = 6,
    /** @~english 7: The server fails to send the media stream.
     */
    /** @~chinese 7: 服务器发送跨频道转发媒体流失败。
     */
    RELAY_ERROR_FAILED_PACKET_SENT_TO_DEST = 7,
    /** @~english 8: The SDK disconnects from the server due to poor network
     * connections. You can call the \ref agora::rtc::IRtcEngine::leaveChannel
     * "leaveChannel" method to leave the channel.
     */
    /** @~chinese 8: SDK 因网络质量不佳与服务器断开。你可以调用
     * \ref agora::rtc::IRtcEngine::leaveChannel
     * "leaveChannel" 方法离开当前频道。
     */
    RELAY_ERROR_SERVER_CONNECTION_LOST = 8,
    /** @~english 9: An internal error occurs in the server.
     */
    /** @~chinese 9: 服务器内部出错。
     */
    RELAY_ERROR_INTERNAL_ERROR = 9,
    /** @~english 10: The token of the source channel has expired.
     */
    /** @~chinese 10: 源频道的 Token 已过期。
     */
    RELAY_ERROR_SRC_TOKEN_EXPIRED = 10,
    /** @~english 11: The token of the destination channel has expired.
     */
    /** @~chinese 11: 目标频道的 Token 已过期。
     */
    RELAY_ERROR_DEST_TOKEN_EXPIRED = 11,
};

/** @~english The event code in CHANNEL_MEDIA_RELAY_EVENT. */
/** @~chinese 跨频道媒体流转发事件码。 */
enum CHANNEL_MEDIA_RELAY_EVENT {
    /** @~english 0: The user disconnects from the server due to poor network
     * connections.
     */
    /** @~chinese 0: 网络中断导致用户与服务器连接断开。
     */
    RELAY_EVENT_NETWORK_DISCONNECTED = 0,
    /** @~english 1: The network reconnects.
     */
    /** @~chinese 1: 用户与服务器建立连接。
     */
    RELAY_EVENT_NETWORK_CONNECTED = 1,
    /** @~english 2: The user joins the source channel.
     */
    /** @~chinese 2: 用户已加入源频道。
     */
    RELAY_EVENT_PACKET_JOINED_SRC_CHANNEL = 2,
    /** @~english 3: The user joins the destination channel.
     */
    /** @~chinese 3: 用户已加入目标频道。
     */
    RELAY_EVENT_PACKET_JOINED_DEST_CHANNEL = 3,
    /** @~english 4: The SDK starts relaying the media stream to the destination channel.
     */
    /** @~chinese 4: SDK 开始向目标频道发送数据包。
     */
    RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL = 4,
    /** @~english 5: The server receives the video stream from the source channel.
     */
    /** @~chinese 5: 服务器收到了频道发送的视频流。
     */
    RELAY_EVENT_PACKET_RECEIVED_VIDEO_FROM_SRC = 5,
    /** @~english 6: The server receives the audio stream from the source channel.
     */
    /** @~chinese 6: 服务器收到了频道发送的音频流。
     */
    RELAY_EVENT_PACKET_RECEIVED_AUDIO_FROM_SRC = 6,
    /** @~english 7: The destination channel is updated.
     */
    /** @~chinese 7: 目标频道已更新。
     */
    RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL = 7,
    /** @~english 8: The destination channel update fails due to internal reasons.
     */
    /** @~chinese 8: 内部原因导致目标频道更新失败。
     */
    RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_REFUSED = 8,
    /** @~english 9: The destination channel does not change, which means that the
     * destination channel fails to be updated.
     */
    /** @~chinese 9: 目标频道未发生改变，即目标频道更新失败。
     */
    RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_NOT_CHANGE = 9,
    /** @~english 10: The destination channel name is NULL.
     */
    /** @~chinese 10: 目标频道名为 NULL。
     */
    RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_IS_NULL = 10,
    /** @~english 11: The video profile is sent to the server.
     */
    /** @~chinese 11: 视频属性已发送至服务器。
     */
    RELAY_EVENT_VIDEO_PROFILE_UPDATE = 11,
};

/** @~english The state code in CHANNEL_MEDIA_RELAY_STATE. */
/** @~chinese 跨频道媒体流转发状态码。 */
enum CHANNEL_MEDIA_RELAY_STATE {
    /** @~english 0: The SDK is initializing.
     */
    /** @~chinese 0: 初始状态。
     */
    RELAY_STATE_IDLE = 0,
    /** @~english 1: The SDK tries to relay the media stream to the destination channel.
     */
    /** @~chinese 1: SDK 尝试跨频道。
     */
    RELAY_STATE_CONNECTING = 1,
    /** @~english 2: The SDK successfully relays the media stream to the destination
     * channel.
     */
    /** @~chinese 2: 源频道主播成功加入目标频道。
     */
    RELAY_STATE_RUNNING = 2,
    /** @~english 3: A failure occurs. See the details in code.
     */
    /** @~chinese 3: 发生异常，详见提示的错误信息。
     */
    RELAY_STATE_FAILURE = 3,
};

/** @~english Statistics of the local video stream.
 */
/** @~chinese 本地视频流上传统计信息。
 */
struct LocalVideoStats
{
  /** @~english Bitrate (Kbps) sent in the reported interval, which does not include
   * the bitrate of the retransmission video after packet loss.
   */
  /** @~chinese 实际发送码率 (Kbps)。不包含丢包后重传视频等的发送码率。
   */
  int sentBitrate;
  /** @~english Frame rate (fps) sent in the reported interval, which does not include
   * the frame rate of the retransmission video after packet loss.
   */
  /** @~chinese 实际发送帧率 (fps)。不包含丢包后重传视频等的发送帧率。
   */
  int sentFrameRate;
  /** @~english The encoder output frame rate (fps) of the local video.
   */
  /** @~chinese 本地视频编码器的输出帧率，单位为 fps。
   */
  int encoderOutputFrameRate;
  /** @~english The render output frame rate (fps) of the local video.
   */
  /** @~chinese 本地视频渲染器的输出帧率，单位为 fps
   */
  int rendererOutputFrameRate;
  /** @~english The target bitrate (Kbps) of the current encoder. This value is estimated by the SDK based on the current network conditions.
    */
  /** @~chinese 当前编码器的目标编码码率 (Kbps)，该码率为 SDK 根据当前网络状况预估的一个值。
     */
  int targetBitrate;
  /** @~english The target frame rate (fps) of the current encoder.
    */
  /** @~chinese 当前编码器的目标编码帧率 (fps)。
     */
  int targetFrameRate;
  /** @~english Quality change of the local video in terms of target frame rate and
   * target bit rate in this reported interval. See #QUALITY_ADAPT_INDICATION.
   */
  /** @~chinese 统计周期内本地视频质量（基于目标帧率和目标码率）的自适应情况。详见 #QUALITY_ADAPT_INDICATION 。*/
  QUALITY_ADAPT_INDICATION qualityAdaptIndication;
  /** @~english The encoding bitrate (Kbps), which does not include the bitrate of the
   * re-transmission video after packet loss.
   */
  /** @~chinese 视频编码码率（Kbps）。不包含丢包后重传视频等的编码码率。
     */
  int encodedBitrate;
  /** @~english The width of the encoding frame (px).
   */
  /** @~chinese 视频编码宽度（px）。
     */
  int encodedFrameWidth;
  /** @~english The height of the encoding frame (px).
   */
  /** @~chinese 视频编码高度（px）。
     */
  int encodedFrameHeight;
  /** @~english The value of the sent frames, represented by an aggregate value.
   */
  /** @~chinese 发送的视频帧数，累计值。
   */
  int encodedFrameCount;
  /** @~english The codec type of the local video:
   * - VIDEO_CODEC_VP8 = 1: VP8.
   * - VIDEO_CODEC_H264 = 2: (Default) H.264.
   */
  /** @~chinese 视频的编码类型：
     * - VIDEO_CODEC_VP8 = 1: VP8。
     * - VIDEO_CODEC_H264 = 2: （默认值）H.264。
     */
  VIDEO_CODEC_TYPE codecType;
};

/** @~english Statistics of the remote video stream.
 */
/** @~chinese 远端视频流的统计信息。
 */
struct RemoteVideoStats
{
  /** @~english
 User ID of the remote user sending the video streams.
 */
  /** @~chinese 用户 ID，指定是哪个用户的视频流。 */
    uid_t uid;
    /** @~english **DEPRECATED** Time delay (ms).
     *
     * In scenarios where audio and video is synchronized, you can use the value of
     * `networkTransportDelay` and `jitterBufferDelay` in `RemoteAudioStats` to know the delay statistics of the remote video.
     */
    /** @~chinese @deprecated
     延时 (毫秒)。

     在有音画同步机制的音视频场景中，你可以参考 RemoteAudioStats 里的 `networkTransportDelay`
     和 `jitterBufferDelay` 成员的值，了解视频的延迟数据。
     */
    int delay;
/** @~english
 Width (pixels) of the video stream.
 */
/** @~chinese 视频流宽（像素）。*/
	int width;
  /** @~english
 Height (pixels) of the video stream.
 */
  /** @~chinese 视频流高（像素）。*/
	int height;
  /** @~english
 Bitrate (Kbps) received since the last count.
 */
  /** @~chinese （上次统计后）接收到的码率(Kbps)。*/
	int receivedBitrate;
  /** @~english The decoder output frame rate (fps) of the remote video.
   */
  /** @~chinese 远端视频解码器的输出帧率，单位为 fps。
   */
	int decoderOutputFrameRate;
  /** @~english The render output frame rate (fps) of the remote video.
   */
  /** @~chinese 远端视频渲染器的输出帧率，单位为 fps。
   */
  int rendererOutputFrameRate;
  /** @~english Packet loss rate (%) of the remote video stream after using the anti-packet-loss method.
   */
  /** @~chinese 远端视频在使用抗丢包技术之后的丢包率(%)。
   */
  int packetLossRate;
  /** @~english The type of the remote video stream: #REMOTE_VIDEO_STREAM_TYPE
   */
  /** @~chinese 视频流类型：大流或小流，详见 #REMOTE_VIDEO_STREAM_TYPE。*/
  REMOTE_VIDEO_STREAM_TYPE rxStreamType;
  /** @~english
   The total freeze time (ms) of the remote video stream after the remote user joins the channel.
   In a video session where the frame rate is set to no less than 5 fps, video freeze occurs when
   the time interval between two adjacent renderable video frames is more than 500 ms.
   */
  /** @~chinese
  远端用户在加入频道后发生视频卡顿的累计时长（ms）。
  通话过程中，视频帧率设置不低于 5 fps 时，连续渲染的两帧视频之间间隔超过 500 ms，为一次视频卡顿。
  */
    int totalFrozenTime;
  /** @~english
   The total video freeze time as a percentage (%) of the total time when the video is available.
   */
  /** @~chinese 远端用户在加入频道后发生视频卡顿的累计时长占视频总有效时长的百分比 (%)。视频有效时长是指远端用户加入频道后视频未被停止发送或禁用的时长。 */
    int frozenRate;
    /** @~english
    The total time (ms) when the remote user in the Communication profile or the remote
    broadcaster in the Live-broadcast profile neither stops sending the video stream nor
    disables the video module after joining the channel.

    @since v3.0.1
    */
    /** @~chinese
    视频有效时长（毫秒），即远端用户/主播加入频道后，既没有停止发送视频流，也没有禁用视频模块的通话时长。

    @since v3.0.1
    */
    int totalActiveTime;
};

/** @~english Audio statistics of the local user */
/** @~chinese 本地音频统计数据。 */
struct LocalAudioStats
{
    /** @~english The number of channels.
     */
    /** @~chinese 声道数。
     */
    int numChannels;
    /** @~english The sample rate (Hz).
     */
    /** @~chinese 发送的采样率，单位为 Hz。
     */
    int sentSampleRate;
    /** @~english The average sending bitrate (Kbps).
     */
    /** @~chinese 发送码率的平均值，单位为 Kbps。
     */
    int sentBitrate;
};

/** @~english Audio statistics of a remote user */
/** @~chinese 远端用户的音频统计 */
struct RemoteAudioStats
{
    /** @~english User ID of the remote user sending the audio streams.
     *
     */
    /** @~chinese 用户 ID，指定是哪个用户/主播的音频流。 */
    uid_t uid;
    /** @~english Audio quality received by the user: #QUALITY_TYPE.
     */
    /** @~chinese 远端用户发送的音频流质量：#QUALITY_TYPE 。 */
    int quality;
    /** @~english Network delay (ms) from the sender to the receiver.
     */
    /** @~chinese 音频发送端到接收端的网络延迟（毫秒）。*/
    int networkTransportDelay;
    /** @~english Network delay (ms) from the receiver to the jitter buffer.
     */
    /** @~chinese 接收端到网络抖动缓冲的网络延迟（毫秒）。
     */
    int jitterBufferDelay;
    /** @~english The audio frame loss rate in the reported interval.
     */
    /** @~chinese 统计周期内的远端音频流的丢帧率 (%)。 */
    int audioLossRate;
    /** @~english The number of channels.
     */
    /** @~chinese 声道数。 */
    int numChannels;
    /** @~english The sample rate (Hz) of the received audio stream in the reported
     * interval.
     */
    /** @~chinese 统计周期内接收到的远端音频采样率。 */
    int receivedSampleRate;
    /** @~english The average bitrate (Kbps) of the received audio stream in the
     * reported interval. */
    /** @~chinese 接收流在统计周期内的平均码率（Kbps）。 */
    int receivedBitrate;
    /** @~english The total freeze time (ms) of the remote audio stream after the remote user joins the channel. In a session, audio freeze occurs when the audio frame loss rate reaches 4%.
     */
    /** @~chinese 远端用户在加入频道后发生音频卡顿的累计时长（ms）。通话过程中，音频丢帧率达到 4% 即记为一次音频卡顿。
     */
    int totalFrozenTime;
    /** @~english The total audio freeze time as a percentage (%) of the total time when the audio is available. */
    /** @~chinese 远端用户在加入频道后发生音频卡顿的累计时长占音频总有效时长的百分比 (%)。音频有效时长是指远端用户加入频道后音频未被停止发送或禁用的时长。 */
    int frozenRate;
    /** @~english The total time (ms) when the remote user in the Communication profile or the remote broadcaster in
     the Live-broadcast profile neither stops sending the audio stream nor disables the audio module after joining the channel.
     */
    /** @~chinese 音频有效时长（毫秒），即远端用户/主播加入频道后，既没有停止发送音频流，也没有禁用音频模块的通话时长。 */
    int totalActiveTime;
};

/** @~english
 * Video dimensions.
 */
/** @~chinese 视频尺寸。
 */
struct VideoDimensions {
    /** @~english Width (pixels) of the video. */
    /** @~chinese 视频宽度，单位为像素。*/
    int width;
      /** @~english Height (pixels) of the video. */
      /** @~chinese 视频高度，单位为像素。*/
    int height;
    VideoDimensions()
        : width(640), height(480)
    {}
    VideoDimensions(int w, int h)
        : width(w), height(h)
    {}
};

/** @~english (Recommended) The standard bitrate set in the \ref IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" method.

 In this mode, the bitrates differ between the live broadcast and communication profiles:

 - Communication profile: The video bitrate is the same as the base bitrate.
 - Live broadcast profile: The video bitrate is twice the base bitrate.

 */
/** @~chinese \ref agora::rtc::IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" 的标准码率。

（推荐）标准码率模式。该模式下，视频在通信和直播场景下的码率有所不同：
- 通信场景下，码率与基准码率一致；
- 直播场景下，码率对照基准码率翻倍。
 */
const int STANDARD_BITRATE = 0;

/** @~english The compatible bitrate set in the \ref IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" method.

 The bitrate remains the same regardless of the channel profile. If you choose this mode in the Live-broadcast profile, the video frame rate may be lower than the set value.
 */
/** @~chinese \ref agora::rtc::IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" 的兼容码率。

 适配码率模式。该模式下，视频在通信和直播场景下的码率均与基准码率一致。直播下如果选择该模式，视频帧率可能会低于设置的值。
 */
const int COMPATIBLE_BITRATE = -1;

/** @~english Use the default minimum bitrate.
 */
/** @~chinese 使用系统默认最低编码码率。
 */
const int DEFAULT_MIN_BITRATE = -1;

/** @~english Video encoder configurations.
 */
/** @~chinese 视频编码器配置的属性。
 */
struct VideoEncoderConfiguration {
  /** @~english The video frame dimensions (px) used to specify the video quality and measured by the total number of pixels along a frame's width and height: VideoDimensions. The default value is 640 x 360.
  */
  /** @~chinese 视频编码的分辨率 (px)。视频编码的像素，用于衡量编码质量，以长 &times; 宽表示，默认值为 640 x 360。用户可以自行设置分辨率: VideoDimensions 。
  */
    VideoDimensions dimensions;
    /** @~english The frame rate of the video: #FRAME_RATE. The default value is 15.

     Note that we do not recommend setting this to a value greater than 30.
    */
    /** @~chinese 视频编码的帧率: #FRAME_RATE 。默认值为 15。Agora 不建议设置成高于 30 的值。
    */
    FRAME_RATE frameRate;
    /** @~english The minimum frame rate of the video. The default value is -1.
     */
    /** @~chinese 视频的最小帧率。默认值为 -1。
   */
    int minFrameRate;
    /** @~english The video encoding bitrate (Kbps).

     Choose one of the following options:

     - #STANDARD_BITRATE: (Recommended) The standard bitrate.
        - The Communication profile: the encoding bitrate equals the base bitrate.
        - The Live-broadcast profile: the encoding bitrate is twice the base bitrate.
     - #COMPATIBLE_BITRATE: The compatible bitrate: the bitrate stays the same regardless of the profile.

     The Communication profile prioritizes smoothness, while the Live-broadcast profile prioritizes video quality (requiring a higher bitrate). We recommend setting the bitrate mode as #STANDARD_BITRATE to address this difference.

     The following table lists the recommended video encoder configurations, where the base bitrate applies to the Communication profile. Set your bitrate based on this table. If you set a bitrate beyond the proper range, the SDK automatically sets it to within the range.

     @note
     In the following table, **Base Bitrate** applies to the Communication profile, and **Live Bitrate** applies to the Live-broadcast profile.

     | Resolution             | Frame Rate (fps) | Base Bitrate (Kbps)                    | Live Bitrate (Kbps)                    |
     |------------------------|------------------|----------------------------------------|----------------------------------------|
     | 160 * 120              | 15               | 65                                     | 130                                    |
     | 120 * 120              | 15               | 50                                     | 100                                    |
     | 320 * 180              | 15               | 140                                    | 280                                    |
     | 180 * 180              | 15               | 100                                    | 200                                    |
     | 240 * 180              | 15               | 120                                    | 240                                    |
     | 320 * 240              | 15               | 200                                    | 400                                    |
     | 240 * 240              | 15               | 140                                    | 280                                    |
     | 424 * 240              | 15               | 220                                    | 440                                    |
     | 640 * 360              | 15               | 400                                    | 800                                    |
     | 360 * 360              | 15               | 260                                    | 520                                    |
     | 640 * 360              | 30               | 600                                    | 1200                                   |
     | 360 * 360              | 30               | 400                                    | 800                                    |
     | 480 * 360              | 15               | 320                                    | 640                                    |
     | 480 * 360              | 30               | 490                                    | 980                                    |
     | 640 * 480              | 15               | 500                                    | 1000                                   |
     | 480 * 480              | 15               | 400                                    | 800                                    |
     | 640 * 480              | 30               | 750                                    | 1500                                   |
     | 480 * 480              | 30               | 600                                    | 1200                                   |
     | 848 * 480              | 15               | 610                                    | 1220                                   |
     | 848 * 480              | 30               | 930                                    | 1860                                   |
     | 640 * 480              | 10               | 400                                    | 800                                    |
     | 1280 * 720             | 15               | 1130                                   | 2260                                   |
     | 1280 * 720             | 30               | 1710                                   | 3420                                   |
     | 960 * 720              | 15               | 910                                    | 1820                                   |
     | 960 * 720              | 30               | 1380                                   | 2760                                   |
     | 1920 * 1080            | 15               | 2080                                   | 4160                                   |
     | 1920 * 1080            | 30               | 3150                                   | 6300                                   |
     | 1920 * 1080            | 60               | 4780                                   | 6500                                   |
     | 2560 * 1440            | 30               | 4850                                   | 6500                                   |
     | 2560 * 1440            | 60               | 6500                                   | 6500                                   |
     | 3840 * 2160            | 30               | 6500                                   | 6500                                   |
     | 3840 * 2160            | 60               | 6500                                   | 6500                                   |

     */
    /** @~chinese 视频编码码率，单位为 Kbps:

     你可以根据场景需要参照下表手动设置你想要的码率。若设置的视频码率超出合理范围，SDK 会自动按照合理区间处理码率。你也可以直接选择如下任意一种模式进行设置：
     - #STANDARD_BITRATE : (推荐) 标准码率模式。该模式下，视频在通信和直播场景下的码率有所不同：
       - 通信场景下，码率与基准码率一致；
       - 直播场景下，码率对照基准码率翻倍。
     - #COMPATIBLE_BITRATE : 适配码率模式。该模式下，视频在通信和直播场景下的码率均与基准码率一致。直播下如果选择该模式，视频帧率可能会低于设置的值。

     Agora 在通信和直播场景下采用不同的编码方式，以提升不同场景下的用户体验。通信场景保证流畅，而直播场景则更注重画面质量，因此直播场景对码率的需求大于通信场景。所以声网推荐将该参数设置为 #STANDARD_BITRATE 。

     |分辨率                   |帧率（fps）        |通信码率（Kbps）                           |直播码率（Kbps）                          |
     |------------------------|------------------|----------------------------------------|----------------------------------------|
     | 160 &times; 120        | 15               | 65                                     | 130                                    |
     | 120 &times; 120        | 15               | 50                                     | 100                                    |
     | 320 &times; 180        | 15               | 140                                    | 280                                    |
     | 180 &times; 180        | 15               | 100                                    | 200                                    |
     | 240 &times; 180        | 15               | 120                                    | 240                                    |
     | 320 &times; 240        | 15               | 200                                    | 400                                    |
     | 240 &times; 240        | 15               | 140                                    | 280                                    |
     | 424 &times; 240        | 15               | 220                                    | 440                                    |
     | 640 &times; 360        | 15               | 400                                    | 800                                    |
     | 360 &times; 360        | 15               | 260                                    | 520                                    |
     | 640 &times; 360        | 30               | 600                                    | 1200                                   |
     | 360 &times; 360        | 30               | 400                                    | 800                                    |
     | 480 &times; 360        | 15               | 320                                    | 640                                    |
     | 480 &times; 360        | 30               | 490                                    | 980                                    |
     | 640 &times; 480        | 15               | 500                                    | 1000                                   |
     | 480 &times; 480        | 15               | 400                                    | 800                                    |
     | 640 &times; 480        | 30               | 750                                    | 1500                                   |
     | 480 &times; 480        | 30               | 600                                    | 1200                                   |
     | 848 &times; 480        | 15               | 610                                    | 1220                                   |
     | 848 &times; 480        | 30               | 930                                    | 1860                                   |
     | 640 &times; 480        | 10               | 400                                    | 800                                    |
     | 1280 &times; 720       | 15               | 1130                                   | 2260                                   |
     | 1280 &times; 720       | 30               | 1710                                   | 3420                                   |
     | 960 &times; 720        | 15               | 910                                    | 1820                                   |
     | 960 &times; 720        | 30               | 1380                                   | 2760                                   |
     | 1920 &times; 1080      | 15               | 2080                                   | 4160                                   |
     | 1920 &times; 1080      | 30               | 3150                                   | 6300                                   |
     | 1920 &times; 1080      | 60               | 4780                                   | 6500                                   |
     | 2560 &times; 1440      | 30               | 4850                                   | 6500                                   |
     | 2560 &times; 1440      | 60               | 6500                                   | 6500                                   |
     | 3840 &times; 2160      | 30               | 6500                                   | 6500                                   |
     | 3840 &times; 2160      | 60               | 6500                                   | 6500                                   |

     @note 该表中的基准码率适用于通信场景。直播场景下通常需要较大码率来提升视频质量。声网推荐通过设置 #STANDARD_BITRATE 模式来实现。你也可以直接将码率值设为基准码率值 &times; 2。
     */
    int bitrate;
    /** @~english The minimum encoding bitrate (Kbps).

     The SDK automatically adjusts the encoding bitrate to adapt to the network conditions. Using a value greater than the default value forces the video encoder to output high-quality images but may cause more packet loss and hence sacrifice the smoothness of the video transmission. That said, unless you have special requirements for image quality, Agora does not recommend changing this value.

     @note This parameter applies only to the Live-broadcast profile.
     */
    /** @~chinese 最低编码码率，单位为 Kbps。

     SDK 会根据网络状况自动调整视频编码码率。将参数设为高于默认值可强制视频编码器输出高质量图片，但在网络状况不佳情况下可能导致网络丢包并影响视频播放的流畅度造成卡顿。因此如非对画质有特殊需求，声网建议不要修改该参数的值。

     @note 该参数仅适用于直播场景。
     */
    int minBitrate;
    /** @~english The video orientation mode of the video: #ORIENTATION_MODE.
    */
    /** @~chinese 视频编码的方向模式: #ORIENTATION_MODE 。
     */
    ORIENTATION_MODE orientationMode;
    /** @~english The video encoding degradation preference under limited bandwidth: #DEGRADATION_PREFERENCE.
     */
    /** @~chinese 带宽受限时，视频编码降级偏好: #DEGRADATION_PREFERENCE 。
     */
    DEGRADATION_PREFERENCE degradationPreference;
    /** @~english Sets the mirror mode of the published local video stream. It only affects the video that the remote user sees. See #VIDEO_MIRROR_MODE_TYPE

    @note: The SDK disables the mirror mode by default.
    */
    /** @~chinese 设置本地发送视频的镜像模式，只影响远端用户看到的视频画面。详见 #VIDEO_MIRROR_MODE_TYPE。

    @note 默认关闭镜像模式。
     */
    VIDEO_MIRROR_MODE_TYPE mirrorMode;

    VideoEncoderConfiguration(
        const VideoDimensions& d, FRAME_RATE f,
        int b, ORIENTATION_MODE m, VIDEO_MIRROR_MODE_TYPE mr = VIDEO_MIRROR_MODE_AUTO)
        : dimensions(d), frameRate(f), minFrameRate(-1), bitrate(b),
          minBitrate(DEFAULT_MIN_BITRATE), orientationMode(m),
          degradationPreference(MAINTAIN_QUALITY), mirrorMode(mr)
    {}
    VideoEncoderConfiguration(
        int width, int height, FRAME_RATE f,
        int b, ORIENTATION_MODE m, VIDEO_MIRROR_MODE_TYPE mr = VIDEO_MIRROR_MODE_AUTO)
        : dimensions(width, height), frameRate(f),
          minFrameRate(-1), bitrate(b),
          minBitrate(DEFAULT_MIN_BITRATE), orientationMode(m),
          degradationPreference(MAINTAIN_QUALITY), mirrorMode(mr)
    {}
    VideoEncoderConfiguration()
        : dimensions(640, 480)
        , frameRate(FRAME_RATE_FPS_15)
        , minFrameRate(-1)
        , bitrate(STANDARD_BITRATE)
        , minBitrate(DEFAULT_MIN_BITRATE)
        , orientationMode(ORIENTATION_MODE_ADAPTIVE)
        , degradationPreference(MAINTAIN_QUALITY)
        , mirrorMode(VIDEO_MIRROR_MODE_AUTO)
    {}
};

/** @~english The video and audio properties of the user displaying the video in the CDN live. Agora supports a maximum of 17 transcoding users in a CDN streaming channel.
*/
/** @~chinese TranscodingUser 用于管理参与旁路直播的音视频转码合图的用户。最多支持 17 人同时参与转码合图。
*/
typedef struct TranscodingUser {
  /** @~english User ID of the user displaying the video in the CDN live.
  */
  /** @~chinese 旁路主播的用户 ID。
  */
    uid_t uid;

/** @~english Horizontal position (pixel) of the video frame relative to the top left corner.
*/
/** @~chinese 屏幕里该区域相对左上角的横坐标绝对值 (pixel)。*/
    int x;
    /** @~english Vertical position (pixel) of the video frame relative to the top left corner.
    */
    /** @~chinese 屏幕里该区域相对左上角的纵坐标绝对值 (pixel)。*/
    int y;
    /** @~english Width (pixel) of the video frame. The default value is 360.
    */
    /** @~chinese 视频帧宽度 (pixel)。默认值为 360。*/
    int width;
    /** @~english Height (pixel) of the video frame. The default value is 640.
    */
    /** @~chinese 视频帧高度 (pixel)。默认值为640。*/
    int height;

    /** @~english The layer index of the video frame. An integer. The value range is [0, 100].

     - 0: (Default) Bottom layer.
     - 100: Top layer.

     @note
     - If zOrder is beyond this range, the SDK reports #ERR_INVALID_ARGUMENT.
     - As of v2.3, the SDK supports zOrder = 0.
     */
    /** @~chinese 视频帧图层编号。

     - 0:（默认）表示该区域图像位于最下层，
     - 100: 表示该区域图像位于最上层。

     @note
     - 如果取值小于 0 或大于 100，会返回错误 #ERR_INVALID_ARGUMENT 。
     - 从 v2.3 开始，支持将 zOrder 设置为 0。
     */
    int zOrder;
    /** @~english The transparency level of the user's video. The value ranges between 0 and 1.0:

     - 0: Completely transparent
     - 1.0: (Default) Opaque
     */
    /** @~chinese 直播视频上用户视频的透明度。

     - 0: 该区域图像完全透明；
     - 1:（默认）该区域图像完全不透明。
    */
    double alpha;
    /** @~english The audio channel of the sound. The default value is 0:

     - 0: (Default) Supports dual channels at most, depending on the upstream of the broadcaster.
     - 1: The audio stream of the broadcaster uses the FL audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.
     - 2: The audio stream of the broadcaster uses the FC audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.
     - 3: The audio stream of the broadcaster uses the FR audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.
     - 4: The audio stream of the broadcaster uses the BL audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.
     - 5: The audio stream of the broadcaster uses the BR audio channel. If the upstream of the broadcaster uses multiple audio channels, these channels are mixed into mono first.

     @note If your setting is not 0, you may need a specialized player.
     */
    /** @~chinese 音频所在声道。取值范围为 [0, 5]，默认值为 0：

     - 0: (推荐) 默认混音设置，最多支持双声道，与主播端上行音频相关。
     - 1: 对应主播的音频，推流中位于 FL 声道。如果主播端上行音频是多声道，会先把多声道混音成单声道。
     - 2: 对应主播的音频，推流中位于 FC 声道。如果主播端上行音频是多声道，会先把多声道混音成单声道。
     - 3: 对应主播的音频，推流中位于 FR 声道。如果主播端上行音频是多声道，会先把多声道混音成单声道。
     - 4: 对应主播的音频，推流中位于 BL 声道。如果主播端上行音频是多声道，会先把多声道混音成单声道。
     - 5: 对应主播的音频，推流中位于 BR 声道。如果主播端上行音频是多声道，会先把多声道混音成单声道。

     @note 选项不为 0 时，需要特殊的播放器支持。
     */
    int audioChannel;
    TranscodingUser()
        : uid(0)
        , x(0)
        , y(0)
        , width(0)
        , height(0)
        , zOrder(0)
        , alpha(1.0)
        , audioChannel(0)
    {}

} TranscodingUser;

/** @~english Image properties.

 The properties of the watermark and background images.
 */
/** @~chinese 图像属性。

用于设置直播视频的水印和背景图片的属性。
*/
typedef struct RtcImage {
    RtcImage() :
       url(NULL),
       x(0),
       y(0),
       width(0),
       height(0)
    {}
    /** @~english HTTP/HTTPS URL address of the image on the broadcasting video. The maximum length of this parameter is 1024 bytes. */
    /** @~chinese 直播视频上图片的 HTTP/HTTPS 地址。字符长度不得超过 1024 字节。*/
    const char* url;
    /** @~english Horizontal position of the image from the upper left of the broadcasting video. */
    /** @~chinese 水印或背景图片在视频帧左上角的横轴坐标。*/
    int x;
    /** @~english Vertical position of the image from the upper left of the broadcasting video. */
    /** @~chinese 水印或背景图片在视频帧左上角的纵轴坐标。*/
    int y;
    /** @~english Width of the image on the broadcasting video. */
    /** @~chinese 水印或背景图片在视频帧上的宽度。*/
    int width;
    /** @~english Height of the image on the broadcasting video. */
    /** @~chinese 水印或背景图片在视频帧上的高度。*/
    int height;
} RtcImage;
/** @~english A struct for managing CDN live audio/video transcoding settings.
*/
/** @~chinese LiveTranscoding 定义。
*/
typedef struct LiveTranscoding {
   /** @~english The width of the video in pixels. The default value is 360.
    * - When pushing video streams to the CDN, ensure that `width` is at least 64; otherwise, the Agora server adjusts the value to 64.
    * - When pushing audio streams to the CDN, set `width` and `height` as 0.
    */
   /** @~chinese 推流视频的总宽度，默认值 360，单位为像素。
     * - 如果推视频流，`width` 值不得低于 64，否则 Agora 会调整为 64。
     * - 如果推音频流，请将 `width` 和 `height` 设为 0。
     */
    int width;
    /** @~english The height of the video in pixels. The default value is 640.
     * - When pushing video streams to the CDN, ensure that `height` is at least 64; otherwise, the Agora server adjusts the value to 64.
     * - When pushing audio streams to the CDN, set `width` and `height` as 0.
    */
    /** @~chinese 推流视频的总高度，默认值 640，单位为像素。
     * - 如果推视频流，`height` 值不得低于 64，否则 Agora 会调整为 64。
     * - 如果推音频流，请将 `width` 和 `height` 设为 0。
    */
    int height;
    /** @~english Bitrate of the CDN live output video stream. The default value is 400 Kbps.

	Set this parameter according to the Video Bitrate Table. If you set a bitrate beyond the proper range, the SDK automatically adapts it to a value within the range.
    */
    /** @~chinese 用于旁路推流的输出视频的码率。 单位为 Kbps。 400 Kbps 为默认值。
    用户可以根据 Video Bitrate 参考表中的码率值进行设置；如果设置的码率超出合理范围，Agora 服务器会在合理区间内自动调整码率值。
    */
    int videoBitrate;
    /** @~english Frame rate of the output video stream set for the CDN live broadcast. The default value is 15 fps, and the value range is (0,30].

	@note The Agora server adjusts any value over 30 to 30.
    */
    /** @~chinese 用于旁路推流的输出视频的帧率。取值范围是 (0,30]，单位为 fps。15 fps 为默认值。

     @note Agora 会将所有高于 30 fps 的帧率统一设为 30 fps。
    */
    int videoFramerate;

    /** @~english **DEPRECATED** Latency mode:

     - true: Low latency with unassured quality.
     - false: (Default) High latency with assured quality.
     */
    /** @~chinese @deprecated

     - true: 低延时，不保证画质；
     - false:（默认值）高延时，保证画质。
     */
    bool lowLatency;

    /** @~english Video GOP in frames. The default value is 30 fps.
    */
    /** @~chinese 用于旁路直播的输出视频的 GOP。单位为帧。默认值为 30 fps。
    */
    int videoGop;
    /** @~english Self-defined video codec profile: #VIDEO_CODEC_PROFILE_TYPE.

	@note If you set this parameter to other values, Agora adjusts it to the default value of 100.
    */
    /** @~chinese 用于旁路推流的输出视频的编码规格: #VIDEO_CODEC_PROFILE_TYPE 。

     @note 如果你将这个参数设为其他值，Agora 会将其设为默认值 100。
    */
    VIDEO_CODEC_PROFILE_TYPE videoCodecProfile;
    /** @~english The background color in RGB hex value. Value only. Do not include a preceeding #. For example, 0xFFB6C1 (light pink). The default value is 0x000000 (black).
     */
    /** @~chinese 用于旁路直播的输出视频的背景色，格式为 RGB 定义下的十六进制整数，不要带 # 号，如 0xFFB6C1 表示浅粉色。默认0x000000，黑色。
     */
    unsigned int backgroundColor;
    /** @~english The number of users in the live broadcast.
     */
    /** @~chinese 参与合图的用户数量，默认 0。
    */
    unsigned int userCount;
    /** @~english TranscodingUser
    */
    /** @~chinese TranscodingUser
    */
    TranscodingUser *transcodingUsers;
    /** @~english Reserved property. Extra user-defined information to send SEI for the H.264/H.265 video stream to the CDN live client. Maximum length: 4096 Bytes.

     For more information on SEI frame, see [SEI-related questions](https://docs.agora.io/en/faq/sei).
     */
    /** @~chinese 预留参数：用户自定义的发送到旁路推流客户端的信息。用于填充 H.264/H.265 视频中 SEI 帧内容。长度限制 4096 字节。关于 SEI 的详细信息，详见 [SEI 帧相关问题](https://docs.agora.io/cn/faq/sei)。
     */
    const char *transcodingExtraInfo;

    /** @~english **DEPRECATED** The metadata sent to the CDN live client defined by the RTMP or HTTP-FLV metadata.
     */
    /** @~chinese @deprecated 发送给 CDN 客户端的 metadata。
     */
    const char *metadata;
    /** @~english The watermark image added to the CDN live publishing stream.

	Ensure that the format of the image is PNG. Once a watermark image is added, the audience of the CDN live publishing stream can see the watermark image. See RtcImage.
    */
    /** @~chinese 用于旁路直播的输出视频上的水印图片。

    添加后所有旁路直播的观众都可以看到水印。水印图片的定义详见 RtcImage 。必须为 PNG 格式。
     */
    RtcImage* watermark;
    /** @~english The background image added to the CDN live publishing stream.

     Once a background image is added, the audience of the CDN live publishing stream can see the background image. See RtcImage.
    */
    /** @~chinese 用于旁路直播的输出视频上的背景图片。添加后所有旁路直播的观众都可以看到背景图片。背景图片的定义详见 RtcImage 。
     */
    RtcImage* backgroundImage;
    /** @~english Self-defined audio-sample rate: #AUDIO_SAMPLE_RATE_TYPE.
    */
    /** @~chinese 自定义音频采样率: #AUDIO_SAMPLE_RATE_TYPE 。
     */
    AUDIO_SAMPLE_RATE_TYPE audioSampleRate;
    /** @~english Bitrate of the CDN live audio output stream. The default value is 48 Kbps, and the highest value is 128.
     */
    /** @~chinese 用于旁路推流的输出音频的码率。单位为 Kbps，默认值为 48，最大值为 128。
    */
    int audioBitrate;
    /** @~english The numbder of audio channels for the CDN live stream. Agora recommends choosing 1 (mono), or 2 (stereo) audio channels. Special players are required if you choose option 3, 4, or 5:

     - 1: (Default) Mono.
     - 2: Stereo.
     - 3: Three audio channels.
     - 4: Four audio channels.
     - 5: Five audio channels.
     */
    /** @~chinese 用于旁路推流的输出音频的声道数，默认值为 1。取值范围为 [1,5] 中的整型，建议取 1 或 2：

     - 1: 单声道（默认）
     - 2: 双声道
     - 3: 三声道
     - 4: 四声道
     - 5: 五声道
     */
    int audioChannels;
    /** @~english Self-defined audio codec profile: #AUDIO_CODEC_PROFILE_TYPE.
     */
    /** @~chinese 用于旁路推流的输出音频的编码规格: #AUDIO_CODEC_PROFILE_TYPE 。
     */

    AUDIO_CODEC_PROFILE_TYPE audioCodecProfile;


    LiveTranscoding()
        : width(360)
        , height(640)
        , videoBitrate(400)
        , videoFramerate(15)
        , lowLatency(false)
        , videoGop(30)
        , videoCodecProfile(VIDEO_CODEC_PROFILE_HIGH)
        , backgroundColor(0x000000)
        , userCount(0)
        , transcodingUsers(NULL)
        , transcodingExtraInfo(NULL)
        , metadata(NULL)
        , watermark(NULL)
        , backgroundImage(NULL)
        , audioSampleRate(AUDIO_SAMPLE_RATE_48000)
        , audioBitrate(48)
        , audioChannels(1)
        , audioCodecProfile(AUDIO_CODEC_PROFILE_LC_AAC)
    {}
} LiveTranscoding;

 /** @~english Camera capturer configuration.
  */
/** @~chinese 摄像头采集偏好设置
 */
 struct CameraCapturerConfiguration{

     /** @~english Camera capturer preference settings. See: #CAPTURER_OUTPUT_PREFERENCE. */
     /** @~chinese 摄像头采集偏好，详见 #CAPTURER_OUTPUT_PREFERENCE */
     CAPTURER_OUTPUT_PREFERENCE preference;
     #if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
     /** @~english Camera direction settings (for Android/iOS only). See: #CAMERA_DIRECTION. */
     /** @~chinese （仅适用于 Android 和 iOS 平台）摄像头方向，详见 #CAMERA_DIRECTION */
     CAMERA_DIRECTION cameraDirection;
     #endif
 };

/** @~english Configuration of the imported live broadcast voice or video stream.
 */
/** @~chinese InjectStreamConfig 定义。
*/
struct InjectStreamConfig {
    /** @~english Width of the added stream in the live broadcast. The default value is 0 (same width as the original stream).
     */
    /** @~chinese 添加进入直播的外部视频源宽度。默认值为 0，即保留视频源原始宽度。*/
    int width;
    /** @~english Height of the added stream in the live broadcast. The default value is 0 (same height as the original stream).
     */
    /** @~chinese 添加进入直播的外部视频源高度。默认值为 0，即保留视频源原始高度。*/
    int height;
    /** @~english Video GOP of the added stream in the live broadcast in frames. The default value is 30 fps.
     */
    /** @~chinese 用于旁路直播的输出视频的 GOP。单位为帧。默认值为 30 帧。*/
    int videoGop;
    /** @~english Video frame rate of the added stream in the live broadcast. The default value is 15 fps.
     */
    /** @~chinese 添加进入直播的外部视频源帧率。默认值为 15 fps。*/
    int videoFramerate;
    /** @~english Video bitrate of the added stream in the live broadcast. The default value is 400 Kbps.

     @note The setting of the video bitrate is closely linked to the resolution. If the video bitrate you set is beyond a reasonable range, the SDK sets it within a reasonable range.
     */
    /** @~chinese 添加进入直播的外部视频源码率。默认设置为 400 Kbps。

     @note 视频码率的设置与分辨率相关。如果设置的视频码率超出合理范围，SDK 会按照合理区间自动设置码率。
     */
    int videoBitrate;
    /** @~english Audio-sample rate of the added stream in the live broadcast: #AUDIO_SAMPLE_RATE_TYPE. The default value is 48000 Hz.

     @note We recommend setting the default value.
     */
    /** @~chinese 添加进入直播的外部音频采样率。默认值为 48000。详见 #AUDIO_SAMPLE_RATE_TYPE 。

     @note 声网建议目前采用默认值，不要自行设置。
     */
    AUDIO_SAMPLE_RATE_TYPE audioSampleRate;
    /** @~english Audio bitrate of the added stream in the live broadcast. The default value is 48.

     @note We recommend setting the default value.
     */
    /** @~chinese 添加进入直播的外部音频码率。默认值为 48 Kbps。

     @note 声网建议目前采用默认值，不要自行设置。
     */
    int audioBitrate;
    /** @~english Audio channels in the live broadcast.

     - 1: (Default) Mono
     - 2: Two-channel stereo

     @note We recommend setting the default value.
     */
    /** @~chinese 添加进入直播的外部音频频道。

     - 1: 单声道（默认）
     - 2: 双声道

     @note 声网建议目前采用默认值，不要自行设置。
     */
    int audioChannels;

    // width / height default set to 0 means pull the stream with its original resolution
    InjectStreamConfig()
        : width(0)
        , height(0)
        , videoGop(30)
        , videoFramerate(15)
        , videoBitrate(400)
        , audioSampleRate(AUDIO_SAMPLE_RATE_48000)
        , audioBitrate(48)
        , audioChannels(1)
    {}
};
/** @~english The definition of ChannelMediaInfo.
 */
/** @~chinese ChannelMediaInfo 类定义。
 */
struct ChannelMediaInfo {
    /** @~english The channel name.
     */
    /** @~chinese 频道名。
     */
	const char* channelName;
    /** @~english The token that enables the user to join the channel.
     */
    /** @~chinese 能加入频道的 Token。
     */
	const char* token;
    /** @~english The user ID.
     */
    /** @~chinese 用户 ID。
     */
	uid_t uid;
};

/** @~english The definition of ChannelMediaRelayConfiguration.
 */
/** @~chinese ChannelMediaRelayConfiguration 类定义。
 */
struct ChannelMediaRelayConfiguration {
    /** @~english Pointer to the information of the source channel: ChannelMediaInfo. It contains the following members:
     * - `channelName`: The name of the source channel. The default value is `NULL`, which means the SDK applies the name of the current channel.
     * - `uid`: ID of the broadcaster whose media stream you want to relay. The default value is 0, which means the SDK generates a random UID. You must set it as 0.
     * - `token`: The token for joining the source channel. It is generated with the `channelName` and `uid` you set in `srcInfo`.
     *   - If you have not enabled the App Certificate, set this parameter as the default value `NULL`, which means the SDK applies the App ID.
     *   - If you have enabled the App Certificate, you must use the `token` generated with the `channelName` and `uid`, and the `uid` must be set as 0.
     */
    /** @~chinese 源频道信息指针 ChannelMediaInfo，包含如下成员：
     * - `channelName`：源频道名。默认值为 `NULL`，表示 SDK 填充当前的频道名。
     * - `uid`：标识源频道中的转发媒体流的 UID。默认值为 0，表示 SDK 随机分配一个 `uid`。请确保设为 0。
     * - `token`：能加入源频道的 `token`。由你在 `srcInfo` 中设置的 `channelName` 和 `uid` 生成。
     *   - 如未启用 App Certificate，可直接将该参数设为默认值 `NULL`，表示 SDK 填充 App ID。
     *   - 如已启用 App Certificate，则务必填入使用 `channelName` 和 `uid` 生成的 `token`，且其中的 `uid` 必须为 0。
     */
	ChannelMediaInfo *srcInfo;
    /** @~english Pointer to the information of the destination channel: ChannelMediaInfo. It contains the following members:
     * - `channelName`: The name of the destination channel.
     * - `uid`: ID of the broadcaster in the destination channel. The value ranges from 0 to (2<sup>32</sup>-1). To avoid UID conflicts, this `uid` must be different from any other UIDs in the destination channel. The default value is 0, which means the SDK generates a random UID.
     * - `token`: The token for joining the destination channel. It is generated with the `channelName` and `uid` you set in `destInfos`.
     *   - If you have not enabled the App Certificate, set this parameter as the default value `NULL`, which means the SDK applies the App ID.
     *   - If you have enabled the App Certificate, you must use the `token` generated with the `channelName` and `uid`.
     */
    /** @~chinese 目标频道信息指针 ChannelMediaInfo，包含如下成员：
     * - `channelName`：目标频道的频道名。
     * - `uid`：标识目标频道中的转发媒体流的 UID。取值范围为 0 到（2<sup>32</sup>-1），请确保与目标频道中的所有 UID 不同。默认值为 0，
     * 表示 SDK 随机分配一个 UID。请确保不要将该参数设为目标频道的主播的 UID，并与目标频道中的所有 UID 都不同。
     * - `token`：能加入目标频道的 `token`。由你在 `destInfos` 中设置的 `channelName` 和 `uid` 生成。
     *   - 如未启用 App Certificate，可直接将该参数设为默认值 `NULL`，表示 SDK 填充 App ID。
     *   - 如已启用 App Certificate，则务必填入使用 `channelName` 和 `uid` 生成的 `token`。
     */
	ChannelMediaInfo *destInfos;
    /** @~english The number of destination channels. The default value is 0, and the
     * value range is [0,4). Ensure that the value of this parameter
     * corresponds to the number of ChannelMediaInfo structs you define in
     * `destInfos`.
     */
    /** @~chinese 目标频道数量，默认值为 0，取值范围为 [0，4]。该参数应与你在 `destInfo`
     * 中定义的 ChannelMediaInfo 数组的数目一致。
     */
	int destCount;

	ChannelMediaRelayConfiguration()
			: srcInfo(nullptr)
			, destInfos(nullptr)
			, destCount(0)
	{}
};

/**  @~english **DEPRECATED** Lifecycle of the CDN live video stream.
*/
/**  @~chinese @deprecated 服务端转码推流的生命周期。
*/
enum RTMP_STREAM_LIFE_CYCLE_TYPE
{
  /** @~english Bind to the channel lifecycle. If all hosts leave the channel, the CDN live streaming stops after 30 seconds.
  */
  /** @~chinese @deprecated 跟频道生命周期绑定，即频道内所有主播离开，服务端转码推流会在 30 秒之后停止。
  */
	RTMP_STREAM_LIFE_CYCLE_BIND2CHANNEL = 1,
  /** @~english Bind to the owner of the RTMP stream. If the owner leaves the channel, the CDN live streaming stops immediately.
  */
  /** @~chinese @deprecated 跟启动服务端转码推流的主播生命周期绑定，即该主播离开，服务端转码推流会立即停止。
  */
	RTMP_STREAM_LIFE_CYCLE_BIND2OWNER = 2,
};

/** @~english Content hints for screen sharing.
*/
/** @~chinese 屏幕共享的内容类型 */
enum VideoContentHint
{
    /** @~english (Default) No content hint.
     */
    /** @~chinese （默认）无指定的内容类型 */
    CONTENT_HINT_NONE,
    /** @~english Motion-intensive content. Choose this option if you prefer smoothness or when you are sharing a video clip, movie, or video game.
     */
    /** @~chinese 内容类型为动画。当共享的内容是视频、电影或视频游戏时，推荐选择该内容类型。 */
    CONTENT_HINT_MOTION,
    /** @~english Motionless content. Choose this option if you prefer sharpness or when you are sharing a picture, PowerPoint slide, or text.
     */
    /** @~chinese 内容类型为细节。当共享的内容是图片或文字时，推荐选择该内容类型。 */
    CONTENT_HINT_DETAILS
};

/** @~english The relative location of the region to the screen or window.
 */
/** @~chinese 待共享区域相对于整个屏幕或窗口的位置，如不填，则表示共享整个屏幕或窗口。
 */
struct Rectangle
{
    /** @~english The horizontal offset from the top-left corner.
    */
    /** @~chinese 左上角的横向偏移。
    */
    int x;
    /** @~english The vertical offset from the top-left corner.
    */
    /** @~chinese 左上角的纵向偏移。
    */
    int y;
    /** @~english The width of the region.
    */
    /** @~chinese 待共享区域的宽。
    */
    int width;
    /** @~english The height of the region.
    */
    /** @~chinese 待共享区域的高。
    */
    int height;

    Rectangle(): x(0), y(0), width(0), height(0) {}
    Rectangle(int xx, int yy, int ww, int hh): x(xx), y(yy), width(ww), height(hh) {}
};

/** @~english **DEPRECATED** Definition of the rectangular region. */
/** @~chinese @deprecated 定义矩形区域。*/
typedef struct Rect {
    /** @~english Y-axis of the top line.
     */
    /** @~chinese 矩形上边的 Y 轴坐标。
     */
    int top;
    /** @~english X-axis of the left line.
     */
    /** @~chinese 矩形左边的 X 轴坐标。
     */
    int left;
    /** @~english Y-axis of the bottom line.
     */
    /** @~chinese 矩形下边的 Y 轴坐标。
     */
    int bottom;
    /** @~english X-axis of the right line.
     */
    /** @~chinese 矩形右边的 X 轴坐标。
     */
    int right;

    Rect(): top(0), left(0), bottom(0), right(0) {}
    Rect(int t, int l, int b, int r): top(t), left(l), bottom(b), right(r) {}
} Rect;

/** @~english The options of the watermark image to be added. */
/** @~chinese 待添加的水印图片的设置选项。 */
typedef struct WatermarkOptions {
    /** @~english Sets whether or not the watermark image is visible in the local video preview:
     * - true: (Default) The watermark image is visible in preview.
     * - false: The watermark image is not visible in preview.
     */
    /** @~chinese 是否将水印设为预览时本地可见：
     - true：(默认) 预览时水印本地可见；
     - false：预览时水印本地不可见。
     */
    bool visibleInPreview;
    /** @~english
     * The watermark position in the landscape mode. See Rectangle.
     * For detailed information on the landscape mode, see the advanced guide *Video Rotation*.
     */
    /** @~chinese 视频编码模式为横屏时（详见进阶功能《视频采集旋转》）的水印坐标。详见 Rectangle 。
     */
    Rectangle positionInLandscapeMode;
    /** @~english
     * The watermark position in the portrait mode. See Rectangle.
     * For detailed information on the portrait mode, see the advanced guide *Video Rotation*.
     */
    /** @~chinese 视频编码模式为竖屏时（详见进阶功能《视频采集旋转》）的水印坐标。详见 Rectangle 。
    */
    Rectangle positionInPortraitMode;

    WatermarkOptions()
        : visibleInPreview(true)
        , positionInLandscapeMode(0, 0, 0, 0)
        , positionInPortraitMode(0, 0, 0, 0)
    {}
} WatermarkOptions;

/** @~english Screen sharing encoding parameters.
*/
/** @~chinese 屏幕共享的参数配置。
 */
struct ScreenCaptureParameters
{
    /** @~english The maximum encoding dimensions of the shared region in terms of width * height.

	 The default value is 1920 * 1080 pixels, that is, 2073600 pixels. Agora uses the value of this parameter to calculate the charges.

	 If the aspect ratio is different between the encoding dimensions and screen dimensions, Agora applies the following algorithms for encoding. Suppose the encoding dimensions are 1920 x 1080:

	 - If the value of the screen dimensions is lower than that of the encoding dimensions, for example, 1000 * 1000, the SDK uses 1000 * 1000 for encoding.
	 - If the value of the screen dimensions is higher than that of the encoding dimensions, for example, 2000 * 1500, the SDK uses the maximum value under 1920 * 1080 with the aspect ratio of the screen dimension (4:3) for encoding, that is, 1440 * 1080.
     */
    /** @~chinese 屏幕共享视频发送的最大像素值。

     默认值为 1920 &times; 1080，即 2073600 像素。该像素值为计费标准。

     当共享的屏幕分辨率宽高比与该值设置不一致时，SDK 按如下策略进行编码。假设 dimensions 为 1920 &times; 1080：

     - 如果屏幕分辨率小于 dimensions，如 1000 &times; 1000，SDK 直接按 1000 &times; 1000 进行编码；
     - 如果屏幕分辨率大于 dimensions，如 2000 &times; 1500，SDK 按屏幕分辨率的宽高比，即 4：3，取 dimensions 以内的最大分辨率进行编码，即 1440 &times; 1080 。
     */
    VideoDimensions dimensions;
    /** @~english The frame rate (fps) of the shared region.

	The default value is 5. We do not recommend setting this to a value greater than 15.
     */
    /** @~chinese 共享视频的帧率，单位为 fps；默认值为 5，建议不要超过 15。
     */
    int frameRate;
    /** @~english The bitrate (Kbps) of the shared region.

	The default value is 0 (the SDK works out a bitrate according to the dimensions of the current screen).
     */
    /** @~chinese 共享视频的码率，单位为 Kbps；默认值为 0，表示 SDK 根据当前共享屏幕的分辨率计算出一个合理的值。
     */
    int bitrate;
    /** @~english Sets whether or not to capture the mouse for screen sharing:

	- true: (Default) Capture the mouse.
	- false: Do not capture the mouse.
     */
    /** @~chinese 是否采集鼠标用于屏幕共享

     - true: （默认）采集鼠标
     - false: 不采集鼠标
     */
    bool captureMouseCursor;

    ScreenCaptureParameters() : dimensions(1920, 1080), frameRate(5), bitrate(STANDARD_BITRATE), captureMouseCursor(true) {}
    ScreenCaptureParameters(const VideoDimensions& d, int f, int b, bool c) : dimensions(d), frameRate(f), bitrate(b), captureMouseCursor(c) {}
    ScreenCaptureParameters(int width, int height, int f, int b, bool c) : dimensions(width, height), frameRate(f), bitrate(b), captureMouseCursor(c) {}
};

/** @~english Video display settings of the VideoCanvas class.
*/
/** @~chinese VideoCanvas 类的视频显示设置。
*/
struct VideoCanvas
{
    /** @~english Video display window (view).
     */
    /** @~chinese 视频显示窗口 (view)。
  */
    view_t view;
    /** @~english The rendering mode of the video view. See RENDER_MODE_TYPE
     */
    /** @~chinese 视频渲染模式，详见 #RENDER_MODE_TYPE
    */
    int renderMode;
    /** @~english The unique channel name for the AgoraRTC session in the string format. The string length must be less than 64 bytes. Supported character scopes are:
     - All lowercase English letters: a to z.
     - All uppercase English letters: A to Z.
     - All numeric characters: 0 to 9.
     - The space character.
     - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".

     @note
     - The default value is the empty string "". Use the default value if the user joins the channel using the \ref IRtcEngine::joinChannel "joinChannel" method in the IRtcEngine class. The `VideoCanvas` struct defines the video canvas of the user in the channel.
     - If the user joins the channel using the \ref IRtcEngine::joinChannel "joinChannel" method in the IChannel class, set this parameter as the `channelId` of the `IChannel` object. The `VideoCanvas` struct defines the video canvas of the user in the channel with the specified channel ID.
     */
    /** @~chinese 能标识频道的频道名，长度在 64 字节以内的字符。以下为支持的字符集范围（共 89 个字符）：
     - 26 个小写英文字母 a~z；
     - 26 个大写英文字母 A~Z；
     - 10 个数字 0~9；
     - 空格；
     - "!"、"#"、"$"、"%"、"&"、"("、")"、"+"、"-"、":"、";"、"<"、"="、"."、">"、"?"、"@"、"["、"]"、"^"、"_"、" {"、"}"、"|"、"~"、","。

     @note
     - 该参数默认值为空字符 ""。如果用户是通过 IRtcEngine 类的 \ref IRtcEngine::joinChannel "joinChannel" 方法加入频道的，则将参数设为默认值，表示该用户在频道内的渲染视图。
     - 如果用户是通过 IChannel 类的 \ref IChannel::joinChannel "joinChannel" 方法加入频道的，则将该参数设为该 IChannel 类对应的 `channelId`，表示该用户在该 `channelId` 对应频道内的渲染视图。
     */
    char channelId[MAX_CHANNEL_ID_LENGTH];
    /** @~english The user ID. */
    /** @~chinese 用户 ID */
    uid_t uid;
    void *priv; // private data (underlying video engine denotes it)
    /** @~english The mirror mode of the video view. See VIDEO_MIRROR_MODE_TYPE
     @note
     - For the mirror mode of the local video view: If you use a front camera, the SDK enables the mirror mode by default; if you use a rear camera, the SDK disables the mirror mode by default.
     - For the mirror mode of the remote video view: The SDK disables the mirror mode by default.
    */
    /** @~chinese 视图镜像模式，详见 #VIDEO_MIRROR_MODE_TYPE
     @note
     - 本地视图镜像模式：如果你使用前置摄像头，默认启动本地视图镜像模式；如果你使用后置摄像头，默认关闭本地视图镜像模式。
     - 远端用户视图镜像模式：默认关闭远端用户的镜像模式。
     */
    VIDEO_MIRROR_MODE_TYPE mirrorMode;

    VideoCanvas()
        : view(NULL)
        , renderMode(RENDER_MODE_HIDDEN)
        , uid(0)
        , priv(NULL)
        , mirrorMode(VIDEO_MIRROR_MODE_AUTO)
    {
        channelId[0] = '\0';
    }
    VideoCanvas(view_t v, int m, uid_t u)
        : view(v)
        , renderMode(m)
        , uid(u)
        , priv(NULL)
        , mirrorMode(VIDEO_MIRROR_MODE_AUTO)
    {
        channelId[0] = '\0';
    }
    VideoCanvas(view_t v, int m, const char *ch, uid_t u)
        : view(v)
        , renderMode(m)
        , uid(u)
        , priv(NULL)
        , mirrorMode(VIDEO_MIRROR_MODE_AUTO)
    {
        strncpy(channelId, ch, MAX_CHANNEL_ID_LENGTH);
        channelId[MAX_CHANNEL_ID_LENGTH - 1] = '\0';
    }
    VideoCanvas(view_t v, int rm, uid_t u, VIDEO_MIRROR_MODE_TYPE mm)
        : view(v)
        , renderMode(rm)
        , uid(u)
        , priv(NULL)
        , mirrorMode(mm)
    {
        channelId[0] = '\0';
    }
    VideoCanvas(view_t v, int rm, const char *ch, uid_t u, VIDEO_MIRROR_MODE_TYPE mm)
        : view(v)
        , renderMode(rm)
        , uid(u)
        , priv(NULL)
        , mirrorMode(mm)
    {
        strncpy(channelId, ch, MAX_CHANNEL_ID_LENGTH);
        channelId[MAX_CHANNEL_ID_LENGTH - 1] = '\0';
    }
};

/** @~english Image enhancement options.
*/
/** @~chinese 美颜选项。
*/
struct BeautyOptions {
    /** @~english The contrast level, used with the @p lightening parameter.
    */
    /** @~chinese 亮度明暗对比度，和参数 @p lightening 一起使用。 */
    enum LIGHTENING_CONTRAST_LEVEL
    {
        /** @~english Low contrast level. */
        /** @~chinese 低对比度。 */
        LIGHTENING_CONTRAST_LOW = 0,
        /** @~english (Default) Normal contrast level. */
        /** @~chinese 正常对比度。 */
        LIGHTENING_CONTRAST_NORMAL,
        /** @~english High contrast level. */
        /** @~chinese 高对比度。 */
        LIGHTENING_CONTRAST_HIGH
    };

/** @~english The contrast level, used with the @p lightening parameter.
*/
/** @~chinese 亮度明暗对比度,和参数 @p lightening 一起使用。
*/
LIGHTENING_CONTRAST_LEVEL lighteningContrastLevel;

/** @~english The brightness level. The value ranges from 0.0 (original) to 1.0. */
/** @~chinese 亮度，取值范围为 [0.0, 1.0]，其中 0.0 表示原始亮度。可用来实现美白等视觉效果。 */
float lighteningLevel;

/** @~english The sharpness level. The value ranges between 0 (original) and 1. This parameter is usually used to remove blemishes.
 */
/** @~chinese 平滑度，取值范围为 [0.0, 1.0]，其中 0.0 表示原始平滑等级。可用来实现祛痘、磨皮等视觉效果。
*/
float smoothnessLevel;

/** @~english The redness level. The value ranges between 0 (original) and 1. This parameter adjusts the red saturation level.
*/
/** @~chinese 红色度，取值范围为 [0.0, 1.0]，其中 0.0 表示原始红色度。可用来实现红润肤色等视觉效果。
*/
float rednessLevel;

BeautyOptions(LIGHTENING_CONTRAST_LEVEL contrastLevel, float lightening, float smoothness, float redness)
    : lighteningContrastLevel(contrastLevel),
	lighteningLevel(lightening),
    smoothnessLevel(smoothness),
    rednessLevel(redness) {}

BeautyOptions()
    : lighteningContrastLevel(LIGHTENING_CONTRAST_NORMAL),
	lighteningLevel(0),
    smoothnessLevel(0),
    rednessLevel(0) {}
};

/** @~english
 * The UserInfo struct.
 */
/** @~chinese
 * UserInfo 的定义。
 */
struct UserInfo {
  /** @~english
   * The user ID.
   */
  /** @~chinese
   * 用户 ID。
   */
  uid_t uid;
  /** @~english
   * The user account.
   */
  /** @~chinese
   * 用户 Account。
   */
  char userAccount[MAX_USER_ACCOUNT_LENGTH];
  UserInfo()
      : uid(0) {
    userAccount[0] = '\0';
  }
};

/** @~english
 * IP areas.
 */
/** @~chinese
 * 访问区域。
 */
enum AREA_CODE {
    /** @~english
     * Mainland China.
     */
    /** @~chinese
     * 中国大陆。
     */
    AREA_CODE_CN = (1 << 0),
    /** @~english
     * North America.
     */
    /** @~chinese
     * 北美区域。
     */
    AREA_CODE_NA = (1 << 1),
    /** @~english
     * Europe.
     */
    /** @~chinese
     * 欧洲区域。
     */
    AREA_CODE_EUR = (1 << 2),
    /** @~english
     * Asia, excluding mainland China.
     */
    /** @~chinese
     * 除中国大陆以外的亚洲区域。
     */
    AREA_CODE_AS = (1 << 3),
    /** @~english
     * (Default) Global.
     */
    /** @~chinese
     * （默认）全球。
     */
    AREA_CODE_GLOBAL = (0xFFFFFFFF)
};

enum ENCRYPTION_CONFIG {
    /** @~english
	 * - 1: Force set master key and mode;
	 * - 0: Not force set, checking whether encryption plugin exists
	 */
    /** @~chinese
	 * - 1: 强制配置加密密钥和模式。
	 * - 0: 不强制配置加密密钥和模式，检查是否存在加密插件。
	 */
    ENCRYPTION_FORCE_SETTING = (1 << 0),
    /** @~english
	 * - 1: Force not encrypting packet;
	 * - 0: Not force encrypting;
	 */
    /** @~chinese
	 * - 1: 强制加密数据包。
	 * - 0: 不强制加密数据包。
	 */
    ENCRYPTION_FORCE_DISABLE_PACKET = (1 << 1)
};
/** @~english Definition of IPacketObserver.
*/
/** @~chinese IPacketObserver 定义。
 */
class IPacketObserver
{
public:
/** @~english Definition of Packet.
 */
/** @~chinese Packet 定义。
     */
	struct Packet
	{
        /** @~english Buffer address of the sent or received data.
         * @note Agora recommends that the value of buffer is more than 2048 bytes, otherwise, you may meet undefined behaviors such as a crash.
         */
        /** @~chinese 需要发送或接收的数据的缓存地址。
         * @note Agora 建议 buffer 值不要小于 2048 字节，否则有可能会出现未定义行为（例如崩溃）。
         */
		const unsigned char* buffer;
        /** @~english Buffer size of the sent or received data.
         */
        /** @~chinese 将要发送或接收的数据的缓存大小。
         */
		unsigned int size;
	};
	/** @~english Occurs when the local user sends an audio packet.

     @param packet The sent audio packet. See Packet.
     @return
     - true: The audio packet is sent successfully.
     - false: The audio packet is discarded.
     */
    /** @~chinese 已发送音频包回调。

     在音频包被发送给对方用户前由 SDK 调用。

     @param packet 详见: Packet 。
     @return
     - true: 发送音频包；
     - false: 丢弃音频包。
     */
	virtual bool onSendAudioPacket(Packet& packet) = 0;
	/** @~english Occurs when the local user sends a video packet.

     @param packet The sent video packet. See Packet.
     @return
     - true: The video packet is sent successfully.
     - false: The video packet is discarded.
     */
    /** @~chinese 已发送视频包回调。

     在视频包被发送给对方用户前由 SDK 调用。

     @param packet 详见: Packet 。
     @return
     - true: 发送视频包；
     - false: 丢弃视频包。
     */
	virtual bool onSendVideoPacket(Packet& packet) = 0;
	/** @~english Occurs when the local user receives an audio packet.

     @param packet The received audio packet. See Packet.
     @return
     - true: The audio packet is received successfully.
     - false: The audio packet is discarded.
	 */
    /** @~chinese 收到音频包回调。

     在收到对方用户的音频包之前由 SDK 调用。

     @param packet 详见: Packet 。
     @return
     - true: 发送音频包；
     - false: 丢弃音频包。
     */
	virtual bool onReceiveAudioPacket(Packet& packet) = 0;
	/** @~english Occurs when the local user receives a video packet.

     @param packet The received video packet. See Packet.
     @return
     - true: The video packet is received successfully.
     - false: The video packet is discarded.
	 */
    /** @~chinese 收到视频包回调。

     在收到对方用户的视频包之前由 SDK 调用。

     @param packet 详见: Packet 。
     @return
     - true: 发送视频包；
     - false: 丢弃视频包。
     */
	virtual bool onReceiveVideoPacket(Packet& packet) = 0;
};

/** @~english The SDK uses the IRtcEngineEventHandler interface class to send callbacks to the application. The application inherits the methods of this interface class to retrieve these callbacks.

 All methods in this interface class have default (empty) implementations. Therefore, the application can only inherit some required events. In the callbacks, avoid time-consuming tasks or calling blocking APIs, such as the SendMessage method. Otherwise, the SDK may not work properly.
 */
/** @~chinese
IRtcEngineEventHandler 接口类用于 SDK 向 App 发送回调事件通知，App 通过继承该接口类的方法获取 SDK 的事件通知。

接口类的所有方法都由缺省（空）实现，App 可以根据需要只继承关心的事件。在回调方法中，App 不应该做耗时或者调用可能会引起阻塞的 API（如发送消息），否则可能影响 SDK 的运行。
*/
class IRtcEngineEventHandler
{
public:
    virtual ~IRtcEngineEventHandler() {}

    /** @~english Reports a warning during SDK runtime.

     In most cases, the application can ignore the warning reported by the SDK because the SDK can usually fix the issue and resume running. For example, when losing connection with the server, the SDK may report #WARN_LOOKUP_CHANNEL_TIMEOUT and automatically try to reconnect.

     @param warn Warning code: #WARN_CODE_TYPE.
     @param msg Pointer to the warning message.
     */
    /** @~chinese 发生警告回调。

     该回调方法表示 SDK 运行时出现了（网络或媒体相关的）警告。通常情况下，SDK 上报的警告信息 App 可以忽略，SDK 会自动恢复。比如和服务器失去连接时，SDK 可能会上报 #WARN_OPEN_CHANNEL_TIMEOUT 警告，同时自动尝试重连。

     @param warn 警告代码： #WARN_CODE_TYPE 。
     @param msg 警告描述。
     */
    virtual void onWarning(int warn, const char* msg) {
        (void)warn;
        (void)msg;
    }

    /** @~english Reports an error during SDK runtime.

     In most cases, the SDK cannot fix the issue and resume running. The SDK requires the application to take action or informs the user about the issue.

     For example, the SDK reports an #ERR_START_CALL error when failing to initialize a call. The application informs the user that the call initialization failed and invokes the \ref IRtcEngine::leaveChannel "leaveChannel" method to leave the channel.

     @param err Error code: #ERROR_CODE_TYPE.
     @param msg Pointer to the error message.
     */
    /** @~chinese 发生错误回调。

     该回调方法表示 SDK 运行时出现了（网络或媒体相关的）错误。通常情况下，SDK 上报的错误意味着 SDK 无法自动恢复，需要 App 干预或提示用户。 比如启动通话失败时，SDK 会上报 #ERR_START_CALL 错误。App 可以提示用户启动通话失败，并调用 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 退出频道。

     @param err 错误代码： #ERROR_CODE_TYPE 。
     @param msg 错误描述。
     */
    virtual void onError(int err, const char* msg) {
        (void)err;
        (void)msg;
    }

    /** @~english Occurs when a user joins a channel.

     This callback notifies the application that a user joins a specified channel when the application calls the \ref IRtcEngine::joinChannel "joinChannel" method.

     The channel name assignment is based on @p channelName specified in the \ref IRtcEngine::joinChannel "joinChannel" method.

     If the @p uid is not specified in the *joinChannel* method, the server automatically assigns a @p uid.

     @param channel  Pointer to the channel name.
     @param  uid User ID of the user joining the channel.
     @param  elapsed Time elapsed (ms) from the user calling the \ref IRtcEngine::joinChannel "joinChannel" method until the SDK triggers this callback.
     */
    /** @~chinese 加入频道回调。

     该回调方法表示该客户端成功加入了指定的频道。

     channel ID 基于 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 中指定的 channel name 分配。如果调用 IRtcEngine::joinChannel 时并没有指定 user ID。服务器会自动分配一个。

     @param channel      频道名。
     @param  uid 用户 ID。如果 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 中指定了 uid，则此处返回该 ID；否则使用 Agora 服务器自动分配的 ID。
     @param  elapsed 从 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 开始到发生此事件过去的时间（毫秒）。
     */
    virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) {
        (void)channel;
        (void)uid;
        (void)elapsed;
    }

    /** @~english Occurs when a user rejoins the channel after disconnection due to network problems.

    When a user loses connection with the server because of network problems, the SDK automatically tries to reconnect and triggers this callback upon reconnection.

     @param channel Pointer to the channel name.
     @param uid User ID of the user rejoining the channel.
     @param elapsed Time elapsed (ms) from starting to reconnect until the SDK triggers this callback.
     */
    /** @~chinese 重新加入频道回调。

     有时候由于网络原因，客户端可能会和服务器失去连接，SDK 会进行自动重连，自动重连成功后触发此回调方法。

     @param channel 频道名。
     @param uid 用户 ID。
     @param elapsed 从开始重连到重连成功的时间（毫秒）。
     */
    virtual void onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed) {
        (void)channel;
        (void)uid;
        (void)elapsed;
    }

    /** @~english Occurs when a user leaves the channel.

    This callback notifies the application that a user leaves the channel when the application calls the \ref IRtcEngine::leaveChannel "leaveChannel" method.

    The application retrieves information, such as the call duration and statistics.

     @param stats Pointer to the statistics of the call: RtcStats.
     */
    /** @~chinese 离开频道回调。

     App 调用 \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" 方法时，SDK提示 App 离开频道成功。在该回调方法中，App 可以得到此次通话的总通话时长、SDK 收发数据的流量等信息。App 通过该回调获取通话时长以及 SDK 接收到或发送的数据统计信息。

     @param stats 通话的统计数据: RtcStats 。
     */
    virtual void onLeaveChannel(const RtcStats& stats) {
        (void)stats;
    }

    /** @~english Occurs when the user role switches in a live broadcast. For example, from a host to an audience or vice versa.

    This callback notifies the application of a user role switch when the application calls the \ref IRtcEngine::setClientRole "setClientRole" method.

    The SDK triggers this callback when the local user switches the user role by calling the \ref agora::rtc::IRtcEngine::setClientRole "setClientRole" method after joining the channel.
     @param oldRole Role that the user switches from: #CLIENT_ROLE_TYPE.
     @param newRole Role that the user switches to: #CLIENT_ROLE_TYPE.
     */
    /** @~chinese 直播场景下用户角色已切换回调。

     直播场景下，当用户切换角色时会触发此回调，即主播切换为观众时，或观众切换为主播时。
     该回调由本地用户在加入频道后调用 \ref agora::rtc::IRtcEngine::setClientRole "setClientRole" 改变用户角色触发的。
     @param oldRole 切换前的角色: #CLIENT_ROLE_TYPE 。
     @param newRole 切换后的角色: #CLIENT_ROLE_TYPE 。
     */
    virtual void onClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole) {
    }

    /** @~english Occurs when a remote user (Communication)/ host (Live Broadcast) joins the channel.

     - Communication profile: This callback notifies the application that another user joins the channel. If other users are already in the channel, the SDK also reports to the application on the existing users.
     - Live-broadcast profile: This callback notifies the application that the host joins the channel. If other hosts are already in the channel, the SDK also reports to the application on the existing hosts. We recommend limiting the number of hosts to 17.

     The SDK triggers this callback under one of the following circumstances:
     - A remote user/host joins the channel by calling the \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" method.
     - A remote user switches the user role to the host by calling the \ref agora::rtc::IRtcEngine::setClientRole "setClientRole" method after joining the channel.
     - A remote user/host rejoins the channel after a network interruption.
     - The host injects an online media stream into the channel by calling the \ref agora::rtc::IRtcEngine::addInjectStreamUrl "addInjectStreamUrl" method.

     @note In the Live-broadcast profile:
     - The host receives this callback when another host joins the channel.
     - The audience in the channel receives this callback when a new host joins the channel.
     - When a web application joins the channel, the SDK triggers this callback as long as the web application publishes streams.

     @param uid User ID of the user or host joining the channel.
     @param elapsed Time delay (ms) from the local user calling the \ref IRtcEngine::joinChannel "joinChannel" method until the SDK triggers this callback.
     */
    /** @~chinese 远端用户（通信场景）/主播（直播场景）加入当前频道回调。

     - 通信场景下，该回调提示有远端用户加入了频道，并返回新加入用户的 ID；如果加入之前，已经有其他用户在频道中了，新加入的用户也会收到这些已有用户加入频道的回调。
     - 直播场景下，该回调提示有主播加入了频道，并返回该主播的 ID。如果在加入之前，已经有主播在频道中了，新加入的用户也会收到已有主播加入频道的回调。声网建议连麦主播不超过 17 人。

     该回调在如下情况下会被触发：
     - 远端用户/主播调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 方法加入频道
     - 远端用户加入频道后调用 \ref agora::rtc::IRtcEngine::setClientRole "setClientRole" 将用户角色改变为主播
     - 远端用户/主播网络中断后重新加入频道
     - 主播通过调用 \ref agora::rtc::IRtcEngine::addInjectStreamUrl "addInjectStreamUrl" 方法成功输入在线媒体流

     @note 直播场景下，
     - 主播间能相互收到新主播加入频道的回调，并能获得该主播的 uid。
     - 观众也能收到新主播加入频道的回调，并能获得该主播的 uid。
     - 当 Web 端加入直播频道时，只要 Web 端有推流，SDK 会默认该 Web 端为主播，并触发该回调。

     @param uid 新加入频道的远端用户/主播 ID。
     @param elapsed 从本地用户调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 到该回调触发的延迟（毫秒)。
     */
    virtual void onUserJoined(uid_t uid, int elapsed) {
        (void)uid;
        (void)elapsed;
    }

    /** @~english Occurs when a remote user (Communication)/host (Live Broadcast) leaves the channel.

    Reasons why the user is offline:

    - Leave the channel: When the user/host leaves the channel, the user/host sends a goodbye message. When the message is received, the SDK assumes that the user/host leaves the channel.
    - Drop offline: When no data packet of the user or host is received for a certain period of time, the SDK assumes that the user/host drops offline. Unreliable network connections may lead to false detections, so we recommend using the Agora RTM SDK for more reliable offline detection.

     @param uid User ID of the user leaving the channel or going offline.
     @param reason Reason why the user is offline: #USER_OFFLINE_REASON_TYPE.
     */
    /** @~chinese 远端用户（通信场景）/主播（直播场景）离开当前频道回调。

     提示有远端用户/主播离开了频道（或掉线）。用户离开频道有两个原因，即正常离开和超时掉线：
     - 正常离开的时候，远端用户/主播会发送类似“再见”的消息。接收此消息后，判断用户离开频道。
     - 超时掉线的依据是，在一定时间内（直播场景稍有延时），
     用户没有收到对方的任何数据包，则判定为对方掉线。在网络较差的情况下，有可能会误报。
     我们建议使用 Agora 实时消息 SDK 来做可靠的掉线检测。

     @param uid 离线用户或主播的用户 ID。
     @param reason 离线原因: #USER_OFFLINE_REASON_TYPE 。
     */
    virtual void onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) {
        (void)uid;
        (void)reason;
    }

    /** @~english Reports the last mile network quality of the local user once every two seconds before the user joins the channel.

     Last mile refers to the connection between the local device and Agora's edge server. After the application calls the \ref IRtcEngine::enableLastmileTest "enableLastmileTest" method, this callback reports once every two seconds the uplink and downlink last mile network conditions of the local user before the user joins the channel.

     @param quality The last mile network quality: #QUALITY_TYPE.
     */
    /** @~chinese 通话前网络上下行 last mile 质量报告回调。

     该回调描述本地用户在加入频道前的 last mile 网络探测的结果，其中 last mile 是指设备到 Agora 边缘服务器的网络状态。

     在调用 \ref agora::rtc::IRtcEngine::enableLastmileTest "enableLastmileTest" 之后，该回调函数每 2 秒触发一次。如果远端有多个用户/主播，该回调每 2 秒会被触发多次。

     @param quality 网络上下行质量，基于上下行网络的丢包率和抖动计算，探测结果主要反映上行网络的状态。详见: #QUALITY_TYPE 。
     */
    virtual void onLastmileQuality(int quality) {
        (void)quality;
    }

    /** @~english Reports the last-mile network probe result.

    The SDK triggers this callback within 30 seconds after the app calls the \ref agora::rtc::IRtcEngine::startLastmileProbeTest "startLastmileProbeTest" method.

    @param result The uplink and downlink last-mile network probe test result. See LastmileProbeResult.
    */
    /** @~chinese 通话前网络质量探测报告回调。

    通话前网络上下行 Last mile 质量探测报告回调。在调用 \ref agora::rtc::IRtcEngine::startLastmileProbeTest "startLastmileProbeTest" 之后，SDK 会在约 30 秒内返回该回调。

    @param result 上下行 Last mile 质量探测结果。 详见: LastmileProbeResult 。

     */
    virtual void onLastmileProbeResult(const LastmileProbeResult& result) {
        (void)result;
    }

    /** @~english **DEPRECATED** Occurs when the connection between the SDK and the server is interrupted.

     Deprecated as of v2.3.2. Replaced by the \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged(CONNECTION_STATE_RECONNECTING, CONNECTION_CHANGED_INTERRUPTED)" callback.

     The SDK triggers this callback when it loses connection with the server for more than four seconds after the connection is established.

     After triggering this callback, the SDK tries reconnecting to the server. You can use this callback to implement pop-up reminders.

     This callback is different from \ref agora::rtc::IRtcEngineEventHandler::onConnectionLost "onConnectionLost":
     - The SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onConnectionInterrupted "onConnectionInterrupted" callback when it loses connection with the server for more than four seconds after it successfully joins the channel.
     - The SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onConnectionLost "onConnectionLost" callback when it loses connection with the server for more than 10 seconds, whether or not it joins the channel.

     If the SDK fails to rejoin the channel 20 minutes after being disconnected from Agora's edge server, the SDK stops rejoining the channel.

    */
    /** @~chinese 网络连接中断回调。已废弃，被 \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged(CONNECTION_STATE_RECONNECTING, CONNECTION_CHANGED_INTERRUPTED)" 取代。

     SDK 在和服务器建立连接后，失去了网络连接超过 4 秒，会触发该回调。在触发事件后，SDK 会主动重连服务器，所以该事件可以用于 UI 提示。

     与 \ref agora::rtc::IRtcEngineEventHandler::onConnectionLost "onConnectionLost" 回调的区别是：
     - *onConnectionInterrupted* 回调一定是发生在加入频道成功后，且 SDK 刚失去和服务器连接超过 4 秒时触发。
     - *onConnectionLost* 回调是无论之前加入频道是否成功，只要 10 秒内和服务器无法建立连接都会触发。

     如果 SDK 在断开连接后，20 分钟内还是没能重新加入频道，SDK 会停止尝试重连。
     */
    virtual void onConnectionInterrupted() {}

    /** @~english Occurs when the SDK cannot reconnect to Agora's edge server 10 seconds after its connection to the server is interrupted.

    The SDK triggers this callback when it cannot connect to the server 10 seconds after calling the \ref IRtcEngine::joinChannel "joinChannel" method, whether or not it is in the channel.

    This callback is different from \ref agora::rtc::IRtcEngineEventHandler::onConnectionInterrupted "onConnectionInterrupted":

    - The SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onConnectionInterrupted "onConnectionInterrupted" callback when it loses connection with the server for more than four seconds after it successfully joins the channel.
    - The SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onConnectionLost "onConnectionLost" callback when it loses connection with the server for more than 10 seconds, whether or not it joins the channel.

    If the SDK fails to rejoin the channel 20 minutes after being disconnected from Agora's edge server, the SDK stops rejoining the channel.

     */
    /** @~chinese 网络连接丢失回调。

     SDK 在调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 后无论是否加入成功，只要 10 秒和服务器无法连接就会触发该回调。

     与 \ref agora::rtc::IRtcEngineEventHandler::onConnectionInterrupted "onConnectionInterrupted" 的区别是：

     - *onConnectionInterrupted* 回调一定是发生在加入频道成功后，且 SDK 刚失去和服务器连接超过 4 秒时触发。
     - *onConnectionLost* 回调是无论之前加入频道是否成功，只要 10 秒内和服务器无法建立连接都会触发。

     如果 SDK 在断开连接后，20 分钟内还是没能重新加入频道，SDK 会停止尝试重连。
     */
    virtual void onConnectionLost() {}

    /** @~english **DEPRECATED** Deprecated as of v2.3.2. Replaced by the \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged(CONNECTION_STATE_FAILED, CONNECTION_CHANGED_BANNED_BY_SERVER)" callback.

    Occurs when your connection is banned by the Agora Server.
     */
    /** @~chinese @deprecated 连接已被服务器禁止回调。已废弃，被 \ref agora::rtc::IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged(CONNECTION_STATE_FAILED, CONNECTION_CHANGED_BANNED_BY_SERVER)" 取代。

     当你被服务端禁掉连接的权限时，会触发该回调。
     */
    virtual void onConnectionBanned() {}

    /** @~english Occurs when a method is executed by the SDK.

     @param err The error code (#ERROR_CODE_TYPE) returned by the SDK when a method call fails. If the SDK returns 0, then the method call is successful.
     @param api Pointer to the method executed by the SDK.
     @param result Pointer to the result of the method call.
     */
    /** @~chinese API 方法已执行回调。

     @param err 当该方法调用失败时 SDK 返回的错误码。如果方法调用失败，会返回错误码 #ERROR_CODE_TYPE 。如果该方法调用成功，SDK 将返回 0。
     @param api SDK 执行的 API。
     @param result SDK 调用 API 的调用结果。
     */
    virtual void onApiCallExecuted(int err, const char* api, const char* result) {
        (void)err;
        (void)api;
        (void)result;
    }

    /** @~english Occurs when the token expires.

     After a token is specified by calling the \ref IRtcEngine::joinChannel "joinChannel" method, if the SDK losses connection with the Agora server due to network issues, the token may expire after a certain period of time and a new token may be required to reconnect to the server.

     This callback notifies the app to generate a new token and call joinChannel to rejoin the channel with the new token.
     */
    /** @~chinese Token 已过期回调。

     在调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel", 时如果指定了 Token，由于 Token 具有一定的时效，
     在通话过程中 SDK 可能由于网络原因和服务器失去连接，重连时可能需要新的 Token。

     该回调通知 App 需要生成新的 Token，并调用 \ref agora::rtc::IRtcEngine::renewToken "renewToken" 更新 Token。
     */
    virtual void onRequestToken() {
    }

    /** @~english Occurs when the token expires in 30 seconds.

     The user becomes offline if the token used in the \ref IRtcEngine::joinChannel "joinChannel" method expires. The SDK triggers this callback 30 seconds before the token expires to remind the application to get a new token. Upon receiving this callback, generate a new token on the server and call the \ref IRtcEngine::renewToken "renewToken" method to pass the new token to the SDK.

     @param token Pointer to the token that expires in 30 seconds.
     */
    /** @~chinese Token 服务即将过期回调。

     在调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 时如果指定了 Token，由于 Token 具有一定的时效，在通话过程中如果 Token 即将失效，SDK 会提前 30 秒触发该回调，提醒 App 更新 Token。 当收到该回调时，用户需要重新在服务端生成新的 Token，然后调用 \ref agora::rtc::IRtcEngine::renewToken "renewToken" 将新生成的 Token 传给 SDK。

     @param token 即将服务失效的 Token。
     */
    virtual void onTokenPrivilegeWillExpire(const char* token) {
        (void)token;
    }

    /** @~english **DEPRECATED** Reports the statistics of the audio stream from each remote user/host.

    Deprecated as of v2.3.2. Use the \ref agora::rtc::IRtcEngineEventHandler::onRemoteAudioStats "onRemoteAudioStats" callback instead.

     The SDK triggers this callback once every two seconds to report the audio quality of each remote user/host sending an audio stream. If a channel has multiple users/hosts sending audio streams, the SDK triggers this callback as many times.

     @param uid User ID of the speaker.
     @param quality Audio quality of the user: #QUALITY_TYPE.
     @param delay Time delay (ms) of sending the audio packet from the sender to the receiver, including the time delay of audio sampling pre-processing, transmission, and the jitter buffer.
     @param lost Packet loss rate (%) of the audio packet sent from the sender to the receiver.
     */
    /** @~chinese @deprecated 远端声音质量回调。

     已废弃。请改用 \ref agora::rtc::IRtcEngineEventHandler::onRemoteAudioStats "onRemoteAudioStats" 方法。

     该回调描述远端用户在通话中的音频质量，针对每个远端用户/主播每 2 秒触发一次。如果远端同时存在多个用户/主播，该回调每 2 秒会被触发多次。

     @param uid 用户 ID，指定是谁发的音频流。
     @param quality 语音质量，详见: #QUALITY_TYPE 。
     @param delay 音频包从发送端到接收端的延迟（毫秒）。包括声音采样前处理、网络传输、网络抖动缓冲引起的延迟。
     @param lost 音频包从发送端到接收端的丢包率 (%)。
     */
    virtual void onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost) {
        (void)uid;
        (void)quality;
        (void)delay;
        (void)lost;
    }

    /** @~english Reports the statistics of the current call.

     The SDK triggers this callback once every two seconds after the user joins the channel.

     @param stats Statistics of the IRtcEngine: RtcStats.
     */
    /** @~chinese 当前通话统计回调。

     SDK 定期向 App 报告当前通话的统计信息，每两秒触发一次。

     @param stats RTC 引擎统计数据: RtcStats 。
     */
    virtual void onRtcStats(const RtcStats& stats) {
        (void)stats;
    }

    /** @~english Reports the last mile network quality of each user in the channel once every two seconds.

     Last mile refers to the connection between the local device and Agora's edge server. This callback reports once every two seconds the last mile network conditions of each user in the channel. If a channel includes multiple users, the SDK triggers this callback as many times.

     @param uid User ID. The network quality of the user with this @p uid is reported. If @p uid is 0, the local network quality is reported.
     @param txQuality Uplink transmission quality rating of the user in terms of the transmission bitrate, packet loss rate, average RTT (Round-Trip Time), and jitter of the uplink network. @p txQuality is a quality rating helping you understand how well the current uplink network conditions can support the selected VideoEncoderConfiguration. For example, a 1000 Kbps uplink network may be adequate for video frames with a resolution of 640 * 480 and a frame rate of 15 fps in the Live-broadcast profile, but may be inadequate for resolutions higher than 1280 * 720. See #QUALITY_TYPE.
     @param rxQuality Downlink network quality rating of the user in terms of the packet loss rate, average RTT, and jitter of the downlink network. See #QUALITY_TYPE.
     */
    /** @~chinese 通话中每个用户的网络上下行 last mile 质量报告回调。

     该回调描述每个用户在通话中的 last mile 网络状态，其中 last mile 是指设备到 Agora 边缘服务器的网络状态。

     该回调每 2 秒触发一次。如果远端有多个用户，该回调每 2 秒会被触发多次。

     @param uid 用户 ID。表示该回调报告的是持有该 ID 的用户的网络质量。当 uid 为 0 时，返回的是本地用户的网络质量。
     @param txQuality 该用户的上行网络质量，基于发送码率、上行丢包率、平均往返时延和网络抖动计算。该值代表当前的上行网络质量，帮助判断是否可以支持当前设置的视频编码属性。假设上行码率是 1000 Kbps，那么支持直播场景下 640 &times; 480 的分辨率、15 fps 的帧率没有问题，但是支持 1280 &times; 720 的分辨率就会有困难。详见 #QUALITY_TYPE 。
     @param rxQuality 该用户的下行网络质量，基于下行网络的丢包率、平均往返延时和网络抖动计算。详见 #QUALITY_TYPE 。
     */
    virtual void onNetworkQuality(uid_t uid, int txQuality, int rxQuality) {
    (void)uid;
    (void)txQuality;
    (void)rxQuality;
    }

    /** @~english Reports the statistics of the local video stream.
     *
     * The SDK triggers this callback once every two seconds for each
     * user/host. If there are multiple users/hosts in the channel, the SDK
     * triggers this callback as many times.
     *
     * @note
     * If you have called the
     * \ref agora::rtc::IRtcEngine::enableDualStreamMode "enableDualStreamMode"
     * method, the \ref onLocalVideoStats() "onLocalVideoStats" callback
     * reports the statistics of the high-video
     * stream (high bitrate, and high-resolution video stream).
     *
     * @param stats Statistics of the local video stream. See LocalVideoStats.
     */
    /** @~chinese 本地视频流统计信息回调。

    该回调描述本地设备发送视频流的统计信息，每 2 秒触发一次。

     @param stats 本地视频流统计信息。详见: LocalVideoStats 。
     */
   virtual void onLocalVideoStats(const LocalVideoStats& stats) {
    (void)stats;
    }

    /** @~english Reports the statistics of the video stream from each remote user/host.
     *
     * The SDK triggers this callback once every two seconds for each remote
     * user/host. If a channel includes multiple remote users, the SDK
     * triggers this callback as many times.
     *
     * @param stats Statistics of the remote video stream. See
     * RemoteVideoStats.
     */
    /** @~chinese 通话中远端视频流的统计信息回调。
     *
     * 该回调描述远端用户在通话中端到端的视频流统计信息，
     * 针对每个远端用户/主播每 2 秒触发一次。如果远端同时存在多个用户/主播，
     * 该回调每 2 秒会被触发多次。
     *
     * @param stats 远端视频统计数据。详见: RemoteVideoStats 。
     */
    virtual void onRemoteVideoStats(const RemoteVideoStats& stats) {
      (void)stats;
      }

    /** @~english Reports the statistics of the local audio stream.
     *
     * The SDK triggers this callback once every two seconds.
     *
     * @param stats The statistics of the local audio stream.
     * See LocalAudioStats.
     */
    /** @~chinese 通话中本地音频流的统计信息回调。
     *
     * 该回调描述本地设备发送音频流的统计信息。SDK 每 2 秒触发该回调一次。
     *
     * @param stats 本地音频统计数据。详见 LocalAudioStats 。
     */
    virtual void onLocalAudioStats(const LocalAudioStats& stats) {
        (void)stats;
    }

    /** @~english Reports the statistics of the audio stream from each remote user/host.

     This callback replaces the \ref agora::rtc::IRtcEngineEventHandler::onAudioQuality "onAudioQuality" callback.

     The SDK triggers this callback once every two seconds for each remote user/host. If a channel includes multiple remote users, the SDK triggers this callback as many times.

     @param stats Pointer to the statistics of the received remote audio streams. See RemoteAudioStats.
     */
    /** @~chinese 通话中远端音频流的统计信息回调。用于取代 \ref agora::rtc::IRtcEngineEventHandler::onAudioQuality "onAudioQuality" 回调。

     该回调描述远端用户在通话中端到端的音频流统计信息。该回调函数针对每个发送音频流的远端用户/主播每 2 秒触发一次。如果远端有多个用户/主播发送音频流，该回调每 2 秒会被触发多次。

     @param stats 接收到的远端音频统计数据，详细定义见: RemoteAudioStats 。
     */
    virtual void onRemoteAudioStats(const RemoteAudioStats& stats) {
        (void)stats;
    }

    /** @~english Occurs when the local audio state changes.
     *
     * This callback indicates the state change of the local audio stream,
     * including the state of the audio recording and encoding, and allows
     * you to troubleshoot issues when exceptions occur.
     *
     * @note
     * When the state is #LOCAL_AUDIO_STREAM_STATE_FAILED (3), see the `error`
     * parameter for details.
     *
     * @param state State of the local audio. See #LOCAL_AUDIO_STREAM_STATE.
     * @param error The error information of the local audio.
     * See #LOCAL_AUDIO_STREAM_ERROR.
     */
    /** @~chinese 本地音频状态发生改变回调。
     *
     * 本地音频的状态发生改变时（包括本地麦克风采集状态和音频编码状态），
     * SDK 会触发该回调报告当前的本地音频状态。在本地音频出现故障时，
     * 该回调可以帮助你了解当前音频的状态以及出现故障的原因，方便你排查问题。
     *
     * @note
     * 当状态为 #LOCAL_AUDIO_STREAM_STATE_FAILED (3) 时，
     * 你可以在 `error` 参数中查看返回的错误信息。
     *
     * @param state 当前的本地音频状态。详见 #LOCAL_AUDIO_STREAM_STATE 。
     * @param error 本地音频出错原因。详见 #LOCAL_AUDIO_STREAM_ERROR 。
     */
    virtual void onLocalAudioStateChanged(LOCAL_AUDIO_STREAM_STATE state, LOCAL_AUDIO_STREAM_ERROR error) {
        (void)state;
        (void)error;
    }

    /** @~english Occurs when the remote audio state changes.

     This callback indicates the state change of the remote audio stream.
     @note This callback does not work properly when the number of users (in the Communication profile) or broadcasters (in the Live-broadcast profile) in the channel exceeds 17.

     @param uid ID of the remote user whose audio state changes.
     @param state State of the remote audio. See #REMOTE_AUDIO_STATE.
     @param reason The reason of the remote audio state change.
     See #REMOTE_AUDIO_STATE_REASON.
     @param elapsed Time elapsed (ms) from the local user calling the
     \ref IRtcEngine::joinChannel "joinChannel" method until the SDK
     triggers this callback.
     */
    /** @~chinese 远端音频流状态发生改变回调。

     远端用户/主播音频状态发生改变时，SDK 会触发该回调向本地用户报告当前的远端音频流状态。

     @note 频道内的用户（通信场景）或主播（直播场景）人数超过 17 人时，该回调不生效。

     @param uid 发生音频状态改变的远端用户 ID。
     @param state 远端音频流状态。 详见 #REMOTE_AUDIO_STATE 。
     @param reason 远端音频流状态改变的具体原因。详见 #REMOTE_AUDIO_STATE_REASON 。
     @param elapsed 从本地用户调用 \ref IRtcEngine::joinChannel "joinChannel"
     方法到发生本事件经历的时间，单位为 ms。
     */
    virtual void onRemoteAudioStateChanged(uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed) {
        (void)uid;
        (void)state;
        (void)reason;
        (void)elapsed;
    }

    /** @~english Reports which users are speaking, the speakers' volume and whether the local user is speaking.

     This callback reports the IDs and volumes of the loudest speakers (at most 3 users) at the moment in the channel, and whether the local user is speaking.

     By default, this callback is disabled. You can enable it by calling the \ref IRtcEngine::enableAudioVolumeIndication(int, int, bool) "enableAudioVolumeIndication" method.
     Once enabled, this callback is triggered at the set interval, regardless of whether a user speaks or not.

     The SDK triggers two independent `onAudioVolumeIndication` callbacks at one time, which separately report the volume information of the local user and all the remote speakers.
     For more information, see the detailed parameter descriptions.

     @note
     - To enable the voice activity detection of the local user, ensure that you set `report_vad`(true) in the `enableAudioVolumeIndication` method.
     - Calling the \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream" method affects the SDK's behavior:
        - If the local user calls the \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream" method, the SDK stops triggering the local user's callback.
        - 20 seconds after a remote speaker calls the *muteLocalAudioStream* method, the remote speakers' callback excludes this remote user's information; 20 seconds after all remote users call the *muteLocalAudioStream* method, the SDK stops triggering the remote speakers' callback.
     - An empty @p speakers array in the *onAudioVolumeIndication* callback suggests that no remote user is speaking at the moment.

     @param speakers A pointer to AudioVolumeInfo:
     - In the local user's callback, this struct contains the following members:
       - `uid` = 0,
       - `volume` = `totalVolume`, which reports the sum of the voice volume and audio-mixing volume of the local user, and
       - `vad`, which reports the voice activity status of the local user.
     - In the remote speakers' callback, this array contains the following members:
       - `uid` of the remote speaker,
       - `volume`, which reports the sum of the voice volume and audio-mixing volume of each remote speaker, and
       - `vad` = 0.

       An empty speakers array in the callback indicates that no remote user is speaking at the moment.
     @param speakerNumber Total number of speakers. The value range is [0, 3].
     - In the local user’s callback, `speakerNumber` = 1, regardless of whether the local user speaks or not.
     - In the remote speakers' callback, the callback reports the IDs and volumes of the three loudest speakers when there are more than three remote users in the channel, and `speakerNumber` = 3.
     @param totalVolume Total volume after audio mixing. The value ranges between 0 (lowest volume) and 255 (highest volume).
     - In the local user’s callback, `totalVolume` is the sum of the voice volume and audio-mixing volume of the local user.
     - In the remote speakers' callback, `totalVolume` is the sum of the voice volume and audio-mixing volume of all the remote speakers.
     */
    /** @~chinese 用户音量提示回调。

     该回调默认禁用，你可以通过 \ref IRtcEngine::enableAudioVolumeIndication(int, int, bool) "enableAudioVolumeIndication" 开启。
     开启后，只要频道内有发流用户，SDK 会在加入频道后按 `enableAudioVolumeIndication` 中设置的时间间隔触发
     `onAudioVolumeIndication` 回调。每次会触发两个 `onAudioVolumeIndication` 回调，一个报告本地发流用户的音量相关信息，另一个报告
     瞬时音量最高的远端用户（最多 3 位）的音量相关信息。

     @note 启用该功能后，如果有用户将自己静音（调用了 \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream"），SDK 行为会受如下影响：
     - 本地用户静音后，SDK 立即停止报告本地用户的音量提示回调。
     - 远端说话者静音后 20 秒，远端的音量提示回调中将不再包含该用户；如果远端所有用户都将自己静音，20 秒后 SDK 不再报告远端用户的音量提示回调。

     @param speakers 用户音量信息，详见 AudioVolumeInfo 数组。如果 `speakers` 为空，则表示远端用户不发流或没有远端用户。
     @param speakerNumber 用户数量。
     - 在本地用户的回调中，只要本地用户在发流，speakerNumber 始终为 1。
     - 在远端用户的回调中，`speakerNumber` 取值范围为 [0,3]。如果远端发流用户数量大于 3，则此回调中 `speakerNumber` 值为 3。
     @param totalVolume 混音后的总音量，取值范围为 [0,255]。
     - 在本地用户的回调中，`totalVolume` 为本地发流用户的音量。
     - 在远端用户的回调中，`totalVolume` 为瞬时音量最高的远端用户（最多 3 位）混音后的总音量。
     如果用户调用了 \ref agora::rtc::IRtcEngine::startAudioMixing "startAudioMixing"，则 `totalVolume` 为音乐文件和用户声音的总音量。
     */
    virtual void onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) {
        (void)speakers;
        (void)speakerNumber;
        (void)totalVolume;
    }

    /** @~english Reports which user is the loudest speaker.

    If the user enables the audio volume indication by calling the \ref IRtcEngine::enableAudioVolumeIndication(int, int, bool) "enableAudioVolumeIndication" method, this callback returns the @p uid of the active speaker detected by the audio volume detection module of the SDK.

    @note
    - To receive this callback, you need to call the \ref IRtcEngine::enableAudioVolumeIndication(int, int, bool) "enableAudioVolumeIndication" method.
    - This callback returns the user ID of the user with the highest voice volume during a period of time, instead of at the moment.

    @param uid User ID of the active speaker. A @p uid of 0 represents the local user.
    */
    /** @~chinese 监测到最活跃用户回调。

     成功调用 \ref agora::rtc::IRtcEngine::enableAudioVolumeIndication "enableAudioVolumeIndication" 后，SDK 会持续监测音量
     最大的远端用户，并统计该用户被判断为音量最大者的次数。当前时间段内，该次数累积最多的远端用户为最活跃的用户。

     当频道内用户数量大于或等于 2 且有活跃用户时，SDK 会触发该回调并报告最活跃用户的 `uid`。
     - 如果最活跃用户一直是同一位用户，则 SDK 不会再次触发 `onActiveSpeaker` 回调。
     - 如果最活跃用户有变化，则 SDK 会再次触发该回调并报告新的最活跃用户的 `uid`。

     @param uid 远端最活跃用户的 ID。
     */
    virtual void onActiveSpeaker(uid_t uid) {
        (void)uid;
    }

    /** @~english **DEPRECATED** Occurs when the video stops playing.

     The application can use this callback to change the configuration of the view (for example, displaying other pictures in the view) after the video stops playing.

     Deprecated as of v2.4.1. Use LOCAL_VIDEO_STREAM_STATE_STOPPED(0) in the \ref agora::rtc::IRtcEngineEventHandler::onLocalVideoStateChanged "onLocalVideoStateChanged" callback instead.
     */
    /** @~chinese @deprecated 视频功能已停止回调。

     提示视频功能已停止。 App 如需在停止视频后对 view 做其他处理（比如显示其他画面），可以在这个回调中进行。

     已废弃。请改用 \ref agora::rtc::IRtcEngineEventHandler::onLocalVideoStateChanged "onLocalVideoStateChanged" 回调中的 LOCAL_VIDEO_STREAM_STATE_STOPPED(0)。
     */
    virtual void onVideoStopped() {}

    /** @~english Occurs when the first local video frame is displayed/rendered on the local video view.

    @param width Width (px) of the first local video frame.
    @param height Height (px) of the first local video frame.
    @param elapsed Time elapsed (ms) from the local user calling the \ref IRtcEngine::joinChannel "joinChannel" method until the SDK triggers this callback.
    If you call the \ref IRtcEngine::startPreview "startPreview" method  before calling the *joinChannel* method, then @p elapsed is the time elapsed from calling the *startPreview* method until the SDK triggers this callback.
    */
    /** @~chinese 已显示本地视频首帧回调。

     本地视频首帧显示在本地视图上时，SDK 会触发此回调。

     @param width 本地渲染视频的宽 (px) 。
     @param height 本地渲染视频的高 (px)。
     @param elapsed 从调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 到发生此事件过去的时间（毫秒）。如果在 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 前调用了 \ref agora::rtc::IRtcEngine::startPreview "startPreview"，则是从 \ref agora::rtc::IRtcEngine::startPreview "startPreview" 到发生此事件过去的时间。
     */
    virtual void onFirstLocalVideoFrame(int width, int height, int elapsed) {
        (void)width;
        (void)height;
        (void)elapsed;
    }

    /** @~english Occurs when the first remote video frame is received and decoded.
     *
     * @deprecated v2.9.0
     *
     * This callback is deprecated and replaced by the
     * \ref onRemoteVideoStateChanged() "onRemoteVideoStateChanged" callback
     * with the following parameters:
     * - #REMOTE_VIDEO_STATE_STARTING (1)
     * - #REMOTE_VIDEO_STATE_DECODING (2)
     *
     * This callback is triggered in either of the following scenarios:
     *
     * - The remote user joins the channel and sends the video stream.
     * - The remote user stops sending the video stream and re-sends it after
     * 15 seconds. Reasons for such an interruption include:
     *  - The remote user leaves the channel.
     *  - The remote user drops offline.
     *  - The remote user calls the
     * \ref agora::rtc::IRtcEngine::muteLocalVideoStream "muteLocalVideoStream"
     *  method to stop sending the video stream.
     *  - The remote user calls the
     * \ref agora::rtc::IRtcEngine::disableVideo "disableVideo" method to
     * disable video.
     *
     * The application can configure the user view settings in this callback.
     *
     * @param uid User ID of the remote user sending the video stream.
     * @param width Width (px) of the video stream.
     * @param height Height (px) of the video stream.
     * @param elapsed Time elapsed (ms) from the local user calling the
     * \ref IRtcEngine::joinChannel "joinChannel" method until the SDK
     * triggers this callback.
     */
    /** @~chinese 已接收到远端视频并完成解码回调。
     *
     * @deprecated
     *
     * 该回调已废弃，请改用 \ref onRemoteVideoStateChanged()
     * "onRemoteVideoStateChanged" 回调的：
     * - #REMOTE_VIDEO_STATE_STARTING (1)。
     * - #REMOTE_VIDEO_STATE_DECODING (2)。
     *
     * 引擎收到第一帧远端视频流并解码成功时，触发此调用。
     * App 可在此回调中设置该用户的 view。有两种情况：
     * - 远端用户首次上线后发送视频。
     * - 远端用户视频离线再上线后发送视频。出现这种中断的可能原因包括：
     *  - 远端用户离开频道。
     *  - 远端用户掉线。
     *  - 远端用户调用 \ref agora::rtc::IRtcEngine::muteLocalVideoStream
     * "muteLocalVideoStream" 方法停止发送本地视频流。
     *  - 远端用户调用 \ref agora::rtc::IRtcEngine::disableVideo
     * "disableVideo" 方法关闭视频模块。
     *
     * @param uid 用户 ID，指定是哪个用户的视频流。
     * @param width 视频流宽（px）。
     * @param height 视频流高（px）。
     * @param elapsed 从本地调用 \ref agora::rtc::IRtcEngine::joinChannel
     * "joinChannel" 开始到该回调触发的延迟（毫秒)。
     */
    virtual void onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed) {
        (void)uid;
        (void)width;
        (void)height;
        (void)elapsed;
    }

    /** @~english Occurs when the first remote video frame is rendered.

     The SDK triggers this callback when the first frame of the remote video is displayed in the user's video window. The application can retrieve the time elapsed from a user joining the channel until the first video frame is displayed.

     @param uid User ID of the remote user sending the video stream.
     @param width Width (px) of the video frame.
     @param height Height (px) of the video stream.
     @param elapsed Time elapsed (ms) from the local user calling the \ref IRtcEngine::joinChannel "joinChannel" method until the SDK triggers this callback.
    */
    /** @~chinese 已显示首帧远端视频回调。

     第一帧远端视频显示在视图上时，触发此调用。 App 可在此调用中获知出图时间（elapsed）。

     @param uid 用户 ID，指定是哪个用户的视频流。
     @param width 视频流宽（px）。
     @param height 视频流高（px）。
     @param elapsed 从本地调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 到发生此事件过去的时间（毫秒)。
     */
    virtual void onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed) {
        (void)uid;
        (void)width;
        (void)height;
        (void)elapsed;
    }

    /** @~english @deprecated This method is deprecated from v3.0.0, use the \ref agora::rtc::IRtcEngineEventHandler::onRemoteAudioStateChanged "onRemoteAudioStateChanged" callback instead.

     Occurs when a remote user's audio stream playback pauses/resumes.

     The SDK triggers this callback when the remote user stops or resumes sending the audio stream by calling the \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream" method.

     @note This callback does not work properly when the number of users (in the Communication profile) or broadcasters (in the Live-broadcast profile) in the channel exceeds 17.

     @param uid User ID of the remote user.
     @param muted Whether the remote user's audio stream is muted/unmuted:
     - true: Muted.
     - false: Unmuted.
     */
    /** @~chinese 远端用户静音回调。

     @deprecated 该回调已废弃。请改用 \ref agora::rtc::IRtcEngineEventHandler::onRemoteAudioStateChanged "onRemoteAudioStateChanged"

     提示有远端用户已将其音频流静音（或取消静音）。

     该回调是由远端用户调用 \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream" 方法关闭或开启音频发送触发的。

     @note 频道内的用户（通信场景）或主播（直播场景）人数超过 17 人时，该回调不生效。

     @param uid 用户 ID。
     @param muted 该用户是否静音：
     - true: 该用户已将音频静音；
     - false: 该用户取消了音频静音。
     */
    virtual void onUserMuteAudio(uid_t uid, bool muted) {
        (void)uid;
        (void)muted;
    }

    /** @~english Occurs when a remote user's video stream playback pauses/resumes.
     *
     * You can also use the
     * \ref onRemoteVideoStateChanged() "onRemoteVideoStateChanged" callback
     * with the following parameters:
     * - #REMOTE_VIDEO_STATE_STOPPED (0) and
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5).
     * - #REMOTE_VIDEO_STATE_DECODING (2) and
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6).
     *
     * The SDK triggers this callback when the remote user stops or resumes
     * sending the video stream by calling the
     * \ref agora::rtc::IRtcEngine::muteLocalVideoStream
     * "muteLocalVideoStream" method.
     *
     * @note This callback does not work properly when the number of users (in the Communication profile) or broadcasters (in the Live-broadcast profile) in the channel exceeds 17.
     *
     * @param uid User ID of the remote user.
     * @param muted Whether the remote user's video stream playback is
     * paused/resumed:
     * - true: Paused.
     * - false: Resumed.
     */
    /** @~chinese 远端用户暂停/恢复发送视频流回调。
     * @deprecated 该回调已废弃。你也可以使用
     * \ref onRemoteVideoStateChanged() "onRemoteVideoStateChanged" 回调的：
     * - #REMOTE_VIDEO_STATE_STOPPED (0) 和
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5) 。
     * - #REMOTE_VIDEO_STATE_DECODING (2) 和
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6)。
     *
     * 该回调是由远端用户调用 \ref agora::rtc::IRtcEngine::muteLocalVideoStream
     * "muteLocalVideoStream" 方法关闭或开启视频发送触发的。
     *
     * @note 频道内的用户（通信场景）或主播（直播场景）人数超过 17 人时，该回调不生效。
     *
     * @param uid 远端用户 ID。
     * @param muted 该用户是否暂停发送其视频流
     * - true: 该用户已暂停发送其视频流；
     * - false: 该用户已恢复发送其视频流。
     */
    virtual void onUserMuteVideo(uid_t uid, bool muted) {
        (void)uid;
        (void)muted;
    }

    /** @~english Occurs when a specific remote user enables/disables the video
     * module.
     *
     * @deprecated v2.9.0
     *
     * This callback is deprecated and replaced by the
     * \ref onRemoteVideoStateChanged() "onRemoteVideoStateChanged" callback
     * with the following parameters:
     * - #REMOTE_VIDEO_STATE_STOPPED (0) and
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5).
     * - #REMOTE_VIDEO_STATE_DECODING (2) and
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6).
     *
     * Once the video module is disabled, the remote user can only use a
     * voice call. The remote user cannot send or receive any video from
     * other users.
     *
     * The SDK triggers this callback when the remote user enables or disables
     * the video module by calling the
     * \ref agora::rtc::IRtcEngine::enableVideo "enableVideo" or
     * \ref agora::rtc::IRtcEngine::disableVideo "disableVideo" method.
     *
     * @note This callback returns invalid when the number of users in a
     * channel exceeds 20.
     *
     * @param uid User ID of the remote user.
     * @param enabled Whether the remote user enables/disables the video
     * module:
     * - true: Enable. The remote user can enter a video session.
     * - false: Disable. The remote user can only enter a voice session, and
     * cannot send or receive any video stream.
     */
    /**
     * @~chinese 远端用户开关本地视频采集回调。
     *
     * @deprecated 该回调已废弃，请改用 \ref onRemoteVideoStateChanged() "onRemoteVideoStateChanged"
     * 回调的：
     * - #REMOTE_VIDEO_STATE_STOPPED (0) 和
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5)。
     * - #REMOTE_VIDEO_STATE_DECODING (2) 和
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6)。
     *
     * 提示有远端用户开关了本地视频采集。关闭视频功能是指该用户只能进行语音通话，不能显示、
     * 发送自己的视频，也不能接收、显示别人的视频。
     * 该回调是由远端用户调用 \ref agora::rtc::IRtcEngine::enableVideo
     * "enableVideo" 或 \ref agora::rtc::IRtcEngine::disableVideo
     * "disableVideo" 方法开启或关闭视频模块触发的。
     *
     * @param uid 用户 ID，提示是哪个用户的视频流。
     * @param enabled
     * - true: 该用户已启用了视频功能。启用后，该用户可以进行视频通话或直播。
     * - false: 该用户已关闭了视频功能。关闭后，该用户只能进行语音通话或直播，不能显示、
     * 发送自己的视频，也不能接收、显示别人的视频。
     */
    	virtual void onUserEnableVideo(uid_t uid, bool enabled) {
    		(void)uid;
    		(void)enabled;
    	}

    /** @~english Occurs when the audio device state changes.

     This callback notifies the application that the system's audio device state is changed. For example, a headset is unplugged from the device.

     @param deviceId Pointer to the device ID.
     @param deviceType Device type: #MEDIA_DEVICE_TYPE.
     @param deviceState Device state: #MEDIA_DEVICE_STATE_TYPE.
     */
    /** @~chinese 音频设备变化回调。

     提示系统音频设备状态发生改变，比如耳机被拔出。

     @param deviceId 设备 ID。
     @param deviceType 设备类型定义: #MEDIA_DEVICE_TYPE 。
     @param deviceState 设备状态定义: #MEDIA_DEVICE_STATE_TYPE 。
    */
    virtual void onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) {
        (void)deviceId;
        (void)deviceType;
        (void)deviceState;
    }

    /** @~english Occurs when the volume of the playback device, microphone, or application changes.

     @param deviceType Device type: #MEDIA_DEVICE_TYPE.
     @param volume Volume of the device. The value ranges between 0 and 255.
     @param muted
     - true: The audio device is muted.
     - false: The audio device is not muted.
     */
    /** @~chinese 回放、音频采集设备、或 App 的音量发生改变。

     @param deviceType 设备类型定义: #MEDIA_DEVICE_TYPE 。
     @param volume 音量：范围 [0,255]。
     @param muted
     - true: 音频设备已被静音；
     - false: 音频设备未被静音。
     */
    virtual void onAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted) {
        (void)deviceType;
        (void)volume;
        (void)muted;
    }

    /** @~english **DEPRECATED** Occurs when the camera turns on and is ready to capture the video.

     If the camera fails to turn on, fix the error reported in the \ref IRtcEngineEventHandler::onError "onError" callback.

     Deprecated as of v2.4.1. Use #LOCAL_VIDEO_STREAM_STATE_CAPTURING (1) in the \ref agora::rtc::IRtcEngineEventHandler::onLocalVideoStateChanged "onLocalVideoStateChanged" callback instead.
     */
    /** @~chinese @deprecated 摄像头就绪回调。

     提示已成功打开摄像头，可以开始捕获视频。如果摄像头打开失败，可在 \ref agora::rtc::IRtcEngineEventHandler::onError "onError" 中处理相应错误。

     已废弃。请改用 \ref agora::rtc::IRtcEngineEventHandler::onLocalVideoStateChanged "onLocalVideoStateChanged" 回调中的 #LOCAL_VIDEO_STREAM_STATE_CAPTURING (1)。
     */
    virtual void onCameraReady() {}

    /** @~english Occurs when the camera focus area changes.

     The SDK triggers this callback when the local user changes the camera focus position by calling the setCameraFocusPositionInPreview method.

     @note This callback is for Android and iOS only.

     @param x x coordinate of the changed camera focus area.
     @param y y coordinate of the changed camera focus area.
     @param width Width of the changed camera focus area.
     @param height Height of the changed camera focus area.
     */
    /** @~chinese 相机对焦区域已改变回调。

     该回调表示相机的对焦区域发生了改变。
     该回调是由本地用户调用 setCameraFocusPositionPreview 方法改变对焦位置触发的。

     @note 该回调只适用于 Android 和 iOS 平台。

     @param x 发生改变的对焦区域的 x 坐标。
     @param y 发生改变的对焦区域的 y 坐标。
     @param width 发生改变的对焦区域的宽度。
     @param height 发生改变的对焦区域的高度。
     */
    virtual void onCameraFocusAreaChanged(int x, int y, int width, int height) {
        (void)x;
        (void)y;
        (void)width;
        (void)height;
    }
#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
    /** @~english
     * Reports the face detection result of the local user. Applies to Android and iOS only.
     * @since v3.0.1
     *
     * Once you enable face detection by calling \ref IRtcEngine::enableFaceDetection "enableFaceDetection"(true), you can get the following information on the local user in real-time:
     * - The width and height of the local video.
     * - The position of the human face in the local video.
     * - The distance between the human face and the device screen. This value is based on the fitting calculation of the local video size and the position of the human face.
     *
     * @note
     * - If the SDK does not detect a face, it reduces the frequency of this callback to reduce power consumption on the local device.
     * - The SDK stops triggering this callback when a human face is in close proximity to the screen.
     * - On Android, the `distance` value reported in this callback may be slightly different from the actual distance. Therefore, Agora does not recommend using it for
     * accurate calculation.
     * @param imageWidth The width (px) of the local video.
     * @param imageHeight The height (px) of the local video.
     * @param vecRectangle The position and size of the human face on the local video:
     * - `x`: The x coordinate (px) of the human face in the local video. Taking the top left corner of the captured video as the origin,
     * the x coordinate represents the relative lateral displacement of the top left corner of the human face to the origin.
     * - `y`: The y coordinate (px) of the human face in the local video. Taking the top left corner of the captured video as the origin,
     * the y coordinate represents the relative longitudinal displacement of the top left corner of the human face to the origin.
     * - `width`: The width (px) of the human face in the captured video.
     * - `height`: The height (px) of the human face in the captured video.
     * @param vecDistance The distance (cm) between the human face and the screen.
     * @param numFaces The number of faces detected. If the value is 0, it means that no human face is detected.
     */
    /** @~chinese
     * 报告本地人脸检测结果。仅适用于 Android 和 iOS 平台。
     * @since v3.0.1
     *
     * 调用 \ref IRtcEngine::enableFaceDetection "enableFaceDetection"(true) 开启本地人脸检测后，你可以通过该回调实时获取以下人脸检测的信息：
     * - 摄像头采集的画面大小
     * - 人脸在画面中的位置
     * - 人脸距设备屏幕的距离
     *
     * 其中，人脸距设备屏幕的距离由 SDK 通过摄像头采集的画面大小和人脸在画面中的位置拟合计算得出。
     * @note
     * - 当检测到摄像头前没有人脸时，该回调触发频率会降低，以节省设备耗能。
     * - 当人脸距离设备屏幕过近时，SDK 不会触发该回调。
     * - Android 平台上，人脸距设备屏幕的距离（`distance`）值有一定误差，请不要用它进行精确计算。
     * @param imageWidth 摄像头采集画面的宽度 (px)。
     * @param imageHeight 摄像头采集画面的高度 (px)。
     * @param vecRectangle 检测到的人脸信息：
     * - `x`：人脸在画面中的 x 坐标 (px)。以摄像头采集画面的左上角为原点，x 坐标为人脸左上角相对于原点的横向位移。
     * - `y`：人脸在画面中的 y 坐标 (px)。以摄像头采集画面的左上角为原点，y 坐标为人脸左上角相对原点的纵向位移。
     * - `width`：人脸在画面中的宽度 (px)。
     * - `height`：人脸在画面中的高度 (px)。
     * @param vecDistance 人脸距设备屏幕的距离 (cm)。
     * @param numFaces 检测的人脸数量。如果为 0，则表示没有检测到人脸。
     */
    virtual void onFacePositionChanged(int imageWidth, int imageHeight, Rectangle* vecRectangle, int* vecDistance, int numFaces){
       (void)imageWidth;
       (void)imageHeight;
       (void)vecRectangle;
       (void)vecDistance;
        (void)numFaces;
    }
#endif
    /** @~english Occurs when the camera exposure area changes.

    The SDK triggers this callback when the local user changes the camera exposure position by calling the setCameraExposurePosition method.

     @note This callback is for Android and iOS only.

     @param x x coordinate of the changed camera exposure area.
     @param y y coordinate of the changed camera exposure area.
     @param width Width of the changed camera exposure area.
     @param height Height of the changed camera exposure area.
     */
    /** @~chinese 摄像头曝光区域已改变回调。
     该回调是由本地用户调用 setCameraExposurePosition 方法改变曝光位置触发的。

     @note 该回调只适用于 Android 和 iOS 平台。

     @param x 发生改变的曝光区域的 x 坐标。
     @param y 发生改变的曝光区域的 y 坐标。
     @param width 发生改变的曝光区域的宽度。
     @param height 发生改变的曝光区域的高度。
     */
    virtual void onCameraExposureAreaChanged(int x, int y, int width, int height) {
        (void)x;
        (void)y;
        (void)width;
        (void)height;
    }

    /** @~english Occurs when the audio mixing file playback finishes.

     **DEPRECATED**  use onAudioMixingStateChanged instead.

     You can start an audio mixing file playback by calling the \ref IRtcEngine::startAudioMixing "startAudioMixing" method. The SDK triggers this callback when the audio mixing file playback finishes.

     If the *startAudioMixing* method call fails, an error code returns in the \ref IRtcEngineEventHandler::onError "onError" callback.

     */
    /** @~chinese 本地音乐文件播放已结束回调。
    **DEPRECATED**  请改用 onAudioMixingStateChanged 。
     当调用 \ref agora::rtc::IRtcEngine::startAudioMixing "startAudioMixing" 播放本地音乐文件结束后，会触发该回调。
     如果调用  \ref agora::rtc::IRtcEngine::startAudioMixing "startAudioMixing" 失败，会在 \ref agora::rtc::IRtcEngineEventHandler::onError "onError" 回调里，返回错误码 #WARN_AUDIO_MIXING_OPEN_ERROR 。
     */
    virtual void onAudioMixingFinished() {
    }

    /** @~english Occurs when the state of the local user's audio mixing file changes.

     When you call the \ref IRtcEngine::startAudioMixing "startAudioMixing" method and the state of audio mixing file changes, the SDK triggers this callback.
     - When the audio mixing file plays, pauses playing, or stops playing, this callback returns 710, 711, or 713 in @p state, and 0 in @p errorCode.
     - When exceptions occur during playback, this callback returns 714 in @p state and an error in @p errorCode.
     - If the local audio mixing file does not exist, or if the SDK does not support the file format or cannot access the music file URL, the SDK returns WARN_AUDIO_MIXING_OPEN_ERROR = 701.

     @param state The state code. See #AUDIO_MIXING_STATE_TYPE.
     @param errorCode The error code. See #AUDIO_MIXING_ERROR_TYPE.
     */
    /** @~chinese 本地用户的音乐文件播放状态已改变回调。

     该回调在音乐文件播放状态发生改变时触发，并报告当前的播放状态和错误码。

     如果本地音乐文件不存在、文件格式不支持或无法访问在线音乐文件 URL，SDK 会返回警告码 #WARN_AUDIO_MIXING_OPEN_ERROR (701)。

     @param state 音乐文件播放状态，详见 #AUDIO_MIXING_STATE_TYPE
     @param errorCode 错误码，详见 #AUDIO_MIXING_ERROR_TYPE
     */
    virtual void onAudioMixingStateChanged(AUDIO_MIXING_STATE_TYPE state, AUDIO_MIXING_ERROR_TYPE errorCode){
    }
    /** @~english Occurs when a remote user starts audio mixing.

     When a remote user calls \ref IRtcEngine::startAudioMixing "startAudioMixing" to play the background music, the SDK reports this callback.
     */
    /** @~chinese 远端音乐文件播放已开始回调。

     当远端有用户调用 \ref agora::rtc::IRtcEngine::startAudioMixing "startAudioMixing" 播放本地音乐文件，会触发该回调。
     */
    virtual void onRemoteAudioMixingBegin() {
    }
    /** @~english Occurs when a remote user finishes audio mixing.
     */
    /** @~chinese 远端音乐文件播放已结束回调。

     当远端有用户播放本地音乐文件结束，会触发该回调。
     */
    virtual void onRemoteAudioMixingEnd() {
    }

    /** @~english Occurs when the local audio effect playback finishes.

     The SDK triggers this callback when the local audio effect file playback finishes.

     @param soundId ID of the local audio effect. Each local audio effect has a unique ID.
     */
    /** @~chinese 本地音效文件播放已结束回调。

     当播放音效结束后，会触发该回调。

     @param soundId 指定音效的 ID。每个音效均有唯一的 ID。
     */
    virtual void onAudioEffectFinished(int soundId) {
    }


    /** @~english
     Occurs when the SDK decodes the first remote audio frame for playback.

     @deprecated v3.0.0

     This callback is deprecated. Use `onRemoteAudioStateChanged` instead.

     This callback is triggered in either of the following scenarios:

     - The remote user joins the channel and sends the audio stream.
     - The remote user stops sending the audio stream and re-sends it after 15 seconds. Reasons for such an interruption include:
         - The remote user leaves channel.
         - The remote user drops offline.
         - The remote user calls the \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream" method to stop sending the local audio stream.
         - The remote user calls the \ref agora::rtc::IRtcEngine::disableAudio "disableAudio" method to disable audio.

     @param uid User ID of the remote user sending the audio stream.
     @param elapsed Time elapsed (ms) from the local user calling the \ref IRtcEngine::joinChannel "joinChannel" method until the SDK triggers this callback.
     */
    /** @~chinese
     已解码远端音频首帧的回调。

     @deprecated 该回调已废弃。请改用 \ref agora::rtc::IRtcEngineEventHandler::onRemoteAudioStateChanged "onRemoteAudioStateChanged"

     SDK 完成远端音频首帧解码，并发送给音频模块用以播放时，会触发此回调。有两种情况：
     - 远端用户首次上线后发送音频
     - 远端用户音频离线再上线发送音频。音频离线指本地在 15 秒内没有收到音频包，可能有如下原因：
         - 远端用户离开频道
         - 远端用户掉线
         - 远端用户调用 \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream" 方法停止发送音频流
         - 远端用户调用 \ref agora::rtc::IRtcEngine::disableAudio "disableAudio" 方法关闭音频

     @param uid 远端用户 ID
     @param elapsed 从本地用户调用 \ref IRtcEngine::joinChannel "joinChannel" 直至该回调触发的延迟，单位为毫秒。
     */
    virtual void onFirstRemoteAudioDecoded(uid_t uid, int elapsed) {
        (void)uid;
        (void)elapsed;
    }

    /** @~english Occurs when the video device state changes.

     @note On a Windows device with an external camera for video capturing, the video disables once the external camera is unplugged.

     @param deviceId Pointer to the device ID of the video device that changes state.
     @param deviceType Device type: #MEDIA_DEVICE_TYPE.
     @param deviceState Device state: #MEDIA_DEVICE_STATE_TYPE.
     */
    /** @~chinese 视频设备变化回调。

     @note 该回调提示系统视频设备状态发生改变，比如被拔出或移除。如果设备已使用外接摄像头采集，外接摄像头被拔开后，视频会中断。

     @param deviceId 设备 ID。
     @param deviceType 设备类型: #MEDIA_DEVICE_TYPE 。
     @param deviceState 设备状态: #MEDIA_DEVICE_STATE_TYPE 。
     */
    virtual void onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) {
        (void)deviceId;
        (void)deviceType;
        (void)deviceState;
    }

    /** @~english Occurs when the local video stream state changes.

     This callback indicates the state of the local video stream, including camera capturing and video encoding, and allows you to troubleshoot issues when exceptions occur.

     @note For some device models, the SDK will not trigger this callback when the state of the local video changes while the local video capturing device is in use, so you have to make your own timeout judgment.

     @param localVideoState State type #LOCAL_VIDEO_STREAM_STATE. When the state is LOCAL_VIDEO_STREAM_STATE_FAILED (3), see the `error` parameter for details.
     @param error The detailed error information: #LOCAL_VIDEO_STREAM_ERROR.
     */
    /** @~chinese 本地视频状态发生改变回调

     本地视频的状态发生改变时，SDK 会触发该回调返回当前的本地视频状态。

     在本地视频出现故障时，你可以通过该回调了解当前视频的状态以及出现故障的原因，方便排查问题。

     @note 对某些机型而言，当本地视频采集设备正在使用中时，SDK 不会在本地视频状态发生改变时触发该回调，你需要自行做超时判断。

     @param localVideoState 本地视频状态，详见: #LOCAL_VIDEO_STREAM_STATE 。当本地视频状态为 #LOCAL_VIDEO_STREAM_STATE_FAILED (3) 时，你可以在 `error` 参数中查看返回的错误原因。
     @param error 本地视频出错原因，详见: #LOCAL_VIDEO_STREAM_ERROR 。
     */
    virtual void onLocalVideoStateChanged(LOCAL_VIDEO_STREAM_STATE localVideoState, LOCAL_VIDEO_STREAM_ERROR error) {
        (void)localVideoState;
        (void)error;
    }

    /** @~english Occurs when the video size or rotation of a specified user changes.

     @param uid User ID of the remote user or local user (0) whose video size or rotation changes.
     @param width New width (pixels) of the video.
     @param height New height (pixels) of the video.
     @param rotation New rotation of the video [0 to 360).
     */
    /** @~chinese 本地或远端视频大小和旋转信息发生改变回调。

     @param uid 图像尺寸和旋转信息发生变化的用户的用户 ID（本地用户的 uid 为 0）。
     @param width 视频流的宽度（像素）。
     @param height 视频流的高度（像素）。
     @param rotation 旋转信息 [0,360)。
     */
    virtual void onVideoSizeChanged(uid_t uid, int width, int height, int rotation) {
        (void)uid;
        (void)width;
        (void)height;
        (void)rotation;
    }
    /** @~english Occurs when the remote video state changes.
     @note This callback does not work properly when the number of users (in the Communication profile) or broadcasters (in the Live-broadcast profile) in the channel exceeds 17.

     @param uid ID of the remote user whose video state changes.
     @param state State of the remote video. See #REMOTE_VIDEO_STATE.
     @param reason The reason of the remote video state change. See
     #REMOTE_VIDEO_STATE_REASON.
     @param elapsed Time elapsed (ms) from the local user calling the
     \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" method until the
     SDK triggers this callback.
     */
    /** @~chinese 远端视频状态发生改变回调。

     @note 频道内的用户（通信场景）或主播（直播场景）人数超过 17 人时，该回调不生效。

     @param uid 发生视频状态改变的远端用户 ID。
     @param state 远端视频流状态。详见 #REMOTE_VIDEO_STATE 。
     @param reason 远端视频流状态改变的具体原因。详见 #REMOTE_VIDEO_STATE_REASON 。
     @param elapsed 从本地用户调用 \ref agora::rtc::IRtcEngine::joinChannel
     "joinChannel" 方法到发生本事件经历的时间，单位为 ms。
     */
    virtual void onRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed) {
        (void)uid;
        (void)state;
        (void)reason;
        (void)elapsed;
    }

	/** @~english Occurs when a specified remote user enables/disables the local video
     * capturing function.
     *
     * @deprecated v2.9.0
     *
     * This callback is deprecated and replaced by the
     * \ref onRemoteVideoStateChanged() "onRemoteVideoStateChanged" callback
     * with the following parameters:
     * - #REMOTE_VIDEO_STATE_STOPPED (0) and
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5).
     * - #REMOTE_VIDEO_STATE_DECODING (2) and
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6).
     *
     * This callback is only applicable to the scenario when the user only
     * wants to watch the remote video without sending any video stream to the
     * other user.
     *
     * The SDK triggers this callback when the remote user resumes or stops
     * capturing the video stream by calling the
     * \ref agora::rtc::IRtcEngine::enableLocalVideo "enableLocalVideo" method.
     *
     * @param uid User ID of the remote user.
     * @param enabled Whether the specified remote user enables/disables the
     * local video capturing function:
     * - true: Enable. Other users in the channel can see the video of this
     * remote user.
     * - false: Disable. Other users in the channel can no longer receive the
     * video stream from this remote user, while this remote user can still
     * receive the video streams from other users.
     */
    /** @~chinese 其他用户启用/关闭本地视频。
     *
     * @deprecated 该回调已废弃，请改用 \ref onRemoteVideoStateChanged()
     * "onRemoteVideoStateChanged" 回调的：
     * - #REMOTE_VIDEO_STATE_STOPPED (0) 和
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED (5)。
     * - #REMOTE_VIDEO_STATE_DECODING (2) 和
     * #REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED (6)。
     *
     * 提示有其他用户启用/关闭了本地视频功能。关闭视频功能是指该用户只能进行语音通话，
     * 不能显示、发送自己的视频，也不能接收、显示别人的视频。
     *
     * 该回调是由远端用户调用 \ref agora::rtc::IRtcEngine::enableLocalVideo
     * "enableLocalVideo" 方法开启或关闭视频采集触发的。
     *
     * @param uid 用户 ID，提示是哪个用户的视频流。
     * @param enabled
     * - true: 该用户已启用视频功能。启用后，其他用户可以接收到该用户的视频流。
     * - false: 该用户已关闭视频功能。关闭后，该用户仍然可以接收其他用户的视频流，
     * 但其他用户接收不到该用户的视频流。
     */
    virtual void onUserEnableLocalVideo(uid_t uid, bool enabled) {
        (void)uid;
        (void)enabled;
    }

//    virtual void onStreamError(int streamId, int code, int parameter, const char* message, size_t length) {}
    /** @~english Occurs when the local user receives the data stream from the remote user within five seconds.

    The SDK triggers this callback when the local user receives the stream message that the remote user sends by calling the \ref agora::rtc::IRtcEngine::sendStreamMessage "sendStreamMessage" method.
    @param uid User ID of the remote user sending the message.
    @param streamId Stream ID.
    @param data Pointer to the data received by the local user.
    @param length Length of the data in bytes.
    */
    /** @~chinese 接收到对方数据流消息的回调。

     该回调表示本地用户收到了远端用户调用 \ref agora::rtc::IRtcEngine::sendStreamMessage "sendStreamMessage" 方法发送的流消息。

     @param uid 发送消息的用户 ID。
     @param streamId Stream ID。
     @param data 接收到的数据。
     @param length 数据长度。
     */
    virtual void onStreamMessage(uid_t uid, int streamId, const char* data, size_t length) {
        (void)uid;
        (void)streamId;
        (void)data;
        (void)length;
    }

	/** @~english Occurs when the local user does not receive the data stream from the remote user within five seconds.

     The SDK triggers this callback when the local user fails to receive the stream message that the remote user sends by calling the \ref agora::rtc::IRtcEngine::sendStreamMessage "sendStreamMessage" method.
     @param uid User ID of the remote user sending the message.
     @param streamId Stream ID.
     @param code Error code: #ERROR_CODE_TYPE.
     @param missed Number of lost messages.
     @param cached Number of incoming cached messages when the data stream is interrupted.
     */
    /** @~chinese 接收对方数据流消息发生错误的回调。

     该回调表示本地用户未收到远端用户调用 \ref agora::rtc::IRtcEngine::sendStreamMessage "sendStreamMessage" 方法发送的流消息。

     @param uid 发送消息的用户 ID。
     @param streamId Stream ID。
     @param code 错误码: #ERROR_CODE_TYPE 。
     @param missed 丢失的消息数量。
     @param cached 数据流中断时，后面缓存的消息数量。
     */
	virtual void onStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached) {
        (void)uid;
        (void)streamId;
        (void)code;
        (void)missed;
        (void)cached;
    }

    /** @~english Occurs when the media engine loads.*/
    /** @~chinese 媒体引擎成功加载的回调。*/
    virtual void onMediaEngineLoadSuccess() {
    }
    /** @~english Occurs when the media engine call starts.*/
    /** @~chinese 媒体引擎成功启动的回调。*/
    virtual void onMediaEngineStartCallSuccess() {
    }

    /** @~english Occurs when the state of the media stream relay changes.
     *
     * The SDK returns the state of the current media relay with any error
     * message.
     *
     * @param state The state code in #CHANNEL_MEDIA_RELAY_STATE.
     * @param code The error code in #CHANNEL_MEDIA_RELAY_ERROR.
     */
    /** @~chinese 跨频道媒体流转发状态发生改变回调。
     *
     * 当跨频道媒体流转发状态发生改变时，SDK 会触发该回调，
     * 并报告当前的转发状态以及相关的错误信息。
     *
     * @param state 跨频道媒体流转发状态。详见 #CHANNEL_MEDIA_RELAY_STATE 。
     * @param code 跨频道媒体流转发出错的错误码。详见 #CHANNEL_MEDIA_RELAY_ERROR 。
     */
    virtual void onChannelMediaRelayStateChanged(CHANNEL_MEDIA_RELAY_STATE state,CHANNEL_MEDIA_RELAY_ERROR code) {
    }

    /** @~english Reports events during the media stream relay.
     *
     * @param code The event code in #CHANNEL_MEDIA_RELAY_EVENT.
     */
    /** @~chinese 跨频道媒体流转发事件回调。
     *
     * 该回调报告跨频道媒体流转发过程中发生的事件。
     *
     * @param code 跨频道媒体流转发事件码。详见 #CHANNEL_MEDIA_RELAY_EVENT 。
     */
    virtual void onChannelMediaRelayEvent(CHANNEL_MEDIA_RELAY_EVENT code) {
    }

    /** @~english Occurs when the engine sends the first local audio frame.

    @param elapsed Time elapsed (ms) from the local user calling \ref IRtcEngine::joinChannel "joinChannel" until the SDK triggers this callback.
    */
    /** @~chinese 已发送本地音频首帧回调。
     *
     * @deprecated 该回调自 v3.1.0 废弃，请改用 \ref IRtcEngineEventHandler::onFirstLocalAudioFramePublished "onFirstLocalAudioFramePublished" 回调。
     *
     * @param elapsed 从调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 方法直至该回调被触发的时间。
     */
    virtual void onFirstLocalAudioFrame(int elapsed) {
        (void)elapsed;
    }

    /** @~english Occurs when the engine receives the first audio frame from a specific remote user.

    @deprecated v3.0.0

    This callback is deprecated. Use `onRemoteAudioStateChanged` instead.

    @param uid User ID of the remote user.
    @param elapsed Time elapsed (ms) from the remote user calling \ref IRtcEngine::joinChannel "joinChannel" until the SDK triggers this callback.
    */
    /** @~chinese 已接收远端音频首帧回调。

     @deprecated

     该回调已废弃。请改用 \ref agora::rtc::IRtcEngineEventHandler::onRemoteAudioStateChanged "onRemoteAudioStateChanged"

     @param uid 发送音频帧的远端用户的用户 ID。
     @param elapsed 从调用 \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" 方法直至该回调被触发的时间。
     */
    virtual void onFirstRemoteAudioFrame(uid_t uid, int elapsed) {
        (void)uid;
        (void)elapsed;
    }

  /** @~english
   Occurs when the state of the RTMP streaming changes.

   The SDK triggers this callback to report the result of the local user calling the \ref agora::rtc::IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" or \ref agora::rtc::IRtcEngine::removePublishStreamUrl "removePublishStreamUrl" method.

   This callback indicates the state of the RTMP streaming. When exceptions occur, you can troubleshoot issues by referring to the detailed error descriptions in the *errCode* parameter.

   @param url The RTMP URL address.
   @param state The RTMP streaming state. See: #RTMP_STREAM_PUBLISH_STATE.
   @param errCode The detailed error information for streaming. See: #RTMP_STREAM_PUBLISH_ERROR.
   */
  /** @~chinese RTMP/RTMPS 推流状态发生改变回调。

     该回调返回本地用户调用 \ref agora::rtc::IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" 或 \ref agora::rtc::IRtcEngine::removePublishStreamUrl "removePublishStreamUrl" 方法的结果。
     RTMP/RTMPS 推流状态发生改变时，SDK 会触发该回调，并在回调中明确状态发生改变的 URL 地址及当前推流状态。
     该回调方便推流用户了解当前的推流状态；推流出错时，你可以通过返回的错误码了解出错的原因，方便排查问题。

     @param url 推流状态发生改变的 URL 地址。
     @param state 当前的推流状态，详见 #RTMP_STREAM_PUBLISH_STATE 。当推流状态为 RTMP_STREAM_PUBLISH_STATE_FAILURE (4) 时，你可以在 errorCode 参数中查看返回的错误信息。
     @param errCode 推流错误信息，详见 #RTMP_STREAM_PUBLISH_ERROR 。
     */
  virtual void onRtmpStreamingStateChanged(const char *url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR errCode) {
    (void) url;
    (void) state;
    (void) errCode;
  }

    /** @~english @deprecated This method is deprecated, use the \ref agora::rtc::IRtcEngineEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" callback instead.

     Reports the result of calling the \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" method. (CDN live only.)

     @param url The RTMP URL address.
     @param error Error code: #ERROR_CODE_TYPE. Main errors include:
     - #ERR_OK (0): The publishing succeeds.
     - #ERR_FAILED (1): The publishing fails.
     - #ERR_INVALID_ARGUMENT (2): Invalid argument used. If, for example, you did not call \ref agora::rtc::IRtcEngine::setLiveTranscoding "setLiveTranscoding" to configure LiveTranscoding before calling \ref agora::rtc::IRtcEngine::addPublishStreamUrl "addPublishStreamUrl", the SDK reports #ERR_INVALID_ARGUMENT.
     - #ERR_TIMEDOUT (10): The publishing timed out.
     - #ERR_ALREADY_IN_USE (19): The chosen URL address is already in use for CDN live streaming.
     - #ERR_RESOURCE_LIMITED (22): The backend system does not have enough resources for the CDN live streaming.
     - #ERR_ENCRYPTED_STREAM_NOT_ALLOWED_PUBLISH (130): You cannot publish an encrypted stream.
     - #ERR_PUBLISH_STREAM_CDN_ERROR (151)
     - #ERR_PUBLISH_STREAM_NUM_REACH_LIMIT (152)
     - #ERR_PUBLISH_STREAM_NOT_AUTHORIZED (153)
     - #ERR_PUBLISH_STREAM_INTERNAL_SERVER_ERROR (154)
     - #ERR_PUBLISH_STREAM_FORMAT_NOT_SUPPORTED (156)
     */
    /** @~chinese 旁路推流已开启回调。

     @deprecated

     此方法已废弃，请改用 \ref agora::rtc::IRtcEngineEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged"

     该回调用于通知主播推流状态。

     @param url 主播推流的 URL 地址 。
     @param error #ERROR_CODE_TYPE 。
     - #ERR_OK (0): 推流成功。
     - #ERR_FAILED (1): 推流失败。
     - #ERR_INVALID_ARGUMENT (2): 参数错误。如果你在调用 \ref agora::rtc::IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" 前没有调用 \ref agora::rtc::IRtcEngine::setLiveTranscoding "setLiveTranscoding" 配置 LiveTranscoding ，SDK 会回调 #ERR_INVALID_ARGUMENT 。
     - #ERR_TIMEDOUT (10): 推流超时未成功。
     - #ERR_ALREADY_IN_USE (19): 推流地址已推流。
     - #ERR_ABORTED (20): SDK 与推流服务器断开连接。推流中断。
     - #ERR_RESOURCE_LIMITED (22): 后台没有足够资源推流。
     - #ERR_ENCRYPTED_STREAM_NOT_ALLOWED_PUBLISH (130): 推流已加密不能推流。
     - #ERR_PUBLISH_STREAM_CDN_ERROR (151)
     - #ERR_PUBLISH_STREAM_NUM_REACH_LIMIT (152)
     - #ERR_PUBLISH_STREAM_NOT_AUTHORIZED (153)
     - #ERR_PUBLISH_STREAM_INTERNAL_SERVER_ERROR (154)
     - #ERR_PUBLISH_STREAM_FORMAT_NOT_SUPPORTED (156)
     */
    virtual void onStreamPublished(const char *url, int error) {
        (void)url;
        (void)error;
    }
    /** @~english @deprecated This method is deprecated, use the \ref agora::rtc::IRtcEngineEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" callback instead.

     Reports the result of calling the \ref agora::rtc::IRtcEngine::removePublishStreamUrl "removePublishStreamUrl" method. (CDN live only.)

     This callback indicates whether you have successfully removed an RTMP stream from the CDN.

     @param url The RTMP URL address.
     */
    /** @~chinese 旁路推流已停止回调。

     @deprecated 此方法已废弃，请改用 \ref agora::rtc::IRtcEngineEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged"

     回调用于通知主播停止推流成功。

     @param url 被删除的 RTMP/RTMPS 推流地址。
     */
    virtual void onStreamUnpublished(const char *url) {
        (void)url;
    }
/** @~english Occurs when the publisher's transcoding is updated.
 *
 * When the `LiveTranscoding` class in the \ref agora::rtc::IRtcEngine::setLiveTranscoding "setLiveTranscoding" method updates, the SDK triggers the `onTranscodingUpdated` callback to report the update information to the local host.
 *
 * @note If you call the `setLiveTranscoding` method to set the LiveTranscoding class for the first time, the SDK does not trigger the `onTranscodingUpdated` callback.
 *
 */
/** @~chinese 旁路推流设置已被更新回调。
     *
     * \ref agora::rtc::IRtcEngine::setLiveTranscoding "setLiveTranscoding" 方法中的直播参数 `LiveTranscoding` 更新时，`onTranscodingUpdated` 回调会被触发并向主播报告更新信息。
     *
     * @note 首次调用 `setLiveTranscoding` 方法设置转码参数 `LiveTranscoding` 时，不会触发此回调。
     *
     */
    virtual void onTranscodingUpdated() {
    }
   /** @~english Occurs when a voice or video stream URL address is added to a live broadcast.

    @param url Pointer to the URL address of the externally injected stream.
    @param uid User ID.
    @param status State of the externally injected stream: #INJECT_STREAM_STATUS.
    */
    /** @~chinese 输入在线媒体流状态回调。

     @param url 在线媒体流的地址。
     @param uid 用户 ID。
     @param status 输入的在线媒体流状态: #INJECT_STREAM_STATUS 。
     */
    virtual void onStreamInjectedStatus(const char* url, uid_t uid, int status) {
        (void)url;
        (void)uid;
        (void)status;
    }

    /** @~english Occurs when the local audio route changes.

     The SDK triggers this callback when the local audio route switches to an earpiece, speakerphone, headset, or Bluetooth device.

     @note This callback is for Android and iOS only.

     @param routing Audio output routing. See: #AUDIO_ROUTE_TYPE.
     */
    /** @~chinese 语音路由已发生变化回调。

     当语音路由发生变化时，SDK 会触发此回调。

     @note 该回调仅适用于安卓和 iOS 。

     @param routing 当前的语音路由。详见： #AUDIO_ROUTE_TYPE 。
     */
    virtual void onAudioRouteChanged(AUDIO_ROUTE_TYPE routing) {
		(void)routing;
	}

   /** @~english Occurs when the published media stream falls back to an audio-only stream due to poor network conditions or switches back to the video after the network conditions improve.

    If you call \ref IRtcEngine::setLocalPublishFallbackOption "setLocalPublishFallbackOption" and set *option* as #STREAM_FALLBACK_OPTION_AUDIO_ONLY, the SDK triggers this callback when the
    published stream falls back to audio-only mode due to poor uplink conditions, or when the audio stream switches back to the video after the uplink network condition improves.
    @note If the local stream fallbacks to the audio-only stream, the remote user receives the \ref IRtcEngineEventHandler::onUserMuteVideo "onUserMuteVideo" callback.

    @param isFallbackOrRecover Whether the published stream falls back to audio-only or switches back to the video:
    - true: The published stream falls back to audio-only due to poor network conditions.
    - false: The published stream switches back to the video after the network conditions improve.
    */
    /** @~chinese 本地发布流已回退为音频流回调。

     如果你调用了 \ref agora::rtc::IRtcEngine::setLocalPublishFallbackOption "setLocalPublishFallbackOption" 接口并将 option 设置为 #STREAM_FALLBACK_OPTION_AUDIO_ONLY ，当上行网络环境不理想、本地发布的媒体流回退为音频流时，或当上行网络改善、媒体流恢复为音视频流时，会触发该回调。

     @note 如果本地发流已回退为音频流，远端的 App 上会收到 \ref agora::rtc::IRtcEngineEventHandler::onUserMuteVideo "onUserMuteVideo" 的回调事件。

     @param isFallbackOrRecover
     - true: 由于网络环境不理想，本地发布的媒体流已回退为音频流；
     - false: 由于网络环境改善，发布的音频流已恢复为音视频流。
     */
    virtual void onLocalPublishFallbackToAudioOnly(bool isFallbackOrRecover) {
        (void)isFallbackOrRecover;
    }

    /** @~english Occurs when the remote media stream falls back to audio-only stream
     * due to poor network conditions or switches back to the video stream
     * after the network conditions improve.
     *
     * If you call
     * \ref IRtcEngine::setRemoteSubscribeFallbackOption
     * "setRemoteSubscribeFallbackOption" and set
     * @p option as #STREAM_FALLBACK_OPTION_AUDIO_ONLY, the SDK triggers this
     * callback when the remote media stream falls back to audio-only mode due
     * to poor uplink conditions, or when the remote media stream switches
     * back to the video after the uplink network condition improves.
     *
     * @note Once the remote media stream switches to the low stream due to
     * poor network conditions, you can monitor the stream switch between a
     * high and low stream in the RemoteVideoStats callback.
     *
     * @param uid ID of the remote user sending the stream.
     * @param isFallbackOrRecover Whether the remotely subscribed media stream
     * falls back to audio-only or switches back to the video:
     * - true: The remotely subscribed media stream falls back to audio-only
     * due to poor network conditions.
     * - false: The remotely subscribed media stream switches back to the
     * video stream after the network conditions improved.
     */
    /** @~chinese 远端订阅流已回退为音频流回调。

     如果你调用了 \ref agora::rtc::IRtcEngine::setRemoteSubscribeFallbackOption "setRemoteSubscribeFallbackOption" 接口并将 option 设置为 #STREAM_FALLBACK_OPTION_AUDIO_ONLY ，当下行网络环境不理想、仅接收远端音频流时，或当下行网络改善、恢复订阅音视频流时，会触发该回调。

     @note 远端订阅流因弱网环境不能同时满足音视频而回退为小流时，你可以使用 RemoteVideoStats 来监控远端视频大小流的切换。

     @param uid    远端用户的用户 ID。
     @param  isFallbackOrRecover
     - true: 由于网络环境不理想，远端订阅流已回退为音频流；
     - false: 由于网络环境改善，订阅的音频流已恢复为音视频流。
     */
    virtual void onRemoteSubscribeFallbackToAudioOnly(uid_t uid, bool isFallbackOrRecover) {
        (void)uid;
        (void)isFallbackOrRecover;
    }

    /** @~english Reports the transport-layer statistics of each remote audio stream.
     *
     * @deprecated
     * This callback is deprecated and replaced by the
     * \ref onRemoteAudioStats() "onRemoteAudioStats" callback.
     *
     * This callback reports the transport-layer statistics, such as the
     * packet loss rate and network time delay, once every two seconds after
     * the local user receives an audio packet from a remote user.
     *
     * @param uid  User ID of the remote user sending the audio packet.
     * @param delay Network time delay (ms) from the remote user sending the
     * audio packet to the local user.
     * @param lost Packet loss rate (%) of the audio packet sent from the
     * remote user.
     * @param rxKBitRate  Received bitrate (Kbps) of the audio packet sent
     * from the remote user.
     */
    /** @~chinese @deprecated 通话中远端音频流传输的统计信息回调。
     *
     * 该回调已废弃，请改用 \ref onRemoteAudioStats() "onRemoteAudioStats"。
     *
     * 该回调描述远端用户通话中端到端的网络统计信息，通过音频包计算，用客观的数据，如丢包、
     * 网络延迟等，展示当前网络状态。
     *
     * 通话中，当用户收到远端用户/主播发送的音频数据包后 ，会每 2 秒触发一次该回调。
     *
     * 和 \ref agora::rtc::IRtcEngineEventHandler::onRemoteAudioStats
     * "onRemoteAudioStats" 回调相比，该回调以数据展示当前网络状态，因此更客观。
     *
     * @param uid  用户 ID，指定是哪个用户/主播的音频包。
     * @param delay 音频包从发送端到接收端的延时（毫秒）。
     * @param lost 音频包从发送端到接收端的丢包率 (%)。
     * @param rxKBitRate  远端音频包的接收码率（Kbps）。
     */
    virtual void onRemoteAudioTransportStats(
        uid_t uid, unsigned short delay, unsigned short lost,
        unsigned short rxKBitRate) {
        (void)uid;
        (void)delay;
        (void)lost;
        (void)rxKBitRate;
    }

    /** @~english Reports the transport-layer statistics of each remote video stream.
     *
     * @deprecated
     * This callback is deprecated and replaced by the
     * \ref onRemoteVideoStats() "onRemoteVideoStats" callback.
     *
     * This callback reports the transport-layer statistics, such as the
     * packet loss rate and network time delay, once every two seconds after
     * the local user receives a video packet from a remote user.
     *
     * @param uid User ID of the remote user sending the video packet.
     * @param delay Network time delay (ms) from the remote user sending the
     * video packet to the local user.
     * @param lost Packet loss rate (%) of the video packet sent from the
     * remote user.
     * @param rxKBitRate Received bitrate (Kbps) of the video packet sent
     * from the remote user.
     */
    /** @~chinese @deprecated 通话中远端视频流传输的统计信息回调。
     *
     * 该回调已废弃，请改用 \ref onRemoteVideoStats() "onRemoteVideoStats"。
     *
     * 该回调描述远端用户通话中端到端的网络统计信息，通过视频包计算，用客观的数据，如丢包、
     * 网络延迟等，展示当前网络状态。
     *
     * 通话中，当用户收到远端用户/主播发送的视频数据包后，会每 2 秒触发一次该回调。
     *
     * 和 \ref agora::rtc::IRtcEngineEventHandler::onRemoteVideoStats
     * "onRemoteVideoStats" 回调相比，该回调以数据展示当前网络状态，因此更客观。
     *
     * @param uid 用户 ID，指定是哪个用户/主播的视频包。
     * @param delay 视频包从发送端到接收端的延时（毫秒）。
     * @param lost 视频包从发送端到接收端的丢包率 (%)。
     * @param rxKBitRate 远端视频包的接收码率（Kbps）。
     */
    virtual void onRemoteVideoTransportStats(
        uid_t uid, unsigned short delay, unsigned short lost,
        unsigned short rxKBitRate) {
        (void)uid;
        (void)delay;
        (void)lost;
        (void)rxKBitRate;
    }

    /** @~english Occurs when the microphone is enabled/disabled.
     *
     * @deprecated v2.9.0
     *
     * The \ref onMicrophoneEnabled() "onMicrophoneEnabled" callback is
     * deprecated. Use #LOCAL_AUDIO_STREAM_STATE_STOPPED (0) or
     * #LOCAL_AUDIO_STREAM_STATE_RECORDING (1) in the
     * \ref onLocalAudioStateChanged() "onLocalAudioStateChanged" callback
     * instead.
     *
     * The SDK triggers this callback when the local user resumes or stops
     * capturing the local audio stream by calling the
     * \ref agora::rtc::IRtcEngine::enableLocalAudio "enbaleLocalAudio" method.
     *
     * @param enabled Whether the microphone is enabled/disabled:
     * - true: Enabled.
     * - false: Disabled.
     */
    /** @~chinese 麦克风状态已改变回调。
     *
     * @deprecated 此方法已废弃，请改用 \ref onLocalAudioStateChanged()
     * "onLocalAudioStateChanged" 回调的：
     * - #LOCAL_AUDIO_STREAM_STATE_STOPPED (0)。
     * - #LOCAL_AUDIO_STREAM_STATE_RECORDING (1)。
     *
     * 该回调由本地用户调用
     * \ref agora::rtc::IRtcEngine::enableLocalAudio "enableLocalAudio"
     * 方法开启或关闭本地音频采集触发的.
     *
     * @param enabled
     * - true: 麦克风已启用；
     * - false: 麦克风已禁用。
     */
    virtual void onMicrophoneEnabled(bool enabled) {
        (void)enabled;
    }
    /** @~english Occurs when the connection state between the SDK and the server changes.

     @param state See #CONNECTION_STATE_TYPE.
     @param reason See #CONNECTION_CHANGED_REASON_TYPE.
     */
    /** @~chinese 网络连接状态已改变回调。

     该回调在网络连接状态发生改变的时候触发，并告知用户当前的网络连接状态和引起网络状态改变的原因。

     @param state 详见： #CONNECTION_STATE_TYPE 。
     @param reason 详见： #CONNECTION_CHANGED_REASON_TYPE 。
     */
    virtual void onConnectionStateChanged(
        CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason) {
      (void)state;
      (void)reason;
    }

    /** @~english Occurs when the local network type changes.

	When the network connection is interrupted, this callback indicates whether the interruption is caused by a network type change or poor network conditions.

     @param type See #NETWORK_TYPE.
     */
    /** @~chinese 本地网络类型发生改变回调。

     本地网络连接类型发生改变时，SDK 会触发该回调，并在回调中明确当前的网络连接类型。

     你可以通过该回调获取正在使用的网络类型；当连接中断时，该回调能辨别引起中断的原因是网络切换还是网络条件不好。

     @param type 详见： #NETWORK_TYPE 。
     */
    virtual void onNetworkTypeChanged(NETWORK_TYPE type) {
      (void)type;
    }
    /** @~english Occurs when the local user successfully registers a user account by calling the \ref agora::rtc::IRtcEngine::registerLocalUserAccount "registerLocalUserAccount" method or joins a channel by calling the \ref agora::rtc::IRtcEngine::joinChannelWithUserAccount "joinChannelWithUserAccount" method.This callback reports the user ID and user account of the local user.

     @param uid The ID of the local user.
     @param userAccount The user account of the local user.
     */
    /** @~chinese 本地用户成功注册 User Account 回调。

     本地用户成功调用 \ref agora::rtc::IRtcEngine::registerLocalUserAccount "registerLocalUserAccount" 方法注册用户 User Account 或
     调用 \ref agora::rtc::IRtcEngine::joinChannelWithUserAccount "joinChannelWithUserAccount" 加入频道后，
     SDK 会触发该回调，并告知本地用户的 UID 和 User Account。

     @param uid 本地用户的 UID
     @param userAccount 本地用户的 User Account
     */
    virtual void onLocalUserRegistered(uid_t uid, const char* userAccount) {
      (void)uid;
      (void)userAccount;
    }
    /** @~english Occurs when the SDK gets the user ID and user account of the remote user.

     After a remote user joins the channel, the SDK gets the UID and user account of the remote user,
     caches them in a mapping table object (`userInfo`), and triggers this callback on the local client.

     @param uid The ID of the remote user.
     @param info The `UserInfo` object that contains the user ID and user account of the remote user.
     */
    /** @~chinese 远端用户信息已更新回调。

     远端用户加入频道后， SDK 会获取到该远端用户的 UID 和 User Account，然后缓存一个包含了远端用户 UID 和 User Account 的 Mapping 表，
     并在本地触发该回调。

     @param uid 远端用户的 UID
     @param info 标识用户信息的 `UserInfo` 对象，包含用户 UID 和 User Account
     */
    virtual void onUserInfoUpdated(uid_t uid, const UserInfo& info) {
      (void)uid;
      (void)info;
    }
};

/**
* Video device collection methods.

 The IVideoDeviceCollection interface class retrieves the video device information.
*/
class IVideoDeviceCollection
{
protected:
    virtual ~IVideoDeviceCollection(){}
public:
    /** Retrieves the total number of the indexed video devices in the system.

    @return Total number of the indexed video devices:
    */
    virtual int getCount() = 0;

    /** Retrieves a specified piece of information about an indexed video device.

     @param index The specified index of the video device that must be less than the return value of \ref IVideoDeviceCollection::getCount "getCount".
     @param deviceName Pointer to the video device name.
     @param deviceId Pointer to the video device ID.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getDevice(int index, char deviceName[MAX_DEVICE_ID_LENGTH], char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Sets the device with the device ID.

     @param deviceId Device ID of the device.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Releases all IVideoDeviceCollection resources.
    */
    virtual void release() = 0;
};

/** Video device management methods.

 The IVideoDeviceManager interface class tests the video device interfaces. Instantiate an AVideoDeviceManager class to retrieve an IVideoDeviceManager interface.
*/
class IVideoDeviceManager
{
protected:
    virtual ~IVideoDeviceManager(){}
public:

    /** Enumerates the video devices.

     This method returns an IVideoDeviceCollection object including all video devices in the system. With the IVideoDeviceCollection object, the application can enumerate the video devices. The application must call the \ref IVideoDeviceCollection::release "release" method to release the returned object after using it.

     @return
     - An IVideoDeviceCollection object including all video devices in the system: Success.
     - NULL: Failure.
     */
    virtual IVideoDeviceCollection* enumerateVideoDevices() = 0;

    /** Starts the video-capture device test.

     This method tests whether the video-capture device works properly. Before calling this method, ensure that you have already called the \ref IRtcEngine::enableVideo "enableVideo" method, and the window handle (*hwnd*) parameter is valid.

     @param hwnd The window handle used to display the screen.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int startDeviceTest(view_t hwnd) = 0;

    /** Stops the video-capture device test.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int stopDeviceTest() = 0;

    /** Sets a device with the device ID.

     @param deviceId Pointer to the video-capture device ID. Call the \ref IVideoDeviceManager::enumerateVideoDevices "enumerateVideoDevices" method to retrieve it.

     @note Plugging or unplugging the device does not change the device ID.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Retrieves the video-capture device that is in use.

     @param deviceId Pointer to the video-capture device ID.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getDevice(char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Releases all IVideoDeviceManager resources.
    */
    virtual void release() = 0;
};

/** Audio device collection methods.

The IAudioDeviceCollection interface class retrieves device-related information.
*/
class IAudioDeviceCollection
{
protected:
    virtual ~IAudioDeviceCollection(){}
public:

    /** Retrieves the total number of audio playback or audio recording devices.

     @note You must first call the \ref IAudioDeviceManager::enumeratePlaybackDevices "enumeratePlaybackDevices" or \ref IAudioDeviceManager::enumerateRecordingDevices "enumerateRecordingDevices" method before calling this method to return the number of  audio playback or audio recording devices.

     @return Number of audio playback or audio recording devices.
     */
    virtual int getCount() = 0;

    /** Retrieves a specified piece of information about an indexed audio device.

     @param index The specified index that must be less than the return value of \ref IAudioDeviceCollection::getCount "getCount".
     @param deviceName Pointer to the audio device name.
     @param deviceId Pointer to the audio device ID.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getDevice(int index, char deviceName[MAX_DEVICE_ID_LENGTH], char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Specifies a device with the device ID.

     @param deviceId Pointer to the device ID of the device.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Sets the volume of the application.

    @param volume Application volume. The value ranges between 0 (lowest volume) and 255 (highest volume).
    @return
    - 0: Success.
    - < 0: Failure.
    */
    virtual int setApplicationVolume(int volume) = 0;

    /** Retrieves the volume of the application.

     @param volume Pointer to the application volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getApplicationVolume(int& volume) = 0;

    /** Mutes the application.

     @param mute Sets whether to mute/unmute the application:
     - true: Mute the application.
     - false: Unmute the application.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setApplicationMute(bool mute) = 0;
    /** Gets the mute state of the application.

     @param mute Pointer to whether the application is muted/unmuted.
     - true: The application is muted.
     - false: The application is not muted.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int isApplicationMute(bool& mute) = 0;

    /** Releases all IAudioDeviceCollection resources.
    */
    virtual void release() = 0;
};
/** Audio device management methods.

 The IAudioDeviceManager interface class allows for audio device interface testing. Instantiate an AAudioDeviceManager class to retrieve the IAudioDeviceManager interface.
*/
class IAudioDeviceManager
{
protected:
    virtual ~IAudioDeviceManager(){}
public:

    /** Enumerates the audio playback devices.

     This method returns an IAudioDeviceCollection object that includes all audio playback devices in the system. With the IAudioDeviceCollection object, the application can enumerate the audio playback devices.

     @note The application must call the \ref IAudioDeviceCollection::release "release" method to release the returned object after using it.

     @return
     - Success: Returns an IAudioDeviceCollection object that includes all audio playback devices in the system. For wireless Bluetooth headset devices with master and slave headsets, the master headset is the playback device.
     - Returns NULL: Failure.
     */
    virtual IAudioDeviceCollection* enumeratePlaybackDevices() = 0;

    /** Enumerates the audio recording devices.

     This method returns an IAudioDeviceCollection object that includes all audio recording devices in the system. With the IAudioDeviceCollection object, the application can enumerate the audio recording devices.

     @note The application needs to call the \ref IAudioDeviceCollection::release "release" method to release the returned object after using it.

     @return
     - Returns an IAudioDeviceCollection object that includes all audio recording devices in the system: Success.
     - Returns NULL: Failure.
     */
    virtual IAudioDeviceCollection* enumerateRecordingDevices() = 0;

    /** Sets the audio playback device using the device ID.

     @note Plugging or unplugging the audio device does not change the device ID.

     @param deviceId Device ID of the audio playback device, retrieved by calling the \ref IAudioDeviceManager::enumeratePlaybackDevices "enumeratePlaybackDevices" method.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setPlaybackDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Sets the audio recording device using the device ID.

     @param deviceId Device ID of the audio recording device, retrieved by calling the \ref IAudioDeviceManager::enumerateRecordingDevices "enumerateRecordingDevices" method.

     @note Plugging or unplugging the audio device does not change the device ID.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setRecordingDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Starts the audio playback device test.

     This method tests if the playback device works properly. In the test, the SDK plays an audio file specified by the user. If the user can hear the audio, the playback device works properly.

     @param testAudioFilePath Pointer to the path of the audio file for the audio playback device test in UTF-8:
     - Supported file formats: wav, mp3, m4a, and aac.
     - Supported file sample rates: 8000, 16000, 32000, 44100, and 48000 Hz.

     @return
     - 0: Success, and you can hear the sound of the specified audio file.
     - < 0: Failure.
     */
    virtual int startPlaybackDeviceTest(const char* testAudioFilePath) = 0;

    /** Stops the audio playback device test.

     This method stops testing the audio playback device. You must call this method to stop the test after calling the \ref IAudioDeviceManager::startPlaybackDeviceTest "startPlaybackDeviceTest" method.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int stopPlaybackDeviceTest() = 0;

    /** Sets the volume of the audio playback device.

     @param volume Sets the volume of the audio playback device. The value ranges between 0 (lowest volume) and 255 (highest volume).
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setPlaybackDeviceVolume(int volume) = 0;

    /** Retrieves the volume of the audio playback device.

     @param volume Pointer to the audio playback device volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getPlaybackDeviceVolume(int *volume) = 0;

    /** Sets the volume of the microphone.

     @param volume Sets the volume of the microphone. The value ranges between 0 (lowest volume) and 255 (highest volume).
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setRecordingDeviceVolume(int volume) = 0;

    /** Retrieves the volume of the microphone.

     @param volume Pointer to the microphone volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getRecordingDeviceVolume(int *volume) = 0;

    /** Mutes the audio playback device.

     @param mute Sets whether to mute/unmute the audio playback device:
     - true: Mutes.
     - false: Unmutes.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setPlaybackDeviceMute(bool mute) = 0;
    /** Retrieves the mute status of the audio playback device.

     @param mute Pointer to whether the audio playback device is muted/unmuted.
     - true: Muted.
     - false: Unmuted.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getPlaybackDeviceMute(bool *mute) = 0;
    /** Mutes/Unmutes the microphone.

     @param mute Sets whether to mute/unmute the microphone:
     - true: Mutes.
     - false: Unmutes.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setRecordingDeviceMute(bool mute) = 0;

    /** Retrieves the microphone's mute status.

     @param mute Pointer to whether the microphone is muted/unmuted.
     - true: Muted.
     - false: Unmuted.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getRecordingDeviceMute(bool *mute) = 0;

    /** Starts the microphone test.

     This method tests whether the microphone works properly. Once the test starts, the SDK uses the \ref IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" callback to notify the application with the volume information.

     @param indicationInterval Interval period (ms) of the \ref IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" callback cycle.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int startRecordingDeviceTest(int indicationInterval) = 0;

    /** Stops the microphone test.

     This method stops the microphone test. You must call this method to stop the test after calling the \ref IAudioDeviceManager::startRecordingDeviceTest "startRecordingDeviceTest" method.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int stopRecordingDeviceTest() = 0;

    /** Retrieves the audio playback device associated with the device ID.

     @param deviceId Pointer to the ID of the audio playback device.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getPlaybackDevice(char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Retrieves the audio playback device information associated with the device ID and device name.

     @param deviceId Pointer to the device ID of the audio playback device.
     @param deviceName Pointer to the device name of the audio playback device.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getPlaybackDeviceInfo(char deviceId[MAX_DEVICE_ID_LENGTH], char deviceName[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Retrieves the audio recording device associated with the device ID.

     @param deviceId Pointer to the device ID of the audio recording device.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getRecordingDevice(char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Retrieves the audio recording device information associated with the device ID and device name.

     @param deviceId Pointer to the device ID of the recording audio device.
     @param deviceName Pointer to the device name of the recording audio device.
     @return
     - 0: Success.
     - < 0: Failure.
     */
   virtual int getRecordingDeviceInfo(char deviceId[MAX_DEVICE_ID_LENGTH], char deviceName[MAX_DEVICE_ID_LENGTH]) = 0;

   /** Starts the audio device loopback test.

   This method tests whether the local audio devices are working properly. After calling this method, the microphone captures the local audio and plays it through the speaker. The \ref IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" callback returns the local audio volume information at the set interval.

   @note This method tests the local audio devices and does not report the network conditions.

   @param indicationInterval The time interval (ms) at which the \ref IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" callback returns.

   @return
   - 0: Success.
   - < 0: Failure.
   */
   virtual int startAudioDeviceLoopbackTest(int indicationInterval) = 0;

   /** Stops the audio device loopback test.

   @note Ensure that you call this method to stop the loopback test after calling the \ref IAudioDeviceManager::startAudioDeviceLoopbackTest "startAudioDeviceLoopbackTest" method.

   @return
   - 0: Success.
   - < 0: Failure.
   */
   virtual int stopAudioDeviceLoopbackTest() = 0;

   /** Releases all IAudioDeviceManager resources.
   */
    virtual void release() = 0;
};

/** Definition of RtcEngineContext.
*/
struct RtcEngineContext
{
    /** The IRtcEngineEventHandler object.
     */
    IRtcEngineEventHandler* eventHandler;
    /**
     * The App ID issued to you by Agora. See [How to get the App ID](https://docs.agora.io/en/Agora%20Platform/token#get-an-app-id).
     * Only users in apps with the same App ID can join the same channel and communicate with each other. Use an App ID to create only one `IRtcEngine` instance. To change your App ID, call `release` to destroy the current `IRtcEngine` instance and then call `createAgoraRtcEngine`
     * and `initialize` to create an `IRtcEngine` instance with the new App ID.
     */
    const char* appId;
    // For android, it the context(Activity or Application
	// for windows,Video hot plug device
    /** The video window handle. Once set, this parameter enables you to plug
     * or unplug the video devices while they are powered.
     */
	void* context;
    /**
     * The area of connection. This advanced feature applies to scenarios that have regional restrictions.
     *
     * You can use the bitwise OR operator (|) to specify multiple areas. For details, see #AREA_CODE.
     *
     * After specifying the area of connection:
     * - When the app that integrates the Agora SDK is used within the specified area, it connects to the Agora servers within the specified area under normal circumstances.
     * - When the app that integrates the Agora SDK is used out of the specified area, it connects to the Agora servers either in the specified area or in the area where the app is located.
     */
	int areaCode;
    RtcEngineContext()
    :eventHandler(NULL)
    ,appId(NULL)
    ,context(NULL)
    ,areaCode(rtc::AREA_CODE_GLOBAL)
    {}
};

/** Definition of IMetadataObserver
*/
class IMetadataObserver
{
public:
    /** Metadata type of the observer.
     @note We only support video metadata for now.
     */
    enum METADATA_TYPE
    {
        /** -1: the metadata type is unknown.
         */
        UNKNOWN_METADATA = -1,
        /** 0: the metadata type is video.
         */
        VIDEO_METADATA = 0,
    };

    struct Metadata
    {
        /** The User ID.

         - For the receiver: the ID of the user who sent the metadata.
         - For the sender: ignore it.
         */
        unsigned int uid;
        /** Buffer size of the sent or received Metadata.
         */
        unsigned int size;
        /** Buffer address of the sent or received Metadata.
         */
        unsigned char *buffer;
        /** Time statmp of the frame following the metadata.
         */
        long long timeStampMs;
    };

    virtual ~IMetadataObserver() {};

    /** Occurs when the SDK requests the maximum size of the Metadata.

     The metadata includes the following parameters:
     - `uid`: ID of the user who sends the metadata.
     - `size`: The size of the sent or received metadata.
     - `buffer`: The sent or received metadata.
     - `timeStampMs`: The timestamp of the metadata.

     The SDK triggers this callback after you successfully call the \ref agora::rtc::IRtcEngine::registerMediaMetadataObserver "registerMediaMetadataObserver" method. You need to specify the maximum size of the metadata in the return value of this callback.

     @return The maximum size of the buffer of the metadata that you want to use. The highest value is 1024 bytes. Ensure that you set the return value.
     */
    virtual int getMaxMetadataSize() = 0;

    /** Occurs when the SDK is ready to receive and send metadata.

     @note Ensure that the size of the metadata does not exceed the value set in the \ref agora::rtc::IMetadataObserver::getMaxMetadataSize "getMaxMetadataSize" callback.

     @param metadata The Metadata to be sent.
     @return
     - true:  Send.
     - false: Do not send.
     */
    virtual bool onReadyToSendMetadata(Metadata &metadata) = 0;

    /** Occurs when the local user receives the metadata.

     @param metadata The received Metadata.
     */
    virtual void onMetadataReceived(const Metadata &metadata) = 0;
};

/** IRtcEngine is the base interface class of the Agora SDK that provides the main Agora SDK methods invoked by your application.

Enable the Agora SDK's communication functionality through the creation of an IRtcEngine object, then call the methods of this object.
 */
class IRtcEngine
{
protected:
    virtual ~IRtcEngine() {}
public:

    /** Initializes the Agora service.
     *
     * Unless otherwise specified, all the methods provided by the IRtcEngine class are executed asynchronously. Agora recommends calling these methods in the same thread.
     *
     * @note Ensure that you call the
     * \ref agora::rtc::IRtcEngine::createAgoraRtcEngine
     * "createAgoraRtcEngine" and \ref agora::rtc::IRtcEngine::initialize
     * "initialize" methods before calling any other APIs.
     *
     * @param context Pointer to the RTC engine context. See RtcEngineContext.
     *
     * @return
     * - 0: Success.
     * - < 0: Failure.
     *  - `ERR_INVALID_APP_ID (101)`: The app ID is invalid. Check if it is in the correct format.
     */
    virtual int initialize(const RtcEngineContext& context) = 0;

    /** Releases all IRtcEngine resources.

     @note
     - If you want to create a new `IRtcEngine` instance after releasing the current one,
     ensure that you wait till this method is executed.
     - Do not immediately uninstall the SDK's dynamic library after the call, or it may cause a crash due to the SDK clean-up thread not quitting.

     @param sync
     - true: (Synchronous call) The result returns after the IRtcEngine resources are released. The application should not call this method in the SDK generated callbacks. Otherwise, the SDK must wait for the callbacks to return to recover the associated IRtcEngine resources, resulting in a deadlock. The SDK automatically detects the deadlock and converts this method into an asynchronous call, causing the test to take additional time.
     - false: (Asynchronous call) The result returns immediately, even when the IRtcEngine resources have not been released. The SDK releases all resources.
     */
    AGORA_CPP_API static void release (bool sync = false);

    /** Sets the channel profile of the Agora IRtcEngine.

     The Agora IRtcEngine differentiates channel profiles and applies optimization algorithms accordingly.
     For example, it prioritizes smoothness and low latency for a video call, and prioritizes video quality for a video broadcast.

     @warning
     - To ensure the quality of real-time communication, we recommend that all users in a channel use the same channel profile.
     - Call this method before calling \ref IRtcEngine::joinChannel "joinChannel" . You cannot set the channel profile once you have joined the channel.

     @param profile The channel profile of the Agora IRtcEngine. See #CHANNEL_PROFILE_TYPE
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setChannelProfile(CHANNEL_PROFILE_TYPE profile) = 0;

    /** Sets the role of the user, such as a host or an audience (default), before joining a channel in a live broadcast.

     This method can be used to switch the user role in a live broadcast after the user joins a channel.

     In the Live Broadcast profile, when a user switches user roles after joining a channel, a successful \ref agora::rtc::IRtcEngine::setClientRole "setClientRole" method call triggers the following callbacks:
     - The local client: \ref agora::rtc::IRtcEngineEventHandler::onClientRoleChanged "onClientRoleChanged"
     - The remote client: \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" or \ref agora::rtc::IRtcEngineEventHandler::onUserOffline "onUserOffline" (BECOME_AUDIENCE)

     @note
     This method applies only to the Live-broadcast profile.

     @param role Sets the role of the user. See #CLIENT_ROLE_TYPE.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setClientRole(CLIENT_ROLE_TYPE role) = 0;

    /** Joins a channel with the user ID.

     Users in the same channel can talk to each other, and multiple users in the same channel can start a group chat. Users with different App IDs cannot call each other.


     You must call the \ref IRtcEngine::leaveChannel "leaveChannel" method to exit the current call before entering another channel.

     A successful \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" method call triggers the following callbacks:
     - The local client: \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess"
     - The remote client: \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" , if the user joining the channel is in the Communication profile, or is a BROADCASTER in the Live Broadcast profile.

     When the connection between the client and Agora's server is interrupted due to poor network conditions, the SDK tries reconnecting to the server. When the local client successfully rejoins the channel, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onRejoinChannelSuccess "onRejoinChannelSuccess" callback on the local client.

     @note A channel does not accept duplicate uids, such as two users with the same @p uid. If you set @p uid as 0, the system automatically assigns a @p uid. If you want to join a channel from different devices, ensure that each device has a different uid.
     @warning Ensure that the App ID used for creating the token is the same App ID used by the \ref IRtcEngine::initialize "initialize" method for initializing the RTC engine. Otherwise, the CDN live streaming may fail.

     @param token Pointer to the token generated by the application server. In most circumstances, a static App ID suffices. For added security, use a Channel Key.
     - If the user uses a static App ID, *token* is optional and can be set as NULL.
     - If the user uses a Channel Key, Agora issues an additional App Certificate for you to generate a user key based on the algorithm and App Certificate for user authentication on the server.
     @param channelId Pointer to the unique channel name for the Agora RTC session in the string format smaller than 64 bytes. Supported characters:
     - All lowercase English letters: a to z.
     - All uppercase English letters: A to Z.
     - All numeric characters: 0 to 9.
     - The space character.
     - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
     @param info (Optional) Pointer to additional information about the channel. This parameter can be set to NULL or contain channel related information. Other users in the channel will not receive this message.
     @param uid (Optional) User ID. A 32-bit unsigned integer with a value ranging from 1 to 2<sup>32</sup>-1. The @p uid must be unique. If a @p uid is not assigned (or set to 0), the SDK assigns and returns a @p uid in the \ref IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" callback. Your application must record and maintain the returned *uid* since the SDK does not do so.

     @return
     - 0: Success.
     - < 0: Failure:
        - #ERR_INVALID_ARGUMENT (-2)
        - #ERR_NOT_READY (-3)
        - #ERR_REFUSED (-5)
     */
    virtual int joinChannel(const char* token, const char* channelId, const char* info, uid_t uid) = 0;
    /** Switches to a different channel.
     *
     * This method allows the audience of a Live-broadcast channel to switch
     * to a different channel.
     *
     * After the user successfully switches to another channel, the
     * \ref agora::rtc::IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel"
     *  and \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess
     * "onJoinChannelSuccess" callbacks are triggered to indicate that the
     * user has left the original channel and joined a new one.
     *
     * @note
     * This method applies to the audience role in a Live-broadcast channel
     * only.
     *
     * @param token The token generated at your server:
     * - For low-security requirements: You can use the temporary token
     * generated in Console. For details, see
     * [Get a temporary token](https://docs.agora.io/en/Agora%20Platform/token?platfor%20*%20m=All%20Platforms#get-a-temporary-token).
     * - For high-security requirements: Use the token generated at your
     * server. For details, see
     * [Get a token](https://docs.agora.io/en/Agora%20Platform/token?platfor%20*%20m=All%20Platforms#get-a-token).
     * @param channelId Unique channel name for the AgoraRTC session in the
     * string format. The string length must be less than 64 bytes. Supported
     * character scopes are:
     * - All lowercase English letters: a to z.
     * - All uppercase English letters: A to Z.
     * - All numeric characters: 0 to 9.
     * - The space character.
     * - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".

     @return
     - 0: Success.
     - < 0: Failure.
        - #ERR_INVALID_ARGUMENT (-2)
        - #ERR_NOT_READY (-3)
        - #ERR_REFUSED (-5)
     */
    virtual int switchChannel(const char* token, const char* channelId) = 0;

    /** Allows a user to leave a channel, such as hanging up or exiting a call.

     After joining a channel, the user must call the *leaveChannel* method to end the call before joining another channel.

     This method returns 0 if the user leaves the channel and releases all resources related to the call.

     This method call is asynchronous, and the user has not left the channel when the method call returns. Once the user leaves the channel, the SDK triggers the \ref IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel" callback.

     A successful \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" method call triggers the following callbacks:
     - The local client: \ref agora::rtc::IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel"
     - The remote client: \ref agora::rtc::IRtcEngineEventHandler::onUserOffline "onUserOffline" , if the user leaving the channel is in the Communication channel, or is a BROADCASTER in the Live Broadcast profile.

     @note
     - If you call the \ref IRtcEngine::release "release" method immediately after the *leaveChannel* method, the *leaveChannel* process interrupts, and the \ref IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel" callback is not triggered.
     - If you call the *leaveChannel* method during a CDN live streaming, the SDK triggers the \ref IRtcEngine::removePublishStreamUrl "removePublishStreamUrl" method.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int leaveChannel() = 0;

    /** Gets a new token when the current token expires after a period of time.

     The `token` expires after a period of time once the token schema is enabled when:

     - The SDK triggers the \ref IRtcEngineEventHandler::onTokenPrivilegeWillExpire "onTokenPrivilegeWillExpire" callback, or
     - The \ref IRtcEngineEventHandler::onConnectionStateChanged "onConnectionStateChanged" reports CONNECTION_CHANGED_TOKEN_EXPIRED(9).

     The application should call this method to get the new `token`. Failure to do so will result in the SDK disconnecting from the server.

     @param token Pointer to the new token.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int renewToken(const char* token) = 0;

    /** Retrieves the pointer to the device manager object.

     @param iid ID of the interface.
     @param inter Pointer to the *DeviceManager* object.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int queryInterface(INTERFACE_ID_TYPE iid, void** inter) = 0;

     /** Registers a user account.

     Once registered, the user account can be used to identify the local user when the user joins the channel.
     After the user successfully registers a user account, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onLocalUserRegistered "onLocalUserRegistered" callback on the local client,
     reporting the user ID and user account of the local user.

     To join a channel with a user account, you can choose either of the following:

     - Call the \ref agora::rtc::IRtcEngine::registerLocalUserAccount "registerLocalUserAccount" method to create a user account, and then the \ref agora::rtc::IRtcEngine::joinChannelWithUserAccount "joinChannelWithUserAccount" method to join the channel.
     - Call the \ref agora::rtc::IRtcEngine::joinChannelWithUserAccount "joinChannelWithUserAccount" method to join the channel.

     The difference between the two is that for the former, the time elapsed between calling the \ref agora::rtc::IRtcEngine::joinChannelWithUserAccount "joinChannelWithUserAccount" method
     and joining the channel is shorter than the latter.

     @note
     - Ensure that you set the `userAccount` parameter. Otherwise, this method does not take effect.
     - Ensure that the value of the `userAccount` parameter is unique in the channel.
     - To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account. If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.

     @param appId The App ID of your project.
     @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
     - All lowercase English letters: a to z.
     - All uppercase English letters: A to Z.
     - All numeric characters: 0 to 9.
     - The space character.
     - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".

     @return
     - 0: Success.
     - < 0: Failure.
    */
    virtual int registerLocalUserAccount(
        const char* appId, const char* userAccount) = 0;
    /** Joins the channel with a user account.

     After the user successfully joins the channel, the SDK triggers the following callbacks:

     - The local client: \ref agora::rtc::IRtcEngineEventHandler::onLocalUserRegistered "onLocalUserRegistered" and \ref agora::rtc::IRtcEngineEventHandler::onJoinChannelSuccess "onJoinChannelSuccess" .
     The remote client: \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" and \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" , if the user joining the channel is in the Communication profile, or is a BROADCASTER in the Live Broadcast profile.

     @note To ensure smooth communication, use the same parameter type to identify the user. For example, if a user joins the channel with a user ID, then ensure all the other users use the user ID too. The same applies to the user account.
     If a user joins the channel with the Agora Web SDK, ensure that the uid of the user is set to the same parameter type.

     @param token The token generated at your server:
     - For low-security requirements: You can use the temporary token generated at Console. For details, see [Get a temporary toke](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-temporary-token).
     - For high-security requirements: Set it as the token generated at your server. For details, see [Get a token](https://docs.agora.io/en/Voice/token?platform=All%20Platforms#get-a-token).
     @param channelId The channel name. The maximum length of this parameter is 64 bytes. Supported character scopes are:
     - All lowercase English letters: a to z.
     - All uppercase English letters: A to Z.
     - All numeric characters: 0 to 9.
     - The space character.
     - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".
     @param userAccount The user account. The maximum length of this parameter is 255 bytes. Ensure that you set this parameter and do not set it as null. Supported character scopes are:
     - All lowercase English letters: a to z.
     - All uppercase English letters: A to Z.
     - All numeric characters: 0 to 9.
     - The space character.
     - Punctuation characters and other symbols, including: "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", " {", "}", "|", "~", ",".

     @return
     - 0: Success.
     - < 0: Failure.
        - #ERR_INVALID_ARGUMENT (-2)
        - #ERR_NOT_READY (-3)
        - #ERR_REFUSED (-5)
     */
    virtual int joinChannelWithUserAccount(const char* token,
                                           const char* channelId,
                                           const char* userAccount) = 0;

    /** Gets the user information by passing in the user account.

     After a remote user joins the channel, the SDK gets the user ID and user account of the remote user, caches them
     in a mapping table object (`userInfo`), and triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" callback on the local client.

     After receiving the o\ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" callback, you can call this method to get the user ID of the
     remote user from the `userInfo` object by passing in the user account.

     @param userAccount The user account of the user. Ensure that you set this parameter.
     @param [in,out] userInfo  A userInfo object that identifies the user:
     - Input: A userInfo object.
     - Output: A userInfo object that contains the user account and user ID of the user.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getUserInfoByUserAccount(const char* userAccount, UserInfo* userInfo) = 0;
    /** Gets the user information by passing in the user ID.

     After a remote user joins the channel, the SDK gets the user ID and user account of the remote user,
     caches them in a mapping table object (`userInfo`), and triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" callback on the local client.

     After receiving the \ref agora::rtc::IRtcEngineEventHandler::onUserInfoUpdated "onUserInfoUpdated" callback, you can call this method to get the user account of the remote user
     from the `userInfo` object by passing in the user ID.

     @param uid The user ID of the remote user. Ensure that you set this parameter.
     @param[in,out] userInfo A userInfo object that identifies the user:
     - Input: A userInfo object.
     - Output: A userInfo object that contains the user account and user ID of the user.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getUserInfoByUid(uid_t uid, UserInfo* userInfo) = 0;

    /** **DEPRECATED** Starts an audio call test.

     This method is deprecated as of v2.4.0.

     This method starts an audio call test to check whether the audio devices (for example, headset and speaker) and the network connection are working properly.

     To conduct the test:

     - The user speaks and the recording is played back within 10 seconds.
     - If the user can hear the recording within 10 seconds, the audio devices and network connection are working properly.

     @note
     - After calling this method, always call the \ref IRtcEngine::stopEchoTest "stopEchoTest" method to end the test. Otherwise, the application cannot run the next echo test.
     - In the Live-broadcast profile, only the hosts can call this method. If the user switches from the Communication to Live-broadcast profile, the user must call the \ref IRtcEngine::setClientRole "setClientRole" method to change the user role from the audience (default) to the host before calling this method.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int startEchoTest() = 0;

    /** Starts an audio call test.

    This method starts an audio call test to determine whether the audio devices (for example, headset and speaker) and the network connection are working properly.

    In the audio call test, you record your voice. If the recording plays back within the set time interval, the audio devices and the network connection are working properly.

    @note
    - Call this method before joining a channel.
    - After calling this method, call the \ref IRtcEngine::stopEchoTest "stopEchoTest" method to end the test. Otherwise, the app cannot run the next echo test, or call the \ref IRtcEngine::joinChannel "joinChannel" method.
    - In the Live-broadcast profile, only a host can call this method.
    @param intervalInSeconds The time interval (s) between when you speak and when the recording plays back.

     @return
     - 0: Success.
     - < 0: Failure.
     */
  virtual int startEchoTest(int intervalInSeconds) = 0;

    /** Stops the audio call test.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int stopEchoTest() = 0;

    /** Enables the video module.

     Call this method either before joining a channel or during a call. If this method is called before joining a channel, the call starts in the video mode. If this method is called during an audio call, the audio mode switches to the video mode. To disable the video module, call the \ref IRtcEngine::disableVideo "disableVideo" method.

     A successful \ref agora::rtc::IRtcEngine::enableVideo "enableVideo" method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserEnableVideo "onUserEnableVideo" (true) callback on the remote client.
     @note
     - This method affects the internal engine and can be called after the \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" method.
     - This method resets the internal engine and takes some time to take effect. We recommend using the following API methods to control the video engine modules separately:
         - \ref IRtcEngine::enableLocalVideo "enableLocalVideo": Whether to enable the camera to create the local video stream.
         - \ref IRtcEngine::muteLocalVideoStream "muteLocalVideoStream": Whether to publish the local video stream.
         - \ref IRtcEngine::muteRemoteVideoStream "muteRemoteVideoStream": Whether to subscribe to and play the remote video stream.
         - \ref IRtcEngine::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams": Whether to subscribe to and play all remote video streams.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int enableVideo() = 0;

    /** Disables the video module.

    This method can be called before joining a channel or during a call. If this method is called before joining a channel, the call starts in audio mode. If this method is called during a video call, the video mode switches to the audio mode. To enable the video module, call the \ref IRtcEngine::enableVideo "enableVideo" method.

    A successful \ref agora::rtc::IRtcEngine::disableVideo "disableVideo" method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserEnableVideo "onUserEnableVideo" (false) callback on the remote client.
     @note
     - This method affects the internal engine and can be called after the \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" method.
     - This method resets the internal engine and takes some time to take effect. We recommend using the following API methods to control the video engine modules separately:
         - \ref IRtcEngine::enableLocalVideo "enableLocalVideo": Whether to enable the camera to create the local video stream.
         - \ref IRtcEngine::muteLocalVideoStream "muteLocalVideoStream": Whether to publish the local video stream.
         - \ref IRtcEngine::muteRemoteVideoStream "muteRemoteVideoStream": Whether to subscribe to and play the remote video stream.
         - \ref IRtcEngine::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams": Whether to subscribe to and play all remote video streams.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int disableVideo() = 0;

    /** **DEPRECATED** Sets the video profile.

     This method is deprecated as of v2.3. Use the \ref IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" method instead.

     Each video profile includes a set of parameters, such as the resolution, frame rate, and bitrate. If the camera device does not support the specified resolution, the SDK automatically chooses a suitable camera resolution, keeping the encoder resolution specified by the *setVideoProfile* method.

     @note
     - If you do not need to set the video profile after joining the channel, call this method before the \ref IRtcEngine::enableVideo "enableVideo" method to reduce the render time of the first video frame.
     - Always set the video profile before calling the \ref IRtcEngine::joinChannel "joinChannel" or \ref IRtcEngine::startPreview "startPreview" method.

     @param profile Sets the video profile. See #VIDEO_PROFILE_TYPE.
     @param swapWidthAndHeight Sets whether to swap the width and height of the video stream:
     - true: Swap the width and height.
     - false: (Default) Do not swap the width and height.
     The width and height of the output video are consistent with the set video profile.
     @note Since the landscape or portrait mode of the output video can be decided directly by the video profile, We recommend setting *swapWidthAndHeight* to *false* (default).

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setVideoProfile(VIDEO_PROFILE_TYPE profile, bool swapWidthAndHeight) = 0;

    /** Sets the video encoder configuration.

     Each video encoder configuration corresponds to a set of video parameters, including the resolution, frame rate, bitrate, and video orientation.

     The parameters specified in this method are the maximum values under ideal network conditions. If the video engine cannot render the video using the specified parameters due to poor network conditions, the parameters further down the list are considered until a successful configuration is found.

     @note If you do not need to set the video encoder configuration after joining the channel, you can call this method before the \ref IRtcEngine::enableVideo "enableVideo" method to reduce the render time of the first video frame.

     @param config Sets the local video encoder configuration. See VideoEncoderConfiguration.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setVideoEncoderConfiguration(const VideoEncoderConfiguration& config) = 0;
    /** Sets the camera capture configuration.

     For a video call or live broadcast, generally the SDK controls the camera output parameters. When the default camera capturer settings do not meet special requirements or cause performance problems, we recommend using this method to set the camera capturer configuration:

     - If the resolution or frame rate of the captured raw video data are higher than those set by \ref IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration", processing video frames requires extra CPU and RAM usage and degrades performance. We recommend setting config as CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = 1 to avoid such problems.
     - If you do not need local video preview or are willing to sacrifice preview quality, we recommend setting config as CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = 1 to optimize CPU and RAM usage.
     - If you want better quality for the local video preview, we recommend setting config as CAPTURER_OUTPUT_PREFERENCE_PREVIEW = 2.

     @note Call this method before enabling the local camera. That said, you can call this method before calling \ref agora::rtc::IRtcEngine::joinChannel "joinChannel", \ref agora::rtc::IRtcEngine::enableVideo "enableVideo", or \ref IRtcEngine::enableLocalVideo "enableLocalVideo", depending on which method you use to turn on your local camera.

     @param config Sets the camera capturer configuration. See CameraCapturerConfiguration.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setCameraCapturerConfiguration(const CameraCapturerConfiguration& config) = 0;

    /** Initializes the local video view.

     This method initializes the video view of a local stream on the local device. It affects only the video view that the local user sees, not the published local video stream.

     Call this method to bind the local video stream to a video view and to set the rendering and mirror modes of the video view.
     The binding is still valid after the user leaves the channel, which means that the window still displays. To unbind the view, set the *view* in VideoCanvas to NULL.

     @note
     - Call this method before joining a channel.
     - During a call, you can call this method as many times as necessary to update the display mode of the local video view.
     @param canvas Pointer to the local video view and settings. See VideoCanvas.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setupLocalVideo(const VideoCanvas& canvas) = 0;

    /** Initializes the video view of a remote user.

     This method initializes the video view of a remote stream on the local device. It affects only the video view that the local user sees.

     Call this method to bind the remote video stream to a video view and to set the rendering and mirror modes of the video view.

     The application specifies the uid of the remote video in this method before the remote user joins the channel. If the remote uid is unknown to the application, set it after the application receives the \ref IRtcEngineEventHandler::onUserJoined "onUserJoined" callback.
     If the Video Recording function is enabled, the Video Recording Service joins the channel as a dummy client, causing other clients to also receive the \ref IRtcEngineEventHandler::onUserJoined "onUserJoined" callback. Do not bind the dummy client to the application view because the dummy client does not send any video streams. If your application does not recognize the dummy client, bind the remote user to the view when the SDK triggers the \ref IRtcEngineEventHandler::onFirstRemoteVideoDecoded "onFirstRemoteVideoDecoded" callback.
     To unbind the remote user from the view, set the view in VideoCanvas to NULL. Once the remote user leaves the channel, the SDK unbinds the remote user.

     @note To update the rendering or mirror mode of the remote video view during a call, use the \ref IRtcEngine::setRemoteRenderMode "setRemoteRenderMode" method.

     @param canvas Pointer to the remote video view and settings. See VideoCanvas.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setupRemoteVideo(const VideoCanvas& canvas) = 0;

    /** Starts the local video preview before joining the channel.

     Before calling this method, you must:

     - Call the \ref IRtcEngine::setupLocalVideo "setupLocalVideo" method to set up the local preview window and configure the attributes.
     - Call the \ref IRtcEngine::enableVideo "enableVideo" method to enable video.

     @note Once the startPreview method is called to start the local video preview, if you leave the channel by calling the \ref IRtcEngine::leaveChannel "leaveChannel" method, the local video preview remains until you call the \ref IRtcEngine::stopPreview "stopPreview" method to disable it.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int startPreview() = 0;

    /** Prioritizes a remote user's stream.

    Use this method with the \ref IRtcEngine::setRemoteSubscribeFallbackOption "setRemoteSubscribeFallbackOption" method. If the fallback function is enabled for a subscribed stream, the SDK ensures the high-priority user gets the best possible stream quality.

    @note The Agora SDK supports setting @p userPriority as high for one user only.

    @param  uid  The ID of the remote user.
    @param  userPriority Sets the priority of the remote user. See #PRIORITY_TYPE.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setRemoteUserPriority(uid_t uid, PRIORITY_TYPE userPriority) = 0;

    /** Stops the local video preview and disables video.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int stopPreview() = 0;

    /** Enables the audio module.

    The audio mode is enabled by default.

     @note
     - This method affects the internal engine and can be called after the \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" method. You can call this method either before or after joining a channel.
     - This method resets the internal engine and takes some time to take effect. We recommend using the following API methods to control the audio engine modules separately:
         - \ref IRtcEngine::enableLocalAudio "enableLocalAudio": Whether to enable the microphone to create the local audio stream.
         - \ref IRtcEngine::muteLocalAudioStream "muteLocalAudioStream": Whether to publish the local audio stream.
         - \ref IRtcEngine::muteRemoteAudioStream "muteRemoteAudioStream": Whether to subscribe to and play the remote audio stream.
         - \ref IRtcEngine::muteAllRemoteAudioStreams "muteAllRemoteAudioStreams": Whether to subscribe to and play all remote audio streams.

    @return
    - 0: Success.
    - < 0: Failure.
    */
    virtual int enableAudio() = 0;

    /** Disables/Re-enables the local audio function.

    The audio function is enabled by default. This method disables or re-enables the local audio function, that is, to stop or restart local audio capturing.

    This method does not affect receiving or playing the remote audio streams,and enableLocalAudio(false) is applicable to scenarios where the user wants to
    receive remote audio streams without sending any audio stream to other users in the channel.

    The SDK triggers the \ref IRtcEngineEventHandler::onMicrophoneEnabled "onMicrophoneEnabled" callback once the local audio function is disabled or enabled.

     @note
     This method is different from the \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream" method:
        - \ref agora::rtc::IRtcEngine::enableLocalAudio "enableLocalAudio": Disables/Re-enables the local audio capturing and processing.
        If you disable or re-enable local audio recording using the `enableLocalAudio` method, the local user may hear a pause in the remote audio playback.
        - \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream": Sends/Stops sending the local audio streams.

     @param enabled Sets whether to disable/re-enable the local audio function:
     - true: (Default) Re-enable the local audio function, that is, to start the local audio capturing device (for example, the microphone).
     - false: Disable the local audio function, that is, to stop local audio capturing.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int enableLocalAudio(bool enabled) = 0;

    /** Disables the audio module.

     @note
     - This method affects the internal engine and can be called after the \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" method. You can call this method either before or after joining a channel.
     - This method resets the internal engine and takes some time to take effect. We recommend using the \ref agora::rtc::IRtcEngine::enableLocalAudio "enableLocalAudio" and \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream" methods to capture, process, and send the local audio streams.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int disableAudio() = 0;

	/** Sets the audio parameters and application scenarios.

     @note
     - The *setAudioProfile* method must be called before the \ref IRtcEngine::joinChannel "joinChannel" method.
     - In the Communication and Live-broadcast profiles, the bitrate may be different from your settings due to network self-adaptation.
     - In scenarios requiring high-quality audio, for example, a music teaching scenario, we recommend setting profile as AUDIO_PROFILE_MUSIC_HIGH_QUALITY (4) and  scenario as AUDIO_SCENARIO_GAME_STREAMING (3).

     @param  profile Sets the sample rate, bitrate, encoding mode, and the number of channels. See #AUDIO_PROFILE_TYPE.
     @param  scenario Sets the audio application scenario. See #AUDIO_SCENARIO_TYPE.
     Under different audio scenarios, the device uses different volume tracks,
     i.e. either the in-call volume or the media volume. For details, see
     [What is the difference between the in-call volume and the media volume?](https://docs.agora.io/en/faq/system_volume).

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setAudioProfile(AUDIO_PROFILE_TYPE profile, AUDIO_SCENARIO_TYPE scenario) = 0;
    /** Stops/Resumes sending the local audio stream.

     A successful \ref agora::rtc::IRtcEngine::muteLocalAudioStream "muteLocalAudioStream" method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserMuteAudio "onUserMuteAudio" callback on the remote client.
     @note
     - When @p mute is set as @p true, this method does not disable the microphone, which does not affect any ongoing recording.
     - If you call \ref agora::rtc::IRtcEngine::setChannelProfile "setChannelProfile" after this method, the SDK resets whether or not to mute the local audio according to the channel profile and user role. Therefore, we recommend calling this method after the `setChannelProfile` method.

     @param mute Sets whether to send/stop sending the local audio stream:
     - true: Stops sending the local audio stream.
     - false: (Default) Sends the local audio stream.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int muteLocalAudioStream(bool mute) = 0;
    /** Stops/Resumes receiving all remote users' audio streams.

     @param mute Sets whether to receive/stop receiving all remote users' audio streams.
     - true: Stops receiving all remote users' audio streams.
     - false: (Default) Receives all remote users' audio streams.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int muteAllRemoteAudioStreams(bool mute) = 0;
    /** Stops/Resumes receiving all remote users' audio streams by default.

     You can call this method either before or after joining a channel. If you call `setDefaultMuteAllRemoteAudioStreams (true)` after joining a channel, the remote audio streams of all subsequent users are not received.

     @note If you want to resume receiving the audio stream, call \ref agora::rtc::IRtcEngine::muteRemoteAudioStream "muteRemoteAudioStream (false)",
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
	virtual int setDefaultMuteAllRemoteAudioStreams(bool mute) = 0;

    /** Adjusts the playback volume of a specified remote user.

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
    virtual int adjustUserPlaybackSignalVolume(unsigned int uid, int volume) = 0;
	/** Stops/Resumes receiving a specified remote user's audio stream.

	 @note If you called the \ref agora::rtc::IRtcEngine::muteAllRemoteAudioStreams "muteAllRemoteAudioStreams" method and set @p mute as @p true to stop receiving all remote users' audio streams, call the *muteAllRemoteAudioStreams* method and set @p mute as @p false before calling this method. The *muteAllRemoteAudioStreams* method sets all remote audio streams, while the *muteRemoteAudioStream* method sets a specified remote audio stream.

	 @param userId User ID of the specified remote user sending the audio.
	 @param mute Sets whether to receive/stop receiving a specified remote user's audio stream:
	 - true: Stops receiving the specified remote user's audio stream.
	 - false: (Default) Receives the specified remote user's audio stream.

	 @return
	 - 0: Success.
	 - < 0: Failure.

	 */
	virtual int muteRemoteAudioStream(uid_t userId, bool mute) = 0;
    /** Stops/Resumes sending the local video stream.

     A successful \ref agora::rtc::IRtcEngine::muteLocalVideoStream "muteLocalVideoStream" method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserMuteVideo "onUserMuteVideo" callback on the remote client.

     @note
     - When set to *true*, this method does not disable the camera which does not affect the retrieval of the local video streams. This method executes faster than the \ref agora::rtc::IRtcEngine::enableLocalVideo "enableLocalVideo" method which controls the sending of the local video stream.
     - If you call \ref agora::rtc::IRtcEngine::setChannelProfile "setChannelProfile" after this method, the SDK resets whether or not to mute the local video according to the channel profile and user role. Therefore, we recommend calling this method after the `setChannelProfile` method.

     @param mute Sets whether to send/stop sending the local video stream:
     - true: Stop sending the local video stream.
     - false: (Default) Send the local video stream.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int muteLocalVideoStream(bool mute) = 0;
    /** Enables/Disables the local video capture.

     This method disables or re-enables the local video capturer, and does not affect receiving the remote video stream.

     After you call the \ref agora::rtc::IRtcEngine::enableVideo "enableVideo" method, the local video capturer is enabled by default. You can call \ref agora::rtc::IRtcEngine::enableLocalVideo "enableLocalVideo(false)" to disable the local video capturer. If you want to re-enable it, call \ref agora::rtc::IRtcEngine::enableLocalVideo "enableLocalVideo(true)".

     After the local video capturer is successfully disabled or re-enabled, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onUserEnableLocalVideo "onUserEnableLocalVideo" callback on the remote client.

     @note This method affects the internal engine and can be called after the \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" method.

     @param enabled Sets whether to disable/re-enable the local video, including the capturer, renderer, and sender:
     - true: (Default) Re-enable the local video.
     - false: Disable the local video. Once the local video is disabled, the remote users can no longer receive the video stream of this user, while this user can still receive the video streams of the other remote users.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int enableLocalVideo(bool enabled) = 0;
    /** Stops/Resumes receiving all video stream from a specified remote user.

     @param  mute Sets whether to receive/stop receiving all remote users' video streams:
     - true: Stop receiving all remote users' video streams.
     - false: (Default) Receive all remote users' video streams.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int muteAllRemoteVideoStreams(bool mute) = 0;
    /** Stops/Resumes receiving all remote users' video streams by default.

     You can call this method either before or after joining a channel. If you call `setDefaultMuteAllRemoteVideoStreams (true)` after joining a channel, the remote video streams of all subsequent users are not received.

     @note If you want to resume receiving the video stream, call \ref agora::rtc::IRtcEngine::muteRemoteVideoStream "muteRemoteVideoStream (false)", and specify the ID of the remote user whose video stream you want to receive. To receive the video streams of multiple remote users, call `muteRemoteVideoStream (false)` as many times. Calling `setDefaultMuteAllRemoteVideoStreams (false)` resumes receiving the video streams of subsequent users only.

     @param mute Sets whether to receive/stop receiving all remote users' video streams by default:
     - true: Stop receiving all remote users' video streams by default.
     - false: (Default) Receive all remote users' video streams by default.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setDefaultMuteAllRemoteVideoStreams(bool mute) = 0;
    /** Stops/Resumes receiving the video stream from a specified remote user.

     @note If you called the \ref agora::rtc::IRtcEngine::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams" method and set @p mute as @p true to stop receiving all remote video streams, call the *muteAllRemoteVideoStreams* method and set @p mute as @p false before calling this method.

     @param userId User ID of the specified remote user.
     @param mute Sets whether to stop/resume receiving the video stream from a specified remote user:
     - true: Stop receiving the specified remote user's video stream.
     - false: (Default) Receive the specified remote user's video stream.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int muteRemoteVideoStream(uid_t userId, bool mute) = 0;
    /** Sets the stream type of the remote video.

     Under limited network conditions, if the publisher has not disabled the dual-stream mode using `enableDualStreamMode(false)`,
     the receiver can choose to receive either the high-quality video stream (the high resolution, and high bitrate video stream) or
     the low-video stream (the low resolution, and low bitrate video stream).

     By default, users receive the high-quality video stream. Call this method if you want to switch to the low-video stream.
     This method allows the app to adjust the corresponding video stream type based on the size of the video window to
     reduce the bandwidth and resources.

     The aspect ratio of the low-video stream is the same as the high-quality video stream. Once the resolution of the high-quality video
     stream is set, the system automatically sets the resolution, frame rate, and bitrate of the low-video stream.

     The method result returns in the \ref agora::rtc::IRtcEngineEventHandler::onApiCallExecuted "onApiCallExecuted" callback.

     @param userId ID of the remote user sending the video stream.
     @param streamType  Sets the video-stream type. See #REMOTE_VIDEO_STREAM_TYPE.
     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setRemoteVideoStreamType(uid_t userId, REMOTE_VIDEO_STREAM_TYPE streamType) = 0;
    /** Sets the default stream type of remote videos.

     Under limited network conditions, if the publisher has not disabled the dual-stream mode using `enableDualStreamMode(false)`,
     the receiver can choose to receive either the high-quality video stream (the high resolution, and high bitrate video stream) or
     the low-video stream (the low resolution, and low bitrate video stream).

     By default, users receive the high-quality video stream. Call this method if you want to switch to the low-video stream.
     This method allows the app to adjust the corresponding video stream type based on the size of the video window to
     reduce the bandwidth and resources. The aspect ratio of the low-video stream is the same as the high-quality video stream.
     Once the resolution of the high-quality video
     stream is set, the system automatically sets the resolution, frame rate, and bitrate of the low-video stream.

     The method result returns in the \ref agora::rtc::IRtcEngineEventHandler::onApiCallExecuted "onApiCallExecuted" callback.

     @param streamType Sets the default video-stream type. See #REMOTE_VIDEO_STREAM_TYPE.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setRemoteDefaultVideoStreamType(REMOTE_VIDEO_STREAM_TYPE streamType) = 0;

    /** Enables the \ref agora::rtc::IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" callback at a set time interval to report on which users are speaking and the speakers' volume.

     Once this method is enabled, the SDK returns the volume indication in the \ref agora::rtc::IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" callback at the set time interval, whether or not any user is speaking in the channel.

     @param interval Sets the time interval between two consecutive volume indications:
     - &le; 0: Disables the volume indication.
     - > 0: Time interval (ms) between two consecutive volume indications. We recommend setting @p interval &gt; 200 ms. Do not set @p interval &lt; 10 ms, or the *onAudioVolumeIndication* callback will not be triggered.
     @param smooth  Smoothing factor sets the sensitivity of the audio volume indicator. The value ranges between 0 and 10. The greater the value, the more sensitive the indicator. The recommended value is 3.
     @param report_vad

     - true: Enable the voice activity detection of the local user. Once it is enabled, the `vad` parameter of the `onAudioVolumeIndication` callback reports the voice activity status of the local user.
     - false: (Default) Disable the voice activity detection of the local user. Once it is disabled, the `vad` parameter of the `onAudioVolumeIndication` callback does not report the voice activity status of the local user, except for the scenario where the engine automatically detects the voice activity of the local user.
     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int enableAudioVolumeIndication(int interval, int smooth, bool report_vad) = 0;
    /** @deprecated Starts an audio recording.

     Use \ref IRtcEngine::startAudioRecording(const char* filePath, int sampleRate, AUDIO_RECORDING_QUALITY_TYPE quality) "startAudioRecording"2 instead.

     The SDK allows recording during a call. Supported formats:

     - .wav: Large file size with high fidelity.
     - .aac: Small file size with low fidelity.

     This method has a fixed sample rate of 32 kHz.

     Ensure that the directory to save the recording file exists and is writable.
     This method is usually called after the \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" method.
     The recording automatically stops when the \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" method is called.

     @param filePath Pointer to the absolute file path of the recording file. The string of the file name is in UTF-8.
     @param quality Sets the audio recording quality. See #AUDIO_RECORDING_QUALITY_TYPE.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int startAudioRecording(const char* filePath, AUDIO_RECORDING_QUALITY_TYPE quality) = 0;

    /** Starts an audio recording on the client.
     *
     * The SDK allows recording during a call. After successfully calling this method, you can record the audio of all the users in the channel and get an audio recording file.
     * Supported formats of the recording file are as follows:
     * - .wav: Large file size with high fidelity.
     * - .aac: Small file size with low fidelity.
     *
     * @note
     * - Ensure that the directory you use to save the recording file exists and is writable.
     * - This method is usually called after the `joinChannel` method. The recording automatically stops when you call the `leaveChannel` method.
     * - For better recording effects, set quality as #AUDIO_RECORDING_QUALITY_MEDIUM or #AUDIO_RECORDING_QUALITY_HIGH when `sampleRate` is 44.1 kHz or 48 kHz.
     *
     * @param filePath Pointer to the absolute file path of the recording file. The string of the file name is in UTF-8, such as c:/music/audio.aac.
     * @param sampleRate Sample rate (kHz) of the recording file. Supported values are as follows:
     * - 16
     * - (Default) 32
     * - 44.1
     * - 48
     * @param quality Sets the audio recording quality. See #AUDIO_RECORDING_QUALITY_TYPE.
     *
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
	virtual int startAudioRecording(const char* filePath, int sampleRate, AUDIO_RECORDING_QUALITY_TYPE quality) = 0;
    /** Stops an audio recording on the client.

     You can call this method before calling the \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" method else, the recording automatically stops when the \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" method is called.

     @return
     - 0: Success
     - < 0: Failure.
     */
	virtual int stopAudioRecording() = 0;
    /** Starts playing and mixing the music file.

     This method mixes the specified local audio file with the audio stream from the microphone, or replaces the microphone's audio stream with the specified local audio file. You can choose whether the other user can hear the local audio playback and specify the number of playback loops. This method also supports online music playback.

     When the audio mixing file playback finishes after calling this method, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onAudioMixingFinished "onAudioMixingFinished" callback.

     A successful \ref agora::rtc::IRtcEngine::startAudioMixing "startAudioMixing" method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onAudioMixingStateChanged "onAudioMixingStateChanged" (PLAY) callback on the local client.

     When the audio mixing file playback finishes, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onAudioMixingStateChanged "onAudioMixingStateChanged" (STOPPED) callback on the local client.
     @note
     - Call this method after joining a channel, otherwise issues may occur.
     - If the local audio mixing file does not exist, or if the SDK does not support the file format or cannot access the music file URL, the SDK returns WARN_AUDIO_MIXING_OPEN_ERROR = 701.
     - If you want to play an online music file, ensure that the time interval between calling this method is more than 100 ms, or the AUDIO_MIXING_ERROR_TOO_FREQUENT_CALL(702) error code occurs.
     @param filePath Pointer to the absolute path (including the suffixes of the filename) of the local or online audio file to mix, for example, c:/music/audio.mp4. Supported audio formats: 3GP, ASF, ADTS, AVI, MP3, MP4, MPEG-4, SAMI, and WAVE. For more information, see [Supported Media Formats in Media Foundation](https://docs.microsoft.com/en-us/windows/desktop/medfound/supported-media-formats-in-media-foundation).
     @param loopback Sets which user can hear the audio mixing:
     - true: Only the local user can hear the audio mixing.
     - false: Both users can hear the audio mixing.
     @param replace Sets the audio mixing content:
     - true: Only publish the specified audio file. The audio stream from the microphone is not published.
     - false: The local audio file is mixed with the audio stream from the microphone.
     @param cycle Sets the number of playback loops:
     - Positive integer: Number of playback loops.
     - `-1`: Infinite playback loops.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int startAudioMixing(const char* filePath, bool loopback, bool replace, int cycle) = 0;
    /** Stops playing and mixing the music file.

     Call this method when you are in a channel.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int stopAudioMixing() = 0;
    /** Pauses playing and mixing the music file.

     Call this method when you are in a channel.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int pauseAudioMixing() = 0;
    /** Resumes playing and mixing the music file.

     Call this method when you are in a channel.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int resumeAudioMixing() = 0;
    /** **DEPRECATED** Agora does not recommend using this method.

     Sets the high-quality audio preferences. Call this method and set all parameters before joining a channel.

     Do not call this method again after joining a channel.

     @param fullband Sets whether to enable/disable full-band codec (48-kHz sample rate). Not compatible with SDK versions before v1.7.4:
     - true: Enable full-band codec.
     - false: Disable full-band codec.
     @param  stereo Sets whether to enable/disable stereo codec. Not compatible with SDK versions before v1.7.4:
     - true: Enable stereo codec.
     - false: Disable stereo codec.
     @param fullBitrate Sets whether to enable/disable high-bitrate mode. Recommended in voice-only mode:
     - true: Enable high-bitrate mode.
     - false: Disable high-bitrate mode.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setHighQualityAudioParameters(bool fullband, bool stereo, bool fullBitrate) = 0;
    /** Adjusts the volume during audio mixing.

     Call this method when you are in a channel.

     @note Calling this method does not affect the volume of audio effect file playback invoked by the \ref agora::rtc::IRtcEngine::playEffect "playEffect" method.

     @param volume Audio mixing volume. The value ranges between 0 and 100 (default).

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int adjustAudioMixingVolume(int volume) = 0;
    /** Adjusts the audio mixing volume for local playback.

     @note Call this method when you are in a channel.

     @param volume Audio mixing volume for local playback. The value ranges between 0 and 100 (default).

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int adjustAudioMixingPlayoutVolume(int volume) = 0;
    /** Retrieves the audio mixing volume for local playback.

     This method helps troubleshoot audio volume related issues.

     @note Call this method when you are in a channel.

     @return
     - &ge; 0: The audio mixing volume, if this method call succeeds. The value range is [0,100].
     - < 0: Failure.
     */
    virtual int getAudioMixingPlayoutVolume() = 0;
    /** Adjusts the audio mixing volume for publishing (for remote users).

     @note Call this method when you are in a channel.

     @param volume Audio mixing volume for publishing. The value ranges between 0 and 100 (default).

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int adjustAudioMixingPublishVolume(int volume) = 0;
    /** Retrieves the audio mixing volume for publishing.

     This method helps troubleshoot audio volume related issues.

     @note Call this method when you are in a channel.

     @return
     - &ge; 0: The audio mixing volume for publishing, if this method call succeeds. The value range is [0,100].
     - < 0: Failure.
     */
    virtual int getAudioMixingPublishVolume() = 0;

    /** Retrieves the duration (ms) of the music file.

     Call this method when you are in a channel.

     @return
     - &ge; 0: The audio mixing duration, if this method call succeeds.
     - < 0: Failure.
     */
	virtual int getAudioMixingDuration() = 0;
    /** Retrieves the playback position (ms) of the music file.

     Call this method when you are in a channel.

     @return
     - &ge; 0: The current playback position of the audio mixing, if this method call succeeds.
     - < 0: Failure.
     */
	virtual int getAudioMixingCurrentPosition() = 0;
    /** Sets the playback position of the music file to a different starting position (the default plays from the beginning).

     @param pos The playback starting position (ms) of the music file.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setAudioMixingPosition(int pos /*in ms*/) = 0;
    /** Sets the pitch of the local music file.
     * @since v3.0.1
     *
     * When a local music file is mixed with a local human voice, call this method to set the pitch of the local music file only.
     *
     * @note
     * Call this method after calling `startAudioMixing`.
     *
     * @param pitch Sets the pitch of the local music file by chromatic scale. The default value is 0,
     * which means keeping the original pitch. The value ranges from -12 to 12, and the pitch value between
     * consecutive values is a chromatic value. The greater the absolute value of this parameter, the
     * higher or lower the pitch of the local music file.
     *
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int setAudioMixingPitch(int pitch) = 0;
    /** Retrieves the volume of the audio effects.

     The value ranges between 0.0 and 100.0.

     @return
     - &ge; 0: Volume of the audio effects, if this method call succeeds.

     - < 0: Failure.
     */
	virtual int getEffectsVolume() = 0;
    /** Sets the volume of the audio effects.

     @param volume Sets the volume of the audio effects. The value ranges between 0 and 100 (default).

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setEffectsVolume(int volume) = 0;
    /** Sets the volume of a specified audio effect.

     @param soundId ID of the audio effect. Each audio effect has a unique ID.
     @param volume Sets the volume of the specified audio effect. The value ranges between 0 and 100 (default).

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setVolumeOfEffect(int soundId, int volume) = 0;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
    /**
     * Enables/Disables face detection for the local user. Applies to Android and iOS only.
     * @since v3.0.1
     *
     * Once face detection is enabled, the SDK triggers the \ref IRtcEngineEventHandler::onFacePositionChanged "onFacePositionChanged" callback
     * to report the face information of the local user, which includes the following aspects:
     * - The width and height of the local video.
     * - The position of the human face in the local video.
     * - The distance between the human face and the device screen.
     *
     * @param enable Determines whether to enable the face detection function for the local user:
     * - true: Enable face detection.
     * - false: (Default) Disable face detection.
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int enableFaceDetection(bool enable) = 0;
#endif
    /** Plays a specified local or online audio effect file.

     This method allows you to set the loop count, pitch, pan, and gain of the audio effect file, as well as whether the remote user can hear the audio effect.

     To play multiple audio effect files simultaneously, call this method multiple times with different soundIds and filePaths. We recommend playing no more than three audio effect files at the same time.

     @param soundId ID of the specified audio effect. Each audio effect has a unique ID.

     @note
     - If the audio effect is preloaded into the memory through the \ref IRtcEngine::preloadEffect "preloadEffect" method, the value of @p soundID must be the same as that in the *preloadEffect* method.
     - Playing multiple online audio effect files simultaneously is not supported on macOS and Windows.

     @param filePath Specifies the absolute path (including the suffixes of the filename) to the local audio effect file or the URL of the online audio effect file, for example, c:/music/audio.mp4. Supported audio formats: mp3, mp4, m4a, aac, 3gp, mkv and wav.
     @param loopCount Sets the number of times the audio effect loops:
     - 0: Play the audio effect once.
     - 1: Play the audio effect twice.
     - -1: Play the audio effect in an indefinite loop until the \ref IRtcEngine::stopEffect "stopEffect" or \ref IRtcEngine::stopAllEffects "stopAllEffects" method is called.
     @param pitch Sets the pitch of the audio effect. The value ranges between 0.5 and 2. The default value is 1 (no change to the pitch). The lower the value, the lower the pitch.
     @param pan Sets the spatial position of the audio effect. The value ranges between -1.0 and 1.0:
     - 0.0: The audio effect displays ahead.
     - 1.0: The audio effect displays to the right.
     - -1.0: The audio effect displays to the left.
     @param gain  Sets the volume of the audio effect. The value ranges between 0 and 100 (default). The lower the value, the lower the volume of the audio effect.
     @param publish Sets whether or not to publish the specified audio effect to the remote stream:
     - true: The locally played audio effect is published to the Agora Cloud and the remote users can hear it.
     - false: The locally played audio effect is not published to the Agora Cloud and the remote users cannot hear it.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int playEffect(int soundId, const char* filePath, int loopCount, double pitch, double pan, int gain, bool publish = false) = 0;
    /** Stops playing a specified audio effect.

     @param soundId ID of the audio effect to stop playing. Each audio effect has a unique ID.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int stopEffect(int soundId) = 0;
    /** Stops playing all audio effects.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int stopAllEffects() = 0;

    /** Preloads a specified audio effect file into the memory.

     @note This method does not support online audio effect files.

     To ensure smooth communication, limit the size of the audio effect file. We recommend using this method to preload the audio effect before calling the \ref IRtcEngine::joinChannel "joinChannel" method.

     Supported audio formats: mp3, aac, m4a, 3gp, and wav.

     @param soundId ID of the audio effect. Each audio effect has a unique ID.
     @param filePath Pointer to the absolute path of the audio effect file.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int preloadEffect(int soundId, const char* filePath) = 0;
    /** Releases a specified preloaded audio effect from the memory.

     @param soundId ID of the audio effect. Each audio effect has a unique ID.
     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int unloadEffect(int soundId) = 0;
    /** Pauses a specified audio effect.

     @param soundId ID of the audio effect. Each audio effect has a unique ID.
     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int pauseEffect(int soundId) = 0;
    /** Pauses all audio effects.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int pauseAllEffects() = 0;
    /** Resumes playing a specified audio effect.

     @param soundId ID of the audio effect. Each audio effect has a unique ID.
     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int resumeEffect(int soundId) = 0;
    /** Resumes playing all audio effects.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int resumeAllEffects() = 0;
    /** Enables/Disables stereo panning for remote users.

     Ensure that you call this method before joinChannel to enable stereo panning for remote users so that the local user can track the position of a remote user by calling \ref agora::rtc::IRtcEngine::setRemoteVoicePosition "setRemoteVoicePosition".

     @param enabled Sets whether or not to enable stereo panning for remote users:
     - true: enables stereo panning.
     - false: disables stereo panning.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int enableSoundPositionIndication(bool enabled) = 0;
    /** Sets the sound position and gain of a remote user.

     When the local user calls this method to set the sound position of a remote user, the sound difference between the left and right channels allows the local user to track the real-time position of the remote user, creating a real sense of space. This method applies to massively multiplayer online games, such as Battle Royale games.

     @note
     - For this method to work, enable stereo panning for remote users by calling the \ref agora::rtc::IRtcEngine::enableSoundPositionIndication "enableSoundPositionIndication" method before joining a channel.
     - This method requires hardware support. For the best sound positioning, we recommend using a stereo speaker.

     @param uid The ID of the remote user.
     @param pan The sound position of the remote user. The value ranges from -1.0 to 1.0:
     - 0.0: the remote sound comes from the front.
     - -1.0: the remote sound comes from the left.
     - 1.0: the remote sound comes from the right.
     @param gain Gain of the remote user. The value ranges from 0.0 to 100.0. The default value is 100.0 (the original gain of the remote user). The smaller the value, the less the gain.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setRemoteVoicePosition(uid_t uid, double pan, double gain) = 0;

    /** Changes the voice pitch of the local speaker.

     @param pitch Sets the voice pitch. The value ranges between 0.5 and 2.0. The lower the value, the lower the voice pitch. The default value is 1.0 (no change to the local voice pitch).
     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setLocalVoicePitch(double pitch) = 0;
    /** Sets the local voice equalization effect.

     @param bandFrequency Sets the band frequency. The value ranges between 0 and 9, representing the respective 10-band center frequencies of the voice effects, including 31, 62, 125, 500, 1k, 2k, 4k, 8k, and 16k Hz. See #AUDIO_EQUALIZATION_BAND_FREQUENCY.
     @param bandGain  Sets the gain of each band in dB. The value ranges between -15 and 15.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setLocalVoiceEqualization(AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain) = 0;
    /**  Sets the local voice reverberation.

     v2.4.0 adds the \ref agora::rtc::IRtcEngine::setLocalVoiceReverbPreset "setLocalVoiceReverbPreset" method, a more user-friendly method for setting the local voice reverberation. You can use this method to set the local reverberation effect, such as pop music, R&B, rock music, and hip-hop.

     @param reverbKey Sets the reverberation key. See #AUDIO_REVERB_TYPE.
     @param value Sets the value of the reverberation key.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setLocalVoiceReverb(AUDIO_REVERB_TYPE reverbKey, int value) = 0;
    /** Sets the local voice changer option.

     This method can be used to set the local voice effect for users in a Communication channel or broadcasters in a live broadcast channel.
     Voice changer options include the following voice effects:

     - `VOICE_CHANGER_XXX`: Changes the local voice to an old man, a little boy, or the Hulk. Applies to the voice talk scenario.
     - `VOICE_BEAUTY_XXX`: Beautifies the local voice by making it sound more vigorous, resounding, or adding spacial resonance. Applies to the voice talk and singing scenario.
     - `GENERAL_VOICE_BEAUTY_XXX`: Adds gender-based beautification effect to the local voice. Applies to the voice talk scenario.
       - For a male voice: Adds magnetism to the voice.
       - For a female voice: Adds freshness or vitality to the voice.

     @note
     - To achieve better voice effect quality, Agora recommends setting the profile parameter in `setAudioProfile` as `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`.
     - This method works best with the human voice, and Agora does not recommend using it for audio containing music and a human voice.
     - Do not use this method with `setLocalVoiceReverbPreset`, because the method called later overrides the one called earlier. For detailed considerations, see the advanced guide *Voice Changer and Reverberation*.

     @param voiceChanger Sets the local voice changer option. The default value is `VOICE_CHANGER_OFF`, which means the original voice. See details in #VOICE_CHANGER_PRESET.
     Gender-based beatification effect works best only when assigned a proper gender:
     - For male: `GENERAL_BEAUTY_VOICE_MALE_MAGNETIC`.
     - For female: `GENERAL_BEAUTY_VOICE_FEMALE_FRESH` or `GENERAL_BEAUTY_VOICE_FEMALE_VITALITY`.
     Failure to do so can lead to voice distortion.

     @return
     - 0: Success.
     - < 0: Failure. Check if the enumeration is properly set.
     */
    virtual int setLocalVoiceChanger(VOICE_CHANGER_PRESET voiceChanger) = 0;
    /** Sets the local voice reverberation option, including the virtual stereo.
     *
     * This method sets the local voice reverberation for users in a Communication channel or broadcasters in a Live-broadcast channel.
     * After successfully calling this method, all users in the channel can hear the voice with reverberation.
     *
     * @note
     * - When calling this method with enumerations that begin with `AUDIO_REVERB_FX`, ensure that you set profile in `setAudioProfile` as
     * `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`; otherwise, this methods cannot set the corresponding voice reverberation option.
     * - When calling this method with `AUDIO_VIRTUAL_STEREO`, Agora recommends setting the `profile` parameter in `setAudioProfile` as `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`.
     * - This method works best with the human voice, and Agora does not recommend using it for audio containing music and a human voice.
     * - Do not use this method with `setLocalVoiceChanger`, because the method called later overrides the one called earlier.
     * For detailed considerations, see the advanced guide *Voice Changer and Reverberation*.

     @param reverbPreset The local voice reverberation option. The default value is `AUDIO_REVERB_OFF`,
     which means the original voice.  See #AUDIO_REVERB_PRESET.
     To achieve better voice effects, Agora recommends the enumeration whose name begins with `AUDIO_REVERB_FX`.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setLocalVoiceReverbPreset(AUDIO_REVERB_PRESET reverbPreset) = 0;

    /** Specifies an SDK output log file.

     The log file records all SDK operations during runtime. If it does not exist, the SDK creates one.

     @note
     - The default log file is located at: `C: \Users\<user_name>\AppData\Local\Agora\<process_name>`.
     - Ensure that you call this method immediately after calling the \ref agora::rtc::IRtcEngine::initialize "initialize" method, otherwise the output log may not be complete.

     @param filePath File path of the log file. The string of the log file is in UTF-8.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setLogFile(const char* filePath) = 0;
    /** Sets the output log level of the SDK.

     You can use one or a combination of the log filter levels. The log level follows the sequence of OFF, CRITICAL, ERROR, WARNING, INFO, and DEBUG. Choose a level to see the logs preceding that level.

     If you set the log level to WARNING, you see the logs within levels CRITICAL, ERROR, and WARNING.

     @param filter Sets the log filter level. See #LOG_FILTER_TYPE.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setLogFilter(unsigned int filter) = 0;
    /** Sets the log file size (KB).

     The SDK has two log files, each with a default size of 512 KB. If you set @p fileSizeInBytes as 1024 KB, the SDK outputs log files with a total maximum size of 2 MB. If the total size of the log files exceed the set value, the new output log files overwrite the old output log files.

     @param fileSizeInKBytes The SDK log file size (KB).
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setLogFileSize(unsigned int fileSizeInKBytes) = 0;
    /**
     @deprecated This method is deprecated, use the \ref IRtcEngine::setLocalRenderMode(RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) "setLocalRenderMode"2 method instead.
     Sets the local video display mode.

     This method can be called multiple times during a call to change the display mode.

     @param renderMode  Sets the local video display mode. See #RENDER_MODE_TYPE.
     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setLocalRenderMode(RENDER_MODE_TYPE renderMode) = 0;
    /** Updates the display mode of the local video view.

     @since v3.0.0

     After initializing the local video view, you can call this method to update its rendering and mirror modes. It affects only the video view that the local user sees, not the published local video stream.

     @note
     - Ensure that you have called the \ref IRtcEngine::setupLocalVideo "setupLocalVideo" method to initialize the local video view before calling this method.
     - During a call, you can call this method as many times as necessary to update the display mode of the local video view.
     @param renderMode The rendering mode of the local video view. See #RENDER_MODE_TYPE.
     @param mirrorMode
     - The mirror mode of the local video view. See #VIDEO_MIRROR_MODE_TYPE.
     - **Note**: If you use a front camera, the SDK enables the mirror mode by default; if you use a rear camera, the SDK disables the mirror mode by default.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setLocalRenderMode(RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) = 0;
    /**
     @deprecated This method is deprecated, use the \ref IRtcEngine::setRemoteRenderMode(uid_t userId, RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) "setRemoteRenderMode"2 method instead.
     Sets the video display mode of a specified remote user.

     This method can be called multiple times during a call to change the display mode.

     @param userId ID of the remote user.
     @param renderMode  Sets the video display mode. See #RENDER_MODE_TYPE.
     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setRemoteRenderMode(uid_t userId, RENDER_MODE_TYPE renderMode) = 0;
    /** Updates the display mode of the video view of a remote user.

     @since v3.0.0
     After initializing the video view of a remote user, you can call this method to update its rendering and mirror modes. This method affects only the video view that the local user sees.

     @note
     - Ensure that you have called the \ref IRtcEngine::setupRemoteVideo "setupRemoteVideo" method to initialize the remote video view before calling this method.
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
    virtual int setRemoteRenderMode(uid_t userId, RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) = 0;
    /**
     @deprecated This method is deprecated, use the \ref IRtcEngine::setupLocalVideo "setupLocalVideo"
     or \ref IRtcEngine::setLocalRenderMode(RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode) "setLocalRenderMode" method instead.

     Sets the local video mirror mode.

     You must call this method before calling the \ref agora::rtc::IRtcEngine::startPreview "startPreview" method, otherwise the mirror mode will not work.

     @warning
     - Call this method after calling the \ref agora::rtc::IRtcEngine::setupLocalVideo "setupLocalVideo" method to initialize the local video view.
     - During a call, you can call this method as many times as necessary to update the mirror mode of the local video view.

     @param mirrorMode Sets the local video mirror mode. See #VIDEO_MIRROR_MODE_TYPE.
     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setLocalVideoMirrorMode(VIDEO_MIRROR_MODE_TYPE mirrorMode) = 0;
    /** Sets the stream mode to the single-stream (default) or dual-stream mode. (Live broadcast only.)

     If the dual-stream mode is enabled, the receiver can choose to receive the high stream (high-resolution and high-bitrate video stream), or the low stream (low-resolution and low-bitrate video stream).

     @param enabled Sets the stream mode:
     - true: Dual-stream mode.
     - false: (Default) Single-stream mode.
     */
	virtual int enableDualStreamMode(bool enabled) = 0;
    /** Sets the external audio source. Please call this method before \ref agora::rtc::IRtcEngine::joinChannel "joinChannel".

     @param enabled Sets whether to enable/disable the external audio source:
     - true: Enables the external audio source.
     - false: (Default) Disables the external audio source.
     @param sampleRate Sets the sample rate (Hz) of the external audio source, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
     @param channels Sets the number of audio channels of the external audio source:
     - 1: Mono.
     - 2: Stereo.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setExternalAudioSource(bool enabled, int sampleRate, int channels) = 0;
    /** Sets the external audio sink.
     * This method applies to scenarios where you want to use external audio
     * data for playback. After enabling the external audio sink, you can call
     * the \ref agora::media::IMediaEngine::pullAudioFrame "pullAudioFrame" method to pull the remote audio data, process
     * it, and play it with the audio effects that you want.
     *
     * @note
     * Once you enable the external audio sink, the app will not retrieve any
     * audio data from the
     * \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" callback.
     *
     * @param enabled
     * - true: Enables the external audio sink.
     * - false: (Default) Disables the external audio sink.
     * @param sampleRate Sets the sample rate (Hz) of the external audio sink, which can be set as 16000, 32000, 44100 or 48000.
     * @param channels Sets the number of audio channels of the external
     * audio sink:
     * - 1: Mono.
     * - 2: Stereo.
     *
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
    virtual int setExternalAudioSink(bool enabled, int sampleRate, int channels) = 0;
    /** Sets the audio recording format for the \ref agora::media::IAudioFrameObserver::onRecordAudioFrame "onRecordAudioFrame" callback.


     @param sampleRate Sets the sample rate (@p samplesPerSec) returned in the *onRecordAudioFrame* callback, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
     @param channel Sets the number of audio channels (@p channels) returned in the *onRecordAudioFrame* callback:
     - 1: Mono
     - 2: Stereo
     @param mode Sets the use mode (see #RAW_AUDIO_FRAME_OP_MODE_TYPE) of the *onRecordAudioFrame* callback.
     @param samplesPerCall Sets the number of samples returned in the *onRecordAudioFrame* callback. `samplesPerCall` is usually set as 1024 for RTMP streaming.


     @note The SDK triggers the `onRecordAudioFrame` callback according to the sample interval. Ensure that the sample interval ≥ 0.01 (s). And, Sample interval (sec) = `samplePerCall`/(`sampleRate` × `channel`).

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setRecordingAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) = 0;
    /** Sets the audio playback format for the \ref agora::media::IAudioFrameObserver::onPlaybackAudioFrame "onPlaybackAudioFrame" callback.


     @param sampleRate Sets the sample rate (@p samplesPerSec) returned in the *onPlaybackAudioFrame* callback, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
     @param channel Sets the number of channels (@p channels) returned in the *onPlaybackAudioFrame* callback:
     - 1: Mono
     - 2: Stereo
     @param mode Sets the use mode (see #RAW_AUDIO_FRAME_OP_MODE_TYPE) of the *onPlaybackAudioFrame* callback.
     @param samplesPerCall Sets the number of samples returned in the *onPlaybackAudioFrame* callback. `samplesPerCall` is usually set as 1024 for RTMP streaming.

     @note The SDK triggers the `onPlaybackAudioFrame` callback according to the sample interval. Ensure that the sample interval ≥ 0.01 (s). And, Sample interval (sec) = `samplePerCall`/(`sampleRate` × `channel`).

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setPlaybackAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) = 0;
    /** Sets the mixed audio format for the \ref agora::media::IAudioFrameObserver::onMixedAudioFrame "onMixedAudioFrame" callback.


     @param sampleRate Sets the sample rate (@p samplesPerSec) returned in the *onMixedAudioFrame* callback, which can be set as 8000, 16000, 32000, 44100, or 48000 Hz.
     @param samplesPerCall Sets the number of samples (`samples`) returned in the *onMixedAudioFrame* callback. `samplesPerCall` is usually set as 1024 for RTMP streaming.

     @note The SDK triggers the `onMixedAudioFrame` callback according to the sample interval. Ensure that the sample interval ≥ 0.01 (s). And, Sample interval (sec) = `samplePerCall`/(`sampleRate` × `channels`).

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall) = 0;
    /** Adjusts the recording volume.

     @param volume Recording volume. To avoid echoes and
     improve call quality, Agora recommends setting the value of volume between
     0 and 100. If you need to set the value higher than 100, contact
     support@agora.io first.
     - 0: Mute.
     - 100: Original volume.


     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int adjustRecordingSignalVolume(int volume) = 0;
    /** Adjusts the playback volume of all remote users.

     @note
     - This method adjusts the playback volume that is the mixed volume of all remote users.
     - (Since v2.3.2) To mute the local audio playback, call both the `adjustPlaybackSignalVolume` and \ref IRtcEngine::adjustAudioMixingVolume "adjustAudioMixingVolume" methods and set the volume as `0`.

     @param volume The playback volume of all remote users. To avoid echoes and
     improve call quality, Agora recommends setting the value of volume between
     0 and 100. If you need to set the value higher than 100, contact
     support@agora.io first.
     - 0: Mute.
     - 100: Original volume.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int adjustPlaybackSignalVolume(int volume) = 0;

    /**
     @deprecated This method is deprecated. As of v3.0.0, the Native SDK automatically enables interoperability with the Web SDK, so you no longer need to call this method.
     Enables interoperability with the Agora Web SDK.

     @note
     - This method applies only to the Live-broadcast profile. In the Communication profile, interoperability with the Agora Web SDK is enabled by default.
     - If the channel has Web SDK users, ensure that you call this method, or the video of the Native user will be a black screen for the Web user.

     @param enabled Sets whether to enable/disable interoperability with the Agora Web SDK:
     - true: Enable.
     - false: (Default) Disable.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int enableWebSdkInteroperability(bool enabled) = 0;
    //only for live broadcast
    /** **DEPRECATED** Sets the preferences for the high-quality video. (Live broadcast only).

     This method is deprecated as of v2.4.0.

     @param preferFrameRateOverImageQuality Sets the video quality preference:
     - true: Frame rate over image quality.
     - false: (Default) Image quality over frame rate.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setVideoQualityParameters(bool preferFrameRateOverImageQuality) = 0;
    /** Sets the fallback option for the published video stream based on the network conditions.

     If `option` is set as #STREAM_FALLBACK_OPTION_AUDIO_ONLY (2), the SDK will:

     - Disable the upstream video but enable audio only when the network conditions deteriorate and cannot support both video and audio.
     - Re-enable the video when the network conditions improve.

     When the published video stream falls back to audio only or when the audio-only stream switches back to the video, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onLocalPublishFallbackToAudioOnly "onLocalPublishFallbackToAudioOnly" callback.

     @note Agora does not recommend using this method for CDN live streaming, because the remote CDN live user will have a noticeable lag when the published video stream falls back to audio only.

     @param option Sets the fallback option for the published video stream:
     - #STREAM_FALLBACK_OPTION_DISABLED (0): (Default) No fallback behavior for the published video stream when the uplink network condition is poor. The stream quality is not guaranteed.
     - #STREAM_FALLBACK_OPTION_AUDIO_ONLY (2): The published video stream falls back to audio only when the uplink network condition is poor.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setLocalPublishFallbackOption(STREAM_FALLBACK_OPTIONS option) = 0;
    /** Sets the fallback option for the remotely subscribed video stream based on the network conditions.

     The default setting for `option` is #STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW (1), where the remotely subscribed video stream falls back to the low-stream video (low resolution and low bitrate) under poor downlink network conditions.

     If `option` is set as #STREAM_FALLBACK_OPTION_AUDIO_ONLY (2), the SDK automatically switches the video from a high-stream to a low-stream, or disables the video when the downlink network conditions cannot support both audio and video to guarantee the quality of the audio. The SDK monitors the network quality and restores the video stream when the network conditions improve.

     When the remotely subscribed video stream falls back to audio only or when the audio-only stream switches back to the video stream, the SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onRemoteSubscribeFallbackToAudioOnly "onRemoteSubscribeFallbackToAudioOnly" callback.

     @param  option  Sets the fallback option for the remotely subscribed video stream. See #STREAM_FALLBACK_OPTIONS.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setRemoteSubscribeFallbackOption(STREAM_FALLBACK_OPTIONS option) = 0;

#if defined(__ANDROID__) || (defined(__APPLE__) && TARGET_OS_IOS)
	/** Switches between front and rear cameras.

     @note This method is for Android and iOS only.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int switchCamera() = 0;
    /// @cond
    /** Switches between front and rear cameras.

     @note This method is for Android and iOS only.
     @note This method is private.

     @param direction Sets the camera to be used:
     - CAMERA_DIRECTION.CAMERA_REAR: Use the rear camera.
     - CAMERA_DIRECTION.CAMERA_FRONT: Use the front camera.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int switchCamera(CAMERA_DIRECTION direction) = 0;
    /// @endcond
    /** Sets the default audio playback route.

     This method sets whether the received audio is routed to the earpiece or speakerphone by default before joining a channel.
     If a user does not call this method, the audio is routed to the earpiece by default. If you need to change the default audio route after joining a channel, call the \ref IRtcEngine::setEnableSpeakerphone "setEnableSpeakerphone" method.

     The default setting for each profile:
     - Communication: In a voice call, the default audio route is the earpiece. In a video call, the default audio route is the speakerphone. If a user who is in the Communication profile calls
     the \ref IRtcEngine.disableVideo "disableVideo" method or if the user calls
     the \ref IRtcEngine.muteLocalVideoStream "muteLocalVideoStream" and
     \ref IRtcEngine.muteAllRemoteVideoStreams "muteAllRemoteVideoStreams" methods, the
     default audio route switches back to the earpiece automatically.
     - Live Broadcast: Speakerphone.

     @note
     - This method is for Android and iOS only.
     - This method is applicable only to the Communication profile.
     - For iOS, this method only works in a voice call.
     - Call this method before calling the \ref IRtcEngine::joinChannel "joinChannel" method.

     @param defaultToSpeaker Sets the default audio route:
     - true: Route the audio to the speakerphone. If the playback device connects to the earpiece or Bluetooth, the audio cannot be routed to the speakerphone.
     - false: (Default) Route the audio to the earpiece. If a headset is plugged in, the audio is routed to the headset.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setDefaultAudioRouteToSpeakerphone(bool defaultToSpeaker) = 0;
    /** Enables/Disables the audio playback route to the speakerphone.

     This method sets whether the audio is routed to the speakerphone or earpiece.

     See the default audio route explanation in the \ref IRtcEngine::setDefaultAudioRouteToSpeakerphone "setDefaultAudioRouteToSpeakerphone" method and check whether it is necessary to call this method.

     @note
     - This method is for Android and iOS only.
     - Ensure that you have successfully called the \ref IRtcEngine::joinChannel "joinChannel" method before calling this method.
     - After calling this method, the SDK returns the \ref IRtcEngineEventHandler::onAudioRouteChanged "onAudioRouteChanged" callback to indicate the changes.
     - This method does not take effect if a headset is used.

     @param speakerOn Sets whether to route the audio to the speakerphone or earpiece:
     - true: Route the audio to the speakerphone. If the playback device connects to the earpiece or Bluetooth, the audio cannot be routed to the speakerphone.
     - false: Route the audio to the earpiece. If a headset is plugged in, the audio is routed to the headset.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setEnableSpeakerphone(bool speakerOn) = 0;
    /** Enables in-ear monitoring (for Android and iOS only).
     @param enabled Determines whether to enable in-ear monitoring.
     - true: Enable.
     - false: (Default) Disable.

     * @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int enableInEarMonitoring(bool enabled) = 0;
    /** Sets the volume of the in-ear monitor.

     @param volume Sets the volume of the in-ear monitor. The value ranges between 0 and 100 (default).

     @note This method is for Android and iOS only.

     @return
     - 0: Success.
     - < 0: Failure.
     */
	virtual int setInEarMonitoringVolume(int volume) = 0;
    /** Checks whether the speakerphone is enabled.

     @note This method is for Android and iOS only.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual bool isSpeakerphoneEnabled() = 0;
#endif

#if (defined(__APPLE__) && TARGET_OS_IOS)
    /** Sets the audio session’s operational restriction.

     The SDK and the app can both configure the audio session by default. The app may occasionally use other apps or third-party components to manipulate the audio session and restrict the SDK from doing so. This method allows the app to restrict the SDK’s manipulation of the audio session.

     You can call this method at any time to return the control of the audio sessions to the SDK.

     @note
     - This method is for iOS only.
     - This method restricts the SDK’s manipulation of the audio session. Any operation to the audio session relies solely on the app, other apps, or third-party components.

     @param restriction The operational restriction (bit mask) of the SDK on the audio session. See #AUDIO_SESSION_OPERATION_RESTRICTION.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setAudioSessionOperationRestriction(AUDIO_SESSION_OPERATION_RESTRICTION restriction) = 0;
#endif

#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE) || defined(_WIN32)
    /** Enables loopback recording.

     If you enable loopback recording, the output of the sound card is mixed into the audio stream sent to the other end.

     @param enabled Sets whether to enable/disable loopback recording.
     - true: Enable loopback recording.
     - false: (Default) Disable loopback recording.
     @param deviceName Pointer to the device name of the sound card. The default value is NULL (the default sound card).

     @note
     - This method is for macOS and Windows only.
     - macOS does not support loopback recording of the default sound card. If you need to use this method, please use a virtual sound card and pass its name to the deviceName parameter. Agora has tested and recommends using soundflower.

     */
    virtual int enableLoopbackRecording(bool enabled, const char* deviceName = NULL) = 0;

#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE)
    /** Shares the whole or part of a screen by specifying the display ID.

     @note This method is for macOS only.

     @param  displayId The display ID of the screen to be shared. This parameter specifies which screen you want to share.
     @param  regionRect (Optional) Sets the relative location of the region to the screen. NIL means sharing the whole screen. See Rectangle. If the specified region overruns the screen, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole screen.
     @param  captureParams Sets the screen sharing encoding parameters. See ScreenCaptureParameters.


     @return
     - 0: Success.
     - < 0: Failure:
        - #ERR_INVALID_ARGUMENT: the argument is invalid.
     */
    virtual int startScreenCaptureByDisplayId(unsigned int displayId, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams) = 0;
#endif

#if defined(_WIN32)
    /** Shares the whole or part of a screen by specifying the screen rect.

     @param  screenRect Sets the relative location of the screen to the virtual screen. For information on how to get screenRect, see the advanced guide *Share Screen*.
     @param  regionRect (Optional) Sets the relative location of the region to the screen. NULL means sharing the whole screen. See Rectangle. If the specified region overruns the screen, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole screen.
     @param  captureParams Sets the screen sharing encoding parameters. See ScreenCaptureParameters.

     @return
     - 0: Success.
     - < 0: Failure:
        - #ERR_INVALID_ARGUMENT : the argument is invalid.
     */
    virtual int startScreenCaptureByScreenRect(const Rectangle& screenRect, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams) = 0;
#endif

    /** Shares the whole or part of a window by specifying the window ID.

     Since v3.0.0, this method supports sharing with common Windows platforms. Agora tests the mainstream Windows applications, see details as follows:

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

     @param  windowId The ID of the window to be shared. For information on how to get the windowId, see the advanced guide *Share Screen*.
     @param  regionRect (Optional) The relative location of the region to the window. NULL/NIL means sharing the whole window. See Rectangle. If the specified region overruns the window, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole window.
     @param  captureParams Window sharing encoding parameters. See ScreenCaptureParameters.

     @return
     - 0: Success.
     - < 0: Failure:
        - #ERR_INVALID_ARGUMENT: the argument is invalid.
     */
    virtual int startScreenCaptureByWindowId(view_t windowId, const Rectangle& regionRect, const ScreenCaptureParameters& captureParams) = 0;

    /** Sets the content hint for screen sharing.

    A content hint suggests the type of the content being shared, so that the SDK applies different optimization algorithm to different types of content.

     @param  contentHint Sets the content hint for screen sharing. See VideoContentHint.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setScreenCaptureContentHint(VideoContentHint contentHint) = 0;

    /** Updates the screen sharing parameters.

     @param  captureParams Sets the screen sharing encoding parameters. See ScreenCaptureParameters.

     @return
     - 0: Success.
     - < 0: Failure:
        - #ERR_NOT_READY: no screen or windows is being shared.
     */
    virtual int updateScreenCaptureParameters(const ScreenCaptureParameters& captureParams) = 0;

    /** Updates the screen sharing region.

     @param  regionRect Sets the relative location of the region to the screen or window. NULL means sharing the whole screen or window. See Rectangle. If the specified region overruns the screen or window, the SDK shares only the region within it; if you set width or height as 0, the SDK shares the whole screen or window.

     @return
     - 0: Success.
     - < 0: Failure:
        - #ERR_NOT_READY: no screen or window is being shared.
     */
    virtual int updateScreenCaptureRegion(const Rectangle& regionRect) = 0;

    /** Stop screen sharing.

     @return
     - 0: Success.
     - < 0: Failure.
    */
    virtual int stopScreenCapture() = 0;

#if defined(__APPLE__)
    typedef unsigned int WindowIDType;
#elif defined(_WIN32)
    typedef HWND WindowIDType;
#endif

    /** **DEPRECATED** Starts screen sharing.

     This method is deprecated as of v2.4.0. See the following methods instead:

     - \ref agora::rtc::IRtcEngine::startScreenCaptureByDisplayId "startScreenCaptureByDisplayId"
     - \ref agora::rtc::IRtcEngine::startScreenCaptureByScreenRect "startScreenCaptureByScreenRect"
     - \ref agora::rtc::IRtcEngine::startScreenCaptureByWindowId "startScreenCaptureByWindowId"

     This method shares the whole screen, specified window, or specified region:

     - Whole screen: Set @p windowId as 0 and @p rect as NULL.
     - Specified window: Set @p windowId as a value other than 0. Each window has a @p windowId that is not 0.
     - Specified region: Set @p windowId as 0 and @p rect not as NULL. In this case, you can share the specified region, for example by dragging the mouse or implementing your own logic.

     @note The specified region is a region on the whole screen. Currently, sharing a specified region in a specific window is not supported.
     *captureFreq* is the captured frame rate once the screen-sharing function is enabled. The mandatory value ranges between 1 fps and 15 fps.

     @param windowId Sets the screen sharing area. See WindowIDType.
     @param captureFreq (Mandatory) The captured frame rate. The value ranges between 1 fps and 15 fps.
     @param rect Specifies the screen-sharing region. @p rect is valid when @p windowsId is set as 0. When @p rect is set as NULL, the whole screen is shared.
     @param bitrate The captured bitrate.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int startScreenCapture(WindowIDType windowId, int captureFreq, const Rect *rect, int bitrate) = 0;

    /** **DEPRECATED** Updates the screen capture region.

     @param rect Specifies the required region inside the screen or window.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int updateScreenCaptureRegion(const Rect *rect) = 0;
#endif

    /** Retrieves the current call ID.

     When a user joins a channel on a client, a @p callId is generated to identify the call from the client. Feedback methods, such as \ref IRtcEngine::rate "rate" and \ref IRtcEngine::complain "complain", must be called after the call ends to submit feedback to the SDK.

     The \ref IRtcEngine::rate "rate" and \ref IRtcEngine::complain "complain" methods require the @p callId parameter retrieved from the *getCallId* method during a call. @p callId is passed as an argument into the \ref IRtcEngine::rate "rate" and \ref IRtcEngine::complain "complain" methods after the call ends.

     @param callId Pointer to the current call ID.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getCallId(agora::util::AString& callId) = 0;

    /** Allows a user to rate a call after the call ends.

     @param callId Pointer to the ID of the call, retrieved from the \ref IRtcEngine::getCallId "getCallId" method.
     @param rating  Rating of the call. The value is between 1 (lowest score) and 5 (highest score). If you set a value out of this range, the #ERR_INVALID_ARGUMENT (2) error returns.
     @param description (Optional) Pointer to the description of the rating, with a string length of less than 800 bytes.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int rate(const char* callId, int rating, const char* description) = 0;

    /** Allows a user to complain about the call quality after a call ends.

    @param callId Pointer to the ID of the call, retrieved from the \ref IRtcEngine::getCallId "getCallId" method.
    @param description (Optional) Pointer to the description of the complaint, with a string length of less than 800 bytes.

    @return
    - 0: Success.
    - < 0: Failure.

    */
    virtual int complain(const char* callId, const char* description) = 0;

    /** Retrieves the SDK version number.

     @param build Pointer to the build number.
     @return The version of the current SDK in the string format. For example, 2.3.1.
     */
    virtual const char* getVersion(int* build) = 0;

    /**  Enables the network connection quality test.

     This method tests the quality of the users' network connections and is disabled by default.

     Before a user joins a channel or before an audience switches to a host, call this method to check the uplink network quality.

     This method consumes additional network traffic, and hence may affect communication quality.

     Call the \ref IRtcEngine::disableLastmileTest "disableLastmileTest" method to disable this test after receiving the \ref IRtcEngineEventHandler::onLastmileQuality "onLastmileQuality" callback, and before joining a channel.

     @note
     - Do not call any other methods before receiving the \ref IRtcEngineEventHandler::onLastmileQuality "onLastmileQuality" callback. Otherwise, the callback may be interrupted by other methods, and hence may not be triggered.
     - A host should not call this method after joining a channel (when in a call).
     - If you call this method to test the last-mile quality, the SDK consumes the bandwidth of a video stream, whose bitrate corresponds to the bitrate you set in the \ref agora::rtc::IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" method. After you join the channel, whether you have called the `disableLastmileTest` method or not, the SDK automatically stops consuming the bandwidth.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int enableLastmileTest() = 0;

    /** Disables the network connection quality test.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int disableLastmileTest() = 0;

    /** Starts the last-mile network probe test.

    This method starts the last-mile network probe test before joining a channel to get the uplink and downlink last-mile network statistics, including the bandwidth, packet loss, jitter, and round-trip time (RTT).

    Call this method to check the uplink network quality before users join a channel or before an audience switches to a host.
    Once this method is enabled, the SDK returns the following callbacks:
    - \ref IRtcEngineEventHandler::onLastmileQuality "onLastmileQuality": the SDK triggers this callback within two seconds depending on the network conditions. This callback rates the network conditions and is more closely linked to the user experience.
    - \ref IRtcEngineEventHandler::onLastmileProbeResult "onLastmileProbeResult": the SDK triggers this callback within 30 seconds depending on the network conditions. This callback returns the real-time statistics of the network conditions and is more objective.

    @note
    - This method consumes extra network traffic and may affect communication quality. We do not recommend calling this method together with enableLastmileTest.
    - Do not call other methods before receiving the \ref IRtcEngineEventHandler::onLastmileQuality "onLastmileQuality" and \ref IRtcEngineEventHandler::onLastmileProbeResult "onLastmileProbeResult" callbacks. Otherwise, the callbacks may be interrupted.
    - In the Live-broadcast profile, a host should not call this method after joining a channel.

    @param config Sets the configurations of the last-mile network probe test. See LastmileProbeConfig.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int startLastmileProbeTest(const LastmileProbeConfig& config) = 0;

    /** Stops the last-mile network probe test. */
    virtual int stopLastmileProbeTest() = 0;

    /** Retrieves the warning or error description.

     @param code Warning code or error code returned in the \ref agora::rtc::IRtcEngineEventHandler::onWarning "onWarning" or \ref agora::rtc::IRtcEngineEventHandler::onError "onError" callback.

     @return #WARN_CODE_TYPE or #ERROR_CODE_TYPE.
     */
    virtual const char* getErrorDescription(int code) = 0;

    /** Enables built-in encryption with an encryption password before users join a channel.

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
    virtual int setEncryptionSecret(const char* secret) = 0;

    /** Sets the built-in encryption mode.

     The Agora SDK supports built-in encryption, which is set to the @p aes-128-xts mode by default. Call this method to use other encryption modes.

     All users in the same channel must use the same encryption mode and password.

     Refer to the information related to the AES encryption algorithm on the differences between the encryption modes.

     @note Call the \ref IRtcEngine::setEncryptionSecret "setEncryptionSecret" method to enable the built-in encryption function before calling this method.

     @param encryptionMode Pointer to the set encryption mode:
     - "aes-128-xts": (Default) 128-bit AES encryption, XTS mode.
     - "aes-128-ecb": 128-bit AES encryption, ECB mode.
     - "aes-256-xts": 256-bit AES encryption, XTS mode.
     - "": When encryptionMode is set as NULL, the encryption mode is set as "aes-128-xts" by default.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setEncryptionMode(const char* encryptionMode) = 0;

    /** Registers a packet observer.

     The Agora SDK allows your application to register a packet observer to receive callbacks for voice or video packet transmission.

     @note
     - The size of the packet sent to the network after processing should not exceed 1200 bytes, otherwise, the packet may fail to be sent.
     - Ensure that both receivers and senders call this method, otherwise, you may meet undefined behaviors such as no voice and black screen.
     - When you use CDN live streaming, recording or storage functions, Agora doesn't recommend calling this method.

     @param observer Pointer to the registered packet observer. See IPacketObserver.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int registerPacketObserver(IPacketObserver* observer) = 0;

    /** Creates a data stream.

     Each user can create up to five data streams during the lifecycle of the IRtcEngine.

     @note Set both the @p reliable and @p ordered parameters to true or false. Do not set one as true and the other as false.

     @param streamId Pointer to the ID of the created data stream.
     @param reliable Sets whether or not the recipients are guaranteed to receive the data stream from the sender within five seconds:
     - true: The recipients receive the data stream from the sender within five seconds. If the recipient does not receive the data stream within five seconds, an error is reported to the application.
     - false: There is no guarantee that the recipients receive the data stream within five seconds and no error message is reported for any delay or missing data stream.
     @param ordered Sets whether or not the recipients receive the data stream in the sent order:
     - true: The recipients receive the data stream in the sent order.
     - false: The recipients do not receive the data stream in the sent order.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int createDataStream(int* streamId, bool reliable, bool ordered) = 0;

    /** Sends data stream messages to all users in a channel.

     The SDK has the following restrictions on this method:
     - Up to 30 packets can be sent per second in a channel with each packet having a maximum size of 1 kB.
     - Each client can send up to 6 kB of data per second.
     - Each user can have up to five data streams simultaneously.

     A successful \ref agora::rtc::IRtcEngine::sendStreamMessage "sendStreamMessage" method call triggers the
     \ref agora::rtc::IRtcEngineEventHandler::onStreamMessage "onStreamMessage" callback on the remote client, from which the remote user gets the stream message.

     A failed \ref agora::rtc::IRtcEngine::sendStreamMessage "sendStreamMessage" method call triggers the
      \ref agora::rtc::IRtcEngineEventHandler::onStreamMessage "onStreamMessage" callback on the remote client.
     @note This method applies only to the Communication profile or to the hosts in the Live-broadcast profile. If an audience in the Live-broadcast profile calls this method, the audience may be switched to a host.
     @param  streamId  ID of the sent data stream, returned in the \ref IRtcEngine::createDataStream "createDataStream" method.
     @param data Pointer to the sent data.
     @param length Length of the sent data.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int sendStreamMessage(int streamId, const char* data, size_t length) = 0;

    /** Publishes the local stream to a specified CDN live RTMP address.  (CDN live only.)

     The SDK returns the result of this method call in the \ref IRtcEngineEventHandler::onStreamPublished "onStreamPublished" callback.

     The \ref agora::rtc::IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" callback on the local client to report the state of adding a local stream to the CDN.
     @note
     - Ensure that the user joins the channel before calling this method.
     - Ensure that you enable the RTMP Converter service before using this function. See  *Prerequisites* in the advanced guide *Push Streams to CDN*.
     - This method adds only one stream RTMP URL address each time it is called.
     - This method applies to Live Broadcast only.

     @param url The CDN streaming URL in the RTMP format. The maximum length of this parameter is 1024 bytes. The RTMP URL address must not contain special characters, such as Chinese language characters.
     @param  transcodingEnabled Sets whether transcoding is enabled/disabled:
     - true: Enable transcoding. To [transcode](https://docs.agora.io/en/Agora%20Platform/terms?platform=All%20Platforms#transcoding) the audio or video streams when publishing them to CDN live, often used for combining the audio and video streams of multiple hosts in CDN live. If you set this parameter as `true`, ensure that you call the \ref IRtcEngine::setLiveTranscoding "setLiveTranscoding" method before this method.
     - false: Disable transcoding.

     @return
     - 0: Success.
     - < 0: Failure.
          - #ERR_INVALID_ARGUMENT (2): The RTMP URL address is NULL or has a string length of 0.
          - #ERR_NOT_INITIALIZED (7): You have not initialized the RTC engine when publishing the stream.
     */
    virtual int addPublishStreamUrl(const char *url, bool transcodingEnabled) = 0;

    /** Removes an RTMP stream from the CDN. (CDN live only.)

     This method removes the RTMP URL address (added by the \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" method) from a CDN live stream. The SDK returns the result of this method call in the \ref IRtcEngineEventHandler::onStreamUnpublished "onStreamUnpublished" callback.

     The \ref agora::rtc::IRtcEngine::removePublishStreamUrl "removePublishStreamUrl" method call triggers the \ref agora::rtc::IRtcEngineEventHandler::onRtmpStreamingStateChanged "onRtmpStreamingStateChanged" callback on the local client to report the state of removing an RTMP stream from the CDN.
     @note
     - This method removes only one RTMP URL address each time it is called.
     - The RTMP URL address must not contain special characters, such as Chinese language characters.
     - This method applies to Live Broadcast only.

     @param url The RTMP URL address to be removed. The maximum length of this parameter is 1024 bytes.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int removePublishStreamUrl(const char *url) = 0;

    /** Sets the video layout and audio settings for CDN live. (CDN live only.)

     The SDK triggers the \ref agora::rtc::IRtcEngineEventHandler::onTranscodingUpdated "onTranscodingUpdated" callback when you call the `setLiveTranscoding` method to update the transcoding setting.

     @note
     - This method applies to Live Broadcast only.
     - Ensure that you enable the RTMP Converter service before using this function. See *Prerequisites* in the advanced guide *Push Streams to CDN*.
     - If you call the `setLiveTranscoding` method to update the transcoding setting for the first time, the SDK does not trigger the `onTranscodingUpdated` callback.

     @param transcoding Sets the CDN live audio/video transcoding settings. See LiveTranscoding.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setLiveTranscoding(const LiveTranscoding &transcoding) = 0;

    /** **DEPRECATED** Adds a watermark image to the local video or CDN live stream.

     This method is deprecated from v2.9.1. Use \ref agora::rtc::IRtcEngine::addVideoWatermark(const char* watermarkUrl, const WatermarkOptions& options) "addVideoWatermark"2 instead.

     This method adds a PNG watermark image to the local video stream for the recording device, channel audience, and CDN live audience to view and capture.

     To add the PNG file to the CDN live publishing stream, see the \ref IRtcEngine::setLiveTranscoding "setLiveTranscoding" method.

     @param watermark Pointer to the watermark image to be added to the local video stream. See RtcImage.

     @note
     - The URL descriptions are different for the local video and CDN live streams:
        - In a local video stream, `url` in RtcImage refers to the absolute path of the added watermark image file in the local video stream.
        - In a CDN live stream, `url` in RtcImage refers to the URL address of the added watermark image in the CDN live broadcast.
     - The source file of the watermark image must be in the PNG file format. If the width and height of the PNG file differ from your settings in this method, the PNG file will be cropped to conform to your settings.
     - The Agora SDK supports adding only one watermark image onto a local video or CDN live stream. The newly added watermark image replaces the previous one.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int addVideoWatermark(const RtcImage& watermark) = 0;

    /** Adds a watermark image to the local video.

     This method adds a PNG watermark image to the local video in a live broadcast. Once the watermark image is added, all the audience in the channel (CDN audience included),
     and the recording device can see and capture it. Agora supports adding only one watermark image onto the local video, and the newly watermark image replaces the previous one.

     The watermark position depends on the settings in the \ref IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration" method:
     - If the orientation mode of the encoding video is #ORIENTATION_MODE_FIXED_LANDSCAPE, or the landscape mode in #ORIENTATION_MODE_ADAPTIVE, the watermark uses the landscape orientation.
     - If the orientation mode of the encoding video is #ORIENTATION_MODE_FIXED_PORTRAIT, or the portrait mode in #ORIENTATION_MODE_ADAPTIVE, the watermark uses the portrait orientation.
     - When setting the watermark position, the region must be less than the dimensions set in the `setVideoEncoderConfiguration` method. Otherwise, the watermark image will be cropped.

     @note
     - Ensure that you have called the \ref agora::rtc::IRtcEngine::enableVideo "enableVideo" method to enable the video module before calling this method.
     - If you only want to add a watermark image to the local video for the audience in the CDN live broadcast channel to see and capture, you can call this method or the \ref agora::rtc::IRtcEngine::setLiveTranscoding "setLiveTranscoding" method.
     - This method supports adding a watermark image in the PNG file format only. Supported pixel formats of the PNG image are RGBA, RGB, Palette, Gray, and Alpha_gray.
     - If the dimensions of the PNG image differ from your settings in this method, the image will be cropped or zoomed to conform to your settings.
     - If you have enabled the local video preview by calling the \ref agora::rtc::IRtcEngine::startPreview "startPreview" method, you can use the `visibleInPreview` member in the WatermarkOptions class to set whether or not the watermark is visible in preview.
     - If you have enabled the mirror mode for the local video, the watermark on the local video is also mirrored. To avoid mirroring the watermark, Agora recommends that you do not use the mirror and watermark functions for the local video at the same time. You can implement the watermark function in your application layer.

     @param watermarkUrl The local file path of the watermark image to be added. This method supports adding a watermark image from the local absolute or relative file path.
     @param options Pointer to the watermark's options to be added. See WatermarkOptions for more infomation.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int addVideoWatermark(const char* watermarkUrl, const WatermarkOptions& options) = 0;

    /** Removes the watermark image from the video stream added by the \ref agora::rtc::IRtcEngine::addVideoWatermark(const char* watermarkUrl, const WatermarkOptions& options) "addVideoWatermark" method.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int clearVideoWatermarks() = 0;

    /** @since v3.0.0

     Enables/Disables image enhancement and sets the options.

    @note
    - Call this method after calling the enableVideo method.
    - Currently this method does not apply for macOS.

    @param enabled Sets whether or not to enable image enhancement:
    - true: enables image enhancement.
    - false: disables image enhancement.
    @param options Sets the image enhancement option. See BeautyOptions.
    */
    virtual int setBeautyEffectOptions(bool enabled, BeautyOptions options) = 0;

    /** Adds a voice or video stream URL address to a live broadcast.

    The \ref IRtcEngineEventHandler::onStreamPublished "onStreamPublished" callback returns the inject status. If this method call is successful, the server pulls the voice or video stream and injects it into a live channel. This is applicable to scenarios where all audience members in the channel can watch a live show and interact with each other.

     The \ref agora::rtc::IRtcEngine::addInjectStreamUrl "addInjectStreamUrl" method call triggers the following callbacks:
    - The local client:
      - \ref agora::rtc::IRtcEngineEventHandler::onStreamInjectedStatus "onStreamInjectedStatus" , with the state of the injecting the online stream.
      - \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" (uid: 666), if the method call is successful and the online media stream is injected into the channel.
    - The remote client:
      - \ref agora::rtc::IRtcEngineEventHandler::onUserJoined "onUserJoined" (uid: 666), if the method call is successful and the online media stream is injected into the channel.

     @note
     - Ensure that you enable the RTMP Converter service before using this function. See *Prerequisites* in the advanced guide *Push Streams to CDN*.
     - This method applies to the Native SDK v2.4.1 and later.
     - This method applies to the Live-Broadcast profile only.
     - You can inject only one media stream into the channel at the same time.

     @param url Pointer to the URL address to be added to the ongoing live broadcast. Valid protocols are RTMP, HLS, and HTTP-FLV.
     - Supported audio codec type: AAC.
     - Supported video codec type: H264 (AVC).
     @param config Pointer to the InjectStreamConfig object that contains the configuration of the added voice or video stream.

     @return
     - 0: Success.
     - < 0: Failure.
        - #ERR_INVALID_ARGUMENT (2): The injected URL does not exist. Call this method again to inject the stream and ensure that the URL is valid.
        - #ERR_NOT_READY (3): The user is not in the channel.
        - #ERR_NOT_SUPPORTED (4): The channel profile is not live broadcast. Call the \ref agora::rtc::IRtcEngine::setChannelProfile "setChannelProfile" method and set the channel profile to live broadcast before calling this method.
        - #ERR_NOT_INITIALIZED (7): The SDK is not initialized. Ensure that the IRtcEngine object is initialized before calling this method.
     */
    virtual int addInjectStreamUrl(const char* url, const InjectStreamConfig& config) = 0;
    /** Starts to relay media streams across channels.
     *
     * After a successful method call, the SDK triggers the
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
     *  "onChannelMediaRelayStateChanged" and
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayEvent
     * "onChannelMediaRelayEvent" callbacks, and these callbacks return the
     * state and events of the media stream relay.
     * - If the
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
     *  "onChannelMediaRelayStateChanged" callback returns
     * #RELAY_STATE_RUNNING (2) and #RELAY_OK (0), and the
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayEvent
     * "onChannelMediaRelayEvent" callback returns
     * #RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL (4), the broadcaster starts
     * sending data to the destination channel.
     * - If the
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
     *  "onChannelMediaRelayStateChanged" callback returns
     * #RELAY_STATE_FAILURE (3), an exception occurs during the media stream
     * relay.
     *
     * @note
     * - Call this method after the \ref joinChannel() "joinChannel" method.
     * - This method takes effect only when you are a broadcaster in a
     * Live-broadcast channel.
     * - After a successful method call, if you want to call this method
     * again, ensure that you call the
     * \ref stopChannelMediaRelay() "stopChannelMediaRelay" method to quit the
     * current relay.
     * - Contact sales-us@agora.io before implementing this function.
     * - We do not support string user accounts in this API.
     *
     * @param configuration The configuration of the media stream relay:
     * ChannelMediaRelayConfiguration.
     *
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
	virtual int startChannelMediaRelay(const ChannelMediaRelayConfiguration &configuration) = 0;
    /** Updates the channels for media stream relay. After a successful
     * \ref startChannelMediaRelay() "startChannelMediaRelay" method call, if
     * you want to relay the media stream to more channels, or leave the
     * current relay channel, you can call the
     * \ref updateChannelMediaRelay() "updateChannelMediaRelay" method.
     *
     * After a successful method call, the SDK triggers the
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayEvent
     *  "onChannelMediaRelayEvent" callback with the
     * #RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL (7) state code.
     *
     * @note
     * Call this method after the
     * \ref startChannelMediaRelay() "startChannelMediaRelay" method to update
     * the destination channel.
     *
     * @param configuration The media stream relay configuration:
     * ChannelMediaRelayConfiguration.
     *
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
	virtual int updateChannelMediaRelay(const ChannelMediaRelayConfiguration &configuration) = 0;
    /** Stops the media stream relay.
     *
     * Once the relay stops, the broadcaster quits all the destination
     * channels.
     *
     * After a successful method call, the SDK triggers the
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
     *  "onChannelMediaRelayStateChanged" callback. If the callback returns
     * #RELAY_STATE_IDLE (0) and #RELAY_OK (0), the broadcaster successfully
     * stops the relay.
     *
     * @note
     * If the method call fails, the SDK triggers the
     * \ref agora::rtc::IRtcEngineEventHandler::onChannelMediaRelayStateChanged
     *  "onChannelMediaRelayStateChanged" callback with the
     * #RELAY_ERROR_SERVER_NO_RESPONSE (2) or
     * #RELAY_ERROR_SERVER_CONNECTION_LOST (8) state code. You can leave the
     * channel by calling the \ref leaveChannel() "leaveChannel" method, and
     * the media stream relay automatically stops.
     *
     * @return
     * - 0: Success.
     * - < 0: Failure.
     */
	virtual int stopChannelMediaRelay() = 0;

    /** Removes the voice or video stream URL address from a live broadcast.

     This method removes the URL address (added by the \ref IRtcEngine::addInjectStreamUrl "addInjectStreamUrl" method) from the live broadcast.

     @note If this method is called successfully, the SDK triggers the \ref IRtcEngineEventHandler::onUserOffline "onUserOffline" callback and returns a stream uid of 666.

     @param url Pointer to the URL address of the added stream to be removed.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int removeInjectStreamUrl(const char* url) = 0;
    virtual bool registerEventHandler(IRtcEngineEventHandler *eventHandler) = 0;
    virtual bool unregisterEventHandler(IRtcEngineEventHandler *eventHandler) = 0;
    /** Gets the current connection state of the SDK.

     @return #CONNECTION_STATE_TYPE.
     */
    virtual CONNECTION_STATE_TYPE getConnectionState() = 0;

    /** Registers the metadata observer.

     Registers the metadata observer. You need to implement the IMetadataObserver class and specify the metadata type in this method. A successful call of this method triggers the \ref agora::rtc::IMetadataObserver::getMaxMetadataSize "getMaxMetadataSize" callback.
     This method enables you to add synchronized metadata in the video stream for more diversified live broadcast interactions, such as sending shopping links, digital coupons, and online quizzes.

     @note
     - Call this method before the joinChannel method.
     - This method applies to the Live-broadcast channel profile.

     @param observer The IMetadataObserver class. See the definition of IMetadataObserver for details.
     @param type See \ref IMetadataObserver::METADATA_TYPE "METADATA_TYPE". The SDK supports VIDEO_METADATA (0) only for now.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int registerMediaMetadataObserver(IMetadataObserver *observer, IMetadataObserver::METADATA_TYPE type) = 0;
    /** Provides technical preview functionalities or special customizations by configuring the SDK with JSON options.

     The JSON options are not public by default. Agora is working on making commonly used JSON options public in a standard way.

     @param parameters Sets the parameter as a JSON string in the specified format.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setParameters(const char* parameters) = 0;
};


class IRtcEngineParameter
{
public:
    virtual ~IRtcEngineParameter () {}
    /**
    * Releases all IRtcEngineParameter resources.
    */
    virtual void release() = 0;

    /** Sets the bool value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Sets the value.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setBool(const char* key, bool value) = 0;

    /** Sets the int value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Sets the value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setInt(const char* key, int value) = 0;

    /** Sets the unsigned int value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Sets the value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setUInt(const char* key, unsigned int value) = 0;

    /** Sets the double value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Sets the value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setNumber(const char* key, double value) = 0;

    /** Sets the string value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the set value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setString(const char* key, const char* value) = 0;

    /** Sets the object value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the set value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setObject(const char* key, const char* value) = 0;

    /** Retrieves the bool value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the retrieved value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getBool(const char* key, bool& value) = 0;

    /** Retrieves the int value of the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the retrieved value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getInt(const char* key, int& value) = 0;

    /** Retrieves the unsigned int value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the retrieved value.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getUInt(const char* key, unsigned int& value) = 0;

    /** Retrieves the double value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the retrieved value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getNumber(const char* key, double& value) = 0;

    /** Retrieves the string value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the retrieved value.

     @return
     - 0: Success.
     - < 0: Failure.
    */
    virtual int getString(const char* key, agora::util::AString& value) = 0;

    /** Retrieves a child object value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the retrieved value.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getObject(const char* key, agora::util::AString& value) = 0;

    /** Retrieves the array value of a specified key in the JSON format.

     @param key Pointer to the name of the key.
     @param value Pointer to the retrieved value.
     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int getArray(const char* key, agora::util::AString& value) = 0;

    /** Provides the technical preview functionalities or special customizations by configuring the SDK with JSON options.

     @param parameters Pointer to the set parameters in a JSON string.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setParameters(const char* parameters) = 0;

    /** Sets the profile to control the RTC engine.

     @param profile Pointer to the set profile.
     @param merge Sets whether to merge the profile data with the original value:
     - true: Merge the profile data with the original value.
     - false: Do not merge the profile data with the original value.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    virtual int setProfile(const char* profile, bool merge) = 0;

	virtual int convertPath(const char* filePath, agora::util::AString& value) = 0;
};

class AAudioDeviceManager : public agora::util::AutoPtr<IAudioDeviceManager>
{
public:
    AAudioDeviceManager(IRtcEngine* engine)
    {
		queryInterface(engine, AGORA_IID_AUDIO_DEVICE_MANAGER);
    }
};

class AVideoDeviceManager : public agora::util::AutoPtr<IVideoDeviceManager>
{
public:
    AVideoDeviceManager(IRtcEngine* engine)
    {
		queryInterface(engine, AGORA_IID_VIDEO_DEVICE_MANAGER);
    }
};

class AParameter : public agora::util::AutoPtr<IRtcEngineParameter>
{
public:
    AParameter(IRtcEngine& engine) { initialize(&engine); }
    AParameter(IRtcEngine* engine) { initialize(engine); }
    AParameter(IRtcEngineParameter* p) :agora::util::AutoPtr<IRtcEngineParameter>(p) {}
private:
    bool initialize(IRtcEngine* engine)
    {
        IRtcEngineParameter* p = NULL;
        if (engine && !engine->queryInterface(AGORA_IID_RTC_ENGINE_PARAMETER, (void**)&p))
            reset(p);
        return p != NULL;
    }
};
/** **DEPRECATED** The RtcEngineParameters class is deprecated, use the IRtcEngine class instead.
*/
class RtcEngineParameters
{
public:
    RtcEngineParameters(IRtcEngine& engine)
        :m_parameter(&engine){}
    RtcEngineParameters(IRtcEngine* engine)
        :m_parameter(engine){}


    int enableLocalVideo(bool enabled) {
        return setParameters("{\"rtc.video.capture\":%s,\"che.video.local.capture\":%s,\"che.video.local.render\":%s,\"che.video.local.send\":%s}", enabled ? "true" : "false", enabled ? "true" : "false", enabled ? "true" : "false", enabled ? "true" : "false");
    }



    int muteLocalVideoStream(bool mute) {
        return setParameters("{\"rtc.video.mute_me\":%s,\"che.video.local.send\":%s}", mute ? "true" : "false", mute ? "false" : "true");
    }


    int muteAllRemoteVideoStreams(bool mute) {
        return m_parameter ? m_parameter->setBool("rtc.video.mute_peers", mute) : -ERR_NOT_INITIALIZED;
    }



    int setDefaultMuteAllRemoteVideoStreams(bool mute) {
        return m_parameter ? m_parameter->setBool("rtc.video.set_default_mute_peers", mute) : -ERR_NOT_INITIALIZED;
    }


    int muteRemoteVideoStream(uid_t uid, bool mute) {
        return setObject("rtc.video.mute_peer", "{\"uid\":%u,\"mute\":%s}", uid, mute ? "true" : "false");
    }


    int setPlaybackDeviceVolume(int volume) {// [0,255]
        return m_parameter ? m_parameter->setInt("che.audio.output.volume", volume) : -ERR_NOT_INITIALIZED;
    }


    int startAudioRecording(const char* filePath, AUDIO_RECORDING_QUALITY_TYPE quality) {
        return startAudioRecording(filePath, 32000, quality);
    }

    int startAudioRecording(const char* filePath, int sampleRate, AUDIO_RECORDING_QUALITY_TYPE quality) {
        if (!m_parameter) return -ERR_NOT_INITIALIZED;
#if defined(_WIN32)
        util::AString path;
        if (!m_parameter->convertPath(filePath, path))
            filePath = path->c_str();
        else
            return -ERR_INVALID_ARGUMENT;
#endif
        return setObject("che.audio.start_recording", "{\"filePath\":\"%s\",\"sampleRate\":%d,\"quality\":%d}", filePath, sampleRate, quality);
    }


    int stopAudioRecording() {
        return m_parameter ? m_parameter->setBool("che.audio.stop_recording", true) : -ERR_NOT_INITIALIZED;
    }


    int startAudioMixing(const char* filePath, bool loopback, bool replace, int cycle) {
        if (!m_parameter) return -ERR_NOT_INITIALIZED;
#if defined(_WIN32)
        util::AString path;
        if (!m_parameter->convertPath(filePath, path))
            filePath = path->c_str();
        else
            return -ERR_INVALID_ARGUMENT;
#endif
        return setObject("che.audio.start_file_as_playout", "{\"filePath\":\"%s\",\"loopback\":%s,\"replace\":%s,\"cycle\":%d}",
                         filePath,
                         loopback?"true":"false",
                         replace?"true":"false",
                         cycle);
    }


    int stopAudioMixing() {
        return m_parameter ? m_parameter->setBool("che.audio.stop_file_as_playout", true) : -ERR_NOT_INITIALIZED;
    }


    int pauseAudioMixing() {
        return m_parameter ? m_parameter->setBool("che.audio.pause_file_as_playout", true) : -ERR_NOT_INITIALIZED;
    }


    int resumeAudioMixing() {
        return m_parameter ? m_parameter->setBool("che.audio.pause_file_as_playout", false) : -ERR_NOT_INITIALIZED;
    }


    int adjustAudioMixingVolume(int volume) {
        int ret = adjustAudioMixingPlayoutVolume(volume);
        if (ret == 0) {
            adjustAudioMixingPublishVolume(volume);
        }
        return ret;
    }


    int adjustAudioMixingPlayoutVolume(int volume) {
        return m_parameter ? m_parameter->setInt("che.audio.set_file_as_playout_volume", volume) : -ERR_NOT_INITIALIZED;
    }


    int getAudioMixingPlayoutVolume() {
        int volume = 0;
        int r = m_parameter ? m_parameter->getInt("che.audio.get_file_as_playout_volume", volume) : -ERR_NOT_INITIALIZED;
        if (r == 0)
            r = volume;
        return r;
    }


    int adjustAudioMixingPublishVolume(int volume) {
        return m_parameter ? m_parameter->setInt("che.audio.set_file_as_playout_publish_volume", volume) : -ERR_NOT_INITIALIZED;
    }


    int getAudioMixingPublishVolume() {
        int volume = 0;
        int r = m_parameter ? m_parameter->getInt("che.audio.get_file_as_playout_publish_volume", volume) : -ERR_NOT_INITIALIZED;
        if (r == 0)
            r = volume;
        return r;
    }


    int getAudioMixingDuration() {
        int duration = 0;
        int r = m_parameter ? m_parameter->getInt("che.audio.get_mixing_file_length_ms", duration) : -ERR_NOT_INITIALIZED;
        if (r == 0)
            r = duration;
        return r;
    }


    int getAudioMixingCurrentPosition() {
        if (!m_parameter) return -ERR_NOT_INITIALIZED;
        int pos = 0;
        int r = m_parameter->getInt("che.audio.get_mixing_file_played_ms", pos);
        if (r == 0)
            r = pos;
        return r;
    }

    int setAudioMixingPosition(int pos /*in ms*/) {
        return m_parameter ? m_parameter->setInt("che.audio.mixing.file.position", pos) : -ERR_NOT_INITIALIZED;
    }

    int setAudioMixingPitch(int pitch) {
        if (!m_parameter) {
            return -ERR_NOT_INITIALIZED;
        }
        if (pitch > 12 || pitch < -12) {
            return -ERR_INVALID_ARGUMENT;
        }
        return m_parameter->setInt("che.audio.set_playout_file_pitch_semitones", pitch);
    }

    int getEffectsVolume() {
        if (!m_parameter) return -ERR_NOT_INITIALIZED;
        int volume = 0;
        int r = m_parameter->getInt("che.audio.game_get_effects_volume", volume);
        if (r == 0)
            r = volume;
        return r;
    }


    int setEffectsVolume(int volume) {
        return m_parameter ? m_parameter->setInt("che.audio.game_set_effects_volume", volume) : -ERR_NOT_INITIALIZED;
    }


    int setVolumeOfEffect(int soundId, int volume) {
        return setObject(
                         "che.audio.game_adjust_effect_volume",
                         "{\"soundId\":%d,\"gain\":%d}",
                         soundId, volume);
    }


    int playEffect(int soundId, const char* filePath, int loopCount, double pitch, double pan, int gain, bool publish = false) {
#if defined(_WIN32)
        util::AString path;
        if (!m_parameter->convertPath(filePath, path))
            filePath = path->c_str();
        else if (!filePath)
            filePath = "";
#endif
        return setObject(
                         "che.audio.game_play_effect",
                         "{\"soundId\":%d,\"filePath\":\"%s\",\"loopCount\":%d, \"pitch\":%lf,\"pan\":%lf,\"gain\":%d, \"send2far\":%d}",
                         soundId, filePath, loopCount, pitch, pan, gain, publish);
    }


    int stopEffect(int soundId) {
        return m_parameter ? m_parameter->setInt(
                                                 "che.audio.game_stop_effect", soundId) : -ERR_NOT_INITIALIZED;
    }


    int stopAllEffects() {
        return m_parameter ? m_parameter->setBool(
                                                  "che.audio.game_stop_all_effects", true) : -ERR_NOT_INITIALIZED;
    }


    int preloadEffect(int soundId, char* filePath) {
        return setObject(
                         "che.audio.game_preload_effect",
                         "{\"soundId\":%d,\"filePath\":\"%s\"}",
                         soundId, filePath);
    }


    int unloadEffect(int soundId) {
        return m_parameter ? m_parameter->setInt(
                                                 "che.audio.game_unload_effect", soundId) : -ERR_NOT_INITIALIZED;
    }


    int pauseEffect(int soundId) {
        return m_parameter ? m_parameter->setInt(
                                                 "che.audio.game_pause_effect", soundId) : -ERR_NOT_INITIALIZED;
    }


    int pauseAllEffects() {
        return m_parameter ? m_parameter->setBool(
                                                  "che.audio.game_pause_all_effects", true) : -ERR_NOT_INITIALIZED;
    }


    int resumeEffect(int soundId) {
        return m_parameter ? m_parameter->setInt(
                                                 "che.audio.game_resume_effect", soundId) : -ERR_NOT_INITIALIZED;
    }


    int resumeAllEffects() {
        return m_parameter ? m_parameter->setBool(
                                                  "che.audio.game_resume_all_effects", true) : -ERR_NOT_INITIALIZED;
    }


    int enableSoundPositionIndication(bool enabled) {
        return m_parameter ? m_parameter->setBool(
                                                  "che.audio.enable_sound_position", enabled) : -ERR_NOT_INITIALIZED;
    }


    int setRemoteVoicePosition(uid_t uid, double pan, double gain) {
        return setObject("che.audio.game_place_sound_position", "{\"uid\":%u,\"pan\":%lf,\"gain\":%lf}", uid, pan, gain);
    }


    int setLocalVoicePitch(double pitch) {
        return m_parameter ? m_parameter->setInt(
                                                 "che.audio.morph.pitch_shift",
                                                 static_cast<int>(pitch * 100)) : -ERR_NOT_INITIALIZED;
    }

    int setLocalVoiceEqualization(AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain) {
        return setObject(
                         "che.audio.morph.equalization",
                         "{\"index\":%d,\"gain\":%d}",
                         static_cast<int>(bandFrequency), bandGain);
    }

    int setLocalVoiceReverb(AUDIO_REVERB_TYPE reverbKey, int value) {
        return setObject(
                         "che.audio.morph.reverb",
                         "{\"key\":%d,\"value\":%d}",
                         static_cast<int>(reverbKey), value);
    }


    int setLocalVoiceChanger(VOICE_CHANGER_PRESET voiceChanger) {
        if(voiceChanger == 0x00000000)
        {
            return m_parameter ? m_parameter->setInt("che.audio.morph.voice_changer", static_cast<int>(voiceChanger)) : -ERR_NOT_INITIALIZED;
        }
        else if(voiceChanger > 0x00000000 && voiceChanger < 0x00100000)
        {
            return m_parameter ? m_parameter->setInt("che.audio.morph.voice_changer", static_cast<int>(voiceChanger)) : -ERR_NOT_INITIALIZED;
        }
        else if(voiceChanger > 0x00100000 && voiceChanger < 0x00200000)
        {
            return m_parameter ? m_parameter->setInt("che.audio.morph.voice_changer", static_cast<int>(voiceChanger - 0x00100000 + 6)) : -ERR_NOT_INITIALIZED;
        }
        else if(voiceChanger > 0x00200000 && voiceChanger < 0x00300000)
        {
            return m_parameter ? m_parameter->setInt("che.audio.morph.beauty_voice", static_cast<int>(voiceChanger - 0x00200000)) : -ERR_NOT_INITIALIZED;
        }
        else
        {
            return -ERR_NOT_INITIALIZED;
        }
    }


    int setLocalVoiceReverbPreset(AUDIO_REVERB_PRESET reverbPreset) {
        if(reverbPreset == 0x00000000)
        {
            return m_parameter ? m_parameter->setInt("che.audio.morph.reverb_preset", static_cast<int>(reverbPreset)) : -ERR_NOT_INITIALIZED;
        }
        else if(reverbPreset > 0x00000000 && reverbPreset < 0x00100000)
        {
            return m_parameter ? m_parameter->setInt("che.audio.morph.reverb_preset", static_cast<int>(reverbPreset + 8)) : -ERR_NOT_INITIALIZED;
        }
        else if(reverbPreset > 0x00100000 && reverbPreset < 0x00200000)
        {
            return m_parameter ? m_parameter->setInt("che.audio.morph.reverb_preset", static_cast<int>(reverbPreset - 0x00100000)) : -ERR_NOT_INITIALIZED;
        }
        else if(reverbPreset > 0x00200000 && reverbPreset < 0x00200002)
        {
            return m_parameter ? m_parameter->setInt("che.audio.morph.virtual_stereo", static_cast<int>(reverbPreset - 0x00200000)) : -ERR_NOT_INITIALIZED;
        }
        else
        {
            return -ERR_NOT_INITIALIZED;
        }
    }

    /** **DEPRECATED** Use \ref IRtcEngine::disableAudio "disableAudio" instead. Disables the audio function in the channel.

     @return
     - 0: Success.
     - < 0: Failure.
     */
    int pauseAudio() {
        return m_parameter ? m_parameter->setBool("che.pause.audio", true) : -ERR_NOT_INITIALIZED;
    }


    int resumeAudio() {
        return m_parameter ? m_parameter->setBool("che.pause.audio", false) : -ERR_NOT_INITIALIZED;
    }


    int setHighQualityAudioParameters(bool fullband, bool stereo, bool fullBitrate) {
        return setObject("che.audio.codec.hq", "{\"fullband\":%s,\"stereo\":%s,\"fullBitrate\":%s}", fullband ? "true" : "false", stereo ? "true" : "false", fullBitrate ? "true" : "false");
    }


    int adjustRecordingSignalVolume(int volume) {//[0, 400]: e.g. 50~0.5x 100~1x 400~4x
        if (volume < 0)
            volume = 0;
        else if (volume > 400)
            volume = 400;
        return m_parameter ? m_parameter->setInt("che.audio.record.signal.volume", volume) : -ERR_NOT_INITIALIZED;
    }


    int adjustPlaybackSignalVolume(int volume) {//[0, 400]
        if (volume < 0)
            volume = 0;
        else if (volume > 400)
            volume = 400;
        return m_parameter ? m_parameter->setInt("che.audio.playout.signal.volume", volume) : -ERR_NOT_INITIALIZED;
    }


    int enableAudioVolumeIndication(int interval, int smooth, bool report_vad) { // in ms: <= 0: disable, > 0: enable, interval in ms
        if (interval < 0)
            interval = 0;
        return setObject("che.audio.volume_indication", "{\"interval\":%d,\"smooth\":%d,\"vad\":%d}", interval, smooth, report_vad);
    }


    int muteLocalAudioStream(bool mute) {
        return setParameters("{\"rtc.audio.mute_me\":%s,\"che.audio.mute_me\":%s}", mute ? "true" : "false", mute ? "true" : "false");
    }
    // mute/unmute all peers. unmute will clear all muted peers specified mutePeer() interface


    int muteRemoteAudioStream(uid_t uid, bool mute) {
        return setObject("rtc.audio.mute_peer", "{\"uid\":%u,\"mute\":%s}", uid, mute?"true":"false");
    }


    int muteAllRemoteAudioStreams(bool mute) {
        return m_parameter ? m_parameter->setBool("rtc.audio.mute_peers", mute) : -ERR_NOT_INITIALIZED;
    }


    int setDefaultMuteAllRemoteAudioStreams(bool mute) {
        return m_parameter ? m_parameter->setBool("rtc.audio.set_default_mute_peers", mute) : -ERR_NOT_INITIALIZED;
    }


    int setExternalAudioSource(bool enabled, int sampleRate, int channels) {
        if (enabled)
            return setParameters("{\"che.audio.external_capture\":true,\"che.audio.external_capture.push\":true,\"che.audio.set_capture_raw_audio_format\":{\"sampleRate\":%d,\"channelCnt\":%d,\"mode\":%d}}", sampleRate, channels, RAW_AUDIO_FRAME_OP_MODE_TYPE::RAW_AUDIO_FRAME_OP_MODE_READ_WRITE);
        else
            return setParameters("{\"che.audio.external_capture\":false,\"che.audio.external_capture.push\":false}");
    }


    int setExternalAudioSink(bool enabled, int sampleRate, int channels) {
        if (enabled)
            return setParameters("{\"che.audio.external_render\":true,\"che.audio.external_render.pull\":true,\"che.audio.set_render_raw_audio_format\":{\"sampleRate\":%d,\"channelCnt\":%d,\"mode\":%d}}", sampleRate, channels, RAW_AUDIO_FRAME_OP_MODE_TYPE::RAW_AUDIO_FRAME_OP_MODE_READ_ONLY);
        else
            return setParameters("{\"che.audio.external_render\":false,\"che.audio.external_render.pull\":false}");
    }


    int setLogFile(const char* filePath) {
        if (!m_parameter) return -ERR_NOT_INITIALIZED;
#if defined(_WIN32)
        util::AString path;
        if (!m_parameter->convertPath(filePath, path))
            filePath = path->c_str();
        else if (!filePath)
            filePath = "";
#endif
        return m_parameter->setString("rtc.log_file", filePath);
    }


    int setLogFilter(unsigned int filter) {
        return m_parameter ? m_parameter->setUInt("rtc.log_filter", filter&LOG_FILTER_MASK) : -ERR_NOT_INITIALIZED;
    }


    int setLogFileSize(unsigned int fileSizeInKBytes) {
        return m_parameter ? m_parameter->setUInt("rtc.log_size", fileSizeInKBytes) : -ERR_NOT_INITIALIZED;
    }


    int setLocalRenderMode(RENDER_MODE_TYPE renderMode) {
        return setRemoteRenderMode(0, renderMode);
    }


    int setRemoteRenderMode(uid_t uid, RENDER_MODE_TYPE renderMode) {
        return setParameters("{\"che.video.render_mode\":[{\"uid\":%u,\"renderMode\":%d}]}", uid, renderMode);
    }


    int setCameraCapturerConfiguration(const CameraCapturerConfiguration& config) {
        if (!m_parameter) return -ERR_NOT_INITIALIZED;
        return m_parameter->setInt("che.video.camera_capture_mode", (int)config.preference);
    }


    int enableDualStreamMode(bool enabled) {
        return setParameters("{\"rtc.dual_stream_mode\":%s,\"che.video.enableLowBitRateStream\":%d}", enabled ? "true" : "false", enabled ? 1 : 0);
    }


    int setRemoteVideoStreamType(uid_t uid, REMOTE_VIDEO_STREAM_TYPE streamType) {
        return setParameters("{\"rtc.video.set_remote_video_stream\":{\"uid\":%u,\"stream\":%d}, \"che.video.setstream\":{\"uid\":%u,\"stream\":%d}}", uid, streamType, uid, streamType);
//        return setObject("rtc.video.set_remote_video_stream", "{\"uid\":%u,\"stream\":%d}", uid, streamType);
    }


    int setRemoteDefaultVideoStreamType(REMOTE_VIDEO_STREAM_TYPE streamType) {
        return m_parameter ? m_parameter->setInt("rtc.video.set_remote_default_video_stream_type", streamType) : -ERR_NOT_INITIALIZED;
    }


    int setRecordingAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) {
        return setObject("che.audio.set_capture_raw_audio_format", "{\"sampleRate\":%d,\"channelCnt\":%d,\"mode\":%d,\"samplesPerCall\":%d}", sampleRate, channel, mode, samplesPerCall);
    }

    int setPlaybackAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) {
        return setObject("che.audio.set_render_raw_audio_format", "{\"sampleRate\":%d,\"channelCnt\":%d,\"mode\":%d,\"samplesPerCall\":%d}", sampleRate, channel, mode, samplesPerCall);
    }

    int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall) {
        return setObject("che.audio.set_mixed_raw_audio_format", "{\"sampleRate\":%d,\"samplesPerCall\":%d}", sampleRate, samplesPerCall);
    }


    int enableWebSdkInteroperability(bool enabled) {//enable interoperability with zero-plugin web sdk
        return setParameters("{\"rtc.video.web_h264_interop_enable\":%s,\"che.video.web_h264_interop_enable\":%s}", enabled ? "true" : "false", enabled ? "true" : "false");
    }

    //only for live broadcast

    int setVideoQualityParameters(bool preferFrameRateOverImageQuality) {
        return setParameters("{\"rtc.video.prefer_frame_rate\":%s,\"che.video.prefer_frame_rate\":%s}", preferFrameRateOverImageQuality ? "true" : "false", preferFrameRateOverImageQuality ? "true" : "false");
    }


    int setLocalVideoMirrorMode(VIDEO_MIRROR_MODE_TYPE mirrorMode) {
        if (!m_parameter) return -ERR_NOT_INITIALIZED;
        const char *value;
        switch (mirrorMode) {
            case VIDEO_MIRROR_MODE_AUTO:
                value = "default";
                break;
            case VIDEO_MIRROR_MODE_ENABLED:
                value = "forceMirror";
                break;
            case VIDEO_MIRROR_MODE_DISABLED:
                value = "disableMirror";
                break;
            default:
                return -ERR_INVALID_ARGUMENT;
        }
        return m_parameter->setString("che.video.localViewMirrorSetting", value);
    }


    int setLocalPublishFallbackOption(STREAM_FALLBACK_OPTIONS option) {
        return m_parameter ? m_parameter->setInt("rtc.local_publish_fallback_option", option) : -ERR_NOT_INITIALIZED;
    }


    int setRemoteSubscribeFallbackOption(STREAM_FALLBACK_OPTIONS option) {
        return m_parameter ? m_parameter->setInt("rtc.remote_subscribe_fallback_option", option) : -ERR_NOT_INITIALIZED;
    }

#if (defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE) || defined(_WIN32)

    int enableLoopbackRecording(bool enabled, const char* deviceName = NULL) {
        if (!deviceName) {
            return setParameters("{\"che.audio.loopback.recording\":%s}", enabled ? "true" : "false");
        }
        else {
            return setParameters("{\"che.audio.loopback.deviceName\":\"%s\",\"che.audio.loopback.recording\":%s}", deviceName, enabled ? "true" : "false");
        }
    }
#endif


    int setInEarMonitoringVolume(int volume) {
        return m_parameter ? m_parameter->setInt("che.audio.headset.monitoring.parameter", volume) : -ERR_NOT_INITIALIZED;
    }

protected:
    AParameter& parameter() {
        return m_parameter;
    }
    int setParameters(const char* format, ...) {
        char buf[512];
        va_list args;
        va_start(args, format);
        vsnprintf(buf, sizeof(buf)-1, format, args);
        va_end(args);
        return m_parameter ? m_parameter->setParameters(buf) : -ERR_NOT_INITIALIZED;
    }
    int setObject(const char* key, const char* format, ...) {
        char buf[512];
        va_list args;
        va_start(args, format);
        vsnprintf(buf, sizeof(buf)-1, format, args);
        va_end(args);
        return m_parameter ? m_parameter->setObject(key, buf) : -ERR_NOT_INITIALIZED;
    }
    int stopAllRemoteVideo() {
        return m_parameter ? m_parameter->setBool("che.video.peer.stop_render", true) : -ERR_NOT_INITIALIZED;
    }
private:
    AParameter m_parameter;
};

} //namespace rtc
} // namespace agora


#define getAgoraRtcEngineVersion getAgoraSdkVersion

////////////////////////////////////////////////////////
/** \addtogroup createAgoraRtcEngine
 @{
 */
////////////////////////////////////////////////////////

/** Creates the IRtcEngine object and returns the pointer.
 *
 * @note The Agora RTC Native SDK supports creating only one `IRtcEngine` object for an app for now.
 *
 * @return Pointer to the IRtcEngine object.
 */
AGORA_API agora::rtc::IRtcEngine* AGORA_CALL createAgoraRtcEngine();

////////////////////////////////////////////////////////
/** @} */
////////////////////////////////////////////////////////

#define getAgoraRtcEngineErrorDescription getAgoraSdkErrorDescription
#define setAgoraRtcEngineExternalSymbolLoader setAgoraSdkExternalSymbolLoader

#endif
