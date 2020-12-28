//  Copyright (c) 2019 Agora.io. All rights reserved.

#pragma once

#if PLATFORM_WINDOWS

#include "CoreMinimal.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif

#if (defined(__APPLE__) && TARGET_OS_IPHONE)
#include <Agora/iOS/Include/IAgoraService.h>
#else
#include <Agora/IAgoraService.h>
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

/** @~chinese
 * AgoraService 类。
 */
/** @~english
 * Wrapper around agora::base::IAgoraService.
 */
class AGORAPLUGIN_API AgoraService
{
public:
	AgoraService() = delete;
	AgoraService(const AgoraService& other);
	AgoraService(AgoraService&& other) noexcept;
	AgoraService& operator=(const AgoraService& other);
	AgoraService& operator=(AgoraService&& other) noexcept;
	~AgoraService();

public:

  /** @~chinese
   * 创建 AgoraService 对象。
   * @return
   * - 方法调用成功：返回 AgoraService 对象的指针。
   * - 方法调用失败：返回一个空指针。
   */
   /** @~english
   * @brief          Creates the AgoraService object.
   * @return
   *                 -  Success: Returns a pointer to the AgoraService object.
   *                 -  Failure: Returns a null pointer.
   */
	static AgoraService* createAgoraService();

	//TODO: duplicate getVersion?
	//const char* getAgoraSdkVersion(int* build);

   /** @~chinese
   * 获取警告信息或错误信息描述。
   * @param err 错误码。
   * @return SDK 错误信息。
   */
   /** @~english
   * @brief          Retrieves the warning or error description.
   * @param          err
   *                 The error code.
   * @return         The detailed error description.
   */
	static const char* getAgoraSdkErrorDescription(int err);

   /**
   * @brief          Sets function, which loads external symbol.
   * @param          func (symname)
   *                 Function(Symbol name)
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	static int setAgoraSdkExternalSymbolLoader(void* (*func)(const char* symname));

   /** @~chinese
   * 初始化 Agora SDK 服务。
   *
   * 请确保在调用任何其他 API 之前先调用 \ref createAgoraRtcEngine 和 \ref initialize。
   * @param context AgoraServiceContext 的引用。
   * @return
   * - 0: 方法调用成功
   * - < 0: 方法调用失败
   */
   /**
   * @brief          Initializes the Agora SDK service.
   * @brief          Ensure that you call the createAgoraRtcEngine and initialize methods before calling any other API.
   * @param          context
   *                 A const reference to AgoraServiceContext
   * @return         
   *                 -  0: Success.
   *                 -  < 0: Failure.
   */
	int initialize(const agora::base::AgoraServiceContext& context);

   /** @~chinese
   * 获取 SDK 版本号。
   * @param build SDK 版本号。
   * @return SDK 的版本号，数据类型为 String。如：2.3.1。
   */
   /** @~english
   * @brief          Retrieves the SDK version number.
   * @param          build
   *                 Pointer to the build number.
   * @return         The version of the current SDK in the string format. For example, 2.3.1.
   */
	const char* getVersion(int* build);

	//TODO: where is IRtmService?
	//virtual rtm::IRtmService* createRtmService() = 0;

private:
   /** @~chinese
    * 释放所有 AgoraService 资源。
    */
   /** @~english
   * @brief Releases all AgoraService resources.
   */
	void release();

private:
	AgoraService(agora::base::IAgoraService* agoraService);

private:
	agora::base::IAgoraService* m_agoraService;
};

}
}
}
#endif
