.set LOCALID_MOM, 1
.set LOCALID_DAD, 4

Arnold_PlayersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Arnold_PlayersHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, Arnold_PlayersHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Arnold_PlayersHouse_1F_OnFrame
	.byte 0

Arnold_PlayersHouse_1F_OnLoad:
	call_if_lt VAR_ARNOLD_INTRO_STATE, 6, Arnold_PlayersHouse_1F_EventScript_SetMovingBoxes
	call_if_set FLAG_RECEIVED_RUNNING_SHOES, Arnold_PlayersHouse_1F_EventScript_CheckShowShoesManual
	end

Arnold_PlayersHouse_1F_EventScript_SetMovingBoxes::
	setmetatile 5, 4, METATILE_BrendansMaysHouse_MovingBox_Open, TRUE
	setmetatile 5, 2, METATILE_BrendansMaysHouse_MovingBox_Closed, TRUE
	return

Arnold_PlayersHouse_1F_EventScript_CheckShowShoesManual::
	setmetatile 3, 7, METATILE_BrendansMaysHouse_BookOnTable, TRUE
	return

Arnold_PlayersHouse_1F_OnTransition:
	call_if_eq VAR_ARNOLD_INTRO_STATE, 3, Arnold_PlayersHouse_1F_EventScript_MoveMomToDoor
	call_if_eq VAR_ARNOLD_INTRO_STATE, 5, Arnold_PlayersHouse_1F_EventScript_MoveMomToStairs
	call_if_eq VAR_ARNOLD_INTRO_STATE, 6, Arnold_PlayersHouse_1F_EventScript_MoveMomToTV
	end

Arnold_PlayersHouse_1F_EventScript_MoveMomToStairs::
	setobjectxyperm LOCALID_MOM, 8, 4
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

Arnold_PlayersHouse_1F_EventScript_MoveMomToTV::
	setobjectxyperm LOCALID_MOM, 4, 5
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

Arnold_PlayersHouse_1F_EventScript_MoveMomToDoor::
	setobjectxyperm LOCALID_MOM, 9, 8
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

@ Many of the below scripts have no gender check because they assume youre in the correct house
@ The below SS Ticket script uses Mays house state by accident(?), but theyre both set identically after the intro
Arnold_PlayersHouse_1F_OnFrame:
	map_script_2 VAR_ARNOLD_INTRO_STATE, 3, Arnold_PlayersHouse_1F_EventScript_EnterHouseMovingIn
	map_script_2 VAR_ARNOLD_INTRO_STATE, 5, Arnold_PlayersHouse_1F_EventScript_GoUpstairsToSetClock
	map_script_2 VAR_ARNOLD_INTRO_STATE, 6, Arnold_PlayersHouse_1F_EventScript_PetalburgGymReport
	map_script_2 VAR_ARNOLD_HOUSES_STATE, 3, PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV
	.2byte 0

Arnold_PlayersHouse_1F_EventScript_GoUpstairsToSetClock::
	lockall
	msgbox Arnold_PlayersHouse_1F_Text_GoSetTheClock, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_PlayersHouse_1F_Movement_PushTowardStairs
	applymovement LOCALID_MOM, Arnold_PlayersHouse_1F_Movement_PushTowardStairs
	waitmovement 0
	warp MAP_ARNOLD_PLAYERS_HOUSE_2F, 7, 1
	waitstate
	releaseall
	end

Arnold_PlayersHouse_1F_Movement_PushTowardStairs:
	walk_up
	step_end

Arnold_PlayersHouse_1F_EventScript_EnterHouseMovingIn::
    lockall
	msgbox Arnold_PlayersHouse_1F_Text_IsntItNiceInHere, MSGBOX_DEFAULT
	applymovement LOCALID_MOM, Common_Movement_FacePlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
    waitmovement 0
	msgbox Arnold_PlayersHouse_1F_Text_MoversPokemonGoSetClock, MSGBOX_DEFAULT
	closemessage
	setvar VAR_ARNOLD_INTRO_STATE, 4
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_PlayersHouse_1F_Movement_PlayerWalkIn
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	releaseall
	end

Arnold_PlayersHouse_1F_EventScript_SetWatchedBroadcast::
	setvar VAR_ARNOLD_INTRO_STATE, 7
	releaseall
	end

