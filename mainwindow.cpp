#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, tr("open"), "/home/denes/Documents/Labor/SpectrumAnalysis/spektrum_hordó");
    QFile file;
    QTextStream stream(&file);
    double wavelength, count, num = 0;
    spectrumMap.clear();

    if(!fileList.isEmpty()){
        foreach(QString filename, fileList){

            file.setFileName(filename);

            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
                qDebug("baj");

            while(!stream.atEnd()){
                QString line = stream.readLine();
                QTextStream lineStream(&line);
                lineStream >> wavelength >> count;
                spectrumMap[wavelength] += count;
            }

            file.close();

            num++;
        }
        foreach(double key, spectrumMap.keys())
            spectrumMap[key] /= num;
        writeToList("Spectrum averaging ready.");
    }
    else
        return;

    qDebug("alma");
}

void MainWindow::writeToList(QString text)
{
    if(ui->listWidget->count() > 100)
        ui->listWidget->takeItem(0);

    ui->listWidget->addItem(text);
    ui->listWidget->scrollToBottom();
}

void MainWindow::on_pushButton_2_clicked()
{
    QFile outFile(QFileDialog::getSaveFileName(this, tr("save"), "/home/denes/Documents/Labor/SpectrumAnalysis/spektrum_hordó"));
    if(!outFile.fileName().contains(".csv")) outFile.setFileName(outFile.fileName() + ".csv");
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug("baj");
    QTextStream out(&outFile);
    foreach(double key, spectrumMap.keys())
        out << QString::number(key) + "\t" + QString::number(spectrumMap[key]) + "\n";
    outFile.close();
    writeToList(outFile.fileName() + " file written.");
}
