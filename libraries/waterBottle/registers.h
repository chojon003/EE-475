// microcontroller registers file

#include <stdint.h>

#ifndef REGISTERS_H
#define REGISTERS_H

// power registers
#define DCDCEN                  (*(volatile uint32_t *) 0x40000578)
#define SYSTEMOFF               (*(volatile uint32_t *) 0x40000500)
#define RAM4POWER               (*(volatile uint32_t *) 0x40000940)
#define RAM5POWER               (*(volatile uint32_t *) 0x40000950)
#define RAM6POWER               (*(volatile uint32_t *) 0x40000960)
#define RAM7POWER               (*(volatile uint32_t *) 0x40000970)
#define RAM8POWER               (*(volatile uint32_t *) 0x40000980)

// clock registers
#define TASKS_LFCLKSTART        (*(volatile uint32_t *) 0x40000008)
#define TASKS_LFCLKSTOP         (*(volatile uint32_t *) 0x4000000C)
#define LFCLKSRC                (*(volatile uint32_t *) 0x40000518)
#define LFRCMODE                (*(volatile uint32_t *) 0x400005B4)
#define LFCLKSTAT               (*(volatile uint32_t *) 0x40000418)

#endif // REGISTERS_H
