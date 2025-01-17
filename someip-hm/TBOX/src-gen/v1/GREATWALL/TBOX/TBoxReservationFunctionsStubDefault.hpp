/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.12.v202002200719.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_GREATWALL_TBOX_T_Box_Reservation_Functions_STUB_DEFAULT_HPP_
#define V1_GREATWALL_TBOX_T_Box_Reservation_Functions_STUB_DEFAULT_HPP_


#include <CommonAPI/Export.hpp>

#include <v1/GREATWALL/TBOX/TBoxReservationFunctionsStub.hpp>
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
namespace TBOX {

/**
 * Provides a default implementation for TBoxReservationFunctionsStubRemoteEvent and
 * TBoxReservationFunctionsStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 *
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class COMMONAPI_EXPORT_CLASS_EXPLICIT TBoxReservationFunctionsStubDefault
    : public virtual TBoxReservationFunctionsStub {
public:
    COMMONAPI_EXPORT TBoxReservationFunctionsStubDefault();

    COMMONAPI_EXPORT TBoxReservationFunctionsStubRemoteEvent* initStubAdapter(const std::shared_ptr< TBoxReservationFunctionsStubAdapter> &_adapter);

    COMMONAPI_EXPORT const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client);

    COMMONAPI_EXPORT virtual const ::v1::GREATWALL::TBOX::TBoxReservationFunctions::LocalFOTAResParStruct& getLocalFOTAResParAttribute();
    COMMONAPI_EXPORT virtual const ::v1::GREATWALL::TBOX::TBoxReservationFunctions::LocalFOTAResParStruct& getLocalFOTAResParAttribute(const std::shared_ptr<CommonAPI::ClientId> _client);
    COMMONAPI_EXPORT virtual void setLocalFOTAResParAttribute(::v1::GREATWALL::TBOX::TBoxReservationFunctions::LocalFOTAResParStruct _value);
    COMMONAPI_EXPORT virtual const ::v1::GREATWALL::TBOX::TBoxReservationFunctions::LocalChargeResParStruct& getLocalChargeResParAttribute();
    COMMONAPI_EXPORT virtual const ::v1::GREATWALL::TBOX::TBoxReservationFunctions::LocalChargeResParStruct& getLocalChargeResParAttribute(const std::shared_ptr<CommonAPI::ClientId> _client);
    COMMONAPI_EXPORT virtual void setLocalChargeResParAttribute(::v1::GREATWALL::TBOX::TBoxReservationFunctions::LocalChargeResParStruct _value);

    COMMONAPI_EXPORT virtual void RemoteFOTAReservation(const std::shared_ptr<CommonAPI::ClientId> _client, TBoxReservationFunctions::ReservationACK _ReservationACK);
    COMMONAPI_EXPORT virtual void LocalChargeReservation(const std::shared_ptr<CommonAPI::ClientId> _client, TBoxReservationFunctions::ChargMode _ChargMode, TBoxReservationFunctions::TimeArray _StartTime, TBoxReservationFunctions::Repeat _Repeat, TBoxReservationFunctions::TimeArray _EndTime, LocalChargeReservationReply_t _reply);
    COMMONAPI_EXPORT virtual void LocalFOTAReservation(const std::shared_ptr<CommonAPI::ClientId> _client, TBoxReservationFunctions::ReservationOperation _ReservationOperation, TBoxReservationFunctions::TimeArray _UpdateTime, LocalFOTAReservationReply_t _reply);
    COMMONAPI_EXPORT virtual void RemoteChargeReservation(const std::shared_ptr<CommonAPI::ClientId> _client, TBoxReservationFunctions::ReservationACK _ReservationACK);

    COMMONAPI_EXPORT virtual void fireRemoteFOTAReservationEvent(const ::v1::GREATWALL::TBOX::TBoxReservationFunctions::ReservationOperation &_ReservationOperation, const ::v1::GREATWALL::TBOX::TBoxReservationFunctions::TimeArray &_UpdateTime);
    COMMONAPI_EXPORT virtual void fireRemoteChargeReservationEvent(const ::v1::GREATWALL::TBOX::TBoxReservationFunctions::ChargMode &_ChargMode, const ::v1::GREATWALL::TBOX::TBoxReservationFunctions::TimeArray &_StartTime, const ::v1::GREATWALL::TBOX::TBoxReservationFunctions::Repeat &_Repeat, const ::v1::GREATWALL::TBOX::TBoxReservationFunctions::TimeArray &_EndTime);

    
protected:
    COMMONAPI_EXPORT virtual bool trySetLocalFOTAResParAttribute(::v1::GREATWALL::TBOX::TBoxReservationFunctions::LocalFOTAResParStruct _value);
    COMMONAPI_EXPORT virtual bool validateLocalFOTAResParAttributeRequestedValue(const ::v1::GREATWALL::TBOX::TBoxReservationFunctions::LocalFOTAResParStruct &_value);
    COMMONAPI_EXPORT virtual bool trySetLocalChargeResParAttribute(::v1::GREATWALL::TBOX::TBoxReservationFunctions::LocalChargeResParStruct _value);
    COMMONAPI_EXPORT virtual bool validateLocalChargeResParAttributeRequestedValue(const ::v1::GREATWALL::TBOX::TBoxReservationFunctions::LocalChargeResParStruct &_value);
    class COMMONAPI_EXPORT_CLASS_EXPLICIT RemoteEventHandler: public virtual TBoxReservationFunctionsStubRemoteEvent {
    public:
        COMMONAPI_EXPORT RemoteEventHandler(TBoxReservationFunctionsStubDefault *_defaultStub);




    private:
        TBoxReservationFunctionsStubDefault *defaultStub_;
    };
protected:
    TBoxReservationFunctionsStubDefault::RemoteEventHandler remoteEventHandler_;

private:

    ::v1::GREATWALL::TBOX::TBoxReservationFunctions::LocalFOTAResParStruct localFOTAResParAttributeValue_ {};
    ::v1::GREATWALL::TBOX::TBoxReservationFunctions::LocalChargeResParStruct localChargeResParAttributeValue_ {};

    CommonAPI::Version interfaceVersion_;
};

} // namespace TBOX
} // namespace GREATWALL
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_GREATWALL_TBOX_T_Box_Reservation_Functions_STUB_DEFAULT
