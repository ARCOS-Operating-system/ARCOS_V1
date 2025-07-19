#include "boot/init.h"
#include "drivers/video/framebuffer.h"
#include "core/panic.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>

LIMINE_BASE_REVISION(3)

// Limine framebuffer request
__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

static void hcf(void) {
    for (;;) {
#if defined (__x86_64__)
        asm volatile ("hlt");
#endif
    }
}

void kmain(void) {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        hcf();
    }

    if (framebuffer_request.response == NULL
        || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    struct limine_framebuffer *fb = framebuffer_request.response->framebuffers[0];
    for (size_t i = 0; i < 100; i++) {
        volatile uint32_t *fb_ptr = fb->address;
        fb_ptr[i * (fb->pitch / 4) + i] = 0xffffff;
    }

    hcf();
}
