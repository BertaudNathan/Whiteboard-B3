#include "board.h"
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>


DrawingArea::DrawingArea(QWidget *parent)
    : QWidget(parent), penColor(Qt::black), penSize(5), drawing(false) {
    setStyleSheet("background-color: white;");
    setFixedSize(700, 500);
    setMouseTracking(true);
    mapIdCurseur->insert(0, new CurseurWidget(this));
}

void DrawingArea::setPenColor(const QColor &color) {
    penColor = color;
}

void DrawingArea::setPenSize(int size) {
    penSize = size;
}

void DrawingArea::setClient(Client *client) {
    qDebug() << "setClient";
    this->client = client;
    bool success = connect(client->getSocket(), &QTcpSocket::readyRead, this, &DrawingArea::incomingData);
    qDebug() << "Connexion au signal readyRead:" << success;

    qDebug() << client->getSocket();
}

Client *DrawingArea::getClient() const {
    return client;
}


void DrawingArea::clearCanvas() {
    lines.clear();
    update();
}





void DrawingArea::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        lines.append(std::make_pair(
            QLine(event->pos().x()-1,event->pos().y()-1 , event->pos().x(),event->pos().y() ),
            QPen(penColor, penSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
            ));
        lastPoint = event->pos();
        Point p;
        p.x = event->pos().x();
        p.y = event->pos().y();
        p.couleur = penColor.name();
        p.taille = penSize;
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        quint8 type = 0x01;
        stream << type;  
        stream << p;
        qDebug() << "debug 1";
        qDebug() << this;
        this->getClient()->sendMessage(data);
        update();
    }
}

void DrawingArea::incomingData() {
    qDebug() << "incomingDraw";
    QByteArray data = this->getClient()->getSocket()->readAll();
    qDebug() << data;
    QDataStream stream(&data, QIODevice::ReadOnly);
    quint8 type;
    stream >> type; // Désérialisation du type de message
    qDebug() << "type = " << type;
    if (type == 0x01){
        Point p;
        stream >> p;  // Désérialisation du Point
        qDebug() << "Point reçu -> X:" << p.x << ", Y:" << p.y << ", Couleur:" << p.couleur << ", Taille:" << p.taille;
        Draw(p);
    } else if (type ==0x02){
        Curseur c;
        stream >> c;  // Désérialisation du Curseur
        CurseurWidget *widget = mapIdCurseur->find(0).value();
        widget->move(c.x,c.y);
    }
}

void DrawingArea::Draw(Point p) {
    qDebug() << p.x-1 << p.y-1;
    lines.append(std::make_pair(
            QLine(p.x-1,p.y-1 , p.x,p.y ),
            QPen(penColor, p.taille, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
            ));
    update();
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event) {
    Curseur c;
    c.x = event->pos().x();
    c.y = event->pos().y();
    c.id = 3;
    c.couleur = penColor.name();
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    quint8 type = 0x02;
    stream << type;
    stream << c;
    this->getClient()->sendMessage(data);
    if (drawing) {
        lines.append(std::make_pair(
            QLine(lastPoint, event->pos()),
            QPen(penColor, penSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
            ));
    lastPoint = event->pos(); 
    }
    
}

void DrawingArea::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawing = false;
    }
}

void DrawingArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    for (const auto &line : lines) {
        painter.setPen(line.second);  
        painter.drawLine(line.first); 
    }
}


Board::Board(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Whiteboard");
    setFixedSize(800, 600);
    this->client = new Client();
    QString ip = "127.0.0.1";
    this->client->connectToServer(ip,8000);
    Password p;
    p.password = "t";
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    quint8 type = 0x03;
    stream << type;
    stream << p;
    this->client->sendMessage(data);
    initializeUI();
}

Board::~Board() {}

void Board::initializeUI() {
    drawingArea = new DrawingArea(this);
    drawingArea->setClient(this->client);

    mainLayout = new QVBoxLayout(this);
    controlsLayout = new QHBoxLayout();
    sizeComboBox = new QComboBox(this);
    sizeComboBox->addItem("5");
    sizeComboBox->addItem("10");
    sizeComboBox->addItem("15");
    sizeComboBox->addItem("20");

    colorButton = new QPushButton("Choose Color", this);
    clearButton = new QPushButton("Clear Board", this);

    QLabel *brushSizeLabel = new QLabel("Brush Size:", this);

    controlsLayout->addWidget(brushSizeLabel);
    controlsLayout->addWidget(sizeComboBox);
    controlsLayout->addWidget(colorButton);
    controlsLayout->addWidget(clearButton);

    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(drawingArea, 0, Qt::AlignCenter);

    connect(sizeComboBox, &QComboBox::currentTextChanged, this, &Board::changeBrushSize);
    connect(colorButton, &QPushButton::clicked, this, &Board::changeColor);
    connect(clearButton, &QPushButton::clicked, this, &Board::clearBoard);
}

void Board::changeBrushSize(const QString &size) {
    bool ok;
    int newSize = size.toInt(&ok);
    if (ok) {
        drawingArea->setPenSize(newSize);
    }
}

void Board::changeColor() {
    QColor color = QColorDialog::getColor(Qt::black, this, "Choose Brush Color");
    if (color.isValid()) {
        drawingArea->setPenColor(color);
    }
}

void Board::clearBoard() {
    drawingArea->clearCanvas();
}
