.set LOCALID_MART_EMPLOYEE, 1
.set LOCALID_RIVAL, 3

SevernaPark_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SevernaPark_OnTransition
	.byte 0

SevernaPark_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	setflag FLAG_VISITED_SEVERNA_PARK
	call_if_unset FLAG_RECEIVED_POTION_SEVERNA_PARK, SevernaPark_EventScript_MoveMartEmployee
	call_if_set FLAG_ADVENTURE_STARTED, SevernaPark_EventScript_SetSevernaParkState
	end

@ This script seems pointless because nothing uses VAR_SEVERNA_PARK_STATE
SevernaPark_EventScript_SetSevernaParkState::
	setvar VAR_SEVERNA_PARK_STATE, 1
	return

SevernaPark_EventScript_MoveMartEmployee::
	setobjectxyperm LOCALID_MART_EMPLOYEE, 25, 7
	setobjectmovementtype LOCALID_MART_EMPLOYEE, MOVEMENT_TYPE_FACE_DOWN
	return

SevernaPark_EventScript_TownSign::
	msgbox SevernaPark_Text_TownSign, MSGBOX_SIGN
	end

SevernaPark_EventScript_Fisherman::
	msgbox SevernaPark_Text_SevernFishing, MSGBOX_NPC
	end

SevernaPark_EventScript_MartEmployee::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POTION_SEVERNA_PARK, SevernaPark_EventScript_ExplainPotion
	goto_if_set FLAG_TEMP_1, SevernaPark_EventScript_ExplainPotion
	setflag FLAG_TEMP_1
	playbgm MUS_FOLLOW_ME, FALSE
	msgbox SevernaPark_Text_IWorkAtPokemonMart, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, SevernaPark_EventScript_GoToMartSouth
	case DIR_NORTH, SevernaPark_EventScript_GoToMartNorth
	case DIR_EAST, SevernaPark_EventScript_GoToMartEast
	end

SevernaPark_EventScript_GoToMartSouth::
	applymovement LOCALID_MART_EMPLOYEE, SevernaPark_Movement_EmployeeSouth
	applymovement OBJ_EVENT_ID_PLAYER, SevernaPark_Movement_PlayerSouth
	waitmovement 0
	goto SevernaPark_EventScript_ExplainPokemonMart
	end

SevernaPark_EventScript_GoToMartNorth::
	applymovement LOCALID_MART_EMPLOYEE, SevernaPark_Movement_EmployeeNorth
	applymovement OBJ_EVENT_ID_PLAYER, SevernaPark_Movement_PlayerNorth
	waitmovement 0
	goto SevernaPark_EventScript_ExplainPokemonMart
	end

SevernaPark_EventScript_GoToMartEast::
	applymovement OBJ_EVENT_ID_PLAYER, SevernaPark_Movement_PlayerEast
	applymovement LOCALID_MART_EMPLOYEE, SevernaPark_Movement_EmployeeEast
	waitmovement 0
	goto SevernaPark_EventScript_ExplainPokemonMart
	end

SevernaPark_EventScript_ExplainPokemonMart::
	msgbox SevernaPark_Text_ThisIsAPokemonMart, MSGBOX_DEFAULT
	giveitem ITEM_POTION
	goto_if_eq VAR_RESULT, FALSE, SevernaPark_EventScript_BagIsFull
	msgbox SevernaPark_Text_PotionExplanation, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_POTION_SEVERNA_PARK
	fadedefaultbgm
	release
	end

SevernaPark_EventScript_ExplainPotion::
	msgbox SevernaPark_Text_PotionExplanation, MSGBOX_DEFAULT
	release
	end

SevernaPark_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	fadedefaultbgm
	release
	end

SevernaPark_Movement_EmployeeEast:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_in_place_faster_left
	step_end

SevernaPark_Movement_EmployeeSouth:
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_in_place_faster_left
	step_end

SevernaPark_Movement_EmployeeNorth:
	walk_up
    walk_up
    walk_up
    walk_right
    walk_in_place_faster_left
    step_end

SevernaPark_Movement_PlayerEast:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

SevernaPark_Movement_PlayerSouth:
	delay_16
	delay_16
	delay_16
	delay_16
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

SevernaPark_Movement_PlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

SevernaPark_EventScript_Rival::
	lockall
	applymovement LOCALID_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_0x8009, 0
	goto SevernaPark_EventScript_ShowRivalMessage
	end

SevernaPark_EventScript_RivalTrigger1::
	lockall
	applymovement LOCALID_RIVAL, SevernaPark_Movement_RivalApproachPlayer1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto SevernaPark_EventScript_ShowRivalMessage
	end

