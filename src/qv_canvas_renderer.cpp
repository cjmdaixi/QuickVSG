#include "qv_canvas_renderer.h"
#include <QVulkanFunctions>
#include <QVulkanDeviceFunctions>
#include <QFile>

BEGIN_QUICKVSG_NAMESPACE

class KeyboardMap : public vsg::Inherit<vsg::Object, KeyboardMap>
{
public:
    KeyboardMap();

    bool getKeySymbol(const QKeyEvent* e, vsg::KeySymbol& keySymbol, vsg::KeySymbol& modifiedKeySymbol, vsg::KeyModifier& keyModifier);

protected:
    using VirtualKeyToKeySymbolMap = std::map<uint16_t, vsg::KeySymbol>;
    VirtualKeyToKeySymbolMap _keycodeMap;
};

KeyboardMap::KeyboardMap()
    : _keycodeMap{
        {0x0, vsg::KEY_Undefined},
        {Qt::Key_Space, vsg::KEY_Space},

        {'0', vsg::KEY_0},
        {'1', vsg::KEY_1},
        {'2', vsg::KEY_2},
        {'3', vsg::KEY_3},
        {'4', vsg::KEY_4},
        {'5', vsg::KEY_5},
        {'6', vsg::KEY_6},
        {'7', vsg::KEY_7},
        {'8', vsg::KEY_8},
        {'9', vsg::KEY_9},

        {'a', vsg::KEY_a},
        {'b', vsg::KEY_b},
        {'c', vsg::KEY_c},
        {'d', vsg::KEY_d},
        {'e', vsg::KEY_e},
        {'f', vsg::KEY_f},
        {'g', vsg::KEY_g},
        {'h', vsg::KEY_h},
        {'i', vsg::KEY_i},
        {'j', vsg::KEY_j},
        {'k', vsg::KEY_k},
        {'l', vsg::KEY_l},
        {'m', vsg::KEY_m},
        {'n', vsg::KEY_n},
        {'o', vsg::KEY_o},
        {'p', vsg::KEY_p},
        {'q', vsg::KEY_q},
        {'r', vsg::KEY_r},
        {'s', vsg::KEY_s},
        {'t', vsg::KEY_t},
        {'u', vsg::KEY_u},
        {'z', vsg::KEY_v},
        {'w', vsg::KEY_w},
        {'x', vsg::KEY_x},
        {'y', vsg::KEY_y},
        {'z', vsg::KEY_z},

        {'A', vsg::KEY_A},
        {'B', vsg::KEY_B},
        {'C', vsg::KEY_C},
        {'D', vsg::KEY_D},
        {'E', vsg::KEY_E},
        {'F', vsg::KEY_F},
        {'G', vsg::KEY_G},
        {'H', vsg::KEY_H},
        {'I', vsg::KEY_I},
        {'J', vsg::KEY_J},
        {'K', vsg::KEY_K},
        {'L', vsg::KEY_L},
        {'M', vsg::KEY_M},
        {'N', vsg::KEY_N},
        {'O', vsg::KEY_O},
        {'P', vsg::KEY_P},
        {'Q', vsg::KEY_Q},
        {'R', vsg::KEY_R},
        {'S', vsg::KEY_S},
        {'T', vsg::KEY_T},
        {'U', vsg::KEY_U},
        {'V', vsg::KEY_V},
        {'W', vsg::KEY_W},
        {'X', vsg::KEY_X},
        {'Y', vsg::KEY_Y},
        {'Z', vsg::KEY_Z},

        /* Cursor control & motion */

        {Qt::Key_Home, vsg::KEY_Home},
        {Qt::Key_Left, vsg::KEY_Left},   /* Move left, left arrow */
        {Qt::Key_Up, vsg::KEY_Up},       /* Move up, up arrow */
        {Qt::Key_Right, vsg::KEY_Right}, /* Move right, right arrow */
        {Qt::Key_Down, vsg::KEY_Down},   /* Move down, down arrow */
        //{Qt::Key_Home, vsg::KEY_Prior}, /* Prior, previous */
        //{ VK_, KEY_Page_Up = 0xFF55,
        {Qt::Key_Home, vsg::KEY_Next}, /* Next */
        //KEY_Page_Down = 0xFF56,
        {Qt::Key_End, vsg::KEY_End}, /* EOL */
        //{ KEY_Begin = 0xFF58, /* BOL */

        {'!', vsg::KEY_Exclaim},
        {'"', vsg::KEY_Quotedbl},
        {'#', vsg::KEY_Hash},
        {'$', vsg::KEY_Dollar},
        {'&', vsg::KEY_Ampersand},
        {Qt::Key_QuoteLeft, vsg::KEY_Quote},
        {'(', vsg::KEY_Leftparen},
        {')', vsg::KEY_Rightparen},
        {'*', vsg::KEY_Asterisk},
        {'+', vsg::KEY_Plus},
        {Qt::Key_Comma, vsg::KEY_Comma},
        {Qt::Key_Minus, vsg::KEY_Minus},
        {Qt::Key_Period, vsg::KEY_Period},
        {Qt::Key_Slash, vsg::KEY_Slash},
        {':', vsg::KEY_Colon},
        {Qt::Key_Semicolon, vsg::KEY_Semicolon},
        {'<', vsg::KEY_Less},
        {Qt::Key_Equal, vsg::KEY_Equals}, // + isn't an unmodded key, why does windows map is as a virtual??
        {'>', vsg::KEY_Greater},
        {'?', vsg::KEY_Question},
        {'@', vsg::KEY_At},
        {Qt::Key_BracketLeft, vsg::KEY_Leftbracket},
        {Qt::Key_Backslash, vsg::KEY_Backslash},
        {Qt::Key_BracketRight, vsg::KEY_Rightbracket},
        {'|', vsg::KEY_Caret},
        {'_', vsg::KEY_Underscore},
        {0xc0, vsg::KEY_Backquote},

        {Qt::Key_Back, vsg::KEY_BackSpace}, /* back space, back char */
        {Qt::Key_Tab, vsg::KEY_Tab},
        //    KEY_Linefeed = 0xFF0A, /* Linefeed, LF */
        {Qt::Key_Clear, vsg::KEY_Clear},
        {Qt::Key_Return, vsg::KEY_Return}, /* Return, enter */
        {Qt::Key_Pause, vsg::KEY_Pause},   /* Pause, hold */
        {Qt::Key_ScrollLock, vsg::KEY_Scroll_Lock},
        //    KEY_Sys_Req = 0xFF15,
        {Qt::Key_Escape, vsg::KEY_Escape},
        {Qt::Key_Delete, vsg::KEY_Delete}, /* Delete, rubout */

        /* Misc Functions */

        {Qt::Key_Select, vsg::KEY_Select}, /* Select, mark */
        {Qt::Key_Print, vsg::KEY_Print},
        {Qt::Key_Execute, vsg::KEY_Execute}, /* Execute, run, do */
        {Qt::Key_Insert, vsg::KEY_Insert},   /* Insert, insert here */
        //{ KEY_Undo = 0xFF65,    /* Undo, oops */
        //KEY_Redo = 0xFF66,    /* redo, again */
        {Qt::Key_Menu, vsg::KEY_Menu}, /* On Windows, this is VK_APPS, the context-menu key */
        // KEY_Find = 0xFF68,    /* Find, search */
        {Qt::Key_Cancel, vsg::KEY_Cancel}, /* Cancel, stop, abort, exit */
        {Qt::Key_Help, vsg::KEY_Help},     /* Help */
        //{ KEY_Break = 0xFF6B,
        //KEY_Mode_switch = 0xFF7E,   /* Character set switch */
        //KEY_Script_switch = 0xFF7E, /* Alias for mode_switch */
        {Qt::Key_NumLock, vsg::KEY_Num_Lock},

        /* Keypad Functions, keypad numbers cleverly chosen to map to ascii */

        //KEY_KP_Space = 0xFF80, /* space */
        //KEY_KP_Tab = 0xFF89,
        //KEY_KP_Enter = 0xFF8D, /* enter */
        //KEY_KP_F1 = 0xFF91,    /* PF1, KP_A, ... */
        //KEY_KP_F2 = 0xFF92,
        //KEY_KP_F3 = 0xFF93,
        //KEY_KP_F4 = 0xFF94,
        //KEY_KP_Home = 0xFF95,
        //KEY_KP_Left = 0xFF96,
        //KEY_KP_Up = 0xFF97,
        //KEY_KP_Right = 0xFF98,
        //KEY_KP_Down = 0xFF99,
        //KEY_KP_Prior = 0xFF9A,
        //KEY_KP_Page_Up = 0xFF9A,
        //KEY_KP_Next = 0xFF9B,
        //KEY_KP_Page_Down = 0xFF9B,
        //KEY_KP_End = 0xFF9C,
        //KEY_KP_Begin = 0xFF9D,
        //KEY_KP_Insert = 0xFF9E,
        //KEY_KP_Delete = 0xFF9F,
        //KEY_KP_Equal = 0xFFBD, /* equals */
        //KEY_KP_Multiply = 0xFFAA,
        //KEY_KP_Add = 0xFFAB,
        //KEY_KP_Separator = 0xFFAC, /* separator, often comma */
        //KEY_KP_Subtract = 0xFFAD,
        //KEY_KP_Decimal = 0xFFAE,
        //KEY_KP_Divide = 0xFFAF,

        {Qt::Key_0, vsg::KEY_KP_0},
        {Qt::Key_1, vsg::KEY_KP_1},
        {Qt::Key_2, vsg::KEY_KP_2},
        {Qt::Key_3, vsg::KEY_KP_3},
        {Qt::Key_4, vsg::KEY_KP_4},
        {Qt::Key_5, vsg::KEY_KP_5},
        {Qt::Key_6, vsg::KEY_KP_6},
        {Qt::Key_7, vsg::KEY_KP_7},
        {Qt::Key_8, vsg::KEY_KP_8},
        {Qt::Key_9, vsg::KEY_KP_9},

        /*
                * Auxiliary Functions; note the duplicate definitions for left and right
                * function keys;  Sun keyboards and a few other manufactures have such
                * function key groups on the left and/or right sides of the keyboard.
                * We've not found a keyboard with more than 35 function keys total.
                */

        {Qt::Key_F1, vsg::KEY_F1},
        {Qt::Key_F2, vsg::KEY_F2},
        {Qt::Key_F3, vsg::KEY_F3},
        {Qt::Key_F4, vsg::KEY_F4},
        {Qt::Key_F5, vsg::KEY_F5},
        {Qt::Key_F6, vsg::KEY_F6},
        {Qt::Key_F7, vsg::KEY_F7},
        {Qt::Key_F8, vsg::KEY_F8},
        {Qt::Key_F9, vsg::KEY_F9},
        {Qt::Key_F10, vsg::KEY_F10},
        {Qt::Key_F11, vsg::KEY_F11},
        {Qt::Key_F12, vsg::KEY_F12},
        {Qt::Key_F13, vsg::KEY_F13},
        {Qt::Key_F14, vsg::KEY_F14},
        {Qt::Key_F15, vsg::KEY_F15},
        {Qt::Key_F16, vsg::KEY_F16},
        {Qt::Key_F17, vsg::KEY_F17},
        {Qt::Key_F18, vsg::KEY_F18},
        {Qt::Key_F19, vsg::KEY_F19},
        {Qt::Key_F20, vsg::KEY_F20},
        {Qt::Key_F21, vsg::KEY_F21},
        {Qt::Key_F22, vsg::KEY_F22},
        {Qt::Key_F23, vsg::KEY_F23},
        {Qt::Key_F24, vsg::KEY_F24},

        //KEY_F25 = 0xFFD6,
        //KEY_F26 = 0xFFD7,
        //KEY_F27 = 0xFFD8,
        //KEY_F28 = 0xFFD9,
        //KEY_F29 = 0xFFDA,
        //KEY_F30 = 0xFFDB,
        //KEY_F31 = 0xFFDC,
        //KEY_F32 = 0xFFDD,
        //KEY_F33 = 0xFFDE,
        //KEY_F34 = 0xFFDF,
        //KEY_F35 = 0xFFE0,

        /* Modifiers */

        {Qt::Key_Shift, vsg::KEY_Shift_L},     /* Left shift */
        //            {VK_RSHIFT, KEY_Shift_R},     /* Right shift */
        //            {VK_LCONTROL, KEY_Control_L}, /* Left control */
        {Qt::Key_Control, vsg::KEY_Control_R}, /* Right control */
        {Qt::Key_CapsLock, vsg::KEY_Caps_Lock}  /* Caps lock */
        //KEY_Shift_Lock = 0xFFE6, /* Shift lock */

        //KEY_Meta_L = 0xFFE7,  /* Left meta */
        //KEY_Meta_R = 0xFFE8,  /* Right meta */
        //            {VK_LMENU, KEY_Alt_L},  /* Left alt */
        //            {VK_RMENU, KEY_Alt_R},  /* Right alt */
        //            {VK_LWIN, KEY_Super_L}, /* Left super */
        //            {VK_RWIN, KEY_Super_R}  /* Right super */
        //KEY_Hyper_L = 0xFFED, /* Left hyper */
        //KEY_Hyper_R = 0xFFEE  /* Right hyper */
    }
{
}

