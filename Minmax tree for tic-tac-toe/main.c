#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

typedef struct gametree{
    char table[4][4];
    int nr_of_spaces;
    char jucator;
    char win;
    int val;
    int nivel;
    struct gametree **next;
}gametree;

int poz1[9],poz2[9];


/* Functie de initializare a arborelui. */
void init_Tree(gametree **tree,int n)
{    int i;
    (*tree)=(gametree *)malloc(sizeof(gametree));
    (*tree)->nr_of_spaces=n;
    (*tree)->win='F';
    if((*tree)->nr_of_spaces!=0)
    {
        (*tree)->next=(gametree**)malloc((n+1)*sizeof(gametree*));    
        for(i=0;i<n;i++)
            (*tree)->next[i]=NULL;
    }
}


/* Functie care numara spatiile care nu au fost deja ocupate in
tabloul de X si O ,si, de asemenea, retine in 2 vectori declarati global
pozitile acestor locuri. */
int nr_aparitii(char t[][4])
{
    int i,j,k=0;

    for(i=0;i<3;i++)    
    {
        for(j=0;j<3;j++)
        {
            if(t[i][j]=='-')
            {
                poz1[k]=i;
                poz2[k]=j;
                k++;
            }
        }
            
    }
    return k;
}

/* Functie care verifica daca jocul s-a terminat , fie jucatorul X , fie
jucatorul 0 , a castigat , intorcand 1 ,sau 0 in cazul in care niciunul nu
a castigat si jocul continua. Se verifica pe diagonala principala , secundara,
pe linii si coloane. */
int verifica_castig(char table[][4])
{
    int i,j,count1=0,count2=0,count3=0,count4=0;
    for(i=0;i<3;i++)
    {
        count1=0;
        count2=0;
        for(j=0;j<3;j++)
        {
            if(table[i][j]=='O')
                count1++;
            if(table[j][i]=='O')
                count2++;
        }
        if(table[i][i]=='O')
            count3++;
        if(table[i][3-i-1]=='O')
            count4++;
        if(count1==3 || count2==3 || count3==3 || count4==3)
            return 1;
    }
    count3=0;
    count4=0;
    for(i=0;i<3;i++)
    {
        count1=0;
        count2=0;
        for(j=0;j<3;j++)
        {
            if(table[i][j]=='X')
                count1++;
            if(table[j][i]=='X')
                count2++;
        }
        if(table[i][i]=='X')
            count3++;
        if(table[i][3-i-1]=='X')
            count4++;
        if(count1==3 || count2==3 || count3==3 || count4==3)
            return 1;
    }
    return 0;
}

/* Functie de copiere a unui tablou in alt tablou. */
void copiere(char t1[][4] , char t2[][4])
{
    int i,j ;
    for(i=0;i<3;i++)
    {for(j=0;j<3;j++)
        t1[i][j]=t2[i][j];
    }  
}

/* Functie care schimba mutarea in cea opusa. */
char schimba( char c )
{
    if(c=='X')
        c='O';
    else
        c='X';
    return c;
}

/* Functie de completare a arborelui , cu toate starile posibile ale jocului
curent. */ 
gametree *inserare_gametree(gametree *tree , char table[][4], int nr_of_spaces, char mutare,int p1, int p2,char mutare_initiala)
{
    int k;
    char aux[4][4];

    init_Tree(&tree,nr_of_spaces);
    if(p1!=4 && p2!=4)
    {
        table[p1][p2]=mutare;
        mutare=schimba(mutare);
    }
    copiere(tree->table,table);
    tree->jucator=mutare;
    if(verifica_castig(tree->table)==1)
    {
        if(table[p1][p2]==mutare_initiala)
            tree->win='T';
        return tree;
    }
    else
    {
        for(k=0;k<tree->nr_of_spaces;k++)
        {
            nr_aparitii(tree->table);
/* Reactualizam cei doi vectori pentru urmatorul fiu. */
            copiere(aux,tree->table);    
            tree->next[k]=inserare_gametree(tree->next[k],aux,tree->nr_of_spaces-1,mutare,poz1[k],poz2[k],mutare_initiala);
        }
        return tree;
    }
}


