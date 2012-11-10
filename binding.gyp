{
  "targets": [
    {
      "target_name": "varnishstat",
      "sources": [ "src/varnishstat.cpp", "src/varnishstatwrapped.c" ],
      "include_dirs": [ "/usr/include/varnish" ],
      "link_settings": {
        "libraries": [ "-lrt", "/usr/lib/varnish/libvarnishcompat.so", "/usr/lib/libvarnishapi.so" ],
        "library_dirs": [ "/usr/lib", "/usr/lib/varnish" ]
      }
    }
  ]
}
