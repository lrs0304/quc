#include "../src/wavedouble.h"
#include "wavedoubleplugin.h"

#include <QtPlugin>

WaveDoublePlugin::WaveDoublePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void WaveDoublePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool WaveDoublePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *WaveDoublePlugin::createWidget(QWidget *parent)
{
    return new WaveDouble(parent);
}

QString WaveDoublePlugin::name() const
{
    return QLatin1String("WaveDouble");
}

QString WaveDoublePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon WaveDoublePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/wavedouble.png"));
}

QString WaveDoublePlugin::toolTip() const
{
    return QLatin1String("");
}

QString WaveDoublePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool WaveDoublePlugin::isContainer() const
{
    return false;
}

QString WaveDoublePlugin::domXml() const
{
    return QLatin1String("<widget class=\"WaveDouble\" name=\"waveDouble\">\n</widget>\n");
}

QString WaveDoublePlugin::includeFile() const
{
    return QLatin1String("wavedouble.h");
}

