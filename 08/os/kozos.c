#include "defines.h"
#include "kozos.h"
#include "intr.h"
#include "interrupt.h"
#include "syscall.h"
#include "lib.h"

#define THREAD_NUM 6
#define THREAD_NAME_SIZE 15

typedef struct _kz_context {
  uint32 sp;
} kz_context;

typedef struct _kz_thread {
  struct _kz_thread *next;
  char name(THREAD_NAME_SIZE + 1);
  char *stack;

  struct {
    kz_func_t func;
    int argc;
    char **argv;
  } init;

  struct {
    kz_syscall_type_t type;
    kz_syscall_param_t *param;
  } syscall

  kz_context context;
} kx_thread;

static struct {
  kz_thread *head;
  kz_thread *tail;
} readyque;

static kz_thread *current;
static kz_thread threads(THREAD_NUM);
static kx_handler_t handlers(SOFTVEC_TYPE_NUM);

void dispatch(kz_context *context);

static int getcurrent(void)
{
  if (current == NULL) {
    return -1;
  }

  readyque.head = current->next;
  if (readyque.head == NULL) {
    readyque.tail = NULL;
  }
  current->next = NULL;

  return 0;
}

static int putcurrent(void)
{
  if (current == NULL) {
    return -1;
  }

  if (readyque.tail) {
    readyque.tail->next = current;
  } else {
    readyque.head = current;
  }
  readyque.tail = current;
  return 0;
}

static void thread_end(void)
{
  kz_exit();
}

static void thread_init(kz_thread *thp)
{
  thp->init.func(thp->init.argc, thp->init.argv);
  thread_end();
}

static kz_thread_id_t thread_run(kz_func_t func, char *name,
                                 int stacksize, int argc, char *argv[])
{
  int i;
  kz_thread *thp;
  uint32 *sp;
  extern char userstack;
  static char *thread_stack = &userstack;

  for (i = 0; i < THREAD_NUM; i++) {
    thp = &threads[i];
    if (!thp->init.func)
      break;
  }
  if (i == THREAD_NUM)
    return -1;

  memset(thp, 0, sizeof(*thp));

  strcpy(thp->name, name);
  thp->next = NULL;

  thp->init.func = func;
  thp->init.argc = argc;
  thp->init.argv = argv;

  memset(thread_stack, 0, stacksize);
  thread_stack += stacksize;

  thp->stack = thread_stack;

  sp = (uint32 *)thp->stack;
  *(--sp) = (uint32)thread_end;

  *(--sp) = (uint32)thread_init;

  *(--sp) = 0; /*ER6*/
  *(--sp) = 0; /*ER5*/
  *(--sp) = 0; /*ER4*/
  *(--sp) = 0; /*ER3*/
  *(--sp) = 0; /*ER2*/
  *(--sp) = 0; /*ER1*/

  *(--sp) = (uint32)thp; /*ER0*/

  thp->context.sp = (uint32)sp;

  putcurrent();

  current=thp;
  putcurrent();

  return (kz_thread_id_t)current;
}

static int thread_exit(void)
{
  puts(current->name);
  puts(" EXIT.\n");
  memset(current, 0, sizeof(*current));
  return 0;
}
