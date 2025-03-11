#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QVector>
#include <QLine>
#include <QPen>
#include <QMap>
#include "../models/client.h"
#include "../models/curseur.h"

#include "../models/password.h"
#include "../models/curseurwidget.h"
#include "../models/idClient.h"
#include "../models/logHelper.h"


// Classe représentant la zone de dessin, gere le canvas du dessin en lui meme
class DrawingArea : public QWidget {
    Q_OBJECT

public:
    explicit DrawingArea(QWidget *parent = nullptr);
    void setPenColor(const QColor &color);
    void setPenSize(int size);
    void clearCanvas();
    void setClient(Client *client);
    Client *getClient() const;
    void Draw(Curseur c);

private slots:
    void incomingData();
    void AddCursorWidget(int id);


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;


    


private:
    QColor penColor;
    int penSize;
    bool drawing;
    QPoint lastPoint;
    QVector<std::pair<QLine, QPen>> lines;
    Client *client = nullptr;  
    QMap<int, CurseurWidget*> *mapIdCurseur = new QMap<int, CurseurWidget*>(); 

    QMap<int, Curseur> *mapIdPosition = new QMap<int, Curseur>();
    QImage canvas;
    bool backgroundSet = false;
};


class QVBoxLayout;
class QHBoxLayout;
class QComboBox;
class QPushButton;

// Classe représentant la board, gere le canvas drawingSurface et les diffents controles du stylo
class Board : public QWidget {
    Q_OBJECT



public:
    explicit Board(QWidget *parent = nullptr, QString ip = nullptr);
    ~Board();
    DrawingArea *getDrawingArea() const;
    

private slots:
    void changeBrushSize(const QString &size);
    void changeColor();
    void clearBoard();


private:
    void initializeUI();

    DrawingArea *drawingArea;
    QVBoxLayout *mainLayout;
    QHBoxLayout *controlsLayout;
    QComboBox *sizeComboBox;
    QPushButton *colorButton; 
    QPushButton *clearButton;
    Client *client = nullptr; 
};

#endif // BOARD_H