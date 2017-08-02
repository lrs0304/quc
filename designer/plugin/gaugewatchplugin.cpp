#include "../src/gaugewatch.h"
#include "gaugewatchplugin.h"

#include <QtPlugin>

GaugeWatchPlugin::GaugeWatchPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void GaugeWatchPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeWatchPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeWatchPlugin::createWidget(QWidget *parent)
{
    return new GaugeWatch(parent);
}

QString GaugeWatchPlugin::name() const
{
    return QLatin1String("GaugeWatch");
}

QString GaugeWatchPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeWatchPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugewatch.png"));
}

QString GaugeWatchPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeWatchPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeWatchPlugin::isContainer() const
{
    return false;
}

QString GaugeWatchPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeWatch\" name=\"gaugeWatch\">\n</widget>\n");
}

QString GaugeWatchPlugin::includeFile() const
{
    return QLatin1String("gaugewatch.h");
}