SevernaPark_EventScript_RivalTrigger2::
	lockall
	applymovement LOCALID_RIVAL, SevernaPark_Movement_RivalApproachPlayer2
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto SevernaPark_EventScript_ShowRivalMessage
	end

SevernaPark_EventScript_RivalTrigger3::
	lockall
	applymovement LOCALID_RIVAL, SevernaPark_Movement_RivalApproachPlayer3
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto SevernaPark_EventScript_ShowRivalMessage
	end

SevernaPark_EventScript_ShowRivalMessage::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, SevernaPark_EventScript_ShowMayMessage
	goto_if_eq VAR_RESULT, FEMALE, SevernaPark_EventScript_ShowBrendanMessage
	end

SevernaPark_EventScript_ShowMayMessage::
	msgbox SevernaPark_Text_MayLetsGoBack, MSGBOX_DEFAULT
	goto SevernaPark_EventScript_RivalFinish
	end

SevernaPark_EventScript_ShowBrendanMessage::
	msgbox SevernaPark_Text_BrendanLetsGoBack, MSGBOX_DEFAULT
	goto SevernaPark_EventScript_RivalFinish
	end

SevernaPark_EventScript_RivalFinish::
	closemessage
	call_if_eq VAR_0x8009, 0, SevernaPark_EventScript_DoExitMovement1
	call_if_eq VAR_0x8009, 1, SevernaPark_EventScript_DoExitMovement2
	applymovement LOCALID_RIVAL, SevernaPark_Movement_RivalExit
	waitmovement 0
	removeobject LOCALID_RIVAL
	setvar VAR_SEVERNA_PARK_RIVAL_STATE, 2
	setflag FLAG_HIDE_SEVERNA_PARK_RIVAL
	releaseall
	end

SevernaPark_EventScript_DoExitMovement1::
	goto_if_ne VAR_FACING, DIR_SOUTH, SevernaPark_EventScript_DoExitMovement2
	applymovement LOCALID_RIVAL, SevernaPark_Movement_RivalExit
	waitmovement 0
	return

SevernaPark_EventScript_DoExitMovement2::
	applymovement OBJ_EVENT_ID_PLAYER, SevernaPark_Movement_WatchRivalExit
	applymovement LOCALID_RIVAL, SevernaPark_Movement_RivalExit
	waitmovement 0
	return

SevernaPark_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	step_end

SevernaPark_Movement_RivalApproachPlayer2:
	walk_left
	step_end

SevernaPark_Movement_RivalApproachPlayer3:
	face_left
	step_end

SevernaPark_Movement_RivalExit:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
    walk_down
	step_end

SevernaPark_Movement_WatchRivalExit:
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

SevernaPark_Movement_PlayerStepBack:
	delay_8
	walk_right
	step_end

SevernaPark_Movement_BackUp:
	walk_fast_up
	walk_in_place_faster_left
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

SevernaPark_Movement_ReturnToOriginalPosition:
	walk_down
	walk_left
	step_end

SevernaPark_Text_SevernFishing:
	.string "The fishing ain't too great here\n"
	.string "at the Severn River no more.\p"
	.string "Used to be we'd get a ton of KRABBY.\l"
	.string "Now it's just MAGIKARP!$"

SevernaPark_Text_IWorkAtPokemonMart:
	.string "Hi!\n"
	.string "I work at a POKéMON MART.\p"
	.string "Can I get you to come with me?$"

SevernaPark_Text_ThisIsAPokemonMart:
	.string "This is a POKéMON MART.\n"
	.string "Just look for our blue roof.\p"
	.string "We sell a variety of goods including\n"
	.string "POKé BALLS for catching POKéMON.\p"
	.string "Here, I'd like you to have this as\n"
	.string "a promotional item.$"

SevernaPark_Text_PotionExplanation:
	.string "A POTION can be used anytime, so it's\n"
	.string "even more useful than a POKéMON CENTER\l"
	.string "in certain situations.$"

SevernaPark_Text_MayLetsGoBack:
	.string "MAY: {PLAYER}{KUN}!\n"
	.string "Over here!\l"
	.string "Let's hurry home!$"

SevernaPark_Text_BrendanLetsGoBack:
	.string "BRENDAN: I'm heading back to my dad's\n"
	.string "LAB now.\l"
	.string "{PLAYER}, you should hustle back, too.$"

SevernaPark_Text_TownSign:
	.string "SEVERNA PARK\n"
	.string "“Where things start off scarce.”$"


