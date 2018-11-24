#include <stdio.h>
#include <math.h>
#include "xor.h"
#include <stdlib.h>



void add_neurone(float v, float c)
{
  Neurone neurone;
  neurone.value = v;
  neurone.couche = c;
  neurone.nbE = 0;
  neurone.bias = 0;
  n[nbNeurones] = neurone;
  nbNeurones += 1;
}

void add_bias(size_t i)
{
  Neurone neurone;
  n[i].bias = 0;
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
      }
  }
}

void add_link(size_t n1, size_t n2)
{
  n[n1].weightE[n[n1].nbE] = 0;
  n[n1].neuronesE[n[n1].nbE] = n2;
  n[n1].nbE += 1;
}

void init_table()
{ // Initializes the weights to 0
    for(int i = 0 ; i < 7 ; i++)
    {
      weight[i] = 0;
    }
}


void init_network(size_t nI, int nH[], size_t lH, size_t nO, size_t b[], size_t lB)
{
  layer0 = nI;
  for (size_t i = 0; i < nI; i++) {
    add_neurone(0, 0);
  }
  for (size_t i = 0; i < lH; i++) {
    for (size_t j = 0; j < nH[i]; j++) {
      add_neurone(0, 1 + i);
    }
  }
  for (size_t i = 0; i < nO; i++) {
    add_neurone(0.5f, lH + 1);
  }
  init_weigths();

  for (size_t i = 0; i < lB; i++) {
    add_bias(b[i]);
  }

}

void change_value(float a, float b, float w)
{
  n[0].value = a;
  n[1].value = b;
  wanted = w;
}



float sigmoid(float n)
{ // Sigmoid Function
  return 1 / (1 + exp(- n));
}


void change_activation_values()
{ // Changes the activation values of hidden neurone and output neurone
  neth = 0;
  for (size_t i = layer0; i < nbNeurones - 1; i++) {
    for (size_t j = 0; j < n[i].nbE; j++) {

      neth += n[n[i].neuronesE[j]].value * n[i].weightE[j];
    }
    neth += n[i].bias;
    n[i].value = sigmoid(neth);
  }

  /*neth = x * weight[2] + bias_h * weight[4] + y * weight[5];
  h = sigmoid(neth); // New activation value of the hidden cell*/

  size_t k = nbNeurones - 1;
  netz = 0;
  for (size_t i = 0; i < n[k].nbE; i++) {
    netz += n[n[k].neuronesE[i]].value * n[k].weightE[i];
  }
  netz += n[k].bias;
  n[k].value = sigmoid(netz);


  /*netz = bias_z * weight[0] + x * weight[1] + h * weight[3] + y * weight[6];
  z = sigmoid(netz); // New activation value of output cell*/
}


float calculate_weight(float p, float cell, float entry)
{ // Calculates the new value of a weight
  return p * cell * entry;
}


void error_calcul_modify_weights()
{ // Calculates the error of hidden and output neurones and modify the weights
  size_t k = nbNeurones - 1;
  // Output neurone
  dz = (wanted - n[k].value) * n[k].value * (1 - n[k].value);
  for (size_t i = 0; i < n[k].nbE; i++) {
    n[k].weightE[i] += calculate_weight(p, dz, n[n[k].neuronesE[i]].value);
  }
  n[k].bias += calculate_weight(p, dz, 1);


/*  weight[0] += calculate_weight(p, dz, bias_z);
  weight[1] += calculate_weight(p, dz, x);
  weight[3] += calculate_weight(p, dz, h);
  weight[6] += calculate_weight(p, dz, y);*/

  // Hidden neurone
  for (size_t i = layer0; i < nbNeurones - 1; i++) {
    dh = n[i].value * (1 - n[i].value) * dz * n[4].weightE[i - 2];
  /*  printf("dh = %f\n", dh);
    printf("nV = %f\n", n[i].value);
    printf("dz = %f\n", dz);
    printf("S = %f\n", n[3].weightE[i - 2]);*/
    for (size_t j = 0; j < n[i].nbE; j++) {
      n[i].weightE[j] += calculate_weight(p, dh, n[n[i].neuronesE[j]].value);
    }
  }
  for (size_t i = layer0; i < nbNeurones - 1; i++) {
    n[i].bias += calculate_weight(p, dz, 1);
  }


  /*dh = h * (1 - h) * dz * weight[3];
  weight[2] += calculate_weight(p, dh, x);
  weight[4] += calculate_weight(p, dh, bias_h);
  weight[5] += calculate_weight(p, dh, y);*/
}


