#include "../src/textmovewidget.h"
#include "textmovewidgetplugin.h"

#include <QtPlugin>

TextMoveWidgetPlugin::TextMoveWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void TextMoveWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TextMoveWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TextMoveWidgetPlugin::createWidget(QWidget *parent)
{
    return new TextMoveWidget(parent);
}

QString TextMoveWidgetPlugin::name() const
{
    return QLatin1String("TextMoveWidget");
}

QString TextMoveWidgetPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon TextMoveWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/textmovewidget.png"));
}

QString TextMoveWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString TextMoveWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool TextMoveWidgetPlugin::isContainer() const
{
    return false;
}

QString TextMoveWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"TextMoveWidget\" name=\"textMoveWidget\">\n</widget>\n");
}

QString TextMoveWidgetPlugin::includeFile() const
{
    return QLatin1String("textmovewidget.h");
}

