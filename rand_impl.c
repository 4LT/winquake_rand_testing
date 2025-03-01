#include <stdio.h>

unsigned long wq_rand() {
    static unsigned long state = 1;
    unsigned long eax, ecx;
    
    // mov <address>,%eax
    eax = state;

    // lea (%eax,%eax,4),%ecx
    ecx = eax * 5;

    // lea (%ecx,%ecx,4),%ecx
    ecx*= 5;

    // add %eax,%ecx
    ecx+= eax;

    // lea (%eax,%ecx,8),%ecx
    ecx = eax + ecx * 8;

    // shl $0x8,%ecx
    ecx<<= 8;

    // sub %eax,%ecx
    ecx-= eax;

    // lea 0x269ec3(%eax,%ecx,4),%eax
    eax = 0x269ec3 + eax + ecx * 4;

    // mov %eax,<address>
    state = eax;

    // and $0x7fff0000,%eax
    // shr $0x10,%eax
    eax = (eax & 0x7fff0000) >> 16;

    // ret
    return eax;
}

float pf_rand() {
    return (wq_rand() & 0x7fff) / (float)0x7fff;
}

int main() {
    int i;

    for (i = 0; i < 50; i++) {
        printf("%f\n", pf_rand());
    }
}
