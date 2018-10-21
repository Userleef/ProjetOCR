#ifndef XOR_H
#define XOR_H

// Functions

void apply_xor();

void init_table();

void init_neural_XOR(float a, float b, float wanted);

float sigmoid(float n);

void change_activation_values();

float calculate_weight(float p, float cell, float entry);

void error_calcul_modify_weights();

#endif
