#include "Datatype.h"

int main() {
    struct List *l1 = List();

    struct Integer* a = Integer(123);
    struct Integer* b = Integer(100000);
    struct String* c = String("Hello,");

    struct List* l2 = List();
    l2->append(l2, Integer(-10));
    l2->append(l2, String("another list inside"));

    l1->append(l1, a);
    l1->append(l1, b);
    l1->append(l1, c);
    l2->append(l1, l2);

    l1->print(l1);

    return 0;
}
