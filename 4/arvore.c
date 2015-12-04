#include <stdio.h>
#include <stdlib.h>
typedef char info;


typedef struct Arvore
{
	struct Arvore *filho;
	info dado;
	struct Arvore *irmao;
	int filhos;
}arvore;

arvore *busca_chave(arvore *raiz, info chave);
void insere_arvore_generica (arvore **raiz, FILE *fp);
//int altura (arvore *raiz);
void printar_arvore(arvore *raiz);


arvore *busca_chave(arvore *raiz, info chave)
{
	arvore *retorno1,*retorno2;
	if(raiz==NULL)
		return(NULL);
	printf("chave=%c\n",chave );

	if (raiz->dado ==  chave)
	{
			return raiz;
	}
	else
	{
		if(raiz->filho != NULL)
		{
			retorno1=busca_chave(raiz->filho,chave);
		}
		if(raiz->irmao != NULL)
		{
			retorno2=busca_chave(raiz->irmao,chave);
		}
		return(retorno1!=NULL?retorno1:retorno2);
	}
}

void insere_arvore_generica (arvore **raiz, FILE *fp)
{
	int n;
	info c, aux;
	arvore *ptr_aux, *inserir;
	while (!feof(fp))
	{
		c = getc(fp);
		printf("%c ",c );
		//fscanf(fp,"%d",&n);
		aux=getc(fp);
		n=atoi(&aux);
		printf("n= %d\n",n );
		//aux = getc(fp);
		//printf("c = %c =\n",c );
		if(NULL)
		{
			if(*raiz!=NULL)
			{
				ptr_aux = busca_chave(*raiz,c);
				//ptr_aux->dado == c ? printf("%s\n","Igual" ):printf("%s\n","diferente" );
				printf("busca = %c\n", ptr_aux->dado);
				if (ptr_aux == NULL)
				{
					printf("%s\n", "arvore vazia.");
					return;
				}
			}
			else
			{
				*raiz = (arvore *)calloc (1,sizeof(arvore));
				(*raiz)->dado = c;
				(*raiz)->filhos = n;
			}
			for (int i = 0; i < n; ++i)
			{
				inserir = (arvore *)calloc (1,sizeof(arvore));
				inserir->dado = getc (fp);
				if (ptr_aux->filho == NULL)
				{
					ptr_aux->filho = inserir;
					ptr_aux=ptr_aux->filho;
				}
				else
				{
					ptr_aux->irmao = inserir;
					ptr_aux = ptr_aux->irmao;
				}
			}
		}
	}
	return;
}

/*int altura (arvore *raiz)
{
	int alt_dir, alt_esq;
	if (raiz == NULL)
		return -1;
	else
	{
		alt_dir = altura (raiz->dir);
		alt_esq = altura (raiz->esq);
		return((alt_dir > alt_esq) ? (1 + alt_dir) : (1 + alt_esq));
	}
}*/


/*int percorrer(arvore *raiz1, arvore *raiz2)
{
	int retorno1=0,retorno2=0;
	if(raiz1 == NULL && raiz2 == NULL)
	{
		return (0);
	}
	else
	{
		if((raiz1 == NULL && raiz2 != NULL) || (raiz1 != NULL && raiz2 == NULL))
		{
			return 1;
		}
		else
		{
			if(raiz1->dado == raiz2->dado)
			{
				retorno1=percorrer(raiz1 -> esq, raiz2 -> esq);
				retorno2=percorrer(raiz1 -> dir, raiz2 -> dir);
				return (retorno1 > retorno2 ? retorno1 : retorno2);
			}
		}
	}
		return (1);
}*/


void printar_arvore(arvore *raiz)
{
	if(raiz!=NULL)
	{
		if(raiz->irmao != NULL);
			//printf("%c",raiz->dado);
			printar_arvore(raiz->irmao);
		if(raiz->filho != NULL);
			printar_arvore(raiz->filho);
	}
	return;
}

/* int contagem(arvore *raiz)
 {
    return ((raiz != NULL) ? (contagem(raiz->esq) + contagem(raiz->dir) + 1) : 0);
 }*/

int main()
{
	FILE *fp1;
	arvore *raiz1 = NULL;

	if(!fopen("texto1.txt","r"))
		printf("%s\n", "sem arquivo 1");
	else
		fp1=fopen("texto1.txt","r");
	insere_arvore_generica (&raiz1, fp1);
	printf("Arvore 1: ");
	printar_arvore(raiz1);
	//printf("\nElementos no arvore 1 = %d ",contagem(raiz1));
	//printf("\nAltura no arvore 1 = %d ",altura(raiz1));
	//printf("\n");
	return 0;
}