#include "whiteboard.h"
#include "ui_whiteboard.h"

WhiteBoard::WhiteBoard(QWidget *parent, QString ip) : QMainWindow(parent)
    , ui(new Ui::WhiteBoard)
{

    ui->setupUi(this);


    QWidget *container = ui->boardContainer;

    if (container) {
        QVBoxLayout *layout = new QVBoxLayout(container);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        board = new Board(container,ip);
        layout->addWidget(board);
        container->setLayout(layout);
    }
    connect(ui->buttonSave, &QPushButton::clicked, this, &WhiteBoard::saveDrawing);

}



void WhiteBoard::saveDrawing() {
    QWidget *drawingAreaWidget = board->getDrawingArea(); 

    QPixmap pixmap(drawingAreaWidget->size());

    drawingAreaWidget->render(&pixmap); 

    QString fileName = QFileDialog::getSaveFileName(this, "Save Drawing", "", "JPEG Files (.jpg.jpeg)");

    if (!fileName.isEmpty()) {

        if (!pixmap.save(fileName, "JPEG")) {

            QMessageBox::critical(this, "Error", "Failed to save the drawing.");
        }
    }
}

WhiteBoard::~WhiteBoard()
{
    delete ui;
}
