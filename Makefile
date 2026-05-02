# Unix/macOS: run `make`. Windows without make: run `build.bat` or:
#   gcc src/main.c src/editor.c src/file.c -o editor.exe

all:
	gcc src/main.c src/editor.c src/file.c -o editor

clean:
	$(RM) editor editor.exe