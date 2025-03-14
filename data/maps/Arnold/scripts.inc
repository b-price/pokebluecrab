.set LOCALID_AIDE, 1
.set LOCALID_WOMAN, 3
.set LOCALID_MOM, 6
.set LOCALID_RIVAL, 7
.set LOCALID_BIRCH, 5

Arnold_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Arnold_OnTransition
    map_script MAP_SCRIPT_ON_FRAME_TABLE, Arnold_OnFrame
	.byte 0

@ State descriptions for VAR_ARNOLD_STATE
	@ 1: Met Rival
	@ 2: Saving Birch
	@ 3: Received Pokedex
	@ 4: Received Running Shoes

	@ State descriptions for VAR_ARNOLD_INTRO_STATE
	@ 1: In truck male
	@ 2: In truck female
	@ 3: Entered house
	@ 4: Told to go set clock
	@ 5: Entered 2F to set clock
	@ 6: Set clock
	@ 7: Told to go meet rival

	@ State descriptions for VAR_ARNOLD_HOUSES_STATE
	@ 1: On Truck (and is corresponding gender)
	@ 2: Met Rival's Mom (and is corresponding gender)
	@ 3: Entered Hall of Fame
	@ 4: Completed Lati TV / SS Ticket event
	@ 5: Exited house after above event

	@ State descriptions for VAR_ARNOLD_RIVAL_STATE
	@ 1: Never occurs
	@ 2: Entered Rival's bedroom
	@ 3: Met Rival
	@ 4: Received Pokedex

Arnold_OnTransition:
	setflag FLAG_VISITED_ARNOLD
	call Common_EventScript_SetupRivalGfxId
    call_if_unset FLAG_RESCUED_BIRCH, Arnold_EventScript_SetWomanAndAidePos
    call_if_eq VAR_ARNOLD_STATE, 3, Arnold_EventScript_SetMomStandingInFrontOfDoorPos
    call_if_eq VAR_ARNOLD_HOUSES_STATE, 4, Arnold_EventScript_SetExitedHouseAfterLatiSSTicketEvent
    call_if_eq VAR_SEVERNA_PARK_RIVAL_STATE, 1, Arnold_EventScript_MoveRivalFromSevernaPark
    call_if_eq VAR_ARNOLD_RIVAL_STATE, 3, Arnold_EventScript_SetRivalLeftForRoute103
	end
	
Arnold_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

Arnold_EventScript_SetRivalLeftForRoute103::
	setflag FLAG_RIVAL_LEFT_FOR_ROUTE103
	return

Arnold_EventScript_MoveRivalFromSevernaPark::
	setvar VAR_SEVERNA_PARK_RIVAL_STATE, 2
	setflag FLAG_HIDE_SEVERNA_PARK_RIVAL
	return

Arnold_EventScript_SetExitedHouseAfterLatiSSTicketEvent::
	setvar VAR_ARNOLD_HOUSES_STATE, 5
	return

Arnold_EventScript_SetWomanAndAidePos::
	setobjectxyperm LOCALID_AIDE, 18, 13
	setobjectmovementtype LOCALID_AIDE, MOVEMENT_TYPE_FACE_RIGHT
	goto_if_eq VAR_ARNOLD_STATE, 0, Arnold_EventScript_SetWomanGuardingRoutePos
	setobjectxyperm LOCALID_WOMAN, 19, 0
	setobjectmovementtype LOCALID_WOMAN, MOVEMENT_TYPE_FACE_UP
	return

Arnold_EventScript_SetWomanGuardingRoutePos::
	setobjectxyperm LOCALID_WOMAN, 18, 0
	setobjectmovementtype LOCALID_WOMAN, MOVEMENT_TYPE_FACE_DOWN
	return

Arnold_EventScript_SetMomStandingInFrontOfDoorPos::
	clearflag FLAG_HIDE_ARNOLD_MOM_OUTSIDE
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_DOWN
    setobjectxyperm LOCALID_MOM, 16, 5
	return
	
