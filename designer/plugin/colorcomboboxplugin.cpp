#include "../src/colorcombobox.h"
#include "colorcomboboxplugin.h"

#include <QtPlugin>

ColorComboBoxPlugin::ColorComboBoxPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ColorComboBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ColorComboBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ColorComboBoxPlugin::createWidget(QWidget *parent)
{
    return new ColorComboBox(parent);
}

QString ColorComboBoxPlugin::name() const
{
    return QLatin1String("ColorComboBox");
}

QString ColorComboBoxPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ColorComboBoxPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/colorcombobox.png"));
}

QString ColorComboBoxPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ColorComboBoxPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ColorComboBoxPlugin::isContainer() const
{
    return false;
}

QString ColorComboBoxPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ColorComboBox\" name=\"colorComboBox\">\n</widget>\n");
}

QString ColorComboBoxPlugin::includeFile() const
{
    return QLatin1String("colorcombobox.h");
}