/* Functie pentru indeplinirea conditiei de AND/OR prin recursivitate
de la cel mai jos nivel. */
gametree *si_sau_completion(gametree *tree , char mutare_initiala)
{
    int i,k;
    for(i=0;i<tree->nr_of_spaces;i++)
    {    
        if(tree->next[i]!=NULL)
        si_sau_completion(tree->next[i],mutare_initiala);
    }
    if(tree->jucator==mutare_initiala)
    {

        for(k=0;k<tree->nr_of_spaces;k++)
        {
            if(tree->next[k]!=NULL)
            {
                if(tree->next[k]->win=='T')
                    tree->win='T';
            }
        }
    }
    else
    {    
        if(verifica_castig(tree->table)==1 || nr_aparitii(tree->table)!=0)
        tree->win='T';
        for(k=0;k<tree->nr_of_spaces;k++)
        {
            if(tree->next[k]!=NULL)
            {
                if(tree->next[k]->win=='F')
                    tree->win='F';
            }
        }
    }
    return tree;
}


/* Functie pentru inserarea in arbore,in cazul cerintei pentru minimax. Se
foloseste o coada pentru usurinta extragerii elementelor si introduceri
lor in arbore pe nivel. */
gametree *insert_minimax(gametree *tree, Queue *q , int h)
{
	char *s;
	gametree *nou;
    int i;
    
	if(tree==NULL)
	{
        s=pop_queue(q);
        if(s[0]=='(')
        {
            init_Tree(&nou,atoi(s+1));
            nou->val=0;
        }
        else if(s[0]=='[')
        {
            init_Tree(&nou,0);
            nou->val=atoi(s+1);
        }
        nou->nivel=h;
        tree=nou;		
		return tree;
    }
	else
	{
	   for(i=0;i<tree->nr_of_spaces;i++)
            tree->next[i]=insert_minimax(tree->next[i],q,h);
	}
return tree;
}

/* Functie pentru indeplinirea conditiei de minimax , bazandu-se pe
acelasi principiu ca si functia de AND/OR , putin modificat. */
gametree *minimax(gametree *tree )
{
    int i,k,max,min;
    for(i=0;i<tree->nr_of_spaces;i++)
    {    
        if(tree->next[i]!=NULL)
            minimax(tree->next[i]);
    }
    if(tree->nivel%2!=0 && tree->nr_of_spaces!=0)
    {
        max=tree->next[0]->val;  
        for(k=0;k<tree->nr_of_spaces;k++)
        {
            if(tree->next[k]!=NULL)
            {
                if(tree->next[k]->val>max)
                    max=tree->next[k]->val;
            }
        }
        tree->val=max;
    }
    else if(tree->nivel%2==0 && tree->nr_of_spaces!=0)
    {
        min=tree->next[0]->val;
        for(k=1;k<tree->nr_of_spaces;k++)
        {
            if(tree->next[k]!=NULL)
            {
                if(tree->next[k]->val<min)
                    min=tree->next[k]->val;
            }
        }
        tree->val=min;
    }
    return tree;
}

/* Functie pentru scrierea unui singur tablou. */
void print_table_only(char t[][4],char fisier[])
{
    int i,j;
    FILE *fp;
    fp=fopen(fisier,"w");
    for(i=0;i<3;i++)
    {    
        for(j=0;j<3;j++)
        {
            if(j==2)
                fprintf(fp, "%c\n",t[i][j] );
            else
                fprintf(fp, "%c ",t[i][j] );
        }
    }
    fprintf(fp, "\n");
    fclose(fp);
}

/* Functie pentru scrierea tuturor tablourilor din arbore. */
void print_table(char t[][4],FILE *fp,int n)
{
    int i,j,k;

    for(i=0;i<3;i++)
    {    
        for(k=0;k<n;k++)
            fprintf(fp, "\t");


        for(j=0;j<3;j++)
        {
            if(j==2)
                fprintf(fp, "%c\n",t[i][j] );
            else
                fprintf(fp, "%c ",t[i][j] );
        }
    }
    fprintf(fp, "\n");
}

/* Functie pentru scrierea valorilor True sau False in cazul
cerintei de AND/OR. */
void print_si_sau(char c,FILE *fp, int n)
{
    int i;

    for(i=0;i<n;i++)
        fprintf(fp, "\t");
    fprintf(fp, "%c\n",c );
}

/* Functie pentru scrierea valorilor in cazul cerintei de minimax. */
void print_minimax(int val,FILE *fp,int n)
{
    int i;

    for(i=0;i<n;i++)
        fprintf(fp, "\t");
    fprintf(fp, "%d\n",val );
}

