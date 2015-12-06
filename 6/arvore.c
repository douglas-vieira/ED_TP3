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
		return;
	}
	return(letra > (*raiz)->dado) ? insere_arvore_ordenando(&(*raiz)->dir, letra): insere_arvore_ordenando(&(*raiz)->esq, letra);	
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
int contagem(arvore *raiz){
   return ((raiz != NULL) ? (contagem(raiz->esq) + contagem(raiz->dir) + 1) : 0);
}
void percorre_arvore(arvore *raiz, char vet[], int *i){
	if(raiz!=NULL){
		vet[*i] = raiz->dado;
		*i=*i+1;
		if(raiz->esq != NULL);
			percorre_arvore(raiz->esq,vet, i);
		if(raiz->dir != NULL);
			percorre_arvore(raiz->dir,vet, i);
	}
	return;
}
void retira_elemento_2(arvore* raiz) {
    if (raiz != NULL){
	    if(raiz->esq != NULL);
	    	retira_elemento_2(raiz->esq);
	    if(raiz->dir != NULL);
	    	retira_elemento_2(raiz->dir);
	    free(raiz);
    }
}
void retira_elemento(arvore **raiz){
	int cont=contagem(*raiz), i=0;
	char chave;
	char *vet=(char*) calloc(1,cont*sizeof(char));
	percorre_arvore(*raiz,vet,&i);
	*raiz=NULL;
	printf("\nDigite a chave de exclusao:");
	scanf("%c",&chave);
	getchar();
	for (int i = 0; i < cont; ++i){
		if(vet[i]>chave)
			insere_arvore_ordenando(raiz,vet[i]);
	}
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
void printar_arvore(arvore *raiz){
	if(raiz){
		if(raiz->esq != NULL);
			printar_arvore(raiz->esq);
		printf("%c ",raiz->dado);
		if(raiz->dir != NULL);
			printar_arvore(raiz->dir);
	}
	return;
}
int main(){
	FILE *fp1;
	arvore *raiz1 = NULL;
	info letra1;
	if(((fp1=fopen("texto1.txt","r"))==NULL)){
		printf("%s\n", "sem arquivos necessarios");
		exit (1);
	}
	while (!feof(fp1)){
		letra1 = getc(fp1);
		if((letra1!='\n') && (letra1!=EOF) && (letra1!='\r'))
			insere_arvore_ordenando(&raiz1,letra1);
	}
	printf("\n\tANTES DE EXCLUIR\n\nArvore em sequencia: ");
	printar_arvore(raiz1);
	printf("\nElementos no arvore 1 = %d ",contagem(raiz1));
	printf("\nAltura no arvore 1 = %d\n",1+altura(raiz1));
	printf("Estrutura da Arvore:\n");
	printar_largura(raiz1);
	retira_elemento(&raiz1);
	printf("\n\tDEPOIS DE EXCLUIR\n\nArvore em sequencia: ");
	printar_arvore(raiz1);
	printf("\nElementos no arvore 1 = %d ",contagem(raiz1));
	printf("\nAltura no arvore 1 = %d\n",1+altura(raiz1));
	printf("Estrutura da Arvore:\n");
	printar_largura(raiz1);
	return 0;
}