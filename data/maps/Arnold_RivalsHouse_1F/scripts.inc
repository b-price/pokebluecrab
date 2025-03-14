.set LOCALID_RIVAL_MOM, 1
.set LOCALID_RIVAL, 3

Arnold_RivalsHouse_1F_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Arnold_RivalsHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Arnold_RivalsHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Arnold_RivalsHouse_1F_OnFrame
	.byte 0

Arnold_RivalsHouse_1F_OnTransition::
    call Common_EventScript_SetupRivalGfxId
    end

Arnold_RivalsHouse_1F_OnLoad:
    checkplayergender
    goto_if_eq VAR_RESULT, MALE, Arnold_RivalsHouse_1F_EventScript_RivalSetMale
    goto_if_eq VAR_RESULT, FEMALE, Arnold_RivalsHouse_1F_EventScript_RivalSetFemale
    end

@ Many of the below scripts have no gender check because they assume youre in the correct house
Arnold_RivalsHouse_1F_OnFrame:
	map_script_2 VAR_ARNOLD_HOUSES_STATE, 1, Arnold_RivalsHouse_1F_EventScript_YoureNewNeighbor
	.2byte 0

Arnold_RivalsHouse_1F_Movement_PushTowardStairs:
	walk_up
	step_end

Arnold_RivalsHouse_1F_EventScript_YoureNewNeighbor::
	lockall
	playse SE_PIN
	applymovement LOCALID_RIVAL_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL_MOM, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_RIVAL_MOM, Arnold_RivalsHouse_1F_Movement_RivalMomApproach
	waitmovement 0
	special GetRivalSonDaughterString
	msgbox Arnold_RivalsHouse_1F_Text_OhYoureTheNewNeighbor, MSGBOX_DEFAULT
	setflag FLAG_MET_RIVAL_MOM
	setvar VAR_ARNOLD_HOUSES_STATE, 2
	releaseall
	end

Arnold_RivalsHouse_1F_Movement_RivalMomApproach:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Arnold_RivalsHouse_1F_EventScript_RivalMom::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_RIVAL_ROUTE103, Arnold_RivalsHouse_1F_EventScript_GoHomeEverySoOften
	goto_if_set FLAG_SYS_POKEMON_GET, Arnold_RivalsHouse_1F_EventScript_RivalIsOnRoute103
	goto_if_eq VAR_ARNOLD_RIVAL_STATE, 3, Arnold_RivalsHouse_1F_EventScript_RivalTooBusy
	special GetRivalSonDaughterString
	msgbox Arnold_RivalsHouse_1F_Text_LikeChildLikeFather, MSGBOX_DEFAULT
	release
	end

Arnold_RivalsHouse_1F_EventScript_RivalTooBusy::
	msgbox Arnold_RivalsHouse_1F_Text_TooBusyToNoticeVisit, MSGBOX_DEFAULT
	release
	end

Arnold_RivalsHouse_1F_EventScript_RivalIsOnRoute103::
	msgbox Arnold_RivalsHouse_1F_Text_WentOutToRoute103, MSGBOX_DEFAULT
	release
	end

Arnold_RivalsHouse_1F_EventScript_GoHomeEverySoOften::
	msgbox Arnold_RivalsHouse_1F_Text_ShouldGoHomeEverySoOften, MSGBOX_DEFAULT
	release
	end

Arnold_RivalsHouse_1F_EventScript_RivalSibling::
	lock
	faceplayer
	special GetPlayerBigGuyGirlString
	msgbox Arnold_RivalsHouse_1F_Text_DoYouHavePokemon, MSGBOX_DEFAULT
	release
	end

Arnold_RivalsHouse_1F_EventScript_MeetRival0::
	lockall
	setvar VAR_0x8008, 0
	goto Arnold_RivalsHouse_1F_EventScript_MeetRival
	end

