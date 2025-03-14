.set LOCALID_RIVAL, 1

Arnold_RivalsHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Arnold_RivalsHouse_2F_OnTransition
	.byte 0

Arnold_RivalsHouse_2F_OnTransition:
    call Common_EventScript_SetupRivalGfxId
	call_if_lt VAR_ARNOLD_RIVAL_STATE, 2, Arnold_RivalsHouse_2F_EventScript_SetReadyToMeetRival
	call_if_ge VAR_ARNOLD_RIVAL_STATE, 3, Arnold_RivalsHouse_2F_EventScript_CheckShouldUpdateRivalPos
	end

Arnold_RivalsHouse_2F_EventScript_CheckShouldUpdateRivalPos::
	goto_if_set FLAG_MET_RIVAL_LILYCOVE, Arnold_RivalsHouse_2F_EventScript_TryUpdateRivalPos
	goto_if_ge VAR_BIRCH_LAB_STATE, 2, Arnold_RivalsHouse_2F_EventScript_Ret
	goto Arnold_RivalsHouse_2F_EventScript_TryUpdateRivalPos

Arnold_RivalsHouse_2F_EventScript_TryUpdateRivalPos::
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, Arnold_RivalsHouse_2F_EventScript_Ret
	setobjectxyperm LOCALID_RIVAL, 8, 2
	setobjectmovementtype LOCALID_RIVAL, MOVEMENT_TYPE_FACE_UP
	return

Arnold_RivalsHouse_2F_EventScript_Ret::
	return

Arnold_RivalsHouse_2F_EventScript_SetReadyToMeetRival::
	setvar VAR_ARNOLD_RIVAL_STATE, 2
	return

Arnold_RivalsHouse_2F_EventScript_RivalsPokeBall::
	lockall
	goto_if_eq VAR_ARNOLD_RIVAL_STATE, 2, Arnold_RivalsHouse_2F_EventScript_MeetRival
	msgbox Arnold_RivalsHouse_2F_Text_ItsRivalsPokeBall, MSGBOX_DEFAULT
	releaseall
	end

Arnold_RivalsHouse_2F_EventScript_MeetRival::
	delay 10
	addobject LOCALID_RIVAL
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_2F_Movement_RivalEnters
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	delay 10
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Arnold_RivalsHouse_2F_EventScript_MayMusic
	call_if_eq VAR_RESULT, FEMALE, Arnold_RivalsHouse_2F_EventScript_BrendanMusic
	call_if_eq VAR_FACING, DIR_NORTH, Arnold_RivalsHouse_2F_EventScript_MeetRivalNorth
	call_if_eq VAR_FACING, DIR_SOUTH, Arnold_RivalsHouse_2F_EventScript_MeetRivalSouth
	call_if_eq VAR_FACING, DIR_WEST, Arnold_RivalsHouse_2F_EventScript_MeetRivalWest
	call_if_eq VAR_FACING, DIR_EAST, Arnold_RivalsHouse_2F_EventScript_MeetRivalEast
	setvar VAR_ARNOLD_RIVAL_STATE, 3
	setflag FLAG_HIDE_ARNOLD_RIVALS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_ARNOLD_RIVALS_HOUSE_RIVAL_BEDROOM
	setvar VAR_ARNOLD_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

Arnold_RivalsHouse_2F_EventScript_MeetRivalNorth::
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_2F_Movement_RivalApproachPlayerNorth
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Arnold_RivalsHouse_2F_EventScript_MayDialogue
	call_if_eq VAR_RESULT, FEMALE, Arnold_RivalsHouse_2F_EventScript_BrendanDialogue
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_RivalsHouse_2F_Movement_PlayerWatchRivalNorth
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_2F_Movement_RivalWalkToPCNorth
	waitmovement 0
	return

Arnold_RivalsHouse_2F_EventScript_MeetRivalSouth::
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_2F_Movement_RivalApproachPlayerSouth
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	checkplayergender
    call_if_eq VAR_RESULT, MALE, Arnold_RivalsHouse_2F_EventScript_MayDialogue
    call_if_eq VAR_RESULT, FEMALE, Arnold_RivalsHouse_2F_EventScript_BrendanDialogue
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_RivalsHouse_2F_Movement_PlayerWatchRivalSouth
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_2F_Movement_RivalWalkToPCSouth
	waitmovement 0
	return

Arnold_RivalsHouse_2F_EventScript_MeetRivalWest::
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_2F_Movement_RivalApproachPlayerWest
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	checkplayergender
    call_if_eq VAR_RESULT, MALE, Arnold_RivalsHouse_2F_EventScript_MayDialogue
    call_if_eq VAR_RESULT, FEMALE, Arnold_RivalsHouse_2F_EventScript_BrendanDialogue
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_2F_Movement_RivalWalkToPCWest
	waitmovement 0
	return

