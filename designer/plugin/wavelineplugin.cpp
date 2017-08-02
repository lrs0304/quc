#include "../src/waveline.h"
#include "wavelineplugin.h"

#include <QtPlugin>

WaveLinePlugin::WaveLinePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void WaveLinePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool WaveLinePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *WaveLinePlugin::createWidget(QWidget *parent)
{
    return new WaveLine(parent);
}

QString WaveLinePlugin::name() const
{
    return QLatin1String("WaveLine");
}

QString WaveLinePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon WaveLinePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/waveline.png"));
}

QString WaveLinePlugin::toolTip() const
{
    return QLatin1String("");
}

QString WaveLinePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool WaveLinePlugin::isContainer() const
{
    return false;
}

QString WaveLinePlugin::domXml() const
{
    return QLatin1String("<widget class=\"WaveLine\" name=\"waveLine\">\n</widget>\n");
}

QString WaveLinePlugin::includeFile() const
{
    return QLatin1String("waveline.h");
}

