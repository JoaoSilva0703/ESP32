idf_component_register(SRCS "src/serialDemo.c"
                        INCLUDE_DIRS "inc" "../uart/inc" "../logs/inc"
                        REQUIRES uart logs)