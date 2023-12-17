# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly

set(srcs "src/nvs_configurator.c")
set(includes "include")
idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${includes}
                       REQUIRES nvs_flash)
