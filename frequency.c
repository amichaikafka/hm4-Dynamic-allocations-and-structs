//
// Created by amichai on 07/01/2021.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NUM_LETTERS ((int)26)
typedef enum
{
    FALSE = 0,
    TRUE = 1
} boolean;
typedef struct node
{
    int depth;
    char letter;
    long unsigned int count;
    struct node *children[NUM_LETTERS];
} node;

node* add_node(char c)
{
    node *n = (node *)(calloc(1,sizeof(node)));
    n->letter = c;
    n->count = 1;
    return n;
}
int insertword(char *c, node *root)
{
    while (*c)
    {

        if (root->children[*c - 'a'] == NULL)
        {
            node *n = add_node(*c);
            n->depth = root->depth + 1;
            root->children[*c - 'a'] = n;
        }
        else
        {
            root->children[*c - 'a']->count++;
        }

        root = root->children[*c - 'a'];
        c++;
    }
    return 1;
}

int isword(node *n)
{
    int sum = 0;
    for (int i = 0; i < NUM_LETTERS; ++i)
    {
        if (n->children[i] != NULL)
        {
            sum += n->children[i]->count;
        }
    }
    return (n->count - sum);
}

void printT(node *root, char *s)
{
    if (root == NULL)
    {
        return;
    }
    if (root->letter != '0')
    {

        s[root->depth - 1] = root->letter;

        int n = isword(root);

        if (n> 0)
        {
            for (int i = 0; i < root->depth; i++)
            {
                //printf("%c", s[i]);
                putc(s[i], stdout);
            }

            printf(" %d\n", n);
        }
    }

    for (int i = 0; i < NUM_LETTERS; ++i)
    {
        if (root->children[i] != NULL)
        {
            printT(root->children[i], s);
        }
    }
}
void printTr(node *root, char *s)
{
    if (root == NULL)
    {
        return;
    }

    if (root->letter != '0')
    {

        s[root->depth - 1] = root->letter;
    }

    for (int i = NUM_LETTERS - 1; i >= 0; i--)
    {

        if (root->children[i] != NULL)
        {
            printTr(root->children[i], s);
        }
    }
    int n = isword(root);
    if (n> 0)
    {
        for (int i = 0; i < root->depth; i++)
        {
            //printf("%c", s[i]);
            putc(s[i], stdout);
        }

        printf(" %d\n", n);
    }
}
int freeT(node *root)
{
    if (root == NULL)
    {
        return 1;
    }
    for (int i = 0; i < NUM_LETTERS; ++i)
    {
        freeT(root->children[i]);
    }
    free(root);
    return 1;
}
int main(int argc, char *argv[])
{
    char *str = (char *)calloc(26,sizeof(char));
    char c;
    c = getchar();
    node *root = add_node('0');
    root->count=0;
    root->depth = 0;

    int i = 0;
    while (1)
    {
        c = tolower(c);

        if (c == ' ' || c == EOF)
        {

            str = realloc(str, 26*sizeof(char));
            str[i] = '\0';

            insertword(str, root);
            free(str);
            str = (char *)calloc( 26,sizeof(char));

            i = 0;

            if (c == EOF)
            {
                break;
            }
        }
        else if (c <= 'z' && c >= 'a')
        {

            *(str+i) = c;
            str = realloc(str,26*sizeof(char));

            i++;
        }
        c = getchar();
    }

    //char *str2 = (char *)calloc(26,sizeof(char));

    if (argc > 1 && argv[1][0] == 'r')
    {

        printTr(root, str);
    }
    else
    {

        printT(root, str);
    }
    free(str);
    //free(str2);
    freeT(root);
    return 1;
}
