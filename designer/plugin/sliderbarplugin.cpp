#include "../src/sliderbar.h"
#include "sliderbarplugin.h"

#include <QtPlugin>

SliderBarPlugin::SliderBarPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void SliderBarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool SliderBarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SliderBarPlugin::createWidget(QWidget *parent)
{
    return new SliderBar(parent);
}

QString SliderBarPlugin::name() const
{
    return QLatin1String("SliderBar");
}

QString SliderBarPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon SliderBarPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/sliderbar.png"));
}

QString SliderBarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString SliderBarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool SliderBarPlugin::isContainer() const
{
    return false;
}

QString SliderBarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"SliderBar\" name=\"sliderBar\">\n</widget>\n");
}

QString SliderBarPlugin::includeFile() const
{
    return QLatin1String("sliderbar.h");
}

