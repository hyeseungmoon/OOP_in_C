#include "Datatype.h"

void print_integer(struct Integer* this) {
    int res = 0;
    for(int i=0;i<4;i++){
    res |= this->parent->bytes[i] << ((3 - i) * 8);
    }
    printf("%d", res);
}

struct Integer* Integer(int x) {
    struct Integer* this = (struct Integer*)malloc(sizeof(struct Integer));
    this->parent = (struct Object*)malloc(sizeof(struct Object));
    this->parent->bytes = (unsigned char*)malloc(sizeof(char) * 4);

    this->parent->bytes[0] = (char)((x & 0xFF000000) >> 24);
    this->parent->bytes[1] = (char)((x & 0x00FF0000) >> 16);
    this->parent->bytes[2] = (char)((x & 0x0000FF00) >> 8);
    this->parent->bytes[3] = (char)((x & 0x000000FF));

    this->print = print_integer;
    return this;
}

void print_string(struct String* this) {
printf("\"%s\"", this->parent->bytes);
}

struct String* String(char* x) {
    struct String* this = (struct String*)malloc(sizeof(struct String));
    this->parent = (struct Object*)malloc(sizeof(struct Object));

    size_t len = strlen(x);
    this->parent->bytes = (unsigned char*) malloc(sizeof(char) * (len + 1));
    this->parent->bytes[len] = 0;
    strcpy(this->parent->bytes, x);
    this->print = print_string;

    return this;
}

void print_list(struct List* this) {
    printf("[");
    if(this->length != 0) {
        for(int i=0;i<this->length - 1;i++) {
            struct Integer* cur = (struct Integer*)this->get(this, i);
            cur->print(cur);
            printf(", ");
        }
        struct Integer* cur = (struct Integer*)this->get(this, this->length - 1);
        cur->print(cur);
    }
    printf("]");
}

void list_append(struct List *this, struct Object* x) {
    if(this->length == this->size) {
        this->size *= 2;
        unsigned char* new_bytes = (unsigned char*)malloc(sizeof(size_t) * this->size);
        for(int i=0;i<this->size * 4;i++) {
            new_bytes[i] = this->parent->bytes[i];
        }
        free(this->parent->bytes);
        this->parent->bytes = new_bytes;
    }

    unsigned int base_idx = this->length * sizeof(size_t);
    size_t addr = (size_t)x;

    this->parent->bytes[base_idx] = ((addr & 0xFF00000000000000) >> 56);
    this->parent->bytes[base_idx + 1] = ((addr & 0xFF000000000000) >> 48);
    this->parent->bytes[base_idx + 2] = ((addr & 0xFF0000000000) >> 40);
    this->parent->bytes[base_idx + 3] = ((addr & 0xFF00000000) >> 32);
    this->parent->bytes[base_idx + 4] = ((addr & 0xFF000000) >> 24);
    this->parent->bytes[base_idx + 5] = ((addr & 0xFF0000) >> 16);
    this->parent->bytes[base_idx + 6] = ((addr & 0xFF00) >> 8);
    this->parent->bytes[base_idx + 7] = (addr & 0xFF);

    this->length++;
}

struct Object* list_pop(struct List* this) {
    if(this->length == 0) return NULL;

    struct Object* ret = this->get(this, this->length - 1);
    this->length--;
    return ret;
}

struct Obeject* list_get(struct List* this, unsigned int index) {
    index *= sizeof(size_t);
    size_t addr = 0;
    for(int i=0;i<sizeof(size_t);i++) {
        addr |= (size_t)this->parent->bytes[index + i] << (56 - 8 * i);
    }
    return (struct Object *) addr;
}

struct List* List() {
    struct List* this = (struct List*)malloc(sizeof(struct List));
    this->parent = (struct Object*)malloc(sizeof(struct Object));

    this->parent->bytes = (unsigned char*)malloc(sizeof(size_t) * 1);
    this->print = print_list;

    this->size = 1;
    this->length = 0;

    this->append = list_append;
    this->get = list_get;
    this->pop = list_pop;

    return this;
}
