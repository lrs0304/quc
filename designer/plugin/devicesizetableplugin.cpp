#include "../src/devicesizetable.h"
#include "devicesizetableplugin.h"

#include <QtPlugin>

DeviceSizeTablePlugin::DeviceSizeTablePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void DeviceSizeTablePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool DeviceSizeTablePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *DeviceSizeTablePlugin::createWidget(QWidget *parent)
{
    return new DeviceSizeTable(parent);
}

QString DeviceSizeTablePlugin::name() const
{
    return QLatin1String("DeviceSizeTable");
}

QString DeviceSizeTablePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon DeviceSizeTablePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/devicesizetable.png"));
}

QString DeviceSizeTablePlugin::toolTip() const
{
    return QLatin1String("");
}

QString DeviceSizeTablePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool DeviceSizeTablePlugin::isContainer() const
{
    return false;
}

QString DeviceSizeTablePlugin::domXml() const
{
    return QLatin1String("<widget class=\"DeviceSizeTable\" name=\"deviceSizeTable\">\n</widget>\n");
}

QString DeviceSizeTablePlugin::includeFile() const
{
    return QLatin1String("devicesizetable.h");
}

