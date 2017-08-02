#include "../src/verifiedcode.h"
#include "verifiedcodeplugin.h"

#include <QtPlugin>

VerifiedCodePlugin::VerifiedCodePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void VerifiedCodePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool VerifiedCodePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *VerifiedCodePlugin::createWidget(QWidget *parent)
{
    return new VerifiedCode(parent);
}

QString VerifiedCodePlugin::name() const
{
    return QLatin1String("VerifiedCode");
}

QString VerifiedCodePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon VerifiedCodePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/verifiedcode.png"));
}

QString VerifiedCodePlugin::toolTip() const
{
    return QLatin1String("");
}

QString VerifiedCodePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool VerifiedCodePlugin::isContainer() const
{
    return false;
}

QString VerifiedCodePlugin::domXml() const
{
    return QLatin1String("<widget class=\"VerifiedCode\" name=\"verifiedCode\">\n</widget>\n");
}

QString VerifiedCodePlugin::includeFile() const
{
    return QLatin1String("verifiedcode.h");
}

