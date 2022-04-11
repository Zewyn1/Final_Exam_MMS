#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
struct item{
    signed int number;
    char desc[250];
    double weight;
    double price;
    struct item *next;
};
//linked list items_count elements, generate random data with which to fill the list, number should be signed int 16bit unique number, desc should begin with a capital letter and contain between 5 and 10 random words seperated by an interval, weight is a double number between 0.100kg and 100.00kg,price is a double number between 1.00lv and 1500.00lv
struct item *generate_list(int items_count){
    struct item *head = NULL;
    struct item *current = NULL;
    struct item *new_item = NULL;
    int i;
    for(i = 0; i < items_count; i++){
        new_item = malloc(sizeof(struct item));
        if(new_item == NULL){
            printf("Error: malloc failed\n");
            exit(1);
        }
        new_item->number = rand() % 65536;
        new_item->weight = (double)rand() / (double)RAND_MAX * 100.00 + 0.100;
        new_item->price = (double)rand() / (double)RAND_MAX * 1500.00 + 1.00;
        new_item->next = NULL;
        if(head == NULL){
            head = new_item;
            current = new_item;
        }else{
            current->next = new_item;
            current = new_item;
        }
    }
    return head;
}
//print the list to stdout
void print_list(struct item *head){
    struct item *current = head;
    while(current != NULL){
        printf("%d %s %.2f %.2f\n", current->number, current->desc, current->weight, current->price);
        current = current->next;
    }
}
//free the list
void free_list(struct item *head){
    struct item *current = head;
    struct item *next = NULL;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
}
//function to find the weight of all items in the list, if it doesn't succeed it returns -1
double get_weight(struct item *head){
    struct item *current = head;
    double weight = 0.00;
    while(current != NULL){
        weight += current->weight;
        current = current->next;
    }
    return weight;
}
//function to find the lowest priced item in the list if it doesn't succeed it returns a pointer to null
struct item *get_lowest_price(struct item *head){
    struct item *current = head;
    struct item *lowest_price = NULL;
    double lowest_price_value = 0.00;
    while(current != NULL){
        if(current->price < lowest_price_value || lowest_price_value == 0.00){
            lowest_price_value = current->price;
            lowest_price = current;
        }
        current = current->next;
    }
    return lowest_price;
}
int main() {
    int items_count = 0;
    scanf("%d", &items_count);
    struct item *head = generate_list(items_count);
    print_list(head);
    double weight = get_weight(head);
    if(weight == -1){
        printf("Error: get_weight failed\n");
        exit(1);
    }
    printf("%.2f\n", weight);
    struct item *lowest_price = get_lowest_price(head);
    if(lowest_price == NULL){
        printf("Error: get_lowest_price failed\n");
        exit(1);
    }
    printf("%d %s %.2f %.2f\n", lowest_price->number, lowest_price->desc, lowest_price->weight, lowest_price->price);
    free_list(head);
    return 0;
}