Arnold_RivalsHouse_2F_EventScript_MeetRivalEast::
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_2F_Movement_RivalApproachPlayerEast
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	checkplayergender
    call_if_eq VAR_RESULT, MALE, Arnold_RivalsHouse_2F_EventScript_MayDialogue
    call_if_eq VAR_RESULT, FEMALE, Arnold_RivalsHouse_2F_EventScript_BrendanDialogue
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_RivalsHouse_2F_Movement_PlayerWatchRivalEast
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_2F_Movement_RivalWalkToPCEast
	waitmovement 0
	return
	
Arnold_RivalsHouse_2F_EventScript_MayDialogue:
    msgbox Arnold_RivalsHouse_2F_Text_MayWhoAreYou, MSGBOX_DEFAULT
    closemessage
    return
    
Arnold_RivalsHouse_2F_EventScript_BrendanDialogue:
    msgbox Arnold_RivalsHouse_2F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
    closemessage
    return

Arnold_RivalsHouse_2F_EventScript_MayMusic:
    playbgm MUS_ENCOUNTER_MAY, TRUE
    return
    
Arnold_RivalsHouse_2F_EventScript_BrendanMusic:
    playbgm MUS_ENCOUNTER_BRENDAN, TRUE
    return

Arnold_RivalsHouse_2F_Movement_RivalEnters:
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

Arnold_RivalsHouse_2F_Movement_RivalApproachPlayerNorth:
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	step_end

Arnold_RivalsHouse_2F_Movement_RivalWalkToPCNorth:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

Arnold_RivalsHouse_2F_Movement_PlayerWatchRivalNorth:
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_right
	step_end

Arnold_RivalsHouse_2F_Movement_RivalApproachPlayerSouth:
	walk_right
	walk_right
	walk_right
	step_end

Arnold_RivalsHouse_2F_Movement_RivalWalkToPCSouth:
	walk_up
	walk_in_place_faster_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

Arnold_RivalsHouse_2F_Movement_PlayerWatchRivalSouth:
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	walk_in_place_faster_right
	step_end

Arnold_RivalsHouse_2F_Movement_RivalApproachPlayerWest:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_down
	step_end

Arnold_RivalsHouse_2F_Movement_RivalWalkToPCWest:
	walk_up
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

@ Unused, the player is already facing this direction so its unneeded
Arnold_RivalsHouse_2F_Movement_PlayerWatchRivalWest:
	delay_16
	delay_16
	walk_in_place_faster_right
	step_end

Arnold_RivalsHouse_2F_Movement_RivalApproachPlayerEast:
	walk_right
	walk_right
	walk_down
	walk_in_place_faster_right
	step_end

Arnold_RivalsHouse_2F_Movement_RivalWalkToPCEast:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

Arnold_RivalsHouse_2F_Movement_PlayerWatchRivalEast:
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	walk_in_place_faster_right
	step_end

Arnold_RivalsHouse_2F_EventScript_Rival::
	lockall
	goto_if_set FLAG_MET_RIVAL_LILYCOVE, Arnold_RivalsHouse_2F_EventScript_RivalPostLilycove
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Arnold_RivalsHouse_2F_EventScript_May
	goto_if_eq VAR_RESULT, FEMALE, Arnold_RivalsHouse_2F_EventScript_Brendan
	end

Arnold_RivalsHouse_2F_EventScript_May::
	msgbox Arnold_RivalsHouse_2F_Text_MayGettingReady, MSGBOX_DEFAULT
	releaseall
	end

Arnold_RivalsHouse_2F_EventScript_Brendan::
	msgbox Arnold_RivalsHouse_2F_Text_BrendanGettingReady, MSGBOX_DEFAULT
	releaseall
	end

Arnold_RivalsHouse_2F_EventScript_RivalPostLilycove::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Arnold_RivalsHouse_2F_EventScript_MayPostLilycove
	call_if_eq VAR_RESULT, FEMALE, Arnold_RivalsHouse_2F_EventScript_BrendanPostLilycove
	setflag FLAG_MET_RIVAL_IN_HOUSE_AFTER_LILYCOVE
	releaseall
	end

Arnold_RivalsHouse_2F_EventScript_MayPostLilycove::
	goto_if_set FLAG_MET_RIVAL_IN_HOUSE_AFTER_LILYCOVE, Arnold_RivalsHouse_2F_EventScript_MayWhereShouldIGoNext
	msgbox Arnold_RivalsHouse_2F_Text_MayJustCheckingMyPokedex, MSGBOX_DEFAULT
	return

Arnold_RivalsHouse_2F_EventScript_BrendanPostLilycove::
	goto_if_set FLAG_MET_RIVAL_IN_HOUSE_AFTER_LILYCOVE, Arnold_RivalsHouse_2F_EventScript_BrendanWhereShouldIGoNext
	msgbox Arnold_RivalsHouse_2F_Text_BrendanJustCheckingMyPokedex, MSGBOX_DEFAULT
	return

