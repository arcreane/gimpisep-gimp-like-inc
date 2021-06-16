//
// Created by yakiimo on 6/15/21.
//

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCheckBox>
#include <QString>
#include <QLabel>
#include <QFileDialog>
#include <QScrollArea>
#include "Panorama.h"

using namespace std;
using namespace cv;

Panorama::Panorama(Workspace &w) : Manipulation(w) {
    this->name = "Panorama";
    this->mustBeCropped = false;
    this->options->setLayout(new QVBoxLayout());
    this->thumbnails = new QWidget();
    this->panelThumbnails = new QScrollArea;

    QPushButton *selectFiles = new QPushButton(("Select files"));
    connect(selectFiles, &QPushButton::released, this, [this]() {
        this->paths = QFileDialog::getOpenFileNames(nullptr, "Open file", "/",
                                                    "Image Files (*.png * jpg *bmp *jpeg * jfif)");
        this->images_to_stitch.clear();
        for (int i = 0; i < paths.length(); i++) {
            string filePath = paths.at(i).toUtf8().constData();
            this->images_to_stitch.push_back(imread(filePath));
        }
        this->displayImagesThumbnails();
        this->options->layout()->addWidget(this->panelThumbnails);
    });

    QPushButton *applyStitching = new QPushButton(tr("Stitch below images"));
    connect(applyStitching, &QPushButton::released, this, [this]() {
        if (images_to_stitch.size() > 1) {
            this->updateImageDisplay();
        } else {
            std::cout << "Can't create a panorama out of less than 2 images" << std::endl;
            QMessageBox error;
            error.setText("Can't create a panorama out of less than 2 images!");
            error.exec();
        }

    });

    QCheckBox *correctStitching = new QCheckBox(tr("Correct stitching"));
    connect(correctStitching, &QCheckBox::stateChanged, this, [this](int state) {
        this->mustBeCropped = state;
    });

    this->options->layout()->addWidget(selectFiles);
    this->options->layout()->addWidget(correctStitching);
    this->options->layout()->addWidget(applyStitching);
    this->options->layout()->setMargin(0);
    this->options->setStyleSheet("QWidget{background-color: green;}");

}

void Panorama::displayImagesThumbnails() {
    delete this->thumbnails;
    delete this->panelThumbnails;
    this->thumbnails = new QWidget();
    this->panelThumbnails = new QScrollArea;
    this->thumbnails->setLayout(new QVBoxLayout());

    for (Mat image : this->images_to_stitch) {
        Mat tmp;
        QLabel *thumbnail = new QLabel();
        thumbnail->setMaximumWidth(this->options->width() - 35);
        cvtColor(image, tmp, COLOR_BGR2RGB);
        QImage qImage = QImage((uchar *) tmp.data, tmp.cols, tmp.rows, tmp.step, QImage::Format_RGB888)
                .scaled(thumbnail->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        thumbnail->setPixmap(QPixmap::fromImage(qImage));
        this->thumbnails->layout()->addWidget(thumbnail);
        this->thumbnails->layout()->setAlignment(thumbnail, Qt::AlignHCenter);
    }
    this->panelThumbnails->setWidget(this->thumbnails);

}

/* Cree un panorama a partir d'un vecteur d'images */
Mat Panorama::stitch(vector<Mat> images_to_stitch) {

    // Initialise le panorama qui sera le resultat
    Mat panorama;
    Mat panorama_cropped;

    // Cree le Stitcher qui permettra d'assembler les images pour creer le panorama
    Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::PANORAMA);

    // Assemble les images pour creer le panorama
    Stitcher::Status status = stitcher->stitch(images_to_stitch, panorama);
    // Verifie que l'assemblage et la construction du panorama s'est bien deroule
    if (status != Stitcher::OK) {
        cout << "An error occured while stitching the images! Error: " << int(status) << endl;
        QMessageBox error;
        error.setText("Can't perform requested manipulation on the current image!");
        error.exec();
    }

    // Retourne le panorama resultant
    if (this->mustBeCropped) {
        crop_after_stitching(panorama, panorama_cropped);
        return panorama_cropped;
    }
    return panorama;

}

