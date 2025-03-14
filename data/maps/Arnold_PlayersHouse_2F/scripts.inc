.set LOCALID_MOM_2F, 13

Arnold_PlayersHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Arnold_PlayersHouse_2F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Arnold_PlayersHouse_2F_OnWarp
	.byte 0

Arnold_PlayersHouse_2F_OnTransition:
	call_if_eq VAR_ARNOLD_INTRO_STATE, 4, PlayersHouse_2F_EventScript_BlockStairsUntilClockIsSet
	call SecretBase_EventScript_SetDecorationFlags
	setvar VAR_SECRET_BASE_INITIALIZED, 0
	end

Arnold_PlayersHouse_2F_EventScript_Ret::
	return

Arnold_PlayersHouse_2F_OnWarp:
	map_script_2 VAR_SECRET_BASE_INITIALIZED, 0, SecretBase_EventScript_InitDecorations
	.2byte 0

Arnold_PlayersHouse_2F_EventScript_BlockStairsUntilClockIsSet::
	setvar VAR_ARNOLD_INTRO_STATE, 5
	return

Arnold_PlayersHouse_2F_EventScript_WallClock::
    lockall
    checkplayergender
    call_if_eq VAR_RESULT, MALE, Arnold_PlayersHouse_2F_EventScript_SetClockGenderMale
    call_if_eq VAR_RESULT, FEMALE, Arnold_PlayersHouse_2F_EventScript_SetClockGenderFemale
	goto_if_set FLAG_SET_WALL_CLOCK, Arnold_PlayersHouse_2F_EventScript_CheckWallClock
	msgbox Arnold_PlayersHouse_2F_Text_ClockIsStopped, MSGBOX_DEFAULT
	call Arnold_PlayersHouse_2F_EventScript_SetWallClock
	delay 30
	setvar VAR_ARNOLD_INTRO_STATE, 6
	setflag FLAG_SET_WALL_CLOCK
	setflag FLAG_HIDE_LITTLEROOT_TOWN_PLAYERS_HOUSE_VIGOROTH_1
	setflag FLAG_HIDE_LITTLEROOT_TOWN_PLAYERS_HOUSE_VIGOROTH_2
	call Arnold_PlayersHouse_2F_EventScript_MomComesUpstairs
	playse SE_EXIT
	removeobject LOCALID_MOM_2F
	releaseall
	end

Arnold_PlayersHouse_2F_EventScript_SetClockGenderMale:
    setvar VAR_0x8004, MALE
    return

Arnold_PlayersHouse_2F_EventScript_SetClockGenderFemale:
   setvar VAR_0x8004, FEMALE
   return

Arnold_PlayersHouse_2F_EventScript_MomComesUpstairs::
	addobject LOCALID_MOM_2F
	applymovement LOCALID_MOM_2F, Arnold_PlayersHouse_2F_Movement_MomEnters
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox Arnold_PlayersHouse_2F_Text_HowDoYouLikeYourRoom, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOM_2F, Arnold_PlayersHouse_2F_Movement_MomExits
	waitmovement 0
	return

Arnold_PlayersHouse_2F_EventScript_CheckWallClock::
	incrementgamestat GAME_STAT_CHECKED_CLOCK
	fadescreen FADE_TO_BLACK
	special Special_ViewWallClock
	waitstate
	releaseall
	end

Arnold_PlayersHouse_2F_EventScript_SetWallClock::
	fadescreen FADE_TO_BLACK
	special StartWallClock
	waitstate
	return

Arnold_PlayersHouse_2F_EventScript_PC::
	lockall
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
    special DoPCTurnOnEffect
    playse SE_PC_ON
    msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
    special BedroomPC
    waitstate
    releaseall
    end

Arnold_PlayersHouse_2F_EventScript_TurnOffPlayerPC::
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

Arnold_PlayersHouse_2F_EventScript_Notebook::
	msgbox Arnold_PlayersHouse_2F_Text_Notebook, MSGBOX_SIGN
	end

Arnold_PlayersHouse_2F_EventScript_GameCube::
	msgbox Arnold_PlayersHouse_2F_Text_ItsAGameCube, MSGBOX_SIGN
	end

Arnold_PlayersHouse_2F_Movement_MomEnters:
	delay_8
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_8
	walk_left
	step_end

Arnold_PlayersHouse_2F_Movement_MomExits:
	walk_right
	walk_up
	delay_8
	step_end

Arnold_PlayersHouse_2F_Text_ClockIsStopped:
	.string "The clock is stopped…\p"
	.string "Better set it and start it!$"

Arnold_PlayersHouse_2F_Text_HowDoYouLikeYourRoom:
	.string "MOM: {PLAYER}, how do you like your\n"
	.string "new room?\p"
	.string "Good! Everything's put away neatly!\p"
	.string "They finished moving everything in\n"
	.string "downstairs, too.\p"
	.string "POKéMON movers are so convenient!\p"
	.string "Oh, you should make sure that\n"
	.string "everything's all there on your desk.$"

Arnold_PlayersHouse_2F_Text_Notebook:
	.string "{PLAYER} flipped open the notebook.\p"
	.string "ADVENTURE RULE NO. 1\n"
	.string "Open the MENU with START.\p"
	.string "ADVENTURE RULE NO. 2\n"
	.string "Record your progress with SAVE.\p"
	.string "The remaining pages are blank…$"

ArnoldPlayersHouse_2F_Text_LookCloserAtMap:
	.string "{PLAYER} took a closer look at the\n"
	.string "MARYLAND region map.$"

Arnold_PlayersHouse_2F_Text_ItsAGameCube:
	.string "It's a Nintendo GameCube.\p"
	.string "A Game Boy Advance is connected to\n"
	.string "serve as the Controller.$"
