SevernaPark_Mart_MapScripts::
	.byte 0

SevernaPark_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_ADVENTURE_STARTED, SevernaPark_Mart_ExpandedItems
	pokemart SevernaPark_Mart_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SevernaPark_Mart_Pokemart_Basic:
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	pokemartlistend

SevernaPark_Mart_ExpandedItems::
	pokemart SevernaPark_Mart_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SevernaPark_Mart_Pokemart_Expanded:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	pokemartlistend

SevernaPark_Mart_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, SevernaPark_Mart_EventScript_PokeBallsInStock
	msgbox SevernaPark_Mart_Text_PokeBallsAreSoldOut, MSGBOX_DEFAULT
	release
	end

SevernaPark_Mart_EventScript_PokeBallsInStock::
	msgbox SevernaPark_Mart_Text_ImGoingToBuyPokeBalls, MSGBOX_DEFAULT
	release
	end

SevernaPark_Mart_EventScript_Boy::
	msgbox SevernaPark_Mart_Text_RestoreHPWithPotion, MSGBOX_NPC
	end

SevernaPark_Mart_Text_PokeBallsAreSoldOut:
	.string "The clerk says they're all sold out.\n"
	.string "I can't buy any POKé BALLS.$"

SevernaPark_Mart_Text_ImGoingToBuyPokeBalls:
	.string "I'm going to buy a bunch of POKé BALLS\n"
	.string "and catch a bunch of POKéMON!$"

SevernaPark_Mart_Text_RestoreHPWithPotion:
	.string "If a POKéMON gets hurt and loses its HP\n"
	.string "and faints, it won't be able to battle.\p"
	.string "To prevent your POKéMON from fainting,\n"
	.string "restore its HP with a POTION.$"

