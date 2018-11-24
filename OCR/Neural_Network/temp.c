void add_neurone(float v, float c)
{
  if(c == 0)
  {
    layer0 += 1;
  }
  Neurone neurone;
  neurone.value = v;
  neurone.couche = c;
  neurone.nbE = 0;
  neurone.bias = 0;
  n[nbNeurones] = neurone;
  nbNeurones += 1;
}

void add_bias(float v, size_t i)
{
  Neurone neurone;
  neurone.value = v;
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
  size_t k = nbNeurones - 1;

  if(_0toEnd ==  1){
    for (size_t i = 0; i < layer0; i++) {
      n[k].weightE[n[k].nbE] = 0;
      n[k].neuronesE[n[k].nbE] = i;
      n[k].nbE += 1;
    }
  }
}

void init_table()
{ // Initializes the weights to 0
    for(int i = 0 ; i < 7 ; i++)
    {
      weight[i] = 0;
    }
}


void init_neural_XOR(int o)
{
  _0toEnd = o;
  add_neurone(0, 0);
  add_neurone(0, 0);
  add_neurone(0, 1);
  add_neurone(0.5f, 2);
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
    dh = n[i].value * (1 - n[i].value) * dz * n[3].weightE[i - 2];
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
