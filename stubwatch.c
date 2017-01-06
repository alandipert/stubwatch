/* Inspirado: https://readmes.numm.org/init/upstart/init/tests/wrap_inotify.c */
#define _GNU_SOURCE

#include <stdio.h>
#include <search.h>
#include <stdint.h>

void __hset(struct hsearch_data *tbl, const char *k, int v) {
  ENTRY e, *ep;
  e.key  = (char*)(size_t)k;
  e.data = (void*)(intptr_t)v;
  hsearch_r(e, ENTER, &ep, tbl);
}

int __hget(struct hsearch_data *tbl, const char *k) {
  ENTRY e, *ep;
  e.key = (char*)(size_t)k;
  return hsearch_r(e, FIND, &ep, tbl) ? (intptr_t)ep->data : -1;
}

int inotify_add_watch (int fd, const char *pathname, uint32_t mask)
{
  static struct hsearch_data tbl = {0};
  static int path_counter        = 1;
  static int initialized         = 0;
  int prev_watch;

  if(!initialized) {
    hcreate_r(1024, &tbl);
    initialized = 1;
  }

  if(prev_watch = __hget(&tbl, pathname), prev_watch != -1) {
    return prev_watch;
  } else {
    __hset(&tbl, pathname, path_counter);
    return path_counter++;
  }
}

int inotify_rm_watch (int fd, int wd) { return 0; }
