#include "../src/imagepower.h"
#include "imagepowerplugin.h"

#include <QtPlugin>

ImagePowerPlugin::ImagePowerPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ImagePowerPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ImagePowerPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ImagePowerPlugin::createWidget(QWidget *parent)
{
    return new ImagePower(parent);
}

QString ImagePowerPlugin::name() const
{
    return QLatin1String("ImagePower");
}

QString ImagePowerPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ImagePowerPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/imagepower.png"));
}

QString ImagePowerPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ImagePowerPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ImagePowerPlugin::isContainer() const
{
    return false;
}

QString ImagePowerPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ImagePower\" name=\"imagePower\">\n</widget>\n");
}

QString ImagePowerPlugin::includeFile() const
{
    return QLatin1String("imagepower.h");
}

