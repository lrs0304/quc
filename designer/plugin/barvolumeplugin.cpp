#include "../src/barvolume.h"
#include "barvolumeplugin.h"

#include <QtPlugin>

BarVolumePlugin::BarVolumePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void BarVolumePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool BarVolumePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *BarVolumePlugin::createWidget(QWidget *parent)
{
    return new BarVolume(parent);
}

QString BarVolumePlugin::name() const
{
    return QLatin1String("BarVolume");
}

QString BarVolumePlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon BarVolumePlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/barvolume.png"));
}

QString BarVolumePlugin::toolTip() const
{
    return QLatin1String("");
}

QString BarVolumePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool BarVolumePlugin::isContainer() const
{
    return false;
}

QString BarVolumePlugin::domXml() const
{
    return QLatin1String("<widget class=\"BarVolume\" name=\"barVolume\">\n</widget>\n");
}

QString BarVolumePlugin::includeFile() const
{
    return QLatin1String("barvolume.h");
}