bool KeyboardMap::getKeySymbol(const QKeyEvent *e, vsg::KeySymbol &keySymbol, vsg::KeySymbol &modifiedKeySymbol, vsg::KeyModifier &keyModifier)
{
    auto itr = _keycodeMap.find((uint32_t)e->key());

    if (itr == _keycodeMap.end())
        return false;

    keySymbol = itr->second;
    modifiedKeySymbol = keySymbol;

    uint16_t modifierMask = 0;
    switch (e->modifiers())
    {
    case Qt::NoModifier:
        break;
    case Qt::ShiftModifier:
        modifierMask |= vsg::KeyModifier::MODKEY_Shift;
        break;
    case Qt::ControlModifier:
        modifierMask |= vsg::KeyModifier::MODKEY_Control;
        break;
    case Qt::AltModifier:
        modifierMask |= vsg::KeyModifier::MODKEY_Alt;
        break;
    }

    keyModifier = (vsg::KeyModifier)modifierMask;

    return true;
}

HANDLE getExternalMemoryHandle(vsg::Device* device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagBits handleType)
{
    HANDLE handle = 0;

    VkMemoryGetWin32HandleInfoKHR vkMemoryGetWin32HandleInfoKHR = {};
    vkMemoryGetWin32HandleInfoKHR.sType = VK_STRUCTURE_TYPE_MEMORY_GET_WIN32_HANDLE_INFO_KHR;
    vkMemoryGetWin32HandleInfoKHR.pNext = NULL;
    vkMemoryGetWin32HandleInfoKHR.memory = memory;
    vkMemoryGetWin32HandleInfoKHR.handleType = handleType;

    PFN_vkGetMemoryWin32HandleKHR fpGetMemoryWin32HandleKHR;
    fpGetMemoryWin32HandleKHR = (PFN_vkGetMemoryWin32HandleKHR)vkGetDeviceProcAddr(*device, "vkGetMemoryWin32HandleKHR");
    if (!fpGetMemoryWin32HandleKHR) {
        throw std::runtime_error("Failed to retrieve vkGetMemoryWin32HandleKHR!");
    }
    if (fpGetMemoryWin32HandleKHR(*device, &vkMemoryGetWin32HandleInfoKHR, &handle) != VK_SUCCESS) {
        throw std::runtime_error("Failed to retrieve handle for buffer!");
    }
    return handle;
}

