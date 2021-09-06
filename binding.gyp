{
  "targets": [
    {
      "target_name": "nativelib",
      "sources": [
        "main.cc"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "/usr/include/at-spi2-atk/2.0", 
        "/usr/include/at-spi-2.0",
        "/usr/include/dbus-1.0",
        "/usr/lib/x86_64-linux-gnu/dbus-1.0/include",
        "/usr/include/gtk-3.0",
        "/usr/include/gio-unix-2.0",
        "/usr/include/cairo",
        "/usr/include/pango-1.0",
        "/usr/include/fribidi",
        "/usr/include/harfbuzz",
        "/usr/include/atk-1.0",
        "/usr/include/cairo",
        "/usr/include/pixman-1",
        "/usr/include/uuid",
        "/usr/include/freetype2",
        "/usr/include/libpng16",
        "/usr/include/gdk-pixbuf-2.0",
        "/usr/include/libmount",
        "/usr/include/blkid",
        "/usr/include/glib-2.0",
        "/usr/lib/x86_64-linux-gnu/glib-2.0/include"
      ],
      "libraries": [ 
        "-lgtk-3",
        "-lgdk-3",
        "-lpangocairo-1.0",
        "-lpango-1.0",
        "-lharfbuzz -latk-1.0",
        "-lcairo-gobject",
        "-lcairo",
        "-lgdk_pixbuf-2.0",
        "-lgio-2.0",
        "-lgobject-2.0",
        "-lglib-2.0",
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "defines": ["NAPI_CPP_EXCEPTIONS"],
      "xcode_settings": {
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
      }
    }
  ]
}