Arnold_PlayersHouse_1F_EventScript_PetalburgGymReport::
	lockall
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	call Arnold_PlayersHouse_1F_EventScript_MomNoticeGymBroadcast
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_PlayersHouse_1F_Movement_PlayerApproachTVForGym
	waitmovement 0
	playbgm MUS_ENCOUNTER_INTERVIEWER, FALSE
	msgbox Arnold_PlayersHouse_1F_Text_MaybeDadWillBeOn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOM, Arnold_PlayersHouse_1F_Movement_MomMakeRoomToSeeTV
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_PlayersHouse_1F_Movement_PlayerMoveToTV
	waitmovement 0
	call Arnold_PlayersHouse_1F_EventScript_WatchGymBroadcast
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox Arnold_PlayersHouse_1F_Text_ItsOverWeMissedHim, MSGBOX_DEFAULT
	msgbox Arnold_PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_1, 1
	applymovement LOCALID_MOM, Arnold_PlayersHouse_1F_Movement_MomReturnToSeat
	waitmovement 0
	goto Arnold_PlayersHouse_1F_EventScript_SetWatchedBroadcast
	end

Arnold_PlayersHouse_1F_EventScript_MomNoticeGymBroadcast::
	playse SE_PIN
	applymovement LOCALID_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MOM, Common_Movement_Delay48
	waitmovement 0
	msgbox Arnold_PlayersHouse_1F_Text_OhComeQuickly, MSGBOX_DEFAULT
	closemessage
	return

Arnold_PlayersHouse_1F_EventScript_WatchGymBroadcast::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox Arnold_PlayersHouse_1F_Text_ReportFromPetalburgGym, MSGBOX_DEFAULT
	fadedefaultbgm
	special TurnOffTVScreen
	setflag FLAG_SYS_TV_HOME
	delay 35
	return

Arnold_PlayersHouse_1F_EventScript_GoSeeRoom::
	lockall
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto Arnold_PlayersHouse_1F_EventScript_MomGoSeeRoom
	end

Arnold_PlayersHouse_1F_EventScript_MomGoSeeRoom::
	msgbox Arnold_PlayersHouse_1F_Text_ArentYouInterestedInRoom, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterUp
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_PlayersHouse_1F_Movement_MovePlayerAwayFromDoor
	waitmovement 0
	releaseall
	end

Arnold_PlayersHouse_1F_EventScript_Mom::
	lock
	faceplayer
	goto_if_eq VAR_ARNOLD_HOUSES_STATE, 4, Arnold_PlayersHouse_1F_EventScript_DontPushYourselfTooHard
	goto_if_set FLAG_HAS_MATCH_CALL, Arnold_PlayersHouse_1F_EventScript_TryRegisterMom
	goto_if_set FLAG_RESCUED_BIRCH, Arnold_PlayersHouse_1F_EventScript_MomHealsParty
	goto_if_eq VAR_TEMP_1, 1, Arnold_PlayersHouse_1F_EventScript_SeeYouHoney
	goto_if_eq VAR_ARNOLD_INTRO_STATE, 7, Arnold_PlayersHouse_1F_EventScript_DidYouMeetProfBirch
	msgbox Arnold_PlayersHouse_1F_Text_IsntItNiceInHere, MSGBOX_DEFAULT
	release
	end

Arnold_PlayersHouse_1F_EventScript_DontPushYourselfTooHard::
	msgbox PlayersHouse_1F_Text_DontPushYourselfTooHard, MSGBOX_DEFAULT
	release
	end

Arnold_PlayersHouse_1F_EventScript_TryRegisterMom::
	goto_if_set FLAG_ENABLE_MOM_MATCH_CALL, Arnold_PlayersHouse_1F_EventScript_CheckGiveAmuletCoin
	msgbox Arnold_PlayersHouse_1F_Text_IsThatAPokenav, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Arnold_PlayersHouse_1F_Text_RegisteredMom, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_MOM_MATCH_CALL
	release
	end

Arnold_PlayersHouse_1F_EventScript_CheckGiveAmuletCoin::
	goto_if_set FLAG_BADGE05_GET, Arnold_PlayersHouse_1F_EventScript_TryGiveAmuletCoin
	goto Arnold_PlayersHouse_1F_EventScript_MomHealsParty

Arnold_PlayersHouse_1F_EventScript_TryGiveAmuletCoin::
	goto_if_set FLAG_RECEIVED_AMULET_COIN, Arnold_PlayersHouse_1F_EventScript_MomHealsParty
	msgbox Arnold_PlayersHouse_1F_Text_GotDadsBadgeHeresSomethingFromMom, MSGBOX_DEFAULT
	giveitem ITEM_AMULET_COIN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox Arnold_PlayersHouse_1F_Text_DontPushYourselfTooHard, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_AMULET_COIN
	release
	end

