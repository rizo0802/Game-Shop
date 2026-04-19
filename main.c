#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//variabila globala
int gold= 200;
//initializarea a doua structuri
//structura pentru itemele complete
typedef struct items {

    char name[50];

    struct  items* left;

    struct  items* right;

} ITEMS;

//structura pentru inventarul userului
typedef struct inventorySlot {

    char name[50];

    struct inventorySlot* next;

} INVENTORY;

//creare arborilor ITEMS
ITEMS* createITEMS(char* name) {

    ITEMS* newInventorySlot= (ITEMS*)malloc(sizeof(ITEMS));

    strcpy(newInventorySlot->name,name);

    newInventorySlot->left= NULL;

    newInventorySlot->right= NULL;

    return newInventorySlot;

}
//crearea listei simplu inlantuite pentru inventar
INVENTORY* createINVENTORY( char* name) {

    INVENTORY* newInventorySlot= (INVENTORY*)malloc(sizeof(INVENTORY));

    strcpy(newInventorySlot->name,name);

    newInventorySlot->next= NULL;

    return newInventorySlot;

}
//adaugarea itemelor cumparate in invetar
void addToInventory(INVENTORY** inventory,char* name) {

    INVENTORY* newInventorySlot= createINVENTORY(name);

    newInventorySlot->next= *inventory;

    *inventory= newInventorySlot;

    printf("\nItem %s has been added to your inventory.\n",name);

}
//afisarea inventarului curent
void displayInventory(INVENTORY* inventory) {

    printf("\n--- Your Inventory ---\n");

    if (inventory== NULL) {

        printf("- Empty\n");

        return;
    }
    while (inventory!= NULL) {

        printf("- %s\n", inventory->name);

        inventory= inventory->next;

    }
}
//afisarea arborilor ce contin itemele finale
void displaypreItems(ITEMS* preItems[], int itemcount) {

    printf("\n--- Available items to build ---\n");

    for (int i = 0; i < itemcount; i++) {

        printf("- %s: [%s, %s]\n", preItems[i]->name, preItems[i]->left->name, preItems[i]->right->name);

    }

}

//crearea interfatei shopului
void shopMenu(char* items[],int prices[], int itemCount) {
    printf("\n--- Shop Menu ---\n");

    int i;

    for (i= 0;i< itemCount;i++) {

        printf("%d. %s (%d gold)\n", i + 1, items[i], prices[i]);

    }

    printf("9. Exit Shop\n");

}

//cumpararea itemelor din shop si anumite checkuri
void buyComponents(int choice, char* items[], int prices[], int itemCount, INVENTORY** inventory) {
    if ((choice<1||choice>itemCount)&&(choice!=9)) {
        if (choice!= 9) {

            printf("\nInvalid choice, your selection doesnt exist.\n");

        }

        return;

    }

    char* itemName= items[choice - 1];

    int cost= prices[choice - 1];

    if (gold< cost) {

        printf("\nNot enough gold to buy %s. You need %d gold but have %d gold.\n", itemName, cost, gold);

    } else {

        gold=gold - cost;
        addToInventory(inventory, itemName);

        printf("\nYou purchased %s for %d gold. Remaining gold: %d\n", itemName, cost, gold);
    }
}

//metoda de a obtine gold pentru iteme este un
void farmGold() {
    int earnedGold = rand()%50;
    gold=gold+ earnedGold;
    printf("\nYou farmed %d gold! Current gold is: %d\n", earnedGold, gold);
}

