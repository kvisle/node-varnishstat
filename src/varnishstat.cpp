/*-
 * Copyright (c) 2012 Trygve Vea
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
 *
 * Most of this code is from varnishstat.
 */
#define BUILDING_NODE_EXTENSION
#include <node.h>

#include "varnishstatwrapped.h"
#include <iostream>

using namespace v8;

Local<Object> myCounters;

extern "C" {
void updateCounter(const char *key, uint64_t value) {
  myCounters->Set(String::NewSymbol(key), Number::New(value));
}
}

Handle<Value> fetchStats(const Arguments& args) {
  HandleScope scope;

  myCounters = Object::New();
  wrapUpdate();

  return scope.Close(myCounters);
}

void Init(Handle<Object> target) {
  wrapInit();

  target->Set(String::NewSymbol("fetchStats"),
    FunctionTemplate::New(fetchStats)->GetFunction());
}

NODE_MODULE(varnishstat, Init);
