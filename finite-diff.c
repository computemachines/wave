#include <stdio.h>
#include <math.h>
#include "lib/BMP.h"

#define N (1366)
#define M (768)

typedef struct {
  int r;
  int g;
  int b;
} Color_t;

Color_t
Color_new(int r, int g, int b)
{
  Color_t c;
  c.r = r;
  c.g = g;
  c.b = b;
  return c;
}

double last[N][M];
double current[N][M];
double new[N][M];

long
colorToI(Color_t c)
{
  return c.r*0x010000+c.g*0x000100+c.b*0x000001;
}

Color_t
interpolate(Color_t a, Color_t b, float t) // 0 < t < 1
{
  Color_t c;
  if(t > 1)
    t = 1;
  else if(t < 0)
    t = 0;    

  c.r = a.r*(t-1)+b.r*t;
  c.g = a.g*(t-1)+b.g*t;
  c.b = a.b*(t-1)+b.b*t;
  return c;
}

double sq(double i)
{
  return i*i;
}

float
c(int i, int j)
{
  float R = 212.5;
  float c = 0.1;
  if(sq(i-112.5)+sq(j-M/2) < sq(R)){
    if(sq(i-487.5)+sq(j-M/2) < sq(R)){
      c = 0.5*c;
    }
  }
  return c;
}

void
draw(BMP* im)
{
  for(int i = 0; i < N; i ++){
    for(int j = 0; j < M; j ++){
      Color_t blueish = interpolate(Color_new(0,0,255),
				    Color_new(0,0,0),
				    c(i,j)/0.1);
	  BMP_point (im, i, j, colorToI(interpolate(blueish, 
						    Color_new(255,255,255),
						    (current[i][j]+1)/4)));
    }
  }
}

void
rotate()
{
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      last[i][j] = current[i][j];
      current[i][j] = new[i][j];
    }
  }
}

void
step()
{
  for(int i = 1; i < N-1; i++){
    for(int j = 1; j < M-1; j++){
      new[i][j] = 2*current[i][j] - last[i][j] + c(i, j)*(current[i][j+1] - 2*current[i][j] + current[i][j-1] + current[i+1][j] - 2*current[i][j] + current[i-1][j]);
    }
  }
  rotate();
}

int t = 0;

void
IC()
{
  /* for(int i = 50; i < 150; i ++){ */
  /*   for(int j = 0; j < M; j++){ */
  /*     new[i][j] = last[i][j] = 1.0; */
  /*   } */
  /* } */
}

void
BC()
{
  for(int j = 0; j < M; j++){
    current[0][j] = last[0][j] = sin(t/10-sq(j-M/2)/1800)*exp(-sq(j-M/2)/800);
  }
}

void
loop()
{
  t ++;

  char filename[30] = {0};
  sprintf(filename, "images/f%06d.bmp", t);
  printf(filename);
  printf("\n");

  BMP* im = BMP_new (N, M);
  BMP_clear (im, colorToI(interpolate(Color_new(0,0,0),
				      Color_new(255,255,255),
				      0.5)));
  step();
  BC();

  draw(im);
  

  BMP_write(im, filename);
  BMP_delete (im);
}

int
main(int argc, char **argv)
{

  IC();
  while(1){
    loop();
  }
}

