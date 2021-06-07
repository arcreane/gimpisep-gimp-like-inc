#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int panorama(vector<Mat> images_to_stitch);

bool crop_after_stitching(Mat &image, Mat &output);

bool checkBlackRow(const Mat &gray_image, int y, const Rect &outputRect);

bool checkBlackColumn(const Mat &gray_image, int x, const Rect &outputRect);


/* Cree un panorama a partir d'un vecteur d'images */
cv::Mat panorama(vector<Mat> images_to_stitch) {

    // Initialise le panorama qui sera le resultat
    Mat panorama;

    // Cree le Stitcher qui permettra d'assembler les images pour creer le panorama
    Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::PANORAMA);

    // Assemble les images pour creer le panorama
    Stitcher::Status status = stitcher->stitch(images_to_stitch, panorama);


    // Verifie que l'assemblage et la construction du panorama s'est bien deroule
    if (status != Stitcher::OK) {
        cout << "An error occured while stitching the images! Error: " << int(status) << endl;
        return -1;
    }

    // Retourne le panorama resultant
    return crop_after_stitching(panorama);

}

// Rogne le panorama apres sa construction pour retirer les eventuels bords noirs
bool crop_after_stitching(Mat &image, Mat &output) {

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
    return 0;
}


/* Compte le nombre de pixels noirs sur la ligne et verifie qu'il est inferieur au seuil voulu*/
bool checkBlackRow(const Mat &gray_image, int y, const Rect &outputRect) {
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
bool checkBlackColumn(const Mat &gray_image, int x, const Rect &outputRect) {
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