Arnold_OnFrame:
	map_script_2 VAR_ARNOLD_INTRO_STATE, 1, Arnold_EventScript_StepOffTruck
	.2byte 0

Arnold_EventScript_StepOffTruck::
	lockall
	setvar VAR_0x8004, 16
	setvar VAR_0x8005, 4
	call Arnold_EventScript_GoInsideWithMom
	setflag FLAG_HIDE_ARNOLD_TRUCK
	warpsilent MAP_ARNOLD_PLAYERS_HOUSE_1F, 8, 8
	waitstate
	releaseall
	end
	
Arnold_EventScript_GoInsideWithMom::
	delay 15
	playse SE_LEDGE
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_Movement_PlayerStepOffTruck
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	addobject LOCALID_MOM
	applymovement LOCALID_MOM, Arnold_Movement_MomExitHouse
	waitmovement 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	delay 10
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_Movement_PlayerApproachMom
	applymovement LOCALID_MOM, Arnold_Movement_MomApproachPlayerAtTruck
	waitmovement 0
	msgbox Arnold_Text_OurNewHomeLetsGoInside, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOM, Arnold_Movement_MomApproachDoor
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_Movement_PlayerApproachDoor
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement LOCALID_MOM, Arnold_Movement_MomEnterHouse
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_Movement_PlayerEnterHouse
	waitmovement 0
	setflag FLAG_HIDE_ARNOLD_MOM_OUTSIDE
	setvar VAR_ARNOLD_INTRO_STATE, 3
	hideobjectat OBJ_EVENT_ID_PLAYER, 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return

Arnold_Movement_MomExitHouse:
	walk_down
	step_end

Arnold_Movement_MomApproachPlayerAtTruck:
	walk_down
	walk_in_place_faster_right
	step_end

Arnold_Movement_MomApproachDoor:
	delay_16
	delay_8
	walk_up
	step_end

Arnold_Movement_MomEnterHouse:
	walk_up
	set_invisible
	step_end

Arnold_Movement_PlayerApproachDoor:
	delay_16
	delay_8
	walk_left
	walk_in_place_faster_up
	step_end

Arnold_Movement_PlayerEnterHouse:
	walk_up
	walk_up
	step_end

Arnold_Movement_PlayerStepOffTruck:
	jump_right
	delay_16
	delay_16
	delay_16
	step_end

Arnold_Movement_PlayerApproachMom:
    walk_up
    walk_up
    walk_in_place_faster_left
    step_end

Arnold_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, Arnold_EventScript_GoodLuck
	goto_if_set FLAG_RESCUED_BIRCH, Arnold_EventScript_YouSavedBirch
	goto_if_ne VAR_ARNOLD_STATE, 0, Arnold_EventScript_GoSaveBirch
	msgbox Arnold_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	release
	end

Arnold_EventScript_GoSaveBirch::
	special GetPlayerBigGuyGirlString
	msgbox Arnold_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_ARNOLD_STATE, 2
	release
	end

Arnold_EventScript_YouSavedBirch::
	special GetPlayerBigGuyGirlString
	msgbox Arnold_Text_YouSavedBirch, MSGBOX_DEFAULT
	release
	end

Arnold_EventScript_GoodLuck::
	msgbox Arnold_Text_GoodLuckCatchingPokemon, MSGBOX_DEFAULT
	release
	end

Arnold_EventScript_NeedPokemonTriggerLeft::
	lockall
	applymovement LOCALID_WOMAN, Arnold_Movement_WomanApproachPlayerLeft
	waitmovement 0
	call Arnold_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_WOMAN, Arnold_Movement_WomanReturnLeft
	waitmovement 0
	releaseall
	end

