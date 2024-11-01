// Copyright Epic Games, Inc. All Rights Reserved.

#include "PersonalUEWikiCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Algo/MaxElement.h"
#include "Algo/RandomShuffle.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APersonalUEWikiCharacter

APersonalUEWikiCharacter::APersonalUEWikiCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void APersonalUEWikiCharacter::Foo(FName Param)
{
}

void APersonalUEWikiCharacter::FooWithParams(FName Param)
{
}

TArray<FName> APersonalUEWikiCharacter::FooParams()
{
	static TArray<FName> Params = {"FirstFooParam", "SecondFooParam"};
	return Params;
}

void APersonalUEWikiCharacter::Tag(FGameplayTag Tag)
{
}

void APersonalUEWikiCharacter::TagWithCategory(FGameplayTag InTag)
{
}

void APersonalUEWikiCharacter::ArrayAllocatorsWiki()
{
	TArray<FGenericStruct, TInlineAllocator<1024>> InlineNodes;
	for(int32 i = 0; i < 1024; i++)
	{
		// This won't crash when allocating more than 1024 elements
		FGenericStruct& Node = InlineNodes.AddDefaulted_GetRef();
		Node.X = 111.0f;
		Node.Z = 111;
		Node.Y = 111.0;
	}

	TArray<FGenericStruct, TFixedAllocator<1024>> FixedNodes;
	for(int32 i = 0; i < 1024; i++)
	{
		// This will crash when allocating more than 1024 elements
		FGenericStruct& Node = FixedNodes.AddDefaulted_GetRef();
		Node.X = 111.0f;
		Node.Z = 111;
		Node.Y = 111.0;
	}
}

void APersonalUEWikiCharacter::ParallelForWiki()
{
	// Regular For

	TArray<AActor*> RegularAllActors;
	TArray<AActor*> RegularValidActors;
	for(AActor* Actor : RegularAllActors)
	{
		// Do something
		
		RegularValidActors.Add(Actor);
	}

	// Parallel For

	TArray<AActor*> ParallelAllActors;
	TQueue<AActor*, EQueueMode::Mpsc> ParallelValidActors;
	ParallelFor(ParallelAllActors.Num(), [&ParallelValidActors, &ParallelAllActors](int32 Index)
	{
		AActor* Actor = ParallelAllActors[Index];

		// Do something

		ParallelValidActors.Enqueue(Actor);
	});

	TArray<FVector> ParallelAllLocations;
	TQueue<FVector, EQueueMode::Mpsc> ParallelValidLocations;
	ParallelFor(ParallelAllLocations.Num(), [&ParallelValidLocations, &ParallelAllLocations](int32 Index)
	{
		const FVector& Vector = ParallelAllLocations[Index];

		// Do something

		ParallelValidLocations.Enqueue(Vector);
	});
}

void APersonalUEWikiCharacter::DeferredCodeExecWiki()
{
	ExampleOne();

	// Example two

	if(true)
	{
		ON_SCOPE_EXIT
		{
			UE_LOG(LogTemp, Warning, TEXT("World"));	
		};
		UE_LOG(LogTemp, Warning, TEXT("Hello"));	
	}
	UE_LOG(LogTemp, Warning, TEXT("!"));

	// This might be useful for something like this

	UObject* Ptr;
	ON_SCOPE_EXIT
	{
		delete Ptr;
	};

	// Any Handle
	FTimerHandle TimerHandle;
	ON_SCOPE_EXIT
	{
		TimerHandle.Invalidate();
	};
}

void APersonalUEWikiCharacter::ExampleOne()
{
	ON_SCOPE_EXIT
	{
		UE_LOG(LogTemp, Warning, TEXT("World!"));	
	};
	UE_LOG(LogTemp, Warning, TEXT("Hello"));	
}

void APersonalUEWikiCharacter::AlgoNamespaceWiki()
{
	struct Foo
	{
		int32 X;
		int32 Y;
		int32 Z;
	};

	TArray<Foo> FooArray = {{1, 2, 3}, {32, 213, 21}, {12, 312, 32}, {1, 6, 2}};
	Foo* MaxFooByX = Algo::MaxElementBy(FooArray, [](const Foo& FooElem)
	{
		return FooElem.X;
	});
	
	TArray<float> FloatyNumbers = {0.0f, 2.0f, 123.321f, 1.321f, 315.21f, 12.0f, 12.235f, 112.21f, 4.32f, 6.42f, 35.42f};

	float* Highest = Algo::MaxElement(FloatyNumbers);
	float Sum = Algo::Accumulate(FloatyNumbers,0, TPlus<>());
	Algo::HeapSort(FloatyNumbers);
	const int32 Index = Algo::BinarySearch(FloatyNumbers, 2.0f);
	float SearchedForElem = FloatyNumbers[Index];
	Algo::RandomShuffle(FloatyNumbers);
	Algo::Reverse(FloatyNumbers);
	Algo::Rotate(FloatyNumbers, 5);
	Algo::LowerBound(FloatyNumbers, 12.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void APersonalUEWikiCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	DeferredCodeExecWiki();
}

//////////////////////////////////////////////////////////////////////////
// Input

void APersonalUEWikiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APersonalUEWikiCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APersonalUEWikiCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APersonalUEWikiCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APersonalUEWikiCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}