// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "SpawnData.h"

FSpawnData::FSpawnData()
{
}

FSpawnData::FSpawnData(FLinearColor Color, float Score)
{
	this->Color = Color;
	this->Score = Score;
}

FSpawnData::~FSpawnData()
{
}