//contruirea itemelor finale bazata pe conditia ca userul are componentele necesare in inventar
int ItemBuilding(ITEMS* preItems[], int itemcount, INVENTORY** inventory) {
    int i;
    for (i = 0; i< itemcount; i++) {
        int hasFirstComponent=0;
        int hasSecondComponent=0;//checkurile daca are componentele necesare pentru construire
        INVENTORY* current;
        current = *inventory;

        while (current != NULL) {//verificare daca in invetar exista componentele necesare
            if (strcmp(current->name, preItems[i]->left->name) == 0) {
                hasFirstComponent= 1;
            }
            if (strcmp(current->name, preItems[i]->right->name) == 0) {
                hasSecondComponent= 1;
            }
            current = current->next;
        }

        if (hasFirstComponent && hasSecondComponent) {//daca s au gasit componentele userul poate construi itemul
            char choice;
            INVENTORY *prev = NULL, *temp = *inventory;
            printf("\nIt seems that you can build %s! Would you want to build it :3? (y/n): ", preItems[i]->name);
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                printf("\nCongratulations you built %s !\n", preItems[i]->name);

                //daca userul accepta construirea itemului componentele din inventar vor fi sterse iar itemul completat va fi adaugat in inventar
                while (temp!= NULL) {
                    if (strcmp(temp->name,preItems[i]->left->name) == 0||strcmp(temp->name, preItems[i]->right->name) == 0) {
                        if (prev== NULL)
                            *inventory= temp->next;
                        else
                            prev->next= temp->next;
                        //daca componentele din inventar se potrives cu cele din item atunci se vor sterge componentele
                        //prev va avea ca valoare valoarea anterioara a lui temp iar atunci cand pe pozitia temp este o componenta care trebuie stearsa temp va merge pe pozitia din fata lui temp, variabila ComponentToBeDeleted va lua valoarea lui temp, temp merge va merge in fata si este eliberata memoria in ComponentToBeDeleted
                        INVENTORY* ComponentToBeDeleted= temp;
                        temp = temp->next;
                        free(ComponentToBeDeleted);
                    } else {
                        prev= temp;//aici prev va lua din nou valoarea din spatele lui temp
                        temp= temp->next;
                    }
                }

                // itemul este adaugat in inventar
                addToInventory(inventory, preItems[i]->name);
                return 1;
            }
        }
    }
    printf("\nNo items can be built with your current inventory.\n");//daca nu s au gasit componente care coincid
    return 0;
}

int main() {
    //functie necesara pentru functia rand din farmGold
    srand(time(NULL));

    //incarcarea celor 3 arbori cu date despre itemele ce pot fi construite
    ITEMS* preItems[3];
    preItems[0]= createITEMS("InfinityEdge");
    preItems[0]->left= createITEMS("BFSword");
    preItems[0]->right= createITEMS("Pickaxe");
    preItems[1]= createITEMS("Thornmail");
    preItems[1]->left= createITEMS("ChainVest");
    preItems[1]->right= createITEMS("BrambleVest");
    preItems[2]= createITEMS("TitanicHydra");
    preItems[2]->left= createITEMS("Tiamat");
    preItems[2]->right= createITEMS("RubyCrystal");
    //initializarea inventariului cu null pentru verificarea daca inventarul este gol sau nu la inceput
    INVENTORY* inventory = NULL;
    //componentele care pot fi gasite in shop si pretul lor
    char* shopcomponents[8] = {"BFSword", "Pickaxe", "ChainVest", "BrambleVest", "Tiamat", "RubyCrystal", "Armor", "HealingPotion"};
    int shopprices[8] = {100, 80, 50, 70, 120, 60, 40, 30};
    int itemCount= 8;

    printf("\n=== Welcome to the League Of Legends Item Shop! ===\n");
    int choice;
    do {
        printf("\n------------------ Main Menu ------------------\n");
        printf("1. View available items to build\n");
        printf("2. Craft items\n");
        printf("3. View inventory\n");
        printf("4. View current gold\n");
        printf("5. Component Shop\n");
        printf("6. Farm gold\n");
        printf("7. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displaypreItems(preItems, 3);
                break;
            case 2:
                ItemBuilding(preItems, 3, &inventory);
                break;
            case 3:
                displayInventory(inventory);
                break;
            case 4:
                printf("\nCurrent gold: %d\n", gold);
                break;
            case 5: {
                int shopChoice;
                do {
                    shopMenu(shopcomponents, shopprices, itemCount);
                    printf("\nEnter the number of the component you want to buy: ");
                    scanf("%d", &shopChoice);
                    if (shopChoice != 9) {
                        buyComponents(shopChoice, shopcomponents, shopprices, itemCount, &inventory);
                    }
                } while (shopChoice != 9);
                break;
            }
            case 6:
                farmGold();
                break;
            case 7:
                printf("\nEnjoy your items and come back for more!\n");
                break;
            default:
                printf("\nChoice doesnt exist.\n");
        }
    } while (choice!= 7);
    return 0;
}

