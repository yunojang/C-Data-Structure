#include <stdio.h>
#include <stdlib.h>

struct list_elem
{
    struct list_elem *prev;
    struct list_elem *next;
};

struct list
{
    struct list_elem head;
    struct list_elem tail;
};

void list_init(struct list *lst)
{
    lst->head.next = &lst->tail;
    lst->tail.prev = &lst->head;
}

void push_list_back(struct list *lst, struct list_elem *elem)
{
    struct list_elem *before = lst->tail.prev;
    before->next = elem;
    elem->prev = before;
    elem->next = &lst->tail;
    lst->tail.prev = elem;
}

struct list_elem *list_begin(struct list *lst)
{
    return lst->head.next;
}

struct list_elem *list_end(struct list *lst)
{
    return &lst->tail;
}

struct list_elem *list_next(struct list_elem *e)
{
    return e->next;
}

#define LIST_ENTRY(list_elem, struct, member) \
    ((struct *)((char *)list_elem - offset_of(struct, member)))
#define offset_of(type, member) ((size_t)&((type *)0)->member)

struct my_item
{
    int value;
    struct list_elem elem;
};

int main()
{
    struct list my_list;
    list_init(&my_list);

    struct my_item *a = malloc(sizeof *a);
    a->value = 10;
    push_list_back(&my_list, &a->elem);

    struct my_item *b = malloc(sizeof *b);
    b->value = 20;
    push_list_back(&my_list, &b->elem);

    for (struct list_elem *cur = list_begin(&my_list);
         cur != list_end(&my_list);
         cur = list_next(cur))
    {
        struct my_item *it = LIST_ENTRY(cur, struct my_item, elem);
        printf("%d ", it->value);
    }

    printf("%zu", (size_t)&((struct my_item *)0)->elem);
}