Arnold_RivalsHouse_1F_EventScript_MeetRival1::
	lockall
	setvar VAR_0x8008, 1
	goto Arnold_RivalsHouse_1F_EventScript_MeetRival
	end

Arnold_RivalsHouse_1F_EventScript_MeetRival2::
	lockall
	setvar VAR_0x8008, 2
	goto Arnold_RivalsHouse_1F_EventScript_MeetRival
	end

Arnold_RivalsHouse_1F_EventScript_MeetRival::
	playse SE_EXIT
	delay 10
	addobject LOCALID_RIVAL
	delay 30
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call_if_ne VAR_0x8008, 1, Arnold_RivalsHouse_1F_EventScript_PlayerFaceRival
	call_if_eq VAR_0x8004, MALE, Arnold_RivalsHouse_1F_EventScript_MayMusic
	call_if_eq VAR_0x8004, FEMALE, Arnold_RivalsHouse_1F_EventScript_BrendanMusic
	call_if_eq VAR_0x8008, 0, Arnold_RivalsHouse_1F_EventScript_RivalApproachPlayer0
	call_if_eq VAR_0x8008, 1, Arnold_RivalsHouse_1F_EventScript_RivalApproachPlayer1
	call_if_eq VAR_0x8008, 2, Arnold_RivalsHouse_1F_EventScript_RivalApproachPlayer2
	call_if_eq VAR_0x8004, MALE, Arnold_RivalsHouse_1F_EventScript_MayDialogue
	call_if_eq VAR_0x8004, FEMALE, Arnold_RivalsHouse_1F_EventScript_BrendanDialogue
	call_if_eq VAR_0x8008, 0, Arnold_RivalsHouse_1F_EventScript_RivalGoUpstairs0
	call_if_eq VAR_0x8008, 1, Arnold_RivalsHouse_1F_EventScript_RivalGoUpstairs1
	call_if_eq VAR_0x8008, 2, Arnold_RivalsHouse_1F_EventScript_RivalGoUpstairs2
	playse SE_EXIT
	removeobject LOCALID_RIVAL
	setflag FLAG_HIDE_ARNOLD_RIVALS_HOUSE_RIVAL
	setflag FLAG_HIDE_ARNOLD_RIVALS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_ARNOLD_RIVALS_HOUSE_RIVAL_BEDROOM
	delay 30
	setvar VAR_ARNOLD_RIVAL_STATE, 3
	setvar VAR_ARNOLD_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

Arnold_RivalsHouse_1F_EventScript_RivalSetMale:
    setvar VAR_0x8004, MALE
    return

Arnold_RivalsHouse_1F_EventScript_RivalSetFemale:
    setvar VAR_0x8004, FEMALE
    return

Arnold_RivalsHouse_1F_EventScript_MayDialogue:
    msgbox Arnold_RivalsHouse_1F_Text_MayWhoAreYou, MSGBOX_DEFAULT
    closemessage
    return

Arnold_RivalsHouse_1F_EventScript_BrendanDialogue:
    msgbox Arnold_RivalsHouse_1F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
    closemessage
    return

Arnold_RivalsHouse_1F_EventScript_MayMusic:
    playbgm MUS_ENCOUNTER_MAY, TRUE
    return

Arnold_RivalsHouse_1F_EventScript_BrendanMusic:
    playbgm MUS_ENCOUNTER_BRENDAN, TRUE
    return

Arnold_RivalsHouse_1F_EventScript_PlayerFaceRival::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

Arnold_RivalsHouse_1F_EventScript_RivalApproachPlayer0::
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_1F_Movement_RivalApproachPlayer0
	waitmovement 0
	return

Arnold_RivalsHouse_1F_EventScript_RivalApproachPlayer1::
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_1F_Movement_RivalApproachPlayer1
	waitmovement 0
	return

Arnold_RivalsHouse_1F_EventScript_RivalApproachPlayer2::
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_1F_Movement_RivalApproachPlayer2
	waitmovement 0
	return

