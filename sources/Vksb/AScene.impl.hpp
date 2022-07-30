#pragma once

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
template <
    typename ComponentType
> [[ nodiscard ]] auto ::vksb::AScene::getPlayerComponent()
    -> ComponentType&
{
    XRN_SASSERT(
        m_registry.all_of<ComponentType>(m_player),
        "the controlled index is greater than the number of game ojects"
    );

    return m_registry.get<ComponentType>(m_player);
}
