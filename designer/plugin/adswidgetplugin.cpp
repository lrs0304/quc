#include "../src/adswidget.h"
#include "adswidgetplugin.h"

#include <QtPlugin>

AdsWidgetPlugin::AdsWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void AdsWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool AdsWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *AdsWidgetPlugin::createWidget(QWidget *parent)
{
    return new AdsWidget(parent);
}

QString AdsWidgetPlugin::name() const
{
    return QLatin1String("AdsWidget");
}

QString AdsWidgetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon AdsWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/adswidget.png"));
}

QString AdsWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString AdsWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool AdsWidgetPlugin::isContainer() const
{
    return false;
}

QString AdsWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"AdsWidget\" name=\"adsWidget\">\n</widget>\n");
}

QString AdsWidgetPlugin::includeFile() const
{
    return QLatin1String("adswidget.h");
}

