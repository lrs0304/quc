#include "../src/gaugesimple.h"
#include "gaugesimpleplugin.h"

#include <QtPlugin>

GaugeSimplePlugin::GaugeSimplePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void GaugeSimplePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeSimplePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeSimplePlugin::createWidget(QWidget *parent)
{
    return new GaugeSimple(parent);
}

QString GaugeSimplePlugin::name() const
{
    return QLatin1String("GaugeSimple");
}

QString GaugeSimplePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeSimplePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugesimple.png"));
}

QString GaugeSimplePlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeSimplePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeSimplePlugin::isContainer() const
{
    return false;
}

QString GaugeSimplePlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeSimple\" name=\"gaugeSimple\">\n</widget>\n");
}

QString GaugeSimplePlugin::includeFile() const
{
    return QLatin1String("gaugesimple.h");
}

