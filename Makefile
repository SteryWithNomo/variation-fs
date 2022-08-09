# ---------------------------------------- #
# SINGLE-HEADER FILE SYSTEM | VARIATION-FS #
#    SHARED-LIBRARY CONVERTING MAKEFILE    #
# ---------------------------------------- #

CC = gcc
lib = vn_fs.h
win_out = vn_fs.dll
uni_out = vn_fs.so

ifeq ($(OS),Windows_NT)
	delete = del
else
	delete = rm
endif

.PHONY: win_run uni_run win_clean uni_clean

win_run: $(lib)
	$(CC) -shared -fPIC $(lib) -o $(win_out)

win_clean: $(win_out)
	$(delete) $(win_out)

uni_run: $(lib)
	$(CC) -shared -fPIC $(lib) -o $(uni_out)

uni_clean:
	$(delete) $(uni_out)

# MADE BY @hanilr #