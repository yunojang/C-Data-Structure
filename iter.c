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

// tail은 마지막에 고정된 더미노드
void list_init(struct list *lst)
{
    lst->head.next = &lst->tail;
    lst->tail.prev = &lst->head;
}

void list_push_back(struct list *lst, struct list_elem *e)
{
    struct list_elem *before = lst->tail.prev;
    before->next = e;
    e->prev = before;
    e->next = &lst->tail;
    lst->tail.prev = e;
}

// lst를 바꾸지는 않지만, list*이 아니라 list로하면 struct가 크면 불필요한 메모리 복사 발생
struct list_elem *list_begin(struct list *lst)
{
    return lst->head.next; // 시작 노드
}

struct list_elem *list_end(struct list *lst)
{
    return &lst->tail;
}

struct list_elem *list_next(struct list_elem *e)
{
    return e->next;
}

#define list_entry(LIST_ELEM, STRUCT, MEMBER) \
    ((STRUCT *)((char *)(LIST_ELEM) - offset_of(STRUCT, MEMBER)))
#define offsetof(TYPE, MEMBER) ((size_t)&(((TYPE *)0)->MEMBER))

// 사용자 구조
struct my_item
{
    int value;
    struct list_elem elem;
};

int main()
{
    struct list mylist;
    list_init(&mylist);

    struct my_item *a = malloc(sizeof *a);
    a->value = 10;
    list_push_back(&mylist, &a->elem);

    // 끝 테일과 다를때까지
    for (struct list_elem *e = list_begin(&mylist);
         e != list_end(&mylist);
         e = list_next(e))
    {
        // 반복 내 구현
    }
}