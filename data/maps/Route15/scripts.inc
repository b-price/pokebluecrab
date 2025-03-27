Route15_MapScripts::
    map_script MAP_SCRIPT_ON_RESUME, Route15_OnResume
	.byte 0

Route15_OnResume:
	setstepcallback STEP_CB_ASH
	end
