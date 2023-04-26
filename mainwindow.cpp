#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QMessageBox>

//----------------------------Global Variable----------------------------------//
QGraphicsItem *sourceInputImage;
QGraphicsItem *sourceSecretImage;
//----------------------------------------------------------------------------//

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->saveAsButton->setDisabled(true);
    ui->toHideTextEdit->setPlaceholderText("Saisisser votre texte secret ici...");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openImageButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Load Image"),tr("Images (*.png *.jpg)"));

    if (filename.isEmpty())  {
        return;
    }

    QPixmap pixmap(filename);
    if (! ui->imageGraphicsView->scene()) {
        qDebug() << "No Scene in open button!";
        QGraphicsScene *scene = new QGraphicsScene(this);
        ui->imageGraphicsView->setScene(scene);
        ui->imageGraphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    }

    // Redimensionner l'image à la taille de QGraphicsView
    ui->imageGraphicsView->scene()->addPixmap(pixmap);
    sourceInputImage = ui->imageGraphicsView->scene()->items().first();
    ui->imageGraphicsView->fitInView(ui->imageGraphicsView->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_EncodeButton_clicked()
{

    QString secretText = ui->toHideTextEdit->toPlainText();

    // Convertir la chaîne de caractères en une séquence de bits
    QByteArray secretData = secretText.toUtf8();
    QByteArray binaryData;
    for (int i = 0; i < secretData.size(); ++i) {
        char byte = secretData.at(i);
        for (int j = 0; j < 8; ++j) {
            binaryData.append((byte & 0x80) >> 7);
            byte <<= 1;
        }
    }

    // Récupérer le pixmap de l'image dans QGraphicsView
    //QGraphicsItem *item = ui->imageGraphicsView->scene()->items().first();
    QGraphicsPixmapItem *pixmapItem = dynamic_cast<QGraphicsPixmapItem *>(sourceInputImage);
    if (!pixmapItem) {
        qDebug() << "No pixmap item found in the scene";
        QMessageBox::information(this, "Erreur", "Veuillez charger une image");
        return;
    }
    if(secretText.isEmpty()) {
        QMessageBox::information(this, "Erreur", "Veuillez enter un texte secret");
        return;
    }
    QPixmap pixmap = pixmapItem->pixmap();

    // Convertir le pixmap en QImage pour pouvoir utiliser setPixelColor()
    QImage image = pixmap.toImage();

    // Modifier les bits LSB de chaque pixel de l'image
    int dataIdx = 0;
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor pixelColor = image.pixelColor(x, y);
            if (dataIdx >= binaryData.size()) {
                // Si toutes les données ont été encodées, sortir de la boucle
                break;
            }
            pixelColor.setRed((pixelColor.red() & 0xFE) | binaryData.at(dataIdx++));
            pixelColor.setGreen((pixelColor.green() & 0xFE) | binaryData.at(dataIdx++));
            pixelColor.setBlue((pixelColor.blue() & 0xFE) | binaryData.at(dataIdx++));
            image.setPixelColor(x, y, pixelColor);
        }
        if (dataIdx >= binaryData.size()) {
            // Si toutes les données ont été encodées, sortir de la boucle
            break;
        }
    }

    // Convertir l'image en pixmap pour pouvoir l'afficher dans QGraphicsView
    pixmap = QPixmap::fromImage(image);

    // Afficher l'image modifiée dans QGraphicsView
    pixmapItem->setPixmap(pixmap);
    ui->imageGraphicsView->scene()->addPixmap(pixmap);
    QMessageBox::information(this, "Secret", "Votre message secret a été masquée avec succès !");
    ui->saveAsButton->setDisabled(false);
}


void MainWindow::on_saveAsButton_clicked()
{
    // Récupérer le pixmap modifié de l'image dans QGraphicsView
    //QGraphicsItem *item = ui->imageGraphicsView->scene()->items().first();
    QGraphicsPixmapItem *pixmapItem = dynamic_cast<QGraphicsPixmapItem *>(sourceInputImage);
    if (!pixmapItem) {
        qDebug() << "No pixmap item found in the scene";
        QMessageBox::information(this, "Erreur", "Veuillez charger une image");
        return;
    }
    QPixmap pixmap = pixmapItem->pixmap();

    // Ouvrir un dialogue de sélection de fichier pour permettre à l'utilisateur de choisir où enregistrer l'image
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer sous..."), QString(), tr("Images (*.png *.xpm *.jpg)"));
    if (!fileName.isEmpty()) {
        // Enregistrer le pixmap modifié dans le fichier sélectionné
        pixmap.save(fileName);
    }
}


void MainWindow::on_openImageButtonDecode_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Load Image"),tr("Images (*.png *.jpg)"));

    if (filename.isEmpty())  {
        return;
    }

    QPixmap pixmap(filename);
    if (! ui->imageGraphicsViewDecode->scene()) {
        qDebug() << "No Scene!";
        QGraphicsScene *scene = new QGraphicsScene(this);
        ui->imageGraphicsViewDecode->setScene(scene);
        ui->imageGraphicsViewDecode->setDragMode(QGraphicsView::ScrollHandDrag);
    }
    // Redimensionner l'image à la taille de QGraphicsView
    ui->imageGraphicsViewDecode->scene()->addPixmap(pixmap);
    sourceSecretImage = ui->imageGraphicsViewDecode->scene()->items().first();
    ui->imageGraphicsViewDecode->fitInView(ui->imageGraphicsViewDecode->sceneRect(), Qt::KeepAspectRatio);
}


void MainWindow::on_DecodeButton_clicked()
{
    // Récupérer le pixmap de l'image dans QGraphicsView
    //QGraphicsItem *item = ui->imageGraphicsViewDecode->scene()->items().first();
    QGraphicsPixmapItem *pixmapItem = dynamic_cast<QGraphicsPixmapItem *>(sourceSecretImage);
    if (!pixmapItem) {
        qDebug() << "No pixmap item found in the scene";
        QMessageBox::information(this, "Erreur", "Veuillez charger une image");
        return;
    }
    QPixmap pixmap = pixmapItem->pixmap();

    // Décoder les bits LSB de chaque pixel de l'image pour récupérer les données cachées
    QByteArray binaryData;
    for (int y = 0; y < pixmap.height(); ++y) {
        for (int x = 0; x < pixmap.width(); ++x) {
            QColor pixelColor = pixmap.toImage().pixelColor(x, y);
            binaryData.append(pixelColor.red() & 0x01);
            binaryData.append(pixelColor.green() & 0x01);
            binaryData.append(pixelColor.blue() & 0x01);
        }
    }

    // Convertir la séquence de bits en une chaîne de caractères
    QByteArray secretData;
    for (int i = 0; i < binaryData.size(); i += 8) {
        char byte = 0;
        for (int j = 0; j < 8; ++j) {
            byte <<= 1;
            byte |= binaryData.at(i+j);
        }
        if (byte == '\0')break;
        secretData.append(byte);
    }
    QString secretText = QString::fromUtf8(secretData);

    // Afficher le texte décodé dans la fenêtre de texte
    ui->toRevealTextEdit->setPlainText(secretText);
}

