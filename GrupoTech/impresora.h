#ifndef IMPRESORA_H
#define IMPRESORA_H

#include <QMainWindow>
#include "datos.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Impresora; }
QT_END_NAMESPACE

class Impresora : public QMainWindow
{
    Q_OBJECT

public:
    Impresora(QWidget *parent = nullptr);
    ~Impresora();

private:
    Ui::Impresora *ui;
    QList<Datos*> m_tipo;
    Datos *datos;
    float m_subtotal;
    void inicializarDatos();
    void inicializarWidgets();
    void total(float precio);
    void limpiar();

public slots:
    void guardar();
    void agregar();

};
#endif // IMPRESORA_H
