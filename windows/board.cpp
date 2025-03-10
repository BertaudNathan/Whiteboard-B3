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
    //mapIdCurseur->insert(0, new CurseurWidget(this));
    }


void DrawingArea::AddCursorWidget(int id) {
    qDebug() << "ajout curseur " << id;
    CurseurWidget *widget = new CurseurWidget(this);
    if ( !mapIdCurseur->contains(id) ){
        mapIdCurseur->insert(id, widget);
    }
}

void DrawingArea::setPenColor(const QColor &color) {
    penColor = color;
}

void DrawingArea::setPenSize(int size) {
    penSize = size;
}

void DrawingArea::setClient(Client *client) {
    this->client = client;
    bool success = connect(client->getSocket(), &QTcpSocket::readyRead, this, &DrawingArea::incomingData);
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
        lastPoint = event->pos();
        Curseur p;
        p.id = this->client->getId();
        p.x = event->pos().x();
        p.y = event->pos().y();
        p.couleur = penColor.name();
        p.taille = penSize;
        p.drawing = true; 
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        quint8 type = 0x02;
        stream << type;  
        stream << p;
        Draw(p);
        this->getClient()->sendMessage(data);
    }
}

void DrawingArea::incomingData() {
    QByteArray data = this->getClient()->getSocket()->readAll();
    QDataStream stream(&data, QIODevice::ReadOnly);
    //qDebug << "Données reçues:" << data;
    quint8 type;
    stream >> type; // Désérialisation du type de message
    qDebug() <<"type : "<< type;
    if (type ==0x02){
        Curseur c;
        stream >> c;  // Désérialisation du Curseur
        qDebug() << "id " << c.id;
        qDebug() <<"taille " << mapIdCurseur->keys().size();
        CurseurWidget *widget;
        if (mapIdCurseur->contains(c.id)){
            widget = mapIdCurseur->find(c.id).value();
            widget->show();
        }else{
            widget = new CurseurWidget(this);
            widget->show();
            mapIdCurseur->insert(c.id, widget);
        }
        if (c.drawing == true){
            Draw(c);
        }
        widget->move(c.x,c.y);
    }
    if (type == 0x05){
        IdClient idC;
        stream >> idC;
        Client *client = this->getClient();
        client->setId(idC.id);
        qDebug() << "l'id est " << idC.id;
        AddCursorWidget(idC.id);
    }
}

void DrawingArea::Draw(Curseur c) {
    lines.append(std::make_pair(
            QLine(c.x-1,c.y-1 , c.x,c.y ),
            QPen(QColor(c.couleur), c.taille, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
            ));
    QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection);
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event) {
    //qDebug() << "Mouse move";
    Curseur c;
    c.x = event->pos().x();
    c.y = event->pos().y();
    c.id = this->client->getId();
    c.drawing = drawing;
    c.taille = penSize;
    c.couleur = penColor.name();
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    quint8 type = 0x02;
    stream << type;
    stream << c;
    this->getClient()->sendMessage(data);
    
    lastPoint = event->pos(); 

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


Board::Board(QWidget *parent, QString ip) : QWidget(parent) {
    setWindowTitle("Whiteboard");
    setFixedSize(800, 600);
    this->client = new Client();
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