Arnold_PlayersHouse_1F_EventScript_MomHealsParty::
	msgbox Arnold_PlayersHouse_1F_Text_YouShouldRestABit, MSGBOX_DEFAULT
	goto Arnold_PlayersHouse_1F_EventScript_HealParty
	end

Arnold_PlayersHouse_1F_EventScript_SeeYouHoney::
	msgbox Arnold_PlayersHouse_1F_Text_SeeYouHoney, MSGBOX_DEFAULT
	release
	end

Arnold_PlayersHouse_1F_EventScript_HealParty::
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	incrementgamestat GAME_STAT_RESTED_AT_HOME
	msgbox Arnold_PlayersHouse_1F_Text_TakeCareHoney, MSGBOX_DEFAULT
	release
	end

Arnold_PlayersHouse_1F_EventScript_DidYouMeetProfBirch::
	msgbox Arnold_PlayersHouse_1F_Text_DidYouMeetProfBirch, MSGBOX_DEFAULT
	release
	end

Arnold_PlayersHouse_1F_EventScript_Vigoroth1::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_VIGOROTH, CRY_MODE_NORMAL
	msgbox Arnold_PlayersHouse_1F_Text_Vigoroth1, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Arnold_PlayersHouse_1F_EventScript_Vigoroth2::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_VIGOROTH, CRY_MODE_NORMAL
	msgbox Arnold_PlayersHouse_1F_Text_Vigoroth2, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Arnold_PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_PlayersHouse_1F_Movement_PlayerEnterRoom
    waitmovement 0
	applymovement LOCALID_DAD, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_DAD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_DAD, Common_Movement_Delay48
	waitmovement 0
	delay 20
	applymovement LOCALID_DAD, Arnold_PlayersHouse_1F_Movement_DadApproachPlayer
    waitmovement 0
	msgbox Arnold_PlayersHouse_1F_Text_TicketFromBrineyCameForYou, MSGBOX_DEFAULT
	giveitem ITEM_SS_TICKET
	msgbox Arnold_PlayersHouse_1F_Text_PortsInSlateportLilycove, MSGBOX_DEFAULT
	closemessage
	delay 20
	applymovement LOCALID_MOM, Arnold_PlayersHouse_1F_Movement_MomApproachDad
    waitmovement 0
    applymovement LOCALID_DAD, Arnold_PlayersHouse_1F_Movement_DadFaceMom
    waitmovement 0
	msgbox Arnold_PlayersHouse_1F_Text_BetterGetBackToGym, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_PlayersHouse_1F_Movement_MomAndPlayerWatchDadExit
    applymovement LOCALID_MOM, Arnold_PlayersHouse_1F_Movement_MomAndPlayerWatchDadExit
    applymovement LOCALID_DAD, Arnold_PlayersHouse_1F_Movement_DadExits
    waitmovement 0
	playse SE_DOOR
	removeobject LOCALID_DAD
	setflag FLAG_RECEIVED_SS_TICKET
	delay 30
	applymovement LOCALID_MOM, Arnold_PlayersHouse_1F_Movement_MomApproachPlayer
    waitmovement 0
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
    waitmovement 0
	delay 20
	msgbox Arnold_PlayersHouse_1F_Text_DadShouldStayLonger, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SYS_TV_LATIAS_LATIOS
	special TurnOnTVScreen
	delay 60
	applymovement LOCALID_MOM, Arnold_PlayersHouse_1F_Movement_MomNoticesLatiBroadcast
    waitmovement 0
	msgbox Arnold_PlayersHouse_1F_Text_IsThatABreakingStory, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Arnold_PlayersHouse_1F_Movement_PlayerApproachTVForLati
    waitmovement 0
    applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterLeft
    waitmovement 0
	msgbox Arnold_PlayersHouse_1F_Text_LatiEmergencyNewsFlash, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_SYS_TV_LATIAS_LATIOS
	setflag FLAG_LATIOS_OR_LATIAS_ROAMING
	special TurnOffTVScreen
	applymovement LOCALID_MOM, Arnold_PlayersHouse_1F_Movement_MomApproachPlayerAfterTV
    waitmovement 0
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
    waitmovement 0
	msgbox Arnold_PlayersHouse_1F_Text_WhatColorDidTheySay, MSGBOX_DEFAULT
	multichoice 22, 8, MULTI_TV_LATI, TRUE
	copyvar VAR_0x8004, VAR_RESULT
	special InitRoamer
	copyvar VAR_ROAMER_POKEMON, VAR_RESULT
	msgbox Arnold_PlayersHouse_1F_Text_StillUnknownPokemon, MSGBOX_DEFAULT
	closemessage
	setvar VAR_ARNOLD_HOUSES_STATE, 4
	releaseall
	end

