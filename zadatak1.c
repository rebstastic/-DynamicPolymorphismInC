#include<stdio.h>
#include<stdlib.h>

typedef const char* (*funptr)();

/* ============================================================
		ANIMAL
   ============================================================ */
typedef struct {
	funptr* vtable;
	char* name;
} Animal;
void animalPrintGreeting(Animal* obj) {
	printf("%s pozdravlja: %s\n", obj->name, obj->vtable[0]());
}
void animalPrintMenu(Animal* obj) {
	printf("%s voli: %s\n", obj->name, obj->vtable[1]());
}

/* ============================================================
		DOG
   ============================================================ */
typedef struct {
	funptr* vtable;
	char* name;
} Dog;
char const* dogGreet(void){
  return "vau!";
}
char const* dogMenu(void){
  return "kuhanu govedinu";
}
funptr DogVTable[2] = {
	dogGreet,
	dogMenu
};
void DogInit(Dog *obj, char* name) {
	obj->vtable = DogVTable;
	obj->name = name;
}
Animal* createDog(char* name) {
	Animal* dog = (Animal*)malloc(sizeof(Dog));
	DogInit((Dog*) dog, name);
	return dog;
}

/* ============================================================
		CAT
   ============================================================ */
typedef struct {
	funptr* vtable;
	char* name;
} Cat;
char const* catGreet(void){
  return "mijau!";
}
char const* catMenu(void){
  return "konzerviranu tunjevinu";
}
funptr CatVTable[2] = {
	catGreet,
	catMenu
};
void CatInit(Cat *obj, char* name) {
	obj->vtable = CatVTable;
	obj->name = name;
}
Animal* createCat(char* name) {
	Animal* cat = (Animal*)malloc(sizeof(Cat));
	CatInit((Cat*)cat, name);
	return cat;
}

/* ============================================================
		Program
   ============================================================ */
void testAnimals(){
  Animal* p1 = createDog("Hamlet");
  Animal* p2 = createCat("Ofelija");
  Animal* p3 = createDog("Polonije");

  animalPrintGreeting(p1);
  animalPrintGreeting(p2);
  animalPrintGreeting(p3);

  animalPrintMenu(p1);
  animalPrintMenu(p2);
  animalPrintMenu(p3);

  free(p1); free(p2); free(p3);
}
int main() {
	testAnimals();
	getchar();
	return 0;
}