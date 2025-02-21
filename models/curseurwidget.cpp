#include "CurseurWidget.h"

CurseurWidget::CurseurWidget(QWidget *parent) : QWidget(parent) {
    setMouseTracking(true); // Détecter le mouvement de la souris sans clic

    // Création du QLabel pour afficher l'image
    imageLabel = new QLabel(this);
    QPixmap pixmap(":cursor.bmp"); // Remplace avec ton image
    pixmap = pixmap.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel->setPixmap(pixmap);
    imageLabel->setFixedSize(pixmap.size());
}

void CurseurWidget::mouseMoveEvent(QMouseEvent *event) {
    if (!imageLabel->isVisible())
        imageLabel->show();
    int x = event->pos().x();
    int y = event->pos().y();

    // Vérifier que l’image reste dans les limites du widget
    int maxX = width() - imageLabel->width();
    int maxY = height() - imageLabel->height();
    x = qBound(0, x, maxX);
    y = qBound(0, y, maxY);

    imageLabel->move(x, y);
}

int *CurseurWidget::getId() {
    return this->id;
}

void CurseurWidget::setId(int *newId) {
    this->id = newId;
}
