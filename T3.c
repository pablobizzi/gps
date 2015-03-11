#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define tam_cidade 50

///////////
//Structs//
///////////

//Estrutura de uma aresta do grafo de cidades
typedef struct arestas{
   int cidade; //Vertice de destino da aresta
   int rota; //Indice que permite localizar o nome da estrada
   int dist; //Peso da aresta
   struct arestas *prox; //Próxima ligação do vértice de origem
}Arestas;

//Estrutura de um vertice do grafo de cidades
typedef struct vertices{
   char* nome; //Nome da cidade
   struct arestas* rotas; //Arestas do vértice
}Vertices;

//Estrutura de contém o nome de uma estrada
typedef struct rotas{
   char* nome; //Nome da estrada
}Rotas;

//////////////////////////////////////
//Funções que inicializam as structs//
//////////////////////////////////////

//Função que inicializa um vetor de cidades
Vertices* inicializa_cidades(int n){
   int i = 0;
   Vertices* novo=(Vertices*)malloc(n * sizeof(Vertices));
   while(i != n){
      novo[i].rotas = NULL;
      i++;
   }
   return novo;
}

//Função que inicializa um vetor de rotas
Rotas* inicializa_estradas(int r){
   Rotas* novo=(Rotas*)malloc(r * sizeof(Rotas));
   return novo;
}

//////////////////////
//Funções dos grafos//
//////////////////////

//Função que inicializa uma aresta como um vetor NULL
Arestas* cria(void){
   return NULL;
}

//Função que aloca espaço para uma nova aresta
Arestas* inserir(Vertices* v, Rotas* rotas, int origem,int destino, int distancia, int rodovia){
   Arestas *novo = (Arestas*)malloc(sizeof(Arestas));
   novo->cidade = destino;
   novo->dist = distancia;
   novo->rota = rodovia;
   novo->prox = v[origem].rotas;
   return novo;
}

//Função que procura o próximo trecho válido de informação copiada do arquivo
int pula_espacos(char* string, int i){
   while((string[i]==9) || (string[i]==32)){
      i++;
   }
   return i;
}

//Função que cria um vertice
void atribui_v(char* string, Vertices* v){
   int i=1; //nunca pegar o digito inical
   int j=0;
   int k=0;
   int aux;
   char num[4];

   i=pula_espacos(string, i);

   while((string[i]!=9) && (string[i]!=' ')){
      num[j]=string[i];
      j++;
      i++;
   }
   k = atoi(num);

   i=pula_espacos(string, i);

   aux = i;
   for(j=0; string[aux]!='\0'; j++){
      aux++;
   }
   v[k].nome=(char*)malloc(j*sizeof(char));
   j=0;
   while(string[i]!='\0'){
      v[k].nome[j]=string[i];
      i++;
      j++;
   }
   v[k].nome[j]='\0';
}

//Função que cria uma rota
void atribui_r(char* string, Rotas* e){
   int i=1; //nunca pegar o Digito inical
   int j=0;
   int k;
   int p;
   char num[4];

   i=pula_espacos(string, i);

   while((string[i]!=9) && (string[i]!=' ')){
      num[j]=string[i];
      j++;
      i++;
   }
   k = atoi(num);

   i=pula_espacos(string, i);

   p = i;
   for(j=0; string[p]!='\0'; j++){
      p++;
   }
   e[k].nome=(char*)malloc(j*sizeof(char));
   j=0;
   while(string[i]!='\0'){
      e[k].nome[j]=string[i];
      i++;
      j++;
   }
   e[k].nome[j]='\0';
}

//Função que cria uma aresta
void atribui_a(char* string, Vertices* v, Rotas* r){
   int i=1; //nunca pegar o Digito inical
   int j=0;
   char origem_c[4];
   char final_c[4];
   char rodovia_c[4];
   char distancia_c[8];
   int origem;
   int final;
   int distancia;
   int rodovia;
   char mao;

   i=pula_espacos(string, i);
   while((string[i]!=9) && (string[i]!=' ')){
      origem_c[j]=string[i];
      j++;
      i++;
   }
   origem_c[j] = '\0';
   origem = atoi(origem_c);

   j=0;
   i=pula_espacos(string, i);
   while((string[i]!=9) && (string[i]!=' ')){
      final_c[j]=string[i];
      j++;
      i++;
   }
   final_c[j] = '\0';
   final = atoi(final_c);

   j=0;
   i=pula_espacos(string, i);
   while((string[i]!=9) && (string[i]!=' ')){
      rodovia_c[j]=string[i];
      j++;
      i++;
   }
   rodovia_c[j] = '\0';
   rodovia = atoi(rodovia_c);

   j=0;
   i=pula_espacos(string, i);
   while((string[i]!=9) && (string[i]!=' ')){
      distancia_c[j]=string[i];
      j++;
      i++;
   }
   distancia_c[j] = '\0';
   distancia = atoi(distancia_c);

   i=pula_espacos(string, i);
   mao = string[i];

   switch(mao){
      case 'U':
         v[origem].rotas = inserir(v,r,origem,final,distancia,rodovia);
         break;
      case 'D':
         v[origem].rotas = inserir(v,r,origem,final,distancia,rodovia);
         v[final].rotas = inserir(v,r,final,origem,distancia,rodovia);
         break;
   }
}

