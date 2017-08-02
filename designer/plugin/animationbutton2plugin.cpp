#include "../src/animationbutton2.h"
#include "animationbutton2plugin.h"

#include <QtPlugin>

AnimationButton2Plugin::AnimationButton2Plugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void AnimationButton2Plugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool AnimationButton2Plugin::isInitialized() const
{
    return m_initialized;
}

QWidget *AnimationButton2Plugin::createWidget(QWidget *parent)
{
    return new AnimationButton2(parent);
}

QString AnimationButton2Plugin::name() const
{
    return QLatin1String("AnimationButton2");
}

QString AnimationButton2Plugin::group() const
{
    return QLatin1String("Quc Widgets");
}

QIcon AnimationButton2Plugin::icon() const
{
    return QIcon(QLatin1String(":/ico/animationbutton2.png"));
}

QString AnimationButton2Plugin::toolTip() const
{
    return QLatin1String("");
}

QString AnimationButton2Plugin::whatsThis() const
{
    return QLatin1String("");
}

bool AnimationButton2Plugin::isContainer() const
{
    return false;
}

QString AnimationButton2Plugin::domXml() const
{
    return QLatin1String("<widget class=\"AnimationButton2\" name=\"animationButton2\">\n</widget>\n");
}

QString AnimationButton2Plugin::includeFile() const
{
    return QLatin1String("animationbutton2.h");
}

