CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ld $(OPTLIBS)
PREFIX?=/usr/local

SRC=src
TEST=tests
BIN=bin

SOURCES=$(wildcard $(SRC)/**/*.c $(SRC)/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard $(TEST)/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

PROGRAM_SRC=$(wildcard $(BIN)/*.c)
PROGRAMS=$(patsubst %.c,%,$(PROGRAM_SRC))

TARGET=build/libtcunit.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# the target build
all: $(TARGET) $(SO_TARGET) tests $(PROGRAMS)

dev: CFLAGS=-g -Wall -Isrc -Wextra $(OPTFLAGS)
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
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib

# The checker
check:
	@echo Files with potentially dangerous functions
	@egrep '[^_.>a-zA-Z0-9](str(?ncpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|\
		|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
