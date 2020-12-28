//  Agora SDK
//
//  Copyright (c) 2019 Agora.io. All rights reserved.
//

#ifndef AGORA_SERVICE_H
#define AGORA_SERVICE_H
#include "AgoraBase.h"

namespace agora {
    namespace rtc {
        class IRtcEngine;
    }
    namespace rtm {
        class IRtmService;
    }
namespace base {

struct AgoraServiceContext
{
};


class IAgoraService
{
protected:
    virtual ~IAgoraService(){}

public:
    AGORA_CPP_API static void release ();

    /** @~chinese
     * 初始化 RtcEngine。
     * @param context AgoraServiceContext 的指针。
     * @return
     * - 0: 方法调用成功
     * - < 0: 方法调用失败
     */
	/** @~english
    Initializes the engine.

    @param context RtcEngine context.
    @return
     - 0: Success.
     - < 0: Failure.
    */
    virtual int initialize(const AgoraServiceContext& context) = 0;

    /** Retrieves the SDK version number.
    * @param build Build number.
    * @return The current SDK version in the string format. For example, 2.4.0
    */
    virtual const char* getVersion(int* build) = 0;

    virtual rtm::IRtmService* createRtmService() = 0;
};

} //namespace base
} // namespace agora

/** Gets the SDK version number.

 @param build Build number of the Agora SDK.
 @return
 - 0: Success.
 - < 0: Failure.
*/
AGORA_API const char* AGORA_CALL getAgoraSdkVersion(int* build);

/**
* Creates the RtcEngine object and returns the pointer.
* @param err Error code
* @return returns Description of the error code
*/
AGORA_API const char* AGORA_CALL getAgoraSdkErrorDescription(int err);

/** @~chinese
 * 创建 IAgoraService 对象，并返回指针。
 * @return
 * - 方法调用成功：返回 IAgoraService 的指针。
 * - 方法调用失败：返回一个空指针。
/**
* Creates the Agora Service object and returns the pointer.
* @return returns Pointer of the Agora Service object
*/
AGORA_API agora::base::IAgoraService* AGORA_CALL createAgoraService();

AGORA_API int AGORA_CALL setAgoraSdkExternalSymbolLoader(void* (*func)(const char* symname));

#endif