CanvasRenderer::CanvasRenderer(Canvas* canvas)
    : m_canvas(canvas)
{
    m_window = m_canvas->window();
    connect(m_window, &QQuickWindow::beforeRendering, this, &CanvasRenderer::render);
    connect(m_window, &QQuickWindow::screenChanged, this, [this]() {
        if (m_window->effectiveDevicePixelRatio() != m_dpr)
            m_canvas->update();
        });

    m_keyboardMap = KeyboardMap::create();
    qCDebug(log_qv) << "canvas renderer created...";
}

CanvasRenderer::~CanvasRenderer()
{
    delete texture();
    freeTexture();
    qCDebug(log_qv) << "canvas renderer destroyed...";
}

void CanvasRenderer::addUIEvent(vsg::UIEvent* e)
{
    m_UIEvents.emplace_back(e);
}

bool CanvasRenderer::vsgKeySymbol(const QKeyEvent* e, vsg::KeySymbol& keySymbol, vsg::KeySymbol& modifiedKeySymbol, vsg::KeyModifier& keyModifier)
{
    return m_keyboardMap->getKeySymbol(e, keySymbol, modifiedKeySymbol, keyModifier);
}

bool CanvasRenderer::initialize()
{
    const int framesInFlight = m_window->graphicsStateInfo().framesInFlight;

    QSGRendererInterface* rif = m_window->rendererInterface();
    QVulkanInstance* inst = reinterpret_cast<QVulkanInstance*>(
        rif->getResource(m_window, QSGRendererInterface::VulkanInstanceResource));
    Q_ASSERT(inst && inst->isValid());

    m_physDev = *static_cast<VkPhysicalDevice*>(rif->getResource(m_window, QSGRendererInterface::PhysicalDeviceResource));
    m_dev = *static_cast<VkDevice*>(rif->getResource(m_window, QSGRendererInterface::DeviceResource));
    Q_ASSERT(m_physDev && m_dev);

    m_devFuncs = inst->deviceFunctions(m_dev);
    m_funcs = inst->functions();
    Q_ASSERT(m_devFuncs && m_funcs);

    VkPhysicalDeviceProperties physDevProps;
    m_funcs->vkGetPhysicalDeviceProperties(m_physDev, &physDevProps);

    VkPhysicalDeviceMemoryProperties physDevMemProps;
    m_funcs->vkGetPhysicalDeviceMemoryProperties(m_physDev, &physDevMemProps);

    VkExtent2D extent{ uint32_t(m_size.width()), uint32_t(m_size.height()) };

    return initVsgObjects(extent);
}

