#include "../src/lcdnumber.h"
#include "lcdnumberplugin.h"

#include <QtPlugin>

LcdNumberPlugin::LcdNumberPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void LcdNumberPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LcdNumberPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LcdNumberPlugin::createWidget(QWidget *parent)
{
    return new LcdNumber(parent);
}

QString LcdNumberPlugin::name() const
{
    return QLatin1String("LcdNumber");
}

QString LcdNumberPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon LcdNumberPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/lcdnumber.png"));
}

QString LcdNumberPlugin::toolTip() const
{
    return QLatin1String("");
}

QString LcdNumberPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool LcdNumberPlugin::isContainer() const
{
    return false;
}

QString LcdNumberPlugin::domXml() const
{
    return QLatin1String("<widget class=\"LcdNumber\" name=\"lcdNumber\">\n</widget>\n");
}

QString LcdNumberPlugin::includeFile() const
{
    return QLatin1String("lcdnumber.h");
}

