#include "../src/roundcircle.h"
#include "roundcircleplugin.h"

#include <QtPlugin>

RoundCirclePlugin::RoundCirclePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void RoundCirclePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool RoundCirclePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *RoundCirclePlugin::createWidget(QWidget *parent)
{
    return new RoundCircle(parent);
}

QString RoundCirclePlugin::name() const
{
    return QLatin1String("RoundCircle");
}

QString RoundCirclePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon RoundCirclePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/roundcircle.png"));
}

QString RoundCirclePlugin::toolTip() const
{
    return QLatin1String("");
}

QString RoundCirclePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool RoundCirclePlugin::isContainer() const
{
    return false;
}

QString RoundCirclePlugin::domXml() const
{
    return QLatin1String("<widget class=\"RoundCircle\" name=\"roundCircle\">\n</widget>\n");
}

QString RoundCirclePlugin::includeFile() const
{
    return QLatin1String("roundcircle.h");
}