bool CanvasRenderer::initVsgObjects(const VkExtent2D& extent)
{
    vsg::Names instanceExtensions;
    vsg::Names requestedLayers;
    if (m_vsg_debugLayer)
    {
        instanceExtensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);

        instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
        requestedLayers.push_back("VK_LAYER_KHRONOS_validation");
        requestedLayers.push_back("VK_LAYER_LUNARG_standard_validation");
    }
    if (m_vsg_apiDumpLayer) {
        requestedLayers.push_back("VK_LAYER_LUNARG_api_dump");
    }

    vsg::Names validatedNames = vsg::validateInstancelayerNames(requestedLayers);

    m_vsg_instance = vsg::Instance::create(instanceExtensions, validatedNames);

    auto [physicalDevice, queueFamily] = m_vsg_instance->getPhysicalDeviceAndQueueFamily(VK_QUEUE_GRAPHICS_BIT);
    if (!physicalDevice || queueFamily < 0)
    {
        qCCritical(log_qv) << "Could not create PhysicalDevice!";
        return false;
    }

    m_vsg_physicalDevice = physicalDevice;
    m_vsg_graphicsQueueFamily = queueFamily;

    vsg::Names deviceExtensions;
#ifdef _WIN64
    deviceExtensions.push_back(VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME);
    deviceExtensions.push_back(VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME);
