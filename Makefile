CFLAGS=-g -O2 -Wall -Wextra -Iinclude -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ld $(OPTLIBS)
PREFIX?=/usr/local

SRC=src
INCLUDE=include
TEST=tests
BIN=bin

SOURCES=$(wildcard $(SRC)/**/*.c $(SRC)/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
HEADERS=$(wildcard $(INCLUDE)/**/*.h $(INCLUDE)/*.h)

TEST_SRC=$(wildcard $(TEST)/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

PROGRAM_SRC=$(wildcard $(BIN)/*.c)
PROGRAMS=$(patsubst %.c,%,$(PROGRAM_SRC))

TARGET=build/libtcunit.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# the target build
all: $(TARGET) $(SO_TARGET) tests $(PROGRAMS)

dev: CFLAGS=-g -Wall -Iinclude -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p $(BIN)

# The unit tests
.PHONY: tests
tests: LDLIBS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

# The cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS) $(PROGRAMS)
	rm -f tests/tests.log
	find . -name "*.gc" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib
	install -d $(DESTDIR)/$(PREFIX)/include/tcunit
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib
	install $(HEADERS) $(DESTDIR)/$(PREFIX)/include/tcunit

# The checker
check:
	@echo Files with potentially dangerous functions
	grep -E '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
