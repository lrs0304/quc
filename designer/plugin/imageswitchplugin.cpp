#include "../src/imageswitch.h"
#include "imageswitchplugin.h"

#include <QtPlugin>

ImageSwitchPlugin::ImageSwitchPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ImageSwitchPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ImageSwitchPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ImageSwitchPlugin::createWidget(QWidget *parent)
{
    return new ImageSwitch(parent);
}

QString ImageSwitchPlugin::name() const
{
    return QLatin1String("ImageSwitch");
}

QString ImageSwitchPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ImageSwitchPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/imageswitch.png"));
}

QString ImageSwitchPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ImageSwitchPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ImageSwitchPlugin::isContainer() const
{
    return false;
}

QString ImageSwitchPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ImageSwitch\" name=\"imageSwitch\">\n</widget>\n");
}

QString ImageSwitchPlugin::includeFile() const
{
    return QLatin1String("imageswitch.h");
}

