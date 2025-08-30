#include <stdlib.h>

// ======================
//        private 
// ======================

static int* data;
static int capacity = 0;
static int length = 0;

// ======================
//        public
// ======================

int stack_length() {
    return length;
}

void stack_push(int value) {
    if (capacity == 0) {
        data = malloc(sizeof(int) * 2);
        capacity = 2;
    }
    if (length >= capacity) {
        int* new = malloc(sizeof(int) * capacity * 2);
        capacity = capacity * 2;
        for (int i = 0; i < length; i++) {
            new[i] = data[i];
        }
        free(data);
        data = new;
    }
    data[length++] = value;
}

int stack_pop() {
    int ret = data[length - 1];
    length--;
    return ret;
}

int stack_peak() {
    return data[length - 1];
}

void stack_clear() {
    free(data);
    capacity = 0;
    length = 0;
}