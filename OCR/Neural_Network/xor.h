#ifndef XOR_H
#define XOR_H
#include <stdlib.h>

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

typedef struct Neurone Neurone;
struct Neurone
{

  size_t neuronesE[4];
  float weightE[4];
  size_t nbE;
  float value;
  int couche;
  float bias;
};

size_t nbNeurones = 0;
size_t layer0 = 0;
Neurone n[5] = {};
Neurone bias[2] = {};
size_t nbBias = 0;


float w;

// Functions
void add_neurone(float v, float c);
void init_table();
void add_link(size_t n1, size_t n2);

void init_network(size_t nI, int nH[], size_t lH, size_t nO, size_t b[], size_t lB);
void change_value(float a, float b, float wanted);

float sigmoid(float n);

void change_activation_values();

float calculate_weight(float p, float cell, float entry);

void error_calcul_modify_weights();

void Apply_xor();

#endif
