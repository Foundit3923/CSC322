#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int respect;

typedef struct _Room{
  int number;
  int maxRoom;
  int cleanliness;
  int north;
  int south;
  int east;
  int west;
  int num_Of_Creatures;
  long *currentCreatures;
}room;

typedef struct _Creature{
  int number;
  int type;
  int room;
  int maxCreature;
  int neighbor;
}creature;

typedef struct _PC{
  int currentRoom;
}pc;

room **rooms;
creature **creatures;
pc *pC;

/*void updateCreatures(int num_creatures, int i);
void init();
int findDirtyNeighbor(int savePoint);*/
void move(int direction, int currentCreature, int type);


/*---------------------------------------------------------------------*/

void updateCreatures(int num_creatures, int i){
  printf("UC: Init current creatures\n");
  /*Initialize currentCreatures*/
  rooms[i]->currentCreatures = (long*) malloc(sizeof(long));
  printf("UC: Declare creature count\n");
  /*Assign creature count*/
  int creatureCount = 0;
  for(int j = 0; j < num_creatures; j++){
    printf("UC: for loop\n");
    if(creatures[i]->room == i){
      /*Fill current Creatures*/
      for(int k = 0; k < 10; k++){
        printf("UC: Init current creatures[i]\n");
      rooms[i]->currentCreatures[k] = (long) malloc(sizeof(long));
      printf("UC: Assign current creatures[i]\n");
      rooms[i]->currentCreatures[k] = creatures[j]->room;
    }
    creatureCount++;
    }
  }
  printf("UC: fill num of creatures\n");
  /*Fill num_Of_Creatures*/
  rooms[i]->num_Of_Creatures = creatureCount;
}

/*---------------------------------------------------------------------*/

void init(){
  /*Init respect*/
  respect = 40;

  /*Init global pointer pC*/
  pC = (pc*) malloc(sizeof(pc));

  /*Init input variable to store user input*/
  char *input = (char*) malloc(sizeof(char));

  /*Get number of Rooms*/
  printf("Enter the number of rooms: \n");
  fgets(input, 20, stdin);

  int num_rooms = atoi(input);
  /*Init global pointer rooms*/
  rooms = (room**) malloc(num_rooms * sizeof(room*));

  /*create temp multi array to store room information*/
  char **temp = (char**) malloc(sizeof(char*) * (num_rooms));
  /*Get room information and store in temp*/
    printf("Enter room information: \n");

    for(int i = 0; i < num_rooms; i++)

    {
      fgets(input, 20, stdin);
      temp[i] = (char*) malloc(strlen(input));

        strcpy(temp[i], input);

    }
    /*Get number of creatures*/
    printf("Enter the number of creatures: \n");
    fgets(input, 20, stdin);
    int num_creatures = atoi(input);

    printf("Init global creatures\n");
    /*Init global variable creatures*/
    creatures = (creature**) malloc(num_creatures * sizeof(creature*));


    /*Get creature information and store in creatures*/
    printf("Enter creature information: \n");

    printf("Creature for loop\n");

    for(int i = 0; i < num_creatures; i++)
    {
        printf("Init creatures[i]\n");
        /*Initialize creatures[i]*/
        creatures[i] = (creature*) malloc(sizeof(creature*));
        printf("Assing creatures[i]\n");
        creatures[i]->number = i;
        printf("assign maxcreature\n");
        /*Initialize maxCreature*/
        creatures[i]->maxCreature = num_creatures;

        printf("Get input\n");
        fgets(input, 20, stdin);

        int count = 0;

        char *token;
        const char d[2] = " ";

        /*Get first token*/
        token = strtok(input,d);
        printf("Walk through tokens\n");
        /*Walk through the rest*/
        /*Convert token into int*/
        while( token != NULL ){
          switch(count){
            case 0:
            printf("First token\n");
               creatures[i]->type = atoi(token);
              token = strtok(NULL, d);
              break;
            case 1:
            printf("Second token\n");
              creatures[i]->room = atoi(token);
              token = strtok(NULL, d);
              break;
          }
          count++;
        }
    }

    printf("Store room info\n");
    /*Store room information in rooms*/
    for(int i = 0; i < num_rooms; i++){
      printf("Init rooms[i]\n");
      /*Initialize creatures[i]*/
      rooms[i] = (room*) malloc(sizeof(creature*));
      printf("Assign room number\n");
      /*Assign room number*/
      rooms[i]->number = i;


      int count = 0;

      char *token;
      const char d[2] = " ";
      printf("Get first token\n");
      /*Get first token*/
      token = strtok(temp[i],d);
      printf("Walk through the rest\n");
      /*Walk through the rest*/
      /*Convert token into int*/
      while( token != NULL ){
        switch(count){
          case 0:
          printf("First token\n");
            rooms[i]->cleanliness = atoi(token);
            token = strtok(NULL, d);
            break;
          case 1:
          printf("Second token\n");
            rooms[i]->north = atoi(token);
            token = strtok(NULL, d);
            break;
          case 2:
          printf("Third token\n");
            rooms[i]->south = atoi(token);
            token = strtok(NULL, d);
            break;
          case 3:
          printf("Fourth token\n");
            rooms[i]->east = atoi(token);
            token = strtok(NULL, d);
            break;
          case 4:
          printf("Fifth token\n");
            rooms[i]->west = atoi(token);
            token = strtok(NULL, d);
            break;
        }
        count++;
      }
      printf("Update creatures\n");
      updateCreatures(num_creatures, i);

      /*Fill maxRoom*/
      printf("Fills max room\n");
      rooms[i]->maxRoom = num_rooms;

    }


}

