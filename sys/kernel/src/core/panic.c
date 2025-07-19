#include "core/panic.h"

static void hcf(void) {
    for (;;) {
        __asm__ volatile ("hlt");
    }
}


void panic(const char *msg) {
    (void)msg; // TODO: optionally log or display message

    // In the future, you might write msg to framebuffer or serial here.
    // For now, we just halt.
    hcf();
}
