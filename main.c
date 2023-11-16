#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

void exibirResultado(long int arr[], long int qtdNumeros);
long double medirTempo(void (*algoritmo)(long int[], long int), long int arr[], long int n);
void bubbleSort(long int arr[], long int n);
void insertionSort(long int arr[], long int n);
void selectionSort(long int arr[], long int n);
FILE *pegarDadosArquivo();
void ordenarDadosArquivo();
void ordenarDadosAleatorios();
void ordenarDadosDigitados();
void pegarOpcaoMenu();
void exibirOpcoesMenu();
void exibirResultado(long int arr[], long int qtdNumeros);

long double medirTempo(void (*algoritmo)(long int[], long int), long int arr[], long int n)
{
  clock_t inicio, fim;
  long double tempo;

  inicio = clock();
  algoritmo(arr, n);
  fim = clock();

  tempo = ((long double)(fim - inicio)) / CLOCKS_PER_SEC;
  return tempo;
}

void bubbleSort(long int arr[], long int n)
{
  long int i, j, temp;

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

void insertionSort(long int arr[], long int n)
{
  for (long int i = 1; i < n; i++)
  {
    long int key = arr[i];
    long int j = i - 1;
    while (j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

void selectionSort(long int arr[], long int n)
{
  long int i, j, minIndex, temp;

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
  long int numero;
  long int qtdNumerosArquivo = 0;

  while (file == NULL)
  {
    printf("Erro ao abrir o arquivo!\n");
    file = pegarDadosArquivo();
  }

  while (fscanf(file, "%ld", &numero) == 1)
  {
    qtdNumerosArquivo++;
  }

  long int arr[qtdNumerosArquivo];

  rewind(file);

  long int n = 0;
  while (fscanf(file, "%ld", &arr[n]) == 1 && n < qtdNumerosArquivo)
  {
    n++;
  }

  fclose(file);

  exibirResultado(arr, qtdNumerosArquivo);
}

void ordenarDadosAleatorios()
{
  long int qtdDados;

  srand(time(NULL));

  printf("\nDeseja que o sistema gere e ordene quantos dados? ");
  scanf("%ld", &qtdDados);

  long int arr[qtdDados], i;

  for (i = 0; i < qtdDados; i++)
  {
    arr[i] = rand();
  }

  exibirResultado(arr, qtdDados);
}

void ordenarDadosDigitados()
{
  long int qtdDados, i;

  printf("\nDeseja digitar quantos dados? ");
  scanf("%ld", &qtdDados);
  printf("\n");

  long int arr[qtdDados];

  for (i = 0; i < qtdDados; i++)
  {
    printf("Digite o %ldº dado: ", i + 1);
    scanf("%ld", &arr[i]);
  }

  exibirResultado(arr, qtdDados);
}

void pegarOpcaoMenu()
{
  int opcao;

  printf("\n");
  printf("\nInsira o número de uma das opções: ");

  scanf("%d", &opcao);

  int c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
  }

  if (opcao == 1)
  {
    ordenarDadosArquivo();
  }
  else if (opcao == 2)
  {
    ordenarDadosAleatorios();
  }
  else if (opcao == 3)
  {
    ordenarDadosDigitados();
  }
  else if (opcao == 0)
  {
    exit(0);
  }
  else
  {
    printf("Opção inválida!");
    pegarOpcaoMenu();
  }
}

void exibirOpcoesMenu()
{
  printf("\n");
  printf("\nOpções:");
  printf("\n1 - Digitar caminho do arquivo com os dados");
  printf("\n2 - Permitir que o sistema gere e ordene dados aleatórios");
  printf("\n3 - Digitar dados");
  printf("\n0 - Sair");

  pegarOpcaoMenu();
}

void exibirResultado(long int arr[], long int qtdNumeros)
{
  long int arrToBubble[qtdNumeros], arrToInsertion[qtdNumeros], arrToSelection[qtdNumeros], i;

  printf("\nDados gerados a serem ordenados:\n");

  for (i = 0; i < qtdNumeros; i++)
  {
    arrToBubble[i] = arr[i];
    arrToInsertion[i] = arr[i];
    arrToSelection[i] = arr[i];
    printf("%ld ", arrToBubble[i]);
  }

  double tempoBubble = medirTempo(bubbleSort, arrToBubble, qtdNumeros);
  double tempoInsertion = medirTempo(insertionSort, arrToInsertion, qtdNumeros);
  double tempoSelection = medirTempo(selectionSort, arrToSelection, qtdNumeros);

  printf("\n");
  printf("\nDados ordenados:\n");
  for (int i = 0; i < qtdNumeros; i++)
  {
    printf("%ld ", arrToBubble[i]);
  }

  printf("\n");
  printf("\nTempo gasto pelo Bubble Sort: %f segundos\n", tempoBubble);
  printf("Tempo gasto pelo Insertion Sort: %f segundos\n", tempoInsertion);
  printf("Tempo gasto pelo Selection Sort: %f segundos", tempoSelection);

  exibirOpcoesMenu();
}

int main()
{
  SetConsoleOutputCP(CP_UTF8);

  printf("\nSistema de ordenação de dados");

  exibirOpcoesMenu();

  return 0;
}
