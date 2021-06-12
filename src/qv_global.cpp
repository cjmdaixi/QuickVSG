#include "qv_global.h"
#include "qv_canvas.h"
#include <QQmlEngine>

Q_LOGGING_CATEGORY(log_qv, "quickvsg")

BEGIN_QUICKVSG_NAMESPACE

bool initialize()
{
    auto uri = "QuickVSG";

    qmlRegisterType<Canvas>(uri, 1, 0, "Canvas");

    qmlProtectModule(uri, 1);

    return true;
}


void cleanup()
{

}

END_QUICKVSG_NAMESPACE