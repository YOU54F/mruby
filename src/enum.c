/*
** enum.c - Enumerable module
**
** See Copyright Notice in mruby.h
*/

#include <mruby.h>
#include <mruby/proc.h>

/* internal method `__update_hash(oldhash, index, itemhash)` */
static mrb_value
enum_update_hash(mrb_state *mrb, mrb_value self)
{
  mrb_int hash;
  mrb_int index;
  mrb_int hv;

  mrb_get_args(mrb, "iii", &hash, &index, &hv);
  /* All the bits of the element's hash: a boxed Symbol's number sits above
     bit 32, so truncating it to uint32_t gave every [:sym] one hash. The
     multiply makes the result depend on the order without the index. */
  {
    uint64_t h = ((uint64_t)hash ^ (uint64_t)hv) * 0x100000001b3ULL;
    h ^= h >> 29;
    (void)index;
    hash = (mrb_int)(h & 0xfffffffffffffffULL);
  }

  return mrb_int_value(mrb, hash);
}

void
mrb_init_enumerable(mrb_state *mrb)
{
  struct RClass *enumerable = mrb_define_module_id(mrb, MRB_SYM(Enumerable));  /* 15.3.2 */
  mrb_define_module_function_id(mrb, enumerable, MRB_SYM(__update_hash), enum_update_hash, MRB_ARGS_REQ(3));
}
