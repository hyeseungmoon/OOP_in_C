#ifndef DS_DATATYPE_H
#define DS_DATATYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Object {
    void (*print)(struct Object* this);
    unsigned char* bytes;
};

struct Integer {
    void (*print)(struct Integer* this);
    struct Object* parent;
};

struct String {
    void (*print)(struct String* this);
    struct Object* parent;
};

struct List {
    void (*print)(struct List* this);

    struct Object* parent;
    unsigned int size;
    unsigned int length;

    void (*append)(struct List *this, struct Object* x);
    struct Object* (*pop)(struct List *this);
    struct Object* (*get)(struct List* this, unsigned int index);
};

void print_integer(struct Integer* this);

void print_string(struct String* this);

void print_list(struct List* this);

struct Integer* Integer(int x);

struct String* String(char* x);

struct List* List();

void list_append(struct List *this, struct Object* x);

struct Object* list_pop(struct List* this);

struct Obeject* list_get(struct List* this, unsigned int index);

#endif //DS_DATATYPE_H
