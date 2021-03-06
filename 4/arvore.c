#include <stdio.h>
#include <stdlib.h>
typedef char info;
typedef struct Arvore{
	struct Arvore *filho;
	info dado;
	struct Arvore *irmao;
	int filhos;
}arvore;
arvore *busca_chave(arvore *raiz, info chave){
	arvore *retorno=NULL;
	if(raiz==NULL)
		return(NULL);
	if (raiz->dado ==  chave)
		retorno=raiz;
	if(retorno == NULL)
		retorno=busca_chave(raiz->filho,chave);
	if(retorno == NULL)
		retorno=busca_chave(raiz->irmao,chave);
	return(retorno);
}
void insere_arvore_generica (arvore **raiz, FILE *fp){
	int n;
	info c, aux;
	arvore *ptr_aux;
	while (!feof(fp)){
		ptr_aux=NULL;
		aux=c='\0';
		n=0;
		c = getc(fp);
		if((c!='\n') && (c!='\r') && (c!=EOF)){
			aux=getc(fp);
			n=atoi(&aux);
			if(n>0){
				if((*raiz)==NULL){
					*raiz=(arvore *)calloc (1,sizeof(arvore));
					(*raiz)->dado = c;
					(*raiz)->filhos = n;
					ptr_aux=(*raiz);
					ptr_aux->filho = (arvore *)calloc (1,sizeof(arvore));
					ptr_aux->filho->dado = getc(fp);
					ptr_aux=ptr_aux->filho;
					for (c=getc(fp); ((c!='\n') && (c!='\r') && (c!=EOF)) ; c=getc(fp)){
						ptr_aux->irmao=(arvore *)calloc (1,sizeof(arvore));
						ptr_aux->irmao->dado=c;
						ptr_aux=ptr_aux->irmao;
					}
				}
				else{
					ptr_aux = busca_chave(*raiz,c);
					ptr_aux->filhos = n;
					ptr_aux->filho = (arvore *)calloc (1,sizeof(arvore));
					ptr_aux->filho->dado = getc(fp);
					ptr_aux=ptr_aux->filho;
					for (c=getc(fp); ((c!='\n') && (c!='\r')) ; c=getc(fp)){
						ptr_aux->irmao=(arvore *)calloc (1,sizeof(arvore));
						ptr_aux->irmao->dado=c;
						ptr_aux=ptr_aux->irmao;
					}
				}
			}
		}
	}
	return;
}
int altura (arvore *raiz){
	int alt_irmao, alt_filho;
	if (raiz == NULL)
		return -1;
	else{
		alt_irmao = altura (raiz->irmao);
		alt_filho = altura (raiz->filho);
		return((alt_irmao > alt_filho) ? (1 + alt_irmao) : (1 + alt_filho));
	}
}
void printar_arvore(arvore *raiz){
	if(raiz!=NULL){
		if(raiz->irmao != NULL);
			printar_arvore(raiz->irmao);
		printf("%c -> %d filhos\n",raiz->dado,raiz->filhos);
		if(raiz->filho != NULL);
			printar_arvore(raiz->filho);
	}
	return;
}
int contagem(arvore *raiz){
	return ((raiz != NULL) ? (contagem(raiz->filho) + contagem(raiz->irmao) + 1) : 0);
}
void printar_nivel(arvore* raiz, int nivel){
    if (nivel == 1)
        printf("%c ", raiz->dado);
    else if (nivel > 1){
       if(raiz->filho!=NULL)
	       	printar_nivel(raiz->filho, nivel-1);
       else
    	   	printf(" ");
       if(raiz->irmao!=NULL)
       		printar_nivel(raiz->irmao, nivel-1);
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
	if(!fopen("texto1.txt","r"))
		printf("%s\n", "sem arquivo 1");
	else
		fp1=fopen("texto1.txt","r");
	insere_arvore_generica (&raiz1, fp1);
	printf("Elementos no arvore 1 = %d ",contagem(raiz1));
	printf("\nAltura no arvore 1 = %d\n",1+altura(raiz1));
	printf("Nodos e filhos:\n");
	printar_arvore(raiz1);
	printf("Estrutura Arvore:\n");
	printar_largura(raiz1);
	return 0;
}