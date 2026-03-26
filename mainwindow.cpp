#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPainter>
#include <QEvent>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->shapeComboBox->addItems({"Circle", "Square", "Rectangle", "Ellipse"});

    QStringList colours = {"Black", "Red", "Green", "Blue", "Yellow", "White", "Gray", "Cyan", "Magenta"};
    ui->penColorComboBox->addItems(colours);
    ui->fillColorComboBox->addItems(colours);

    ui->penWidthSpinBox->setRange(1, 30);
    ui->penWidthSpinBox->setValue(2);
    ui->property1SpinBox->setRange(1, 500);
    ui->property1SpinBox->setValue(80);
    ui->property2SpinBox->setRange(1, 300);
    ui->property2SpinBox->setValue(50);

    // Restore button disabled until a save has been made
    ui->restorePushButton->setEnabled(false);

    ui->displayWidget->installEventFilter(this);

    // ── Auto-load on open ──────────────────────────────────────────
    File::loadFromXml(xmlSavePath, ShapeList::instance(), &shapeParent);

    if (!ShapeList::instance().isEmpty()) {
        currentIndex = 0;
        currentShape = ShapeList::instance().getShape(0);
        ui->displayWidget->update();
    }
}

MainWindow::~MainWindow()
{
    qDebug() << "==============================================";
    qDebug() << "ShapeList singleton contains" << ShapeList::instance().size() << "shape objects";
    qDebug() << "==============================================";

    // Clean up the memento we own on the heap
    delete m_memento;

    delete ui;

    // ── Auto-save on close ─────────────────────────────────────────
    File::saveToXml(xmlSavePath, ShapeList::instance());

    qDebug() << "ShapeList contains" << ShapeList::instance().size() << "shape objects";
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->displayWidget && event->type() == QEvent::Paint)
    {
        if (currentShape)
        {
            QPainter painter(ui->displayWidget);
            painter.setRenderHint(QPainter::Antialiasing);
            currentShape->draw(painter, ui->displayWidget);
        }
        return true;
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::on_createPushButton_clicked()
{
    int penWidth   = ui->penWidthSpinBox->value();
    QColor penColor  = File::colorFromString(ui->penColorComboBox->currentText());
    QColor fillColor = File::colorFromString(ui->fillColorComboBox->currentText());
    int prop1 = ui->property1SpinBox->value();
    int prop2 = ui->property2SpinBox->value();
    QString shape = ui->shapeComboBox->currentText();

    Shape *newShape = nullptr;

    if (shape == "Circle") {
        newShape = new Circle(penWidth, penColor, fillColor, prop1, &shapeParent);
    } else if (shape == "Square") {
        newShape = new Square(penWidth, penColor, fillColor, prop1, &shapeParent);
    } else if (shape == "Rectangle") {
        newShape = new Rectangle(penWidth, penColor, fillColor, prop1, prop2, &shapeParent);
    } else if (shape == "Ellipse") {
        newShape = new Ellipse(penWidth, penColor, fillColor, prop1, prop2, &shapeParent);
    }

    if (newShape) {
        // Add to the singleton ShapeList
        ShapeList::instance().addShape(newShape);
        currentIndex = ShapeList::instance().size() - 1;
        currentShape = newShape;
        ui->displayWidget->update();
    }
}

void MainWindow::on_nextPushButton_clicked()
{
    if (ShapeList::instance().isEmpty()) return;
    currentShape = ShapeList::instance().next(currentIndex);
    ui->displayWidget->update();
}

void MainWindow::on_previousPushButton_clicked()
{
    if (ShapeList::instance().isEmpty()) return;
    currentShape = ShapeList::instance().previous(currentIndex);
    ui->displayWidget->update();
}

// --- Memento: Save ---
// Ask ShapeList to extract the current state into a ShapeListMemento.
// We own the memento on the heap so it survives until a new save or app close.
void MainWindow::on_savePushButton_clicked()
{
    // Delete any previous save before creating a new one
    delete m_memento;
    m_memento = new ShapeListMemento(ShapeList::instance().createMemento());

    ui->restorePushButton->setEnabled(true);
    qDebug() << "MainWindow: state saved —" << ShapeList::instance().size() << "shapes";
}

// --- Memento: Restore ---
// Hand the saved memento back to ShapeList.
// ShapeList deletes the old objects, clears its list, rebuilds from the snapshot.
// We then reset our display to show the first shape.
void MainWindow::on_restorePushButton_clicked()
{
    if (!m_memento) {
        QMessageBox::information(this, "Restore", "No saved state to restore.");
        return;
    }

    ShapeList::instance().restoreFromMemento(*m_memento, shapeParent);

    if (!ShapeList::instance().isEmpty()) {
        currentIndex  = 0;
        currentShape  = ShapeList::instance().getShape(0);
    } else {
        currentIndex = -1;
        currentShape = nullptr;
    }

    ui->displayWidget->update();
    qDebug() << "MainWindow: state restored —" << ShapeList::instance().size() << "shapes";
}
