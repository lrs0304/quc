#include "../src/lightbutton.h"
#include "lightbuttonplugin.h"

#include <QtPlugin>

LightButtonPlugin::LightButtonPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void LightButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LightButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LightButtonPlugin::createWidget(QWidget *parent)
{
    return new LightButton(parent);
}

QString LightButtonPlugin::name() const
{
    return QLatin1String("LightButton");
}

QString LightButtonPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon LightButtonPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/lightbutton.png"));
}

QString LightButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString LightButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool LightButtonPlugin::isContainer() const
{
    return false;
}

QString LightButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"LightButton\" name=\"lightButton\">\n</widget>\n");
}

QString LightButtonPlugin::includeFile() const
{
    return QLatin1String("lightbutton.h");
}

