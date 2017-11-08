# Zork

## Description
A C++ project to emulate Zork, a text-based video game.

## Commands
n, s, e, w - movement controls.
i - lists the player's inventory.
take (item) - changes item ownership from the original to the player's
     	      inventory.
open (container) - lists the items in the container, making them available for
     		   pickup.
read (item) - prints what is written on an object.
drop (item) - drops an item from the player's inventory to the room.
put (item) in (container) - moves an item from the player's inventory to the
    	      		    specified container.
turn on (item) - activates an item, if it is in the player's inventory.
>attack (creature) with (item) - attemps to attack a creature with an item in
		   	       	 the player's inventory.

##Objects

### Map
The entire game map. Contains different rooms linked together by their borders.

### Room
A specific room. Contains its borders, containers, items, creatures and
triggers.

### Container
A container (think of a chest). Contains items and triggers. In some cases,
can only accept certain items.

### Creature
Contains certain stats determining the toughness of the creature, as well as
vulnerabilities and triggers.

### Triggers
This is a special kind of object. It contains conditions, and upon those
conditions being satisfied, the actions of this trigger will execute. Triggers
contain references to their owners.
