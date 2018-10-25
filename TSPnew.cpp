#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <vector>

using namespace std;

#define TAM 10

int nElementos;
vector <int> solInicial;

void ImprimeMatriz(int matriz[][TAM]){
    for(int i = 0; i < nElementos; i++) {
        for(int j = 0; j < nElementos; j++) {
            printf( "%d ", matriz[i][j]);
        }
        puts("");
    }

}

void ImprimeSolucao(vector <int> sol){
    for(int k = 0 ; k<=nElementos ; k++){
        printf("%d ", sol[k]);
    }
    puts("");
}

int vizinhoProx(int matriz[][TAM]){
    int caminho[nElementos] = {};
    int inseridos[nElementos] = {};

    caminho[0] = 0;
    inseridos[0] = 1;
    solInicial.push_back(0);

    for(int i = 0; i < nElementos; i++) {
        int valor_referencia = INT_MAX;
        int vizinho_selecionado = 0;

        for(int j = 0; j < nElementos; j++) {
            if(!inseridos[j] && valor_referencia > matriz[i][j]) {
                vizinho_selecionado = j;
                valor_referencia = matriz[i][j];
            }
        }

        caminho[i + 1] = vizinho_selecionado;
        inseridos[vizinho_selecionado] = 1;
        solInicial.push_back(vizinho_selecionado);
    }

    caminho[nElementos] = 0;
    solInicial.push_back(0);

    int custo = 0;

    for(int i = 0; i < nElementos; i++) {
        custo = custo + matriz[caminho[i]][caminho[i + 1]];
    } 

    return custo;  


}

int swap(int matriz[][TAM]){

    int solTemporaria[solInicial.size()];
    int melhorCusto = INT_MAX;

   
    for(int i=1 ; i<solInicial.size() ; i++){
        for(int j=i+1 ; j<solInicial.size() ; j++){
            //copiar a solucao inicial pra solucao que vai ser alterada
            for(int k=0 ; k<=solInicial.size() ; k++){
                solTemporaria[k] = solInicial[k];
            }
            
            //troca os valores
            int aux = solTemporaria[i];
            solTemporaria[i] = solTemporaria[j];
            solTemporaria[j] = aux;

            //calcula o novo custo
            int custoAtual = 0;
            for(int w = 0; w < nElementos; w++) {
                custoAtual = custoAtual + matriz[solTemporaria[w]][solTemporaria[w + 1]];
            }
            if(custoAtual<melhorCusto){
                melhorCusto = custoAtual;
            } 

        }
    }
    
    return melhorCusto;
}

vector <int> TrocaElementos(vector <int> Lista){
    int indiceMax = Lista.size()-1;
    for(int i = 0 ; i<Lista.size() ; i++){
       int aux = Lista[i];
       Lista[i] = Lista[indiceMax];
       Lista[indiceMax] = aux;
       indiceMax--;
   }

   return Lista;
}

void twootp(int matriz[][TAM]){
    vector <int> ListaTemporaria;
    int melhorCusto = INT_MAX;
    
    for(int i=1 ; i<TAM-1 ; i++){ //percorre do matriz[1] até matriz[n-2]
        vector <int> ListaTemporaria;
        for(int j=i ; j<TAM-1 ; j++){
            ListaTemporaria.push_back(solInicial[j]);
            
        }
        vector <int> novaLista = TrocaElementos(ListaTemporaria);
        //CalculaNovoCusto;
        int custoAtual = 0;
        for(int w = 0; w < nElementos; w++) {
            custoAtual = custoAtual + matriz[novaLista[w]][novaLista[w + 1]];
        }
        if(custoAtual<melhorCusto){
            melhorCusto = custoAtual;
        } 

    }
    //cout << melhorCusto << endl;

}

int main(){

    //LER ARQUIVO
    FILE* fp = fopen("arquivo.txt", "r");

    fscanf(fp, "%d", &nElementos);

    int matriz[TAM][TAM] = {};
    
    for(int i = 0; i < nElementos; i++) {
        for(int j = 0; j < nElementos; j++) {
            fscanf(fp, "%d ", &matriz[i][j]);
        }
    }

    //ImprimeMatriz(matriz);

    //Calclar custo pelo método dos vizinhos próximos
    int custo = vizinhoProx(matriz);
    cout << "Custo pelo método dos vizinhos próximos: " << custo << endl;
    cout << "A solucao dos vizinhos mais próximos seguiu a sequencia: ";
    ImprimeSolucao(solInicial);

    //Melhorar o custo utilizando o swap
    int CustoSwap = swap(matriz);
    cout << "A solucao utilizando o swap foi de: " << CustoSwap << endl;

    //Melhorar o custo utilizando o 2-OTP

    twootp(matriz);

    return 0;
}

