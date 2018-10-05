// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "ItemGrid.h"

void UItemGrid::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	FillGrid();
	OnSynchronizeProperties();
}
