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
 * VideoDeviceCollection 类是基于 IVideoDeviceCollection 封装的类。
 */
/** @~english
 * Wrapper around agora::rtc::IVideoDeviceCollection
 */
class AGORAPLUGIN_API VideoDeviceCollection
{
public:
	VideoDeviceCollection() = delete;
	VideoDeviceCollection(agora::rtc::IVideoDeviceCollection* collection);
	VideoDeviceCollection(const VideoDeviceCollection& other);
	VideoDeviceCollection(VideoDeviceCollection&& other) noexcept;
	VideoDeviceCollection& operator=(const VideoDeviceCollection& other);
	VideoDeviceCollection& operator=(VideoDeviceCollection&& other) noexcept;

	~VideoDeviceCollection();

public:
   /** @~chinese
   获取系统中被索引的视频设备的总数。

   @return 系统中被索引的视频设备的总数。
   */
   /** @~english
   * @brief           Retrieves the total number of the indexed video devices in the system.
   * @return          Total number of the indexed video devices
   */
	int getCount();

   /** @~chinese
   获取某个被索引的视频设备的指定信息。

   @param index 设备的索引值。请确保该参数的值小于 \ref IVideoDeviceCollection::getCount "getCount" 的返回值。
   @param deviceName 设备的名称。
   @param deviceId 设备的 ID 。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief           Retrieves a specified piece of information about an indexed video device.
   * @param           index
   *                  The specified index of the video device that must be less than the return value of \ref IVideoDeviceCollection::getCount "getCount".
   * @param           deviceName
   *                  Pointer to the video device name.
   * @param           deviceId
   *                  Pointer to the video device ID.
   * @return
   *                  - 0: Success.
   *                  - < 0: Failure.
   */
	int getDevice(
		int index,
		char deviceName[agora::rtc::MAX_DEVICE_ID_LENGTH],
		char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /** @~chinese
   通过设备 ID 指定设备。

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

private:
   /** @~chinese
   释放 VideoDeviceCollection 对象占用的所有资源。
   */
   /** @~english
   * @brief          Releases all VideoDeviceCollection resources.
   */
	void release();

private:
	agora::rtc::IVideoDeviceCollection* m_videoDeviceCollection = nullptr;
};

/** @~chinese
 AgoraVideoDeviceManager 类是基于 IVideoDeviceManager 封装的类。
 */
/** @~english
 * Wrapper around agora::rtc::IVideoDeviceManager
 */
class AGORAPLUGIN_API AgoraVideoDeviceManager
{
public:
	AgoraVideoDeviceManager() = default;

	AgoraVideoDeviceManager(const AgoraVideoDeviceManager& other) = delete;
	AgoraVideoDeviceManager(AgoraVideoDeviceManager&& other) noexcept = delete;
	AgoraVideoDeviceManager& operator=(const AgoraVideoDeviceManager& other) = delete;
	AgoraVideoDeviceManager& operator=(AgoraVideoDeviceManager&& other) noexcept = delete;

	~AgoraVideoDeviceManager() = default;

	static AgoraVideoDeviceManager* Create(AgoraRtcEngine* RtcEngine);
public:

   /** @~chinese
   获取系统中所有的视频设备。

   该方法返回一个 \ref VideoDeviceCollection 对象，其中包含系统中所有的播放设备。
   通过 \ref VideoDeviceCollection 对象，App 可以枚举视频设备。使用结束后，App 需调用 \ref release 方法销毁返回的对象。

   @return
   - 方法调用成功: 返回一个 IVideoDeviceCollection 对象，其中包含系统中所有的播放设备。
   - 方法调用失败: 返回一个空指针。
   */
   /** @~english
   * @brief          Enumerates the video devices.
   * @brief          This method returns an \ref VideoDeviceCollection object including all video devices in the system.
   *                 With the \ref VideoDeviceCollection object, the application can enumerate the video devices.
   * @note           The application must call the release method to \ref release the returned object after using it.
   * @return
   *                 -  An IVideoDeviceCollection object including all video devices in the system: Success.
   *                 -  nullptr: Failure.
   */
	VideoDeviceCollection* enumerateVideoDevices();

   /** @~chinese
   启动视频采集设备测试。

   该方法测试当前视频采集设备是否工作正常。
   调用该方法前，请确保已经调用 \ref agora::rtc::IRtcEngine::enableVideo "enableVideo" 方法，并确保传入的 hwnd 参数有效。
   @param hwnd 用于显示图像的窗口句柄。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Starts the video-capture device test.
   * @brief          This method tests whether the video-capture device works properly.
   *                 Before calling this method, ensure that you have already called the \ref agora::rtc::IRtcEngine::enableVideo "enableVideo" method, and the window handle (hwnd) parameter is valid.
   * @param          hwnd
   *                 The window handle used to display the screen.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int startDeviceTest(agora::rtc::view_t hwnd);

   /** @~chinese
   停止视频采集设备测试。

   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Stops the video-capture device test.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int stopDeviceTest();

   /** @~chinese
   通过设备 ID 指定视频采集设备。
   @param deviceId 设备 ID，可以通过调用 \ref enumerateVideoDevices 方法获取。
   @note 插拔设备不会改变设备 ID。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Sets a device with the device ID.
   * @param          deviceId
   *                 Pointer to the video-capture device ID. Call the \ref enumerateVideoDevices method to retrieve it.
   * @note           Plugging or unplugging the device does not change the device ID.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int setDevice(const char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

   /** @~chinese
   获取正在使用的视频采集设备。
   @param devideId 设备 ID。
   @return
   - 0: 方法调用成功
   - < 0: 方法调用失败
   */
   /** @~english
   * @brief          Retrieves the video-capture device that is in use.
   * @param          deviceId
   *                 Pointer to the video-capture device ID.
   * @return
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int getDevice(char deviceId[agora::rtc::MAX_DEVICE_ID_LENGTH]);

private:
	bool queryInterface(AgoraRtcEngine* engine);

   /** @~chinese
   释放 VideoDeviceManager 对象占用的所有资源。
   */
   /** @~english
   * @brief          Releases all VideoDeviceManager resources.
   */
	void release();

private:
	agora::util::AutoPtr<agora::rtc::IVideoDeviceManager> m_videoDeviceManager;
};

}
}
}
