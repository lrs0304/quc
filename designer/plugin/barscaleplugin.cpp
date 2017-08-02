#include "../src/barscale.h"
#include "barscaleplugin.h"

#include <QtPlugin>

BarScalePlugin::BarScalePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void BarScalePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool BarScalePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *BarScalePlugin::createWidget(QWidget *parent)
{
    return new BarScale(parent);
}

QString BarScalePlugin::name() const
{
    return QLatin1String("BarScale");
}

QString BarScalePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon BarScalePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/barscale.png"));
}

QString BarScalePlugin::toolTip() const
{
    return QLatin1String("");
}

QString BarScalePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool BarScalePlugin::isContainer() const
{
    return false;
}

QString BarScalePlugin::domXml() const
{
    return QLatin1String("<widget class=\"BarScale\" name=\"barScale\">\n</widget>\n");
}

QString BarScalePlugin::includeFile() const
{
    return QLatin1String("barscale.h");
}

