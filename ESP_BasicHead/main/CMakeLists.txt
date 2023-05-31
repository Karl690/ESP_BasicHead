idf_component_register(
                    SRCS "main.c" Pheonix/taskmanager.c Pheonix/rcc/rcc.c Pheonix/gpio/pininit.c
                    INCLUDE_DIRS "."
                    PRIV_INCLUDE_DIRS ./Pheonix)
component_compile_options(-isystem ./Pheonix)