Arnold_EventScript_DangerousWithoutPokemon::
	msgbox Arnold_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WOMAN, Arnold_Movement_WomanPushPlayerFromRoute
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_Movement_PushPlayerBackFromRoute
	waitmovement 0
	msgbox Arnold_Text_DangerousIfYouDontHavePokemon, MSGBOX_DEFAULT
	closemessage
	return
	
Arnold_Movement_WomanApproachPlayerLeft:
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	face_down
	step_end

Arnold_Movement_WomanPushPlayerFromRoute:
	walk_down
	step_end

Arnold_Movement_WomanReturnLeft:
	walk_left
	walk_in_place_faster_down
	step_end

Arnold_Movement_PushPlayerBackFromRoute:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

Arnold_EventScript_NeedPokemonTriggerRight::
	lockall
	applymovement LOCALID_WOMAN, Arnold_Movement_WomanApproachPlayerRight
	waitmovement 0
	call Arnold_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_WOMAN, Arnold_Movement_WomanReturnRight
	waitmovement 0
	releaseall
	end

Arnold_Movement_WomanApproachPlayerRight:
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_up
	walk_fast_right
	face_down
	step_end

Arnold_Movement_WomanReturnRight:
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

Arnold_EventScript_GoSaveBirchTrigger::
	lockall
	applymovement LOCALID_WOMAN, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	special GetPlayerBigGuyGirlString
	msgbox Arnold_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_ARNOLD_STATE, 2
	releaseall
	end

Arnold_EventScript_Aide::
    lock
    faceplayer
    goto_if_set FLAG_ADVENTURE_STARTED, Arnold_EventScript_AideBirchNotHomeMuch
    msgbox Arnold_Text_AideObserving, MSGBOX_DEFAULT
    closemessage
    release
    end

Arnold_EventScript_AideBirchNotHomeMuch::
    msgbox Arnold_Text_BirchSpendsDaysInLab, MSGBOX_DEFAULT
    closemessage
    release
    end
	
Arnold_EventScript_BlockedPath::
    lockall
    faceplayer
    playse SE_PIN
    applymovement LOCALID_AIDE, Common_Movement_ExclamationMark
    waitmovement 0
    msgbox Arnold_Text_AideObserving, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_AIDE, Common_Movement_FaceOriginalDirection
    waitmovement 0
    applymovement OBJ_EVENT_ID_PLAYER, Arnold_Movement_PlayerStepBack
    waitmovement 0
    releaseall
    end

Arnold_EventScript_Azurill::
    lock
    faceplayer
    waitse
    playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
    msgbox Arnold_Text_Azurill, MSGBOX_DEFAULT
    waitmoncry
    release
    end

Arnold_Movement_PlayerStepBack:
    delay_8
	walk_up
	step_end

Arnold_EventScript_TownSign::
	msgbox Arnold_Text_TownSign, MSGBOX_SIGN
	end

Arnold_EventScript_PlayersHouseSign::
	msgbox Arnold_Text_PlayersHouse, MSGBOX_SIGN
	end

Arnold_EventScript_BirchsHouseSign::
	msgbox Arnold_Text_ProfBirchsHouse, MSGBOX_SIGN
	end

Arnold_EventScript_LabSign::
	msgbox Arnold_Text_Lab, MSGBOX_SIGN
	end

Arnold_EventScript_GiveRunningShoesTrigger0::
	lockall
	setvar VAR_0x8008, 0
	setobjectxy LOCALID_MOM, 10, 9
	goto Arnold_EventScript_GiveRunningShoesTrigger
	end

Arnold_EventScript_GiveRunningShoesTrigger1::
	lockall
	setvar VAR_0x8008, 1
	setobjectxy LOCALID_MOM, 11, 9
	goto Arnold_EventScript_GiveRunningShoesTrigger
	end

Arnold_EventScript_GiveRunningShoesTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto Arnold_EventScript_GiveRunningShoesTrigger
	end

Arnold_EventScript_GiveRunningShoesTrigger3::
	lockall
	setvar VAR_0x8008, 3
	goto Arnold_EventScript_GiveRunningShoesTrigger
	end

