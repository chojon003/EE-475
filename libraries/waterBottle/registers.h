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

// lpcomp registers
#define TASKS_LPCOMPSTART       (*(volatile uint32_t *) 0x40013000)
#define EVENTS_LPCOMPREADY      (*(volatile uint32_t *) 0x40013100)
#define LPCOMPEN                (*(volatile uint32_t *) 0x40013500)
#define ANALOGDETECT            (*(volatile uint32_t *) 0x40013520)
#define LPCOMPPSEL              (*(volatile uint32_t *) 0x40013504)
#define LPCOMPREFSEL            (*(volatile uint32_t *) 0x40013508)
#define LPCOMPHYST              (*(volatile uint32_t *) 0x40013538)

#endif // REGISTERS_H
