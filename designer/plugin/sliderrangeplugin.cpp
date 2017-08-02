#include "../src/sliderrange.h"
#include "sliderrangeplugin.h"

#include <QtPlugin>

SliderRangePlugin::SliderRangePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void SliderRangePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool SliderRangePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SliderRangePlugin::createWidget(QWidget *parent)
{
    return new SliderRange(parent);
}

QString SliderRangePlugin::name() const
{
    return QLatin1String("SliderRange");
}

QString SliderRangePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon SliderRangePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/sliderrange.png"));
}

QString SliderRangePlugin::toolTip() const
{
    return QLatin1String("");
}

QString SliderRangePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool SliderRangePlugin::isContainer() const
{
    return false;
}

QString SliderRangePlugin::domXml() const
{
    return QLatin1String("<widget class=\"SliderRange\" name=\"sliderRange\">\n</widget>\n");
}

QString SliderRangePlugin::includeFile() const
{
    return QLatin1String("sliderrange.h");
}