Arnold_EventScript_GiveRunningShoesTrigger4::
	lockall
	setvar VAR_0x8008, 4
	goto Arnold_EventScript_GiveRunningShoesTrigger
	end

Arnold_EventScript_GiveRunningShoesTrigger5::
	lockall
	setvar VAR_0x8008, 5
	goto Arnold_EventScript_GiveRunningShoesTrigger
	end

Arnold_EventScript_GiveRunningShoesTrigger::
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterRight
    waitmovement 0
	msgbox Arnold_Text_WaitPlayer, MSGBOX_DEFAULT
	closemessage
	call Arnold_EventScript_MomApproachPlayer
	call Arnold_EventScript_GiveRunningShoes
	call Arnold_EventScript_MomReturnHome
	goto Arnold_EventScript_SetReceivedRunningShoes
	end

Arnold_EventScript_MomApproachPlayer::
	call_if_eq VAR_0x8008, 0, Arnold_EventScript_MomApproachPlayer0
	call_if_eq VAR_0x8008, 1, Arnold_EventScript_MomApproachPlayer1
	call_if_eq VAR_0x8008, 2, Arnold_EventScript_MomApproachPlayer2
	call_if_eq VAR_0x8008, 3, Arnold_EventScript_MomApproachPlayer3
	call_if_eq VAR_0x8008, 4, Arnold_EventScript_MomApproachPlayer4
	call_if_eq VAR_0x8008, 5, Arnold_EventScript_MomApproachPlayer5
	return

Arnold_EventScript_MomApproachPlayer0::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_MOM, Arnold_Movement_MomApproachPlayer0
	waitmovement 0
	return

Arnold_EventScript_MomApproachPlayer1::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_MOM, Arnold_Movement_MomApproachPlayer1
	waitmovement 0
	return

Arnold_EventScript_MomApproachPlayer2::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_MOM, Arnold_Movement_MomApproachPlayer2
	waitmovement 0
	return

Arnold_EventScript_MomApproachPlayer3::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_MOM, Arnold_Movement_MomApproachPlayer3
	waitmovement 0
	return

Arnold_EventScript_MomApproachPlayer4::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_MOM, Arnold_Movement_MomApproachPlayer4
	waitmovement 0
	return

Arnold_EventScript_MomApproachPlayer5::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_MOM, Arnold_Movement_MomApproachPlayer5
	waitmovement 0
	return


Arnold_EventScript_MomReturnHome::
	call_if_eq VAR_0x8008, 0, Arnold_EventScript_MomReturnHome0
	call_if_eq VAR_0x8008, 1, Arnold_EventScript_MomReturnHome1
	call_if_eq VAR_0x8008, 2, Arnold_EventScript_MomReturnHome2
	call_if_eq VAR_0x8008, 3, Arnold_EventScript_MomReturnHome3
	call_if_eq VAR_0x8008, 4, Arnold_EventScript_MomReturnHome4
	call_if_eq VAR_0x8008, 5, Arnold_EventScript_MomReturnHome5
	return

Arnold_EventScript_MomReturnHome0::
	applymovement LOCALID_MOM, Arnold_Movement_MomReturnHome0
	waitmovement 0
	return

Arnold_EventScript_MomReturnHome1::
	applymovement LOCALID_MOM, Arnold_Movement_MomReturnHome1
	waitmovement 0
	return

Arnold_EventScript_MomReturnHome2::
	applymovement LOCALID_MOM, Arnold_Movement_MomReturnHome2
	waitmovement 0
	opendoor 16, 4
	waitdooranim
	applymovement LOCALID_MOM, Arnold_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_ARNOLD
	closedoor 16, 4
	waitdooranim
	return

Arnold_EventScript_MomReturnHome3::
	applymovement LOCALID_MOM, Arnold_Movement_MomReturnHome3
	waitmovement 0
	opendoor 16, 4
	waitdooranim
	applymovement LOCALID_MOM, Arnold_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_ARNOLD
	closedoor 16, 4
	waitdooranim
	return

