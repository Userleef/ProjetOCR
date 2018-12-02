#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "parser.h"
#include "xor.h"

void add_neurone(float v, size_t c, float b)
{
  Neurone neurone;
  neurone.value = v;
  neurone.couche = c;
  neurone.nbE = 0;
  neurone.nbS = 0;
  neurone.bias = 0;
  neurone.hasBias = b;
  neurone.dz = 0;
  n[nbNeurones] = neurone;
  nbNeurones += 1;
}


void init_weigths()
{
  for (size_t j = 0; j < nbNeurones; j++) {
      for (size_t i = 0; i < nbNeurones; i++) {
        if(n[i].couche == n[j].couche - 1)
        {
          n[j].weightE[n[j].nbE] = 0;
          n[j].neuronesE[n[j].nbE] = i;
          n[j].nbE += 1;
        }
        if(n[i].couche == n[j].couche + 1)
        {
          n[j].weightS[n[j].nbS] = 0;
          n[j].neuronesS[n[j].nbS] = i;
          n[j].nbS += 1;
        }
      }
  }
}


void init_network(size_t nI, size_t lH, size_t nO)
{
  nbNeurones = 0;
  layer0 = nI;
  lO = nO;
  for (size_t i = 0; i < nI; i++) {
    add_neurone(0, 0, 0);
  }
  for (size_t i = 0; i < lH; i++) {
      add_neurone(0.5f, 1, 1);
  }
  for (size_t i = 0; i < nO; i++) {
    add_neurone(0.5f, 2, 1);
  }
  init_weigths();

}


void change_value(float a[], size_t la, float w)
{
  test_value(a, la);
  wanted = w;
}


void test_value(float a[], size_t la)
{
  for (size_t i = 0; i < la; i++) {
    n[i].value = a[i];
  }
}


float sigmoid(float n)
{ // Sigmoid Function
  return 1 / (1 + exp(- n));
}


void change_activation_values()
{ // Changes the activation values of hidden neurone and output neurone
  neth = 0;
  for (size_t i = layer0; i < nbNeurones - lO; i++) {
    for (size_t j = 0; j < n[i].nbE; j++) {
      neth += n[n[i].neuronesE[j]].value * n[i].weightE[j];
    }
    neth += n[i].bias;
    n[i].value = sigmoid(neth);
  }

  size_t k = nbNeurones - 1;
  netz = 0;
  for (size_t j = nbNeurones - lO; j < nbNeurones; j++) {
    for (size_t i = 0; i < n[k].nbE; i++) {
      netz += n[n[j].neuronesE[i]].value * n[j].weightE[i];
    }
    netz += n[j].bias;
    n[j].value = sigmoid(netz);
  }
}


float calculate_weight(float p, float cell, float entry)
{ // Calculates the new value of a weight
  return p * cell * entry;
}


void error_calcul_modify_weights()
{ // Calculates the error of hidden and output neurones and modify the weights
  // Output neurone
  float target;
  for (size_t i = nbNeurones - lO; i < nbNeurones; i++) {
    if(i - (nbNeurones - lO) == wanted){
      target = 1;
    }
    else{
      target = 0;
    }
    n[i].dz = (target - n[i].value) * n[i].value * (1 - n[i].value);
    for (size_t j = 0; j < n[i].nbE; j++) {
      n[i].weightE[j] += calculate_weight(p, n[i].dz, n[n[i].neuronesE[j]].value);
      n[layer0 + j].weightS[i - (nbNeurones - lO)] = n[i].weightE[j];
    }
    if(n[i].hasBias == 1){
      n[i].bias += calculate_weight(p, n[i].dz, 1);

    }
  }

  // Hidden neurone
  float sdz;
  size_t l;
  for (size_t i = layer0; i < layer0 + lH; i++) {
    sdz = 0;
    l = 0;
    for (size_t k = nbNeurones - lO; k < nbNeurones; k++) {
      sdz += n[k].dz * n[i].weightS[l];
      l += 1;
    }
    dh = n[i].value * (1 - n[i].value) * sdz;
    for (size_t j = 0; j < n[i].nbE; j++) {
      n[i].weightE[j] += calculate_weight(p, dh, n[n[i].neuronesE[j]].value);
    }
    if(n[i].hasBias == 1)
    {
      n[i].bias += calculate_weight(p, dh, 1);
    }
  }
}


size_t goodValue(size_t a)
{
  float max = -1;
  size_t j = 0;
  size_t maxI = 0;
  for (size_t i = a; i < nbNeurones; i++) {
    if(n[i].value > max)
    {
      maxI = j;
      max = n[i].value;
    }
    j += 1;
  }
  return maxI;
}

void pars(size_t b, size_t e, char path[])
{
  for (size_t i = b; i < e; i++) {
    Char letter;
    TabChar[i] = letter;
    path[17] = abc[i];
    //printf("%s\n", path);
    char *path_ = path;
    parser(TabChar[i].tab, path_);
    /*for (size_t j = 0; j < 28; j++) {
      for (size_t k = 0; k < 28; k++) {
        printf("%i", TabChar[i].tab[j * 28 + k]);
      }
      printf("\n");
    }*/
  }
}
void init_char()
{
  char path1[25] = "../Character/min/ /0.txt";
  pars(0, 26, path1);
  char path2[25] = "../Character/maj/ /0.txt";
  pars(26, 52, path2);
  char path3[25] = "../Character/sep/ /0.txt";
  pars(52, 62, path3);


}

void Training(size_t ite, size_t len)
{
  int pourcent = 0;
  for (size_t i = 0; i < ite; i++) {
    if(i % (ite/10)  == 0)
    {
      printf("Avancement de l'apprentissage : %d / 100 \n", pourcent);
      pourcent += 10;
    }
    for (size_t j = 0; j < 62; j++) {
      change_value(TabChar[j].tab, len, j);
      change_activation_values();
      error_calcul_modify_weights();
    }
  }
}

int Testing()
{
  int t = 0;
  for (size_t i = 0; i < 62; i++) {
    test_value(TabChar[i].tab, 784);
    change_activation_values();
    printf("%c -> ", abc[i]);
    if(abc[goodValue(nbNeurones - lO)] == abc[i])
      {
        printf("True\n");
        t += 1;
      }
      else { printf("False (%c)\n", abc[goodValue(nbNeurones - lO)]); }
  }
  return t;
}

void HardTest()
{
  int curTest = 0;
  for (size_t i = 70; i < 71; i+=5) {
      for (float k = 0.222f; k < 0.242f; k+=0.004f) {
        int t;
        p = k;
        init_network(len, i, 76);
        Training(700, len);
        for (size_t j = 0; j < 8; j++) {
          Training(50, len);
          t = Testing();
          printf("%d\n", t);
          if(t > tMax)
          {
            tMax = t;
            pMax = k;
            hMax = i;
            iteMax = 700 + 50 * j;
          }
          curTest += 1;
          printf("Iteration : %d / 60\n", curTest);

        }

      }
    }
}

int main()
{
    lH = 60;
    p = 0.222f;

    len = 784;
    int t = 0;
    init_char();
    init_network(len, lH, 62);
    Training(850, len);
    t = Testing();
    printf("%d / lH = %zu / p = %f\n", t, lH, p);

}
