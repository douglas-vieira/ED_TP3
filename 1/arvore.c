#include <stdio.h>
#include <stdlib.h>
typedef char info;
typedef struct Arvore{
	struct Arvore *dir;
	info dado;
	struct Arvore *esq;
}arvore;
int contagem(arvore *raiz){
   return ((raiz != NULL) ? (contagem(raiz->esq) + contagem(raiz->dir) + 1) : 0);
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
void insere_arvore_ordenando(arvore **raiz, info letra){
	if(*raiz==NULL){
		 arvore *inserir = (arvore *)calloc (1,sizeof(arvore));
		*raiz = inserir;
		(*raiz)->dado=letra;
	}
	else
		if(letra > (*raiz)->dado)
			insere_arvore_ordenando(&(*raiz)->dir, letra);
		else
			if (letra < (*raiz)->dado)
				insere_arvore_ordenando(&(*raiz)->esq, letra);
	return;
}
void printar_arvore(arvore *raiz){
	if(raiz!=NULL){
		printf("%c ",raiz->dado);
		if(raiz->esq != NULL);
			printar_arvore(raiz->esq);
		if(raiz->dir != NULL);
			printar_arvore(raiz->dir);
	}
	return;
}
int main(){
	FILE *fp;
	arvore *raiz = NULL;
	info letra;
	if(!fopen("texto.txt","r"))
		printf("%s\n", "sem arquivo");
	else
		fp=fopen("texto.txt","r");
	while(!feof(fp)){
		letra = getc(fp);
		if((letra!='\n') && (letra!=EOF) && (letra!='\r'))
			insere_arvore_ordenando(&raiz,letra);
	}
	printf("Arvore: ");
	printar_arvore(raiz);
	printf("\nElementos na arvore = %d\n",contagem(raiz));
	printf("Altura da arvore = %d ",altura(raiz));
	return 0;
}