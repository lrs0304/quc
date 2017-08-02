#include "../src/gaugeround.h"
#include "gaugeroundplugin.h"

#include <QtPlugin>

GaugeRoundPlugin::GaugeRoundPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void GaugeRoundPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeRoundPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeRoundPlugin::createWidget(QWidget *parent)
{
    return new GaugeRound(parent);
}

QString GaugeRoundPlugin::name() const
{
    return QLatin1String("GaugeRound");
}

QString GaugeRoundPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon GaugeRoundPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/gaugeround.png"));
}

QString GaugeRoundPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeRoundPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeRoundPlugin::isContainer() const
{
    return false;
}

QString GaugeRoundPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GaugeRound\" name=\"gaugeRound\">\n</widget>\n");
}

QString GaugeRoundPlugin::includeFile() const
{
    return QLatin1String("gaugeround.h");
}

