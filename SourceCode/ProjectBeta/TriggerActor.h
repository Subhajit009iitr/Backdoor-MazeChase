// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerActor.generated.h"

UCLASS()
class PROJECTBETA_API ATriggerActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ATriggerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString s = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 checkpoint = 0;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void EndGame();

	UFUNCTION(BlueprintCallable, Category = "AES256")
		static FString Encrypt(FString InputString, FString Key);

	UFUNCTION(BlueprintCallable, Category = "AES256")
		static FString Decrypt(FString InputString, FString Key);

};
