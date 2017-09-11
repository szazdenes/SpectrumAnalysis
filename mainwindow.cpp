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
}

void MainWindow::writeToList(QString text)
{
    if(ui->listWidget->count() > 100)
        ui->listWidget->takeItem(0);

    ui->listWidget->addItem(text);
    ui->listWidget->scrollToBottom();
}

double MainWindow::getIntegralTrapezoidApproach(QMap<double, double> &spectrum)
{
    QList<double> keyList = spectrum.keys();
    qSort(keyList.begin(), keyList.end());

    double result = 0;
    for(int i = 0; i < keyList.size()-1; i++){
        result += 0.5 * (keyList.at(i+1) - keyList.at(i)) * (spectrum[keyList.at(i+1)] + spectrum[keyList.at(i)]);
    }

    return result;
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

void MainWindow::on_pushButton_3_clicked()
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

        QList<double> valueList = spectrumMap.values();
        qSort(valueList.begin(), valueList.end());
        double countMax = valueList.last();

        foreach(double key, spectrumMap.keys())
            spectrumMap[key] /= countMax;

        writeToList("Relative averaged spectrum ready.");
    }
    else
        return;
}

void MainWindow::on_pushButton_4_clicked()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, tr("open"), "../spektrum", QString("*ave.csv"));
    QFile file;
    QFile outFile("integral.csv");
    QTextStream stream(&file), outStream(&outFile);
    double wavelength, count;
    double integral;
    spectrumMap.clear();

    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug("baj");

    if(!fileList.isEmpty()){
        foreach(QString filename, fileList){
            file.setFileName(filename);
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
                qDebug("baj");
            while(!stream.atEnd()){
                QString line = stream.readLine();
                QTextStream lineStream(&line);
                lineStream >> wavelength >> count;
                spectrumMap[wavelength] = count;
            }
            file.close();

            integral = getIntegralTrapezoidApproach(spectrumMap);
            outStream << filename.split("/").last() + "\t" + QString::number(integral, 'f', 4) + "\n";
            spectrumMap.clear();
            writeToList(filename.split("/").last() + " spectrum intergation ready.");
        }
    }
    outFile.close();
}
