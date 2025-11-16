/*Lívia Calado de Carvalho Dias 10737709
  Catarina Silva E Meirelles    10239324
  Beatriz de Assis Siqueira     10741570*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assinatura da codificar_imagem-vamos precisar dela 
void codificar_imagem(int altura, int largura, int matriz[altura][largura], char resultado[]);

void printImg(int altura, int largura, int matriz[altura][largura]){
   printf("\n----");
    for(int i = 0; i < altura; i++){
        printf("\n");
        for(int j = 0; j < largura; j++){ 
            printf(" %d", matriz[i][j]);
        }
   }
}

void copiarMatriz(  int tamanhoCopiaX,
                    int tamanhoCopiaY, 
                    int copia[tamanhoCopiaX][tamanhoCopiaY], 
                    int tamanhoOriginalX,
                    int tamanhoOriginalY, 
                    int original[tamanhoOriginalX][tamanhoOriginalY],
                    int inicioX, int fimX, int inicioY, int fimY){
    
    for(int i= 0; i< tamanhoCopiaX; i++){
        for(int j=0; j<tamanhoCopiaY; j++){
            copia[i][j] = original[i+inicioX][j+inicioY];
        }
    }
}

void cortar(int altura, int largura, int matriz[altura][largura], char resultado[]){
    int X2 = altura/2;//divisão inteira
    int X1 = altura-X2;
    int Y2 = largura/2;
    int Y1 = largura-Y2;
    printf("\n<%d><%d><%d><%d>\n", X1, X2, Y1, Y2);
    if(X1 != 0){
        if(Y1 != 0){
            int md1[X1][Y1];
            copiarMatriz(X1,Y1, md1, altura, largura, matriz, 0,X1,0,Y1);
            printImg(X1,Y1,md1);
            codificar_imagem(X1,Y1, md1, resultado);
        }
        if(Y2 != 0){
            int md2[X1][Y2];
            copiarMatriz(X1,Y2, md2, altura,largura, matriz, 0,X1,Y1,largura);
            printImg(X1,Y2,md2);
            codificar_imagem(X1,Y2, md2, resultado);
        }
    }
    if(X2 != 0){
        if(Y1 != 0){
            int md3[X2][Y1];
            copiarMatriz(X2,Y1, md3, altura,largura, matriz, X1,altura,0,Y1);
            printImg(X2,Y1,md3);
            codificar_imagem(X2,Y1, md3, resultado);
        }
        if(Y2 != 0){
            int md4[X2][Y2];
            copiarMatriz(X2,Y2, md4, altura,largura, matriz, X1,altura,Y1,largura);
            printImg(X2,Y2,md4);
            codificar_imagem(X2,Y2, md4, resultado);
        }
    }
}

void codificar_imagem(int altura, int largura, int matriz[altura][largura], char resultado[]){//cat
    //analisar se a imagem inteira está completa, se não, cortá-la
    char preenchimento[2];
    int referencia = matriz[altura-1][largura-1];
    //printf("\nreferencia =<%d>\n", referencia);

    if (referencia == 0){
            preenchimento[0] = 'B';
        }else{
            preenchimento[0] = 'P';
        }

    if (altura <= 1 && largura <= 1){
        strcat(resultado, preenchimento);
        //printf("\nAltura atual: %d, Larg: %d, item[]: <%d>\n", altura, largura, matriz[altura-1][largura-1]);
        return;
    }

    for(int i=0; i<altura; i++){
        for(int j=0; j<largura; j++){
            //printf("\nmatriz[%d][%d]= <%d>\n", i,j, matriz[i][j]);
            if (matriz[i][j] != referencia){
                preenchimento[0] = 'X';
                strcat(resultado, preenchimento);
                printf("\ncorte\n");
                cortar(altura, largura, matriz, resultado);
                return;
            }
        }
    } 

    strcat(resultado, preenchimento);
    printf("\n percorreu loop ->%s", resultado);

}

void modo_manual(char resultado[]){//Livia
    int largura, altura;
    printf("Modo Manual Ativado;\n");
    do{
        printf("Informe a largura da imagem: ");
        scanf("%d", &largura);
        printf("Informe a altura da imagem: ");
        scanf("%d", &altura);
        if (largura <= 0 || largura > 1024 || altura <= 0 || altura > 768){
            printf("Dimensões inválidas. A largura deve ser entre 1 e 1024, e a altura entre 1 e 768;\n->Tente novamente!\n");
        }
    }while (largura <= 0 || largura > 1024 || altura <= 0 || altura > 768);
    
    
    int matriz[altura][largura];
    printf("Informe os valores da matriz (0 para branco, 1 para preto):\n");
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            scanf("%d", &matriz[i][j]);
            if (matriz [i][j] != 0 && matriz[i][j] != 1){
                printf("Valor invalido na posição (%d, %d). Use 0 para branco e 1 para preto.\nTente novamente!\n", i, j);
                modo_manual(resultado);
                return;
            }
        }
    }
    codificar_imagem(altura, largura, matriz, resultado);
    return;
}

int modo_arquivo(char *file, char resultado[]){//bea
    int largura, altura;
    char tipo[3];
    char coment[1000];
    FILE *file;     

    file = fopen(file[1], "r");

    if(file == NULL){
        printf("Erro ao abrir o arquivo. Arquivo vazio.");
        return 1;
    }
  
    fgets(tipo, sizeof(tipo), file);
    while(fgets(coment, sizeof(coment), file)){
      if(coment[0] == '#') continue;
    }
    fscanf(file, "%d %d", &altura, &largura);
    int matriz[altura][largura];

    for(int i = 0; i <= altura; i++){
        for(int j = 0; j <= largura; j++){
            fscanf(file, "%d", &matriz[i][j]);
        }
    }
    fclose(file);
    codificar_imagem(altura, largura, matriz, resultado);

    return 0;
}


void exibir_ajuda(){
    printf("Uso: ImageEncoder [-? | -m | -f ARQ]\n");
    printf("Codifica imagens binários dadas em arquivos PBM ou por dados informados pelo usuário.\n\n");
    printf("Argumentos:\n");
    printf(" -?, --help : apresenta essa orientação na tela;\n");
    printf("-m, --manual : ativa o modo de entrada manual, em que o usuário fornece todos os dados da imagem infomando-os através do teclado;\n");
    printf("-f, --file : considera a imagem respresentada no arquivo PBM (Portable Bitmap)\n");
}

int main(int argc, char *argv[]){
    if(argc == 1 || strcmp(argv[1], "-?") == 0 || strcmp(argv[1], "--help") == 0){
        //mostra a função que exibe a ajuda
        exibir_ajuda();
        return 0;
    }

    char resultado[500];
    
    if (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "--manual") == 0){
        //ativa o modo manual
        modo_manual(resultado);
    }
    else if(strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0){
        //ativa o modo do arquivo
        int retARQ = modo_arquivo(argv[6], resultado);
        if (retARQ != 0){
            return 1;
        }
    }
    else{
        printf("Argumento inválido. Use -? ou --help para ver as opções disponíveis.\n");
        return 1;
    }
    printf("\n--->O resultado final é: %s\n\n", resultado);
    return 0;
}
