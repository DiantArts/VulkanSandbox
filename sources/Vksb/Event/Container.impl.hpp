#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Managment
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    ::vksb::constraint::isEvent EventType
> void ::vksb::event::Container::emplace(
    auto&&... args
)
{
    m_events.push(::std::make_unique<EventType>(::std::forward<decltype(args)>(args)...));
}
