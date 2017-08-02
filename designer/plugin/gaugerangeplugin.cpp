#include "../src/gaugerange.h"
#include "gaugerangeplugin.h"

#include <QtPlugin>

GaugeRangePlugin::GaugeRangePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void GaugeRangePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeRangePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeRangePlugin::createWidget(QWidget *parent)
{
    return new GaugeRange(parent);
}

QString GaugeRangePlugin::name() const
{
    return QLatin1String("GaugeRange");
}

QString GaugeRangePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeRangePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugerange.png"));
}

QString GaugeRangePlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeRangePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeRangePlugin::isContainer() const
{
    return false;
}

QString GaugeRangePlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeRange\" name=\"gaugeRange\">\n</widget>\n");
}

QString GaugeRangePlugin::includeFile() const
{
    return QLatin1String("gaugerange.h");
}

