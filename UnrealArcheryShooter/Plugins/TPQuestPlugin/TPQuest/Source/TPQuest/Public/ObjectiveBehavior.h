// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/TPQuestPlugin

#pragma once

#include "Object.h"
#include "ObjectiveBehavior.generated.h"

class UQuest;
class UQuestComponent;

UENUM(BlueprintType)
enum class EObjectiveResult : uint8
{
	InProgress,
	Succeed,
	Failed
};

UCLASS(Blueprintable, BlueprintType)
class TPQUEST_API UObjectiveBehavior : public UObject
{
	GENERATED_BODY()

public:
	UObjectiveBehavior();

	UFUNCTION(BlueprintCallable, Category = Quest)
		void AddProgress(int32 Progress) { CurrentProgress += Progress; }

	UFUNCTION(BlueprintCallable, Category = Quest)
		float GetNormalizedProgress() const { return (float)CurrentProgress / (float)NeededProgress; }

	// Called after Objective is completed and going to be removed from Quest
	UFUNCTION(BlueprintCallable, Category = Quest)
		void Complete(const bool bSucceed);

	virtual void Begin();

	virtual EObjectiveResult Execute(UQuest* Owner, UQuestComponent* QuestOwner, float DeltaTime);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
		int32 NeededProgress;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
		int32 CurrentProgress;

	EObjectiveResult CurrentResult;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Init"))
		void ReceiveBegin();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Execute"))
		void ReceiveExecute(UQuest* Owner, UQuestComponent* QuestOwner, float DeltaTime);

	// Called after Objective is completed and going to be removed from Quest
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Complete"))
		void ReceiveComplete(const bool bSucceed);

	// Called after Objective is completed and going to be removed from Quest
	virtual void CompleteImpl(const bool bSucceed) { ReceiveComplete(bSucceed); }

};
