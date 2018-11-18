#ifndef MAP_H_
#define MAP_H_

struct table *createTable(int size);

int hashCode(struct table *t, int key, int val);

void insert(struct table *t, int key, int key);

#endif
