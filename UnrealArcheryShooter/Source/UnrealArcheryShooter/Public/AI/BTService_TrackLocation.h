// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/UnrealArcheryShooter

#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_TrackLocation.generated.h"

USTRUCT(BlueprintType)
struct FActorLocationPair
{
	GENERATED_BODY()

public:
	FActorLocationPair() {}
	~FActorLocationPair() {}

	// Actor key to track location
	UPROPERTY(EditAnywhere)
		struct FBlackboardKeySelector ActorKey;

	// Output vector key to inject tracked location
	UPROPERTY(EditAnywhere)
		struct FBlackboardKeySelector VectorKey;
};

UCLASS()
class UNREALARCHERYSHOOTER_API UBTService_TrackLocation : public UBTService
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		TArray<FActorLocationPair> TrackActorLocations;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void OnGameplayTaskDeactivated(class UGameplayTask& Task) { Super::OnGameplayTaskDeactivated(Task); }
	virtual void OnGameplayTaskActivated(class UGameplayTask& Task) { Super::OnGameplayTaskActivated(Task); }

};
