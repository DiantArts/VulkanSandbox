#pragma once

#include <Engine/Core/Ecs/AComponent.hpp>
#include <Engine/Core/Ecs/Component/Position.hpp>



namespace engine::graphic::opengl::ecs::component {



class Transformable
    : public ::engine::core::ecs::AComponent<engine::graphic::opengl::ecs::component::Transformable>
{

public:

    // ------------------------------------------------------------------ *structors

    Transformable();

    Transformable(
        const ::glm::vec3& position
    );

    Transformable(
        ::glm::vec3&& position
    );

    ~Transformable();



    // ------------------------------------------------------------------ Copy sementic

    Transformable(
        const Transformable&
    ) noexcept = delete;

    auto operator=(
        const Transformable&
    ) noexcept
        -> Transformable& = delete;



    // ------------------------------------------------------------------ Move sementic

    Transformable(
        Transformable&&
    ) noexcept;

    auto operator=(
        Transformable&&
    ) noexcept
        -> Transformable&;



    // ------------------------------------------------------------------ Model

    void generateModel();

    [[ nodiscard ]] auto getModel() const
        -> const ::glm::mat4&;



    // ------------------------------------------------------------------ Position

    void moveForward(
        float velocity
    );

    void moveBackward(
        float velocity
    );

    void moveRight(
        float velocity
    );

    void moveLeft(
        float velocity
    );

    void moveUp(
        float velocity
    );

    void moveDown(
        float velocity
    );



    void move(
        const ::glm::vec3& offset
    );

    void move(
        float offsetX,
        float offsetY,
        float offsetZ
    );

    void moveX(
        float offset
    );

    void moveY(
        float offset
    );

    void moveZ(
        float offset
    );



    void setPosition(
        const ::glm::vec3& position
    );

    void setPosition(
        ::glm::vec3&& position
    );

    void setPosition(
        float positionX,
        float positionY,
        float positionZ
    );

    void setPositionX(
        float position
    );

    void setPositionY(
        float position
    );

    void setPositionZ(
        float position
    );



    void updatePosition(
        float velocity
    );



    [[ nodiscard ]] auto getPosition() const
        -> const ::glm::vec3&;



    // ------------------------------------------------------------------ Scale

    void scale(
        float scale
    );

    void scale(
        const ::glm::vec3& scale
    );

    void scale(
        float scaleX,
        float scaleY,
        float scaleZ
    );

    void scaleX(
        float scale
    );

    void scaleY(
        float scale
    );

    void scaleZ(
        float scale
    );



    void setScale(
        float scale
    );

    void setScale(
        const ::glm::vec3& scale
    );

    void setScale(
        ::glm::vec3&& scale
    );

    void setScale(
        float scaleX,
        float scaleY,
        float scaleZ
    );

    void setScaleX(
        float scale
    );

    void setScaleY(
        float scale
    );

    void setScaleZ(
        float scale
    );



    [[ nodiscard ]] auto getScale() const
        -> const ::glm::vec3&;



    // ------------------------------------------------------------------ Rotation

    void rotate(
        const ::glm::vec2& offset
    );

    void rotate(
        float yawOffset,
        float pitchOffset
    );

    void rotateYaw(
        float offset
    );

    void rotatePitch(
        float offset
    );



    void setRotation(
        const ::glm::vec2& rotation
    );

    void setRotation(
        ::glm::vec2&& rotation
    );

    void setRotation(
        float yaw,
        float pitch
    );

    void setYaw(
        float yaw
    );

    void setPitch(
        float pitch
    );



    [[ nodiscard ]] auto getRotation() const
        -> const ::glm::vec2&;

    [[ nodiscard ]] auto getDirection() const
        -> const ::glm::vec3&;



    // ------------------------------------------------------------------ View

    auto getView() const
        -> ::glm::mat4;



private:

    void adjustDirection();




private:

    ::glm::mat4 m_model;

    ::glm::vec3 m_position;

    ::glm::vec3 m_scale{ 1.0F, 1.0F, 1.0F };

    ::glm::vec2 m_rotation{ -90.00f, 0.0F }; // .x = yaw, .y = pitch
    ::glm::vec3 m_direction;
    static inline constexpr float minPitch{ -89.999f };
    static inline constexpr float maxPitch{ 89.999f };
    static inline constexpr ::glm::vec3 m_up{ 0.0f, 1.0f, 0.0f };

};



} // namespace engine::graphic::opengl::ecs::component
