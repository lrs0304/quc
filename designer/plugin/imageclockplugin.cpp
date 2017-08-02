#include "../src/imageclock.h"
#include "imageclockplugin.h"

#include <QtPlugin>

ImageClockPlugin::ImageClockPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ImageClockPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ImageClockPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ImageClockPlugin::createWidget(QWidget *parent)
{
    return new ImageClock(parent);
}

QString ImageClockPlugin::name() const
{
    return QLatin1String("ImageClock");
}

QString ImageClockPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ImageClockPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/imageclock.png"));
}

QString ImageClockPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ImageClockPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ImageClockPlugin::isContainer() const
{
    return false;
}

QString ImageClockPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ImageClock\" name=\"imageClock\">\n</widget>\n");
}

QString ImageClockPlugin::includeFile() const
{
    return QLatin1String("imageclock.h");
}

