#include <stdio.h>
#include <stdlib.h>
typedef char info;
typedef struct Arvore
{
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
int percorrer(arvore *raiz1, arvore *raiz2){
	if(raiz1 == NULL && raiz2 == NULL)
		return (0);
	else
		if((raiz1 == NULL && raiz2 != NULL) || (raiz1 != NULL && raiz2 == NULL))
			return 1;
		else
			if(raiz1->dado == raiz2->dado)
				return (percorrer(raiz1 -> esq, raiz2 -> esq) > percorrer(raiz1 -> dir, raiz2 -> dir) ? percorrer(raiz1 -> esq, raiz2 -> esq) : percorrer(raiz1 -> dir, raiz2 -> dir));
		return (1);
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
	FILE *fp1, *fp2;
	arvore *raiz1 = NULL;
	arvore *raiz2 = NULL;
	info letra;
	if(!fopen("texto1.txt","r"))
		printf("%s\n", "sem arquivo 1");
	else
		fp1=fopen("texto1.txt","r");
	while (!feof(fp1)){
		letra = getc(fp1);
		if((letra!='\n') && (letra!=EOF) && (letra!='\r'))
			insere_arvore_ordenando(&raiz1,letra);
	}
	if(!fopen("texto2.txt","r"))
		printf("%s\n", "sem arquivo 2");
	else
		fp2=fopen("texto2.txt","r");
	while (!feof(fp2)){
		letra = getc(fp2);
		if((letra!='\n') && (letra!=EOF) && (letra!='\r'))
			insere_arvore_ordenando(&raiz2,letra);
	}
	printf("Arvore 1: ");
	printar_arvore(raiz1);
	printf("\nElementos no arvore 1 = %d ",contagem(raiz1));
	printf("\nAltura no arvore 1 = %d ",1+altura(raiz1));
	printf("\nEstrutura da Arvore 1:\n");
	printar_largura(raiz1);
	printf("\n\n");
	printf("Arvore 2: ");
	printar_arvore(raiz2);
	printf("\nElementos no arvore 2 = %d\n",contagem(raiz2));
	printf("Altura da arvore 2 = %d ",1+altura(raiz2));
	printf("\nEstrutura da Arvore 2:\n");
	printar_largura(raiz1);
	if(!percorrer(raiz1, raiz2))
		printf("\n\nArvores iguais.\n");
	else
		printf("\n\nArvores nao iguais.\n");
	return 0;
}