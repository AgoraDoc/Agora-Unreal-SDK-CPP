//  Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include <memory>

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif

#if (defined(__APPLE__) && TARGET_OS_IPHONE)
#include <Agora/iOS/Include/IAgoraRtcEngine.h>
#else
    #include <Agora/IAgoraRtcEngine.h>
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

/** @~chinese
 * AudioDeviceCollection 类。
 */
/** @~english
 * Wrapper around agora::rtc::IAudioDeviceCollection
 */
class AGORAPLUGIN_API AudioDeviceCollection
{

public:
	AudioDeviceCollection() = delete;
	AudioDeviceCollection(agora::rtc::IAudioDeviceCollection* collection);
	AudioDeviceCollection(const AudioDeviceCollection& other);
	AudioDeviceCollection(AudioDeviceCollection&& other) noexcept;
	AudioDeviceCollection& operator=(const AudioDeviceCollection& other);
	AudioDeviceCollection& operator=(AudioDeviceCollection&& other) noexcept;
	~AudioDeviceCollection();

public:


   /** @~chinese
   获取播放或音频采集设备数量。

   如果先调用 \ref agora::rtc::IAudioDeviceManager::enumeratePlaybackDevices "enumeratePlaybackDevices" 再调用该方法，返回播放设备的数量。
   如果先调用 \ref agora::rtc::IAudioDeviceManager::enumerateRecordingDevices "enumerateRecordingDevices" 再调用该方法，返回音频采集设备的数量。

   @return 音频设备的数量。
   */
   /** @~english
   * @brief           Retrieves the total number of audio playback or audio recording devices.
   * @note            You must first call the \ref IAudioDeviceManager::enumeratePlaybackDevices "enumeratePlaybackDevices"
   *                  or \ref IAudioDeviceManager::enumerateRecordingDevices "enumerateRecordingDevices" method before calling this method to return the number of  audio playback or audio recording devices.
   * @return          Number of audio playback or audio recording devices.
   */
	int getCount();

   /** @~chinese
   获取指定 index 的设备信息。

   @param index 输入参数，指定想查询的设备信息。请确保该参数的值小于 \ref IAudioDeviceCollection::getCount "getCount" 的返回值。
   @param deviceName 输出参数，设备名称。
   @param deviceId 输出参数，设备 ID。

   @return

   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief           Retrieves a specified piece of information about an indexed audio device.
   * @param           index
   *                  The specified index that must be less than the return value of \ref IAudioDeviceCollection::getCount "getCount".
   * @param           deviceName
   *                  Pointer to the audio device name.
   * @param           deviceId
   *                  Pointer to the audio device ID.
   * @return
   *                  - 0: Success.
   *                  - < 0: Failure.
   */
   int getDevice(
		int index,
		char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH],
		char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /** @~chinese
   指定设备。

   @param deviceId 设备 ID。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief           Specifies a device with the device ID.
   * @param           deviceId
   *                  Pointer to the device ID of the device.
   * @return
   *                  - 0: Success.
   *                  - < 0: Failure.
   */
	int setDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /** @~chinese
   设置 App 音量。

   @param volume 音量值，范围 [0,255]。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief           Sets the volume of the application.
   * @param           volume
   *                  Application volume. The value ranges between 0 (lowest volume) and 255 (highest volume).
   * @return
   *                  - 0: Success.
   *                  - < 0: Failure.
   */
	int setApplicationVolume(int volume);

   /** @~chinese
   获取 App 的当前音量。

   @param volume 音量值，范围 [0,255]。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief           Retrieves the volume of the application.
   * @param           volume
   *                  Pointer to the application volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).
   * @return
   *                  - 0: Success.
   *                  - < 0: Failure.
   */
	int getApplicationVolume(int& volume);

