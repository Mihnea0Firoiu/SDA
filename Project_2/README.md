# Compresor de imagini

## Introducere
**Compresorul de imagini** prezinta trei functionalitati:
- Afisarea anumitor caracteristici ale arborelui de compresie. [Task_1](#task_1c)
- Compresia unei imagini **patrate** in format **.ppm** si de tip **P6**. [Task_2](#task_2c)
- Decompresia unei imagini de acelasi fel. [Task_3](#task_3c)


>In continuare va fi prezentat modul in care au fost implementate cele trei task-uri.

## quadtree.c

>Fisierul **quadtree.c** continte doar functia **main**.

```c
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Not enough arguments!\n");
        return -1;
    }

    if (strcmp(argv[1], "-c1") == 0) { // Argument for task_1
        if (argc < 4) {
            printf("Not enough arguments!\n");
            return -1;
        }
        unsigned long long factor = atoll(argv[2]);
        task_1(factor, argv[3], argv[4]);
        return 0;
    } else if (strcmp(argv[1], "-c2") == 0) { // Argument for task_2
        if (argc < 4) {
            printf("Not enough arguments!\n");
            return -1;
        }
        unsigned long long factor = atoll(argv[2]);
        task_2(factor, argv[3], argv[4]);
        return 0;
    } else if (strcmp(argv[1], "-d") == 0) { // Argument for task_3
        task_3(argv[2], argv[3]);
        return 0;
    }
    
    return 0;
}
```
>Aici se apeleaza functiile corespunzatoare fiecarui task, nimic mai mult.

## task_1.c

>Fisierul **task_1.c** contine doar functia **task_1**.

### Citire din fisier

In secventa urmatoare de cod sunt citite informatiile date de imaginea primita ca parametru.

```c
// Read input from file.
read_type(input);
unsigned int measurements = read_measurements(input);
read_colour_value(input);
RGB *rgb_array = read_image(measurements, input);
```

Matricea valorilor rgb va fi de tipul RGB, unde rgb este o structura care retine valoarile rosu, verde si albatru corespunzatoare fiecarui pixel. Structura RGB arata in felul urmator:

```c
typedef struct __attribute__((packed)) {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} RGB;
```

Este folosit ```__attribute__((packed))``` pentru a scapa de bitii de padding (pentru a face citirea matricii mai usoara). Astfel, matricea poate fi citita printr-o singura comanda in interiorul functiei **read_image**:

```c
fread(rgb_array, sizeof(RGB), measurements * measurements, input);
```

### Crearea arborelui de compresie

Pentru lucrul cu fiecare subsectiune a matricii este suficient sa fie retinute "coordonatele" pixelului din coltul stanga-sus si "coordonatele" pixelului din coltul stanga-jos. Astfel, folosim o structura care retine coloana si linia pe care se afla un pixel.

```c
/* For each subsection of the array it is enough to know the coordinates 
    of the top-left corner and down-right corner. */
Point up_left, down_right;
up_left.column = 0;
up_left.row = 0;
down_right.column = measurements - 1;
down_right.row = measurements - 1;
```

Urmeaza construirea arborelui de compresie folosind functia **build_image_tree**:

- Pentru inceput este calculata media:

```c
// Calculate mean value of the current block.
unsigned long long red = 0, green = 0, blue = 0;
int column = down_right.column - up_left.column + 1;
for (int i = up_left.row; i <= down_right.row; i++) {
    for (int j = up_left.column; j <= down_right.column; j++) {
        red = red + rgb_array[i * dim + j].red;
        green = green + rgb_array[i * dim + j].green;
        blue = blue + rgb_array[i * dim + j].blue;
    }
}

red = red / (column * column);
green = green / (column * column);
blue = blue / (column * column);
unsigned long long mean = 0;

for (int i = up_left.row; i <= down_right.row; i++) {
    for (int j = up_left.column; j <= down_right.column; j++) {
        mean = mean + (red - rgb_array[i * dim + j].red) *
            (red - rgb_array[i * dim + j].red)
            + (green - rgb_array[i * dim + j].green)
            * (green - rgb_array[i * dim + j].green)
            + (blue - rgb_array[i * dim + j].blue)
            * (blue - rgb_array[i * dim + j].blue);
    }
}

mean = mean / (3 * column * column);
```

- Daca media este mai mica sau egala cu factorul de compresie primit ca parametru, atunci nodul curent va fi de tip frunza:

```c
if (mean <= factor) { // if mean <= factor, then the node is a leaf.
    (*root)->node_type = 1;
    (*root)->rgb.red = (unsigned char)red;
    (*root)->rgb.green = (unsigned char)green;
    (*root)->rgb.blue = (unsigned char)blue;
    return ;
}
```

- Altfel, se face un apel recursiv pentru fiecare dintre cei 4 fii ai nodului curent:

```c
Point up_left_copy, down_right_copy;

// Up_left
up_left_copy.row = up_left.row;
up_left_copy.column = up_left.column;
down_right_copy.row = (up_left.row + down_right.row) / 2;
down_right_copy.column = (up_left.column + down_right.column) / 2;
build_image_tree(rgb_array, dim, up_left_copy, down_right_copy,
    &((*root)->up_left), factor);

// Up_right
up_left_copy.row = up_left.row;
up_left_copy.column = 1 + (up_left.column + down_right.column) / 2;
down_right_copy.row = (up_left.row + down_right.row) / 2;
down_right_copy.column = down_right.column;
build_image_tree(rgb_array, dim, up_left_copy, down_right_copy,
    &((*root)->up_right), factor);

// Down_right
up_left_copy.row = 1 + (up_left.row + down_right.row) / 2;
up_left_copy.column = 1 + (up_left.column + down_right.column) / 2;
down_right_copy.row = down_right.row;
down_right_copy.column = down_right.column;
build_image_tree(rgb_array, dim, up_left_copy, down_right_copy,
    &((*root)->down_right), factor);

// Down_left
up_left_copy.row = 1 + (up_left.row + down_right.row) / 2;
up_left_copy.column = up_left.column;
down_right_copy.row = down_right.row;
down_right_copy.column = (up_left.column + down_right.column) / 2;
build_image_tree(rgb_array, dim, up_left_copy, down_right_copy,
    &((*root)->down_left), factor);
```

### Afisarea caracteristicilor arborelui

Dupa crearea arborelui sunt afisate anumite caracteristici ale acestuia:
- numarul de niveluri.
- numarul de frunze.
- dimensiunea laturii patratului cel mai mare.

```c
int level_number = height(root) + 1;
int number_of_blocks = leaf_num(root);
int lowest = min_height(root);
int biggest_undiv_square = measurements >> lowest; // Divide by 2^lowest

fprintf(output, "%d\n%d\n%d\n", level_number, number_of_blocks,
 biggest_undiv_square);
```

## task_2.c

[Citire este realizata ca la task-ul precedent. Pentru informatii despre citire vezi "Citire din fisier"](#citire-din-fisier)

[Crearea arborelui de compresie este realizata ca la task-ul precedent. Pentru informatii despre arbore vezi "Crearea arborelui de compresie"](#crearea-arborelui-de-compresie)

### Compresarea arborelui

Este apelata functia **compress**.

```c
void compress(TQuadTree root, int level_number, int measurements,
 FILE* output) {
    fwrite(&measurements, sizeof(unsigned int), 1, output);
    for (int i = 0; i < level_number; i++) {
        print_level(root, i, output);
    }
}
```

Se poate observa ca functia afiseaza dimensiunea imaginii initiale si apoi arborele pe niveluri.

## task_3.c

### Citire fisier compresat.
Pentru inceput sunt citite informatiile din fisierul compresat.

```c
// Read input from file.
unsigned int size = read_size(input);
char *buffer = NULL;
unsigned long long buffer_size = 0;
read_tree(input, &buffer, &buffer_size);
```

### Decompresare.
Apoi este obtinut arborele din bufferul citit anterior.

```c
// Get tree.
TQuadTree root = NULL;
decompress(input, &root, buffer, buffer_size);
```

Functia **decompress** itereaza prin buffer si apeleaza **insert** pentru fiecare nod in parte. Aceasta se foloseste de o coada pentru a insera nodul in primul loc disponibil. Dupa ce arborele a fost creat, memoria alocata pentru coada este eliberata.

**get_array** face operatia opusa compresiei([vezi "Compresarea arborelui"](#compresarea-arborelui)) obtinand matricea din arbore:

```c
void get_array(RGB **rgb_array, int dim, Point up_left, Point down_right,
 TQuadTree root) {
    // The whole section gets the same rgb values if the node type is 1.
    if (root->node_type == 1) {
        for (int i = up_left.row; i <= down_right.row; i++) {
            for (int j = up_left.column; j <= down_right.column; j++) {
                (*rgb_array)[i * dim + j] = root->rgb;
            }
        }
        return;
    }
    Point up_left_copy, down_right_copy;

    // Up_left
    up_left_copy.row = up_left.row;
    up_left_copy.column = up_left.column;
    down_right_copy.row = (up_left.row + down_right.row) / 2;
    down_right_copy.column = (up_left.column + down_right.column) / 2;
    get_array(rgb_array, dim, up_left_copy, down_right_copy, root->up_left);

    // Up_right
    up_left_copy.row = up_left.row;
    up_left_copy.column = 1 + (up_left.column + down_right.column) / 2;
    down_right_copy.row = (up_left.row + down_right.row) / 2;
    down_right_copy.column = down_right.column;
    get_array(rgb_array, dim, up_left_copy, down_right_copy, root->up_right);

    // Down_right
    up_left_copy.row = 1 + (up_left.row + down_right.row) / 2;
    up_left_copy.column = 1 + (up_left.column + down_right.column) / 2;
    down_right_copy.row = down_right.row;
    down_right_copy.column = down_right.column;
    get_array(rgb_array, dim, up_left_copy, down_right_copy, root->down_right);

    // Down_left
    up_left_copy.row = 1 + (up_left.row + down_right.row) / 2;
    up_left_copy.column = up_left.column;
    down_right_copy.row = down_right.row;
    down_right_copy.column = (up_left.column + down_right.column) / 2;
    get_array(rgb_array, dim, up_left_copy, down_right_copy, root->down_left);
    
}
```
Daca nodul este frunza, atunci toata sectiunea primeste valoarile rgb din arbore. Altfel, sunt facute apeluri recursive pentru fiecare dintre cele 4 zone.

In final, matricea este afisata.

```c
print_array(rgb_array, size, output);
```
# Rezultate checker

    Cerința 1 - Compresia fisierelor
    Statistici_Test  0 ................................................. PASS
    VALGRIND ........................................................... PASS
    Statistici_Test  1 ................................................. PASS
    VALGRIND ........................................................... PASS
    Statistici_Test  2 ................................................. PASS
    VALGRIND ........................................................... PASS
    Statistici_Test  3 ................................................. PASS
    VALGRIND ........................................................... PASS
    Statistici_Test  4 ................................................. PASS
    VALGRIND ........................................................... PASS
    Statistici_Test  5 ................................................. PASS
    VALGRIND ........................................................... PASS
    Statistici_Test  6 ................................................. PASS
    VALGRIND ........................................................... PASS
    Statistici_Test  7 ................................................. PASS
    VALGRIND ........................................................... PASS
    Statistici_Test  8 ................................................. PASS
    VALGRIND ........................................................... PASS
    Statistici_Test  9 ................................................. PASS
    VALGRIND ........................................................... PASS
    Statistici_Test 10 ................................................. PASS
    Statistici_Test 11 ................................................. PASS
    Statistici_Test 12 ................................................. PASS
    Statistici_Test 13 ................................................. PASS
    Statistici_Test 14 ................................................. PASS
    Statistici_Test 15 ................................................. PASS
    Statistici_Test 16 ................................................. PASS
    Statistici_Test 17 ................................................. PASS
    Statistici_Test 18 ................................................. PASS
    Statistici_Test 19 ................................................. PASS
    Cerința 2 - Compresia fișierelor
    Compresia_Test  0 .................................................. PASS
    VALGRIND ........................................................... PASS
    Compresia_Test  1 .................................................. PASS
    VALGRIND ........................................................... PASS
    Compresia_Test  2 .................................................. PASS
    VALGRIND ........................................................... PASS
    Compresia_Test  3 .................................................. PASS
    VALGRIND ........................................................... PASS
    Compresia_Test  4 .................................................. PASS
    VALGRIND ........................................................... PASS
    Compresia_Test  5 .................................................. PASS
    VALGRIND ........................................................... PASS
    Compresia_Test  6 .................................................. PASS
    VALGRIND ........................................................... PASS
    Compresia_Test  7 .................................................. PASS
    VALGRIND ........................................................... PASS
    Compresia_Test  8 .................................................. PASS
    VALGRIND ........................................................... PASS
    Compresia_Test  9 .................................................. PASS
    VALGRIND ........................................................... PASS
    Compresia_Test 10 .................................................. PASS
    Compresia_Test 11 .................................................. PASS
    Compresia_Test 12 .................................................. PASS
    Compresia_Test 13 .................................................. PASS
    Compresia_Test 14 .................................................. PASS
    Compresia_Test 15 .................................................. PASS
    Compresia_Test 16 .................................................. PASS
    Compresia_Test 17 .................................................. PASS
    Compresia_Test 18 .................................................. PASS
    Compresia_Test 19 .................................................. PASS
    Cerința 3 - Decompresia fișierelor
    Decompresia_Test  0 ................................................ PASS
    VALGRIND ........................................................... PASS
    Decompresia_Test  1 ................................................ PASS
    VALGRIND ........................................................... PASS
    Decompresia_Test  2 ................................................ PASS
    VALGRIND ........................................................... PASS
    Decompresia_Test  3 ................................................ PASS
    VALGRIND ........................................................... PASS
    Decompresia_Test  4 ................................................ PASS
    VALGRIND ........................................................... PASS
    Decompresia_Test  5 ................................................ PASS
    VALGRIND ........................................................... PASS
    Decompresia_Test  6 ................................................ PASS
    VALGRIND ........................................................... PASS
    Decompresia_Test  7 ................................................ PASS
    VALGRIND ........................................................... PASS
    Decompresia_Test  8 ................................................ PASS
    VALGRIND ........................................................... PASS
    Decompresia_Test  9 ................................................ PASS
    VALGRIND ........................................................... PASS
    Decompresia_Test 10 ................................................ PASS
    Decompresia_Test 11 ................................................ PASS
    Decompresia_Test 12 ................................................ PASS
    Decompresia_Test 13 ................................................ PASS
    Decompresia_Test 14 ................................................ PASS
    Decompresia_Test 15 ................................................ PASS
    Decompresia_Test 16 ................................................ PASS
    Decompresia_Test 17 ................................................ PASS
    Decompresia_Test 18 ................................................ PASS
    Decompresia_Test 19 ................................................ PASS
    Cerinta 1 : 20
    Cerinta 2 : 30.0
    Cerinta 3 : 30.0
    Total     : 80.0
    Bonus     : 20.0
    Felicitari! Ai punctajul maxim: 80p! :)
