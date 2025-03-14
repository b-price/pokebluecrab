.set LOCALID_RIVAL, 3

Route3_MapScripts::
map_script MAP_SCRIPT_ON_TRANSITION, Route3_OnTransition
	.byte 0
	
Route3_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call ProfBirch_EventScript_UpdateLocation
	end
	
Route3_EventScript_Rival::
	lockall
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route3_EventScript_RivalMay
	goto_if_eq VAR_RESULT, FEMALE, Route3_EventScript_RivalBrendan
	end
	
Route3_EventScript_RivalMay::
	msgbox Route3_Text_MayRoute3Pokemon, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_MAY, TRUE
	applymovement LOCALID_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	msgbox Route3_Text_MayLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route3_EventScript_StartMayBattleTurtwig
	case 1, Route3_EventScript_StartMayBattleTorchic
	case 2, Route3_EventScript_StartMayBattleSquirtle
	end

Route3_EventScript_RivalBrendan::
	msgbox Route3_Text_BrendanRoute3Pokemon, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	applymovement LOCALID_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	msgbox Route3_Text_BrendanLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route3_EventScript_StartBrendanBattleTurtwig
	case 1, Route3_EventScript_StartBrendanBattleTorchic
	case 2, Route3_EventScript_StartBrendanBattleSquirtle
	end

Route3_EventScript_StartMayBattleTurtwig::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TREECKO, Route3_Text_MayDefeated
	goto Route3_EventScript_AfterMayBattle
	end

Route3_EventScript_StartMayBattleTorchic::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TORCHIC, Route3_Text_MayDefeated
	goto Route3_EventScript_AfterMayBattle
	end

Route3_EventScript_StartMayBattleSquirtle::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_MUDKIP, Route3_Text_MayDefeated
	goto Route3_EventScript_AfterMayBattle
	end

Route3_EventScript_StartBrendanBattleTurtwig::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_TREECKO, Route3_Text_BrendanDefeated
	goto Route3_EventScript_AfterBrendanBattle
	end

Route3_EventScript_StartBrendanBattleTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_TORCHIC, Route3_Text_BrendanDefeated
	goto Route3_EventScript_AfterBrendanBattle
	end

Route3_EventScript_StartBrendanBattleSquirtle::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_MUDKIP, Route3_Text_BrendanDefeated
	goto Route3_EventScript_AfterBrendanBattle
	end

Route3_EventScript_AfterMayBattle::
	msgbox Route3_Text_MayTimeToHeadBack, MSGBOX_DEFAULT
	goto Route3_EventScript_RivalExit
	end

Route3_EventScript_AfterBrendanBattle::
	msgbox Route3_Text_BrendanTimeToHeadBack, MSGBOX_DEFAULT
	goto Route3_EventScript_RivalExit
	end

Route3_EventScript_RivalExit::
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, Route3_EventScript_RivalExitFacingSouth
	case DIR_NORTH, Route3_EventScript_RivalExitFacingNorth
	case DIR_WEST, Route3_EventScript_RivalExitFacingEastOrWest
	case DIR_EAST, Route3_EventScript_RivalExitFacingEastOrWest
	end

Route3_EventScript_RivalExitFacingNorth::
	applymovement OBJ_EVENT_ID_PLAYER, Route3_Movement_WatchRivalExitFacingNorth
	applymovement LOCALID_RIVAL, Route3_Movement_RivalExitFacingNorth
	waitmovement 0
	goto Route3_EventScript_RivalEnd
	end

Route3_EventScript_RivalExitFacingEastOrWest::
	applymovement OBJ_EVENT_ID_PLAYER, Route3_Movement_WatchRivalExitFacingEastOrWest
	applymovement LOCALID_RIVAL, Route3_Movement_RivalExit
	waitmovement 0
	goto Route3_EventScript_RivalEnd
	end

Route3_EventScript_RivalExitFacingSouth::
	applymovement LOCALID_RIVAL, Route3_Movement_RivalExit
	waitmovement 0
	goto Route3_EventScript_RivalEnd
	end

