#include "../src/battery.h"
#include "batteryplugin.h"

#include <QtPlugin>

BatteryPlugin::BatteryPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void BatteryPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool BatteryPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *BatteryPlugin::createWidget(QWidget *parent)
{
    return new Battery(parent);
}

QString BatteryPlugin::name() const
{
    return QLatin1String("Battery");
}

QString BatteryPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon BatteryPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/battery.png"));
}

QString BatteryPlugin::toolTip() const
{
    return QLatin1String("");
}

QString BatteryPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool BatteryPlugin::isContainer() const
{
    return false;
}

QString BatteryPlugin::domXml() const
{
    return QLatin1String("<widget class=\"Battery\" name=\"battery\">\n</widget>\n");
}

QString BatteryPlugin::includeFile() const
{
    return QLatin1String("battery.h");
}

