Route5_MapScripts::
	.byte 0

Route5_EventScript_Alphonso::
	trainerbattle_single TRAINER_ALPHONSO, Route5_Text_AlphonsoIntro, Route5_Text_AlphonsoDefeat
	msgbox Route5_Text_AlphonsoPostBattle, MSGBOX_AUTOCLOSE
	end

Route5_EventScript_Minh::
	trainerbattle_single TRAINER_MINH, Route5_Text_MinhIntro, Route5_Text_MinhDefeat
	msgbox Route5_Text_MinhPostBattle, MSGBOX_AUTOCLOSE
	end

Route5_EventScript_Gerald::
	trainerbattle_single TRAINER_GERALD, Route5_Text_GeraldIntro, Route5_Text_GeraldDefeat
	msgbox Route5_Text_GeraldPostBattle, MSGBOX_AUTOCLOSE
	end
