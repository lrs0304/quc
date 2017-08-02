#include "../src/lednumber.h"
#include "lednumberplugin.h"

#include <QtPlugin>

LedNumberPlugin::LedNumberPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void LedNumberPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LedNumberPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LedNumberPlugin::createWidget(QWidget *parent)
{
    return new LedNumber(parent);
}

QString LedNumberPlugin::name() const
{
    return QLatin1String("LedNumber");
}

QString LedNumberPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon LedNumberPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/lednumber.png"));
}

QString LedNumberPlugin::toolTip() const
{
    return QLatin1String("");
}

QString LedNumberPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool LedNumberPlugin::isContainer() const
{
    return false;
}

QString LedNumberPlugin::domXml() const
{
    return QLatin1String("<widget class=\"LedNumber\" name=\"ledNumber\">\n</widget>\n");
}

QString LedNumberPlugin::includeFile() const
{
    return QLatin1String("lednumber.h");
}

