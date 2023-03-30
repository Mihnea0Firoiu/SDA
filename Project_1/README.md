# DoublyLinkedListWSentinel.h & DoublyLinkedListWSentinel.c

> Contin implementarea listei dublu inlantuite cu santinela folosita pentru banda
magica.

## Functii folosite lista:

### Node_d *createNode();

> Creaza un nou nod pentru lista.
> Valoarea nodului este pusa initial ca '#'.

### TList initList();

> Initiaza o lista dublu inlantuita cu santinela.
> Se aloca santinela si primul element din lista.

### void moveLeft(TList);

> Daca degetul nu se afla pe prima pozitie din lista, se muta mai la stanga cu un
element.

### void moveRight(TList);

> Degetul se muta mai la dreapta cu un element.
> Daca degetul se afla pe ultima pozitie, se adauga un nou nod la final.

### void write(TList, T);

> Pe pozitia unde se afla degetul se scrie un anumit caracter primit ca parametru.

### void moveLeftChar(TList, T, FILE*);

> Degetul se muta, la stanga, la prima pozitie unde se afla caracterul cautat.
Cautarea incepe de pe pozitia curenta.
> Daca degetul se afla pe prima pozitie, se afiseaza mesajul "ERROR".

### void moveRightChar(TList, T);

> Degetul se muta, la dreapta, la prima pozitie unde se afla caracterul cautat.
Cautarea incepe de pe pozitia curenta.
> Daca degetul ajunge pe ultima pozitie si nu s-a gasit caracterul, se adauga un
 nou nod la final.

### void insertLeft(TList, T, FILE*);

> Insereaza un nod la stanga pozitiei curente a degetului.
> Daca degetul se afla pe prima pozitie, se afiseaza mesajul "ERROR".

### void insertRight(TList, T);

> Insereaza un nod la dreapta pozitiei curente a degetului.

### TList freeList(TList);

> Elibereaza lista.



# Queue.h & Queue.c

> Contin implementarea cozii pentru operatiile de tip UPDATE. Fiecare nod din
 coada are un camp pentru comanda si un camp pentru caracterul asociat. Daca
 o comanda nu are un caracter asociat, campul va fi '\0'.

## Functii folosite coada:

### Node_q *initNode_q(char *);

> Initiaza un nod pentru coada.
> Toate nodurile au la inceput campul 'character' initializat cu '\0'.

### TQueue initQueue(char *);

> Initiaza o coada.

### Node_q *freeNode(Node_q *);

> Elibereaza un nod.

### TQueue enqueue(TQueue, char *);

> Adauga un element la inceputul cozii.

### TQueue dequeue(TQueue);

> Scoate un element de la finalul cozii.

### TQueue freeQueue(TQueue);

> Elibereaza coada.



# Stack.h & Stack.c

> Contin implementarea stivelor pentru operatiile undo si redo.

## Functii folosite stiva:

### TStack initStack(Node_d *);

> Initiaza un nod pentru stiva.

### TStack push(TStack, Node_d *);

> Adauga un nod la inceputul stivei

### TStack pop(TStack);

> Scoate un nod de la inceputul stivei.

### TStack freeStack(TStack);

> Elibereaza stiva.



# Tema1.c

Contine functia main.

## Metoda de rezolvare:

> Comenzile sunt citite pe rand din fisier si in funtctie de tipul lor se aplica
diferite masuri:


> Pentru operatii de tip UPDATE, comanda si caracterul asociat (daca este cazul)
 sunt adaugate in coada.

> Pentru operatii de tip QUERY:
>> SHOW: Se afiseaza valorile din banda magica.
>> SHOW_CURRENT: Se afiseaza valoarea de la pozita degetului.

> Pentru EXECUTE se executa prima operatie din coada. Daca operatia este 
MOVE_LEFT sau MOVE_RIGHT, pozita precedenta a degetului se adauga in stiva UNDO.

> Pentru UNDO/REDO:
>> UNDO: degetul se muta la pozitia precedenta si pozitia actuala se introduce
in stiva REDO.
>> REDO: degetul se muta la pozitia precedenta si pozitia actuala se introduce
in stiva UNDO.
