// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/TPQuestPlugin

#pragma once

#include "Object.h"
#include "Quest.generated.h"

class UObjectiveBehavior;

UCLASS(Blueprintable, BlueprintType)
class TPQUEST_API UQuest : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Quest)
		TArray<UObjectiveBehavior*> Objectives;

	UFUNCTION(BlueprintCallable, Category = Quest)
		void InitObjectives();

	UFUNCTION(BlueprintCallable, Category = Quest)
		bool IsCompleted() const { return bIsCompleted; }

	virtual void Begin();

	virtual void Complete(const bool bSucceeded);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
		TArray<TSubclassOf<UObjectiveBehavior>> ObjectiveClasses;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Init"))
		void ReceiveBegin();

	// Called after Objective is completed and going to be removed from Quest
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Complete"))
		void ReceiveComplete(const bool bSucceeded);

private:
	bool bIsCompleted;

};
