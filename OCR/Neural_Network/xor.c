#include <stdio.h>
#include <math.h>

float extreme;
float x;
float y;
float h = 0.5f;
float dh;
float neth;
float bias_h = 1;
float z = 0.5f;
float netz;
float dz;
float bias_z = 1;
float weight[7];
float wanted;
float p = 2;

void init_table()
{
    for(int i = 0; i < 7; i++)
    {
      weight[i] = 0;
    }
}

void init_neural_XOR(float a, float b, float w)
{
    //init_table()
    x = a;
    y = b;
    wanted = w;
    //printf("x %f : y %f : z %f : w %f : h %f\n", x, y, z, w, h);

}
float sigmoid(float n)
{
  return 1 / (1 + exp(- n));
}

void change_activations_values() //Change the activation value of hidden cell and exit cell
{
  neth = x * weight[2] + bias_h * weight[4] + y * weight[5];
  //printf("neth = %f\n", neth);
  h = sigmoid(neth);
  //printf("h = %f\n", h);
  netz = bias_z * weight[0] + x * weight[1] + h * weight[3] + y * weight[6];
  //printf("netz = %f\n", netz);
  z = sigmoid(netz);
  //printf("z = %f\n", z);
}

float calcul_weight(float p, float cell, float entry)
{
  return p * cell * entry;
}

void error_calcul_modify_weights()
{
  dz = (wanted - z) * z * (1 - z);
  //printf("dz = %f\n", dz);
  weight[0] += calcul_weight(p, dz, bias_z);
  //printf("w0 = %f\n", weight[0]);
  weight[1] += calcul_weight(p, dz, x);
  //printf("w1 = %f\n", weight[1]);
  weight[3] += calcul_weight(p, dz, h);
  //printf("w3 = %f\n", weight[3]);
  weight[6] += calcul_weight(p, dz, y);
  //printf("w6 = %f\n", weight[6]);
  dh = h * (1 - h) * dz * weight[3];
  //printf("dh = %f\n", dh);
  weight[2] += calcul_weight(p, dh, x);
  //printf("w2 = %f\n", weight[2]);
  weight[4] += calcul_weight(p, dh, bias_h);
  //printf("w4 = %f\n", weight[4]);
  weight[5] += calcul_weight(p, dh, y);
  //printf("w5 = %f\n", weight[5]);
}
int main()
{
  init_table();

  init_neural_XOR(0, 0, 0);
  change_activations_values();
  printf("[0 + 0 -> 0] z = %f\n", z);
  init_neural_XOR(0, 1, 1);
  change_activations_values();
  printf("[0 + 1 -> 1] z = %f\n", z);
  init_neural_XOR(1, 0, 1);
  change_activations_values();
  printf("[1 + 0 -> 1] z = %f\n", z);
  init_neural_XOR(1, 1, 0);
  change_activations_values();
  printf("[1 + 1 -> 0] z = %f\n", z);

  printf("\n---------------------------\n\n");

  for(int i = 0 ; i < 5000; i++)
  {
    init_neural_XOR(0, 0, 0);
    change_activations_values();
    error_calcul_modify_weights();
    init_neural_XOR(0, 1, 1);
    change_activations_values();
    error_calcul_modify_weights();
    init_neural_XOR(1, 0, 1);
    change_activations_values();
    error_calcul_modify_weights();
    init_neural_XOR(1, 1, 0);
    change_activations_values();
    error_calcul_modify_weights();
  }

  init_neural_XOR(0, 0, 0);
  change_activations_values();
  printf("[0 + 0 -> 0] z = %f\n", z);
  init_neural_XOR(0, 1, 1);
  change_activations_values();
  printf("[0 + 1 -> 1] z = %f\n", z);
  init_neural_XOR(1, 0, 1);
  change_activations_values();
  printf("[1 + 0 -> 1] z = %f\n", z);
  init_neural_XOR(1, 1, 0);
  change_activations_values();
  printf("[1 + 1 -> 0] z = %f\n", z);


}
