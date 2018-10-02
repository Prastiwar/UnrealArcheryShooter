// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#include "ItemWidget.h"

void UItemWidget::SetItem(UTexture2D* Icon, FText Name, FText Cost)
{
	ItemImage->SetBrushFromTexture(Icon);
	ItemName->SetText(Name);
	ItemCost->SetText(Cost);
}
