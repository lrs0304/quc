#include "../src/iconeditor.h"
#include "iconeditorplugin.h"

#include <QtPlugin>

IconEditorPlugin::IconEditorPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void IconEditorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool IconEditorPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *IconEditorPlugin::createWidget(QWidget *parent)
{
    return new IconEditor(parent);
}

QString IconEditorPlugin::name() const
{
    return QLatin1String("IconEditor");
}

QString IconEditorPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon IconEditorPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/iconeditor.png"));
}

QString IconEditorPlugin::toolTip() const
{
    return QLatin1String("");
}

QString IconEditorPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool IconEditorPlugin::isContainer() const
{
    return false;
}

QString IconEditorPlugin::domXml() const
{
    return QLatin1String("<widget class=\"IconEditor\" name=\"iconEditor\">\n</widget>\n");
}

QString IconEditorPlugin::includeFile() const
{
    return QLatin1String("iconeditor.h");
}

