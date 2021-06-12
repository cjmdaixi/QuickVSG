#pragma once

#include "qv_global.h"
#include <vsg/all.h>
#include <QVulkanInstance>
#include <QQuickWindow>
#include <QMap>
#include <QSGTextureProvider>
#include <QSGSimpleTextureNode>

#include "qv_canvas.h"

BEGIN_QUICKVSG_NAMESPACE

class VsgObjects;
class KeyboardMap;

class CanvasRenderer : public QSGTextureProvider, public QSGSimpleTextureNode
{
    Q_OBJECT
public:
    friend class Canvas;

    explicit CanvasRenderer(Canvas* canvas);
    ~CanvasRenderer() override;

    void addUIEvent(vsg::UIEvent* e);
    bool vsgKeySymbol(const QKeyEvent* e, vsg::KeySymbol& keySymbol, vsg::KeySymbol& modifiedKeySymbol, vsg::KeyModifier& keyModifier);

    QSGTexture* texture() const override;
    void sync();

public slots:
    void render();
private:
    bool buildTexture(const QSizeF& size);
    void freeTexture();
    bool initialize();
    bool initVsgObjects(const VkExtent2D& extent);
    void createVsgFramebuffer(const VkExtent2D& extent);
    void updateVsgScene(const VkExtent2D& extent);
    bool createVsgRenderGraph(const VkExtent2D& extent);

private:
    Canvas *m_canvas;
    QQuickWindow* m_window;
    QSizeF m_size;
    qreal m_dpr;

    bool m_initialized = false;

    VkPhysicalDevice m_physDev = VK_NULL_HANDLE;
    VkDevice m_dev = VK_NULL_HANDLE;

    QVulkanDeviceFunctions* m_devFuncs = nullptr;
    QVulkanFunctions* m_funcs = nullptr;

    vsg::ref_ptr<vsg::Instance> m_vsg_instance;
    bool m_vsg_debugLayer = false, m_vsg_apiDumpLayer = false;
    vsg::ref_ptr<vsg::PhysicalDevice> m_vsg_physicalDevice;
    vsg::ref_ptr<vsg::Device> m_vsg_device;
    vsg::ref_ptr<vsg::Framebuffer> m_vsg_framebuffer;
    vsg::ref_ptr<vsg::Viewer> m_vsg_viewer;
    vsg::ref_ptr<vsg::Camera> m_vsg_camera;
    vsg::ref_ptr<vsg::Node> m_vsg_scene;
    int m_vsg_graphicsQueueFamily;
    vsg::UIEvents m_vsg_events;
    VkExtent2D m_vsg_extent;

    vsg::UIEvents m_UIEvents;
    vsg::ref_ptr<KeyboardMap> m_keyboardMap;
#ifdef _WIN64
    HANDLE m_memoryHandle = INVALID_HANDLE_VALUE;
#else
    int m_memoryFd = -1;
#endif
    VkImage m_textureImage = VK_NULL_HANDLE;

    QString m_modelPath;
};

END_QUICKVSG_NAMESPACE