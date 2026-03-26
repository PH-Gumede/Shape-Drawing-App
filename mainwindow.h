#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "circle.h"
#include "square.h"
#include "rectangle.h"
#include "ellipse.h"
#include "shapelist.h"
#include "shapelistmemento.h"
#include "file.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_createPushButton_clicked();
    void on_nextPushButton_clicked();
    void on_previousPushButton_clicked();
    void on_savePushButton_clicked();
    void on_restorePushButton_clicked();

private:
    Ui::MainWindow *ui;

    // Parent object owns all heap-allocated Shape objects
    QObject shapeParent;

    // Current shape being displayed and its index in the singleton list
    Shape *currentShape = nullptr;
    int currentIndex = -1;

    // The single backup point — nullptr means no save has been made yet
    ShapeListMemento *m_memento = nullptr;

    //Path for save file
    const QString xmlSavePath = "C:/Users/phgum/Documents/Qt - Code/COS3711_A2-Q1-24660892/shapeXML.xml";
};

#endif // MAINWINDOW_H
