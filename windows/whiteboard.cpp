#include "whiteboard.h"
#include "ui_whiteboard.h"
//#include "save.h"


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


    // Trouver le widget conteneur (assure-toi qu'il s'appelle bien "widget" ou "boardContainer" dans l'UI)
    /*
    QWidget *container = ui->centralwidget->findChild<QWidget*>("boardContainer");

    if (container) {
        // Créer et afficher le Board dans le conteneur
        board = new Board(container);

        // Appliquer un layout pour qu'il prenne toute la place disponible
        QVBoxLayout *layout = new QVBoxLayout(container);
        layout->setContentsMargins(0, 0, 0, 0);  // Supprime les marges pour un affichage total
        layout->addWidget(board);  // Ajoute le board dans le layout
        container->setLayout(layout);
    }
*/
/*
void MainWindow::on_buttonSave_clicked() {
    Save::saveWidget(this);  // Appel pour sauvegarder le widget actuel (ici la fenêtre principale)
}
*/
WhiteBoard::~WhiteBoard()
{
    delete ui;
}