Route3_EventScript_RivalEnd::
	removeobject LOCALID_RIVAL
	setvar VAR_BIRCH_LAB_STATE, 4
	clearflag FLAG_HIDE_ARNOLD_LAB_RIVAL
	setflag FLAG_DEFEATED_RIVAL_ROUTE103
	setvar VAR_SEVERNA_PARK_RIVAL_STATE, 1
	clearflag FLAG_HIDE_SEVERNA_PARK_RIVAL
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

Route3_Movement_RivalExitFacingNorth:
	walk_left
	walk_down
    walk_down
	walk_down
	walk_down
	walk_down
	walk_down
    walk_down
	step_end

Route3_Movement_WatchRivalExitFacingNorth:
	delay_16
	delay_4
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

Route3_Movement_RivalExit:
	walk_down
	walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
	step_end

Route3_Movement_WatchRivalExitFacingEastOrWest:
	delay_16
	walk_in_place_faster_down
	step_end

Route3_EventScript_Slowpoke::
    lock
    faceplayer
    waitse
    playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
    msgbox Route3_Text_Slowpoke, MSGBOX_DEFAULT
    waitmoncry
    release
    end

Route3_EventScript_Slowbro::
    lock
    faceplayer
    waitse
    playmoncry SPECIES_SLOWBRO, CRY_MODE_NORMAL
    msgbox Route3_Text_Slowbro, MSGBOX_DEFAULT
    waitmoncry
    release
    end
    
Route3_Text_MayRoute3Pokemon:
	.string "MAY: Let's see… The POKéMON found\n"
	.string "on ROUTE 3 include…$"

Route3_Text_MayLetsBattle:
	.string "Oh, hi, {PLAYER}{KUN}!\p"
	.string "…Oh, I see, my dad gave you\n"
	.string "a POKéMON as a gift.\p"
	.string "Since we're here, let's have a quick\n"
	.string "battle!\p"
	.string "I'll give you a taste of what being\n"
	.string "a TRAINER is like.$"

Route3_Text_MayDefeated:
	.string "Wow! That's great!\n"
	.string "{PLAYER}{KUN}, you're pretty good!$"

Route3_Text_MayTimeToHeadBack:
	.string "MAY: I think I know why my dad has\n"
	.string "an eye out for you now.\p"
	.string "I mean, you just got that POKéMON,\n"
	.string "but it already likes you.\p"
	.string "You might be able to befriend any\n"
	.string "kind of POKéMON easily.\p"
	.string "Well, it's time to head back to\n"
	.string "the LAB.$"

Route3_Text_BrendanRoute3Pokemon:
	.string "BRENDAN: Okay, so it's this one and\n"
	.string "that one that live on ROUTE 3…$"

Route3_Text_BrendanLetsBattle:
	.string "Hey, it's {PLAYER}!\p"
	.string "…Oh, yeah, Dad gave you a POKéMON.\p"
	.string "Since we're here, how about a little\n"
	.string "battle?\p"
	.string "I'll teach you what being a TRAINER's\n"
	.string "about!$"

Route3_Text_BrendanDefeated:
	.string "Huh, {PLAYER}, you're not too shabby.$"

Route3_Text_BrendanTimeToHeadBack:
	.string "BRENDAN: I think I get it.\n"
	.string "I think I know why my dad has his eye\l"
	.string "out for you now.\p"
	.string "Look, your POKéMON already likes you,\n"
	.string "even though you just got it.\p"
	.string "{PLAYER}, I get the feeling that you\n"
	.string "could befriend any POKéMON with ease.\p"
	.string "We should head back to the LAB.$"

Route3_Text_Slowpoke:
    .string "SLOWPOKE: …\p"
    .string "…\p"
    .string "…\p"
    .string "Yarah?$"

Route3_Text_Slowbro:
    .string "SLOWBRO: …\p"
    .string "…\p"
    .string "Yawn…$"