@ Never called.
Arnold_PlayersHouse_1F_EventScript_AirLatiBroadcast::
	setflag FLAG_SYS_TV_LATIAS_LATIOS
	return

Arnold_EventScript_RunningShoesManual::
	msgbox PlayersHouse_1F_Text_RunningShoesManual, MSGBOX_SIGN
	end

@Movement
	
Arnold_PlayersHouse_1F_Movement_PlayerWalkIn:
	walk_up
	step_end

Arnold_PlayersHouse_1F_Movement_MomApproachDad:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_in_place_faster_right
	step_end

Arnold_PlayersHouse_1F_Movement_MomApproachPlayer:
	walk_right
	step_end

Arnold_PlayersHouse_1F_Movement_MomNoticesLatiBroadcast:
	walk_in_place_faster_left
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_right
	delay_16
	delay_16
	step_end

Arnold_PlayersHouse_1F_Movement_MomApproachPlayerAfterTV:
	walk_up
	walk_left
	walk_left
	step_end

Arnold_PlayersHouse_1F_Movement_MomMakeRoomToSeeTV:
	walk_left
	walk_in_place_faster_right
	step_end

Arnold_PlayersHouse_1F_Movement_MomReturnToSeat:
	walk_left
	walk_down
	walk_in_place_faster_right
	step_end

Arnold_PlayersHouse_1F_Movement_PlayerApproachTVForGym:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

Arnold_PlayersHouse_1F_Movement_PlayerMoveToTV:
	walk_left
	step_end

Arnold_PlayersHouse_1F_Movement_MovePlayerAwayFromDoor:
	walk_up
	step_end

Arnold_PlayersHouse_1F_Movement_DadApproachPlayer:
	walk_right
	walk_right
	step_end

Arnold_PlayersHouse_1F_Movement_DadFaceMom:
	face_left
	step_end

Arnold_PlayersHouse_1F_Movement_DadExits:
	walk_down
	walk_right
	walk_down
	delay_8
	step_end

Arnold_PlayersHouse_1F_Movement_PlayerEnterRoom:
	delay_16
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

Arnold_PlayersHouse_1F_Movement_MomAndPlayerWatchDadExit:
	delay_8
	delay_16
	delay_16
	walk_in_place_faster_down
	step_end

Arnold_PlayersHouse_1F_Movement_PlayerApproachTVForLati:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

@Text

Arnold_PlayersHouse_1F_Text_IsntItNiceInHere:
	.string "MOM: See, {PLAYER}?\n"
	.string "Isn't it nice in here, too?$"

Arnold_PlayersHouse_1F_Text_MoversPokemonGoSetClock:
	.string "The mover's POKéMON do all the work\n"
	.string "of moving us in and cleaning up after.\l"
	.string "This is so convenient!\p"
	.string "{PLAYER}, your room is upstairs.\n"
	.string "Go check it out, dear!\p"
	.string "DAD bought you a new clock to mark\n"
	.string "our move here.\l"
	.string "Don't forget to set it!$"

Arnold_PlayersHouse_1F_Text_ArentYouInterestedInRoom:
	.string "MOM: Well, {PLAYER}?\p"
	.string "Aren't you interested in seeing your\n"
	.string "very own room?$"

Arnold_PlayersHouse_1F_Text_GoSetTheClock:
	.string "MOM: {PLAYER}.\p"
	.string "Go set the clock in your room, honey.$"

Arnold_PlayersHouse_1F_Text_OhComeQuickly:
	.string "MOM: Oh! {PLAYER}, {PLAYER}!\n"
	.string "Quick! Come quickly!$"

Arnold_PlayersHouse_1F_Text_MaybeDadWillBeOn:
	.string "MOM: Look! It's ANNAPOLIS GYM!\n"
	.string "Maybe DAD will be on!$"

Arnold_PlayersHouse_1F_Text_ItsOverWeMissedHim:
	.string "MOM: Oh… It's over.\p"
	.string "I think DAD was on, but we missed him.\n"
	.string "Too bad.$"

Arnold_PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor:
	.string "Oh, yes.\n"
	.string "One of DAD's friends lives in town.\p"
	.string "PROF. BIRCH is his name.\p"
	.string "He lives right next door, so you should\n"
	.string "go over and introduce yourself.$"

Arnold_PlayersHouse_1F_Text_SeeYouHoney:
	.string "MOM: See you, honey!$"

Arnold_PlayersHouse_1F_Text_DidYouMeetProfBirch:
	.string "MOM: Did you introduce yourself to\n"
	.string "PROF. BIRCH?$"

