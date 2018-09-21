// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UASHUD.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API AUASHUD : public AHUD
{
	GENERATED_BODY()

public:
	AUASHUD();

	virtual void DrawHUD() override;

private:
	class UTexture2D* CrosshairTex;

};
