#include "../src/combobox.h"
#include "comboboxplugin.h"

#include <QtPlugin>

ComboBoxPlugin::ComboBoxPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ComboBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ComboBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ComboBoxPlugin::createWidget(QWidget *parent)
{
    return new ComboBox(parent);
}

QString ComboBoxPlugin::name() const
{
    return QLatin1String("ComboBox");
}

QString ComboBoxPlugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon ComboBoxPlugin::icon() const
{
    return QIcon(QLatin1String(":/ico/combobox.png"));
}

QString ComboBoxPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ComboBoxPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ComboBoxPlugin::isContainer() const
{
    return false;
}

QString ComboBoxPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ComboBox\" name=\"comboBox\">\n</widget>\n");
}

QString ComboBoxPlugin::includeFile() const
{
    return QLatin1String("combobox.h");
}

