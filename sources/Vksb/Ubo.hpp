#pragma once

#include <Vksb/Component/PointLight.hpp>

namespace vksb {

///////////////////////////////////////////////////////////////////////////
/// \brief No clue what it does xD
/// \ingroup vulkan
///
/// \include Ubo.hpp <Ubo.hpp>
///
///////////////////////////////////////////////////////////////////////////
struct Ubo {
    ::glm::mat4 projection{ 1.0f };
    ::glm::mat4 view{ 1.0f };
    ::glm::vec4 ambientLightColor{ 1.0f, 1.0f, 1.0f, 0.02f }; // w is intensity

    static inline constexpr const ::std::size_t maxLights{ 10uz };
    ::vksb::component::PointLight pointLights[maxLights];
    ::std::size_t numOfLights;
};

} // namespace vksb
