#include "../src/gaugespeed.h"
#include "gaugespeedplugin.h"

#include <QtPlugin>

GaugeSpeedPlugin::GaugeSpeedPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void GaugeSpeedPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeSpeedPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeSpeedPlugin::createWidget(QWidget *parent)
{
    return new GaugeSpeed(parent);
}

QString GaugeSpeedPlugin::name() const
{
    return QLatin1String("GaugeSpeed");
}

QString GaugeSpeedPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeSpeedPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugespeed.png"));
}

QString GaugeSpeedPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeSpeedPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeSpeedPlugin::isContainer() const
{
    return false;
}

QString GaugeSpeedPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeSpeed\" name=\"gaugeSpeed\">\n</widget>\n");
}

QString GaugeSpeedPlugin::includeFile() const
{
    return QLatin1String("gaugespeed.h");
}

