EXENAME = build/db_calc

OBJDIR = obj

CC = gcc
RM = rm -rf
MKDIR = mkdir -p
SRC_ROOT = .

IFLAGS := 

MFLAGS := 

OFLAGS := -g
CFLAGS := $(OFLAGS) $(MFLAGS) $(IFLAGS) 

LDFLAGS = -lsqlite3

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
