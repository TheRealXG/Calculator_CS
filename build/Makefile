EXENAME = ua_face

OBJDIR = obj

CC = gcc
RM = rm -rf
MKDIR = mkdir -p
SRC_ROOT = src

IFLAGS := -Isrc/include
IFLAGS += -Isrc/include/extern
IFLAGS += -Isrc/kcg
IFLAGS += -Isrc/man
IFLAGS += -Isrc/man/faceport
IFLAGS += -Isrc/uaadaptor

MFLAGS := -DKCGOGLXVER=6640 -DUA_SOCKET

OFLAGS := -g
CFLAGS := $(OFLAGS) $(MFLAGS) $(IFLAGS) 

# For Linux
# LDFLAGS = -lsocket -lnsl
LDFLAGS = -lnsl

space := 
space += 
VPATH := $(subst $(space),:,$(shell find $(SRC_ROOT) -type d))

OMIT_SRCS := 

S_SRCS  := $(filter-out $(OMIT_SRCS),$(shell find $(SRC_ROOT) -name "*.c"))
S_OBJS  := $(addprefix $(OBJDIR)/, $(notdir $(S_SRCS:.c=.o)))

all: $(EXENAME)

clean:
	$(RM) $(EXENAME) $(OBJDIR)

$(EXENAME): $(S_OBJS)
	@echo "Building $(EXENAME)..."
	$(CC) $(CFLAGS) -o $@ $(OBJDIR)/*.o $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@$(MKDIR) $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@