   /** @~chinese
   设置 App 静音。

   @param mute
   - true: App 设为静音；
   - false: App 设为不静音。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief           Mutes the application.
   * @param           mute
   *                  Sets whether to mute/unmute the application:
   *                  - true: Mute the application.
   *                  - false: Unmute the application.
   * @return
   *                  - 0: Success.
   *                  - < 0: Failure.
   */
	int setApplicationMute(bool mute);

   /** @~chinese
   获取 App 当前的静音状态。

   @param mute
   - true: App 为静音状态；
   - false: App 为非静音状态。

   @return
   - 0: 方法调用成功
   -  < 0: 方法调用失败
   */
   /** @~english
   * @brief           Gets the mute state of the application.
   * @param           mute
   *                  Pointer to whether the application is muted/unmuted.
   *                  - true: The application is muted.
   *                  - false: The application is not muted.
   * @return
   *                  - 0: Success.
   *                  - < 0: Failure.
   */
	int isApplicationMute(bool& mute);

private:
   /** @~chinese
    * 释放 AudioDeviceCollection 对象占用的所有资源。
    */
   /** @~english
   * @brief          Releases all AudioDeviceCollection resources.
   */
	void release();

private:
	agora::rtc::IAudioDeviceCollection* m_audioDeviceCollection = nullptr;
};

/** @~chinese
 * AgoraAudioDeviceManager 类。
 */
/** @~english
 * Wrapper around agora::rtc::IAudioDeviceManager
 */
class AGORAPLUGIN_API AgoraAudioDeviceManager
{
public:
	AgoraAudioDeviceManager() = default;

	AgoraAudioDeviceManager(const AgoraAudioDeviceManager& other) = delete;
	AgoraAudioDeviceManager(AgoraAudioDeviceManager&& other) noexcept = delete;
	AgoraAudioDeviceManager& operator=(const AgoraAudioDeviceManager& other) = delete;
	AgoraAudioDeviceManager& operator=(AgoraAudioDeviceManager&& other) noexcept = delete;

	~AgoraAudioDeviceManager() = default;

   /** @~chinese
   * 创建并获取 AgoraAudioDeviceManager 对象。
   *
   * @param RtcEngine AgoraRtcEngine 对象的指针。
   * @return
   * - 方法调用成功：返回一个 AgoraAudioDeviceManager 对象的指针。
   * - 方法调用失败：返回一个空指针。
   */
   /** @~english
   * @brief          Creates the AudioDeviceManager object
   * @param          RtcEngine
   *                 Pointer to the RtcEngine object.
   * @return
   *                 -  Success: Returns a pointer to the AudioDeviceManager object
   *                 -  Failure: Returns nullptr.
   */
	static AgoraAudioDeviceManager* Create(AgoraRtcEngine* RtcEngine);
public:


   /** @~chinese
   获取系统中所有的播放设备列表。

   该方法返回一个 AudioDeviceCollection 对象，包含系统中所有的播放设备。
   通过 AudioDeviceCollection 对象，App 可以枚举播放设备。在使用结束后，App 需调用 \ref release 方法销毁返回的对象。

   @return
   - 方法调用成功：返回一个 AudioDeviceCollection 对象，其中包含所有的播放设备。
   - 方法调用失败：返回一个空指针。
   */
   /** @~english
   * @brief          Enumerates the audio playback devices.
   * @brief          This method returns a pointer to \ref AudioDeviceCollection object that includes all audio playback devices in the system. 
   *                 With the \ref AudioDeviceCollection object, the application can enumerate the audio playback devices.
   * @note           The application must call the release method to \ref release the returned object after using it.
   * @return
   *                 -  Success: Returns an AudioDeviceCollection object that includes all audio playback devices in the system. 
   *                    For wireless Bluetooth headset devices with master and slave headsets, the master headset is the playback device.
   *                 -  Failure: Returns nullptr.
   */
	AudioDeviceCollection* enumeratePlaybackDevices();

