
///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Event/Container.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::event::Container::Container() = default;



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rule of 5
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::event::Container::~Container() = default;

///////////////////////////////////////////////////////////////////////////
::vksb::event::Container::Container(
    ::vksb::event::Container&&
) noexcept = default;

///////////////////////////////////////////////////////////////////////////
auto ::vksb::event::Container::operator=(
    ::vksb::event::Container&&
) noexcept
    -> ::vksb::event::Container& = default;




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Managment
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::event::Container::resolve(
    ::vksb::AScene& app
)
{
    while (!m_events.empty()) {
        m_events.front()->resolve(app);
        m_events.pop();
    }
}
