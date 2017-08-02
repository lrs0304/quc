#include "../src/gaugecar.h"
#include "gaugecarplugin.h"

#include <QtPlugin>

GaugeCarPlugin::GaugeCarPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void GaugeCarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeCarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeCarPlugin::createWidget(QWidget *parent)
{
    return new GaugeCar(parent);
}

QString GaugeCarPlugin::name() const
{
    return QLatin1String("GaugeCar");
}

QString GaugeCarPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeCarPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugecar.png"));
}

QString GaugeCarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeCarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeCarPlugin::isContainer() const
{
    return false;
}

QString GaugeCarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeCar\" name=\"gaugeCar\">\n</widget>\n");
}

QString GaugeCarPlugin::includeFile() const
{
    return QLatin1String("gaugecar.h");
}

