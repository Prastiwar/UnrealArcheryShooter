// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "UI/ItemWidget.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/UniformGridPanel.h"
#include "UMG/Public/Components/UniformGridSlot.h"
#include "ItemGrid.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UItemGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		bool bAutoFill;

	UPROPERTY(EditAnywhere)
		uint32 RowCount;

	UPROPERTY(EditAnywhere)
		uint32 ColumnCount;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UItemWidget> ItemWidgetClass;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UUniformGridPanel* Grid;

	virtual void SynchronizeProperties() override;

	template<typename T>
	TArray<T*> FillGridImpl(uint32 RowCount, uint32 ColumnCount)
	{
		TArray<T*> Items = TArray<T*>();
		if (Grid && ItemWidgetClass)
		{
			Grid->ClearChildren();
			for (uint32 Row = 0; Row < RowCount; Row++)
			{
				for (uint32 Column = 0; Column < ColumnCount; Column++)
				{
					UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), ItemWidgetClass);
					int Index = Items.Add(Cast<T>(Widget));

					UUniformGridSlot* GridSlot = Grid->AddChildToUniformGrid(Widget);
					GridSlot->SetColumn(Column);
					GridSlot->SetRow(Row);
				}
			}
		}
		else
		{
			GLog->Log(TEXT("There is no Grid or ItemWidgetClass"));
		}
		return Items;
	}

	template<typename T>
	TArray<T*> FillGrid()
	{
		return FillGridImpl<T>(RowCount, ColumnCount);
	}

};