/*--------------------------------------------------------------------*/

int findNeighbor(int type){
/*Declare variable to hold room number of neighbor, called 'neighbor'*/
int neighbor = 0;

int cleanCount = 0;

int dirtyCount = 0;
/*Declare pointer variable to hold directional number of clean neighbors, called '*cleanNeighbors'*/
int *cleanNeighbors;
  /*Initialize 'cleanNeighbors' to size 4*/
  cleanNeighbors = (int*) malloc(sizeof(int) * 4);
  /*Assign -1 to 'cleanNeighbors[0]'*/
  cleanNeighbors[0] = -1;
/*Declare pointer variable to hold directional number of dirty neighbors, called '*dirtyneighbors'*/
int *dirtyNeighbors;
  /*Initialize 'dirtyNeighbors' to size 4*/
  dirtyNeighbors = (int*) malloc(sizeof(int) * 4);
  /*Assign -1 to 'dirtyNeighbors[0]'*/
  dirtyNeighbors[0] = -1;
/*Declare variable to hold a number representing the direction of the available neighbor, called 'result'*/
int result = -1;
/*Declare variable to hold the current room number, called 'currentRoom'*/
int currentRoom = pC->currentRoom;
/*Check each direction for a neighbor*/
  /*Check north*/
  if(rooms[currentRoom]->north != -1){
    /*If there is a neighbor, assign its room number to 'neighbor'*/
    neighbor = rooms[currentRoom]->north;
    /*If that neighbor has room for another creature*/
    if(rooms[neighbor]->num_Of_Creatures < 10){
    /*If clean*/
      if(rooms[neighbor]->cleanliness == 0 || rooms[neighbor]->cleanliness == 1){
        /*Assign directional number to cleanNeighbors[0]*/
        cleanNeighbors[cleanCount] = 0;
        cleanCount++;
      }
      /*If dirty*/
      else{
        /*Assign directinal number to dirtyNeighbors[0]*/
        dirtyNeighbors[dirtyCount] = 0;
        dirtyCount++;
      }
    }
  }
  /*Check south*/
  else if(rooms[currentRoom]->south != -1){
    /*If there is a neighbor, assign its room number to 'neighbor'*/
    neighbor = rooms[currentRoom]->south;
    /*If that neighbor has room for another creature*/
    if(rooms[neighbor]->num_Of_Creatures < 10){
    /*If clean*/
      if(rooms[neighbor]->cleanliness == 0 || rooms[neighbor]->cleanliness == 1){
        /*Assign directional number to cleanNeighbors[0]*/
        cleanNeighbors[cleanCount] = 1;
        cleanCount++;
      }
      /*If dirty*/
      else{
        /*Assign directinal number to dirtyNeighbors[0]*/
        dirtyNeighbors[dirtyCount] = 1;
        dirtyCount++;
      }
    }
  }
  /*Check east*/
  else if(rooms[currentRoom]->east != -1){
    /*If there is a neighbor, assign its room number to 'neighbor'*/
    neighbor = rooms[currentRoom]->east;
    /*If that neighbor has room for another creature*/
    if(rooms[neighbor]->num_Of_Creatures < 10){
    /*If clean*/
      if(rooms[neighbor]->cleanliness == 0 || rooms[neighbor]->cleanliness == 1){
        /*Assign directional number to cleanNeighbors[0]*/
        cleanNeighbors[cleanCount] = 2;
        cleanCount++;
      }
      /*If dirty*/
      else{
        /*Assign directinal number to dirtyNeighbors[0]*/
        dirtyNeighbors[dirtyCount] = 2;
        dirtyCount++;
      }
    }
  }
  /*Check west*/
  else if(rooms[currentRoom]->west != -1){
    /*If there is a neighbor, assign its room number to 'neighbor'*/
    neighbor = rooms[currentRoom]->west;
    /*If that neighbor has room for another creature*/
    if(rooms[neighbor]->num_Of_Creatures < 10){
    /*If clean*/
      if(rooms[neighbor]->cleanliness == 0 || rooms[neighbor]->cleanliness == 1){
        /*Assign directional number to cleanNeighbors[0]*/
        cleanNeighbors[cleanCount] = 3;
        cleanCount++;
      }
      /*If dirty*/
      else{
        /*Assign directinal number to dirtyNeighbors[0]*/
        dirtyNeighbors[dirtyCount] = 3;
        dirtyCount++;
      }
    }
  }
  /*If animal*/
  if(type == 1){
    /*Check for clean neighbors first*/
    if(cleanNeighbors[0] != -1){
      result = cleanNeighbors[0];
    }
    /*Else check for dirty neighbors*/
    else if(dirtyNeighbors[0] != -1){
      result = dirtyNeighbors[0];
    }
  }
  /*If NPC*/
  else if(type == 2){
    if(dirtyNeighbors[0] != -1){
      result = dirtyNeighbors[0];
    }
    else if(cleanNeighbors[0] != -1){
      result = cleanNeighbors[0];
    }
  }
    return result;
  }