#else
    deviceExtensions.push_back(VK_KHR_EXTERNAL_MEMORY_FD_EXTENSION_NAME);
    deviceExtensions.push_back(VK_KHR_EXTERNAL_FENCE_FD_EXTENSION_NAME);
#endif
    vsg::QueueSettings queueSettings{ vsg::QueueSetting{queueFamily, {1.0}} };

    auto deviceFeatures = vsg::DeviceFeatures::create();
    deviceFeatures->get().samplerAnisotropy = VK_TRUE;

    m_vsg_device = vsg::Device::create(physicalDevice, queueSettings, validatedNames, deviceExtensions, deviceFeatures);  
    
    m_vsg_camera = vsg::Camera::create();
    return true;
}

void CanvasRenderer::createVsgFramebuffer(const VkExtent2D& extent)
{
    auto device = m_vsg_device;

    vsg::ImageInfo colorImageInfo, depthImageInfo;
    VkExtent3D attachmentExtent{ extent.width, extent.height, 1 };
    // Attachments
    // create image for color attachment
    auto colorImage = vsg::Image::create();
    colorImage->imageType = VK_IMAGE_TYPE_2D;
    colorImage->format = VK_FORMAT_R8G8B8A8_UNORM;
    colorImage->extent = attachmentExtent;
    colorImage->mipLevels = 1;
    colorImage->arrayLayers = 1;
    colorImage->samples = VK_SAMPLE_COUNT_1_BIT;
    colorImage->tiling = VK_IMAGE_TILING_OPTIMAL;
    colorImage->usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    colorImage->initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorImage->flags = 0;
    colorImage->sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    colorImage->compile(device);

    VkExportMemoryAllocateInfo exportMemoryAllocateInfo = {};
    exportMemoryAllocateInfo.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO;
    exportMemoryAllocateInfo.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT;

    auto colorImageDeviceMemory = vsg::DeviceMemory::create(device, colorImage->getMemoryRequirements(m_vsg_device->deviceID),
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &exportMemoryAllocateInfo);

    if (!colorImageDeviceMemory)
    {
        throw vsg::Exception{ "Error: Failed allocate memory for color image.", 0 };
    }
#ifdef _WIN64
    m_memoryHandle = getExternalMemoryHandle(device, *colorImageDeviceMemory, VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT);
    if (m_memoryHandle == INVALID_HANDLE_VALUE)
    {
        throw vsg::Exception{ "Error: Failed get external memory handle for image.", 0 };
    }
#else
    m_memoryFd = getExternalMemoryHandle(m_vsg_device, *colorImageDeviceMemory, VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT);

    if (m_memoryFd == -1)
    {
        throw vsg::Exception{ "Error: Failed get external memory handle for image.", 0 };
    }
#endif

    colorImage->bind(colorImageDeviceMemory, 0);

    auto colorImageView = vsg::ImageView::create(colorImage, VK_IMAGE_ASPECT_COLOR_BIT);
    colorImageView->compile(m_vsg_device);

    colorImageInfo.imageView = colorImageView;
    colorImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    colorImageInfo.sampler = nullptr;

    // create depth buffer
    VkFormat depthFormat = VK_FORMAT_D24_UNORM_S8_UINT;
    auto depthImage = vsg::Image::create();
    depthImage->imageType = VK_IMAGE_TYPE_2D;
    depthImage->extent = attachmentExtent;
    depthImage->mipLevels = 1;
    depthImage->arrayLayers = 1;
    depthImage->samples = VK_SAMPLE_COUNT_1_BIT;
    depthImage->format = depthFormat;
    depthImage->tiling = VK_IMAGE_TILING_OPTIMAL;
    depthImage->usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    depthImage->initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depthImage->flags = 0;
    depthImage->sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    // XXX Does layout matter?
    depthImageInfo.sampler = nullptr;
    depthImageInfo.imageView = vsg::createImageView(m_vsg_device, depthImage, VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT);
    depthImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;

    // attachment descriptions
    vsg::RenderPass::Attachments attachments(2);
    // Color attachment
    attachments[0].format = VK_FORMAT_R8G8B8A8_UNORM;
    attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[0].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    // Depth attachment
    attachments[1].format = depthFormat;
    attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference colorReference = { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
    VkAttachmentReference depthReference = { 1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };
    vsg::RenderPass::Subpasses subpassDescription(1);
    subpassDescription[0].pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDescription[0].colorAttachments.emplace_back(VkAttachmentReference{ 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
    subpassDescription[0].depthStencilAttachments.emplace_back(depthReference);

    vsg::RenderPass::Dependencies dependencies(2);

    // XXX This dependency is copied from the offscreenrender.cpp
    // example. I don't completely understand it, but I think it's
    // purpose is to create a barrier if some earlier render pass was
    // using this framebuffer's attachment as a texture.
    dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
    dependencies[0].dstSubpass = 0;
    dependencies[0].srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencies[0].srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
    dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    // This is the heart of what makes Vulkan offscreen rendering
    // work: render passes that follow are blocked from using this
    // passes' color attachment in their fragment shaders until all
    // this pass' color writes are finished.
    dependencies[1].srcSubpass = 0;
    dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
    dependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencies[1].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    dependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependencies[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    auto renderPass = vsg::RenderPass::create(device, attachments, subpassDescription, dependencies);

    // Framebuffer
    m_vsg_framebuffer = vsg::Framebuffer::create(renderPass, vsg::ImageViews{ colorImageInfo.imageView, depthImageInfo.imageView }, extent.width, extent.height, 1);
}

void CanvasRenderer::updateVsgScene(const VkExtent2D& extent)
{
    auto modelPathBytes = m_modelPath.toLocal8Bit();
    m_vsg_scene = vsg::read_cast<vsg::Node>(modelPathBytes.toStdString());

    vsg::ComputeBounds computeBounds;
    m_vsg_scene->accept(computeBounds);
    vsg::dvec3 centre = (computeBounds.bounds.min + computeBounds.bounds.max) * 0.5;
    double radius = vsg::length(computeBounds.bounds.max - computeBounds.bounds.min) * 0.6;
    double nearFarRatio = 0.001;

    // set up the camera
    auto lookAt = vsg::LookAt::create(centre + vsg::dvec3(0.0, -radius * 3.5, 0.0),
        centre, vsg::dvec3(0.0, 0.0, 1.0));

    auto perspective = vsg::Perspective::create(30.0, 
        static_cast<double>(extent.width) / static_cast<double>(extent.height),
        nearFarRatio * radius, radius * 4.5);

    m_vsg_camera = vsg::Camera::create(perspective, lookAt, vsg::ViewportState::create(extent));
}

bool CanvasRenderer::createVsgRenderGraph(const VkExtent2D& extent)
{
    auto renderGraph = vsg::RenderGraph::create();
    renderGraph->renderArea.offset = VkOffset2D{ 0, 0 };
    renderGraph->renderArea.extent = extent;
    renderGraph->framebuffer = m_vsg_framebuffer;

    renderGraph->clearValues.resize(2);
    renderGraph->clearValues[0].color = { {0.4f, 0.2f, 0.4f, 1.0f} };
    renderGraph->clearValues[1].depthStencil = VkClearDepthStencilValue{ 1.0f, 0 };

    // create the viewer
    m_vsg_viewer = vsg::Viewer::create();

    m_vsg_viewer->addEventHandler(vsg::Trackball::create(m_vsg_camera));

    auto rtt_view = vsg::View::create(m_vsg_camera, m_vsg_scene);
    renderGraph->addChild(rtt_view);

    auto commandGraph = vsg::CommandGraph::create(m_vsg_device, m_vsg_graphicsQueueFamily);
    commandGraph->addChild(renderGraph);
    
    m_vsg_viewer->assignRecordAndSubmitTaskAndPresentation({ commandGraph });
    m_vsg_viewer->compile();

    return true;
}

QSGTexture* CanvasRenderer::texture() const
{
    return QSGSimpleTextureNode::texture();
}

void CanvasRenderer::sync()
{
    m_dpr = m_window->effectiveDevicePixelRatio();
    auto newSize = m_canvas->size() * m_dpr;
    bool needsNewTexture = false;
    bool needsUpdateScene = false;

    if (m_modelPath != m_canvas->modelPath()) {
        needsUpdateScene = true;
        m_modelPath = m_canvas->modelPath();
    }
    if (!m_initialized) {
        m_size = newSize;
        initialize();
        m_initialized = true;
    }

    if (!texture()) {
        needsNewTexture = true;
    }

    if (newSize != m_size) {
        needsNewTexture = true;
        m_size = newSize;
    }

    VkExtent2D extent{ uint32_t(m_size.width()), uint32_t(m_size.height()) };

    if (needsUpdateScene) {
        updateVsgScene(extent);
    }
    else {
        m_vsg_camera->setViewportState(vsg::ViewportState::create(extent));
        m_vsg_camera->getProjectionMatrix()->changeExtent(m_vsg_extent, extent);
    }

    if (needsNewTexture) {
        if (texture()) {
            delete texture();
            freeTexture();            
        }

        createVsgFramebuffer(extent);

        buildTexture(m_size);
        QSGTexture* wrapper = QNativeInterface::QSGVulkanTexture::fromNative(m_textureImage,
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
            m_window,
            m_size.toSize());
        setTexture(wrapper);
    }

    if (needsUpdateScene || needsNewTexture) {
        createVsgRenderGraph(extent);
    }

    m_vsg_extent = extent;
    m_vsg_events = m_UIEvents;
    m_UIEvents.clear();
}

bool CanvasRenderer::buildTexture(const QSizeF& size)
{
    VkImageCreateInfo imageInfo;
    memset(&imageInfo, 0, sizeof(imageInfo));
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.flags = 0;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    imageInfo.extent.width = uint32_t(size.width());
    imageInfo.extent.height = uint32_t(size.height());
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;

    imageInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    imageInfo.usage |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    VkImage image = VK_NULL_HANDLE;
    if (m_devFuncs->vkCreateImage(m_dev, &imageInfo, nullptr, &image) != VK_SUCCESS) {
        qCritical("VulkanWrapper: failed to create image!");
        return  false;
    }

    m_textureImage = image;

    VkMemoryRequirements memReq;
    m_devFuncs->vkGetImageMemoryRequirements(m_dev, image, &memReq);

    quint32 memIndex = 0;
    VkPhysicalDeviceMemoryProperties physDevMemProps;
    m_window->vulkanInstance()->functions()->vkGetPhysicalDeviceMemoryProperties(m_physDev, &physDevMemProps);
    for (uint32_t i = 0; i < physDevMemProps.memoryTypeCount; ++i) {
        if (!(memReq.memoryTypeBits & (1 << i)))
            continue;
        memIndex = i;
    }

#ifdef _WIN64
    VkImportMemoryWin32HandleInfoKHR importMemory = {};
    importMemory.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR;
    importMemory.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT;
    importMemory.handle = m_memoryHandle;
#else
    VkImportMemoryFdInfoKHR importMemory = {};
    importMemory.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR;
    importMemory.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT;
    importMemory.fd = m_memoryFd;
#endif

    VkMemoryAllocateInfo allocInfo = {
        VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        &importMemory,
        memReq.size,
        memIndex
    };

    VkDeviceMemory textureImageMemory;
    VkResult err = m_devFuncs->vkAllocateMemory(m_dev, &allocInfo, nullptr, &textureImageMemory);
    if (err != VK_SUCCESS) {
        qWarning("Failed to allocate memory for linear image: %d", err);
        return false;
    }

    err = m_devFuncs->vkBindImageMemory(m_dev, image, textureImageMemory, 0);
    if (err != VK_SUCCESS) {
        qWarning("Failed to bind linear image memory: %d", err);
        return false;
    }

    VkImageViewCreateInfo viewInfo;
    memset(&viewInfo, 0, sizeof(viewInfo));
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = imageInfo.format;
    viewInfo.components.r = VK_COMPONENT_SWIZZLE_R;
    viewInfo.components.g = VK_COMPONENT_SWIZZLE_G;
    viewInfo.components.b = VK_COMPONENT_SWIZZLE_B;
    viewInfo.components.a = VK_COMPONENT_SWIZZLE_A;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = VK_REMAINING_MIP_LEVELS;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = VK_REMAINING_ARRAY_LAYERS;

    VkImageView textureImageView;
    err = m_devFuncs->vkCreateImageView(m_dev, &viewInfo, nullptr, &textureImageView);
    if (err != VK_SUCCESS) {
        qWarning("Failed to create render target image view: %d", err);
        return false;
    }

    return true;
}

void CanvasRenderer::freeTexture()
{
    if (m_textureImage) {
        m_devFuncs->vkDestroyImage(m_dev, m_textureImage, nullptr);
        m_textureImage = VK_NULL_HANDLE;
    }
}

void CanvasRenderer::render()
{
    if (!m_initialized)
        return;

    VkResult err = VK_SUCCESS;

    QSGRendererInterface* rif = m_window->rendererInterface();
    VkCommandBuffer cmdBuf = *reinterpret_cast<VkCommandBuffer*>(
        rif->getResource(m_window, QSGRendererInterface::CommandListResource));

    if (m_vsg_viewer->advanceToNextFrame())
    {
        auto& events = m_vsg_viewer->getEvents();
        for (auto e : m_vsg_events) {
            events.emplace_back(e);
        }
        // pass any events into EventHandlers assigned to the Viewer, this includes Frame events generated by the viewer each frame
        m_vsg_viewer->handleEvents();

        m_vsg_events.clear();

        m_vsg_viewer->update();

        m_vsg_viewer->recordAndSubmit();

        VkImageMemoryBarrier imageTransitionBarrier = {};
        imageTransitionBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        imageTransitionBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        imageTransitionBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        imageTransitionBarrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        imageTransitionBarrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageTransitionBarrier.image = m_textureImage;
        imageTransitionBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageTransitionBarrier.subresourceRange.levelCount = imageTransitionBarrier.subresourceRange.layerCount = 1;

        m_devFuncs->vkCmdPipelineBarrier(cmdBuf,
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            0, 0, nullptr, 0, nullptr,
            1, &imageTransitionBarrier);
    }
}

END_QUICKVSG_NAMESPACE