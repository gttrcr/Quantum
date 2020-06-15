#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<iostream>

#include"Matrix.h"

#define MAXH 512
#define MAXW 512

const int bytesPerPixel = 3; //rgb
const int fileHeaderSize = 14;
const int infoHeaderSize = 40;

class Frame
{
public:
    Frame(unsigned int height, unsigned int width, std::string imageFileName)
    {
        _height = height;
        _width = width;
        _imageFileName = imageFileName;
    }

    void Demo()
    {
        for (unsigned int i = 0; i < _height; i++)
        {
            for (unsigned int j = 0; j < _width; j++)
            {
                unsigned char r = (unsigned char)((double)i / _height * 255);
                unsigned char g = (unsigned char)((double)j / _width * 255);
                unsigned char b = (unsigned char)(((double)i + j) / (_height + _width) * 255);
                rgb(i, j, r, g, b);
            }
        }

        generateBitmapImage();
        std::cout << "Image OK" << std::endl;
        system(_imageFileName.c_str());
    }

    template<typename T>
    static Frame* CreateFromMatrix(Matrix<_Complex>* matrix, bool open = false)
    {
        unsigned int rPos = 0;
        unsigned int cPos = 0;
        _Complex max = matrix->Max(rPos, cPos);
        std::string name = "frame.bmp";
        Frame* frame = new Frame(MAXH, MAXW, name);
        unsigned int uH = (unsigned int)(MAXH / matrix->GetRows());
        unsigned int uW = (unsigned int)(MAXW / matrix->GetCols());
        for (unsigned int i = 0; i < MAXH; i++)
        {
            for (unsigned int j = 0; j < MAXW; j++)
            {
                unsigned int r = (unsigned int)(i / uH);
                unsigned int c = (unsigned int)(j / uW);
                unsigned char bw = 255.0 * matrix->Get(r, c).Mod() / max.Mod();
                frame->bw(i, j, bw);
            }
        }

        frame->RotateImage();
        frame->RotateImage();
        frame->RotateImage();
        frame->generateBitmapImage();
        
        if (open)
            system(frame->_imageFileName.c_str());

        return frame;
    }

private:
    unsigned int _height;
    unsigned int _width;
    unsigned char _image[MAXH][MAXW][bytesPerPixel];
    std::string _imageFileName;

    void generateBitmapImage()
    {
        unsigned char padding[3] = { 0, 0, 0 };
        int paddingSize = (4 - (_width * bytesPerPixel) % 4) % 4;

        unsigned char* fileHeader = createBitmapFileHeader(paddingSize);
        unsigned char* infoHeader = createBitmapInfoHeader();

        FILE* imageFile = fopen(_imageFileName.c_str(), "wb");

        fwrite(fileHeader, 1, fileHeaderSize, imageFile);
        fwrite(infoHeader, 1, infoHeaderSize, imageFile);

        for (unsigned int i = 0; i < _height; i++)
        {
            fwrite((unsigned char*)_image + (i * _width * bytesPerPixel), bytesPerPixel, _width, imageFile);
            fwrite(padding, 1, paddingSize, imageFile);
        }

        fclose(imageFile);
    }

    //The rotation is 90° clockwise
    void RotateImage()
    {
        for (int i = 0; i < _height / 2; i++)
        {
            for (int j = i; j < _width - i - 1; j++)
            {
                unsigned char r = _image[i][j][2];
                unsigned char g = _image[i][j][1];
                unsigned char b = _image[i][j][0];

                _image[i][j][2] = _image[_height - 1 - j][i][2];
                _image[i][j][1] = _image[_height - 1 - j][i][1];
                _image[i][j][0] = _image[_height - 1 - j][i][0];

                _image[_height - 1 - j][i][2] = _image[_height - 1 - i][_width - 1 - j][2];
                _image[_height - 1 - j][i][1] = _image[_height - 1 - i][_width - 1 - j][1];
                _image[_height - 1 - j][i][0] = _image[_height - 1 - i][_width - 1 - j][0];

                _image[_height - 1 - i][_width - 1 - j][2] = _image[j][_width - 1 - i][2];
                _image[_height - 1 - i][_width - 1 - j][1] = _image[j][_width - 1 - i][1];
                _image[_height - 1 - i][_width - 1 - j][0] = _image[j][_width - 1 - i][0];

                _image[j][_width - 1 - i][2] = r;
                _image[j][_width - 1 - i][1] = g;
                _image[j][_width - 1 - i][0] = b;
            }
        }
    }

    unsigned char* createBitmapFileHeader(int paddingSize)
    {
        int fileSize = fileHeaderSize + infoHeaderSize + (bytesPerPixel * _width + paddingSize) * _height;

        static unsigned char fileHeader[] = {
            0,0, /// signature
            0,0,0,0, /// image file size in bytes
            0,0,0,0, /// reserved
            0,0,0,0, /// start of pixel array
        };

        fileHeader[0] = (unsigned char)('B');
        fileHeader[1] = (unsigned char)('M');
        fileHeader[2] = (unsigned char)(fileSize);
        fileHeader[3] = (unsigned char)(fileSize >> 8);
        fileHeader[4] = (unsigned char)(fileSize >> 16);
        fileHeader[5] = (unsigned char)(fileSize >> 24);
        fileHeader[10] = (unsigned char)(fileHeaderSize + infoHeaderSize);

        return fileHeader;
    }

    unsigned char* createBitmapInfoHeader()
    {
        static unsigned char infoHeader[] = {
            0,0,0,0, /// header size
            0,0,0,0, /// image width
            0,0,0,0, /// image height
            0,0, /// number of color planes
            0,0, /// bits per pixel
            0,0,0,0, /// compression
            0,0,0,0, /// image size
            0,0,0,0, /// horizontal resolution
            0,0,0,0, /// vertical resolution
            0,0,0,0, /// colors in color table
            0,0,0,0, /// important color count
        };

        infoHeader[0] = (unsigned char)(infoHeaderSize);
        infoHeader[4] = (unsigned char)(_width);
        infoHeader[5] = (unsigned char)(_width >> 8);
        infoHeader[6] = (unsigned char)(_width >> 16);
        infoHeader[7] = (unsigned char)(_width >> 24);
        infoHeader[8] = (unsigned char)(_height);
        infoHeader[9] = (unsigned char)(_height >> 8);
        infoHeader[10] = (unsigned char)(_height >> 16);
        infoHeader[11] = (unsigned char)(_height >> 24);
        infoHeader[12] = (unsigned char)(1);
        infoHeader[14] = (unsigned char)(bytesPerPixel * 8);

        return infoHeader;
    }

    void rgb(unsigned int i, unsigned int j, unsigned char r, unsigned char g, unsigned char b)
    {
        *(_image[i][j] + 2) = r;
        *(_image[i][j] + 1) = g;
        *(_image[i][j] + 0) = b;
    }

    void bw(unsigned int i, unsigned int j, unsigned char w)
    {
        *(_image[i][j] + 2) = w;
        *(_image[i][j] + 1) = w;
        *(_image[i][j] + 0) = w;
    }
};