Arnold_PlayersHouse_1F_Text_YouShouldRestABit:
	.string "MOM: How are you doing, {PLAYER}?\n"
	.string "You look a little tired.\p"
	.string "I think you should rest a bit.$"

Arnold_PlayersHouse_1F_Text_TakeCareHoney:
	.string "MOM: Take care, honey!$"

Arnold_PlayersHouse_1F_Text_GotDadsBadgeHeresSomethingFromMom:
	.string "MOM: Oh? Did DAD give you that BADGE?\p"
	.string "Then here's something from your MOM!$"

Arnold_PlayersHouse_1F_Text_DontPushYourselfTooHard:
	.string "Don't push yourself too hard, dear.\n"
	.string "You can always come home.\p"
	.string "Go for it, honey!$"

Arnold_PlayersHouse_1F_Text_IsThatAPokenav:
	.string "MOM: What is that, honey? A POKéNAV?\n"
	.string "Someone from DEVON gave it to you?\p"
	.string "Well, honey, how about registering\n"
	.string "your mom?\p"
	.string "… … …$"

Arnold_PlayersHouse_1F_Text_RegisteredMom:
	.string "Registered MOM\n"
	.string "in the POKéNAV.$"

Arnold_PlayersHouse_1F_Text_Vigoroth1:
	.string "Fugiiiiih!$"

Arnold_PlayersHouse_1F_Text_Vigoroth2:
	.string "Huggoh, uggo uggo…$"

Arnold_PlayersHouse_1F_Text_ReportFromPetalburgGym:
	.string "INTERVIEWER: …We brought you this\n"
	.string "report from in front of ANNAPOLIS GYM.$"

Arnold_PlayersHouse_1F_Text_TheresAMovieOnTV:
	.string "There is a movie on TV.\p"
	.string "Two men are dancing on a big piano\n"
	.string "keyboard.\p"
	.string "Better get going!$"

Arnold_PlayersHouse_1F_Text_RunningShoesManual:
	.string "It's the instruction booklet for the\n"
	.string "RUNNING SHOES.\p"
	.string "“Press the B Button to run while\n"
	.string "wearing your RUNNING SHOES.\p"
	.string "“Lace up your RUNNING SHOES and hit\n"
	.string "the road running!”$"

Arnold_PlayersHouse_1F_Text_TicketFromBrineyCameForYou:
	.string "DAD: Hm?\p"
	.string "Hey, it's {PLAYER}!\p"
	.string "It's been a while since I saw you,\n"
	.string "but you look…stronger, somehow.\p"
	.string "That's the impression I get.\n"
	.string "But your old man hasn't given up yet!\p"
	.string "Oh, yes, I have something for you.\n"
	.string "This came to you from someone named\l"
	.string "MR. BRINEY.$"

Arnold_PlayersHouse_1F_Text_PortsInSlateportLilycove:
	.string "DAD: Hm, a TICKET for a ferry?\p"
	.string "If I recall, there are ferry ports in\n"
	.string "BALTIMORE and KENT ISLAND.$"

Arnold_PlayersHouse_1F_Text_BetterGetBackToGym:
	.string "I'd better get back to ANNAPOLIS GYM.\p"
	.string "MOM, thanks for looking after the house\n"
	.string "while I'm away.$"

Arnold_PlayersHouse_1F_Text_DadShouldStayLonger:
	.string "MOM: That DAD of yours…\p"
	.string "He comes home for the first time in a\n"
	.string "while, but all he talks about is POKéMON.\p"
	.string "He should relax and stay a little longer.$"

Arnold_PlayersHouse_1F_Text_IsThatABreakingStory:
	.string "MOM: Is that a breaking news story?$"

Arnold_PlayersHouse_1F_Text_LatiEmergencyNewsFlash:
	.string "We bring you this emergency\n"
	.string "news flash!\p"
	.string "In various HOENN locales, there have\n"
	.string "been reports of a BZZT…colored\l"
	.string "POKéMON in flight.\p"
	.string "The identity of this POKéMON is\n"
	.string "currently unknown.\p"
	.string "We now return you to the regular\n"
	.string "movie program.$"

Arnold_PlayersHouse_1F_Text_WhatColorDidTheySay:
	.string "MOM: {PLAYER}, did you catch that?\p"
	.string "What color did the announcer say\n"
	.string "that POKéMON was?$"

Arnold_PlayersHouse_1F_Text_StillUnknownPokemon:
	.string "MOM: Well, isn't that something!\n"
	.string "There are still unknown POKéMON.$"
