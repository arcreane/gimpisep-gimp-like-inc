using namespace std;
using namespace cv;

Mat changeBrightness_matrix( Mat imageInput, double percentChange) {
    percentChange = (percentChange/100)*260; // On converti le pourcentage en valeur scalaire (260 blanc et -260 noir)
    Mat new_image;
    new_image = imageInput + Scalar(percentChange,percentChange,percentChange);
    return new_image;
}