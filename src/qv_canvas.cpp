#include "qv_canvas.h"
#include "qv_canvas_renderer.h"

BEGIN_QUICKVSG_NAMESPACE

Canvas::Canvas(QQuickItem* parent /*= nullptr*/)
    : QQuickItem(parent)
{
    qCDebug(log_qv) << "canvas constructed...";
    setFlag(ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);
}

Canvas::~Canvas()
{
    qCDebug(log_qv) << "canvas destroyed...";
}

QString Canvas::modelPath() const
{
    return m_modelPath;
}

void Canvas::setModelPath(const QString& newModelPath)
{
    if (m_modelPath == newModelPath) return;
    m_modelPath = newModelPath;
    emit modelPathChanged();
    update();
}

void Canvas::releaseResources()
{
    m_renderer = nullptr;
}

QSGNode* Canvas::updatePaintNode(QSGNode* node, UpdatePaintNodeData*)
{
    CanvasRenderer* renderer = static_cast<CanvasRenderer*>(node);

    if (!renderer && (width() <= 0 || height() <= 0))
        return nullptr;

    if (!renderer) {
        m_renderer = new CanvasRenderer(this);
        renderer = m_renderer;
    }

    m_renderer->sync();

    renderer->setTextureCoordinatesTransform(QSGSimpleTextureNode::NoTransform);
    renderer->setFiltering(QSGTexture::Linear);
    renderer->setRect(0, 0, width(), height());

    window()->update(); // ensure getting to beforeRendering() at some point

    return renderer;
}

void Canvas::geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry)
{
    QQuickItem::geometryChange(newGeometry, oldGeometry);

    if (newGeometry.size() != oldGeometry.size()) {

        vsg::clock::time_point event_time = vsg::clock::now();
        if (m_renderer && m_renderer->m_initialized)
            m_renderer->addUIEvent(new vsg::ConfigureWindowEvent(nullptr, event_time, newGeometry.x(), newGeometry.y(), static_cast<uint32_t>(newGeometry.width()), static_cast<uint32_t>(newGeometry.height())));
        update();
    }
}

void Canvas::keyPressEvent(QKeyEvent* e)
{
    vsg::KeySymbol keySymbol, modifiedKeySymbol;
    vsg::KeyModifier keyModifier;

    //    if (e->key() == Qt::Key_Escape)
    //        QCoreApplication::exit(0);

    if (m_renderer->vsgKeySymbol(e, keySymbol, modifiedKeySymbol, keyModifier))
    {
        vsg::clock::time_point event_time = vsg::clock::now();
        m_renderer->addUIEvent(new vsg::KeyPressEvent(nullptr, event_time, keySymbol, modifiedKeySymbol, keyModifier));
    }
}

void Canvas::keyReleaseEvent(QKeyEvent* e)
{
    vsg::KeySymbol keySymbol, modifiedKeySymbol;
    vsg::KeyModifier keyModifier;

    if (m_renderer->vsgKeySymbol(e, keySymbol, modifiedKeySymbol, keyModifier))
    {
        vsg::clock::time_point event_time = vsg::clock::now();
        m_renderer->addUIEvent(new vsg::KeyReleaseEvent(nullptr, event_time, keySymbol, modifiedKeySymbol, keyModifier));
    }
}

void Canvas::mousePressEvent(QMouseEvent* e)
{
    auto p = e->pos() * window()->effectiveDevicePixelRatio();

    vsg::clock::time_point event_time = vsg::clock::now();

    int button = 0;
    switch (e->buttons())
    {
    case Qt::LeftButton: button |= vsg::BUTTON_MASK_1; break;
    case Qt::RightButton: button |= vsg::BUTTON_MASK_3; break;
    case Qt::MiddleButton: button |= vsg::BUTTON_MASK_2; break;
    case Qt::NoButton: button = 0; break;
    default: button = 0; break;
    }

    m_renderer->addUIEvent(new vsg::ButtonPressEvent(nullptr, event_time, p.x(), p.y(), (vsg::ButtonMask)button, 0));
    update();
}

void Canvas::mouseMoveEvent(QMouseEvent* e)
{
    auto p = e->pos() * window()->effectiveDevicePixelRatio();
    //p.setY(-p.y());

    vsg::clock::time_point event_time = vsg::clock::now();

    int button = 0;
    switch (e->buttons())
    {
    case Qt::LeftButton: button |= vsg::BUTTON_MASK_1; break;
    case Qt::RightButton: button |= vsg::BUTTON_MASK_3; break;
    case Qt::MiddleButton: button |= vsg::BUTTON_MASK_2; break;
    case Qt::NoButton: button = 0; break;
    default: button = 0; break;
    }

    m_renderer->addUIEvent(new vsg::MoveEvent(nullptr, event_time, p.x(), p.y(), (vsg::ButtonMask)button));
    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent* e)
{
    auto p = e->pos() * window()->effectiveDevicePixelRatio();
    //p.setY(-p.y());
    vsg::clock::time_point event_time = vsg::clock::now();

    int button = 0;
    switch (e->buttons())
    {
    case Qt::LeftButton: button |= vsg::BUTTON_MASK_1; break;
    case Qt::RightButton: button |= vsg::BUTTON_MASK_3; break;
    case Qt::MiddleButton: button |= vsg::BUTTON_MASK_2; break;
    case Qt::NoButton: button = 0; break;
    default: button = 0; break;
    }

    m_renderer->addUIEvent(new vsg::ButtonReleaseEvent(nullptr, event_time, p.x(), p.y(), (vsg::ButtonMask)button, 0));
    update();
}

void Canvas::wheelEvent(QWheelEvent* e)
{
    vsg::clock::time_point event_time = vsg::clock::now();

    m_renderer->addUIEvent(new vsg::ScrollWheelEvent(nullptr, event_time, e->angleDelta().y() < 0 ? vsg::vec3(0.0f, -1.0f, 0.0f) : vsg::vec3(0.0f, 1.0f, 0.0f)));
    update();
}


END_QUICKVSG_NAMESPACE