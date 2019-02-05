#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "parser.h"
#include "xor.h"


// Variables

size_t len;
float nbweights; // Number of weights
float weight[7]; // Array of weights

float x; // Input value
float y; // Input value
float z = 0.5f; // Output value
float h = 0.5f; //  Hidden neurone value
float wanted = 0; // Expected output

float p; // Pace


float dh; // Value of the hidden neurone error

float netz; // Used for the activation calcutation
float neth; // Used for the activation calculation

float bias_h = 1; // Bias of the hidden neurone
float bias_z = 1; // Bias of the output neurone

typedef struct Char Char;
struct Char //Structure of a character in the alphabet
{
  float tab[784];
};

Char TabChar[78];

typedef struct Neurone Neurone;
struct Neurone // Structure of a neuron
{

  size_t neuronesE[784]; // Entering neurons of a neuron 
  size_t neuronesS[784]; // Exiting neurons of a neuron
  float weightE[784]; // Entering weights
  float weightS[784]; // Exiting weights
  size_t nbE; // Number of entering neurons
  size_t nbS; // Number of exiting neurons
  float value; // Value of a neuron
  size_t couche; // Layer of a neuron
  int hasBias; // if has a bias
  float bias; // Value of bias weight
  float dz; // Value of error of output neurons
};

size_t lO = 0; // Number of neurons in the layer of output cells
size_t lH = 0; // Number of neurons in the layer of hiddens cells
size_t cH = 0; // Number of hidden layers
size_t nbNeurones = 0; // Number of neurons in the network
size_t layer0 = 0; // Number of neurons in the layer of input cells
Neurone n[1000] = {}; // Array of neurons
Neurone bias[2] = {}; 
size_t nbBias = 0;

int tMax = 0;
float pMax = 0;
size_t hMax = 0;
size_t iteMax = 0;

char abc[63] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
//char path[24];


void add_neurone(float v, size_t c, float b)
{ // Add a neuron
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
{ // Init each weights of neurons
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


void init_network(size_t nI, size_t lH1, size_t nO, float p1)
{ // Init the neural network
  p = p1;
  nbNeurones = 0;
  layer0 = nI;
  lO = nO;
  lH = lH1;
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
{ // Change the values of inputs for training
  test_value(a, la);
  wanted = w;
}


void test_value(float a[], size_t la)
{ // Change the values of inputs for testing
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
{ // Verify if the network recognize a character
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
{ // Parser 
  for (size_t i = b; i < e; i++) {
    Char letter;
    TabChar[i] = letter;
    path[16] = abc[i];
    char *path_ = path;
    parser(TabChar[i].tab, path_);
  }
}
void init_char()
{ // Initialize the data base
  char path1[25] = "./Character/min/ /0.txt";
  pars(0, 26, path1);
  char path2[25] = "./Character/maj/ /0.txt";
  pars(26, 52, path2);
  char path3[25] = "./Character/sep/ /0.txt";
  pars(52, 62, path3);


}

void Training(size_t ite, size_t len)
{ // Train the network
  int pourcent = 0;
  for (size_t i = 0; i <= ite; i++) {
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
void print_matrice2(int h, int w, float T[h * w])
{
   int i, j ;
   for ( i = 0 ; i < h ; ++i )
   {
      for ( j = 0 ; j < w ; ++j )
      {
        printf( "%d", (int)T[i * w + j] ) ;
      }
      printf( "\n" ) ;
   }
}

int Testing()
{
  int t = 0;
  for (size_t i = 0; i < 62; i++) {
    test_value(TabChar[i].tab, 784);
    change_activation_values();
    printf("%c -> ", abc[i]);
  }
  return t;
}

char find_char(float* T)
{
  //print_matrice2(28, 28, T);
  //printf("lO : %zu\n", lO);
  test_value(T,784);
  change_activation_values();
  return abc[goodValue(nbNeurones - lO)];
}
