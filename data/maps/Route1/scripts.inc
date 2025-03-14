.set LOCALID_BIRCH, 3
.set LOCALID_ZIGZAGOON, 2

Route1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route1_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route1_OnFrame
	.byte 0

Route1_OnTransition:
	call ProfBirch_EventScript_UpdateLocation
	end

Route1_OnFrame:
	map_script_2 VAR_ROUTE1_STATE, 0, Route1_EventScript_HideMapNamePopup
	.2byte 0

Route1_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_ROUTE1_STATE, 1
	end

Route1_EventScript_StartBirchRescue::
	lockall
	playbgm MUS_HELP, TRUE
	msgbox Route1_Text_HelpMe, MSGBOX_DEFAULT
	closemessage
	setobjectxy LOCALID_BIRCH, 14, 10
	setobjectxy LOCALID_ZIGZAGOON, 14, 11
	applymovement OBJ_EVENT_ID_PLAYER, Route1_Movement_EnterScene
	applymovement LOCALID_BIRCH, Route1_Movement_BirchRunAway1
	applymovement LOCALID_ZIGZAGOON, Route1_Movement_ZigzagoonChase1
	waitmovement 0
	applymovement LOCALID_ZIGZAGOON, Route1_Movement_ZigzagoonChaseInCircles
	applymovement LOCALID_BIRCH, Route1_Movement_BirchRunInCircles
	waitmovement 0
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_ZIGZAGOON, Route1_Movement_ZigzagoonFaceBirch
	applymovement LOCALID_BIRCH, Route1_Movement_BirchFaceZigzagoon
	waitmovement 0
	msgbox Route1_Text_PleaseHelp, MSGBOX_DEFAULT
	closemessage
	setvar VAR_ROUTE1_STATE, 2
	releaseall
	end

Route1_EventScript_PreventExitSouth::
	lockall
	msgbox Route1_Text_DontLeaveMe, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route1_Movement_PreventExitSouth
	waitmovement 0
	releaseall
	end

Route1_EventScript_PreventExitWest::
	lockall
	msgbox Route1_Text_DontLeaveMe, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route1_Movement_PreventExitWest
	waitmovement 0
	releaseall
	end

Route1_EventScript_PreventExitNorth::
	lockall
	msgbox Route1_Text_DontLeaveMe, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route1_Movement_PreventExitNorth
	waitmovement 0
	releaseall
	end

Route1_Movement_PreventExitSouth:
	walk_up
	step_end

Route1_Movement_PreventExitWest:
	walk_right
	step_end

Route1_Movement_PreventExitNorth:
	walk_down
	step_end

Route1_Movement_ZigzagoonChaseInCircles:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	step_end

Route1_Movement_ZigzagoonChase1:
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route1_Movement_ZigzagoonFaceBirch:
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_fast_right
	step_end

Route1_Movement_EnterScene:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_in_place_faster_left
	step_end

Route1_Movement_BirchRunInCircles:
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route1_Movement_BirchRunAway1:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	step_end

Route1_Movement_BirchFaceZigzagoon:
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	step_end

Route1_EventScript_Youngster::
	msgbox Route1_Text_TakeTiredPokemonToPokeCenter, MSGBOX_NPC
	end

Route1_EventScript_Boy::
	msgbox Route1_Text_WildPokemonInTallGrass, MSGBOX_NPC
	end

Route1_EventScript_RouteSign::
	msgbox Route1_Text_RouteSign, MSGBOX_SIGN
	end

Route1_EventScript_BirchsBag::
	lock
	faceplayer
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_RESCUED_BIRCH
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ZIGZAGOON
	setobjectxy OBJ_EVENT_ID_PLAYER, 19, 11
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	special ChooseStarter
	waitstate
	applymovement LOCALID_BIRCH, Route1_Movement_BirchApproachPlayer
	waitmovement 0
	msgbox Route1_Text_YouSavedMe, MSGBOX_DEFAULT
	special HealPlayerParty
	setflag FLAG_HIDE_ROUTE_1_BIRCH_ZIGZAGOON_BATTLE
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
	setvar VAR_BIRCH_LAB_STATE, 2
	setvar VAR_ROUTE1_STATE, 3
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setflag FLAG_HIDE_ARNOLD_RIVALS_HOUSE_RIVAL_BEDROOM
	warp MAP_ARNOLD_LAB, 6, 5
	waitstate
	release
	end

Route1_Movement_BirchApproachPlayer:
	walk_down
	walk_down
	walk_right
	step_end

Route1_Text_HelpMe:
	.string "H-help me!$"

Route1_Text_PleaseHelp:
	.string "Hello! You over there!\n"
	.string "Please! Help!\p"
	.string "In my BAG!\n"
	.string "There's a POKé BALL!$"

Route1_Text_DontLeaveMe:
	.string "Wh-Where are you going?!\n"
	.string "Don't leave me like this!$"

Route1_Text_YouSavedMe:
	.string "PROF. BIRCH: Whew…\p"
	.string "I was in the tall grass studying wild\n"
	.string "POKéMON when I was jumped.\p"
	.string "You saved me.\n"
	.string "Thanks a lot!\p"
	.string "Oh?\p"
	.string "Hi, you're {PLAYER}{KUN}!\p"
	.string "This is not the place to chat, so come\n"
	.string "by my POKéMON LAB later, okay?$"

Route1_Text_TakeTiredPokemonToPokeCenter:
	.string "If POKéMON get tired, take them to\n"
	.string "a POKéMON CENTER.\p"
	.string "There's a POKéMON CENTER in SEVERNA\n"
	.string "PARK right close by.$"

Route1_Text_WildPokemonInTallGrass:
	.string "Wild POKéMON will jump out at you in\n"
	.string "tall grass.\p"
	.string "If you want to catch POKéMON, you have\n"
	.string "to go into the tall grass and search.$"

Route1_Text_RouteSign:
	.string "ROUTE 1\n"
	.string "{UP_ARROW} SEVERNA PARK$"
