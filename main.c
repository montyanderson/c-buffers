#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	size_t length;
	size_t container;
	char *buf;
} Buffer;

int buffer_init(Buffer *buf) {
	buf->length = 0;
	buf->container = 1;
	buf->buf = malloc(buf->container);

	return buf->buf != NULL;
}

int buffer_append(Buffer *buf, char *data, size_t length) {
	size_t old_length = buf->length;
	buf->length += length;

	while(buf->container < buf->length) {
		buf->container *= 2;
	}

	buf->buf = realloc(buf->buf, buf->container);

	if(buf->buf == NULL) {
		return 0;
	}

	memcpy(&buf->buf[old_length], data, length);

	return 1;
}

void buffer_print(Buffer *buf) {
	size_t i;

	for(i = 0; i < buf->length; i++) {
		printf("%c", buf->buf[i]);
	}
}

int main() {
	Buffer buf;

	buffer_init(&buf);
	buffer_print(&buf);
	buffer_append(&buf, "Monty", 5);
	buffer_print(&buf);
	buffer_append(&buf, "Monty", 5);
	buffer_print(&buf);

	for(size_t i = 0; i < 1000000000; i++) {
		buffer_append(&buf, "c", 1);
	}

	printf("%lu %lu\n", buf.length, buf.container);
}
