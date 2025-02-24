#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

// Stack'as turi tureti limita (pvz. iki 5 elementu)
// visi errorai turetu buti sunumeruoti

// Padaryti user interface (menu) stack'o testavimui
// sukurti funkcija kuri leistu pilnai sunaikinti visa stack'a
// spausdindami visa stack'o turini, turime nusakyti kurioje vietoje yra virsus ir kurioje apacia
// turi buti daugiau negu 1 stack'as
// pagalvoti ar trecias stack'as tampa antru kai mes panaikiname antra stack'a
// maximum 3 stack'ai, bandant sukurti 4-ta, turetu ismesti error
// funckija uzbaigti darba
// iki kovo 5d.
// kita sav. paskaitos nebus

int main() {
stackProperties *a;
a = createStack(a);
int val;
assert(isStackEmpty(a));
assert(!isStackFull(a));

//Create stack tikrinimas
assert(a->top == NULL);
assert(a->counter == 0);
assert(a->isEmpty == true);
assert(a->isCreated == true);

//push komandos tikrinimas
push(1, &a);
assert(a->top->value == 1);
assert(a->top->next == NULL);
assert(a->counter == 1);
assert(a->isEmpty == false);
assert(a->isCreated == true);

stack *b;
b = a->top;

push(5, &a);
assert(a->top->value == 5);
assert((a->top->next) == b);
assert(a->counter == 2);
assert(a->isEmpty == false);
assert(a->isCreated == true);




push(12, &a);
assert(a->top->value == 5);
assert((a->top->next) == b);
assert(a->counter == 2);
assert(a->isEmpty == false);
assert(a->isCreated == true);
displayStack(a);
peek(a);

//pop komandos tikrinimas

val = pop(&a);
assert(a->top->value == 1);
assert((a->top->next) == NULL);
assert(a->counter == 1);
assert(a->isEmpty == false);
assert(a->isCreated == true);
assert(val == 5);

val = pop(&a);
assert((a->top) == NULL);
assert(a->counter == 0);
assert(a->isEmpty == true);
assert(a->isCreated == true);
assert(val == 1);

val = pop(&a);
assert((a->top) == NULL);
assert(a->counter == 0);
assert(a->isEmpty == true);
assert(a->isCreated == true);
assert(val == -1);
assert(isStackEmpty(a));
assert(!isStackFull(a));


printf("%d",a->counter);








   return 0;
}