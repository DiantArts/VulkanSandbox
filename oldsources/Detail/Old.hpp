///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>



namespace {

///////////////////////////////////////////////////////////////////////////
// Memory manager
///////////////////////////////////////////////////////////////////////////
class VulkanMemoryManager {

private:

    VulkanMemoryManager(
        const ::std::string& appName
    )
    {
        // init GLFW
        if (!::glfwInit()) {
            throw::std::runtime_error("glwfInit() function failed");
        }
        ::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        ::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        createInstance();
        setupDebugMessenger();
        return;

        // creates an instance
        ::VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = appName.c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        ::std::uint32_t glfwExtensionCount{ 0 };
        ::VkInstanceCreateInfo instanceCreateInfo{};
        instanceCreateInfo.pApplicationInfo = &appInfo;
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

#ifdef XRN_USE_VALIDATION_LAYERS
        // config log callback
        VkDebugUtilsMessengerCreateInfoEXT createDebugCallbackInfo{};
        createDebugCallbackInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createDebugCallbackInfo.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createDebugCallbackInfo.messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createDebugCallbackInfo.pfnUserCallback = debugCallback;
        createDebugCallbackInfo.pUserData = nullptr;

        // debug extenstions
        const char** glfwExtensions{ ::glfwGetRequiredInstanceExtensions(&glfwExtensionCount) };
        ::std::vector<const char*> extensions{ glfwExtensions, glfwExtensions + glfwExtensionCount };
        extensions.push_back("VK_EXT_debug_utils");
        instanceCreateInfo.enabledExtensionCount = static_cast<::std::uint32_t>(extensions.size());
        instanceCreateInfo.ppEnabledExtensionNames = extensions.data();
        instanceCreateInfo.pNext = reinterpret_cast<VkDebugUtilsMessengerCreateInfoEXT*>(&createDebugCallbackInfo);
        auto* func{ reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT")
        ) };
        if (
            func == nullptr ||
            func(m_instance, &createDebugCallbackInfo, nullptr, &m_debugMessenger) != VK_SUCCESS
        ) {
            throw std::runtime_error("failed to set up debug messenger");
        }
#else // XRN_USE_VALIDATION_LAYERS
        instanceCreateInfo.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        instanceCreateInfo.enabledExtensionCount = glfwExtensionCount;
        instanceCreateInfo.pNext = nullptr;
#endif // XRN_USE_VALIDATION_LAYERS

        if (auto retval{ ::vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance) }; retval != VK_SUCCESS) {
            if (retval == VK_ERROR_EXTENSION_NOT_PRESENT) {
                uint32_t extensionCount = 0;
                ::vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
                ::std::vector<::VkExtensionProperties> extensions(extensionCount);
                ::vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
                ::xrn::Logger::openError() << "available extensions:\n";
                for (const auto& extension : extensions) {
                    ::xrn::Logger::openBlank() << '\t' << extension.extensionName << '\n';
                }
            }
            throw ::std::runtime_error("failed to create instance");
        }
    }

    void createInstance()
    {
#ifdef XRN_USE_VALIDATION_LAYERS
        if (!checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }
#endif // XRN_USE_VALIDATION_LAYERS

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "LittleVulkanEngine App";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
#ifdef XRN_USE_VALIDATION_LAYERS
        createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
        createInfo.ppEnabledLayerNames = m_validationLayers.data();
        populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo;
#else // XRN_USE_VALIDATION_LAYERS
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
#endif // XRN_USE_VALIDATION_LAYERS

        if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }

        hasGflwRequiredInstanceExtensions();
    }

    std::vector<const char *> getRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef XRN_USE_VALIDATION_LAYERS
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif // XRN_USE_VALIDATION_LAYERS

        return extensions;
    }

    void hasGflwRequiredInstanceExtensions() {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "available extensions:" << std::endl;
        std::unordered_set<std::string> available;
        for (const auto &extension : extensions) {
            std::cout << "\t" << extension.extensionName << std::endl;
            available.insert(extension.extensionName);
        }

        std::cout << "required extensions:" << std::endl;
        auto requiredExtensions = getRequiredExtensions();
        for (const auto &required : requiredExtensions) {
            std::cout << "\t" << required << std::endl;
            if (available.find(required) == available.end()) {
                throw std::runtime_error("Missing required glfw extension");
            }
        }
    }

    void setupDebugMessenger()
    {
#ifndef XRN_USE_VALIDATION_LAYERS
        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        populateDebugMessengerCreateInfo(createInfo);
        if (CreateDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
#endif // XRN_USE_VALIDATION_LAYERS
    }

    bool checkValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char *layerName : m_validationLayers) {
            bool layerFound = false;

            for (const auto &layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
              return false;
            }
        }
        return true;
    }

    void populateDebugMessengerCreateInfo(
        VkDebugUtilsMessengerCreateInfoEXT &createInfo
    )
    {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;  // Optional
    }

    ~VulkanMemoryManager()
    {
#ifdef XRN_USE_VALIDATION_LAYERS
        // if (
            // auto func{ reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
                // vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT")
            // ) }; func != nullptr
        // ) {
            // func(m_instance, m_debugMessenger, nullptr);
        // }
#endif // XRN_USE_VALIDATION_LAYERS

        ::vkDestroyInstance(m_instance, nullptr);
        ::glfwTerminate();
    }



    // [[ nodiscard ]] static auto supportsValidationLayer(
    // ) -> bool
    // {
        // ::std::uint32_t layerCount;
        // std::vector<VkLayerProperties> availableLayers(layerCount);
        // vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        // vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        // for (const char* layerName : m_validationLayers) {
            // auto layerFound{ false };

            // for (const auto& layerProperties : availableLayers) {
                // if (::std::strcmp(layerName, layerProperties.layerName) == 0) {
                    // layerFound = true;
                    // break;
                // }
            // }

            // if (!layerFound) {
                // return false;
            // }
        // }
        // return true;
    // }

    static VKAPI_ATTR auto VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    ) -> VkBool32
    {
        switch (messageSeverity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            ::xrn::Logger::openBasic() << " [--- Diagnostic ---] "; break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: ::xrn::Logger::openInfo(); break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: ::xrn::Logger::openWarn(); break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: ::xrn::Logger::openError(); break;
        default: ::xrn::Logger::openBasic() << " [--- Unknown ---] "; break;
        }
        switch (messageType) {
        case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
            ::xrn::Logger::openBlank() << " (General unrelated to the specification or performance)"; break;
        case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
            ::xrn::Logger::openBlank() << " (Violates the specification or possible mistake)"; break;
        case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
            ::xrn::Logger::openBlank() << " (Potential non-optimal use of Vulkan)"; break;
        default: ::xrn::Logger::openBasic() << " (Unknown) "; break;
        }

        ::xrn::Logger::openBlank() << ' ' << pCallbackData->pMessage;
        return VK_FALSE;
    }



private:

    static const VulkanMemoryManager unaccessibleMemoryManager;
    ::VkInstance m_instance{};
    ::VkDebugUtilsMessengerEXT m_debugMessenger{};
    std::vector<const char*> m_validationLayers{};
};
const VulkanMemoryManager VulkanMemoryManager::unaccessibleMemoryManager{ "xrnEngine" };

} // namespace
