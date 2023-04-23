#ifndef KEYVIEWER_H
#define KEYVIEWER_H

#include <QWidget>

using std::vector;

namespace Ui {
class KeyViewer;
}

class KeyViewer : public QWidget
{
    Q_OBJECT

public:
    explicit KeyViewer(QWidget *parent = nullptr);
    ~KeyViewer();
    void setupLocale (std::string locale);
    void setData     (vector<QString>);

private:
    Ui::KeyViewer *ui;
    std::string locale;
    QTimer* timer;

private slots:
    void autoscale ();
};

#endif // KEYVIEWER_H
