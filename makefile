TARGET = ReRaylibPainter
SOURCES = ReRaylibPainter.c menu.c draw.c file.c

$(TARGET): $(SOURCES)
	gcc -o $(TARGET) $(SOURCES) -I include -L lib -lraylib -lgdi32 -lwinmm
	#gcc -o $(TARGET) $(SOURCES)  -lraylib -lm -ldl -lpthread -lX11
