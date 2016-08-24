#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#ifdef __cplusplus
extern "C" {
#endif

int register_handler_process(int irqno);
int reset_handler_process(int irqno);

#ifdef __cplusplus
}
#endif

#endif
 
