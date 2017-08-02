#include "../src/gaugeprogressbar.h"
#include "gaugeprogressbarplugin.h"

#include <QtPlugin>

GaugeProgressBarPlugin::GaugeProgressBarPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void GaugeProgressBarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeProgressBarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeProgressBarPlugin::createWidget(QWidget *parent)
{
    return new GaugeProgressBar(parent);
}

QString GaugeProgressBarPlugin::name() const
{
    return QLatin1String("GaugeProgressBar");
}

QString GaugeProgressBarPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeProgressBarPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugeprogressbar.png"));
}

QString GaugeProgressBarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeProgressBarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeProgressBarPlugin::isContainer() const
{
    return false;
}

QString GaugeProgressBarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeProgressBar\" name=\"gaugeProgressBar\">\n</widget>\n");
}

QString GaugeProgressBarPlugin::includeFile() const
{
    return QLatin1String("gaugeprogressbar.h");
}

