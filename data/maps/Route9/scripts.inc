Route9_MapScripts::
	.byte 0

Route9_EventScript_Adam::
	trainerbattle_single TRAINER_ADAM, Route9_Text_AdamIntro, Route9_Text_AdamDefeat
	msgbox Route9_Text_AdamPostBattle, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_PamCece::
	trainerbattle_single TRAINER_PAM_AND_CECE, Route9_Text_PamCeceIntro, Route9_Text_PamCeceDefeat
	msgbox Route9_Text_PamCecePostBattle, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Buck::
	trainerbattle_single TRAINER_BUCK, Route9_Text_BuckIntro, Route9_Text_BuckDefeat
	msgbox Route9_Text_BuckPostBattle, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Candice::
	trainerbattle_single TRAINER_CANDICE, Route9_Text_CandiceIntro, Route9_Text_CandiceDefeat
	msgbox Route9_Text_CandicePostBattle, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Anna::
	trainerbattle_single TRAINER_ANNA, Route9_Text_AnnaIntro, Route9_Text_AnnaDefeat
	msgbox Route9_Text_AnnaPostBattle, MSGBOX_AUTOCLOSE
	end


