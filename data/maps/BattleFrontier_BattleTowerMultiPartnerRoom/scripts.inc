BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts_MAP_SCRIPT_ON_RESUME
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts_MAP_SCRIPT_ON_RESUME:
	pyramid_resetparty
	end

BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_1
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_2
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_3
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_4
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_5
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_6
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_1
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_2
	tower_loadpartners
	end

BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE:
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom
	.2byte 0


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_3, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_4, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_5, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_6, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_7, OBJ_EVENT_GFX_BOY_1
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_3, 1
	setobjectxyperm 1, 10, 2
	end


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom::
	lockall
	setvar VAR_TEMP_3, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator
	end


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom
	waitmovement 0
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit
	waitmovement 0
	copyobjectxytoperm LOCALID_ATTENDANT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner, MSGBOX_DEFAULT
	special HealPlayerParty
	setvar VAR_TEMP_1, 1
	releaseall
	end


BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom:
	walk_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit:
	walk_left
	walk_in_place_faster_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Attendant::
	lock
	faceplayer
	message BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2, MSGBOX_DEFAULT
	release
	end


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge::
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost
	end


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator::
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 10, 1
	waitdooranim
	call BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator
	closedoor 10, 1
	waitdooranim
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR, 1, 6
	waitstate
	releaseall
	end


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator
	waitmovement 0
	return


BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast:
	walk_right
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest:
	walk_left
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner1::
	lock
	faceplayer
	setvar VAR_TEMP_2, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner::
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_INTRO
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON1
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON2_ASK
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_3
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_4
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_1:
	tower_dopartnermsg PARTNER_MSGID_ACCEPT
	waitmessage
	waitbuttonpress
	closemessage
	call_if_ne VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth
	removeobject VAR_LAST_TALKED
	setflag FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_TOWER_MULTI_PARTNER_ROOM, 10, 3
	waitstate
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_3:
	call BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_1

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_4:
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_1


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner::
	tower_dopartnermsg PARTNER_MSGID_REJECT
	waitmessage
	waitbuttonpress
	release
	end


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit
	waitmovement 0
	return


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth
	waitmovement 0
	return


BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner2::
	lock
	faceplayer
	setvar VAR_TEMP_2, 1
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner3::
	lock
	faceplayer
	setvar VAR_TEMP_2, 2
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner4::
	lock
	faceplayer
	setvar VAR_TEMP_2, 3
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner5::
	lock
	faceplayer
	setvar VAR_TEMP_2, 4
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner6::
	lock
	faceplayer
	setvar VAR_TEMP_2, 5
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner7::
	lock
	faceplayer
	setvar VAR_TEMP_2, 6
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end


BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner8::
	lock
	faceplayer
	setvar VAR_TEMP_2, 7
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end


BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner::
	.string "Please find a partner from out of the\n"
	.string "TRAINERS gathered here.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner::
	.string "{PLAYER}, you have not found a\n"
	.string "partner for your tag team. Would you\l"
	.string "like to quit looking and return to the\l"
	.string "reception counter?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2::
	.string "Then, please find a partner from the\n"
	.string "TRAINERS gathered here.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner::
	.string "Thank you for choosing a partner. I will\n"
	.string "now show you to your MULTI BATTLE\l"
	.string "ROOM.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Intro::
	.string "I'm {STR_VAR_1}'s no. {STR_VAR_2}\n"
	.string "apprentice. You can call me\l"
	.string "{STR_VAR_3}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon1::
	.string "On {STR_VAR_1}'s advice, I brought\n"
	.string "one {STR_VAR_3} with\l"
	.string "{STR_VAR_2} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. Please, let me join you\l"
	.string "as a tag team.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Accept::
	.string "Thank you! I'll go register right now.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Reject::
	.string "I really wanted to form a tag team with\n"
	.string "you, {PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Intro::
	.string "I am {STR_VAR_1}'s no.\n"
	.string "{STR_VAR_2} apprentice. My name is\l"
	.string "{STR_VAR_3}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon1::
	.string "I got advice from {STR_VAR_1} and\n"
	.string "chose one {STR_VAR_3} with\l"
	.string "{STR_VAR_2} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. Please, let's form a\l"
	.string "tag team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Accept::
	.string "Thank you very much! I'll be done with\n"
	.string "registration quickly!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Reject::
	.string "{PLAYER}, I was hoping that I could\n"
	.string "partner up with you…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Intro::
	.string "Um, my name's {STR_VAR_3}, and I'm\n"
	.string "{STR_VAR_1}'s no. {STR_VAR_2}\l"
	.string "apprentice. Snivel… I'm sorry! This\l"
	.string "tension is making me cry…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon1::
	.string "{STR_VAR_3} advised me, so I have\n"
	.string "one {STR_VAR_2} with\l"
	.string "{STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. Snivel… Please, please\l"
	.string "team up with me!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Accept::
	.string "Oh, really? You will? Awesome! Wicked!\n"
	.string "Awoooh! Oh… I'm sorry… I'm so happy, I'm\l"
	.string "crying… I'll go register right away.\l"
	.string "Please don't go away!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Reject::
	.string "Oh, b-but… Sob… Waaaaah!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Intro::
	.string "Hi, there! I'm {STR_VAR_3}! I'm\n"
	.string "{STR_VAR_1}'s no. {STR_VAR_2}\l"
	.string "apprentice!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon1::
	.string "{STR_VAR_3} recommended my crew.\n"
	.string "One {STR_VAR_2} with\l"
	.string "{STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}, that's what I have!\l"
	.string "Cool, huh? So come on! Let's form a tag\l"
	.string "team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Accept::
	.string "Yay! Great! Okay, I'll go register, okay?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Reject::
	.string "Aww, why? I wanted to team up,\n"
	.string "{PLAYER}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Intro::
	.string "I'm {STR_VAR_3}, the no.\n"
	.string "{STR_VAR_2} apprentice of the\l"
	.string "famous {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon1::
	.string "I looked to {STR_VAR_3} for advice.\n"
	.string "One {STR_VAR_1}-using\l"
	.string "{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon2Ask::
	.string "and one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}, that's my pair. Please,\l"
	.string "will you join me in a tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Accept::
	.string "Thank you! I'll register right away!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Reject::
	.string "{PLAYER}, I had been hoping to join\n"
	.string "you in a tag team…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Intro::
	.string "Um… I'm sincerely happy that you would\n"
	.string "take the time to talk to me. I'm\l"
	.string "{STR_VAR_3}. I'm {STR_VAR_1}'s\l"
	.string "no. {STR_VAR_2} apprentice…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon1::
	.string "{STR_VAR_3} gave me advice. I'm very\n"
	.string "grateful for it. I have a team of one\l"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. I know I'm asking a\l"
	.string "lot… I don't think you'll be willing to,\l"
	.string "but may I join you as a partner?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Accept::
	.string "Really? I can't believe it! I can't\n"
	.string "believe you'll let me join you! I… I\l"
	.string "won't let you down! Um… If it's really\l"
	.string "okay, I'll go register right this\l"
	.string "instant!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Reject::
	.string "Oh… I didn't think I was good enough…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Intro::
	.string "Hi, I'm {STR_VAR_3}. I'm\n"
	.string "{STR_VAR_1}'s no. {STR_VAR_2}\l"
	.string "apprentice!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon1::
	.string "{STR_VAR_3} told me that it would be\n"
	.string "good to make this team: one\l"
	.string "{STR_VAR_1}-using {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon2Ask::
	.string "and one {STR_VAR_2} that knows how\n"
	.string "to use {STR_VAR_1}. Not bad, huh?\l"
	.string "Want me to team up with you?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Accept::
	.string "Okay, glad to join you! I hope you won't\n"
	.string "mess things up for me! I'll do my\l"
	.string "registration now.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Reject::
	.string "Huh? Why did you turn me down? You're\n"
	.string "no judge of character!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Intro::
	.string "I'm {STR_VAR_3} and I'm a\n"
	.string "TRIATHLETE. I'm busy every day what\l"
	.string "with jogging, training, and rapping. I\l"
	.string "also happen to be {STR_VAR_1}'s no.\l"
	.string "{STR_VAR_2} apprentice.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon1::
	.string "This is what {STR_VAR_3}\n"
	.string "recommended. One\l"
	.string "{STR_VAR_1}-using {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon2Ask::
	.string "and one {STR_VAR_1}-using\n"
	.string "{STR_VAR_2}. I put a lot of effort\l"
	.string "into raising them, even though I'm\l"
	.string "busy. Let's form a tag team and give it\l"
	.string "a go!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Accept::
	.string "Thanks, that's the spirit! Hang tight\n"
	.string "while I go register, okay?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Reject::
	.string "I took time from my busy schedule to be\n"
	.string "here! Give me a break!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Intro::
	.string "Hi! How's it going? I'm {STR_VAR_3},\n"
	.string "{STR_VAR_1}'s no. {STR_VAR_2}\l"
	.string "apprentice. Glad to meet you!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon1::
	.string "Listen, listen! You have to hear about\n"
	.string "the POKéMON {STR_VAR_3}\l"
	.string "recommended. One {STR_VAR_2} with\l"
	.string "{STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. Of course I raised\l"
	.string "them superbly! So, want to team up? I'm\l"
	.string "sure it'll be a great combo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Accept::
	.string "Yay, I think this will be fun! I'll go\n"
	.string "register!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Reject::
	.string "Oh, you're mean! I come recommended,\n"
	.string "you know.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Intro::
	.string "Please let me introduce myself. I am\n"
	.string "{STR_VAR_3}. I serve as\l"
	.string "{STR_VAR_1}'s no. {STR_VAR_2}\l"
	.string "apprentice.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon1::
	.string "I sought the sage advice of\n"
	.string "{STR_VAR_3} and raised my team of\l"
	.string "one {STR_VAR_2} with\l"
	.string "{STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon2Ask::
	.string "and one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. Please agree to a tag\l"
	.string "team with me!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Accept::
	.string "Oh… I'm delighted! I promise to give you\n"
	.string "my best! Of course I will register us!\l"
	.string "Please wait!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Reject::
	.string "I had been hoping to join you,\n"
	.string "{PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Intro::
	.string "Eek! You spoke to me! I… I'm overjoyed!\n"
	.string "I'm {STR_VAR_3}! I'm\l"
	.string "{STR_VAR_1}'s no. {STR_VAR_2}\l"
	.string "apprentice!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon1::
	.string "On {STR_VAR_3}'s advice, I trained\n"
	.string "one {STR_VAR_1}-using\l"
	.string "{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon2Ask::
	.string "and one {STR_VAR_1}-using\n"
	.string "{STR_VAR_2}. Please, can you grant\l"
	.string "me my wish? I want to be your tag-team\l"
	.string "partner!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Accept::
	.string "Eek! I… I feel giddy! Thank you so much!\n"
	.string "I'll go register us right away!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Reject::
	.string "Waaah! Don't you feel any pity? But\n"
	.string "that makes you cooler…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Intro::
	.string "Yeehaw! I'm {STR_VAR_1}'s no.\n"
	.string "{STR_VAR_2} apprentice!\l"
	.string "{STR_VAR_3}'s my name, hello, hello!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon1::
	.string "My mentor {STR_VAR_3} recommended\n"
	.string "one {STR_VAR_1}-master\l"
	.string "{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon2Ask::
	.string "and one {STR_VAR_1}-master\n"
	.string "{STR_VAR_2}. Good stuff, huh? You'll\l"
	.string "partner with me, won't you?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Accept::
	.string "Okay, excellent! I'll get the\n"
	.string "registration done quickly!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Reject::
	.string "Gwaaah! You're a calculating one,\n"
	.string "{PLAYER}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Intro::
	.string "Hey! There's big trouble! This is the\n"
	.string "BATTLE TOWER's last day! … … … … … … I'm\l"
	.string "only joking! People call me\l"
	.string "{STR_VAR_3} and I do, too! I'm\l"
	.string "{STR_VAR_1}'s 1,000th apprentice!\l"
	.string "Actually, I'm no. {STR_VAR_2}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon1::
	.string "{STR_VAR_3} gave me some advice.\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon2Ask::
	.string "{STR_VAR_2} with {STR_VAR_1}.\n"
	.string "I've got ten of each kind! Actually,\l"
	.string "just one of each! How about it? Want to\l"
	.string "try tag battles with me?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Accept::
	.string "Yippee! I'll give you a POKéMON as my\n"
	.string "thanks! Just joking! But I will really\l"
	.string "go do the registration, okay?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Reject::
	.string "Oh, that's so cold! I'll have to wreck\n"
	.string "the BATTLE TOWER for that! Of course I\l"
	.string "won't!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Intro::
	.string "Hey, there, I'm rockin' and a-rollin'!\n"
	.string "POKéMON, I be controllin'! I'm\l"
	.string "{STR_VAR_3} the rappin' SAILOR.\l"
	.string "Don't be mistakin' me for no wailer! I'm\l"
	.string "{STR_VAR_1}'s no. {STR_VAR_2}\l"
	.string "apprentice. Me, you shouldn't be quick\l"
	.string "to dismiss!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon1::
	.string "With the advice of {STR_VAR_3} I did\n"
	.string "abide, put together my team of pride!\l"
	.string "One {STR_VAR_1}-using\l"
	.string "{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon2Ask::
	.string "and one {STR_VAR_1}-using\n"
	.string "{STR_VAR_2}! Our meeting we should\l"
	.string "commemorate, with a tag-team victory\l"
	.string "to celebrate!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Accept::
	.string "Hey, hey, I like your style! Our\n"
	.string "registration, I will go file!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Reject::
	.string "Oh, hey, {PLAYER}, now that's cold! If\n"
	.string "I may be so bold!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Intro::
	.string "Yippee-yahoo! Oh, don't run! I was just\n"
	.string "having fun! Howdy! I'm {STR_VAR_3}!\l"
	.string "I'm {STR_VAR_1}'s no.\l"
	.string "{STR_VAR_2} apprentice!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon1::
	.string "{STR_VAR_3} told me what to do. So\n"
	.string "one {STR_VAR_1}-using\l"
	.string "{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon2Ask::
	.string "and one {STR_VAR_1}-using\n"
	.string "{STR_VAR_2}, I did choose. So, what\l"
	.string "do you say? Come on, make my day!\l"
	.string "Please, I'm begging you! Let me join\l"
	.string "you, don't leave me blue!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Accept::
	.string "Yeahah! Luck is with me! It sure makes\n"
	.string "me happy! Before we go join the fray,\l"
	.string "I'll go register right away!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Reject::
	.string "You're turning me down? {PLAYER},\n"
	.string "you're making me frown!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Intro::
	.string "Cough! Oh, sorry, I have a cold. My\n"
	.string "POKéMON are fine, though. My name's\l"
	.string "{STR_VAR_3}, {STR_VAR_1}'s no.\l"
	.string "{STR_VAR_2} apprentice. Cough!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon1::
	.string "I took {STR_VAR_3}'s advice to\n"
	.string "heart and put together my team of one\l"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. I trained them every\l"
	.string "day, even in wind and rain. That's why I\l"
	.string "have this cold, I think. That's what I'm\l"
	.string "about. Want to be my tag partner?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Accept::
	.string "Thanks, I appreciate this! Cough,\n"
	.string "cough! Hang on while I go register.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Reject::
	.string "Oh, you won't? {PLAYER}, I think we'd\n"
	.string "make a good pair.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Intro::
	.string "Oh, hello! This is nerve-racking. I'm\n"
	.string "{STR_VAR_3}. I'm the no.\l"
	.string "{STR_VAR_2} apprentice of\l"
	.string "{STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon1::
	.string "{STR_VAR_3} said this team'll be\n"
	.string "good-- one {STR_VAR_2} with\l"
	.string "{STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. I'm feeling\l"
	.string "self-conscious about this, but will you\l"
	.string "let me join you?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Accept::
	.string "Oh, gee, thank you! I feel bashful, but\n"
	.string "I'll do my best! I'll go get the\l"
	.string "registration done.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Reject::
	.string "Oh, please don't say no! I feel\n"
	.string "self-conscious enough already…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Intro::
	.string "I am {STR_VAR_3}, and that's no lie. I\n"
	.string "am {STR_VAR_1}'s no. {STR_VAR_2}\l"
	.string "apprentice.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon1::
	.string "{STR_VAR_3} recommended my team.\n"
	.string "Since the advice sounded sincere, I\l"
	.string "decided to bring with me my\l"
	.string "{STR_VAR_1}-using {STR_VAR_2}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon2Ask::
	.string "my {STR_VAR_1}-using\n"
	.string "{STR_VAR_2}. If possible, I would\l"
	.string "like you to accept me as your tag-team\l"
	.string "partner.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Accept::
	.string "You really will accept me? It would be\n"
	.string "too terrible otherwise. But since\l"
	.string "you've agreed, this is fine. I shall go\l"
	.string "register the both of us.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Reject::
	.string "Hm? Now why would you refuse? Is this\n"
	.string "your idea of a joke?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassIntro::
	.string "I'm {STR_VAR_1}, and I'm a LASS!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon1::
	.string "What I have are one {STR_VAR_2}\n"
	.string "that uses {STR_VAR_1} and one$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon2Ask::
	.string "{STR_VAR_2} that uses\n"
	.string "{STR_VAR_1}. Those are what I have\l"
	.string "with me. Will you be my partner?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassAccept::
	.string "Thank you! I'll go do the registration!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassReject::
	.string "You don't want to be my partner? You'll\n"
	.string "regret it later!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterIntro::
	.string "Hello! I'm YOUNGSTER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon1::
	.string "Want to know what I have? One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! You'll be my tag-team\l"
	.string "partner, won't you?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterAccept::
	.string "Yay! I'll go and register, okay?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterReject::
	.string "Aww! If you'd form a tag team with my\n"
	.string "POKéMON, we'd be unstoppable!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerIntro::
	.string "Yahoo! I'm HIKER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon1::
	.string "Know what I have with me? My\n"
	.string "{STR_VAR_1}-using {STR_VAR_2}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon2Ask::
	.string "my {STR_VAR_1}-using\n"
	.string "{STR_VAR_2}! Sounds good, eh? Want\l"
	.string "to form a tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerAccept::
	.string "Yahoo! I'll go do the registering, then.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerReject::
	.string "I would've liked to battle with you at\n"
	.string "my side.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyIntro::
	.string "Hello! I'm {STR_VAR_1}, and I'm a\n"
	.string "BEAUTY!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon1::
	.string "Do you know what I've been raising? One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! What do you think?\l"
	.string "Want to make a tag team together?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyAccept::
	.string "Wonderful! I'll get the registration\n"
	.string "done now!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyReject::
	.string "How disappointing! We two together--we\n"
	.string "would've been the best!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanIntro::
	.string "Yo! You know who I am? I'm\n"
	.string "{STR_VAR_1} the FISHERMAN!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon1::
	.string "I've got with me a team of one\n"
	.string "{STR_VAR_1}-using {STR_VAR_2}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon2Ask::
	.string "one {STR_VAR_1}-using\n"
	.string "{STR_VAR_2}. So, how about it? Will\l"
	.string "you battle at my side?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanAccept::
	.string "Good, good! Leave it up to me! I'll go\n"
	.string "and register us now.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanReject::
	.string "We matched up perfectly, too…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyIntro::
	.string "Glad to make your acquaintance. I am\n"
	.string "{STR_VAR_1}, a LADY.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon1::
	.string "I am accompanied by a team of one\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. I hope I meet your\l"
	.string "approval. For I wish to have you as my\l"
	.string "partner.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyAccept::
	.string "I thank you sincerely. I shall handle\n"
	.string "the registration.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyReject::
	.string "I'm sure that you will regret not having\n"
	.string "me as your partner.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFIntro::
	.string "I'm TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon1::
	.string "What I have… One {STR_VAR_2} with\n"
	.string "{STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! That's my pair!\l"
	.string "Please? Will you form a tag team with\l"
	.string "me?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFAccept::
	.string "Gee, thanks! I'll go register at the\n"
	.string "counter.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFReject::
	.string "We two together, we would've been tough\n"
	.string "for certain!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherIntro::
	.string "Hiya! I'm BUG CATCHER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon1::
	.string "Check out what I have! One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! So, listen! Do you want\l"
	.string "to form a tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherAccept::
	.string "Gotcha! I'll go do the registration\n"
	.string "stuff at the counter.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherReject::
	.string "Aww, my POKéMON are awesome. I hope you\n"
	.string "won't regret this!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMIntro::
	.string "Good day! I'm SCHOOL KID\n"
	.string "{STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon1::
	.string "What I've been raising are one\n"
	.string "{STR_VAR_2} that uses\l"
	.string "{STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon2Ask::
	.string "and one {STR_VAR_2} that uses\n"
	.string "{STR_VAR_1}. Not too bad, don't you\l"
	.string "think? Would you care to form a tag\l"
	.string "team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMAccept::
	.string "Thank you very much! I'll get done with\n"
	.string "the registration.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMReject::
	.string "That's too bad… I was hoping that I\n"
	.string "could learn from you as your partner…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyIntro::
	.string "Yo! Let me tell you who I am! I'm RICH\n"
	.string "BOY {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon1::
	.string "Guess what I got! One {STR_VAR_2}\n"
	.string "with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! I'm willing to offer\l"
	.string "you the chance to be in a tag team with\l"
	.string "me.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyAccept::
	.string "Smart move! I'll finish up the\n"
	.string "registration process quick!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyReject::
	.string "You'd turn me of all people down? You'll\n"
	.string "regret that decision for sure!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltIntro::
	.string "Hiyah! I am BLACK BELT {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon1::
	.string "As my companions, I have one\n"
	.string "{STR_VAR_2} using {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon2Ask::
	.string "and one {STR_VAR_2} using\n"
	.string "{STR_VAR_1}. Please, grant me my\l"
	.string "wish! Allow me to be your tag partner!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltAccept::
	.string "Hiyah! I will go register forthwith!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltReject::
	.string "I see… I hope for an opportunity the\n"
	.string "next time we meet…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFIntro::
	.string "Hi, there! I'm {STR_VAR_1}, and I'm a\n"
	.string "TUBER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon1::
	.string "I'll tell you what I have. One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! May I please be on\l"
	.string "your tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFAccept::
	.string "Thank you! I'll go register us now!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFReject::
	.string "If we'd become partners, we could have\n"
	.string "been so strong!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacIntro::
	.string "Greetings… I am HEX MANIAC\n"
	.string "{STR_VAR_1}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon1::
	.string "I bear with me one\n"
	.string "{STR_VAR_1}-using {STR_VAR_2}\l"
	.string "together with one$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon2Ask::
	.string "{STR_VAR_1}-using {STR_VAR_2}…\n"
	.string "I beseech you… Join me in a tag team…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacAccept::
	.string "I thank you… I shall register us…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacReject::
	.string "I so longed to join you…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMIntro::
	.string "How do you do? I'm {STR_VAR_1}, and\n"
	.string "I'm a POKéMON BREEDER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon1::
	.string "I'm raising a couple good ones! One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! How about it? Feel like\l"
	.string "making a tag team with me?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMAccept::
	.string "Thank you kindly! I'll go take care of\n"
	.string "the registration stuff, so you wait\l"
	.string "right here!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMReject::
	.string "I was looking forward to being your\n"
	.string "partner…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFIntro::
	.string "Well, hello! I'm TRIATHLETE\n"
	.string "{STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon1::
	.string "Want to know what I run with? One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! Well? Want to be in a\l"
	.string "tag team with me?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFAccept::
	.string "Good going! I'll be quick and get the\n"
	.string "registration all done!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFReject::
	.string "You and me, we would've been tops. It's\n"
	.string "too bad…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMIntro::
	.string "Hey, there! My name's {STR_VAR_1}!\n"
	.string "I'm a TRIATHLETE!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon1::
	.string "I go on runs with my durable team-- one\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! Not too shabby, huh?\l"
	.string "We should be in a tag team together!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMAccept::
	.string "All right! I'll go register in a flash!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMReject::
	.string "I really wanted to battle as your\n"
	.string "tag-team partner…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlIntro::
	.string "I'm BATTLE GIRL {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon1::
	.string "I've been toughening up one\n"
	.string "{STR_VAR_1}-using {STR_VAR_2}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon2Ask::
	.string "one {STR_VAR_1}-using\n"
	.string "{STR_VAR_2}! Do you like that\l"
	.string "combo? How about you and me join up?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlAccept::
	.string "Why, thanks! I'll get the registration\n"
	.string "done right now!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlReject::
	.string "With you, I thought we could form the\n"
	.string "ultimate tag team…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMIntro::
	.string "I'm TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon1::
	.string "I've been running with one\n"
	.string "{STR_VAR_2} that knows how to use\l"
	.string "{STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon2Ask::
	.string "and one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! We could be in a tag\l"
	.string "team. Wouldn't that be great?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMAccept::
	.string "Thank you! I'll go register us, and\n"
	.string "that's right now!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMReject::
	.string "Aww, that's too bad. We would've been\n"
	.string "the toughest tag team around!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMIntro::
	.string "Me? I'm TUBER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon1::
	.string "What do I have with me? One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! Hey? You'll team up\l"
	.string "with me, right?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMAccept::
	.string "Okay! I'll go register! Let's be\n"
	.string "excellent together!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMReject::
	.string "My POKéMON are tough for sure… It's too\n"
	.string "bad you don't want to team up.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristIntro::
	.string "Yay-hey! Call me GUITARIST\n"
	.string "{STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon1::
	.string "Check out my entourage! One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! Yay-hey! Pretty wild,\l"
	.string "huh? We'll have to do a duet in a tag\l"
	.string "team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristAccept::
	.string "Yay-hey! Right on! I'll do that\n"
	.string "registration stuff now!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristReject::
	.string "My POKéMON rock hard! You'll be sorry, I\n"
	.string "tell you!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanIntro::
	.string "Pleased to meet you. I am\n"
	.string "{STR_VAR_1}, a GENTLEMAN.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon1::
	.string "I am accompanied by my trusted\n"
	.string "{STR_VAR_1}-using {STR_VAR_2}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon2Ask::
	.string "one {STR_VAR_1}-using\n"
	.string "{STR_VAR_2}. May I ask you to join\l"
	.string "me in a tag-team partnership\l"
	.string "arrangement?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanAccept::
	.string "Ah, I thank you for your trust. I shall\n"
	.string "be done with the registration.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanReject::
	.string "That is most unfortunate… I shall look\n"
	.string "forward to the next opportunity…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMIntro::
	.string "Hello, I'm {STR_VAR_1}, and I'm a\n"
	.string "POKéFAN.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon1::
	.string "I have with me now one {STR_VAR_2}\n"
	.string "that knows the move {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. Do you like what you\l"
	.string "see? Why don't you be my tag partner?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMAccept::
	.string "Thank you! I'll look after the\n"
	.string "registration!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMReject::
	.string "My POKéMON are top grade… It's too bad\n"
	.string "you can't appreciate that.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMIntro::
	.string "Hm! I am {STR_VAR_1}, and an EXPERT\n"
	.string "am I!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon1::
	.string "The POKéMON that I've toughened up are\n"
	.string "one {STR_VAR_2} with\l"
	.string "{STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! What say you to a tag\l"
	.string "team with me?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMAccept::
	.string "Hm! I shall register us right away! Let\n"
	.string "us both do our best!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMReject::
	.string "I will hope that your choice is indeed\n"
	.string "correct…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFIntro::
	.string "Hello, hello. I'm {STR_VAR_1}, and I'm\n"
	.string "an EXPERT.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon1::
	.string "I've raised my POKéMON thoroughly. One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}-- they're what I have.\l"
	.string "Wouldn't you like to team up with me?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFAccept::
	.string "Good, good. I'll see to the registration\n"
	.string "right away.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFReject::
	.string "Perhaps we can form a team the next\n"
	.string "time we meet.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerIntro::
	.string "I'm DRAGON TAMER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon1::
	.string "The team I've been toughening up is one\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! How about it? Want to\l"
	.string "be my partner?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerAccept::
	.string "Okay, I'll give it my best! I'll go\n"
	.string "register now, all right?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerReject::
	.string "You're not going to find many tougher\n"
	.string "partners than me!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperIntro::
	.string "I'm BIRD KEEPER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon1::
	.string "What POKéMON do I have? One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. Don't you think we'd\l"
	.string "make a decent tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperAccept::
	.string "Great, thanks! I'll look after the\n"
	.string "registration!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperReject::
	.string "My POKéMON and I are strong. What a\n"
	.string "letdown.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyIntro::
	.string "I'm NINJA BOY {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon1::
	.string "My POKéMON team consists of one\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! Let's be in a tag team\l"
	.string "together!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyAccept::
	.string "Yay! Let me go register!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyReject::
	.string "You'll regret not having my tough\n"
	.string "POKéMON on your side!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyIntro::
	.string "Hello! I'm PARASOL LADY {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon1::
	.string "Escorting me now are my {STR_VAR_2}\n"
	.string "that uses {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon2Ask::
	.string "one {STR_VAR_2} that uses\n"
	.string "{STR_VAR_1}. Aren't they nice? Care\l"
	.string "to join us in a tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyAccept::
	.string "Thanks a bunch! I'll go register at the\n"
	.string "counter. Let's not disappoint each\l"
	.string "other!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyReject::
	.string "My POKéMON are tremendously strong.\n"
	.string "How disappointing…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacIntro::
	.string "Hello. I'm {STR_VAR_1}, and I'm a BUG\n"
	.string "MANIAC!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon1::
	.string "I have found my POKéMON, yes. One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}-- they are what I\l"
	.string "found. Could I interest you in forming\l"
	.string "a tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacAccept::
	.string "Okay! Understood! I won't be long with\n"
	.string "the registration!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacReject::
	.string "With the POKéMON I found, we wouldn't\n"
	.string "have lost…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorIntro::
	.string "Ahoy, there! I'm SAILOR {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon1::
	.string "Let me show you my pride and joy! One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! Of course you're not\l"
	.string "going to turn me down. We will team up,\l"
	.string "right?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorAccept::
	.string "I didn't expect any less! I'll go\n"
	.string "register now.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorReject::
	.string "We would've stormed through the\n"
	.string "opposition! Too bad!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorIntro::
	.string "Hi, I'm {STR_VAR_1}. I'm a COLLECTOR.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon1::
	.string "The jewels in my collection are my\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! Swell, huh? We should\l"
	.string "be in a team together.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorAccept::
	.string "Oh, yeah! Well, let's not waste any time.\n"
	.string "I'll go register the two of us.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorReject::
	.string "Well, that's upsetting. You don't\n"
	.string "appreciate my POKéMON.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMIntro::
	.string "Howdy, I'm {STR_VAR_1}. I'm a\n"
	.string "POKéMON RANGER.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon1::
	.string "Keeping me company are one\n"
	.string "{STR_VAR_1}-using {STR_VAR_2}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! Don't you think we'd\l"
	.string "make an impressive tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMAccept::
	.string "That's super! I'll deal with the\n"
	.string "registration now.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMReject::
	.string "Next time, choose my POKéMON, will you?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFIntro::
	.string "My name's {STR_VAR_1}. I'm a POKéMON\n"
	.string "RANGER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon1::
	.string "Let me tell you about my team. I have\n"
	.string "one {STR_VAR_2} with\l"
	.string "{STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! How would you like to\l"
	.string "form a tag team with my little posse?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFAccept::
	.string "We'll be at our best! I'll get the\n"
	.string "registration done quick!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFReject::
	.string "I hope you'll choose my POKéMON next\n"
	.string "time.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyIntro::
	.string "Pleased to meet you. I'm\n"
	.string "{STR_VAR_1}. I consider myself an\l"
	.string "AROMA LADY.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon1::
	.string "I travel with one {STR_VAR_2} that\n"
	.string "uses {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon2Ask::
	.string "one {STR_VAR_2} that uses\n"
	.string "{STR_VAR_1}. I hope they strike\l"
	.string "your fancy. Would you care to be my\l"
	.string "partner?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyAccept::
	.string "I'm honored by your acceptance. I will\n"
	.string "go register right this instant.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyReject::
	.string "It would be wonderful if we could form a\n"
	.string "tag team the next time we meet.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacIntro::
	.string "Want to know who I am? I'm\n"
	.string "{STR_VAR_1}, the RUIN MANIAC!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon1::
	.string "The POKéMON that I have with me are one\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! Intriguing, eh? How\l"
	.string "about you and I partner up?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacAccept::
	.string "That's a sound decision! I'll go do the\n"
	.string "registration paperwork.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacReject::
	.string "Hmm… I think my POKéMON are tough…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMIntro::
	.string "I'm COOLTRAINER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon1::
	.string "The POKéMON I have right now are one\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. Cool, huh? Don't you\l"
	.string "think it'd be pretty cool if we made a\l"
	.string "tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMAccept::
	.string "Cool! I'll go do the registration in a\n"
	.string "flash!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMReject::
	.string "I thought that we'd make just the\n"
	.string "greatest team ever.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFIntro::
	.string "I'm COOLTRAINER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon1::
	.string "The team I've been raising has one\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. Does that sound okay?\l"
	.string "How about we become tag partners?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFAccept::
	.string "Sounds A-OK! I'd better do the\n"
	.string "registration.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFReject::
	.string "I was thinking how we would be one\n"
	.string "tough team…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacIntro::
	.string "Heyo! I'm {STR_VAR_1}, the\n"
	.string "POKéMANIAC!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon1::
	.string "What does a guy like me have? One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}, that's what! Let's do\l"
	.string "it! We'll stomp around as a tag team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacAccept::
	.string "Good call! I'll register the both of us!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacReject::
	.string "My POKéMON are brutal! It's not my fault\n"
	.string "if you regret this!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerIntro::
	.string "Yo, there! I'm KINDLER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon1::
	.string "You know what my training cooked up?\n"
	.string "One {STR_VAR_2} with\l"
	.string "{STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! Well, what do you say?\l"
	.string "Want to form a tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerAccept::
	.string "All right! I'll get on with the\n"
	.string "registration.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerReject::
	.string "Promise you'll partner up with me the\n"
	.string "next time we run into each other.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperIntro::
	.string "I'm {STR_VAR_1}, and I'm a CAMPER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon1::
	.string "I've been raising one {STR_VAR_1}-\n"
	.string "using {STR_VAR_2} and one$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon2Ask::
	.string "{STR_VAR_1}-using {STR_VAR_2}.\n"
	.string "Do you think it'd be fun to team up? I\l"
	.string "bet it would be!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperAccept::
	.string "Yeah! Off I go to register!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperReject::
	.string "Next time, okay? I want to be on your\n"
	.string "team.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerIntro::
	.string "Hello! I'm {STR_VAR_1}, and I'm a\n"
	.string "PICNICKER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon1::
	.string "The POKéMON I've been taking are one\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. Are you interested in\l"
	.string "joining me on a tag team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerAccept::
	.string "Why, thank you! I will do the\n"
	.string "registration now.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerReject::
	.string "It would be nice if I could join you some\n"
	.string "other time.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMIntro::
	.string "I'm PSYCHIC {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon1::
	.string "The twosome I've been raising are one\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. Would you like to form\l"
	.string "a tag team with me?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMAccept::
	.string "Sure thing! I'll take care of the\n"
	.string "registration!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMReject::
	.string "If we meet again, that's when I'd like to\n"
	.string "team up with you.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFIntro::
	.string "I'm {STR_VAR_1}. I'm a PSYCHIC.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon1::
	.string "One {STR_VAR_2} with\n"
	.string "{STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}-- they're my disciples.\l"
	.string "Doesn't the idea of forming a tag-team\l"
	.string "partnership intrigue you?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFAccept::
	.string "Thank you. I'll go deal with the\n"
	.string "registration.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFReject::
	.string "I hope there will be another chance to\n"
	.string "forge an alliance.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFIntro::
	.string "I'm SCHOOL KID {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon1::
	.string "One {STR_VAR_1}-using\n"
	.string "{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon2Ask::
	.string "and one {STR_VAR_1}-using\n"
	.string "{STR_VAR_2} are my POKéMON pair.\l"
	.string "May I please be your partner on a tag\l"
	.string "team?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFAccept::
	.string "Ooh, thank you! I'll register at the\n"
	.string "counter right away!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFReject::
	.string "Please? May I join you the next time?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFIntro::
	.string "Hiya! The name's {STR_VAR_1}! I'm a\n"
	.string "POKéMON BREEDER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon1::
	.string "The POKéMON I've raised are one\n"
	.string "{STR_VAR_1}-using {STR_VAR_2}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon2Ask::
	.string "one {STR_VAR_1}-using\n"
	.string "{STR_VAR_2}. Sound interesting?\l"
	.string "How about we form a tag team, then?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFAccept::
	.string "All righty! You leave the registration\n"
	.string "to me!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFReject::
	.string "You have to team up with me next time,\n"
	.string "all right?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFIntro::
	.string "I'm {STR_VAR_1}, and I'm proud to say\n"
	.string "that I am a POKéFAN.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon1::
	.string "The darling POKéMON I've raised are one\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}. Aren't they just the\l"
	.string "cutest? We ought to make a team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFAccept::
	.string "Thank you, dear! I'll be on my way to\n"
	.string "register!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFReject::
	.string "My darling POKéMON are the best, I'll\n"
	.string "have you know. How annoying!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFIntro::
	.string "Hi, I'm SWIMMER {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon1::
	.string "One {STR_VAR_1}-using\n"
	.string "{STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon2Ask::
	.string "and one {STR_VAR_1}-using\n"
	.string "{STR_VAR_2} are what I've trained.\l"
	.string "You and me, let's make a tag team.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFAccept::
	.string "That's cool! I'll register the two of us.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFReject::
	.string "If we meet again, you owe me a tag team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMIntro::
	.string "What's happening? I'm {STR_VAR_1},\n"
	.string "and I'm a TRIATHLETE.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon1::
	.string "I got a couple decent POKéMON. One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! It'd be neat if we made\l"
	.string "a tag team together, so how about it?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMAccept::
	.string "Right on! You wait while I register,\n"
	.string "okay?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMReject::
	.string "I expect you'll let me join you next\n"
	.string "time, how's that?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFIntro::
	.string "I'm the TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon1::
	.string "One {STR_VAR_2} with\n"
	.string "{STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon2Ask::
	.string "another {STR_VAR_2} that knows how\n"
	.string "to use {STR_VAR_1}. That's my pair.\l"
	.string "What do you think? We'd make a good\l"
	.string "team, I'd say.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFAccept::
	.string "I like that answer! I'll get done with\n"
	.string "registration fast!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFReject::
	.string "You'll give me another chance to form a\n"
	.string "partnership, won't you?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMIntro::
	.string "Hi, there! Hello! I'm {STR_VAR_1}, and\n"
	.string "I'm a SWIMMER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon1::
	.string "Check out what I've been raising! One\n"
	.string "{STR_VAR_2} with {STR_VAR_1}\l"
	.string "and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon2Ask::
	.string "one {STR_VAR_2} with\n"
	.string "{STR_VAR_1}! Sweet, huh? It'd be\l"
	.string "sweet to form a team, too!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMAccept::
	.string "Much obliged! I'll get this registration\n"
	.string "thing done!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMReject::
	.string "If we meet again, you have to team up\n"
	.string "with me. You'll do that, right?$"