/*--------------------------------------------------------------------*/

/*Positive Reaction: creature responds positively to some action*/
void positiveReaction(int creatureNumber, int type, int magnitude){

  /*Check if creature is an animal or NPC*/
  /*If animal*/
  if(type == 1){
    /*If animal is not performing the action*/
    if(magnitude == 0){
      /*Increase respect by 1*/
      respect ++;
      /*Print statement*/
      printf("%d licks your face. Respect is now %d\n", creatureNumber, respect);
    }
    /*If animal is performing the action*/
    else{
      /*Increase respect by 3*/
      respect = respect + 3;
      /*Print statement*/
      printf("%d licks your face a lot. Respect is now %d", creatureNumber, respect);

    }
  }
  /*If NPC*/
  else{
    /*If NPC is not performing action*/
    if(magnitude == 0){
      /*Increase respect by 1*/
      respect ++;
      /*Print statement*/
      printf("%d smiles. Respect is now %d", creatureNumber, respect);
    }
    /*If NPC is performing action*/
    else{
      /*Increase respect by 3*/
      respect = respect + 3;
      /*Print statement*/
      printf("%d smiles a lot. Respect is now %d", creatureNumber, respect);
    }

  }

}

/*----------------------------------------------------------------------*/

/*Negative Reaction: creature responds negatively to some action*/
void negativeReaction(int creatureNumber, int type, int magnitude){
  if(type == 1){
    if(magnitude == 0){
      respect --;
      printf("%d growls. Respect is now %d\n", creatureNumber, respect);
    }
    else{
      respect = respect - 3;
      printf("%d growls a lot. Respect is now %d", creatureNumber, respect);

    }
  }
  else{
    if(magnitude == 0){
      respect --;
      printf("%d grumbles. Respect is now %d", creatureNumber, respect);
    }
    else{
      respect = respect - 3;
      printf("%d grumbles a lot. Respect is now %d", creatureNumber, respect);
    }

  }
}

/*--------------------------------------------------------------------*/

void look(){
  int currentRoom = pC->currentRoom;
  int cleanliness = rooms[currentRoom]->cleanliness;
  int north = rooms[currentRoom]->north;
  int south = rooms[currentRoom]->south;
  int east = rooms[currentRoom]->east;
  int west = rooms[currentRoom]->west;

  printf("Room %d, ",currentRoom);
  if(cleanliness == 0){
    printf("clean, ");
  }
  else if(cleanliness == 1){
    printf("half-dirty, ");
  }
  else{
    printf("dirty, ");
  }
  printf("neighbors ");
  if(north != -1){
    printf("%d to the north ", north);
  }
  if(south != -1){
    printf("%d to the south ", south);
  }
  if(east != -1){
    printf("%d to the east ", east);
  }
  if(west != -1){
    printf("%d to the west ", west);
  }
  printf(", contains: \n");
  printf("PC\n");
  for(int j = 0; j < rooms[currentRoom]->num_Of_Creatures; j++){
      if(creatures[j]->type == 1){

      printf("animal %d\n", creatures[j]->number);
      }
      else if(creatures[j]->type == 2){

        printf("human %d\n", creatures[j]->number);
      }

  }

}

