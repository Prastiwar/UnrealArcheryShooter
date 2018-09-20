// // Copyright 2018-2019 Tomasz Piowczyk, MIT License

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
