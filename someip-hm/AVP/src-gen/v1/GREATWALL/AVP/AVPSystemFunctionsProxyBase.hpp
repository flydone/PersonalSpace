/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_AVP_AVP_System_Functions_PROXY_BASE_HPP_
#define V1_GREATWALL_AVP_AVP_System_Functions_PROXY_BASE_HPP_

#include <v1/GREATWALL/AVP/AVPSystemFunctions.hpp>



#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <cstdint>
#include <string>
#include <vector>

#include <CommonAPI/Event.hpp>
#include <CommonAPI/Proxy.hpp>
#include <functional>
#include <future>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace GREATWALL {
namespace AVP {

class AVPSystemFunctionsProxyBase
    : virtual public CommonAPI::Proxy {
public:
    typedef CommonAPI::Event<
        ::v1::GREATWALL::AVP::AVPSystemFunctions::ParkingListResponseNACK
    > ParkingListResponseNACKEvent;
    typedef CommonAPI::Event<
        ::v1::GREATWALL::AVP::AVPSystemFunctions::ParkingListStructArray
    > ParkingListResponseACKEvent;

    typedef std::function<void(const CommonAPI::CallStatus&, const AVPSystemFunctions::PathInfoStructArray&)> PathInfoRequestAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const AVPSystemFunctions::PathInfoStructArray&)> PathInfoRenameAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const AVPSystemFunctions::PathInfoStructArray&)> PathInfoOperationAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const AVPSystemFunctions::GeoFenceResponse&)> GeoFenceRequestAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const AVPSystemFunctions::PathInfoStructArray&)> PathInfoAddAsyncCallback;


    virtual ParkingListResponseNACKEvent& getParkingListResponseNACKEvent() = 0;
    virtual ParkingListResponseACKEvent& getParkingListResponseACKEvent() = 0;

    /**
     * @invariant Fire And Forget
     */
    virtual void ParkingListRequest(const AVPSystemFunctions::HUTRequest &_ParkingListRequest, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void PAVPFunction(const AVPSystemFunctions::HUTRequest &_PAVPFunctionOpen, CommonAPI::CallStatus &_internalCallStatus) = 0;
    virtual void PathInfoRequest(const AVPSystemFunctions::HUTRequest &_PathInfoRequest, CommonAPI::CallStatus &_internalCallStatus, AVPSystemFunctions::PathInfoStructArray &_PathInfoStructArray, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> PathInfoRequestAsync(const AVPSystemFunctions::HUTRequest &_PathInfoRequest, PathInfoRequestAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * @invariant Fire And Forget
     */
    virtual void PathInfoSelect(const AVPSystemFunctions::PathNum &_PathNum, CommonAPI::CallStatus &_internalCallStatus) = 0;
    virtual void PathInfoRename(const AVPSystemFunctions::PathNum &_PathNum, const AVPSystemFunctions::PathName &_PathName, CommonAPI::CallStatus &_internalCallStatus, AVPSystemFunctions::PathInfoStructArray &_PathInfoStructArray, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> PathInfoRenameAsync(const AVPSystemFunctions::PathNum &_PathNum, const AVPSystemFunctions::PathName &_PathName, PathInfoRenameAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void PathInfoOperation(const AVPSystemFunctions::PathInfoOperation &_PathInfoOperation, const AVPSystemFunctions::PathNum &_PathNum, CommonAPI::CallStatus &_internalCallStatus, AVPSystemFunctions::PathInfoStructArray &_PathInfoStructArray, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> PathInfoOperationAsync(const AVPSystemFunctions::PathInfoOperation &_PathInfoOperation, const AVPSystemFunctions::PathNum &_PathNum, PathInfoOperationAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void GeoFenceRequest(const AVPSystemFunctions::HUTRequest &_GeoFenceRequest, CommonAPI::CallStatus &_internalCallStatus, AVPSystemFunctions::GeoFenceResponse &_GeoFenceResponse, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> GeoFenceRequestAsync(const AVPSystemFunctions::HUTRequest &_GeoFenceRequest, GeoFenceRequestAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void PathInfoAdd(const AVPSystemFunctions::PathType &_PathType, const AVPSystemFunctions::PathLotType &_PathLotType, const AVPSystemFunctions::PathNum &_PathNum, const AVPSystemFunctions::PathName &_PathName, CommonAPI::CallStatus &_internalCallStatus, AVPSystemFunctions::PathInfoStructArray &_PathInfoStructArray, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> PathInfoAddAsync(const AVPSystemFunctions::PathType &_PathType, const AVPSystemFunctions::PathLotType &_PathLotType, const AVPSystemFunctions::PathNum &_PathNum, const AVPSystemFunctions::PathName &_PathName, PathInfoAddAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
};

} // namespace AVP
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_AVP_AVP_System_Functions_PROXY_BASE_HPP_
