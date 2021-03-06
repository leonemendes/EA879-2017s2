
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "imageprocessing.h"

#include <FreeImage.h>

/*
imagem abrir_imagem(char *nome_do_arquivo);
void salvar_imagem(char *nome_do_arquivo);
void liberar_imagem(imagem *i);
 */

imagem abrir_imagem(char *nome_do_arquivo) {
  FIBITMAP *bitmapIn;
  int x, y;
  RGBQUAD color;
  imagem I;

  bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

  if (bitmapIn == 0) {
    printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
  } else {
    printf("Arquivo lido corretamente!\n");
   }

  x = FreeImage_GetWidth(bitmapIn);
  y = FreeImage_GetHeight(bitmapIn);

  I.width = x;
  I.height = y;
  I.r = malloc(sizeof(float) * x * y);
  I.g = malloc(sizeof(float) * x * y);
  I.b = malloc(sizeof(float) * x * y);

   for (int i=0; i<x; i++) {
     for (int j=0; j <y; j++) {
      int idx;
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      idx = i + (j*x);

      I.r[idx] = color.rgbRed;
      I.g[idx] = color.rgbGreen;
      I.b[idx] = color.rgbBlue;
    }
   }
  return I;

}

void liberar_imagem(imagem *I) {
  free(I->r);
  free(I->g);
  free(I->b);
}

void salvar_imagem(char *nome_do_arquivo, imagem *I) {
  FIBITMAP *bitmapOut;
  RGBQUAD color;

  printf("Salvando imagem %d por %d...\n", I->width, I->height);
  bitmapOut = FreeImage_Allocate(I->width, I->height, 24, 0, 0, 0);

   for (int i=0; i<I->width; i++) {
     for (int j=0; j<I->height; j++) {
      int idx;

      idx = i + (j*I->width);
      color.rgbRed = I->r[idx];
      color.rgbGreen = I->g[idx];
      color.rgbBlue = I->b[idx];

      FreeImage_SetPixelColor(bitmapOut, i, j, &color);
    }
  }

  FreeImage_Save(FIF_JPEG, bitmapOut, nome_do_arquivo, JPEG_DEFAULT);
}

void brilho(imagem *I, float valor) {

		for (int i=0; i<((I->width) * (I->height)); i++) {
   		I->r[i] = I->r[i]*valor;
   		if(I->r[i] > 255.0) I->r[i] = 255.0;
   		I->g[i] = I->g[i]*valor;
   		if(I->g[i] > 255.0) I->g[i] = 255.0;
   		I->b[i] = I->b[i]*valor;
   		if(I->b[i] > 255.0) I->b[i] = 255.0;
   	}
}

void valor_maximo(imagem *I) {
float R = 0.0, G = 0.0, B = 0.0, Rmax = 0.0, Gmax = 0.0, Bmax = 0.0, max = 0.0;

		for (int i=0; i<((I->width) * (I->height)); i++) {
			R = I->r[i];
			G = I->g[i];
			B = I->b[i];
			
			if (sqrt(R*R+G*G+B*B) > max) {
				max = sqrt(R*R+G*G+B*B);
				Rmax = R;
				Gmax = G;
				Bmax = B;
			}
   	}
	
   	printf("Valor máximo: R = %f, G = %f, B = %f, MAX = %f\n", Rmax, Gmax, Bmax, max);
}
  
