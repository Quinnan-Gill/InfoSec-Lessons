#include <stdio.h>

int main() {
    int i;

    char char_array[5] = {'a', 'b', 'c', 'd', 'e'};
    int int_array[5] = {1, 2, 3, 4, 5};

    void *void_pointer;

    void_pointer = (void *) char_array;

    for(i=0; i < 5; i++) { // Iterate through the int array with the int_pointer
        printf("[integer pointer] points to %p, which contains the integer %d\n",
            int_pointer, *((char *) int_pointer);
        int_pointer = (void *) ((char *) int_pointer + 1);
    }

    for(i=0; i < 5; i++) { // Iterate through the char array with the char_pointer
        printf("[char pointer] points to %p, which contains the char %c\n",
            char_pointer, *((int *) char_pointer);
        char_pointer = (void *) ((int *) char_pointer + 1);
    }
}
