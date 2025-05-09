set glad=src\glad.c
set main=src\main.c
set global=src\engine\global\global.c
set render=src\engine\render\render.c src\engine\render\render_init.c src\engine\render\render_util.c
set io=src/engine/io/io.c
set input=src/engine/input/input.c
set input_config=src/engine/input_config/input_config.c
set time=src/engine/time/time.c
set files= %glad% %main% %global% %render% %io% %input% %input_config% %time%
set libs=D:\projects\C\engine\lib\SDL2main.lib D:\projects\C\engine\lib\SDL2.lib D:\projects\C\engine\lib\freetype.lib

CL /Zi /I D:\projects\C\engine\includes %files% /link %libs% /OUT:mygame.exe