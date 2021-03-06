Land* getLandWithCord(Map *, Cord *);

Land* createLand () {
	Land *l = (Land *) malloc(sizeof(Land));
	l->items = (ListItems *) malloc(sizeof(ListItems));
	(*l->items) = NULL;
	l->character = NULL;
	l->effect = none;
	
	return l;
}

void addItemsToLandList (Land *land, ItemNode *newNode) {
	ItemNode *landAux = (*land->items);

	if (landAux != NULL) {

		if (strcmp(landAux->item->name, newNode->item->name) > 0) {
			// Comparación con el primer elemento para ver si se inserta al inicio

			newNode->next = landAux->next;
			landAux->next = newNode;

		} else {
			// Comparación con el resto de elementos

			while (landAux->next != NULL && strcmp(landAux->item->name, newNode->item->name) > 0)
				landAux = landAux->next;

			newNode->next = landAux->next;
			landAux->next = newNode;
		}
	} else {

		// La lista está vacía
		newNode->next = (*land->items);
		(*land->items) = newNode;
		
	}
}

// Pre: itemNode must be in land->items
void deleteFromLandListItems(Land *land, ItemNode *itemNode, unsigned short isFirst) {

	switch (isFirst) {
		case 1:
			(*land->items) = (*land->items)->next;
			break;
			
		default:
			itemNode->next = itemNode->next->next;
			break;
	}
}

unsigned short isFree (Map *map, Cord *cord) {

	return map->cols[cord->col - ASCII_A]->lands[cord->row]->character == NULL;
}

void seeLand (Map *map, Cord *cord) {
  Land *land = getLandWithCord(map, cord);
  Character *C = land->character;

  printf("\nDetalles del Terreno (%hu, %c)\n\n", cord->row + 1, cord->col);

  printf("Personaje\n");
  printf("_________\n\n");
  showCharacterDetails(map, C);

  printf("Items\n");
  printf("_____\n\n");
  printItems((*land->items), 1);

  printf("Efectos\n");
  printf("_______\n\n");
  printEffect(land->effect);
}