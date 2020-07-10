#ifndef DATOS_H
#define DATOS_H

#include <QObject>

class Datos : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString tipo READ tipo)
    Q_PROPERTY(QString modelo READ modelo)
    Q_PROPERTY(QString serie READ serie)
    Q_PROPERTY(int codigo READ codigo)
    Q_PROPERTY(QString tipo READ tipo)

public:
    explicit Datos(QObject *parent = nullptr);
    Datos(int codigo, QString tipo);
    //Geters
    QString marca() const;
    QString modelo() const;
    QString serie() const;
    QString tipo() const;
    int codigo() const;
signals:

private:
    QString m_tipo;
    QString m_marca;
    QString m_modelo;
    QString m_serie;
    int m_codigo;

};

#endif // DATOS_H
