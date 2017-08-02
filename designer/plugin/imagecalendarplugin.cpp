#include "../src/imagecalendar.h"
#include "imagecalendarplugin.h"

#include <QtPlugin>

ImageCalendarPlugin::ImageCalendarPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ImageCalendarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ImageCalendarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ImageCalendarPlugin::createWidget(QWidget *parent)
{
    return new ImageCalendar(parent);
}

QString ImageCalendarPlugin::name() const
{
    return QLatin1String("ImageCalendar");
}

QString ImageCalendarPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ImageCalendarPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/imagecalendar.png"));
}

QString ImageCalendarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ImageCalendarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ImageCalendarPlugin::isContainer() const
{
    return false;
}

QString ImageCalendarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ImageCalendar\" name=\"imageCalendar\">\n</widget>\n");
}

QString ImageCalendarPlugin::includeFile() const
{
    return QLatin1String("imagecalendar.h");
}

