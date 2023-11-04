#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

double medirTempo(void (*algoritmo)(int[], int), int arr[], int n)
{
  clock_t inicio, fim;
  long double tempo;

  inicio = clock();
  algoritmo(arr, n);
  fim = clock();

  tempo = ((long double)(fim - inicio)) / CLOCKS_PER_SEC;
  return tempo;
}

void bubbleSort(int arr[], int n)
{
  int i, j, temp;

  for (i = 0; i < n - 1; i++)
  {
    for (j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        // Troca os elementos se estiverem fora de ordem
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void insertionSort(int arr[], int n)
{
  for (int i = 1; i < n; i++)
  {
    int key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

void selectionSort(int arr[], int n)
{
  int i, j, minIndex, temp;

  for (i = 0; i < n - 1; i++)
  {
    minIndex = i;

    for (j = i + 1; j < n; j++)
    {
      if (arr[j] < arr[minIndex])
      {
        minIndex = j;
      }
    }

    temp = arr[i];
    arr[i] = arr[minIndex];
    arr[minIndex] = temp;
  }
}

FILE *pegarDadosArquivo()
{
  char caminhoArquivo[100];

  printf("\nDigite o caminho e nome do arquivo: ");
  scanf("%s", caminhoArquivo);
  return fopen(caminhoArquivo, "r");
}

void ordenarDadosArquivo()
{
  FILE *file = pegarDadosArquivo();
  int numero;
  int qtdNumerosArquivo = 0;

  while (file == NULL)
  {
    printf("Erro ao abrir o arquivo!\n");
    file = pegarDadosArquivo();
  }

  while (fscanf(file, "%d", &numero) == 1)
  {
    qtdNumerosArquivo++;
  }

  int arrToBubble[qtdNumerosArquivo], arrToInsertion[qtdNumerosArquivo], arrToSelection[qtdNumerosArquivo];

  rewind(file);

  printf("\nDados a serem ordenados: \n");

  int n = 0;
  while (fscanf(file, "%d", &arrToBubble[n]) == 1 && n < qtdNumerosArquivo)
  {
    arrToInsertion[n] = arrToBubble[n];
    arrToSelection[n] = arrToBubble[n];
    printf("%d ", arrToBubble[n]);
    n++;
  }

  fclose(file);

  double tempoBubble = medirTempo(bubbleSort, arrToBubble, qtdNumerosArquivo);
  double tempoInsertion = medirTempo(insertionSort, arrToInsertion, qtdNumerosArquivo);
  double tempoSelection = medirTempo(selectionSort, arrToSelection, qtdNumerosArquivo);

  printf("\n");
  printf("\nDados ordenados:\n");
  for (int i = 0; i < qtdNumerosArquivo; i++)
  {
    printf("%d ", arrToBubble[i]);
  }

  printf("\n");
  printf("\nTempo gasto no Bubble Sort: %f segundos\n", tempoBubble);
  printf("Tempo gasto no Insertion Sort: %f segundos\n", tempoInsertion);
  printf("Tempo gasto no Selection Sort: %f segundos\n", tempoSelection);

  printf("\n%d", arrToBubble[qtdNumerosArquivo - 1]);
  printf("\n%d", arrToInsertion[qtdNumerosArquivo - 1]);
  printf("\n%d", arrToSelection[qtdNumerosArquivo - 1]);
}

int main()
{
  int opcao;

  printf("\nSistema de ordenacao de dados");
  printf("\n");
  printf("\nOpcoes para geracao ou obtencao de dados:");
  printf("\n1 - Digitar caminho do arquivo com os dados");
  printf("\n2 - Permitir que o sistema gere e ordene dados aleatorios");
  printf("\n3 - Digitar dados");
  printf("\n");
  printf("\nInsira o numero de uma das opcoes: ");

  scanf("%d", &opcao);

  if (opcao == 1)
  {
    ordenarDadosArquivo();
  }

  return 0;
}
