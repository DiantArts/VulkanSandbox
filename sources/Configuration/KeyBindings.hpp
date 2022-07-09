#pragma once

namespace vksb::detail::configuration {

///////////////////////////////////////////////////////////////////////////
/// \brief No clue what it does xD
/// \ingroup vulkan
///
/// \include KeyBindings.hpp <KeyBindings.hpp>
///
///////////////////////////////////////////////////////////////////////////
struct KeyBindings
{
    // move
    ::std::int16_t moveForward = GLFW_KEY_W;
    ::std::int16_t moveBackward = GLFW_KEY_S;
    ::std::int16_t moveLeft = GLFW_KEY_A;
    ::std::int16_t moveRight = GLFW_KEY_D;
    ::std::int16_t moveUp = GLFW_KEY_SPACE;
    ::std::int16_t moveDown = GLFW_KEY_X;

    // move arrows
    ::std::int16_t moveForward2 = GLFW_KEY_UP;
    ::std::int16_t moveBackward2 = GLFW_KEY_DOWN;
    ::std::int16_t moveLeft2 = GLFW_KEY_LEFT;
    ::std::int16_t moveRight2 = GLFW_KEY_RIGHT;

    // look
    ::std::int16_t lookUp = GLFW_KEY_Z;
    ::std::int16_t lookDown = GLFW_KEY_C;
    ::std::int16_t lookLeft = GLFW_KEY_Q;
    ::std::int16_t lookRight = GLFW_KEY_E;
};

} // namespace vksb::detail::configuration
