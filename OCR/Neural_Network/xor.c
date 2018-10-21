#include "xor.h"
#include <stdio.h>
#include <math.h>

// Variables

float nbweights; // Number of weights
float weight[7]; // Array of weights

float x; // Input value
float y; // Input value
float z = 0.5f; // Output value
float h = 0.5f; //  Hidden neurone value
float wanted; // Expected output

float dz; // Value of the output neurone error
float dh; // Value of the hidden neurone error

float netz; // Used for the activation calcutation
float neth; // Used for the activation calculation

float bias_h = 1; // Bias of the hidden neurone
float bias_z = 1; // Bias of the output neurone

float p = 2; // Pace




void init_table()
{ // Initializes the weights to 0
    for(int i = 0 ; i < 7 ; i++)
    {
      weight[i] = 0;
    }
}


void init_neural_XOR(float a, float b, float w)
{ // Modifies the input values ​​and the expected output value
    x = a;
    y = b;
    wanted = w;
}


float sigmoid(float n)
{ // Sigmoid Function
  return 1 / (1 + exp(-n));
}


void change_activation_values()
{ // Changes the activation values of hidden neurone and output neurone
  neth = x * weight[2] + bias_h * weight[4] + y * weight[5];
  h = sigmoid(neth); // New activation value of the hidden cell

  netz = bias_z * weight[0] + x * weight[1] + h * weight[3] + y * weight[6];
  z = sigmoid(netz); // New activation value of output cell
}


float calculate_weight(float p, float cell, float entry)
{ // Calculates the new value of a weight
  return p * cell * entry;
}


void error_calcul_modify_weights()
{ // Calculates the error of hidden and output neurones and modify the weights

  // Output neurone
  dz = (wanted - z) * z * (1 - z);
  weight[0] += calculate_weight(p, dz, bias_z);
  weight[1] += calculate_weight(p, dz, x);
  weight[3] += calculate_weight(p, dz, h);
  weight[6] += calculate_weight(p, dz, y);

  // Hidden neurone
  dh = h * (1 - h) * dz * weight[3];
  weight[2] += calculate_weight(p, dh, x);
  weight[4] += calculate_weight(p, dh, bias_h);
  weight[5] += calculate_weight(p, dh, y);
}


void apply_xor()
{
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
