* This project has been created as part of the 42 curriculum by ylerges.*

# Get Next Line

## Description

Get Next Line, c'est une fonction qui lit un fichier ligne par ligne. Ça a l'air simple comme ça mais c'est là qu'on découvre les variables statiques en C et comment gérer la mémoire quand on sait pas à l'avance la taille de ce qu'on va lire.

L'idée c'est d'appeler la fonction plusieurs fois et à chaque fois elle te retourne la ligne suivante. Ça marche avec des fichiers normaux mais aussi avec stdin ou n'importe quel descripteur de fichier valide.

## Comment compiler

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

Le BUFFER_SIZE tu peux le changer (1, 42, 1024, peu importe). J'ai testé avec différentes valeurs et ça marche.

## Fichiers du projet

- `get_next_line.c` - la fonction principale
- `get_next_line_utils.c` - les fonctions utiles (strlen, strchr, etc.)
- `get_next_line.h` - le header

## Exemple d'utilisation

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Comment ça marche

Le principe est assez simple : j'utilise une variable statique pour garder ce qui a été lu mais pas encore retourné. À chaque appel de la fonction, je lis des morceaux de BUFFER_SIZE octets jusqu'à trouver un '\n'.

Une fois que j'ai trouvé le '\n', je retourne tout ce qui est avant (y compris le '\n'), et je garde le reste dans ma variable statique pour le prochain appel. Si j'arrive à la fin du fichier et qu'il reste des trucs, je retourne ça sans le '\n'.

J'ai fait des fonctions helper classiques :
- `ft_strlen` pour calculer la taille d'une string
- `ft_strchr` pour trouver le '\n'
- `ft_strjoin` pour coller deux strings ensemble
- `ft_strdup` et `ft_strlcpy` pour copier

Les trucs chiants que j'ai dû gérer :
- Les fichiers sans '\n' à la fin
- Les fichiers vides (direct return NULL)
- Les BUFFER_SIZE minuscules genre 1 (ça marche mais c'est lent)
- Les lignes vides (faut bien retourner juste '\n')

La complexité c'est O(n) où n est la taille du fichier, vu qu'on lit chaque octet une fois. Pour la mémoire c'est O(BUFFER_SIZE + taille de la ligne).

## Tests et ressources

Pour tester, j'ai essayé avec différents BUFFER_SIZE, des gros fichiers, des fichiers vides, des fichiers sans '\n' final, etc.

Les ressources qui m'ont aidé :
- Les man pages de read(2)
- Quelques tutos sur les variables statiques
- L'intranet 42 pour comprendre ce qui est attendu
- Mes camarades qui m'ont donné des idées sur les edge cases

Pour ce qui est de l'IA, je l'ai utilisée pour comprendre certains concepts (surtout les variables statiques au début) et pour debugger quand je comprenais pas pourquoi j'avais des leaks. Mais le code c'est moi qui l'ai écrit, testé et débugué.
