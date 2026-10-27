#ifndef __MANDELBROTSET_H__
#define __MANDELBROTSET_H__

#include"defs.h"
#include<math.h>

typedef struct 
{
    double real;
    double imag;
} Complex;

Complex complex_create(double real, double imag) 
{
    Complex z;
    z.real=real;
    z.imag=imag;
    return z;
}

Complex complex_add(const Complex* a, const Complex* b) 
{
    double realout=a->real+b->real;
    double imagout=a->imag+b->imag;
    return complex_create(realout,imagout);
}

Complex complex_multiply(const Complex* a, const Complex* b) 
{
    double realout=a->real*b->real - a->imag*b->imag;
    double imagout=a->real*b->imag + a->imag*b->real;
    return complex_create(realout,imagout);
}

double complex_magnitude(const Complex* z) 
{
    double num= z->real*z->real + z->imag*z->imag;
    return num;
}

double complex_magnitude_sq(const Complex* z) 
{
    double num=sqrt(complex_magnitude(z));
    return num;
}

int get_mbs_iter(double x, double y) 
{
    const int max_iter = 1500;
    Complex z = complex_create(0, 0);
    Complex c = complex_create(x, y);

    for (int iter = 0; iter < max_iter; iter++) 
    {
        if (complex_magnitude_sq(&z) > 4.0) 
            return iter;
        Complex z_squared = complex_multiply(&z, &z);
        Complex z_squared2 = complex_multiply(&z_squared, &z);
        Complex z_squared3 = complex_multiply(&z_squared2, &z);
        Complex z_squared4 = complex_multiply(&z_squared3, &z);
        Complex z_squared5 = complex_multiply(&z_squared4, &z);
        z = complex_add(&z_squared5, &c);
    }

    return max_iter;
}

void UpdateImageData(ImageState* state)
{
    double X= (state->maxx - state->minx) / state->width;
    double Y = (state->maxy - state->miny) / state->height;
    double angle2 = to_radian(state->angle);
    for (int x = 0; x < state->width; x++) 
    {
        for (int y = 0; y < state->height; y++) 
        {
            double dx = (x - state->width / 2.0) * X;
            double dy = (y - state->height / 2.0) *Y;

            double rx = dx * cos(angle2) + dy * sin(angle2);
            double ry = -dx * sin(angle2) + dy * cos(angle2);

            int iter = get_mbs_iter(rx + state->cx, ry + state->cy);
            state->bmFileData.bmData[y * state->width + x] =iter;
        }
    }
    for (int i = 0; i < NUMCOLORS; i++) 
    {
        if (i == 0) 
        {
            state->bmFileData.bmHeader.colorIdx[i].r = 0;
            state->bmFileData.bmHeader.colorIdx[i].g = 0;
            state->bmFileData.bmHeader.colorIdx[i].b = 0;
        } 
        else if (i < 128) 
        {
            state->bmFileData.bmHeader.colorIdx[i].r = 0;
            state->bmFileData.bmHeader.colorIdx[i].g = 0;
            state->bmFileData.bmHeader.colorIdx[i].b = (i*255)/64;
        } 
        else 
        {
            int X = 40 + ((i - 128) * 50) / 255;
            int Y = (X * 255) / 100;
            
            state->bmFileData.bmHeader.colorIdx[i].r = 0;
            state->bmFileData.bmHeader.colorIdx[i].g = (X * 128) / 100;
            state->bmFileData.bmHeader.colorIdx[i].b = Y;
        }
    }
}

void ChangeCenter(ImageState* state, double newcx, double newcy, int steps)
{
    double dx = (newcx - state->cx) / steps;
    double dy = (newcy - state->cy) / steps;

    for (int i = 0; i < steps; i++)
    {
        state->cx += dx;
        state->cy += dy;
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, &state->bmFileData);
    }
}

void ChangeZoom(ImageState* state, double zoom, int steps)
{
    double zoom_angle = (zoom-1)/steps;

    for (int i = 0; i < steps; i++)
    {
        state->minx /= 1 +zoom_angle *i;
        state->maxx /= 1 +zoom_angle *i;
        state->miny /= 1 +zoom_angle *i;
        state->maxy /= 1 +zoom_angle *i;

        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, &state->bmFileData);
    }
}

void ChangeRotation(ImageState* state, double angle, int steps)
{
    double angle_step = angle/steps;

    for (int i = 0; i < steps; i++)
    {
        state->angle += angle_step;
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, &state->bmFileData);
    }
}

void Hold(ImageState* state, int steps)
{
    for (int i = 0; i < steps; i++)
    {
        WriteBitmapFile(state->image_count++, &state->bmFileData);
    }
}

void ChangeZoomAndRotate(ImageState* state, double target_zoom, double target_angle, int steps) 
{

    double zoom_angle = (target_zoom - 1) / steps;
    double angle_step = target_angle / steps;

    for (int i = 1; i <= steps; i++) 
    {
        state->minx /= 1 +zoom_angle *i;
        state->maxx /= 1 +zoom_angle *i;
        state->miny /= 1 +zoom_angle *i;
        state->maxy /= 1 +zoom_angle *i;

        state->angle += angle_step;

        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, &state->bmFileData);
    }
}

#endif
