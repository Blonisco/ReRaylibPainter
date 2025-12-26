TARGET = ReRaylibPainter
SOURCES = ReRaylibPainter.c menu.c draw.c file.c drawfunc.c file_utils.c

# 检测操作系统
ifeq ($(OS),Windows_NT)
    # Windows 编译选项
    LDFLAGS = -L lib -lraylib -lgdi32 -lwinmm -lcomdlg32
    INCLUDES = -I include
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        # macOS 编译选项 (假设使用 brew 安装的 raylib)
        LDFLAGS = -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
    else
        # Linux 编译选项
        LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    endif
    INCLUDES = 
endif

$(TARGET): $(SOURCES)
	gcc  -o $(TARGET) $(SOURCES) $(INCLUDES) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(TARGET).exe
