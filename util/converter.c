/*
 * converter.c: generates raw audio data to C code and writes it to stdout
 *
 * This file is part of GTick
 *
 *
 * Copyright (c) 1999, Alex Roberts
 * Copyright (c) 2003, 2004, 2005, 2006 Roland Stigge <stigge@antcom.de>
 *
 * GTick is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * GTick is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GTick; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define SAMPLESIZE sizeof(short)

int main(int argc, char* argv[]) {
  short x;
  int fd;
  int i = 0;
  int size;
  
  if (argc != 2) {
    fprintf(stderr, "usage: converter [raw 16 bit signed sample file]\n");
    return 0;
  } else {
    printf("/*                                                          */\n");
    printf("/* This file was automatically generated by converter.      */\n");
    printf("/* It contains samples in signed 16 bit format.             */\n");
    printf("/*                                                          */\n");
    printf("\n");
    printf("static short tickdata[] = {");
  
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
      fprintf(stderr, "Error: Couldn't open file.\n");
      return -1;
    } else {
      size = lseek(fd, 0, SEEK_END) / SAMPLESIZE;
      lseek(fd, 0, SEEK_SET);
      while (read(fd, &x, SAMPLESIZE) == SAMPLESIZE) {
        if (i % 8)
          printf(" ");
        else
          printf("\n");
        printf("%6d", x);
        if (i < size - 1) printf(",");
        i++;
      }
      close(fd);
      printf("\n};\n");
    }
  }
  return 0;
}

