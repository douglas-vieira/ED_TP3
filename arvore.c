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
		if(raiz->esq != NULL);
			printar_arvore(raiz->esq);
		printf("%c-\n",raiz->dado);
		if(raiz->dir != NULL);
			printar_arvore(raiz->dir);
	}
	return;
}

arvore *pesquisa_arvore(arvore *raiz, info chave)
{
	arvore *aux=NULL;
	if(raiz!=NULL)
	{
		if(raiz->dado == chave)
			aux=raiz;
		if(aux==NULL)
			aux=pesquisa_arvore(raiz->esq, chave);
		if(aux==NULL)
			aux=pesquisa_arvore(raiz->dir, chave);
	}
	return aux;
}

arvore *pesquisa_pai(arvore *raiz, info chave, arvore **pai)
{
	arvore *aux=NULL;
	if(raiz!=NULL)
	{
		if(raiz->dado == chave)
			aux=raiz;
		if(aux==NULL)
		{
			*pai=raiz;
			aux=pesquisa_pai(raiz->esq, chave, pai);
		}
		if(aux==NULL)
		{
			aux=pesquisa_pai(raiz->dir, chave, pai);
			*pai=raiz;
		}
	}
	if(raiz==NULL)
		*pai=NULL;
	return aux;
}

int main()
{
	FILE *fp;
	arvore *chave,*pai;
	if(!fopen("texto.txt","r"))
		printf("%s\n", "sem arquivo");
	else
		fp=fopen("texto.txt","r");
	arvore *raiz = NULL;
	info letra;
	for(;!feof(fp);)
	{
		letra = getc(fp);
		if((letra!='\n') && (letra!=EOF) && (letra!='\r'))
			insere_arvore_ordenando(&raiz,letra);
	}
	printar_arvore(raiz);
	printf("digite a chave:");
	//scanf("%c",&letra);
	letra='a';
	chave=pesquisa_arvore(raiz,letra);
	pesquisa_pai(raiz,letra,&pai);
	if(chave==NULL)
		printf("chave não encontrada\n");
	else
	printf("chave encontrada: %c\n",chave->dado);

	if((pai == NULL)&&(pai->dado == -119))
		printf("Não tem pai\n");
	else
	printf("pai encontrado: %c\n",pai->dado);
	return 0;

}