Arnold_EventScript_MomReturnHome4::
	applymovement LOCALID_MOM, Arnold_Movement_MomReturnHome4
	waitmovement 0
	opendoor 16, 4
	waitdooranim
	applymovement LOCALID_MOM, Arnold_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_ARNOLD
	closedoor 16, 4
	waitdooranim
	return

Arnold_EventScript_MomReturnHome5::
	applymovement LOCALID_MOM, Arnold_Movement_MomReturnHome5
	waitmovement 0
	opendoor 16, 4
	waitdooranim
	applymovement LOCALID_MOM, Arnold_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_ARNOLD
	closedoor 16, 4
	waitdooranim
	return

Arnold_Movement_MomApproachPlayer0:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Arnold_Movement_MomApproachPlayer1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Arnold_Movement_MomApproachPlayer2:
	walk_right
	walk_right
	walk_right
	step_end

Arnold_Movement_MomApproachPlayer3:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Arnold_Movement_MomApproachPlayer4:
	walk_right
	step_end

Arnold_Movement_MomApproachPlayer5:
	walk_right
	walk_right
	step_end

Arnold_Movement_MomReturnHome0:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Arnold_Movement_MomReturnHome1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Arnold_Movement_MomReturnHome2:
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

Arnold_Movement_MomReturnHome3:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

Arnold_Movement_MomReturnHome4:
	walk_left
	walk_in_place_faster_up
	step_end

Arnold_Movement_MomReturnHome5:
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

Arnold_Movement_MomExitThroughDoor:
	walk_up
	step_end

Arnold_EventScript_Mom::
	lock
	faceplayer
	call Arnold_EventScript_GiveRunningShoes
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 16, 4
	waitdooranim
	applymovement LOCALID_MOM, Arnold_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_ARNOLD
	closedoor 16, 4
	waitdooranim
	goto Arnold_EventScript_SetReceivedRunningShoes
	end

Arnold_EventScript_SetReceivedRunningShoes::
	removeobject LOCALID_MOM
	setflag FLAG_SYS_B_DASH
	setvar VAR_ARNOLD_STATE, 4
	release
	end

Arnold_EventScript_GiveRunningShoes::
	msgbox Arnold_Text_WearTheseRunningShoes, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message Arnold_Text_SwitchShoesWithRunningShoes
	waitfanfare
	setflag FLAG_RECEIVED_RUNNING_SHOES
	msgbox Arnold_Text_ExplainRunningShoes, MSGBOX_DEFAULT
	msgbox Arnold_Text_ComeHomeIfAnythingHappens, MSGBOX_DEFAULT
	closemessage
	delay 30
	return

Arnold_EventScript_Twin::
	msgbox Arnold_Text_Twin, MSGBOX_NPC
	end

Arnold_Text_OurNewHomeLetsGoInside:
	.string "MOM: {PLAYER}, we're here, honey!\p"
	.string "It must be tiring riding with our things\n"
	.string "in the moving truck.\p"
	.string "Well, this is ARNOLD.\p"
	.string "How do you like it?\n"
	.string "This is our new home!\p"
	.string "It has a quaint feel, but it seems to be\n"
	.string "an easy place to live, don't you think?\p"
	.string "And, you get your own room, {PLAYER}!\n"
	.string "Let's go inside.$"

Arnold_Text_WaitPlayer:
	.string "MOM: Wait, {PLAYER}!$"

Arnold_Text_WearTheseRunningShoes:
	.string "MOM: {PLAYER}! {PLAYER}! Did you\n"
	.string "introduce yourself to PROF. BIRCH?\p"
	.string "Oh! What an adorable POKéMON!\n"
	.string "You got it from PROF. BIRCH. How nice!\p"
	.string "You're your father's child, all right.\n"
	.string "You look good together with POKéMON!\p"
	.string "Here, honey! If you're going out on an\n"
	.string "adventure, wear these RUNNING SHOES.\p"
	.string "They'll put a zip in your step!$"

