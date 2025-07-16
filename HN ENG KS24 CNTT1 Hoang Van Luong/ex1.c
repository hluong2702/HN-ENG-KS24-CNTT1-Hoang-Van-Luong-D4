#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Food {
    int id;
    char foodName[100];
    char foodCategory[100];
    float price;
}Food;

typedef struct Node {
    Food food;
    struct Node *next;
}Node;

typedef struct Nodes {
    Food food;
    struct Nodes *next;
    struct Nodes *prev;
}Nodes;

Node *createNode(Food food) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->food = food;
    node->next = NULL;
    return node;
}

Nodes *createNodes(Food food) {
    Nodes *node = (Nodes *)malloc(sizeof(Nodes));
    node->food = food;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

Food addFood() {
    Food food;
    printf("Moi ban nhap id: ");
    scanf("%d", &food.id);
    getchar();
    printf("Moi ban nhap ten mon an: ");
    fgets(food.foodName,100, stdin);
    food.foodName[strlen(food.foodName)-1] = '\0';
    printf("Moi ban nhap danh muc mon an: ");
    fgets(food.foodCategory, 100, stdin);
    food.foodCategory[strlen(food.foodCategory)-1] = '\0';
    printf("Moi ban nhap gia mon an :");
    scanf("%f", &food.price);
    getchar();
    return food;
}

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d\n", current->food.id);
        printf("%s\n", current->food.foodName);
        printf("%s\n", current->food.foodCategory);
        printf("%.f\n", current->food.price);
        current = current->next;
    }
}

// cập nhật món ăn

Node *repair(Node *head, int pos) {
    Node *current = head;
    int index = 1;
    while (current != NULL && index < pos) {
        current = current->next;
        index++;
    }
    getchar();
    fgets(current->food.foodName, 100, stdin);
    current->food.foodName[strlen(current->food.foodName)-1] = '\0';
    fgets(current->food.foodCategory, 100, stdin);
    current->food.foodCategory[strlen(current->food.foodCategory)-1] = '\0';
    scanf("%f", &current->food.price);
    getchar();
    return head;
}

Node *deleteId(Node *head, int id) {
    Node *current = head;
    if (current != NULL && current->food.id == id) {
        current = current->next;
        free(current);
        return head;
    }
    while (current != NULL && current->next != NULL) {
        if (current->next->food.id == id) {
            Node *temp = current->next;
            current->next = current->next->next;
            free(temp);
            break;
        }
        current = current->next;
    }
    return head;
}

// danh dau ngung ban

Food nextDouble(Node *head) {
    Node *current = head;
    Food food;
    printf("Moi ban nhap mon muon chuyen sang");
    getchar();
    char name[100];
    fgets(name, 100, stdin);
    name[strlen(name)-1] = '\0';
    while (current != NULL && current->next != NULL) {
        if (strstr(current->next->food.foodName,name)) {
            food = current->next->food;
            break;
        }
        current = current->next;
    }
    return food;
}


//tim kiem mon an
void searchFood(Node *head, char* name) {
    Node *current = head;
    while (current != NULL) {
        if (strstr(current->next->food.foodName,name) != NULL) {
            printf("%d ", current->next->food.id);
            printf("%s ", current->next->food.foodName);
            printf("%s ", current->next->food.foodCategory);
            printf("%.f ", current->next->food.price);
        }
        current = current->next;
    }
}

//sap xep

Node *bubbleSort(Node *head) {
    for (Node *i = head; i != NULL; i= i->next) {
        for (Node *j = head; j != NULL; j = j->next) {
            if (j->food.price > j->next->food.price) {
                int temp = j->food.id;
                j->food.id = j->next->food.id;
                j->next->food.id = temp;
            }
        }
    }
    return head;
}


int main() {
    int choice;
    Food food;
    Node *head = NULL;
    Node *tail = NULL;
    Nodes *head2 = NULL;
    Nodes *tail2 = NULL;
    int cap,indexId;
    char name[100];

    do {
        printf("-----Restaurant-----\n");
        printf("1.Them mon an\n");
        printf("2.Hien thi danh sach mon dang ban\n");
        printf("3.Cap nhat thong tin mon an\n");
        printf("4.Danh dau ngung ban\n");
        printf("5.Hien thi danh sach mon da ngung ban\n");
        printf("6.Tim kiem theo ten mon\n");
        printf("7.Sap xep mon theo gia tang dan\n");
        printf("8.Thoat chuong trinh\n");
        printf("Moi ban nhap lua chon cua minh\n");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                printf("Moi ban nhap vao so luong mon muon them ");
                scanf("%d", &cap);
                getchar();
                for (int i = 0; i < cap; i++) {
                    food = addFood();
                    Node *newNode = createNode(food);
                    if (head == NULL) {
                        head = tail = newNode;
                    }else {
                        tail->next = newNode;
                        tail = tail->next;
                    }
                }
                break;
            case 2:
                printList(head);
                break;
            case 3:
                scanf("%d", &indexId);
                head = repair(head, indexId);
                printList(head);
                break;
            case 4:
                food = nextDouble(head);
                head = deleteId(head, food.id);
                Nodes *newNode = createNodes(food);
                if (head2 == NULL) {
                    head2 = tail2 = newNode;
                }else {
                    tail2->next = newNode;
                    newNode->prev = tail2;
                    tail2 = tail2->next;
                }
                printList(head2);
                break;
            case 5:
                break;
            case 6:
                printf("Nhap ten mon an can tim");
                getchar();
                fgets(name, 100, stdin);
                name[strcspn(name,"\n")] = '\0';
                searchFood(head,name);
                break;
            case 7:
                bubbleSort(head);
                printList(head);
                break;
            case 8:
                printf("Thank you.See you soon");
                break;
            default:
                printf("Khong hop le vui long nhap lai\n");
        }
    }while (choice != 8);

}
