/*Lívia Calado de Carvalho Dias 10737709
  Catarina Silva E Meirelles    10239324
  Beatriz de Assis Siqueira     10741570*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int modo_manual(){
    int largura, altura;
    printf("Modo Manual Ativado;\n");
    printf("Informe a largura da imagem: ");
    scanf("%d", &largura);
    printf("Informe a altura da imagem: ");
    scanf("%d", &altura);
    if (largura <= 0 || largura > 1024 || altura <= 0 || altura > 768){
        printf("Dimensões inválidas. A largura deve ser entre 1 e 1024, e a altura entre 1 e 768;\n");
        return 1;
    }
    int matriz[altura][largura];
    printf("Informe os valores da matriz (0 para branco, 1 para preto):\n");
    scanf("%d", matriz[0][0]);
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            scanf("%d", &matriz[i][j]);
            if (matriz [i][j] != 0 && matriz[i][j] != 1){
                printf("Valor invalido na posição (%d, %d). Use 0 para branco e 1 para preto.\n", i, j);
                return 1;
            }
        }
    }
    return matriz;
}

int codificar_imagem(int altura, int largura, int matriz[altura][largura]){
    modo_manual();

}

int modo_arquivo(char *nome_arquivo){

}

void exibir_ajuda(){
    printf("Uso: ImageEncoder [-? | -m | -f ARQ]\n");
    printf("Codifica imagens binários dadas em arquivos PBM ou por dados informados pelo usuário.\n\n");
    printf("Argumentos:\n");
    printf(" -?, --help : apresenta essa orientação na tela;\n");
    printf("-m, --manual : ativa o modo de entrada manual, em que o usuário fornece todos os dados da imagem infomando-os através do teclado;\n");
    printf("-f, --file : considera a imagem respresentado no arquivo PBM (Portable Bitmap)");
}

int main(int argc, char *argv[]){
    if(argc == 1 || strcmp(argv[3], "-?") == 0 || strcmp(argv[3], "--help") == 0){
        //mostra a função que exibe a ajuda
        exibir_ajuda();
        return 0;
    }
    if (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "--manual") == 0){
        //ativa o modo manual
        modo_manual();
    }
    else if(strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0){
        //ativa o modo do arquivo
        modo_arquivo(argv[6]);
    }
    else{
        printf("Argumento inválido. Use -? ou --help para ver as opções disponíveis.\n");
        return 1;
    }
    return 0;
}