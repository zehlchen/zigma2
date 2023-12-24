/*
 * ZIGMAtiq, Copyright (C) 2024 Chase Zehl O'Byrne
 *   <mail: zehl@live.com> http://zehlchen.com/
 *
 * This file is part of ZIGMAtiq.
 *
 * ZIGMAtiq is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * ZIGMAtiq is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ZIGMAtiq; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

#include "common.h"

Buffer* BufferCreate(Buffer* buffer, uint64 length)
{
  if (buffer == NULL)
    buffer = (Buffer*) malloc(sizeof(Buffer));

  uint64 toAllocate = length < ZQ_BUFFER_DEFAULT_CAPACITY ? ZQ_BUFFER_DEFAULT_CAPACITY : length;

  buffer->data     = (uint8*) malloc(toAllocate);
  buffer->length   = length;
  buffer->capacity = toAllocate;

  return buffer;
}

Buffer* BufferCreateCopy(Buffer* buffer, const uint8* data, uint64 length)
{
  if (buffer == NULL)
    buffer = (Buffer*) malloc(sizeof(Buffer));

  uint64 toAllocate = length < ZQ_BUFFER_DEFAULT_CAPACITY ? ZQ_BUFFER_DEFAULT_CAPACITY : length;

  buffer->data     = (uint8*) malloc(toAllocate);
  buffer->length   = length;
  buffer->capacity = toAllocate;

  memcpy(buffer->data, data, length);

  return buffer;
}

Buffer* BufferClone(Buffer* buffer, const Buffer* other)
{
  if (buffer == NULL)
    buffer = (Buffer*) malloc(sizeof(Buffer));

  uint64 toAllocate = other->capacity;

  buffer->data     = (uint8*) malloc(toAllocate);
  buffer->length   = other->length;
  buffer->capacity = toAllocate;

  memcpy(buffer->data, other->data, other->length);

  return buffer;
}

void BufferDestroy(Buffer* buffer)
{
  if (buffer == NULL)
    return;

  Nullify(buffer->data, buffer->capacity);

  free(buffer->data);
  free(buffer);
}

Buffer* BufferResize(Buffer* buffer, uint64 length)
{
  if (buffer == NULL)
    return BufferCreate(buffer, length);

  if (length <= buffer->capacity) {
    buffer->length = length;
    return buffer;
  }

  uint64 toAllocate = length < ZQ_BUFFER_DEFAULT_CAPACITY ? ZQ_BUFFER_DEFAULT_CAPACITY : length;

  buffer->data     = (uint8*) realloc(buffer->data, toAllocate);
  buffer->length   = length;
  buffer->capacity = toAllocate;

  return buffer;
}

void BufferPrint(const Buffer* buffer)
{
  DEBUG_ASSERT(buffer != NULL);

  fprintf(stderr, "Buffer: %p\n", buffer);
  fprintf(stderr, "  Length:   %lu\n", buffer->length);
  fprintf(stderr, "  Capacity: %lu\n", buffer->capacity);
  fprintf(stderr, "  Data:     %p = {\n    ", buffer->data);

  for (int i = 0; i < buffer->length; i++) {
    fprintf(stderr, "%02x", buffer->data[i]);

    if ((i + 1) % 32 == 0)
      fprintf(stderr, "\n    ");
  }

  fprintf(stderr, "\r  }\n");
}