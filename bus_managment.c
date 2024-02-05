
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct driver {
    char name[1000];
    int mobile;
    int busid;
    struct driver *dnext;
} driver;
 


typedef struct BusRoute {
     int id;
     char name[50];
     int fare;
     char from[100];
     char to[100];
    struct BusRoute *bus_route_next;
} BusRoute;
 


typedef struct Card {
    int cardNumber;
    float balance;
} Card;



typedef struct ureg {
    int uid;
    char upass[100];
    float balance;
    struct ureg *urnext;
} ureg;


typedef struct areg {
    int aid;
    char apass[100];
    struct areg *arnext;
} areg;


// Global variables

driver *dhead = NULL;

BusRoute *bushead = NULL;

ureg *urhead = NULL;

areg *arhead = NULL;

// Function declarations
void add_bus_route();
void add_driver();
void displayBusRoutes();
void loadCardBalance();
void deductFare(int routeId);
void freeMemory();
void uregistration();
int ulogin(ureg *ulhead);
void aregistration();
int  alogin(areg *alhead);
void admin();
void user();  
void buyTicket();
void about_project();

int main() {
    system("color f1");
    int choice;

    while (1) {
           printf("\n---------------- Welcome to Daffodil Bus Managment System ----------------\n\n");
        printf("\t\tChoose your role:\n");
        printf("\t\t[1]Admin\n");
        printf("\t\t[2] User\n");
        printf("\t\t[3]About project and contribution\n");
         printf("\t\t[4] Exit \n");
        printf("\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            system("cls");
                admin();
                break;
            case 2:
             system("cls");
                user();
                break;

           case 3 :
             about_project();
             break;

            case 4:
                printf("Exiting...\n");
                
                freeMemory();
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
void add_bus_route() {
    BusRoute *newbus = (BusRoute*)malloc(sizeof(BusRoute));
    printf("\n\n-----------------------------------------------------\n");
    if (newbus == NULL) {
        printf("bus can't added to the list\n");
        return;
    }
    printf("\t\tEnter Bus Name: ");
    scanf("%s",&newbus->name);
    printf("\t\tEnter bus No: ");
    scanf("%d", &newbus->id);
    printf("\t\tEnter bus will start : ");
    scanf("%s", &newbus->from);
    printf("\t\tEnter area to go : ");
    scanf("%s", &newbus->to);
     printf("\t\tEnter fare ");
    scanf("%d", &newbus->fare);

    newbus->bus_route_next= NULL;

    if (bushead == NULL) {
        bushead = newbus;
    } else {
        BusRoute *temp = bushead;
        while (temp->bus_route_next!= NULL) {
            temp = temp->bus_route_next;
        }
        temp->bus_route_next= newbus;
    }
FILE *fp;

fp = fopen("bus_routes.txt", "a");

if(fp == NULL) {
printf("Error opening file!\n");
return;
}

fprintf(fp, "%s %d %s %s %d\n", newbus->name, newbus->id, newbus->from, newbus->to, newbus->fare);

fclose(fp);

    
    

    printf("Bus and Route added successfully.\n");
}


void buyTicket() {
    FILE *fp;

fp = fopen("bus_routes.txt","r");

if(fp == NULL) {
printf("Error opening file!\n");
return;
}
    
    printf("\n\n-----------------------buy ticket section---------------------------\n");
    int routeId;
    int stuid;
    char from1[100];
    char to1[1000];
    printf("\t\twhere you to pick bus : ");
    scanf("%s",&from1);
    printf("\t\twhere you want to go : ");
    
    scanf("%s",&to1);
    printf("\t\tput your student id : ");
    scanf("%d",&stuid);
    ureg  *temp=urhead;
     
    while(temp !=NULL){
        if(temp->uid==stuid){
            break;
        }
        temp=temp->urnext;
    }



    BusRoute *current =bushead;
    while(fscanf(fp, "%s %d %s %s %d", current->name, &current->id, current->from, current->to, &current->fare) != EOF) {
        if (strcmp(current->from,from1)==0 && strcmp(current->to,to1)==0) {
            

            if (temp->balance >= current->fare) {
                temp->balance -= current->fare;
                printf("\t\tFare of %d taka deducted. Remaining balance: %.2f taka\n", current->fare, temp->balance);
           fclose(fp); } else {
                printf("\t\tInsufficient balance on the card. Please load more balance.\n");
             fclose(fp);
             return ;
        
        }

                   
            printf("\t\tTicket purchased successfully for Route ID %d.\n", routeId);
              fclose(fp);            
            return;
        }
        current = current->bus_route_next;
    }

    
    printf("\t\tRoute not found.\n");
}


void add_driver() {
    driver *newdriver = (driver *)malloc(sizeof(driver));
    printf("\n\n--------------------------driver add list section-----------------------\n");
    if (newdriver == NULL) {
        printf("\t\tdriver list can't added to the list.\n");
        return;
    }

    printf("\t\tEnter Driver Name : ");
    scanf("%s", newdriver->name);
    printf("\t\tEnter Mobile No : ");
    scanf("%d", &newdriver->mobile);
    printf("\t\tenter bus code : ");
    scanf("%d",&newdriver->busid);

    newdriver->dnext = NULL;

    if (dhead == NULL) {
        dhead = newdriver;
    } else {
        driver *temp = dhead;
        while (temp->dnext != NULL) {
            temp = temp->dnext;
        }
        temp->dnext = newdriver;
    }

    printf("\t\tDriver added successfully.\n");
}

void displayBusRoutes() {
    BusRoute *current = bushead;
printf("\n\n-----------------------------------------------------\n");
    
    while (current != NULL) {
        printf("\t\tRoute ID: %d\n", current->id);
        printf("\t\tRoute Name: %s\n", current->name);
        
        printf("\t\tFare: %d taka\n", current->fare);
         driver *dtemp=dhead;
      while(dtemp!=NULL){
       if(dtemp->busid==current->id){
        printf("\t\tbus driver name is %s\n",dtemp->name);
        printf("\t\tmobile number : %d\nn",dtemp->mobile);
       }
     dtemp=dtemp->dnext;

       }
      
      


    
        current = current->bus_route_next;
    }






    
}
void loadCardBalance() {
    printf("\n\n---------------------------recharge your one card balance here--------------------------\n");
    int cardnum;
    float balanceid;
    printf("\t\tEnter id Number: ");
    scanf("%d", &cardnum);
    printf("\t\tEnter Initial Balance: ");
    scanf("%f",&balanceid);

   ureg *temp=urhead;
   while(temp!=NULL){
  if(temp->uid==cardnum){
    temp->balance=(temp->balance +balanceid);
    break;

  }
 temp=temp->urnext;

   }





    printf("\t\tCard loaded with %.2f taka\n", temp->balance);
}

void freeMemory() {
    free(dhead);
    free(bushead);
    free(urhead);
    free(arhead);

}

void uregistration() {
    ureg *unewuser = (ureg *)malloc(sizeof(ureg));
    if (unewuser == NULL) {
        printf("\t\tMemory allocation failed.\n");
        return;
    }
printf("\n\n----------------------registration for student-------------------------------\n");
    printf("\t\tEnter Your ID: ");
    scanf("%d", &unewuser->uid);
    printf("\t\tEnter Your Password: ");
    scanf("%s", unewuser->upass);
      unewuser->balance=100;
    unewuser->urnext = NULL;

    if (urhead == NULL) {
        urhead = unewuser;
    } else {
        ureg *temp = urhead;
        while (temp->urnext != NULL) {
            temp = temp->urnext;
        }
        temp->urnext = unewuser;
    }

    printf("\t\tUser registered successfully.\n");
}

int ulogin(ureg *ulhead) {
    printf("\n\n-------------------login section for students----------------------------------\n");
    int uuser;
    char up[100];
    if (ulhead == NULL) {
        printf("\t\tNo users registered yet. Please register first.\n\n");
        return 0;
    } else {
        printf("\t\tEnter ID: ");
        scanf("%d", &uuser);
        getchar(); // Clear the newline character from the buffer

        printf("\t\tEnter Password: ");
        scanf("%s", up);

        ureg *utemp = ulhead;
        while (utemp != NULL) {
            if (utemp->uid == uuser && strcmp(utemp->upass, up) == 0) {
                printf("\t\tUser Found. Logged In.\n\n");
                return 1;
            } else {
                utemp = utemp->urnext;
            }
        }
        printf("\t\tUser ID or password is incorrect.\n\n");
        return 0;
    }
}

void aregistration() {
    printf("\n\n---------------------registration for admin panel--------------------------------\n");
    areg *anewuser = (areg *)malloc(sizeof(areg));
    if (anewuser == NULL) {
        printf("\t\t registration failed.\n");
        return;
    }

    printf("\t\t1.Enter Your ID: ");
    scanf("%d", &anewuser->aid);
    printf("\t\t2.Enter Your Password: ");
    scanf("%s", anewuser->apass);

    anewuser->arnext = NULL;

    if (arhead == NULL) {
        arhead = anewuser;
    } else {
        areg *temp = arhead;
        while (temp->arnext != NULL) {
            temp = temp->arnext;
        }
        temp->arnext = anewuser;
    }

    printf("\t\tAdmin registered successfully.\n");
}

int alogin(areg *alhead) {
    printf("\n\n-----------------------login for admin ------------------------------\n");
    int auser;
    char ap[100];
    if (alhead == NULL) {
        printf("\t\tNo users registered yet. Please register first.\n\n");
        return 0;
    } else {
        printf("\t\tEnter  User ID: ");
        scanf("%d", &auser);
        getchar(); // Clear the newline character from the buffer

        printf("\t\tEnter Password: ");
        scanf("%s", ap);

        areg *atemp = alhead;
        while (atemp != NULL) {
            if (atemp->aid == auser && strcmp(atemp->apass, ap) == 0) {
                printf("\t\tAdmin Found. Logged In.\n\n");
                return 1;
            } else {
                atemp = atemp->arnext;
            }
        }
        printf("\t\tAdmin ID or password is incorrect.\n\n");
        return 0;
    }
}

void admin() {
    int choice;
    int value;
    int choice1;
printf("\n\n---------------------------welcome to admin panel--------------------------\n");
    printf("\t\t(1)Register\n");
    printf("\t\t(2)Login\n");
    printf("\t\t(3)Exit\n");
    printf("\t\t(4)Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            aregistration();
            break;
        case 2:
            value = alogin(arhead);
            if (value == 1) {
                printf("\t\tChoose your activities:\n");
                printf("\t\t1.Add Bus\n");
                
                printf("\t\t2.Add Driver\n");
                printf("\t\t3.Display Bus Routes\n");
                printf("\t\t4.Exit\n");
                printf("\t\t Enter your choice: ");
                scanf("%d", &choice1);

                switch (choice1) {
                    case 1:
                       add_bus_route();
                       break;
                    case 2:
                        add_driver();
                        break;
                    case 3:
                        displayBusRoutes();
                        break;
                    case 4:
                        printf("Exiting...\n");
                        // Free allocated memory before exiting
                        freeMemory();
                        exit(0);
                    default:
                        printf("\t\tInvalid choice. Please try again.\n");
                }
            }
            break;
        case 3:
            printf("Exiting...\n");
            
            freeMemory();
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
    }
}


void user() {
    int choice;
    int value;
    int choice1;
printf("\n\n---------------------------welcome to user panel--------------------------\n");
    printf("\t\t (1)Register\n");
    printf("\t\t (2)Login\n");
    printf("\t\t (3)Exit\n");
    printf("\t\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            uregistration();
            break;
        case 2:
            value = ulogin(urhead);
            if (value == 1) {
                printf("Choose your activities:\n");
                printf("\t\t (1)View Bus\n");
                printf("\t\t (2)Load Balance\n");
                printf("\t\t (3)Buy Ticket\n");
                printf("\t\t (4)Exit\n");
                printf("\t\tEnter your choice: ");
                scanf("%d", &choice1);

                switch (choice1) {
                    case 1:
                        displayBusRoutes();
                        break;
                    case 2:
                        loadCardBalance();
                        break;
                    case 3:
                        buyTicket();  // Call the buyTicket function
                        break;
                    case 4:
                        printf("Exiting...\n");
                        // Free allocated memory before exiting
                        freeMemory();
                        exit(0);
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            }
            break;
        case 3:
            printf("Exiting...\n");
            
            freeMemory();
            exit(0);
        default:
            printf("\t\tInvalid choice. Please try again.\n");
    }
}

                        
// aboutProject funtion defination
void about_project()
{
  printf("\n\n");
  FILE *fp = NULL;
  char ch;
  fp = fopen("text.txt", "r");
  while (!feof(fp))
  {
    ch = fgetc(fp);
    printf("%c", ch);
  }

  fclose(fp);

  printf("\n\n-----------------------------------------------------\n");
  printf("\t\t1. choice panel for admin and user \n");
  printf("\t\t2. Exit\n");

  int choice;
  printf("pree 1 back to home  and 2 for exit: ");
  scanf("%d", &choice);

  if (choice == 1)
  {
    main();
  }
  else
  {
    exit(0);
  }
}







void freememory(){
free(dhead);
free(bushead);
free(urhead); 
free(arhead);



}