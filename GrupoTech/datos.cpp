#include "datos.h"

Datos::Datos(QObject *parent) : QObject(parent)
{
    m_codigo = 0;
    m_tipo = "";
}

Datos::Datos(int codigo, QString tipo)
{
    m_codigo = codigo;
    m_tipo = tipo;
}

QString Datos::marca() const
{
    return m_marca;
}

QString Datos::modelo() const
{
    return m_modelo;
}

QString Datos::serie() const
{
    return m_serie;
}

QString Datos::tipo() const
{
    return m_tipo;
}

int Datos::codigo() const
{
    return m_codigo;
}




