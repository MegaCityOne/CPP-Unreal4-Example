// Copyright Epic Games, Inc. All Rights Reserved.

#include "res_publicaGameModeBase.h"

Ares_publicaGameModeBase::Ares_publicaGameModeBase()
{
	PlayerControllerClass = Aplayer_controller::StaticClass();
	DefaultPawnClass = Amain_map_camera_pawn::StaticClass();
}
