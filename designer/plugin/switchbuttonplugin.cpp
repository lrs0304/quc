#include "../src/switchbutton.h"
#include "switchbuttonplugin.h"

#include <QtPlugin>

SwitchButtonPlugin::SwitchButtonPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void SwitchButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool SwitchButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SwitchButtonPlugin::createWidget(QWidget *parent)
{
    return new SwitchButton(parent);
}

QString SwitchButtonPlugin::name() const
{
    return QLatin1String("SwitchButton");
}

QString SwitchButtonPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon SwitchButtonPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/switchbutton.png"));
}

QString SwitchButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString SwitchButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool SwitchButtonPlugin::isContainer() const
{
    return false;
}

QString SwitchButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"SwitchButton\" name=\"switchButton\">\n</widget>\n");
}

QString SwitchButtonPlugin::includeFile() const
{
    return QLatin1String("switchbutton.h");
}