   /** @~chinese
   获取系统中所有的音频采集设备列表。

   该方法返回一个 AudioDeviceCollection 对象，包含系统中所有的音频采集设备。
   通过 AudioDeviceCollection 对象，App 可以枚举音频采集设备。在使用结束后，App 需调用 \ref release 方法销毁返回的对象。

   @return
   - 方法调用成功：返回一个 AudioDeviceCollection 对象，其中包含所有的音频采集设备。
   - 方法调用失败：返回一个空指针。
   */
   /** @~english
   * @brief          Enumerates the audio recording devices.
   * @brief          This method returns a pointer to \ref AudioDeviceCollection object that includes all audio recording devices in the system.
   *                 With the \ref AudioDeviceCollection object, the application can enumerate the audio recording devices.
   * @note           The application needs to call the \ref release method to release the returned object after using it.
   * @return
   *                 -  Success: Returns an AudioDeviceCollection object that includes all audio recording devices in the system.
   *                    For wireless Bluetooth headset devices with master and slave headsets, the master headset is the playback device.
   *                 -  Failure: Returns nullptr.
   */
	AudioDeviceCollection* enumerateRecordingDevices();

   /** @~chinese
   指定播放设备。

   @param deviceId 通过 deviceID 指定播放设备。由 \ref enumeratePlaybackDevices 获取。插拔设备不会影响 deviceId。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the audio playback device using the device ID.
   * @note           Plugging or unplugging the audio device does not change the device ID.
   * @param          deviceId 
   *                 Device ID of the audio playback device, retrieved by calling the \ref enumeratePlaybackDevices method.
   * @return
   *                 -  0: Success. 
   *                 -  < 0: Failure.
   */
	int setPlaybackDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /** @~chinese
   指定音频采集设备。

   @param deviceId 音频采集设备的 Device ID。可通过 \ref enumerateRecordingDevices 获取。插拔设备不会影响 deviceId。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the audio recording device using the device ID.
   * @note           Plugging or unplugging the audio device does not change the device ID.
   * @param          deviceId 
   *                 Device ID of the audio recording device, retrieved by calling the \ref enumerateRecordingDevices method.
   * @return
   *                 -  0: Success. 
   *                 -  < 0: Failure.
   */
	int setRecordingDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /** @~chinese
   启动音频播放设备测试。

   该方法测试音频播放设备是否能正常工作。启动测试后，SDK 播放指定的音频文件，测试者如果能听到声音，说明播放设备能正常工作。

   调用该方法后，SDK 会每隔 100 ms 触发一次 \ref IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" 回调，报告 `uid = 1` 及播放设备的音量信息。

   @note 该方法需在加入频道前调用。

   @param testAudioFilePath 音频文件的绝对路径，路径字符串使用 UTF-8 编码格式。
   - 支持文件格式: wav、mp3、m4a、aac；
   - 支持文件采样率: 8000、16000、32000、44100、48000。

   @return
   - 0: 方法调用成功，你可以听到设置的音频文件的声音。
   - < 0: 方法调用失败。
   */
   /** @~english
   * @brief          Starts the audio playback device test.
   * @brief          This method tests if the playback device works properly. 
   *                 In the test, the SDK plays an audio file specified by the user. If the user can hear the audio, the playback device works properly.
   * @param          testAudioFilePath 
   *                 Pointer to the path of the audio file for the audio playback device test in UTF-8:
   *                 - Supported file formats: wav, mp3, m4a, and aac.
   *                 - Supported file sample rates: 8000, 16000, 32000, 44100, and 48000 Hz.
   * @return
   *                 -  0: Success, and you can hear the sound of the specified audio file.
   *                 -  < 0: Failure.
   */
	int startPlaybackDeviceTest(const char* testAudioFilePath);

