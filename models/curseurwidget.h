#ifndef CURSEURWIDGET_H
#define CURSEURWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>


//widget du curseur bougeant sur le canvas
class CurseurWidget : public QWidget {
    Q_OBJECT


public:
    explicit CurseurWidget(QWidget *parent = nullptr);
    int *getId();
    void setId(int *newId);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QLabel *imageLabel;
    int *id;
};

#endif // CURSEURWIDGET_H
