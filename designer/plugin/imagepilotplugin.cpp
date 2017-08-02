#include "../src/imagepilot.h"
#include "imagepilotplugin.h"

#include <QtPlugin>

ImagePilotPlugin::ImagePilotPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ImagePilotPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ImagePilotPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ImagePilotPlugin::createWidget(QWidget *parent)
{
    return new ImagePilot(parent);
}

QString ImagePilotPlugin::name() const
{
    return QLatin1String("ImagePilot");
}

QString ImagePilotPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ImagePilotPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/imagepilot.png"));
}

QString ImagePilotPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ImagePilotPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ImagePilotPlugin::isContainer() const
{
    return false;
}

QString ImagePilotPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ImagePilot\" name=\"imagePilot\">\n</widget>\n");
}

QString ImagePilotPlugin::includeFile() const
{
    return QLatin1String("imagepilot.h");
}

