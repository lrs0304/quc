#include "../src/gaugeclock.h"
#include "gaugeclockplugin.h"

#include <QtPlugin>

GaugeClockPlugin::GaugeClockPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void GaugeClockPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeClockPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeClockPlugin::createWidget(QWidget *parent)
{
    return new GaugeClock(parent);
}

QString GaugeClockPlugin::name() const
{
    return QLatin1String("GaugeClock");
}

QString GaugeClockPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeClockPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugeclock.png"));
}

QString GaugeClockPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeClockPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeClockPlugin::isContainer() const
{
    return false;
}

QString GaugeClockPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeClock\" name=\"gaugeClock\">\n</widget>\n");
}

QString GaugeClockPlugin::includeFile() const
{
    return QLatin1String("gaugeclock.h");
}

