#include "../src/ledtext.h"
#include "ledtextplugin.h"

#include <QtPlugin>

LedTextPlugin::LedTextPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void LedTextPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LedTextPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LedTextPlugin::createWidget(QWidget *parent)
{
    return new LedText(parent);
}

QString LedTextPlugin::name() const
{
    return QLatin1String("LedText");
}

QString LedTextPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon LedTextPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/ledtext.png"));
}

QString LedTextPlugin::toolTip() const
{
    return QLatin1String("");
}

QString LedTextPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool LedTextPlugin::isContainer() const
{
    return false;
}

QString LedTextPlugin::domXml() const
{
    return QLatin1String("<widget class=\"LedText\" name=\"ledText\">\n</widget>\n");
}

QString LedTextPlugin::includeFile() const
{
    return QLatin1String("ledtext.h");
}

