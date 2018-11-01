#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <vector>
#include <time.h>
using namespace std;

#define TAM 176

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


int swap(int matriz[][TAM], int *melhorCaminhoSwap, int soluInicial[]){

    int solTemporaria[solInicial.size()];
    int melhorCusto = INT_MAX;

   
    for(int i=1 ; i<solInicial.size() -1; i++){
        for(int j=i+1 ; j<solInicial.size()-2; j++){
            //copiar a solucao inicial pra solucao que vai ser alterada
            for(int k=0 ; k<=solInicial.size() ; k++){
                solTemporaria[k] = soluInicial[k];
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
                //salvar o melhor caminho
                for(int q=0 ; q<solInicial.size() ; q++){
                    melhorCaminhoSwap[q] = solTemporaria[q];
                }
            } 

        }
    }
    
    return melhorCusto;
}


void otpmove(int inicio, int fim, int nElementos, int *array) // inverte os valores do array no algoritmo 2-otp // 
{
    int tam, i, p1, p2, aux;
    if(inicio>fim){
	    tam=nElementos-inicio+fim+1;
    }
    else{
	    tam=fim-inicio+1;
    }
    p1=inicio;
    p2=fim;
    for(i=0;i<tam/2;i++){
	    aux=array[p1];
        array[p1]=array[p2];
	    array[p2]=aux;
	    p1=(p1==nElementos-1)?0:p1+1;
	    p2=(p2==0)?nElementos-1:p2-1;
    }
    
}


int CalculaCusto(int matriz[][TAM], int *array){
    int custo = 0;
    for(int m = 0; m <solInicial.size()-1; m++) {
        custo = custo + matriz[array[m+1]][array[m]];        
    } 
    return custo;
}

int twootp(int matriz[][TAM], int CustoInicial, int melhorSolucao[], int soluInicial[]){
    int solTemporaria[solInicial.size()];
    int custoAtual=0;
    int melhorCusto = CustoInicial;

    //Iniciando a melhor solução como sendo a solução dos vizinhos mais próximos
    for(int w=0 ; w<solInicial.size() ; w++){
        melhorSolucao[w] = soluInicial[w];
    }

    //Percorrer a solução buscando uma melhor
    for(int i = 1 ; i<solInicial.size()-1 ; i++){
        for (int j = i ; j<solInicial.size()-2 ; j++){
            if(j==i) continue; 

            //Copiando para a solução temporária a heurística dos vizinhos mais proximos
            for(int k=0 ; k<solInicial.size() ; k++){
                solTemporaria[k] = soluInicial[k];
            }

            //custoAtual = CustoInicial - matriz[solTemporaria[i]][solTemporaria[i-1]] - matriz[solTemporaria[j]][solTemporaria[j+1]]; //removendo o custo 
            
            //Trocar a posicao de determinada fatia da solucao temporaria que inicialmente é igual a solucao do vizinho
            int numElementosTrocados = (j-i+1);
            otpmove(i, j, numElementosTrocados, solTemporaria);

            //Calcula o novo custo
            custoAtual = CalculaCusto(matriz,solTemporaria);   

            //custoAtual = custoAtual + matriz[solTemporaria[i]][solTemporaria[i-1]] + matriz[solTemporaria[j]][solTemporaria[j+1]]; //colocando o custo dos vertices que foram trocados

            if(custoAtual<melhorCusto){
                //cout << custoAtual << endl;
                melhorCusto = custoAtual;
                for(int k=0 ; k<solInicial.size() ; k++){
                    melhorSolucao[k] = solTemporaria[k];
                }
            }
        }
    }     

    int x = CalculaCusto(matriz, melhorSolucao);

    return x;    
   
}
int VND(int matriz[][TAM], int solInicial[], int melhorSolucao[]){
    int melhorCusto=INT_MAX;
    int custoAtual1, custoAtual2;
    int i=0, k = 0, j=0;

    while(i<3){
        while(k<3){
            custoAtual1 = swap(matriz, melhorSolucao, solInicial);
            if(custoAtual1<melhorCusto){
                melhorCusto = custoAtual1;
                k=0;
            }else{
                k++;
            }
        }
        while(j<3){
            custoAtual2 = twootp(matriz, melhorCusto, melhorSolucao, melhorSolucao);
            if(custoAtual2<melhorCusto){
                melhorCusto = custoAtual2;
                j=0;
            }else{
                j++;
            }
        }
        i++;
    }

    return melhorCusto;

}

