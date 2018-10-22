// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "WeaponItem.h"
#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/ProgressBar.h"

void UWeaponItem::SetItem(UTexture2D* Icon, const bool bSelected)
{
	ItemImage->SetBrushFromTexture(Icon);
	ItemImage->SetOpacity(bSelected ? 1.0f : 0.2f);
}

void UWeaponItem::SetProgressPercentage(const float Percentage)
{
	CooldownProgress->SetPercent(Percentage);
}
