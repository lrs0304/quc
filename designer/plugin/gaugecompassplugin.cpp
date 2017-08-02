#include "../src/gaugecompass.h"
#include "gaugecompassplugin.h"

#include <QtPlugin>

GaugeCompassPlugin::GaugeCompassPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void GaugeCompassPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeCompassPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeCompassPlugin::createWidget(QWidget *parent)
{
    return new GaugeCompass(parent);
}

QString GaugeCompassPlugin::name() const
{
    return QLatin1String("GaugeCompass");
}

QString GaugeCompassPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeCompassPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugecompass.png"));
}

QString GaugeCompassPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeCompassPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeCompassPlugin::isContainer() const
{
    return false;
}

QString GaugeCompassPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeCompass\" name=\"gaugeCompass\">\n</widget>\n");
}

QString GaugeCompassPlugin::includeFile() const
{
    return QLatin1String("gaugecompass.h");
}

