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
