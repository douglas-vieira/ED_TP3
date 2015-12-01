#include <stdio.h>
#include <stdlib.h>
typedef char info;

typedef struct Arvore
{
	struct Arvore *dir;
	info dado;
	struct Arvore *esq;
}arvore;

void insere_arvore_ordenando(arvore **raiz, info letra)
{
	if(*raiz==NULL)
	{
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

void printar_arvore(arvore *raiz)
{
	if(raiz!=NULL)
	{
		printf("%c ",raiz->dado);
		if(raiz->esq != NULL);
			printar_arvore(raiz->esq);
		if(raiz->dir != NULL);
			printar_arvore(raiz->dir);
	}
	return;
}
int main()
{
	FILE *fp;
	arvore *raiz = NULL;
	info letra;
	if(!fopen("texto.txt","r"))
		printf("%s\n", "sem arquivo");
	else
		fp=fopen("texto.txt","r");
	while(!feof(fp))
	{
		letra = getc(fp);
		if((letra!='\n') && (letra!=EOF) && (letra!='\r'))
			insere_arvore_ordenando(&raiz,letra);
	}
	printar_arvore(raiz);
	printf("\n");
	return 0;
}