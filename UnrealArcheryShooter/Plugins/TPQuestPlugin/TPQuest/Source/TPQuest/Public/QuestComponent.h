// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/TPQuestPlugin

#pragma once

#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"

class UQuest;

UCLASS(Blueprintable, BlueprintType)
class TPQUEST_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UQuestComponent();

	UFUNCTION(BlueprintCallable, Category = Quest)
		void AddQuest(UQuest* Quest);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quest)
		TArray<UQuest*> Quests;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