// Rogne le panorama apres sa construction pour retirer les eventuels bords noirs
bool Panorama::crop_after_stitching(Mat &image, Mat &output) {

    // Convertit l'image en noir et blanc
    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);

    // Cree un rectangle qui servira de masque pour notre image rognee, il est initialisee
    // de sorte a ce qu'il remplisse toute l'image de depart
    Rect outputRect(0, 0, gray_image.cols, gray_image.rows);

    while (1) {
        bool isTopBorderNotBlack = checkBlackRow(gray_image, outputRect.y, outputRect);
        bool isLeftBorderNotBlack = checkBlackColumn(gray_image, outputRect.x, outputRect);
        bool isBottomBorderNotBlack = checkBlackRow(gray_image, outputRect.y + outputRect.height - 1, outputRect);
        bool isRightBorderNotBlack = checkBlackColumn(gray_image, outputRect.x + outputRect.width - 1, outputRect);

        // S'il y a moins de pixels noirs sur les bords que le nombre maximal de pixels noirs toleres
        // On considere que les bords noirs ont ete retires et on enregistre le resultat
        if (isTopBorderNotBlack && isLeftBorderNotBlack && isBottomBorderNotBlack && isRightBorderNotBlack) {
            Mat outputImage = image(outputRect);
            outputImage.copyTo(output);
            return true;
        }

        // Si le bord superieur de l'image comporte trop de pixels noirs, on translate le rectangle vers le bas
        // Tout en le retrecissant
        if (!isTopBorderNotBlack) {
            outputRect.y++;
            outputRect.height--;
        }


        // Si le bord gauche de l'image comporte trop de pixels noirs, on translate le rectangle vers la droite
        // Tout en le retrecissant
        if (!isLeftBorderNotBlack) {
            outputRect.x++;
            outputRect.width--;
        }

        // Si le bord inferieur de l'image comporte trop de pixels noirs, on retrecit le rectangle
        if (!isBottomBorderNotBlack) {
            outputRect.height--;
        }

        // Si le bord droit de l'image comporte trop de pixels noirs, on retrecit le rectangle
        if (!isRightBorderNotBlack) {
            outputRect.width--;
        }

        // Si le rectangle comporte une dimension negative, on arrete le programme
        if (outputRect.width <= 0 || outputRect.height <= 0) {
            return false;
        }
    }
}


/* Compte le nombre de pixels noirs sur la ligne et verifie qu'il est inferieur au seuil voulu*/
bool Panorama::checkBlackRow(const Mat &gray_image, int y, const Rect &outputRect) {
    int zeroCount = 0;
    // On verifie pour chaque pixel de la ligne s'il est noir ou non
    for (int x = outputRect.x; x < outputRect.width; x++) {
        if (gray_image.at<uchar>(y, x) == 0) {
            zeroCount++;
        }
    }

    // Si le nombre de pixels noirs est inferieur au seuil tolere, on renvoie false
    if ((zeroCount / (float) gray_image.cols) > 0.0001) {
        return false;
    }

    return true;
}

/* Compte le nombre de pixels noirs sur la colonne et verifie qu'il est inferieur au seuil voulu*/
bool Panorama::checkBlackColumn(const Mat &gray_image, int x, const Rect &outputRect) {
    int zeroCount = 0;
    // On verifie pour chaque pixel de la colonne s'il est noir ou non
    for (int y = outputRect.y; y < outputRect.height; y++) {
        if (gray_image.at<uchar>(y, x) == 0) {
            zeroCount++;
        }
    }

    // Si le nombre de pixels noirs est inferieur au seuil tolere, on renvoie false
    if ((zeroCount / (float) gray_image.rows) > 0.0001) {
        return false;
    }

    return true;
}

Mat Panorama::applyManipulation() {
    return stitch(images_to_stitch);
}

void Panorama::onResize() {
    if (!this->images_to_stitch.empty()) {
        displayImagesThumbnails();
        this->options->layout()->addWidget(this->panelThumbnails);
    }
}