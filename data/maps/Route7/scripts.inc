Route7_MapScripts::
	.byte 0

Route7_EventScript_Caroline::
	trainerbattle_single TRAINER_CAROLINE, Route7_Text_CarolineIntro, Route7_Text_CarolineDefeat
	msgbox Route7_Text_CarolinePostBattle, MSGBOX_AUTOCLOSE
	end

Route7_EventScript_Shelby::
	trainerbattle_single TRAINER_SHELBY, Route7_Text_ShelbyIntro, Route7_Text_ShelbyDefeat
	msgbox Route7_Text_ShelbyPostBattle, MSGBOX_AUTOCLOSE
	end

Route7_EventScript_Violet::
	trainerbattle_single TRAINER_VIOLET, Route7_Text_VioletIntro, Route7_Text_VioletDefeat
	msgbox Route7_Text_VioletPostBattle, MSGBOX_AUTOCLOSE
	end

Route7_EventScript_Sanford::
	trainerbattle_single TRAINER_SANFORD, Route7_Text_SanfordIntro, Route7_Text_SanfordDefeat
	msgbox Route7_Text_SanfordPostBattle, MSGBOX_AUTOCLOSE
	end

Route7_EventScript_Darrell::
	trainerbattle_single TRAINER_DARRELL, Route7_Text_DarrellIntro, Route7_Text_DarrellDefeat
	msgbox Route7_Text_DarrellPostBattle, MSGBOX_AUTOCLOSE
	end

Route7_EventScript_Doris::
	trainerbattle_single TRAINER_DORIS, Route7_Text_DorisIntro, Route7_Text_DorisDefeat
	msgbox Route7_Text_DorisPostBattle, MSGBOX_AUTOCLOSE
	end
