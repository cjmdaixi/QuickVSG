#pragma once 

#include <QtGlobal>
#include <QLoggingCategory>

#if defined(QUICKVSG_LIBRARY)
#define QV_EXPORTS Q_DECL_EXPORT
#else
#define QV_EXPORTS Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(log_qv)

#define BEGIN_QUICKVSG_NAMESPACE namespace QuickVSG{
#define END_QUICKVSG_NAMESPACE }

BEGIN_QUICKVSG_NAMESPACE

QV_EXPORTS bool initialize();

QV_EXPORTS void cleanup();

END_QUICKVSG_NAMESPACE

