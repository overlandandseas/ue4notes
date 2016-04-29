//Character

/*
Character is a Pawn but with MovementComponent added. Thanks to that it can use
navigation and move around. Character have SkeletalMeshComponent added as well
so you can assign graphics representation by default.Let’s create new Character
and name it GameplayCharacter.


USEFUL TIP: On Mobile MovementComponent is expensive so if you are doing RTS
game with lot of Characters you should extend from Pawn and implement your own
movement.
https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/ACharacter/index.html
*/


//The Intial FPSCharacter.h
#pragma once

#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;



};
//
//
//
//The Inital FPSCharacter.cpp
#include "FPSProject.h"
#include "FPSCharacter.h"


// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFPSCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}