/*---------------------------------------------------------------------*/

/*Increase cleanliness of room by one point*/
void clean(int type, int creatureNumber){
  int currentRoom = pC->currentRoom;

  /*Increase cleanliness if room is not already clean*/
  if(rooms[currentRoom]->cleanliness != 0){

  int currentCreature;
  /*If PC cleans*/
  if(type == -1){
    /*Cycle through all creatures in room*/
    for(int i = 0; i < rooms[currentRoom]->num_Of_Creatures; i++){
      /*Get creature number*/
      currentCreature = rooms[currentRoom]->currentCreatures[i];

      /*If animal: positive reaction. If human: negative reaction*/
      if(creatures[currentCreature]->type == 1){
        positiveReaction(currentCreature, 1, 0);

      }
      else if(creatures[currentCreature]->type == 2){
        negativeReaction(currentCreature, 2, 0);

      }
    }
  }

  /*If animal, or NPC cleans*/
  else{
    /*If animal*/
    if(type == 1){
      positiveReaction(creatureNumber, 1, 1);


      /*Reactions of all other creatures in room*/
      for(int i = 0; i < rooms[currentRoom]->num_Of_Creatures; i++){
        currentCreature = rooms[currentRoom]->currentCreatures[i];
        if(creatureNumber != i){
        if(creatures[currentCreature]->type == 1){
          positiveReaction(currentCreature, 1, 0);

        }
        if(creatures[currentCreature]->type == 2){
          negativeReaction(currentCreature, 2, 0);

        }
      }
    }
  }
    else{
      /*IF NPC*/
      if(creatures[creatureNumber]->type == 2){
        negativeReaction(creatureNumber, 2, 1);


        for(int i = 0; i < rooms[currentRoom]->num_Of_Creatures; i++){
          currentCreature = rooms[currentRoom]->currentCreatures[i];
          if(creatureNumber != i){
          if(creatures[currentCreature]->type == 1){
            positiveReaction(currentCreature, 1, 0);

          }
          if(creatures[currentCreature]->type == 2){
            negativeReaction(currentCreature, 2, 0);

          }
        }
      }

      }
    }
  }

  /*If the room is clean move NPCs*/
  if(rooms[currentRoom]->cleanliness == 0){
    /*Cycle through each creature in the room*/
    for(int j = 0; j < rooms[currentRoom]->num_Of_Creatures; j++){
      currentCreature = rooms[currentRoom]->currentCreatures[j];
      /*If a creature is an NPC, find a neighbor and move to that location*/
      if(creatures[currentCreature]->type == 2){

        /*Initialize neighbor*/
        int neighbor = creatures[currentCreature]->neighbor;
        neighbor = findNeighbor(2);

        /*Identify current creature type*/
        int cType = creatures[currentCreature]->type;

        /*If a correct address has been entered*/
        if(neighbor != 4){
        move(neighbor, currentCreature, cType);
        }
        else{
          creatures[currentCreature] = NULL;
        }

        }
      }
    }
    }
    else{
      printf("The room is already clean\n");
    }
  }

/*---------------------------------------------------------------------*/

