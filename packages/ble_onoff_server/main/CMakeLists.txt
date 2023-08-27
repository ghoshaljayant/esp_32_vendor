set(srcs "main.c"
    "board.c")

idf_component_register(SRCS "oled/src/oled_util.c" "${srcs}"
                    INCLUDE_DIRS  ".")
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
