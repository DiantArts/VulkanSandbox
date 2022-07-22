#pragma once

#include <Event/AEvent.hpp>

namespace vksb::event {

///////////////////////////////////////////////////////////////////////////
/// \brief No clue what it does xD
/// \ingroup vulkan
///
/// \include KeyReleased.hpp <KeyReleased.hpp>
///
///////////////////////////////////////////////////////////////////////////
class KeyReleased
    : public ::vksb::AEvent
{

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit KeyReleased(
        ::std::int16_t keyCode
    );




    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Resolve
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Resolve the event
    ///
    ///////////////////////////////////////////////////////////////////////////
    virtual void resolve(
        ::vksb::AScene& app
    ) override;



private:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Member variables
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ::std::int16_t m_keyCode;

};

} // namespace vksb::event