void dirty(int type, int creatureNumber){
  int currentRoom = pC->currentRoom;

  /*Increase cleanliness if room is not already clean*/
  if(rooms[currentRoom]->cleanliness != 0){

  int currentCreature;
  /*If PC cleans*/
  if(type == -1){
    /*Cycle through all creatures in room*/
    for(int i = 0; i < rooms[currentRoom]->num_Of_Creatures; i++){
      /*Get creature number*/
      currentCreature = rooms[currentRoom]->currentCreatures[i];

      /*If NPC: positive reaction. If animal: negative reaction*/
      if(creatures[currentCreature]->type == 2){
        positiveReaction(currentCreature, 2, 0);

      }
      else if(creatures[currentCreature]->type == 1){
        negativeReaction(currentCreature, 1, 0);

      }
    }
  }

  /*If animal, or NPC cleans*/
  else{
    /*If NPC*/
    if(type == 2){
      positiveReaction(creatureNumber, 2, 1);


      /*Reactions of all other creatures in room*/
      for(int i = 0; i < rooms[currentRoom]->num_Of_Creatures; i++){
        currentCreature = rooms[currentRoom]->currentCreatures[i];
        if(creatureNumber != i){
        if(creatures[currentCreature]->type == 2){
          positiveReaction(currentCreature, 2, 0);

        }
        if(creatures[currentCreature]->type == 1){
          negativeReaction(currentCreature, 1, 0);

        }
      }
    }
  }
    else{
      /*If animal*/
      if(creatures[creatureNumber]->type == 1){
        negativeReaction(creatureNumber, 1, 1);


        for(int i = 0; i < rooms[currentRoom]->num_Of_Creatures; i++){
          currentCreature = rooms[currentRoom]->currentCreatures[i];
          if(creatureNumber != i){
          if(creatures[currentCreature]->type == 2){
            positiveReaction(currentCreature, 2, 0);

          }
          if(creatures[currentCreature]->type == 1){
            negativeReaction(currentCreature, 1, 0);

          }
        }
      }

      }
    }
  }

  /*If the room is dirty move animals*/
  if(rooms[currentRoom]->cleanliness == 2){
    /*Cycle through each creature in the room*/
    for(int j = 0; j < rooms[currentRoom]->num_Of_Creatures; j++){
      currentCreature = rooms[currentRoom]->currentCreatures[j];
      /*If a creature is an animal, find a neighbor and move to that location*/
      if(creatures[currentCreature]->type == 1){
        /*Initialize neighbor*/
        int neighbor = creatures[currentCreature]->neighbor;
        neighbor = findNeighbor(2);
        /*Identify current creature type*/
        int cType = creatures[currentCreature]->type;
        /*If a correct address has been entered*/
        if(neighbor != -1){
        move(neighbor, currentCreature, cType);
        }
        else{
          creatures[currentCreature] = NULL;
        }
        }
      }
    }
    }
    else{
      printf("The room is already dirty\n");
    }
}

/*---------------------------------------------------------------------*/

void move(int direction, int currentCreature, int type){
  int currentRoom = pC->currentRoom;

  int north = rooms[currentRoom]->north;
  int south = rooms[currentRoom]->south;
  int east = rooms[currentRoom]->east;
  int west = rooms[currentRoom]->west;

  if(type == -1){
    switch(direction){
    case 0:
      if(north != -1){
        printf("You move towads the north\n");
        pC->currentRoom = north;
        break;
      }
      else{
        printf("There is not a room there");
        break;
      }
    case 1:
      if(south != -1){
        printf("You move towads the south");
        pC->currentRoom = south;
        break;
      }
      else{
        printf("There is not a room there");
        break;
      }
    case 2:
      if(east != -1){
        printf("You move towads the east");
        pC->currentRoom = east;
        break;
      }
      else{
        printf("There is not a room there");
        break;
      }
    case 3:
      if(west != -1){
        printf("You move towads the west\n");
        pC-> currentRoom = west;
        break;
      }
      else{
        printf("There is not a room there");
        break;
      }
    default:
      printf("That is not a valid direction");
      break;
  }
  }
  else if(type == 1 || type == 2){
    switch(direction){
    case 0:

        printf("You move towads the north\n");
        creatures[currentCreature]->room = north;
        break;
    case 1:

        printf("You move towads the south");
        creatures[currentCreature]->room = south;
        break;
    case 2:

        printf("You move towads the east");
        creatures[currentCreature]->room = east;
        break;
    case 3:

        printf("You move towads the west\n");
        creatures[currentCreature]->room = west;
        break;
    default:
      printf("That is not a valid direction");
      break;
  }
 }
}

/*---------------------------------------------------------------------*/

int getCommandNumber(char *command){

      /*Return number 0-7 for each command*/
      if(strcmp(command, "look") == 0 || strcmp(command, "Look") == 0){
        return 0;
      }
      else if(strcmp(command, "clean") == 0 || strcmp(command, "Clean") == 0){
        return 1;
      }
      else if(strcmp(command, "dirty") == 0 || strcmp(command, "Dirty") == 0){
        return 2;
      }
      else if(strcmp(command, "north") == 0 || strcmp(command, "North") == 0){
        return 3;
      }
      else if(strcmp(command, "south") == 0 || strcmp(command, "South") == 0){
        return 4;
      }
      else if(strcmp(command, "east") == 0 || strcmp(command, "East") == 0){
        return 5;
      }
      else if(strcmp(command, "west") == 0 || strcmp(command, "West") == 0){
        return 6;
      }
      else{
        return 7;
      }
}

