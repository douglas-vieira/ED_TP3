#include <stdio.h>
#include <stdlib.h>
typedef char info;
typedef struct Arvore{
	struct Arvore *dir;
	info dado;
	struct Arvore *esq;
}arvore;
void insere_arvore_ordenando(arvore **raiz, info letra){
	if(*raiz==NULL){
		arvore *inserir = (arvore *)calloc (1,sizeof(arvore));
		*raiz = inserir;
		(*raiz)->dado=letra;
	}
	else
		(letra > (*raiz)->dado) ? insere_arvore_ordenando(&(*raiz)->dir, letra): insere_arvore_ordenando(&(*raiz)->esq, letra);
	return;
}
int altura (arvore *raiz){
	int alt_dir, alt_esq;
	if (raiz == NULL)
		return -1;
	else{
		alt_dir = altura (raiz->dir);
		alt_esq = altura (raiz->esq);
		return((alt_dir > alt_esq) ? (1 + alt_dir) : (1 + alt_esq));
	}
}
void printar_arvore(arvore *raiz){
	if(raiz!=NULL){
		if(raiz->esq != NULL);
			printar_arvore(raiz->esq);
		printf("%c ",raiz->dado);
		if(raiz->dir != NULL);
			printar_arvore(raiz->dir);
	}
	return;
}
int contagem(arvore *raiz){
   return ((raiz != NULL) ? (contagem(raiz->esq) + contagem(raiz->dir) + 1) : 0);
}
void printar_nivel(arvore* raiz, int nivel){
    if (nivel == 1)
        printf("%c ", raiz->dado);
    else if (nivel > 1){
       if(raiz->esq!=NULL)
	       	printar_nivel(raiz->esq, nivel-1);
       else
    	   	printf(" ");
       if(raiz->dir!=NULL)
       		printar_nivel(raiz->dir, nivel-1);
       else
       		printf(" ");
   }
}
void printar_largura(arvore* raiz){
    if (raiz)
	    for (int i=1; i<=(altura(raiz)+1); i++){
	        printar_nivel(raiz, i);
	        printf("\n");
	    }
}
int main(){
	FILE *fp1;
	arvore *raiz1 = NULL;
	info letra1;
	int direita, esquerda, resultado;
	if(((fp1=fopen("texto1.txt","r"))==NULL)){
		printf("%s\n", "sem arquivos necessarios");
		exit (1);
	}
	while (!feof(fp1)){
		letra1 = getc(fp1);
		if((letra1!='\n') && (letra1!=EOF) && (letra1!='\r'))
			insere_arvore_ordenando(&raiz1,letra1);
	}
	printf("Arvore: ");
	printar_arvore(raiz1);
	printf("\nAltura da arvore = %d\n",1+altura(raiz1));
	printf("Elementos na arvore = %d ",contagem(raiz1));
	direita=contagem(raiz1->dir);
	esquerda=contagem(raiz1->esq);
	printf("\nElementos a direita da raiz = %d\n",direita);
	printf("Elementos a esquerda da raiz = %d\n",esquerda);
	printf("Estrutura da Arvore:\n\n");
	printar_largura(raiz1);
	direita >= esquerda ? (resultado = (direita - esquerda)) : (resultado = (esquerda - direita));
	resultado > 1 ? printf("\n\tArvore desbalanceada\n") : printf("\n\tArvore balanceada\n");
	return 0;
}