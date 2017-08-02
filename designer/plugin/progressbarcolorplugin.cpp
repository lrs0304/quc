#include "../src/progressbarcolor.h"
#include "progressbarcolorplugin.h"

#include <QtPlugin>

ProgressBarColorPlugin::ProgressBarColorPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ProgressBarColorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ProgressBarColorPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ProgressBarColorPlugin::createWidget(QWidget *parent)
{
    return new ProgressBarColor(parent);
}

QString ProgressBarColorPlugin::name() const
{
    return QLatin1String("ProgressBarColor");
}

QString ProgressBarColorPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ProgressBarColorPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/progressbarcolor.png"));
}

QString ProgressBarColorPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ProgressBarColorPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ProgressBarColorPlugin::isContainer() const
{
    return false;
}

QString ProgressBarColorPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ProgressBarColor\" name=\"progressBarColor\">\n</widget>\n");
}

QString ProgressBarColorPlugin::includeFile() const
{
    return QLatin1String("progressbarcolor.h");
}