/*---------------------------------------------------------------------*/

void executeCommand(int creatureNumber, int type, int command){
  /*If PC is executing command*/
  if(type == -1 ){

    /*Execute command*/
    switch(command){
    case 0:
      look();
      break;
    case 1:
      clean(type, creatureNumber);
      break;
    case 2:
      dirty(type, creatureNumber);
      break;
    case 3:
      move(command, creatureNumber, type);
      break;
    case 4:
      move(command, creatureNumber, type);
      break;
    case 5:
      move(command, creatureNumber, type);
      break;
    case 6:
      move(command, creatureNumber, type);
      break;
    case 7:
      printf("Invalid submission. Try again.");
      break;
    default:
      printf("Invalid submission. Try again.");
      break;

    }
  }
  /*If creature is executing command*/
  else{

    /*Execute command*/
    switch(command){
      case 0:
        look();
        break;
      case 1:
        clean(type, creatureNumber);
        break;
      case 2:
        dirty(type, creatureNumber);
        break;
      case 3:
        move(command, creatureNumber, type);
        break;
      case 4:
        move(command, creatureNumber, type);
        break;
      case 5:
        move(command, creatureNumber, type);
        break;
      case 6:
        move(command, creatureNumber, type);
        break;
      case 7:
        printf("Invalid submission. Try again.");
        break;
      default:
        printf("Invalid submission. Try again.");
        break;

    }

  }
}

/*---------------------------------------------------------------------*/

void play(){
  /*Randomly assign currentRoom*/
  srand((unsigned)time(NULL));
  pC->currentRoom = rand() % (rooms[0]->maxRoom + 1 - 0) + 0;
  int currentRoom = pC->currentRoom;
/*Create char input, temp, and number*/
  char *input = (char*) malloc(sizeof(char) * 20);
  char *beginningInput;
  char *commandString = (char*) malloc(sizeof(char));
  char number[10];
  int creatureNumber = 0;
  int pcNumber = -1;
  int pcType = -1;
  int creatureType = 0;
  long command = 0;

/*Take input and do instructions*/
/*Check if input is about a creature*/
  while(strcmp(input, "end") != 0){

    printf("Enter a command\n");

    /*scanf input*/
    scanf("%s", input);

    /*if the second character is :*/
    if(input[1] == ':'){
      beginningInput = &input[0];

      /*Extract number from input and initialize creatureNumber with it*/
      creatureNumber = atoi(beginningInput);

      /*Initialize creatureType*/
      creatureType = creatures[creatureNumber]->number;

      /*Initialize char *command*/
      command = (long) malloc(sizeof(long));

      /*Isolate command from input*/
      memcpy(commandString, &input[2], (strlen(input) - 2));

      /*Convert command into number, pass to switch and execute command*/

      command = getCommandNumber(commandString);
      executeCommand(creatureNumber, creatureType, command);

      /*Update creatures in currentRoom*/
      updateCreatures(creatures[0]->maxCreature, currentRoom);
    }

    /*If the third character is :*/
    else if(input[2] == ':'){
      /*Extract number from input and initialize creatureNumber with it*/
      memcpy(number, &input[0], 2);
      creatureNumber = atoi(number);

      /*Initialize creatureType*/
      creatureType = creatures[creatureNumber]->number;

      /*Initialize char *command*/
      command = (long) malloc(sizeof(long));

      /*Isolate command from input*/
      memcpy(commandString, &input[2], (strlen(input) - 2));

      /*Convert command into number, pass to switch and execute command*/

      command = getCommandNumber(commandString);
      executeCommand(creatureNumber, creatureType, command);

      /*Update creatures in currentRoom*/
      updateCreatures(creatures[0]->maxCreature, currentRoom);
    }

    /*If input is not about creature*/
    else{
      command = getCommandNumber(input);
      executeCommand(pcNumber, pcType, command);

      updateCreatures(creatures[0]->maxCreature, currentRoom);
    }
  }
}

/*---------------------------------------------------------------------*/

int main(void){
  init();
  play();
  free(rooms);
  free(creatures);

  return (0);
}
