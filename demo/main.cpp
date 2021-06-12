#include <vsg/all.h>
#include <vsg/viewer/Window.h>

#include <QGuiApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVulkanInstance>
#include <QQuickView>
#include <QQuickWindow>
#include <QQuickGraphicsDevice> 
#include <qv_global.h>
#include <QtDebug>
#include <QUrl>

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    QQuickWindow::setGraphicsApi(QSGRendererInterface::VulkanRhi);

    QuickVSG::initialize();

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    auto appPid = app.applicationPid();
    auto modelPath = qgetenv("VSG_FILE_PATH");
    qDebug() << "model path:" << modelPath;

    engine.rootContext()->setContextProperty("$pid", appPid);
    engine.rootContext()->setContextProperty("$modelsPath", "file:///" + QString::fromLocal8Bit(modelPath));

    engine.load(url);
    auto rt = app.exec();

    QuickVSG::cleanup();

    return rt;
}
