#include "../src/gaugenet.h"
#include "gaugenetplugin.h"

#include <QtPlugin>

GaugeNetPlugin::GaugeNetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void GaugeNetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeNetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeNetPlugin::createWidget(QWidget *parent)
{
    return new GaugeNet(parent);
}

QString GaugeNetPlugin::name() const
{
    return QLatin1String("GaugeNet");
}

QString GaugeNetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeNetPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugenet.png"));
}

QString GaugeNetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeNetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeNetPlugin::isContainer() const
{
    return false;
}

QString GaugeNetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeNet\" name=\"gaugeNet\">\n</widget>\n");
}

QString GaugeNetPlugin::includeFile() const
{
    return QLatin1String("gaugenet.h");
}

