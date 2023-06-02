idf_component_register(
                    SRCS
                    	"main.c"
                    	Pheonix/taskmanager.c
                    	Pheonix/rcc/rcc.c
                    	Pheonix/gpio/pininit.c
                    	Pheonix/display/colortables.c
                    	Pheonix/display/display.c
                    	Pheonix/display/DisplayList.c
                    	Pheonix/display/gui.c
                    	Pheonix/utils/messages.c
                    	Pheonix/display/ST7789/st7789.c
                    INCLUDE_DIRS "."
                    PRIV_INCLUDE_DIRS ./Pheonix)
component_compile_options()
