// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "GameplayTags.h"
#include "PersonalUEWikiCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

struct FGenericStruct
{
	float X = 0.0f;
	int32 Z = 0;
	double Y = 0.0;
};

UCLASS(config=Game)
class APersonalUEWikiCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APersonalUEWikiCharacter();
	
	/**
	 * FName Filter
	 */
	
	UFUNCTION(BlueprintCallable)
	void Foo(FName Param);
	
	UFUNCTION(BlueprintCallable)
	void FooWithParams(UPARAM(meta = (GetOptions = FooParams)) FName Param);

	UFUNCTION()
	static TArray<FName> FooParams();

	UPROPERTY(EditDefaultsOnly, meta=(GetOptions = FooParams))
	FName FooProperty;

	/**
	 * Gameplay Tags Filter
	 */

	UFUNCTION(BlueprintCallable)
	void Tag(FGameplayTag InTag);
	
	UFUNCTION(BlueprintCallable)
	void TagWithCategory(UPARAM(meta=(Categories="Ability.Cooldown")) FGameplayTag InTag);

	UPROPERTY(EditDefaultsOnly, meta=(Categories="Ability.Cooldown"))
	FGameplayTag ExampleTag;

	/**
	 * Array Allocators
	 */
	
	void ArrayAllocatorsWiki();

	/**
	 * Multithreading
	 */

	void ParallelForWiki();

	/**
	 * Deferred code execution
	 */

	void DeferredCodeExecWiki();
	void ExampleOne();

	/**
	 * Algo namespace
	 */

	void AlgoNamespaceWiki();
	
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
};
