#include "../src/gaugedial.h"
#include "gaugedialplugin.h"

#include <QtPlugin>

GaugeDialPlugin::GaugeDialPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void GaugeDialPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeDialPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeDialPlugin::createWidget(QWidget *parent)
{
    return new GaugeDial(parent);
}

QString GaugeDialPlugin::name() const
{
    return QLatin1String("GaugeDial");
}

QString GaugeDialPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeDialPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugedial.png"));
}

QString GaugeDialPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeDialPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeDialPlugin::isContainer() const
{
    return false;
}

QString GaugeDialPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeDial\" name=\"gaugeDial\">\n</widget>\n");
}

QString GaugeDialPlugin::includeFile() const
{
    return QLatin1String("gaugedial.h");
}

