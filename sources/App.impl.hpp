#pragma once

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> [[ nodiscard ]] auto ::vksb::App::getPlayerComponent()
    -> ComponentType&
{
    assert(
        m_gameObjects.size() > m_playerIndex &&
        "the controlled index is greater than the number of game ojects"
    );
    return m_components.get<ComponentType>(m_playerIndex);
}