//Função que interpreta o conteúdo do arquivo do programa e o converte
//em uma lista de adjacências e em uma lista encadeada de estradas
void interpreta(char *texto, Vertices* cidades, Rotas* estradas){
   char string[100];
   int i=0;
   int j;
   while(texto[i]!='\0'){
      j=0;
      while(texto[i] != '\n' && texto[i] != '\0'){
         string[j] = texto[i];
         i++;
         j++;
      }
      string[j] = '\0';
      switch(string[0]){
         case 'N':
            //printf("%s\n",string);
            atribui_v(string, cidades);
            break;
         case 'R':
            //printf("%s\n",string);
            atribui_r(string, estradas);
            break;
         case 'A':
            //printf("%s\n",string);
            atribui_a(string, cidades, estradas);
            break;
         default:
            break;
      }
   i++;
   }
}

////////////////////////////////////
//Funções para lidar com o arquivo//
////////////////////////////////////

//Função que conta o número de characteres 'N' dentro de um vetor de char
int conta_n(char* texto){
   int i = 1;
   int k = 0;
   if(texto[0] == 'N')
      k++;
   while(texto[i] != '\0'){
      if(texto[i] == '\n' && texto[i+1] == 'N')
         k++;
      i++;
   }
   return k;
}

//Função que conta o número de characteres 'R' dentro de um vetor de char
int conta_r(char* texto){
   int i = 1;
   int k = 0;
   if(texto[0] == 'R')
      k++;
   while(texto[i] != '\0'){
      if(texto[i] == '\n' && texto[i+1] == 'R')
         k++;
      i++;
   }
   return k;
}

//Função que lê um arquivo e retorna o conteúdo deste arquivo dentro de um vetor de char
char* ler_arquivo(void){
   FILE *fp;
   char* texto = (char*)malloc(sizeof(char)*10000000);
   char c;
   int i=0;
   fp = fopen("grafos.txt","r"); //abre arquivo pra leitura
   if(!fp){
      printf("Erro na abertura do arquivo");
      exit(0);
   }
   while((c = getc(fp)) != EOF){
      texto[i] = c;
      i++;
   }
   texto[i] = '\0';
   fclose(fp);
   return texto;
}

//////////////////////////////////////
//Funçãos de interação com o usuário//
//////////////////////////////////////

//Função que avalia se uma cidade digitada é uma cidade do grafo
int cidade_valida(int i, int n){
   if( i <= 0 || i > n)
      return -1;
   return i-1;
}

//Função que lê o nome de uma cidade digitado pelo usuário
int le_string(int num){
   int i=-1;
   printf("Digite o numero correspondente a uma cidade: ");
   do{
      scanf("%d", &i);
      i=cidade_valida(i, num);
      if(i==-1)
         printf("Cidade Invalida!\nDigite novamente: ");
   }while(i==-1);
   return i;
}

////////////////////////
//Funções de impressão//
////////////////////////

//Função que imprime as rotas, os vértices e as artestas
void imprime_existentes(Vertices* ver, int v){
   int i;
   Arestas* aux;
   printf("\nCidades Disponiveis:\n");
   for(i=0; i<v; i++){
      printf("%d - %s\n", i+1, ver[i].nome);
   }
   printf("\n");
}

////////////////////////////////////
//Funçãos do algoritmo de dijkstra//
////////////////////////////////////

