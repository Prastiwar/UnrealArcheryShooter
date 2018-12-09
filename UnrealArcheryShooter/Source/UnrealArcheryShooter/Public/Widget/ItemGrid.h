// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/UniformGridPanel.h"
#include "UMG/Public/Components/UniformGridSlot.h"
#include "ItemGrid.generated.h"

UCLASS()
class UNREALARCHERYSHOOTER_API UItemGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void BuildGrid() { TArray<UUserWidget*> Array; RebuildGridDefault(Array); }

	virtual void SynchronizeProperties() override;

	UFUNCTION(BlueprintNativeEvent)
		void OnSynchronizeProperties();
	void OnSynchronizeProperties_Implementation() { BuildGrid(); }

	UFUNCTION(BlueprintNativeEvent)
		void OnDirty();
	virtual void OnDirty_Implementation() { BuildGrid(); }

	UFUNCTION(BlueprintCallable)
		void SetDirty() { OnDirty(); }

	// Shortcut for RebuildGrid<UUserWidget>(..)
	FORCEINLINE UFUNCTION(BlueprintCallable)
		void RebuildGridDefault(TArray<UUserWidget*>& OutArray) { RebuildGrid<UUserWidget>(OutArray); }

	// Clears grid, fills with ItemWidgetClass'es with RowCount and ColumnCount and add them to OutArray.
	template<typename T>
	FORCEINLINE void RebuildGrid(TArray<T*>& OutArray) { RebuildGrid<T>(RowCount, ColumnCount, OutArray); }

	// Clears grid, fills with ItemWidgetClass'es and add them to OutArray
	template<typename T>
	FORCEINLINE void RebuildGrid(const uint32 RowCount, const uint32 ColumnCount, TArray<T*>& OutArray)
	{
		TArray<T*> Array = TArray<T*>();
		if (Grid && ItemWidgetClass)
		{
			Grid->ClearChildren();
			for (uint32 Row = 0; Row < RowCount; Row++)
			{
				for (uint32 Column = 0; Column < ColumnCount; Column++)
				{
					UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), ItemWidgetClass);
					const int32 Index = Array.Add(Cast<T>(Widget));
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
		OutArray = Array;
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 RowCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 ColumnCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<UUserWidget> ItemWidgetClass;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UUniformGridPanel* Grid;

};
