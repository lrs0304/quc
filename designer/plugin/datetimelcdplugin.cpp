#include "../src/datetimelcd.h"
#include "datetimelcdplugin.h"

#include <QtPlugin>

DateTimeLcdPlugin::DateTimeLcdPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void DateTimeLcdPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool DateTimeLcdPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *DateTimeLcdPlugin::createWidget(QWidget *parent)
{
    return new DateTimeLcd(parent);
}

QString DateTimeLcdPlugin::name() const
{
    return QLatin1String("DateTimeLcd");
}

QString DateTimeLcdPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon DateTimeLcdPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/datetimelcd.png"));
}

QString DateTimeLcdPlugin::toolTip() const
{
    return QLatin1String("");
}

QString DateTimeLcdPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool DateTimeLcdPlugin::isContainer() const
{
    return false;
}

QString DateTimeLcdPlugin::domXml() const
{
    return QLatin1String("<widget class=\"DateTimeLcd\" name=\"dateTimeLcd\">\n</widget>\n");
}

QString DateTimeLcdPlugin::includeFile() const
{
    return QLatin1String("datetimelcd.h");
}