/*void Apply_xor()
{ //Apply the xor
  init_table();

  // Shows initials output value for each possibility
  printf("\n-------- Initials output -------\n");
  init_neural_XOR(0, 0, 0);
  change_activation_values();
  printf("[0 + 0 -> 0] z = %f\n", z);
  init_neural_XOR(0, 1, 1);
  change_activation_values();
  printf("[0 + 1 -> 1] z = %f\n", z);
  init_neural_XOR(1, 0, 1);
  change_activation_values();
  printf("[1 + 0 -> 1] z = %f\n", z);
  init_neural_XOR(1, 1, 0);
  change_activation_values();
  printf("[1 + 1 -> 0] z = %f\n", z);

  for(int i = 0 ; i < 5000; i++)
  { // Learning the neural network (5000 iterations)

    init_neural_XOR(0, 0, 0);
    change_activation_values();
    error_calcul_modify_weights();

    init_neural_XOR(0, 1, 1);
    change_activation_values();
    error_calcul_modify_weights();

    init_neural_XOR(1, 0, 1);
    change_activation_values();
    error_calcul_modify_weights();

    init_neural_XOR(1, 1, 0);
    change_activation_values();
    error_calcul_modify_weights();
  }

  printf("\n-------- Weights after Learning -------\n");
  for (int i = 0; i < 7; i++) {
    printf("Weight %d = %f\n", i, weight[i]);
  }

  printf("\n-------- Neural Network with weights indexes --------\n\n");
  printf(" (bias_z)-0-(z)\n");
  printf("            /|\\ \n");
  printf("           / 3 \\ \n");
  printf("          / (h) \\ \n");
  printf("         1 / | \\ 6 \n");
  printf("        / 2  4  5 \\ \n");
  printf("       / /   |   \\ \\ \n");
  printf("      (x) (bias_h) (y) \n\n");

  printf("\n-------- Output after learning -------\n");
  init_neural_XOR(0, 0, 0);
  change_activation_values();
  printf("[0 + 0 -> 0] z = %f\n", z);
  init_neural_XOR(0, 1, 1);
  change_activation_values();
  printf("[0 + 1 -> 1] z = %f\n", z);
  init_neural_XOR(1, 0, 1);
  change_activation_values();
  printf("[1 + 0 -> 1] z = %f\n", z);
  init_neural_XOR(1, 1, 0);
  change_activation_values();
  printf("[1 + 1 -> 0] z = %f\n", z);
}
*/
int main()
  {
    //Apply_xor();
    int nH[1] = {4};
    size_t b[] = {};
    init_network(2, nH, 1, 1, b, 0);
  //  add_link(3, 0);
  //  add_link(3, 1);


    for (size_t i = 0; i < 100000; i++) {

      change_value(0, 0, 1);
      change_activation_values();
      error_calcul_modify_weights();
      change_value(1, 0, 0);
      change_activation_values();
      error_calcul_modify_weights();
      change_value(0, 1, 0);
      change_activation_values();
      error_calcul_modify_weights();
      change_value(1, 1, 1);
      change_activation_values();
      error_calcul_modify_weights();





    }
    printf("\n-------- Output after learning -------\n");
    change_value(0, 0, 0);
    change_activation_values();
    printf("[0 + 0 -> 0] z = %f\n", n[nbNeurones - 1].value);
    change_value(0, 1, 0);
    change_activation_values();
    printf("[0 + 1 -> 1] z = %f\n", n[nbNeurones - 1].value);
    change_value(1, 0, 0);
    change_activation_values();
    printf("[1 + 0 -> 1] z = %f\n", n[nbNeurones - 1].value);
    change_value(1, 1, 1);
    change_activation_values();
    printf("[1 + 1 -> 0] z = %f\n", n[nbNeurones - 1].value);


    printf("Nombre de neurones = %zu\n", nbNeurones);
    printf("---------COUCOU---------\n");

    for (size_t i = 0; i < nbNeurones; i++) {
      printf("------------------\n");
      printf("neurone actuel = %f \n", n[i].value);
      printf("couche actuel = %d \n", n[i].couche);
      printf("Nombre de neurone entrants = %zu \n", n[i].nbE);
      for (size_t j = 0; j < n[i].nbE; j++) {
        printf("Neurone entrant = %zu \n", n[i].neuronesE[j]);
        printf("Poids neurone entrant = %f \n", n[i].weightE[j]);
        printf("         ******          \n");
      }
    }

    printf("z = %f\n", n[nbNeurones - 1].value);


  }
