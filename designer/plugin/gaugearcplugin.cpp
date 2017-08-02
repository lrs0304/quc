#include "../src/gaugearc.h"
#include "gaugearcplugin.h"

#include <QtPlugin>

GaugeArcPlugin::GaugeArcPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void GaugeArcPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeArcPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeArcPlugin::createWidget(QWidget *parent)
{
    return new GaugeArc(parent);
}

QString GaugeArcPlugin::name() const
{
    return QLatin1String("GaugeArc");
}

QString GaugeArcPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeArcPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugearc.png"));
}

QString GaugeArcPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeArcPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeArcPlugin::isContainer() const
{
    return false;
}

QString GaugeArcPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeArc\" name=\"gaugeArc\">\n</widget>\n");
}

QString GaugeArcPlugin::includeFile() const
{
    return QLatin1String("gaugearc.h");
}