   /** @~chinese
   停止播放设备测试。

   在调用 \ref startPlaybackDeviceTest 方法开始播放设备测试后，你需要调用该方法停止测试。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Stops the audio playback device test.
   * @brief          This method stops testing the audio playback device. 
   *                 You must call this method to stop the test after calling the startPlaybackDeviceTest method.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int stopPlaybackDeviceTest();

   /** @~chinese
   设置播放设备音量。

   @param volume 播放设备音量。取值可在 [0,255]。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the volume of the audio playback device.
   * @param          volume
   *                 Sets the volume of the audio playback device. The value ranges between 0 (lowest volume) and 255 (highest volume).
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setPlaybackDeviceVolume(int volume);

   /** @~chinese
   获取播放设备音量。

   @param volume 播放设备音量。取值可在 [0,255]。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Retrieves the volume of the audio playback device.
   * @param          volume
   *                 Pointer to the audio playback device volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getPlaybackDeviceVolume(int* volume);

   /** @~chinese
   设置音频采集设备音量。

   @param volume 音频采集设备音量。取值范围 [0,255]。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets the volume of the microphone.
   * @param          volume
   *                 Sets the volume of the microphone. The value ranges between 0 (lowest volume) and 255 (highest volume).
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setRecordingDeviceVolume(int volume);

   /** @~chinese
   获取音频采集设备音量。

   @param volume 音频采集设备音量。取值范围 [0,255]。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Retrieves the volume of the microphone.
   * @param          volume
   *                 Pointer to the microphone volume. The volume value ranges between 0 (lowest volume) and 255 (highest volume).
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getRecordingDeviceVolume(int* volume);

   /** @~chinese
   静音播放设备。

   @param mute
   - true: 设备设为静音；
   - false: 设备设为不静音。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Mutes the audio playback device.
   * @param          mute
   *                 Sets whether to mute/unmute the audio playback device:
   *                 -  true: Mutes.
   *                 -  false: Unmutes.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setPlaybackDeviceMute(bool mute);

   /** @~chinese
   获取播放设备静音状态。

   @param mute
   - true: 已静音状态；
   - false: 非静音状态。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Retrieves the mute status of the audio playback device.
   * @param          mute
   *                 Pointer to whether the audio playback device is muted/unmuted.
   *                 -  true: Muted.
   *                 -  false: Unmuted.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getPlaybackDeviceMute(bool *mute);

   /** @~chinese
   静音音频采集设备。

   @param mute
   - true: 设备设为静音；
   - false: 设备设为非静音。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Mutes/Unmutes the microphone.
   * @param          mute
   *                 Sets whether to mute/unmute the microphone:
   *                 -  true: Mutes.
   *                 -  false: Unmutes.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setRecordingDeviceMute(bool mute);

   /** @~chinese
   获取音频采集设备静音状态。

   @param mute
   - true: 已静音状态；
   - false: 非静音状态。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Retrieves the microphone's mute status.
   * @param          mute
   *                 Pointer to whether the audio playback device is muted/unmuted.
   *                 -  true: Muted.
   *                 -  false: Unmuted.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getRecordingDeviceMute(bool* mute);

   /** @~chinese
   启动音频采集设备测试。

   该方法测试音频采集设备是否能正常工作。

   调用该方法后，SDK 会按设置的时间间隔
   触发 \ref agora::rtc::IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" 回调，
   报告 `uid = 0` 及采集设备的音量信息。

   @note 该方法需在加入频道前调用。

   @param indicationInterval SDK 返回 \ref agora::rtc::IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" 回调的
   时间间隔，单位为毫秒。建议设置到大于 200 毫秒。不得少于 10 毫秒，否则会收不到 `onAudioVolumeIndication` 回调。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Starts the microphone test.
   * @brief          This method tests whether the microphone works properly.
   *                 Once the test starts, the SDK uses the \ref agora::rtc::IRtcEngineEventHandler::onAudioVolumeIndication callback to notify the application with the volume information.
   * @param          indicationInterval
   *                 Interval period (ms) of the \ref agora::rtc::IRtcEngineEventHandler::onAudioVolumeIndication callback cycle.
   *
   *                 -  true: Muted.
   *                 -  false: Unmuted.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int startRecordingDeviceTest(int indicationInterval);

   /** @~chinese
   停止音频采集设备测试。

   该方法停止音频采集设备测试。调用 \ref startRecordingDeviceTest 后，必须调用该方法停止测试。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Stops the microphone test.
   * @brief          This method stops the microphone test.
   *                 You must call this method to stop the test after calling the \ref startRecordingDeviceTest method.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int stopRecordingDeviceTest();

   /** @~chinese
   获取音频播放设备。

   @param deviceId 音频播放设备的设备 ID。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Retrieves the audio playback device associated with the device ID.
   * @param          deviceId
   *                 Pointer to the ID of the audio playback device.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getPlaybackDevice(char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /** @~chinese
   根据设备 ID 和设备名称获取播放设备。

   @param deviceId 播放设备的设备 ID。
   @param deviceName 播放设备的设备名称。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Retrieves the audio playback device information associated with the device ID and device name.
   * @param          deviceId
   *                 Pointer to the ID of the audio playback device.
   * @param          deviceName
   *                 Pointer to the device name of the audio playback device.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getPlaybackDeviceInfo(
		char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH],
		char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH]);


   /** @~chinese
   根据设备 ID 获取音频采集设备。

   @param deviceId 采集设备的设备 ID。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Retrieves the audio recording device associated with the device ID.
   * @param          deviceId
   *                 Pointer to the device ID of the audio recording device.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getRecordingDevice(char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /** @~chinese
   根据设备名称和设备 ID 获取音频采集设备信息。

   @param deviceId 音频采集设备的设备 ID。
   @param deviceName 音频采集设备的设备名称。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Retrieves the audio recording device information associated with the device ID and device name.
   * @param          deviceId
   *                 Pointer to the device ID of the recording audio device.
   * @param          deviceName
   *                 Pointer to the device name of the recording audio device.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getRecordingDeviceInfo(
		char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH],
		char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH]);

  /** @~chinese
   * 开始音频设备回路测试。
   *
   * 该方法测试音频采集和播放设备是否能正常工作。一旦测试开始，音频采集设备会采集本地音频，然后使用音频播放设备播放出来。
   * SDK 会按设置的时间间隔触发两个 \ref IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" 回调，
   * 分别报告音频采集设备（`uid = 0`）和音频播放设备（`uid = 1`）的音量信息。
   *
   * @note
   * - 该方法需在加入频道前调用。
   * - 该方法仅在本地进行音频设备测试，不涉及网络连接。
   *
   * @param indicationInterval SDK 返回 \ref IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" 回调的时间间隔，
   * 单位为毫秒。建议设置到大于 200 毫秒。不得少于 10 毫秒，否则会收不到 onAudioVolumeIndication 回调。
   *
   * @return
   * - 0: 方法调用成功
   * - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Starts the audio device loopback test.
   * @brief          This method tests whether the local audio devices are working properly. 
   *                 After calling this method, the microphone captures the local audio and plays it through the speaker. 
   *                 The \ref agora::rtc::IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" callback returns the local audio volume information at the set interval.
   * @note           This method tests the local audio devices and does not report the network conditions.
   * @param          indicationInterval
   *                 The time interval (ms) at which the \ref agora::rtc::IRtcEngineEventHandler::onAudioVolumeIndication "onAudioVolumeIndication" callback returns.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int startAudioDeviceLoopbackTest(int indicationInterval);

   /** @~chinese
   停止音频设备回路测试。

   @note 在调用 \ref startAudioDeviceLoopbackTest 后，必须调用该方法停止音频设备回路测试。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Stops the audio device loopback test.
   * @note           Ensure that you call this method to stop the loopback test after calling the \ref startAudioDeviceLoopbackTest method.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int stopAudioDeviceLoopbackTest();

private:
	bool queryInterface(AgoraRtcEngine* engine);

   /** @~chinese
    释放 IAudioDeviceManager 对象占用的所有资源。
    */
   /** @~english
   * @brief Releases all AudioDeviceManager resources.
   */
	void release();

private:
	agora::util::AutoPtr<agora::rtc::IAudioDeviceManager> m_audioDeviceManager;
};

}
}
}
