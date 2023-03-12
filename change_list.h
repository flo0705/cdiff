
enum ChangeType { Add, Rem };

struct Change {
    char* file;
    int position;
    enum ChangeType changeType;
};

struct ChangeListItem {
    struct Change item;
    struct ChangeListItem* next;
};

struct ChangeList {
    int length;
    struct ChangeListItem* root;
    struct ChangeListItem* last;
};

struct ChangeList createList(struct Change change) {
   struct ChangeListItem cli = { .item = change, .next = nullptr };
   struct ChangeList li = { .length = 1, .root = &cli, .last = &cli };
   return li;
}

void addToList(struct ChangeList list, struct Change item){
    struct ChangeListItem nli = { .item = item, .next = nullptr };
    list.last->next =  &nli;
    list.length++;
    list.last = &nli;
}

