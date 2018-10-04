#include <stdio.h>
#include <mat.h>

float extreme
float a
float b
float h
float bias_h
float c
float bias_c
float weight[7][7]
float wanted

void init_table()
{
    int i = 0;
    int j = 0;
    extreme = 7;
    while (i != extreme)
    {
	while (j != extreme)
	{
	    weight[i][j] = 0;
	    j += 1;
	}
	i += 1;
    }
}
void init_neural_XOR()
{
    init_table()
    a = 1;
    b = 0;
    h = 1/2;
    bias_h = 1;
    z = 1/2;
    bias_z = 1;
    wanted = 1;
}
