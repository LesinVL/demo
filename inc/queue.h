#ifndef __QUEUE_H
#define __QUEUE_H
#include <stdint.h>
#include "MDR32F9Qx_eth.h"
#include "tcpip.h"


#ifndef NULL
#define NULL ((void*)0)
#endif
#ifndef HeapMax
#define HeapMax 12
#endif

#ifndef UdpMax
#define UdpMax 6
#endif
#ifndef QDS
#define QDS 528 //1500/*128*/
#endif
#ifndef MAX_msg
#define MAX_msg 4*4
#endif
#ifndef CLI
#define CLI() __disable_irq()
#define SEI() __enable_irq()
#endif


struct QRec {
  uint8_t d[QDS];
  uint32_t len;
  uint8_t flags;
  struct QRec *next;
};

struct Queue {
  struct QRec *first, *last;
  uint8_t cnt;
};


//+++++++++++++++++++++++
struct QRecx {
  uint32_t d[1560/4];
  uint32_t Shl;
  ETH_StatusPacketReceptionTypeDef ETH_StatusPacketReceptionStruct;
  struct QRecx *next;
};
struct Queuex {
  struct QRecx *first, *last;
  uint8_t cnt;
};

//++++++++++++++++++++++
//+++++++++++++++++++++++
struct QRecz2 {
  uint32_t d[(1560/4)];
  uint8_t Time;
  uint8_t cnt[8];
  uint8_t flag;
  uint16_t N[8];

 // ETH_StatusPacketReceptionTypeDef ETH_StatusPacketReceptionStruct;
  struct QRecz2 *next;
};

struct Queuez2 {
  struct QRecz2 *first, *last;
  uint8_t cnt;
};

//++++++++++++++++++++++
//+++++++++++++++++++++++
struct QRecz {

  uint32_t d[(1560/4)];
  uint8_t Nk;
 // ETH_StatusPacketReceptionTypeDef ETH_StatusPacketReceptionStruct;
  struct QRecz *next;
};

struct Queuez {
  struct QRecz *first, *last;
  uint8_t cnt;
};

//++++++++++++++++++++++

//+++++++++++++++++++++++
struct QRecv {

  uint32_t d[(48 + MAX_msg)/4];
  uint8_t Nk;
 // ETH_StatusPacketReceptionTypeDef ETH_StatusPacketReceptionStruct;
  struct QRecv *next;
};
struct Queuev {
  struct QRecv *first, *last;
  uint8_t cnt;
};

//++++++++++++++++++++++

#define qinit(q, start) { q.first = q.last = start; q.cnt = 0; }

#define isr_qput(q, rec) { if (q.cnt) q.last->next=(void*)rec; else q.first=(void*)rec; q.last=(void*)rec; q.cnt++; }
#define isr_qget(rec, q) { rec = (void*)q.first; q.first = q.first->next; q.cnt--; }

#define isr_hput(rec) isr_qput(heap, rec);
#define isr_hget(rec) isr_qget(rec, heap);

#define qput(q, rec) { /*CLI();*/ isr_qput(q, rec); /*SEI();*/ }
#define qget(rec, q) {/* CLI();*/ isr_qget(rec, q);/* SEI();*/ }

#define hput(rec) { /*CLI();*/ isr_hput(rec); /*SEI();*/ }
#define hget(rec) { /*CLI();*/ isr_hget(rec); /*SEI();*/ }

void heap_init();
void qempty(struct Queue *q);

#endif  //__QUEUE_H

