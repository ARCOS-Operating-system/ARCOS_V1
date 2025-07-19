#include <limine.h>
#include <stdint.h>
#include <stddef.h>
#include "framebuffer.h"

extern volatile struct limine_framebuffer_request framebuffer_request;

bool framebuffer_available(void) {
    return framebuffer_request.response != NULL &&
           framebuffer_request.response->framebuffer_count >= 1;
}

void framebuffer_draw_test(void) {
    struct limine_framebuffer *fb = framebuffer_request.response->framebuffers[0];
    for (size_t i = 0; i < 100; i++) {
        volatile uint32_t *ptr = fb->address;
        ptr[i * (fb->pitch / 4) + i] = 0xffffff;
    }
}
