/*-
 * Copyright (c) 2006 Verdens Gang AS
 * Copyright (c) 2006-2011 Varnish Software AS
 * All rights reserved.
 *
 * Author: Poul-Henning Kamp <phk@phk.freebsd.dk>
 * Author: Dag-Erling Smørgrav <des@des.no>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include <varnishapi.h>
#include <vsc.h>
#include <stdio.h>
#include <string.h>
#include "varnishstat.h"

struct once_priv {
  double up;
  int pad;
};

struct VSM_data *vd;
const struct VSC_C_main *VSC_C_main;

static int
iterator(void *priv, const struct VSC_point * const pt)
{
  uint64_t val;
  char keybuffer[64] = "";

  val = *(const volatile uint64_t*)pt->ptr;

  if (strcmp(pt->class, ""))
    sprintf(keybuffer, "%s.", pt->class);

  if (strcmp(pt->ident, ""))
    sprintf(keybuffer, "%s%s.", keybuffer, pt->ident);

  sprintf(keybuffer, "%s%s", keybuffer, pt->name);

  updateCounter(keybuffer, val);

  return 0;
  (void)priv;
}

void wrapUpdate(void) {
  struct once_priv op;
  memset(&op, 0, sizeof op);
  op.up = VSC_C_main->uptime;
  op.pad = 18;

  (void)VSC_Iter(vd, iterator, &op);
}

void wrapInit(void) {
  vd = VSM_New();
  VSC_Setup(vd);

  if (VSC_Open(vd, 1))
    return;

  VSC_C_main = VSC_Main(vd);
}
