"GameMenu"
{
	"1"
	{
		"label" "UNPAUSE"
		"command" "ResumeGame"
		"OnlyInGame" "1"
	}
	"2"
	{
		"label" "RETURN TO MAIN MENU"
		"command" "engine save quick;disconnect"
		"OnlyInGame" "1"
	}
	"4"
	{
		"label" ""
		"command" ""
		"OnlyInGame" "1"
	}
	"5"
	{
		"label" "NEW GAME"
		"command" "OpenNewGameDialog"
		"notmulti" "1"
	}
	"6"
	{
		"label" "LOAD GAME"
		"command" "OpenLoadGameDialog"
		"notmulti" "1"
	}
	"7"
	{
		"label" "SAVE GAME"
		"command" "OpenSaveGameDialog"
		"notmulti" "1"
		"OnlyInGame" "1"
	}
	"8"
	{
		"label" ""
		"command" ""
		"notmulti" "1"
	}
//	"11"
//	{
//		"name" "LoadDemo"
//		"label" "#GameUI_GameMenu_PlayDemo"
//		"command" "OpenLoadDemoDialog"
//	}
	"14"
	{
		"label" "OPTIONS"
		"command" "OpenOptionsDialog"
	}
	"15"
	{
		"label" "QUIT"
		"command" "Quit"
	}
	"20"
	{
		"label" "CHANGE GAME/MOD"
		"command" "OpenChangeGameDialog"
	}
}