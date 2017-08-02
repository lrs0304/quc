#include "../src/imageview.h"
#include "imageviewplugin.h"

#include <QtPlugin>

ImageViewPlugin::ImageViewPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ImageViewPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ImageViewPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ImageViewPlugin::createWidget(QWidget *parent)
{
    return new ImageView(parent);
}

QString ImageViewPlugin::name() const
{
    return QLatin1String("ImageView");
}

QString ImageViewPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ImageViewPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/imageview.png"));
}

QString ImageViewPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ImageViewPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ImageViewPlugin::isContainer() const
{
    return false;
}

QString ImageViewPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ImageView\" name=\"imageView\">\n</widget>\n");
}

QString ImageViewPlugin::includeFile() const
{
    return QLatin1String("imageview.h");
}