Arnold_RivalsHouse_2F_EventScript_MayWhereShouldIGoNext::
	msgbox Arnold_RivalsHouse_2F_Text_MayWhereShouldIGoNext, MSGBOX_DEFAULT
	return

Arnold_RivalsHouse_2F_EventScript_BrendanWhereShouldIGoNext::
	msgbox Arnold_RivalsHouse_2F_Text_BrendanWhereShouldIGoNext, MSGBOX_DEFAULT
	return

Arnold_RivalsHouse_2F_EventScript_CheckRivalsPC::
	lockall
	msgbox gText_PokemonTrainerSchoolEmail, MSGBOX_DEFAULT
	releaseall
	end

Arnold_RivalsHouse_2F_Text_MayWhoAreYou:
	.string "Huh?\n"
	.string "Who… Who are you?\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "Oh, you're {PLAYER}{KUN}.\n"
	.string "So your move was today.\p"
	.string "Um… I'm MAY.\n"
	.string "Glad to meet you!\p"
	.string "I…\n"
	.string "I have this dream of becoming friends\l"
	.string "with POKéMON all over the world.\p"
	.string "I… I heard about you, {PLAYER}{KUN}, from\n"
	.string "my dad, PROF. BIRCH.\p"
	.string "I was hoping that you would be nice,\n"
	.string "{PLAYER}{KUN}, and that we could be friends.\p"
	.string "Oh, this is silly, isn't it?\n"
	.string "I… I've just met you, {PLAYER}{KUN}.\p"
	.string "Eheheh…\p"
	.string "Oh, no! I forgot!\p"
	.string "I was supposed to go help Dad catch\n"
	.string "some wild POKéMON!\p"
	.string "{PLAYER}{KUN}, I'll catch you later!$"

Arnold_RivalsHouse_2F_Text_MayGettingReady:
	.string "POKéMON fully restored!\n"
	.string "Items ready, and…$"

Arnold_RivalsHouse_2F_Text_BrendanWhoAreYou:
	.string "Hey!\n"
	.string "You…\p"
	.string "Who are you?\p"
	.string "Oh, you're {PLAYER}, aren't you?\n"
	.string "Moved in next door, right?\p"
	.string "I didn't know that you're a girl.\p"
	.string "Dad, PROF. BIRCH, said that our new\n"
	.string "next-door neighbor is a GYM LEADER's\l"
	.string "kid, so I assumed you'd be a guy.\p"
	.string "My name's BRENDAN.\n"
	.string "So, hi, neighbor!\p"
	.string "Huh? Hey, {PLAYER}, don't you have\n"
	.string "a POKéMON?\p"
	.string "Do you want me to go catch you one?\p"
	.string "Aw, darn, I forgot…\p"
	.string "I'm supposed to go help my dad catch\n"
	.string "some wild POKéMON.\p"
	.string "Some other time, okay?$"

Arnold_RivalsHouse_2F_Text_BrendanGettingReady:
	.string "POKéMON fully restored…\n"
	.string "Items all packed, and…$"

Arnold_RivalsHouse_2F_Text_ItsRivalsPokeBall:
	.string "It's {RIVAL}'s POKé BALL!\p"
	.string "Better leave it right where it is.$"

Arnold_RivalsHouse_2F_Text_MayJustCheckingMyPokedex:
	.string "MAY: {PLAYER}{KUN}!\p"
	.string "I was just checking my POKéDEX.\p"
	.string "There's still a lot of POKéMON that\n"
	.string "I've seen but haven't caught.\p"
	.string "And there are many others that\n"
	.string "I think will evolve.\p"
	.string "I wonder where I should go catch\n"
	.string "some POKéMON next?$"

Arnold_RivalsHouse_2F_Text_MayWhereShouldIGoNext:
	.string "MAY: I wonder where I should go catch\n"
	.string "some POKéMON next?\p"
	.string "Wouldn't it be funny if we ran into each\n"
	.string "other, {PLAYER}{KUN}?$"

Arnold_RivalsHouse_2F_Text_BrendanJustCheckingMyPokedex:
	.string "BRENDAN: Hey, it's {PLAYER}.\p"
	.string "I was just checking out my POKéDEX.\p"
	.string "There are still many POKéMON that\n"
	.string "I need to catch, I know, but this\l"
	.string "is looking pretty good.\p"
	.string "Checking this POKéDEX out gives me\n"
	.string "the urge to hit the road again.$"

Arnold_RivalsHouse_2F_Text_BrendanWhereShouldIGoNext:
	.string "BRENDAN: I'm having a hard time deciding\n"
	.string "where I should catch POKéMON next.\p"
	.string "Hey, {PLAYER}, if I see you while I'm out\n"
	.string "catching POKéMON, I can pitch you a\l"
	.string "battle if you'd like.$"
