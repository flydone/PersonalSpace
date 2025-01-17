/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_DVR_VIMS_DVR_System_Config_STUB_DEFAULT_HPP_
#define V1_GREATWALL_DVR_VIMS_DVR_System_Config_STUB_DEFAULT_HPP_


#include <CommonAPI/Export.hpp>

#include <v1/GREATWALL/DVR_VIMS/DVRSystemConfigStub.hpp>
#include <sstream>

# if defined(_MSC_VER)
#  if _MSC_VER >= 1300
/*
 * Diamond inheritance is used for the CommonAPI::Proxy base class.
 * The Microsoft compiler put warning (C4250) using a desired c++ feature: "Delegating to a sister class"
 * A powerful technique that arises from using virtual inheritance is to delegate a method from a class in another class
 * by using a common abstract base class. This is also called cross delegation.
 */
#    pragma warning( disable : 4250 )
#  endif
# endif

namespace v1 {
namespace GREATWALL {
namespace DVR_VIMS {

/**
 * Provides a default implementation for DVRSystemConfigStubRemoteEvent and
 * DVRSystemConfigStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 *
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class COMMONAPI_EXPORT_CLASS_EXPLICIT DVRSystemConfigStubDefault
    : public virtual DVRSystemConfigStub {
public:
    COMMONAPI_EXPORT DVRSystemConfigStubDefault();

    COMMONAPI_EXPORT DVRSystemConfigStubRemoteEvent* initStubAdapter(const std::shared_ptr< DVRSystemConfigStubAdapter> &_adapter);

    COMMONAPI_EXPORT const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client);


    COMMONAPI_EXPORT virtual void ResetDefaultConfig(const std::shared_ptr<CommonAPI::ClientId> _client, DVRSystemConfig::ResetConfigType _ResetConfigType, ResetDefaultConfigReply_t _reply);
    COMMONAPI_EXPORT virtual void DVRGetConfig(const std::shared_ptr<CommonAPI::ClientId> _client, DVRSystemConfig::GetAllConfig _GetAllConfig, DVRSystemConfig::ConfigTypeList _ConfigTypeList, DVRGetConfigReply_t _reply);
    COMMONAPI_EXPORT virtual void DVRSetConfig(const std::shared_ptr<CommonAPI::ClientId> _client, DVRSystemConfig::ConfigListArray _ConfigListArray, DVRSetConfigReply_t _reply);


    
protected:
    class COMMONAPI_EXPORT_CLASS_EXPLICIT RemoteEventHandler: public virtual DVRSystemConfigStubRemoteEvent {
    public:
        COMMONAPI_EXPORT RemoteEventHandler(DVRSystemConfigStubDefault *_defaultStub);


    private:
        DVRSystemConfigStubDefault *defaultStub_;
    };
protected:
    DVRSystemConfigStubDefault::RemoteEventHandler remoteEventHandler_;

private:


    CommonAPI::Version interfaceVersion_;
};

} // namespace DVR_VIMS
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_DVR_VIMS_DVR_System_Config_STUB_DEFAULT
