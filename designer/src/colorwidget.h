#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include <QMutex>

class QGridLayout;
class QVBoxLayout;
class QLabel;
class QLineEdit;

#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT ColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWidget(QWidget *parent = 0);
    ~ColorWidget();
    static ColorWidget *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new ColorWidget;
            }
        }

        return self;
    }

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    static ColorWidget *self;
    QClipboard *cp;
    bool pressed;
    QTimer *timer;

    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *labColor;
    QLabel *label;
    QLabel *labWeb;
    QLineEdit *txtWeb;
    QLabel *labRgb;
    QLineEdit *txtRgb;
    QLabel *labPoint;
    QLineEdit *txtPoint;

private Q_SLOTS:
    void showColorValue();
};

#endif // COLORWIDGET_H
