#ifndef _XOR_H
#define _XOR_H
#include <stdlib.h>

// Functions
void add_neurone(float v, size_t c, float b);

void init_weigths();

void init_network(size_t nI, size_t lH, size_t nO, float p);

void change_value(float a[], size_t lA, float wanted);

void test_value(float a[], size_t lA);

float sigmoid(float n);

void change_activation_values();

float calculate_weight(float p, float cell, float entry);

void error_calcul_modify_weights();

size_t goodValue(size_t a);

void init_char();

void Training(size_t ite, size_t len);

int Testing();

char find_char(float* T);

#endif
