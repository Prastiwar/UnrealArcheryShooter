// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/UniformGridPanel.h"
#include "UMG/Public/Components/UniformGridSlot.h"
#include "UMG/Public/Components/Button.h"
#include "ItemGrid.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UItemGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 RowCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 ColumnCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class UUserWidget> ItemWidgetClass;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UUniformGridPanel* Grid;

	virtual void FillGrid() { FillUserGrid(); }

	virtual void SynchronizeProperties() override;
	UFUNCTION(BlueprintNativeEvent)
		void OnSynchronizeProperties();
	void OnSynchronizeProperties_Implementation() { FillGrid(); }

	UFUNCTION(BlueprintCallable)
		void SetDirty() { OnDirty(); }
	UFUNCTION(BlueprintNativeEvent)
		void OnDirty();
	void OnDirty_Implementation() { FillGrid(); }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE TArray<UUserWidget*> FillUserGrid() { return FillItemGrid<UUserWidget>(); }

	template<typename T>
	FORCEINLINE TArray<T*> FillItemGrid() { return FillItemGridImpl<T>(RowCount, ColumnCount); }

	template<typename T>
	FORCEINLINE TArray<T*> FillItemGridImpl(uint32 RowCount, uint32 ColumnCount)
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
			UE_LOG(LogTemp, Error, TEXT("There is no Grid or ItemWidgetClass"));
		}
		return Items;
	}

};
