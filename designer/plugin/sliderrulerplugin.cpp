#include "../src/sliderruler.h"
#include "sliderrulerplugin.h"

#include <QtPlugin>

SliderRulerPlugin::SliderRulerPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void SliderRulerPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool SliderRulerPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SliderRulerPlugin::createWidget(QWidget *parent)
{
    return new SliderRuler(parent);
}

QString SliderRulerPlugin::name() const
{
    return QLatin1String("SliderRuler");
}

QString SliderRulerPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon SliderRulerPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/sliderruler.png"));
}

QString SliderRulerPlugin::toolTip() const
{
    return QLatin1String("");
}

QString SliderRulerPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool SliderRulerPlugin::isContainer() const
{
    return false;
}

QString SliderRulerPlugin::domXml() const
{
    return QLatin1String("<widget class=\"SliderRuler\" name=\"sliderRuler\">\n</widget>\n");
}

QString SliderRulerPlugin::includeFile() const
{
    return QLatin1String("sliderruler.h");
}

