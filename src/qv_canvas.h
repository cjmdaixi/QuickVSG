#pragma once

#include "qv_global.h"
#include <QQuickItem>
#include <QQuickWindow>
#include <QColor>

BEGIN_QUICKVSG_NAMESPACE

class CanvasRenderer;

class QV_EXPORTS Canvas : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString modelPath READ modelPath WRITE setModelPath NOTIFY modelPathChanged)
public:
    Canvas(QQuickItem *parent = nullptr);
    ~Canvas() override;

    QString modelPath() const;
    void setModelPath(const QString& newModelPath);
signals:
    void modelPathChanged();
protected:
    QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*) override;
    void geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry) override;
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    void releaseResources() override;
    CanvasRenderer* m_renderer = nullptr;
    QString m_modelPath;
};

END_QUICKVSG_NAMESPACE