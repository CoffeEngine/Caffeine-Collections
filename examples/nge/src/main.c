#include "struct_def.h"

#include <stdio.h>


void present(vector(string) * vec)
{
    printf("\nPresenting:\n");

    vector_foreach(string, vec,
    {
            printf("%s, ", cnano_value);
    });
    printf("\n");
}

void presenca(vector(string) * vec)
{
    int rei = vector_find(string)(vec, "Rei");
    int shinji = vector_find(string)(vec, "Shinji");
    int asuka = vector_find(string)(vec, "Asuka");
    int mari = vector_find(string)(vec, "Makinami Mari");

    if (rei < 0)
        printf("Rei not present\n");
    else
        printf("Rei is in eva %d\n", rei);

    if (shinji < 0)
        printf("Shinji not present\n");
    else
        printf("Shinji is in eva %d\n", shinji);

    if (asuka < 0)
        printf("Asuka not present\n");
    else
        printf("Asuka is in eva %d\n", asuka);

    if (mari < 0)
        printf("Mari not present\n");
    else
        printf("Mari is in eva %d\n", mari);
}

int main()
{
    vector(string) names;

    vector_create(string)(&names, 2);

    vector_push_back(string)(&names, "Rei");
    vector_push_back(string)(&names, "Shinji");
    vector_push_back(string)(&names, "Asuka");

    presenca(&names);

    vector_set(string)(&names, "Ayanami Rei", 0);
    vector_set(string)(&names, "Ikari Shinji", 1);
    vector_set(string)(&names, "Langley Asuka", 2);
    vector_insert(string)(&names, "Makinami Mari", 2);

    present(&names);

    presenca(&names);

    vector_reverse(string)(&names);

    present(&names);

    vector_push_front(string)(&names, "Katsuragi Misato");
    vector_push_back(string)(&names, "Katsuragi Misato");

    present(&names);

    int cc = vector_count(string)(&names, "Katsuragi Misato");
    printf("There are %d %s\n", cc, "Katsuragi Misato");
    printf("Lets remove one\n");
    vector_remove(string)(&names, names.count - 1);

    present(&names);

    vector(string) others;
    vector_create(string)(&others, 1);

    vector_push_back(string)(&others, "Ikari Gendo");
    vector_push_back(string)(&others, "Akagi Ritsuko");
    vector_push_back(string)(&others, "Ryoji Kagi");

    printf("\nThere are others too");
    present(&others);

    printf("\nLets put them togheter");

    vector_join(string)(&names, &others);

    present(&names);

    printf("Lets say goodbye\n");

    vector_free(string)(&names);
    vector_free(string)(&others);

    present(&names);
    present(&others);

    char a[10];
    printf("Press any key..");
    scanf("%s", &a);
}