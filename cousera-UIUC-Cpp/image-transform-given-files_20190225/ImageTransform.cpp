#include <iostream>
#include <cmath>
#include <cstdlib>

#include "uiuc/PNG.h"
#include "uiuc/HSLAPixel.h"
#include "ImageTransform.h"

/* ******************
(Begin multi-line comment...)

Write your name and email address in the comment space here:

Name:
Email:

(...end multi-line comment.)
******************** */

using uiuc::PNG;
using uiuc::HSLAPixel;
using namespace std;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {

  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);
      double dist = sqrt((x-centerX)*(x-centerX)+(y-centerY)*(y-centerY));
      if(dist<=160){
        pixel.l = pixel.l*(1-dist/200);
      }
      else{
        pixel.l = pixel.l*0.2;  // maximum 80% decrease
      }
      
    }
  }


  return image;
  
}
 

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.
      
      // The hue of every pixel should be set to one or the other of these two hue values, 
      // based on whether the pixel's original hue
      // value is closer to Illini Orange(11) or Illini Blue(216).
      double distOrange = 0;    // the distance
      double distBlue = 0;
      if(pixel.h<11){
        distOrange = 11-pixel.h < 360+pixel.h-11?(11-pixel.h):(360+pixel.h-11);
      }
      else{
        distOrange = 360-pixel.h+11<pixel.h-11?(360-pixel.h+11):(pixel.h-11);
      }

      if(pixel.h<216){
        distBlue = 216-pixel.h < 360+pixel.h-216?(216-pixel.h):(360+pixel.h-216);
      }
      else{
        distBlue = 360-pixel.h+216<pixel.h-216?(360-pixel.h+216):(pixel.h-216);
      }

      pixel.h = distBlue<distOrange?216.0:11.0;   // choose hue based on the distance

      
    }
  }

  return image;
}
 

/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs, which is the base image.
* @param secondImage The second of the two PNGs, which acts as the stencil.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
  unsigned int xrange = firstImage.width()<secondImage.width()?firstImage.width():secondImage.width();
  unsigned int yrange = firstImage.height()<secondImage.height()?firstImage.height():secondImage.height();
  // cout<<"xrange="<<xrange<<endl;
  // cout<<"yrange="<<yrange<<endl;
  for(unsigned int x=0;x<xrange;x++){
    for(unsigned int y=0;y<yrange;y++){
      HSLAPixel & secondPixel = secondImage.getPixel(x, y);
      if(secondPixel.l>0.5){
        // color white
        // cout<<"x="<<x<<"y="<<y<<endl;
        HSLAPixel & firstPixel = firstImage.getPixel(x, y);
        if(firstPixel.l<=0.8){
          firstPixel.l+= 0.2;
        }
        else{
          firstPixel.l = 1.0;
        }

      }
    }
  }

  return firstImage;
}
