import Options
from os import unlink, symlink, popen
from os.path import exists 

srcdir = "."
blddir = "build"
VERSION = "0.0.1"

def set_options(opt):
  opt.tool_options("compiler_cc")
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cc")
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")
  conf.check(lib='varnishapi', libpath=['/lib', '/usr/lib', '/usr/local/lib', '/usr/lib/varnish'])

def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.target = "varnishstat"
  obj.source = "src/varnishstat.cpp src/varnishstatwrapped.c"
  obj.linkflags = [ "-lrt", "-lvarnishapi" ]
  obj.cflags = ["-fPIC", "-I/usr/include/varnish"]
  obj.cxxflags = ["-fPIC", "-I/usr/include/varnish"]

def shutdown():
  if Options.commands['clean']:
    if exists('varnishstat.node'): unlink('varnishstat.node')
  else:
    if exists('build/Release/varnishstat.node') and not exists('varnishstat.node'):
      symlink('build/Release/varnishstat.node', 'varnishstat.node')