//Função que executa o algoritimo de dijkstra
void dijkstra(Vertices* cidades, Rotas* estradas, int vertices,int origem,int destino,int *custos){
   //HUGE_VEL = infinito
   int i, v, min, cont=0, j;
   int ant[vertices]; // vetor de cidades anteriores a cada cidade pelo caminho mais curto
   int tmp[vertices]; // vetor temporário
   int dist[vertices]; // vetor de distâncias mínimas
   int visitada[vertices]; // vertices de distâncias mínimas conhecidas
   Arestas* aux; // ponteiro para a rota a ser seguida

   //Laço que inicializa os valores de distância da cidade de origem
   for (i = 0; i < vertices; i++) {
      if (custos[origem * vertices + i] != -1) { //Verifica se há ligação da cidade i com a cidade de origem
         ant[i] = origem;
         dist[i] = custos[(origem)*vertices+i];

      }
      else {
         ant[i]= -1;
         dist[i] = (int) HUGE_VAL;
      }
      visitada[i]=0;
   }
   visitada[origem] = 1; //Marca a cidade de origem como já visitada
   dist[origem] = 0; //Distância acumulada para chegar na cidade de orige pelo caminho mais curto (zero)

   // Laco principal do algorítmo
   do {
      // Busca a próxima cidade a ser visitada
      min = (int) HUGE_VAL;
      for (i=0; i<vertices; i++){
         if (!visitada[i]){ //Verifica se a cidade já foi visitada
            if ( dist[i]>=0 && dist[i]<min){ //Verifica qual cidade é a mais próxima
               min=dist[i];
               v=i;
            }
         }
      }

      // Laço que calcula as distâncias para a nova cidade visitada
      if ( (min != HUGE_VAL) && (v != destino ) ) { //Verifica se é válido visitar a cidade
         visitada[v] = 1;
         for (i = 0; i < vertices; i++){//Laço que inicializa os valores da nova cidade visitada
            if (!visitada[i]) { //Verifica se a cidade que será checada já foi visitada
               //Verifica se a cidade checada é valida (tem ligação com a cidade atual e distância a partir dela é menor)
               if (custos[v*vertices+i] != -1 && dist[v] + custos[v*vertices+i] < dist[i]) {
                  dist[i] = dist[v] + custos[v*vertices+i];
                  ant[i] =v;
               }
            }
         }
      }
   }while ((v != destino ) && (min != HUGE_VAL)); //Repete o processo até visitar todas as cidades e achar um caminho não infinito

   printf("\nViagem de %s\npara %s\n\n\n\n", cidades[origem].nome, cidades[destino].nome);
   if (min == HUGE_VAL) { //Verifica se não foi achado caminho válido
      printf("Nao ha um caminho por terra. Tente pegar um aviao.\n");
   }
   else {
      i=destino;
      for(i=destino; i!=-1; i=ant[i]){
         tmp[cont]=i;
         cont++;
      }
      for(i=cont; i>1; i--){
         v=0;
         for(aux=cidades[tmp[i-1]].rotas; aux!=NULL; aux=aux->prox){
            if(aux->cidade==tmp[i-2])
               v=aux->rota;
         }
         printf("Viaje de %s\nPara %s\nPela %s\n\n", cidades[tmp[i-1]].nome, cidades[tmp[i-2]].nome, estradas[v].nome);
         if(i!=2)
            printf("Depois\n");      
      }
      printf("Distancia total: %d km\n", dist[destino]);
   }
}

//Função que inicializa um vetor de caminhos
int* inicializa_caminho(Vertices* cidades, int n){
   int* novo = (int*) malloc (sizeof(int) * n * n);
   int i;
   Arestas* aux;
   for(i=0; i< n*n; i++){
      novo[i] =-1;
   }
   for(i=0; i<n; i++){
      for(aux=cidades[i].rotas; aux!=NULL; aux=aux->prox){
         novo[ i*n + aux->cidade] = aux->dist;
      }
   }
   return novo;
}

//Função que busca o melhor caminho
void busca(Vertices* cidades, Rotas* estradas, int n, int r){
   int origem;
   int destino;
   origem=le_string(n);
   destino=le_string(n);
   if(origem==destino){
      printf("Fique onde esta, voce ja esta no lugar desejado.\n");
   }else{
      int* caminho = inicializa_caminho(cidades, n);
      dijkstra(cidades, estradas, n,origem,destino,caminho);
      free(caminho);
   }
}

void libera_rotas(Rotas* estradas, int r){
   int i;
   for(i=0; i<r; i++){
      free(estradas[i].nome);
   }
   free(estradas);
}

void libera_grafo(Vertices* cidades, int c){
   int i;
   Arestas* aux;
   Arestas* ant;
   for(i=0; i<c; i++){
      free(cidades[i].nome);
      aux=cidades[i].rotas;
      while(aux!=NULL){
         ant=aux;
         aux=aux->prox;
         free(ant);
      }
   }
   free(cidades);
}

//Função principal do programa
int main(void){
   char* texto = ler_arquivo();
   int n = conta_n(texto);
   int r = conta_r(texto);
   Vertices* cidades=inicializa_cidades(n);
   Rotas* estradas=inicializa_estradas(r);

   interpreta(texto, cidades, estradas);
   imprime_existentes(cidades,n);
   busca(cidades, estradas, n, r);

   free(texto);
   libera_rotas(estradas, r);
   libera_grafo(cidades, n);
   return 0;
}