Arnold_Text_SwitchShoesWithRunningShoes:
	.string "{PLAYER} switched shoes with the\n"
	.string "RUNNING SHOES.$"

Arnold_Text_ExplainRunningShoes:
	.string "MOM: {PLAYER}, those shoes came with\n"
	.string "instructions.\p"
	.string "“Press the B Button while wearing these\n"
	.string "RUNNING SHOES to run extra-fast!\p"
	.string "“Slip on these RUNNING SHOES and race\n"
	.string "in the great outdoors!”$"

Arnold_Text_ComeHomeIfAnythingHappens:
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "To think that you have your very own\n"
	.string "POKéMON now…\l"
	.string "Your father will be overjoyed.\p"
	.string "…But please be careful.\n"
	.string "If anything happens, you can come home.\p"
	.string "Go on, go get them, honey!$"

Arnold_Text_TownSign:
	.string "ARNOLD\n"
	.string "“A town that can't be shaded any hue.”$"

Arnold_Text_AideObserving:
    .string "Hold on, there!\n"
    .string "I'm observing this AZURILL.\l"
    .string "This is important research!$"

Arnold_Text_Azurill:
    .string "AZURILL: Rooleeloo.\p"
    .string "Better not disturb it!$"

Arnold_Text_CanUsePCToStoreItems:
	.string "If you use a PC, you can store items\n"
	.string "and POKéMON.\p"
	.string "The power of science is staggering!$"

Arnold_Text_BirchSpendsDaysInLab:
	.string "PROF. BIRCH spends days in his LAB\n"
	.string "studying, then he'll suddenly go out in\l"
	.string "the wild to do more research…\p"
	.string "When does PROF. BIRCH spend time\n"
	.string "at home?$"

Arnold_Text_IfYouGoInGrassPokemonWillJumpOut:
	.string "Hi! You must be new in town.\p"
	.string "If you go outside and go in the grass,\n"
	.string "wild POKéMON will jump out!$"

Arnold_Text_DangerousIfYouDontHavePokemon:
	.string "It's dangerous if you don't have\n"
	.string "your own POKéMON.$"

Arnold_Text_CanYouGoSeeWhatsHappening:
	.string "Hey!\p"
	.string "There are scary POKéMON outside!\n"
	.string "I can hear their cries!\p"
	.string "I want to go see what's going on,\n"
	.string "but I don't have any POKéMON…\p"
	.string "Can you go see what's happening\n"
	.string "for me?$"

Arnold_Text_YouSavedBirch:
	.string "You saved PROF. BIRCH!\n"
	.string "I'm so glad!$"

Arnold_Text_GoodLuckCatchingPokemon:
	.string "Are you going to catch POKéMON?\n"
	.string "Good luck!$"

Arnold_Text_Lab:
	.string "ARNOLD POKéMON LAB$"

Arnold_Text_PlayersHouse:
	.string "{PLAYER}'s HOUSE$"

Arnold_Text_ProfBirchsHouse:
	.string "PROF. BIRCH'S HOUSE$"

Arnold_Text_BirchSomethingToShowYouAtLab:
	.string "PROF. BIRCH: Well, well, {PLAYER}{KUN}!\n"
	.string "That was good work out there!\p"
	.string "I knew there was something special\n"
	.string "about you when I first saw you,\l"
	.string "but I never expected this.\p"
	.string "Oh, yes. Do you still have the POKéDEX\n"
	.string "I gave you?\p"
	.string "I have something to show you.\n"
	.string "Let's go to my LAB.$"

Arnold_Text_Twin:
    .string "Um, hi!\n"
    .string "Look at the water!\l"
    .string "Isn't it pretty?\p"
    .string "Maybe I'll catch a water POKéMON!$"
