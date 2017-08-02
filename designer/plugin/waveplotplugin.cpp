#include "../src/waveplot.h"
#include "waveplotplugin.h"

#include <QtPlugin>

WavePlotPlugin::WavePlotPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void WavePlotPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool WavePlotPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *WavePlotPlugin::createWidget(QWidget *parent)
{
    return new WavePlot(parent);
}

QString WavePlotPlugin::name() const
{
    return QLatin1String("WavePlot");
}

QString WavePlotPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon WavePlotPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/waveplot.png"));
}

QString WavePlotPlugin::toolTip() const
{
    return QLatin1String("");
}

QString WavePlotPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool WavePlotPlugin::isContainer() const
{
    return false;
}

QString WavePlotPlugin::domXml() const
{
    return QLatin1String("<widget class=\"WavePlot\" name=\"waveWidget\">\n</widget>\n");
}

QString WavePlotPlugin::includeFile() const
{
    return QLatin1String("waveplot.h");
}

