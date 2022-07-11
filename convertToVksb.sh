#!/bin/bash

moveFiles() {
    mv sources/first_app.cpp sources/App.cpp
    mv sources/first_app.hpp sources/App.hpp

    mv sources/lve_device.cpp sources/Device.cpp
    mv sources/lve_device.hpp sources/Device.hpp

    mv sources/lve_model.cpp sources/Model.cpp
    mv sources/lve_model.hpp sources/Model.hpp

    mv sources/lve_pipeline.cpp sources/Pipeline.cpp
    mv sources/lve_pipeline.hpp sources/Pipeline.hpp

    mv sources/lve_swap_chain.cpp sources/SwapChain.cpp
    mv sources/lve_swap_chain.hpp sources/SwapChain.hpp

    mv sources/lve_window.cpp sources/Window.cpp
    mv sources/lve_window.hpp sources/Window.hpp

    mv sources/lve_renderer.cpp sources/Renderer.cpp
    mv sources/lve_renderer.hpp sources/Renderer.hpp

    mkdir -p sources/System
    mv sources/simple_render_system.cpp sources/System/Render.cpp
    mv sources/simple_render_system.hpp sources/System/Render.hpp

    mv sources/lve_game_object.cpp sources/GameObject.cpp
    mv sources/lve_game_object.hpp sources/GameObject.hpp
}

replaceInclude() {
    sed -i "s/\"first_app.hpp\"/<App.hpp>/g" sources/**.cpp sources/**.hpp
    sed -i "s/\"lve_device.hpp\"/<Device.hpp>/g" sources/**.cpp sources/**.hpp
    sed -i "s/\"lve_model.hpp\"/<Model.hpp>/g" sources/**.cpp sources/**.hpp
    sed -i "s/\"lve_pipeline.hpp\"/<Pipeline.hpp>/g" sources/**.cpp sources/**.hpp
    sed -i "s/\"lve_swap_chain.hpp\"/<SwapChain.hpp>/g" sources/**.cpp sources/**.hpp
    sed -i "s/\"lve_window.hpp\"/<Window.hpp>/g" sources/**.cpp sources/**.hpp
    sed -i "s/\"lve_renderer.hpp\"/<Renderer.hpp>/g" sources/**.cpp sources/**.hpp
    sed -i "s/\"simple_render_system.hpp\"/<System\/Render.hpp>/g" sources/**.cpp sources/**.hpp
    sed -i "s/\"lwe_game_object.hpp\"/<GameObject.hpp>/g" sources/**.cpp sources/**.hpp
}

replaceNamespace() {
    sed -i "s/namespace lve/namespace vksb/g" sources/**.cpp sources/**.hpp
    sed -i "s/lve::/vksb::/g" sources/**.cpp sources/**.hpp
}

replaceClassName() {
    sed -i "s/PipelineApp/App/g" sources/**.cpp sources/**.hpp
    sed -i "s/First/Pipeline/g" sources/**.cpp sources/**.hpp
    sed -i "s/LveDevice/Device/g" sources/**.cpp sources/**.hpp
    sed -i "s/LveModel/Model/g" sources/**.cpp sources/**.hpp
    sed -i "s/LvePipeline/Pipeline/g" sources/**.cpp sources/**.hpp
    sed -i "s/LveSwapChain/SwapChain/g" sources/**.cpp sources/**.hpp
    sed -i "s/LveWindow/Window/g" sources/**.cpp sources/**.hpp
    sed -i "s/LveRenderer/Renderer/g" sources/**.cpp sources/**.hpp
    # sed -i "s/SimpleRenderSystem/system::Render/g" sources/**.cpp sources/**.hpp
    sed -i "s/LveGameObject/GameObject/g" sources/**.cpp sources/**.hpp
}

replaceShaderPath() {
    sed -i "s/shaders\/simple_shader.vert.spv/Shaders\/Vertex\/simple.glsl/g" sources/App.cpp
    sed -i "s/shaders\/simple_shader.frag.spv/Shaders\/Fragment\/simple.glsl/g" sources/App.cpp
}

changeFileContent() {
    sed -i "s/Vulkan Tutorial/GlfwMainWindow/g" sources/**.cpp sources/**.hpp
    sed -i "1s/^/#include <pch.hpp>\n/g" sources/**.cpp
    sed -i "s/lveDevice/m_device/g" sources/**.cpp sources/**.hpp
    sed -i "s/lveWindow/m_window/g" sources/**.cpp sources/**.hpp
    sed -i "s/lveSwapChain/m_pSwapChain/g" sources/**.cpp sources/**.hpp
    sed -i "s/lvePipeline/m_pPipeline/g" sources/**.cpp sources/**.hpp
    sed -i "s/lveModel/m_pModel/g" sources/**.cpp sources/**.hpp
    sed -i "s/m_window.getExtent/m_window.getSize/g" sources/**.cpp sources/**.hpp
}

moveFiles
replaceInclude
replaceNamespace
replaceClassName
replaceShaderPath
changeFileContent
