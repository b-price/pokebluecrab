Route2_MapScripts::
	.byte 0
	
Route2_EventScript_Joey::
	trainerbattle_single TRAINER_JOEY, Route2_Text_JoeyIntro, Route2_Text_JoeyDefeat
	msgbox Route2_Text_JoeyPostBattle, MSGBOX_AUTOCLOSE
	end
	
Route2_EventScript_Matt::
	trainerbattle_single TRAINER_MATT, Route2_Text_MattIntro, Route2_Text_MattDefeat
	msgbox Route2_Text_MattPostBattle, MSGBOX_AUTOCLOSE
	end
	
Route2_EventScript_Sally::
	trainerbattle_single TRAINER_SALLY, Route2_Text_SallyIntro, Route2_Text_SallyDefeat
	msgbox Route2_Text_SallyPostBattle, MSGBOX_AUTOCLOSE
	end
	
Route2_EventScript_Noe::
	trainerbattle_single TRAINER_NOE, Route2_Text_NoeIntro, Route2_Text_NoeDefeat
	msgbox Route2_Text_NoePostBattle, MSGBOX_AUTOCLOSE
	end
	
Route2_EventScript_Sonya::
	trainerbattle_single TRAINER_SONYA, Route2_Text_SonyaIntro, Route2_Text_SonyaDefeat
	msgbox Route2_Text_SonyaPostBattle, MSGBOX_AUTOCLOSE
	end
	
Route2_EventScript_Eloy::
	trainerbattle_single TRAINER_ELOY, Route2_Text_EloyIntro, Route2_Text_EloyDefeat
	msgbox Route2_Text_EloyPostBattle, MSGBOX_AUTOCLOSE
	end

Route2_EventScript_RouteSignAnnapolis::
	msgbox Route2_Text_RouteSignAnnapolis, MSGBOX_SIGN
	end

Route2_EventScript_RouteSignArnold::
	msgbox Route2_Text_RouteSignArnold, MSGBOX_SIGN
	end
	
Route2_Text_RouteSignAnnapolis:
	.string "ROUTE 2\n"
	.string "{DOWN_ARROW} ANNAPOLIS$"

Route2_Text_RouteSignArnold:
	.string "ROUTE 2\n"
	.string "{UP_ARROW} ARNOLD$"