vector <int> ConstrucaoSolucao(vector <int> candidatos, int alfa){
    vector <int> solucao;
    int r;
    candidatos.erase(candidatos.begin());
    int tamanhoVector = candidatos.size();
    
    while(solucao.size()<tamanhoVector-1){
        int tamanhoRand = ((alfa * candidatos.size()))/100;
        //Gerar uma nova solucao com parte randomicamente  
        srand(time(NULL));
        if(tamanhoRand == 0)
            tamanhoRand = 1;
        r = (rand() % (tamanhoRand));//indice que será escolhido
        solucao.push_back(candidatos[r]);
        candidatos.erase(candidatos.begin()+r);
        
    }
    solucao.push_back(solucao[0]);

    //ImprimeSolucao(solucao);
    //puts("");
    return solucao;

}

int GRASP(int matriz[][TAM], vector <int> melhorSequencia, int soluFinal[], int alfa, int numIteracoes){
    int solVND[solInicial.size()]={};
    int melhorCusto;
    int custoAtual;
    int count = 0;
    int aux;

   
    while(count<numIteracoes){
        melhorSequencia = ConstrucaoSolucao(solInicial, alfa);

        //ImprimeSolucao(melhorSequencia);
        for(int i=0 ; i<melhorSequencia.size(); i++){
            solVND[i] = melhorSequencia[i];        
        }

        custoAtual = VND(matriz, solVND, soluFinal);

        if(custoAtual<melhorCusto){
            melhorCusto = custoAtual;

            for(int k=0 ; k<solInicial.size(); k++){
                soluFinal[k] = melhorSequencia[k];
            }
        }
        count++;
    }

    return melhorCusto;

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
    int CustoInicial = custo;
    cout << "Custo pelo método dos vizinhos próximos: " << custo << endl;
    cout << "A solucao dos vizinhos mais próximos seguiu a sequencia: ";
    ImprimeSolucao(solInicial);
    puts("");

    //Melhorar o custo utilizando o swap
    int firstSol[nElementos+1] = {};
    for(int a=0 ; a<=nElementos ; a++){
        firstSol[a] = solInicial[a];
    }
    int melhorCaminhoSwap[nElementos+1] = {};
    int CustoSwap = swap(matriz, melhorCaminhoSwap, firstSol);
    cout << "Custo utilizando o swap foi de: " << CustoSwap << endl;
    cout << "A solucao utilizando o swap seguiu a sequencia: ";
    for(int i=0 ; i<=nElementos ; i++){
        printf("%d ", melhorCaminhoSwap[i]);
    }
    puts("");
    puts("");
    

    //Melhorar o custo utilizando o 2-OTP
    int melhorSolucaoOTP[nElementos+1] = {};
    int custo2OTP=0;
    custo2OTP = twootp(matriz, CustoInicial, melhorSolucaoOTP, firstSol);
    cout << "Custo utilizando o 2-otp foi de: " << custo2OTP << endl;
    

    cout << "A solucao utilizando o 2-otp seguiu a sequencia: ";
    for(int j=0 ; j<=nElementos ; j++){
        printf("%d ", melhorSolucaoOTP[j]);
    }
    puts("");
    puts("");    

    int bestsolution[nElementos+1] = {};
    //Melhorar o custo utilizando o VND
    int CustoVND = VND(matriz, firstSol, bestsolution);
    cout << "O melhor custo encontrado utilizando o VND foi de: " << CustoVND << endl;
    cout << "A solução após o VND seguiu a sequencia: ";
    for(int v=0 ; v<=nElementos ; v++){
        printf("%d ", bestsolution[v]);
    } 
    puts("");

    //Utilizando GRASP
    int CustoGrasp;
    vector <int> melhorSequenciaGrasp;
    int SequenciaFinal[nElementos+1] = {};

    CustoGrasp = GRASP(matriz, melhorSequenciaGrasp, SequenciaFinal, 0, 80); // alfa e num de iterações
    puts("");
    cout << "O custo final utilizando o GRASP foi de: " << CustoGrasp << endl;
    cout << "A solucao após o GRASP seguiu a sequencia: ";

    for(int q=0 ; q<=nElementos ; q++){
        printf("%d ", SequenciaFinal[q]);
    }
    puts("");



    
    return 0;
}