/* Functie care se reapeleaza si , in functie de cerinta,
se foloseste de functiile efective de scriere. */
void print_gametree(gametree *tree,FILE *fp,int max,int ok)
{
    int i;
    if(ok==0)
    {
        print_table(tree->table,fp,max-tree->nr_of_spaces);
        for(i=0;i<tree->nr_of_spaces;i++)
        {
            if(tree->next[i]!=NULL)
                print_gametree(tree->next[i],fp,max,ok);
        }
    }
    else if(ok==1)
    {
        print_si_sau(tree->win,fp,max-tree->nr_of_spaces);
        for(i=0;i<tree->nr_of_spaces;i++)
        {
            if(tree->next[i]!=NULL)
                print_gametree(tree->next[i],fp,max,ok);
        }
    }
    else if(ok==2)
    {
        print_minimax(tree->val,fp,tree->nivel-max);
        for(i=0;i<tree->nr_of_spaces;i++)
        {
            if(tree->next[i]!=NULL)
                print_gametree(tree->next[i],fp,max,ok);
        }
    }
}


/* Functie principala care este apelata pentru scrierea in fisier. */
void print(gametree *tree , int cerinta, char fisier[])
{ int ok;
    FILE *fp;
    ok=cerinta;
    fp=fopen(fisier,"w");
    if(tree==NULL)
    {
        fprintf(fp, "%s\n", "Empty tree.");
        exit(0);
    }
    if(ok==2)
        print_gametree(tree,fp,tree->nivel,ok);
    else
        print_gametree(tree,fp,tree->nr_of_spaces,ok);
    fclose(fp);
}

/* Functie de eliberare a nodurilor din arbore. */
void free_gametree(gametree **tree)
{
    int i;
    for (i=0;i<(*tree)->nr_of_spaces;i++)
    {
        if((*tree)->next[i]!=NULL)
            free_gametree(&(*tree)->next[i]);
    }
    if((*tree)->nr_of_spaces!=0)
        free((*tree)->next);
    free(*tree);
}


int main(int argc, char *argv[])
{
    gametree *game=NULL;
    gametree *tree=NULL;
    int i=0,j=0,n;
    char mutare ,table[4][4],mutare_initiala;
    FILE *fp;

/* Rezolvarea primei cerinte. */

    if(strcmp(argv[argc-3],"-c1")==0)
    {
    fp=fopen(argv[argc-2],"r+");
    mutare=fgetc(fp);
    mutare_initiala=mutare;
    fgetc(fp);
    
    for(i=0;i<3;i++)
    {for(j=0;j<3;j++)
        { 
        table[i][j]=fgetc(fp);
        if(fgetc(fp)==EOF)
            break;
        }
    }
    if(verifica_castig(table)==1 )
    {
        print_table_only(table,argv[argc-1]);
        printf("Jocul este deja terminat , introduceti o alta stare.\n");
        exit(0);
    }             
    game=inserare_gametree(game,table,nr_aparitii(table),mutare,4,4,mutare_initiala);
    print(game,0,argv[argc-1]);        
    fclose(fp);
    }

/* Rezolvarea celei de-a doua cerinte. */

    else if(strcmp(argv[argc-3],"-c2")==0)
    {
    fp=fopen(argv[argc-2],"r+");
    mutare=fgetc(fp);
    mutare_initiala=mutare;
    fgetc(fp);
   
    for(i=0;i<3;i++)
    {for(j=0;j<3;j++)
        { 
        table[i][j]=fgetc(fp);
        if(fgetc(fp)==EOF)
            break;
        }
    }          
    game=inserare_gametree(game,table,nr_aparitii(table),mutare,4,4,mutare_initiala);
    game=si_sau_completion(game,mutare_initiala);
    print(game,1,argv[argc-1]);
    fclose(fp);
    }

/* Rezolvarea celei de-a treia cerinte. */

    else if(strcmp(argv[argc-3],"-c3")==0)
    {
        char s[1000000], *token;
        Queue *q=NULL;
        int h,line=0;
        fp=fopen(argv[argc-2],"r+");
        fgets(s,1000000,fp);
        h=atoi(s);
/* Citim linie cu linie , folosim strtok pentru spatii , si trimitem 
in functie impreuna cu nivelul la care ne aflam. */
        while(fgets(s,1000000,fp)!=NULL)
        {
            if(q!=NULL)
                free_queue(&q);
            free(q);
            init_queue(&q);
                token=strtok(s," ");
                while(token!=NULL)
                { 
                    add_queue(q,token);
                    token=strtok(NULL," ");
                }
                tree=insert_minimax(tree,q,line+1);
                line++;
        }
        if(tree!=NULL)
        tree=minimax(tree);
        print(tree,2,argv[argc-1]);
        free(q);
        fclose(fp);
    }
/* Se apeleaza functia de eliberarea  memoriei. */
    if(game!=NULL)
    free_gametree(&game);
    if(tree!=NULL)
    free_gametree(&tree);
    return 0;
}

