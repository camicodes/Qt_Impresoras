#include "impresora.h"
#include "ui_impresora.h"
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QIODevice>
#include <QTextStream>

Impresora::Impresora(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Impresora)
{
    ui->setupUi(this);
    inicializarDatos();
    connect(ui->mnuGuardar, SIGNAL(triggered(bool)),
            this, SLOT(guardar()));
    connect(ui->cmdAgregar, SIGNAL(clicked(bool)),
            this, SLOT(agregar()));
    connect(ui->mnuSalir, SIGNAL(triggered(bool)),
            this, SLOT(close()));
}

Impresora::~Impresora()
{
    delete ui;
}

void Impresora::inicializarDatos()
{

    m_tipo.append(new Datos(1,"Blanco y Negro"));
    m_tipo.append(new Datos(2,"Color"));

    inicializarWidgets();
}

void Impresora::agregar()
{
    //Obtener datos
    QString marca = ui->inMarca->text();
    QString modelo = ui->inModelo->text();
    QString serie = ui->inSerie->text();
    QString contador = ui->inContador->text();
    QString prec = ui->inPrecio->text();
    float precio = prec.toFloat();

    int index = ui->inBNC->currentIndex();
    Datos *d = m_tipo.at(index);

    if (marca == "" || modelo == "" || serie == "" || contador == "" || prec == ""){
        ui->statusbar->showMessage("No se ha ingresado datos para agregar.", 5000);
        return;
    } else{
        ui->statusbar->clearMessage();
    }

    int posicion = ui->outDetalle->rowCount();
    ui->outDetalle->insertRow(posicion);
    ui->outDetalle->setItem(posicion,0, new QTableWidgetItem(marca));
    ui->outDetalle->setItem(posicion,1, new QTableWidgetItem(modelo));
    ui->outDetalle->setItem(posicion,2, new QTableWidgetItem(serie));
    ui->outDetalle->setItem(posicion,3, new QTableWidgetItem(d->tipo()));
    ui->outDetalle->setItem(posicion,4, new QTableWidgetItem(contador));
    ui->outDetalle->setItem(posicion,5, new QTableWidgetItem(QString::number(precio)));

    limpiar();

    total(precio);
}

void Impresora::inicializarWidgets()
{
    for (int i = 0; i< m_tipo.length(); ++i){
        ui->inBNC->addItem(m_tipo.at(i)->tipo());
    }

    QStringList cabecera = {"Marca", "Modelo", "Numero de Serie", "Blanco/Negro - Color", "Contador","Precio"};
    ui->outDetalle->setColumnCount(6);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
}

void Impresora::total(float precio)
{
    m_subtotal += precio;
    precio += precio;
    ui->outTotal->setText(QString::number(m_subtotal));
}

void Impresora::limpiar()
{
    ui->inMarca->setText("");
    ui->inModelo->setText("");
    ui->inPrecio->setText("");
    ui->inSerie->setText("");
    ui->inBNC->setFrame(true);
    ui->inContador->setText("");
}

void Impresora::guardar()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Guardar datos", QDir::home().absolutePath() , "Archivo de Texto (*.txt)");
    QFile data(fileName);
    if (data.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream salida(&data);
        QStringList Lista;
        for( int columna = 0; columna < ui->outDetalle->columnCount(); ++columna ){
            Lista << "\" " + ui->outDetalle->horizontalHeaderItem(columna)->data(Qt::DisplayRole).toString() + "\" ";
        }
        salida << Lista.join(";") << "\n";
        for( int fila = 0; fila < ui->outDetalle->rowCount(); ++fila)
        {
            Lista.clear();
            for( int columna = 0; columna < ui->outDetalle->columnCount(); ++columna){
                QTableWidgetItem* item = ui->outDetalle->item(fila,columna);
                if (!item || item->text().isEmpty()){
                    ui->outDetalle->setItem(fila,columna,new QTableWidgetItem("0"));
                }
                Lista << "\" "+ui->outDetalle->item( fila, columna )->text()+"\" ";
            }
            salida<< Lista.join( ";" )+"\n";
        }
        ui->statusbar->showMessage("Datos almacenados en: " + fileName, 5000);
        data.close();
    }
}