Arnold_RivalsHouse_1F_Movement_RivalApproachPlayer0:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Arnold_RivalsHouse_1F_Movement_RivalApproachPlayer1:
	walk_up
	walk_up
	walk_up
	step_end

Arnold_RivalsHouse_1F_Movement_RivalApproachPlayer2:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Arnold_RivalsHouse_1F_EventScript_RivalGoUpstairs0::
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_RivalsHouse_1F_Movement_PlayerWatchRivalExit0
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_1F_Movement_RivalGoUpstairs0
	waitmovement 0
	return

Arnold_RivalsHouse_1F_EventScript_RivalGoUpstairs1::
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_RivalsHouse_1F_Movement_PlayerWatchRivalExit1
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_1F_Movement_RivalGoUpstairs1
	waitmovement 0
	return

Arnold_RivalsHouse_1F_EventScript_RivalGoUpstairs2::
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_RivalsHouse_1F_Movement_PlayerWatchRivalExit2
	applymovement LOCALID_RIVAL, Arnold_RivalsHouse_1F_Movement_RivalGoUpstairs2
	waitmovement 0
	return

Arnold_RivalsHouse_1F_Movement_PlayerWatchRivalExit0:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

Arnold_RivalsHouse_1F_Movement_PlayerWatchRivalExit1:
	delay_16
	delay_8
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

Arnold_RivalsHouse_1F_Movement_PlayerWatchRivalExit2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

Arnold_RivalsHouse_1F_Movement_RivalGoUpstairs0:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

Arnold_RivalsHouse_1F_Movement_RivalGoUpstairs1:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	step_end

Arnold_RivalsHouse_1F_Movement_RivalGoUpstairs2:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

Arnold_RivalsHouse_1F_Text_OhYoureTheNewNeighbor:
	.string "Oh, hello. And you are?\p"
	.string "… … … … … … … … …\n"
	.string "… … … … … … … … …\p"
	.string "Oh, you're {PLAYER}{KUN}, our new next-door\n"
	.string "neighbor! Hi!\p"
	.string "We have a {STR_VAR_1} about the same\n"
	.string "age as you.\p"
	.string "Our {STR_VAR_1} was excited about making\n"
	.string "a new friend.\p"
	.string "Our {STR_VAR_1} is upstairs, I think.$"

Arnold_RivalsHouse_1F_Text_LikeChildLikeFather:
	.string "Like child, like father.\p"
	.string "My husband is as wild about POKéMON\n"
	.string "as our child.\p"
	.string "If he's not at his LAB, he's likely\n"
	.string "scrabbling about in grassy places.$"

Arnold_RivalsHouse_1F_Text_TooBusyToNoticeVisit:
	.string "That {RIVAL}!\p"
	.string "I guess our child is too busy with\n"
	.string "POKéMON to notice that you came\l"
	.string "to visit, {PLAYER}{KUN}.$"

Arnold_RivalsHouse_1F_Text_WentOutToRoute103:
	.string "Oh, {RIVAL} went out to ROUTE 103\n"
	.string "just a little while ago.\p"
	.string "Like father, like child.\n"
	.string "{RIVAL} can't stay quietly at home.$"

Arnold_RivalsHouse_1F_Text_ShouldGoHomeEverySoOften:
	.string "I think it's wonderful for people to\n"
	.string "travel with POKéMON.\p"
	.string "But you should go home every so often\n"
	.string "to let your mother know you're okay.\p"
	.string "She might not say it, but I'm sure she\n"
	.string "worries about you, {PLAYER}{KUN}.$"

Arnold_RivalsHouse_1F_Text_MayWhoAreYou:
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

Arnold_RivalsHouse_1F_Text_BrendanWhoAreYou:
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

Arnold_RivalsHouse_1F_Text_DoYouHavePokemon:
	.string "Hi, neighbor!\p"
	.string "Do you already have your\n"
	.string "own POKéMON?$"
