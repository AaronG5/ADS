#include <assert.h>
#include <stdlib.h>
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

int main()
{
    stack *top;

    top = createStack(172);
    
    assert(top->value == 172);

    push(20, &top);
    assert(top->value == 20);

    pop(&top);
    assert(top->value == 172);

    peek(top);

    assert(isFull(top) == 0);

    pop(&top);
    assert(top == NULL);

    pop(&top);

/*
    push(11, &top);
    assert(top->value == 11);
    push(22, &top);
    peek(top);
    assert(top->value == 22);
    push(33, &top);
    assert(top->value == 33);
    push(44, &top);
    assert(top->value == 44);
    push(55, &top);
    assert(top->value == 55);
*/
    displayStack(top);


    return 0;
}