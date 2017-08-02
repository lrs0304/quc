#include "../src/wavebar.h"
#include "wavebarplugin.h"

#include <QtPlugin>

WaveBarPlugin::WaveBarPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void WaveBarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool WaveBarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *WaveBarPlugin::createWidget(QWidget *parent)
{
    return new WaveBar(parent);
}

QString WaveBarPlugin::name() const
{
    return QLatin1String("WaveBar");
}

QString WaveBarPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon WaveBarPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/wavebar.png"));
}

QString WaveBarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString WaveBarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool WaveBarPlugin::isContainer() const
{
    return false;
}

QString WaveBarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"WaveBar\" name=\"waveBar\">\n</widget>\n");
}

QString WaveBarPlugin::includeFile() const
{
    return QLatin1String("wavebar.h");
}

