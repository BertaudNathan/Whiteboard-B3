#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "board.h"
#include "ui_whiteboard.h"


namespace Ui {
class WhiteBoard;
}

class WhiteBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit WhiteBoard(QWidget *parent = nullptr, QString ip = "");
    ~WhiteBoard();

private slots:
    void saveDrawing();

private:
    Ui::WhiteBoard *ui;
    Board *board;
};

#endif // WHITEBOARD_H
