KentIsland_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, KentIsland_OnTransition
    map_script MAP_SCRIPT_ON_RESUME, KentIsland_OnResume
    .byte 0

KentIsland_OnTransition:
    setflag FLAG_VISITED_KENT_ISLAND
    end

KentIsland_OnResume:
    setstepcallback STEP_CB_PACIFIDLOG_BRIDGE
    end
